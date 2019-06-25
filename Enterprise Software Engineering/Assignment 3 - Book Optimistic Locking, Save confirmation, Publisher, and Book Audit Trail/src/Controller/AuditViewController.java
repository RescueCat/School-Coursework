package Controller;

import java.io.IOException;
import java.net.URL;
import java.sql.SQLException;
import java.util.ResourceBundle;

import Model.AuditEntryModel;
import Model.BookModel;
import Model.BookTableGateway;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.scene.input.MouseEvent;

public class AuditViewController implements Initializable 
{
	private BookTableGateway gateway;
	private BookModel bookModel;
	private AuditEntryModel audit;
	@FXML private Button backButton;
	@FXML private Label contextLab;
	@FXML private TextArea auditText;
	private String AuditMessage;
	
	public AuditViewController(BookModel Book, BookTableGateway gateway) throws SQLException
	{
		this.gateway = gateway;
		this.bookModel = Book;
		this.audit = this.gateway.getAudits(Book);
	}
	
	@Override
	public void initialize(URL arg0, ResourceBundle arg1) 
	{
		String context = "Audit Trail for \"" + bookModel.getTitle() + "\"";
		contextLab.setText(context);
		auditText.setWrapText(true);
		auditText.setText(audit.getMessage());
		
		backButton.setOnMouseClicked(new EventHandler<MouseEvent>()
        {
			@Override
			public void handle(MouseEvent event) 
			{
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
