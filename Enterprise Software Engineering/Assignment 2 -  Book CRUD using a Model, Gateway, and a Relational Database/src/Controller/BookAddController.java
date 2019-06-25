package Controller;

import java.net.URL;
import java.sql.SQLException;
import java.util.ResourceBundle;

import org.apache.log4j.Logger;

import Model.BookModel;
import Model.BookTableGateway;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.input.MouseEvent;

public class BookAddController implements Initializable 
{
	private static Logger logger = Logger.getLogger(BookAddController.class);
	
	private BookTableGateway gateway;
	private BookModel book;
	
	@FXML private TextField pubIdF;
	@FXML private TextField titleF;
	@FXML private TextField yearF;
	@FXML private TextField isbnF;
 	@FXML private TextArea summaryF;
 	@FXML private Button saveButtAdd;
	
	public BookAddController(BookTableGateway gateway)
	{
		this.gateway = gateway;
	}
	
	public BookAddController(BookModel book) 
	{
		this.book = book;	
	}
	
	public void addBook() throws SQLException
	{
		BookModel book = new BookModel();
		
		//Get updated field information
		String newTitle = titleF.getText();		//Title
		String newYear = yearF.getText();		//Publishing Year
		String newISBN = isbnF.getText();		//ISBN
		String newpubIdF = pubIdF.getText();	//Publishing ID
		String newSumm = summaryF.getText();	//summary
		
		if(newSumm.length()>= 65536 || newSumm.length()<= 0)
		{
			newSumm = "n/a";
			book.setSummary(newSumm);
		}
		else
		{
			book.setSummary(newSumm);
		}
		
		boolean pass = book.save(newTitle, newYear, newISBN, 0);
		
		if(pass != true)
		{
			logger.info("Insert failed.");
			Alert alert = new Alert(AlertType.ERROR);
			
			alert.setHeaderText("Save Aborted");
			alert.setContentText("One or many fields does not meet criteria.");

			alert.showAndWait();
		}
		else
		{
			
			gateway.addBooktoDB(book);
		}
	}

	@Override
	public void initialize(URL arg0, ResourceBundle arg1) 
	{
		
		summaryF.setWrapText(true);
		saveButtAdd.setOnMouseClicked(new EventHandler<MouseEvent>()
		{
			public void handle(MouseEvent event) 
			{
				try {
					addBook();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		});
		
	}

}
