package Model;

import javafx.beans.property.DoubleProperty;
import javafx.beans.property.SimpleDoubleProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public class AuthorBookModel 
{
	private BookModel book;
	private int authorID;
	private int bookID;
	private boolean newRecord;
	
	//Start work here
	private SimpleStringProperty author;
	private SimpleDoubleProperty royalty;
	
	private String authorS;
	private double royaltyS;
	
	//Constructor
	public AuthorBookModel(String string, double d) 
	{
		this.authorS = string;
		this.royaltyS = d;
		
		this.author = new SimpleStringProperty("default name");
		this.royalty = new SimpleDoubleProperty(0.00);
		this.newRecord = true;
	}
	public AuthorBookModel()
	{
		this.royalty = new SimpleDoubleProperty(0.00);
	}
	
	public void setAuthor(String s)
	{
		author.set(s);
	}
	
	public void setRoyalty(double s)
	{
		royalty.set(s);
	}

	public String getAuthor()
	{
		//return author.get();
		return authorS;
	}
	
	public String getAuthor2()
	{
		return author.get();
	}
	public double getRoyalty()
	{
		//return royalty.get();
		return royaltyS;
	}
	
	public StringProperty authorSProperty()
	{
		//this.author = new SimpleStringProperty(authorS);
		return author;
	}
	
	public DoubleProperty royaltySProperty()
	{
		//this.royalty = new SimpleDoubleProperty(royaltyS);
		return royalty;
	}
	//End Work Here



	public void setAuthorID(int int1) 
	{
		this.authorID = int1;
		
	}

	public void setBookID(int int1) 
	{
		this.bookID = int1;
		
	}

	public int getAuthorID() 
	{
		// TODO Auto-generated method stub
		return authorID;
	}

	public int getBookID() 
	{
		// TODO Auto-generated method stub
		return bookID;
	}
}
