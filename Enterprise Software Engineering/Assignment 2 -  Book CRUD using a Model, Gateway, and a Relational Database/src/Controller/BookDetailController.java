package Controller;
import java.io.File;
import java.net.URL;
import java.sql.SQLException;
import java.text.NumberFormat;
import java.util.ResourceBundle;

import org.apache.log4j.Logger;

import Model.BookModel;
import Model.BookTableGateway;
import javafx.collections.ObservableList;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.input.MouseEvent;
import javafx.util.converter.NumberStringConverter;


public class BookDetailController implements Initializable
{
	private static Logger logger = Logger.getLogger(BookDetailController.class);
	
	public String BookTitle;
	private BookModel bookModel;
	@FXML public TextField myLab;
	@FXML private Label aLabel;
	@FXML private TextField isbnLabel;
	@FXML private TextField pubLabel;
	@FXML private ImageView bookImage;
	@FXML private Label dateAddLabel;
	@FXML private TextArea summaryArea;
	@FXML private Button saveButton;
	private BookTableGateway gateway;

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
		//Attempt to update the entries if pass validation
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
				boolean pass = bookModel.save(newTitle, newYear, newISBN, bookId);
				
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
        
	}
	
}
