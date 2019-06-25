package Model;

import java.sql.SQLException;
import java.sql.Timestamp;
import java.time.LocalDateTime;

import org.apache.log4j.Logger;

import Controller.BookDetailController;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleLongProperty;
import javafx.beans.property.SimpleObjectProperty;
import javafx.beans.property.SimpleStringProperty;

public class BookModel 
{
	private static Logger logger = Logger.getLogger(BookModel.class);
	
	private SimpleStringProperty theBookTitle;		//title
	private String Author;
	private SimpleLongProperty ISBN;				//isbn
	private String Publisher;
	private String imgURL;
	private SimpleStringProperty Summary;				//summary
	private int id;						//id
	private SimpleIntegerProperty yearPublished;			//year published
	private SimpleObjectProperty<LocalDateTime> dateAdded;	//date added
	private LocalDateTime lastModified;
	
	private BookTableGateway gatewayModel;
	
	public BookModel(String bookTitle) 
	{
		this.theBookTitle = new SimpleStringProperty(bookTitle);
		this.ISBN = new SimpleLongProperty(0);
		this.Summary = new SimpleStringProperty(null);
		this.yearPublished = new SimpleIntegerProperty(2018); 
	    this.dateAdded = new SimpleObjectProperty<LocalDateTime>();
	    this.lastModified = null;
	    this.setId(0);
		
	}
	
	//For making new book. Please make sure null and default values are set in constructor
	public BookModel()
	{
		this("Untitled Book");
	}

	public SimpleStringProperty titleproperty() {
		// TODO Auto-generated method stub
		return this.theBookTitle;
	}
	
	public SimpleIntegerProperty yearPublishedProperty() 
	{
		// TODO Auto-generated method stub
		return this.yearPublished ;
	}
	
	public SimpleLongProperty isbnproperty() 
	{
		
		return this.ISBN;
	}
	
	public String toString() 
	{
		return this.theBookTitle.get();
	}

	//Setters:
	//ID
	public void setId(int intId)
	{
		this.id = intId;
	}
		
	//Title
	public void setTitle(String stringTitle) 
	{
		this.theBookTitle.set(stringTitle);
	}
	
	//Summary
	public void setSummary(String stringSumm) 
	{
		this.Summary.set(stringSumm);
	}
	
	public void setYearPublished(int intYearPublished) 
	{
		this.yearPublished.set(intYearPublished);
	}
	
	public void setISBN(long longISBN) 
	{
		this.ISBN.set(longISBN);
	}
	
	public void setDateAdded(Timestamp timestamp) 
	{
		
		this.dateAdded.setValue(timestamp.toLocalDateTime());
	}
	
	public void setLastModified(Timestamp timestamp) 
	{
		if(timestamp == null)
		{
			this.lastModified = null;
		}
		else
		{
			this.lastModified = timestamp.toLocalDateTime();
		}
	}
	
	public void setImgUrl(String img_url) 
	{
		
		this.imgURL = img_url;
	}
	
	/*Don't Need Right Now
	private void setPublisher(String[] bookInfo) 
	{
		this.Publisher = bookInfo[2];
	}

	private void setAuthor(String[] bookInfo) 
	{
		this.Author = bookInfo[0];
	}
	
	*/
	
	//Getters
	//Date Added
	public String getDateAdded()
	{
		String theTimeandDate = dateAdded.getValue().toString();
		String newTime = theTimeandDate.replace("T", " ");
		return newTime;
	}
	
	public String getSummary()
	{
		return this.Summary.getValue();
	}
	
	//Id
	public int getId()
	{
		return id;
	}
	
	//Title
	public String getTitle()
	{
		return theBookTitle.getValue();
	}
	
	public int getYearPublished()
	{
			return yearPublished.getValue();
	}
	
	public long getISBN() 
	{	
		return ISBN.getValue();	
	}
	
	public String getImgUrl()
	{
		return imgURL;
	}
	
	public LocalDateTime getLastModified() 
	{
		return lastModified;
	}
	
	//Summary
	/*public String getSumary()
	{
		return Summary;
	}*/
	
	//Year Published
	/*private int Published()
	{
			return yearPublished;
	}
	
	//ISBN
	public String getISBN() 
	{
		return ISBN;	
	}
	
	//Date Added
	private LocalDateTime getDateAdded()
	{
			return dateAdded;
	}*/
	
	
	//Don't Need
	public String getPublisher() 
	{
		return Publisher;
	}

	public String getAuthor() 
	{
		return Author;	
	}



	public void save(BookModel book)
	{

	}
	
	//Attempt to save the book information back to database
	public boolean save(String newTitle, String newYear, String newISBN, int currentID, String newSumm)
	{
		//If year is empty
		if (newYear.isEmpty())
			newYear = "2018";
		if(newISBN.isEmpty())
			newISBN = "0";
		
		boolean pass1 = validateTitle(newTitle);
		boolean pass2 = validateYear(newYear);	int newnewYear = Integer.parseInt(newYear);
		boolean pass3 = validateISBN(newISBN);	long newnewISBN = Long.parseLong(newISBN);
		
		if(pass1 == true && pass2 == true && pass3 == true)//execute save
		{
			//copy changed values to original model
			this.setTitle(newTitle);
			this.setYearPublished(newnewYear);
			this.setISBN(newnewISBN);
			this.setSummary(newSumm);
			return true;
		}
		else//abort save
		{
			return false;
		}
	}

	public boolean validateTitle(String newTitle)
	{
		if((newTitle.length() >= 256) || (newTitle.length() <= 0))
		{
			logger.info("Save book length is too large (over 255) or too small (under 1)");
			return false;
		}
		else
			return true;
	}
	
	public boolean validateYear(String newYear)
	{
		int testYear = Integer.parseInt(newYear);
		if(testYear >= 2019 || newYear.length() != 4 )
		{
			logger.info("Save book publishing date is past current year or isn't a 4-digit year");
			return false;
		}
		else
			return true;
	}
	
	public boolean validateISBN(String newISBN)
	{
		if(newISBN.length()>=14)
		{
			logger.info("Save book ISBN is too large (over 13 characters");
			return false;
		}
			else
			return true;
	}
}
