import java.io.File;
import java.net.URL;
import java.util.ResourceBundle;

import org.apache.log4j.Logger;

import javafx.collections.ObservableList;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.input.MouseEvent;


public class BookDetailController implements Initializable
{
	private static Logger logger = Logger.getLogger(BookDetailController.class);
	
	public String BookTitle;
	private BookModel bookModel;
	@FXML public Label myLab;
	@FXML private Label aLabel;
	@FXML private Label isbnLabel;
	@FXML private Label pubLabel;
	@FXML private ImageView bookImage;
	@FXML private Label dateAddLabel;
	@FXML private TextArea summaryArea;
	@FXML private Button saveButton;

	public BookDetailController(ObservableList<String> theBookTitle)  
	{
		this.BookTitle = theBookTitle.get(0);
		bookModel = new BookModel(BookTitle);
	}

	@Override
	public void initialize(URL arg0, ResourceBundle arg1) 
	{
		myLab.setText("Title: " + this.BookTitle);
		
		String author = bookModel.getAuthor();
		aLabel.setText("Author: " + author);
		
		String publish = bookModel.getPublisher();
		pubLabel.setText("Publisher: " + publish);
		
		String isbn = bookModel.getISBN();
		isbnLabel.setText("ISBN: " + isbn);
		
		String imgURL = bookModel.getImgUrl();
		File file = new File(imgURL);
        Image image = new Image(file.toURI().toString());
        bookImage.setImage(image);
		
        dateAddLabel.setText("Date Added: 08/29/2018");
        
        String summary = bookModel.getSumary();
        summaryArea.setWrapText(true);
        summaryArea.setText(summary);
        
        saveButton.setOnMouseClicked(new EventHandler<MouseEvent>()
        {
			@Override
			public void handle(MouseEvent event) 
			{
				logger.info("Save button was pressed while viewing book title \"" + BookTitle + "\".");
				
			}
        });
        
	}
	
}
