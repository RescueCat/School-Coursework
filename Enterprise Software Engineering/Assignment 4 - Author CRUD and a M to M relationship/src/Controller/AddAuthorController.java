package Controller;

import java.io.IOException;
import java.net.URL;
import java.sql.SQLException;
import java.text.SimpleDateFormat;
import java.time.LocalDate;
import java.util.ResourceBundle;

import Model.AuthorBookModel;
import Model.AuthorModel;
import Model.BookModel;
import Model.BookTableGateway;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.input.MouseEvent;

public class AddAuthorController implements Initializable 
{
	private BookTableGateway gateway;
	private BookModel bookModel;
	private AuthorModel author;
	//private AuthorBookModel authorBook;
	
	@FXML private TextField firstName;
	@FXML private TextField lastName;
	@FXML private TextField dateOfBirth;
	@FXML private TextField genderF;
	@FXML private TextField websiteF;
	@FXML private TextField royaltiesF;
	@FXML private Button addButton;
	@FXML private Button cancelButton;
	
	public AddAuthorController(BookModel Book, BookTableGateway gateway) throws SQLException
	{
		this.gateway = gateway;
		this.bookModel = Book;
	}
	
	@Override
	public void initialize(URL location, ResourceBundle resources) 
	{
		/*Add Author and Royalty
		 * 
		 * */
		addButton.setOnMouseClicked(new EventHandler<MouseEvent>()
        {
					@Override
					public void handle(MouseEvent arg0) 
					{
						/*String firstN = "Default First";
						String lastN = "Default Last";
						String dOB = "2018-11-27";
						String gender = "none";
						String website = "www.google.com";
						String royalties = "0.0";*/
						author = new AuthorModel();
						String royalties = "0.0";
						String dOB = "2018-11-27";
						//authorBook = new AuthorBookModel();
						
						if(! firstName.getText().isEmpty()) 
						{
							author.setFName(firstName.getText());
						}
						if(! lastName.getText().isEmpty())
						{
							author.setLName(lastName.getText());
						}
						if(! dateOfBirth.getText().isEmpty())
						{
							dOB = dateOfBirth.getText();
							LocalDate localDate = LocalDate.parse(dOB);
							author.setDOB(localDate);
						}
						if(! genderF.getText().isEmpty())
						{
							author.setGender(genderF.getText());
						}
						if(! websiteF.getText().isEmpty())
						{
							author.setWeb(websiteF.getText());
						}
						if(! royaltiesF.getText().isEmpty())
						{
							royalties = royaltiesF.getText();
						}
						
						try {
							gateway.CreateNewAuthorRoyalty(author, royalties, dOB, bookModel);
						} catch (SQLException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}
						
						try {
							MenuController.getInstance().ShowBookDetail(bookModel);
						} catch (IOException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}
					}
        });

	}

}
