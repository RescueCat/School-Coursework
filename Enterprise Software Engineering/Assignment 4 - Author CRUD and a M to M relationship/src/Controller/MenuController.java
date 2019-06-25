package Controller;
import java.io.IOException;
import java.net.URL;
import java.sql.Connection;
import java.sql.SQLException;
import java.util.ResourceBundle;

import org.apache.log4j.Logger;

import Model.BookModel;
import Model.BookTableGateway;
import app.Launcher;
import javafx.application.Platform;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.control.Button;
import javafx.scene.layout.BorderPane;

public class MenuController
{
	private static Logger logger = Logger.getLogger(MenuController.class);
	
	private Connection conn;
	
	private static MenuController myInstance = null;
	private BorderPane rootpane = null; 
	private Parent bookList;
	private Parent bookDetail;
	private Parent bookAdd;
	private Parent auditTrail;
	private Parent addAuthorR;
	public Button blButton;
	
	public static MenuController getInstance()
	{
		if(myInstance == null)
			myInstance = new MenuController();
		return myInstance;
	}

	private MenuController()
	{
	}
	
	public void setRootPane(BorderPane rootPane) 
	{
		this.rootpane = rootPane;
	}
	
	public BorderPane getRootPane()
	{
		return rootpane;
	}
	
	public void ShowBookList() throws IOException, SQLException
	{
		BookListController blController = new BookListController(new BookTableGateway(conn));
		FXMLLoader loader = new FXMLLoader(this.getClass().getResource("/View/BookListView.fxml"));
		loader.setController(blController); //make this controller
		bookList = loader.load();
		rootpane.getChildren().remove(bookAdd);
		rootpane.setLeft(bookList);
	}
	
	public void ShowBookDetail(BookModel book) throws IOException
	{
		BookDetailController bdController = new BookDetailController(book, new BookTableGateway(conn));
		FXMLLoader loader = new FXMLLoader(this.getClass().getResource("/View/BookDetailView.fxml"));
		loader.setController(bdController); //make this controller
		bookDetail = loader.load();
		rootpane.getChildren().remove(bookAdd);
		rootpane.getChildren().remove(auditTrail);
		rootpane.setRight(bookDetail);
	}
	
	public void ShowAddBook() throws IOException
	{
		BookAddController baController = new BookAddController(new BookTableGateway(conn));
		FXMLLoader loader = new FXMLLoader(this.getClass().getResource("/View/BookAddView.fxml"));
		loader.setController(baController);
		bookAdd = loader.load();
		rootpane.getChildren().remove(bookDetail);
		rootpane.getChildren().remove(bookList);
		rootpane.setCenter(bookAdd);
	}
	
	public void setConnection(Connection conn)
	{
		this.conn = conn;
	}
	
	public void ShowAuditEntry(BookModel bookModel) throws IOException, SQLException
	{
		AuditViewController avController = new AuditViewController(bookModel, new BookTableGateway(conn));
		FXMLLoader loader = new FXMLLoader(this.getClass().getResource("/View/AuditTrailView.fxml"));
		loader.setController(avController);
		auditTrail = loader.load();
		rootpane.getChildren().remove(bookDetail);
		rootpane.setRight(auditTrail);
		
	}
	
	public void ShowAddAuthor(BookModel bookModel) throws SQLException, IOException 
	{
		AddAuthorController aaController = new AddAuthorController(bookModel, new BookTableGateway(conn));
		FXMLLoader loader = new FXMLLoader(this.getClass().getResource("/View/AddAuthorRoyalty.fxml"));
		loader.setController(aaController);
		addAuthorR = loader.load();
		rootpane.getChildren().remove(bookDetail);
		rootpane.setRight(addAuthorR);
	}
	
	public void ExitOn() throws IOException
	{
		logger.info("Exiting application from save button.");
		Platform.exit();
	}
}
