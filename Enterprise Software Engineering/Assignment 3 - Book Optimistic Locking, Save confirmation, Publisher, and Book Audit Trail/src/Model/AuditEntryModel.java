package Model;

import java.sql.Timestamp;
import java.time.LocalDateTime;

public class AuditEntryModel 
{
	private int id;
	private LocalDateTime dateAdded;
	private String message;
	
	//Constructor
	public AuditEntryModel()
	{
		this.id = 0;
		this.dateAdded = null;
		this.message = "No Entries";
	}
	
	//Setters
	public void setId(int id)
	{
		this.id = id;
	}
	
	public void setDateAdded(LocalDateTime date)
	{
		this.dateAdded = date;
	}
	
	public void setMessage(Timestamp timestamp, String msg)
	{
		
		this.message = message + "\n" + timestamp + " : " + msg;
	}
	
	//Getters
	public int getId()
	{
		return this.id;
	}
	
	public LocalDateTime getDateAdded()
	{
		return this.dateAdded;
	}
	
	public String getMessage()
	{
		return this.message;
	}
}
