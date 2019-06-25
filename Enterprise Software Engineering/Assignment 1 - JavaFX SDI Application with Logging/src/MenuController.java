import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;

import org.apache.log4j.Logger;

import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.control.Button;
import javafx.scene.layout.BorderPane;

public class MenuController 
{
	private static Logger logger = Logger.getLogger(MenuController.class);
	
	private static MenuController myInstance = null;
	private BorderPane rootpane = null; 
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
	
	public void ShowBookList() throws IOException
	{
		BookListController blController = new BookListController();
		FXMLLoader loader = new FXMLLoader(this.getClass().getResource("BookListView.fxml"));
		loader.setController(blController); //make this controller
		Parent bookList = loader.load();
		rootpane.setLeft(bookList);
	}
	
	public void ShowBookDetail(ObservableList<String> theBookTitle) throws IOException
	{
		BookDetailController bdController = new BookDetailController(theBookTitle);
		FXMLLoader loader = new FXMLLoader(this.getClass().getResource("BookDetailView.fxml"));
		loader.setController(bdController); //make this controller
		Parent bookDetail = loader.load();
		rootpane.setRight(bookDetail);
	}
	
	
	public void ExitOn() throws IOException
	{
		logger.info("Exiting application.");
		System.exit(0);
	}
	
	
}
