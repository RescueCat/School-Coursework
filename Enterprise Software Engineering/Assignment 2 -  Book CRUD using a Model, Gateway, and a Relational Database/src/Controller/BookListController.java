package Controller;
import java.util.List;
import java.util.ResourceBundle;

import Model.BookModel;
import Model.BookTableGateway;
import Controller.MenuController;

import org.apache.log4j.Logger;

import java.io.IOException;
import java.lang.Object;
import java.net.URL;
import java.sql.SQLException;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.control.Button;
import javafx.scene.control.ListView;
import javafx.scene.input.MouseEvent;

public class BookListController implements Initializable
{
	private static Logger logger = Logger.getLogger(BookListController.class);
	@FXML public ListView<BookModel> BookList;
	private ObservableList<BookModel> books; 
	private BookTableGateway gateway;
	private BookModel book;
	@FXML private Button deleteButton;
	
	public BookListController(BookTableGateway gateway) throws SQLException
	{
		this.gateway = gateway;
		books = this.gateway.getBooks();
	}
	
	public BookListController(ObservableList<BookModel> books)
	{
		this.books = books;
	}
	

	@Override
	public void initialize(URL location, ResourceBundle resources)
	{
		this.BookList.setItems(books);

		
		BookList.setOnMouseClicked(new EventHandler<MouseEvent>() 
		{
			@Override
			public void handle(MouseEvent arg0)
			{
				if(arg0.getClickCount()==2)
				{
					BookModel book = BookList.getSelectionModel().getSelectedItem();
					ObservableList<BookModel> theBookTitle = BookList.getSelectionModel().getSelectedItems();
					BookModel bookT = theBookTitle.get(0);
					logger.info("The book title \"" + bookT + "\" was double clicked.");
					try {
						MenuController.getInstance().ShowBookDetail(book);
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
			}
		});
		
		deleteButton.setOnMouseClicked(new EventHandler<MouseEvent>()
		{
			@Override
			public void handle(MouseEvent arg0) 
			{
				BookModel book = BookList.getSelectionModel().getSelectedItem();
				//If nothing is selected delete nothing
				if(book == null)
				{
					logger.info("Delete Button pressed but nothing selected");
				}
				else //delete selected
				{
					gateway.deleteBook(book);
					
					//Refresh List
					try {
						books = gateway.getBooks();
					} catch (SQLException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					
					//Clear deleted book data from view
					MenuController.getInstance().getRootPane().setRight(null);
					
					//Populate viewlist with regenerated list
					BookList.setItems(books);
				}
				
			}
		});
	}

}
