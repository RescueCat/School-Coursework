package Model;

import java.sql.Connection;
import java.sql.SQLException;

import com.mysql.cj.jdbc.MysqlDataSource;

public class CreateConnection 
{
	private static Connection conn;
	
	public static Connection createNewConnection() throws SQLException 
	{
		//Establish connection
		MysqlDataSource ds = new MysqlDataSource();				//create empty connection and set params (url, user, pass, etc)
		//ds.setURL("jdbc:mysql://localhost/testdatabase"); 		//testdatabase: this is interchangeable with any database you created in XAMMP/phpMyAdmin
		//ds.setUser("root");										//default xampp password, only change if you set or manually changed (I was not asked during setup)
		//	ds.setPassword("");										//default password is null, only change if you set or manually changed (I was not asked during setup)
				
		ds.setURL("jdbc:mysql://easel2.fulgentcorp.com:3306/omu075?serverTimezone=CST");
		ds.setUser("omu075");
		ds.setPassword("sZ5MKKp8JqB2iRYnnnQW");
		
		try
		{
			conn = ds.getConnection();								//this starts the connection
		}
		catch(SQLException e)
		{
			e.printStackTrace();
		}
		
		return conn;
	}

}
