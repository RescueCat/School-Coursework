import java.util.List;

import org.apache.log4j.Logger;

import java.io.IOException;
import java.lang.Object;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.EventHandler;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.control.ListView;
import javafx.scene.input.MouseEvent;

public class BookListController 
{
	private static Logger logger = Logger.getLogger(BookListController.class);
	public ListView<String> BookList;
	
	public void initialize() 
	{		
		ObservableList<String> data = FXCollections.observableArrayList(
				"Island of the Blue Dolphins",
				"The Cat in the Hat",
				"In Search of Lost Time",
				"Don Quixote",
				"Ulysses",
				"Island of the Blue Dolphins",
				"The Cat in the Hat",
				"In Search of Lost Time",
				"Don Quixote",
				"Ulysses",
				"Island of the Blue Dolphins",
				"The Cat in the Hat",
				"In Search of Lost Time",
				"Don Quixote",
				"Ulysses",
				"Island of the Blue Dolphins",
				"The Cat in the Hat",
				"In Search of Lost Time",
				"Don Quixote",
				"Ulysses"
				);
		BookList.setItems(data);
		
		BookList.setOnMouseClicked(new EventHandler<MouseEvent>() 
		{
			@Override
			public void handle(MouseEvent arg0)
			{
				if(arg0.getClickCount()==2)
				{
					ObservableList<String> theBookTitle = BookList.getSelectionModel().getSelectedItems();
					String bookT = theBookTitle.get(0);
					logger.info("The book title \"" + bookT + "\" was double clicked.");
					try {
						MenuController.getInstance().ShowBookDetail(theBookTitle);
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
			}
		});
	}
}
