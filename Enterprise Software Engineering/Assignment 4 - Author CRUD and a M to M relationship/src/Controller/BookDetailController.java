package Controller;
import java.io.File;
import java.io.IOException;
import java.net.URL;
import java.sql.SQLException;
import java.text.DecimalFormat;
import java.text.NumberFormat;
import java.util.ArrayList;
import java.util.Locale;
import java.util.ResourceBundle;

import org.apache.log4j.Logger;

import Model.AuthorBookModel;
import Model.BookModel;
import Model.BookTableGateway;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.geometry.Insets;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.Button;
import javafx.scene.control.ButtonBar.ButtonData;
import javafx.scene.control.ButtonType;
import javafx.scene.control.Dialog;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableColumn.CellEditEvent;
import javafx.scene.control.TableView;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.control.TextInputDialog;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.control.cell.TextFieldTableCell;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.GridPane;
import javafx.util.Pair;
import javafx.util.converter.DoubleStringConverter;
import javafx.util.converter.NumberStringConverter;


public class BookDetailController implements Initializable
{
	private static Logger logger = Logger.getLogger(BookDetailController.class);
	
	public String BookTitle;
	private BookModel bookModel;
	private ObservableList<AuthorBookModel> authorBook;
	@FXML public TextField myLab;
	@FXML private Label aLabel;
	@FXML private TextField isbnLabel;
	@FXML private TextField pubLabel;
	@FXML private ImageView bookImage;
	@FXML private Label dateAddLabel;
	@FXML private TextArea summaryArea;
	@FXML private Button saveButton;
	@FXML private Button auditButton;
	private BookTableGateway gateway;
	
	@FXML private TableView<AuthorBookModel> arTable;
	@FXML private TableColumn<AuthorBookModel, String> authorTable;
	@FXML private TableColumn<AuthorBookModel, Double> royaltyTable;
	
	@FXML private Button addAuthor;
	@FXML private Button deleteAuthor;
	
	public BookDetailController(BookModel book, BookTableGateway gateway)  
	{
		this.gateway = gateway;
		this.bookModel = book;
	}

	@Override
	public void initialize(URL arg0, ResourceBundle arg1)
	{
		//Set Title 
		myLab.textProperty().bindBidirectional(bookModel.titleproperty());
		
		//Set Publishing  
		NumberFormat format = NumberFormat.getIntegerInstance();	//format for commas
		format.setGroupingUsed(false);								//set to no commas
		pubLabel.textProperty().bindBidirectional(bookModel.yearPublishedProperty(), new NumberStringConverter(format));
		
		//Set ISBN 
		isbnLabel.textProperty().bindBidirectional(bookModel.isbnproperty(), new NumberStringConverter(format));
		
		//Set Date Added
		dateAddLabel.setText("Date Added : " + bookModel.getDateAdded());
		
		//Set Summary
        summaryArea.setWrapText(true);
        summaryArea.setText(bookModel.getSummary());
        
        //Set image
        if(bookModel.getImgUrl() != null)
        {
        	Image img = new Image(bookModel.getImgUrl());
        	bookImage.setImage(img);
        }
        
        /* Author/Royalties area
         * 
         * */
        //Set to editable
        arTable.setEditable(true);
        
        //Get Data
        authorBook = FXCollections.observableArrayList();
        
        try {
			authorBook = gateway.getAuthorsForBook(bookModel);
		} catch (SQLException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}

        //Set up the Columns
        //TODO need to set max and min parameters for these cells
        //String Editable Values
        authorTable.setCellValueFactory(new PropertyValueFactory<AuthorBookModel, String>("authorS"));     
        authorTable.setCellFactory(TextFieldTableCell.<AuthorBookModel>forTableColumn());
        authorTable.setOnEditCommit(new EventHandler<CellEditEvent<AuthorBookModel, String>>() {
        	@Override
        	public void handle(CellEditEvent<AuthorBookModel, String> t)
        	{
        		t.getTableView().getItems().get(t.getTablePosition().getRow()).setAuthor(t.getNewValue());
        	}
        });
        //Double Editable Values
        //TODO Should check for size decimal(6,5)
        royaltyTable.setCellValueFactory(new PropertyValueFactory<AuthorBookModel, Double>("royaltyS"));
        royaltyTable.setCellFactory(TextFieldTableCell.<AuthorBookModel, Double>forTableColumn(new DoubleStringConverter()));
        royaltyTable.setOnEditCommit(new EventHandler<CellEditEvent<AuthorBookModel, Double>>(){
        	@Override
        	public void handle(CellEditEvent<AuthorBookModel, Double> t)
        	{
        		/*NumberFormat f = NumberFormat.getNumberInstance(Locale.US);
        		f.setMinimumFractionDigits(5);
        		String oldDoubleS = f.format(t.getOldValue());
        		System.out.println("Old double: " + oldDoubleS);
        		//Double oldDouble = Double.parseDouble(String.format("%.5f", oldDoubleS));
        		
        		
        		System.out.println(t.getNewValue() + " " + oldDoubleS);*/
        		try {
					gateway.commitNewRValue(bookModel, t.getNewValue(), t.getOldValue());
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
        		t.getTableView().getItems().get(t.getTablePosition().getRow()).setRoyalty(t.getNewValue()); //clear from view
        		
        	}
        });
        
        //Set data
        arTable.setItems(authorBook);
        
     
        
		/*Attempt to update the entries if pass validation
		 * 
		 **/
        saveButton.setOnMouseClicked(new EventHandler<MouseEvent>()
        {
			@Override
			public void handle(MouseEvent event) 
			{
				logger.info("Save button was pressed while viewing book title \"" + BookTitle + "\".");
				
				//Get updated field information
				String newTitle = myLab.getText();
				String newYear = pubLabel.getText();
				String newISBN = isbnLabel.getText();
				String newSumm = summaryArea.getText();
				int bookId = bookModel.getId();
				
				//Check summary length 
				if(newSumm.length()>= 65536 || newSumm.length()<= 0)
				{
					newSumm = "n/a";
					bookModel.setSummary(newSumm);
				}
				else
				{
					bookModel.setSummary(newSumm);
				}
				
				//Call update
				boolean pass = bookModel.save(newTitle, newYear, newISBN, bookId, newSumm);
				
				//If one or any of the fields does noe meet criteria, save will be aborted.
				if(pass!= true)
				{
					logger.info("Update failed.");
					Alert alert = new Alert(AlertType.ERROR);
					
					alert.setHeaderText("Save Aborted");
					alert.setContentText("One or many fields does not meet criteria.");

					alert.showAndWait();
				}
				else
				{
					try {
						gateway.updateBook(bookModel);
					} catch (SQLException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
				
			}
        });
        
        /*Pull up audit trail
         * 
         * */
        auditButton.setOnMouseClicked(new EventHandler<MouseEvent>()
        {
			@Override
			public void handle(MouseEvent event) 
			{
				try {
					MenuController.getInstance().ShowAuditEntry(bookModel);
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				
			}
        });
        
        /*Add author to book and royalty
         * 
         * */
        addAuthor.setOnMouseClicked(new EventHandler<MouseEvent>()
        {
			@Override
			public void handle(MouseEvent event) 
			{
				try {
					MenuController.getInstance().ShowAddAuthor(bookModel);
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				
			}
        });
        
        
        /*Remove Author/Royalty from List and Database
         * 
         * */
        deleteAuthor.setOnMouseClicked(new EventHandler<MouseEvent>()
        {
					@Override
					public void handle(MouseEvent arg0) 
					{
						int selectedIndex = arTable.getSelectionModel().getSelectedIndex();
						int authorID = authorBook.get(selectedIndex).getAuthorID();
						int bookID = authorBook.get(selectedIndex).getBookID();
						
						//remove from database
						try {
							gateway.deleteAuthorRoyal(authorID, bookID, authorBook.get(selectedIndex));
						} catch (SQLException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}
						
						arTable.getItems().remove(selectedIndex);	
					}
        });
        
	}
	
	/*public void onShow()
	{
		System.out.println("Will show now");
	}
	
	public boolean isDifferent()
	{
		//If any of the fields are different we return true
		if(Integer.toString(bookModel.getYearPublished()) != pubLabel.getText())
		{
			return true;
		}
		//Else we return false
		else
		{
			return false;
		}
	}*/
}
