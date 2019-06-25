package Model;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.Optional;

import org.apache.log4j.Logger;

import Controller.BookAddController;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.ButtonType;

public class BookTableGateway 
{
	private static Logger logger = Logger.getLogger(BookTableGateway.class);
	
	private Connection conn;
	
	public BookTableGateway(Connection conn)
	{
		this.conn = conn;
	}
	
	
	
	public ObservableList<BookModel> getBooks() throws SQLException
	{
		ObservableList<BookModel> books = FXCollections.observableArrayList();
		
		PreparedStatement st = conn.prepareStatement("SELECT * FROM bookdb");
		ResultSet rs = st.executeQuery();
		
		while(rs.next())
		{
			BookModel book = new BookModel(rs.getString("title"));
			book.setId(rs.getInt("id"));
			book.setSummary(rs.getString("summary"));
			book.setYearPublished(rs.getInt("year_published"));
			book.setISBN(rs.getLong("isbn"));
			book.setDateAdded(rs.getTimestamp("date_added"));
			book.setImgUrl(rs.getString("img_url"));
			book.setLastModified(rs.getTimestamp("last_modified"));
			books.add(book);
		}

		return books;
	}
	
	public AuditEntryModel getAudits(BookModel book) throws SQLException
	{
		AuditEntryModel audit = new AuditEntryModel();
		PreparedStatement st = conn.prepareStatement("SELECT entry_msg, date_added FROM book_audit_trail WHERE book_id = ?");
		st.setInt(1, book.getId());
		ResultSet rs = st.executeQuery();
		while(rs.next())
		{
			audit.setMessage(rs.getTimestamp("date_added"), rs.getString("entry_msg"));
		}
		
		return audit;
	}
	
	public ObservableList<String> getTitles() throws SQLException
	{
		ObservableList<String> titleList = FXCollections.observableArrayList();
		
		PreparedStatement st = conn.prepareStatement("SELECT * FROM bookdb");
		ResultSet rs = st.executeQuery();
		
		while(rs.next())
		{
			titleList.add(rs.getString("title"));
		}
		
		return titleList;
	}

	public void updateBook(BookModel Book) throws SQLException 
	{
		// TODO Auto-generated method stub
		PreparedStatement st = null;
		PreparedStatement st2 = null;
		
		//System.out.print(Book.getTitle() + " " + Book.getYearPublished() + " " + Book.getISBN() + " " + Book.getSummary() +" " + Book.getId() +"\n");
		
		try
		{
			st = conn.prepareStatement("UPDATE bookdb SET title = ?, year_published = ?, isbn = ?, summary = ? WHERE id = ?");
			
			st.setString(1, Book.getTitle());
			st.setInt(2, Book.getYearPublished());
			st.setLong(3, Book.getISBN());
			st.setString(4, Book.getSummary());
			st.setInt(5, Book.getId());
			
			//Get current time stamp from database
			st2 = conn.prepareStatement("SELECT last_modified FROM bookdb WHERE title = ?");
			st2.setString(1, Book.getTitle());
			ResultSet rs = st2.executeQuery();
			Timestamp dataBaseStamp = null;
			Alert alert = new Alert(AlertType.INFORMATION);
			while(rs.next())
			{
				dataBaseStamp = rs.getTimestamp("last_modified");
			}
			
			//Prepare Audit Trail entry
			//1) Get Current Values of Book From Database
			String title = "default title";
			int yearP = 0;
			long isbn = 0;
			String summA = "default summary";
			st2 = conn.prepareStatement("SELECT * FROM bookdb WHERE id = ?");
			st2.setInt(1, Book.getId());
			rs = st2.executeQuery(); 
			while(rs.next())
			{
				title = rs.getString("title");
				yearP = rs.getInt("year_published");
				isbn = rs.getLong("isbn");
				summA = rs.getString("summary");
				
			}

			//If time stamp is default setting (null) or matches our model fetched time stamp we update
			if(dataBaseStamp == null || dataBaseStamp.toLocalDateTime().equals(Book.getLastModified()))
			{
				//TODO this can and probably should be it's own method to reduce redundancy
				//2) test database values vs new values - write audit entry if different
				if(! title.equals(Book.getTitle())) //if the book title is different
				{
					//make an audit entry
					st2 = conn.prepareStatement("INSERT INTO book_audit_trail(book_id, entry_msg) values(?, ?)");
					st2.setInt(1, Book.getId());
					String msg = "Book title changed from \"" + title + "\" to \"" + Book.getTitle() + "\"" ;
					st2.setString(2, msg);
					st2.executeUpdate();
				}
				if(yearP != Book.getYearPublished()) //if the year published is different
				{
					//make an audit entry
					st2 = conn.prepareStatement("INSERT INTO book_audit_trail(book_id, entry_msg) values(?, ?)");
					st2.setInt(1, Book.getId());
					String msg = "Year published changed from \"" + yearP + "\" to \"" + Book.getYearPublished() + "\"" ;
					st2.setString(2, msg);
					st2.executeUpdate();
				}
				if(isbn != Book.getISBN()) //if the isbn is different
				{
					//make an audit entry
					st2 = conn.prepareStatement("INSERT INTO book_audit_trail(book_id, entry_msg) values(?, ?)");
					st2.setInt(1, Book.getId());
					String msg = "ISBN changed from \"" + isbn + "\" to \"" + Book.getISBN() + "\"" ;
					st2.setString(2, msg);
					st2.executeUpdate();
				}
				if(! summA.equals(Book.getSummary())) //if the summary is different
				{
					//make an audit entry
					st2 = conn.prepareStatement("INSERT INTO book_audit_trail(book_id, entry_msg) values(?, ?)");
					st2.setInt(1, Book.getId());
					String msg = "Summary changed from \"" + summA + "\" to \"" + Book.getSummary() + "\"" ;
					st2.setString(2, msg);
					st2.executeUpdate();
				}
				
				//Update the database
				st.executeUpdate();
				
				//Send info to logger
				logger.info("Update Executed Successfully");
				
				//Inform user of success 
				alert.setTitle("InformationDialog");
				alert.setHeaderText(null);
				alert.setContentText("Save successful.");
				alert.show();
			}
			//If the timestamps do not match we notify the user, they must try again
			else
			{
				alert.setTitle("Information Dialog");
				alert.setHeaderText("Save Failed");
				alert.setContentText("This book has been modified (interm) by another user!" +  "\n" + "Please refresh the Booklist and try again!");
				alert.show();
				
				//YOU DONT
			}
			
			//Update stamp client side, ok to do regardless of update but probably shouldn't 
			st = conn.prepareStatement("SELECT last_modified FROM bookdb WHERE title = ?");
			st.setString(1, Book.getTitle());
			rs = st.executeQuery();
			while(rs.next())
			{
				dataBaseStamp = rs.getTimestamp("last_modified");
			}
			Book.setLastModified(dataBaseStamp);
		}
		catch(SQLException e)
		{
			System.out.println(e.getMessage());
		}
		
		
	}
	
	public void addBooktoDB(BookModel Book) throws SQLException
	{
		PreparedStatement st = null;
		Alert alert = new Alert(AlertType.INFORMATION);
		Alert alert2 = new Alert(AlertType.CONFIRMATION);
		alert.setTitle("Information Dialog");
		alert.setHeaderText(null);
		alert2.setTitle("Information Dialog");
		alert2.setHeaderText(null);
		
		//System.out.print(Book.getTitle() + " " + Book.getYearPublished() + " " + Book.getISBN() + " " + Book.getSummary());
		
		try
		{
			//prepare insert of new book to database
			st = conn.prepareStatement("INSERT INTO bookdb(title, year_published, isbn, summary) values(?,?,?,?)");
			
			st.setString(1, Book.getTitle());
			st.setInt(2, Book.getYearPublished());
			st.setLong(3, Book.getISBN());
			st.setString(4, Book.getSummary());
			
			//insert book into bookdb
			st.executeUpdate();
			
			//prepare audit trail entry
			//1) get the id for newly added book
			st = conn.prepareStatement("SELECT id FROM bookdb WHERE title = ?");
			st.setString(1, Book.getTitle());
			ResultSet rs = st.executeQuery();
			int id = 0;
			while(rs.next())
			{
				id = rs.getInt("id");
			}
			//2)Write the audit entry
			st = conn.prepareStatement("INSERT INTO book_audit_trail(book_id, entry_msg) values(?, ?)");
			st.setInt(1, id);
			st.setString(2, "Book added");
			st.executeUpdate();
			
			//Show user the addition was successful
			alert.setContentText("Addition Successful");
			alert.show();
		}
		catch(SQLException e)
		{
			//TODO The following error SHOULD be asserted, then managed (ex  if e.getMessage.().equals(...) then ...			
			//and update information SHOULD be checked for accuracy before insertion
			//e.printStackTrace(); //this will throw the error : " Duplicate entry 'Fake' for key 'UQ_Title' " when duplicate/not unique 
			
			alert2.setContentText("This book title exists in the database, update?");
			Optional<ButtonType> result = alert2.showAndWait();
			if (result.get() == ButtonType.OK)
			{
			    // ... user chose OK
				st = conn.prepareStatement("SELECT id FROM bookdb where title = ?");
				st.setString(1, Book.getTitle());
				ResultSet rs = st.executeQuery();
				while(rs.next())
				{
					Book.setId(rs.getInt("id"));
				}
				//System.out.println("The id for this book is" + Book.getId());
				updateBook(Book);
			}
			else 
			{
			    // ... user chose CANCEL or closed the dialog
			}
		}
	}



	public void deleteBook(BookModel book) 
	{
		PreparedStatement st = null;
		
		String deleteTitle = book.getTitle();
		
		try
		{
			st = conn.prepareStatement("DELETE FROM bookdb WHERE title =  ? ");
			st.setString(1, deleteTitle);
			
			st.executeUpdate();
			logger.info( "Deletion sucessful,");
		}
		catch(SQLException e)
		{
			e.printStackTrace();
		}
	}

}
