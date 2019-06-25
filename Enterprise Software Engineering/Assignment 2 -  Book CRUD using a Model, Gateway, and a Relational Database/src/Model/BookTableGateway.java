package Model;

import java.sql.*;
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
			books.add(book);
		}

		return books;
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
		
		//System.out.print(Book.getTitle() + " " + Book.getYearPublished() + " " + Book.getISBN() + " " + Book.getSummary() +" " + Book.getId() +"\n");
		
		try
		{
			st = conn.prepareStatement("UPDATE bookdb SET title = ?, year_published = ?, isbn = ?, summary = ? WHERE id = ?");
			
			st.setString(1, Book.getTitle());
			st.setInt(2, Book.getYearPublished());
			st.setLong(3, Book.getISBN());
			st.setString(4, Book.getSummary());
			st.setInt(5, Book.getId());
		
			st.executeUpdate();
			
			logger.info("Update Executed Successfully");
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
			st = conn.prepareStatement("INSERT INTO bookdb(title, year_published, isbn, summary) values(?,?,?,?)");
			
			st.setString(1, Book.getTitle());
			st.setInt(2, Book.getYearPublished());
			st.setLong(3, Book.getISBN());
			st.setString(4, Book.getSummary());
			
			st.executeUpdate();
			
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
