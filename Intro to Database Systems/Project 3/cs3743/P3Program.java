package cs3743;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Date;

public class P3Program 
{
    private Connection connect = null;
    
    private Statement statement = null;
    private PreparedStatement preparedStatement = null;
    private ResultSet resultSet = null;
    public static final int ER_DUP_ENTRY = 1062;
    public static final int ER_DUP_ENTRY_WITH_KEY_NAME = 1586;
    public static final String[] strFlightIdM =
    {   "510"
       ,"705"
       ,"331"
       ,"END"
    };
    
    public P3Program (String user, String password) throws Exception
    {
        try
        {
            // This will load the MySQL driver, each DBMS has its own driver
            Class.forName("com.mysql.jdbc.Driver");
            this.connect = DriverManager.getConnection
                    ("jdbc:mysql://10.100.1.81:3306/omu075db"
                    , user
                    , password);
        }
        catch (Exception e) 
        {
            throw e;
        } 
        
    }
       
    	public void runProgram() throws Exception 
    	{
		try
		{
			statement = connect.createStatement();
			resultSet = statement.executeQuery("select * from omu075db.Customer");
			printCustomers("Beginning Customers", resultSet);

			resultSet = statement.executeQuery("select * from omu075db.Flight");
                        MySqlUtility.printUtility("Beginning Flights", resultSet);

			statement.executeUpdate("insert into omu075db.Customer " 
				+ "(`custNr` , `name` , `preferAirline` , `birthDt` , `gender`)"
				+ "values(\"1999\" , \"Jonathan Houston\" , \"Spirit\" , \"1990-09-16\" , \"M\")");
			
			resultSet = statement.executeQuery("select * from omu075db.Customer");
			printCustomers("Customers after I was added", resultSet);

			preparedStatement = connect.prepareStatement("insert into omu075db.Reservation values (?, ?, ?)");
			
			int i;
			for(i = 0; i < strFlightIdM.length; i++) 
			{
				if(strFlightIdM[i].equals("END"))
					break;
				preparedStatement.setInt(1, 1999);
				preparedStatement.setString(2, strFlightIdM[i]);
				preparedStatement.setInt(3, 2);

				try
				{
					preparedStatement.executeUpdate();
				}
				catch (SQLException e)
               			{
                        		switch(e.getErrorCode())
                        		{
                                		case ER_DUP_ENTRY:
                                		case ER_DUP_ENTRY_WITH_KEY_NAME:
                                        	System.out.printf("Duplicate key error %s\n", e.getMessage());
                                        		break;
                                		default:
                                        		throw e;
                        		}
                		}

			}
			preparedStatement = connect.prepareStatement("SELECT * from omu075db.Reservation where custNr = ?");
			preparedStatement.setInt(1, 1999);
			//resultSet = statement.executeQuery("select * from omu075db.Reservation");
			resultSet = preparedStatement.executeQuery();
			MySqlUtility.printUtility("My reservations", resultSet);

			resultSet = statement.executeQuery("select r.flightId, COUNT(r.flightId) from omu075db.Reservation r group by r.flightId having COUNT(r.flightId)>1");
			MySqlUtility.printUtility("Flights Having more than 2 reservations", resultSet); 

			statement.executeUpdate("delete from omu075db.Reservation where custNr = 1999");
			resultSet = statement.executeQuery("select * from omu075db.Reservation where custNr = 1999");
			MySqlUtility.printUtility("After Deletion from Reservations", resultSet);
			
			statement.executeUpdate("delete from omu075db.Customer where name = \"Jonathan Houston\"");
			resultSet = statement.executeQuery("select * from omu075db.Customer where name = \"Jonathan Houston\""); 
			MySqlUtility.printUtility("After Deletion from Customers", resultSet);
		}
        	catch (SQLException e)
        	{
                	switch(e.getErrorCode())
                	{
                        	case ER_DUP_ENTRY:
                        	case ER_DUP_ENTRY_WITH_KEY_NAME:
                                	System.out.printf("Duplicate key error %s\n", e.getMessage());
                                	break;
                        	default:
                                	throw e;
                	}
        	}
        	catch(Exception e)
		{
			throw e;
		}

		/*try 
        	{
            		// your code
        	}	 
        	catch (Exception e) 
        	{
            		throw e;
        	} 
        	finally 
        	{
            		close();
        	}*/

    }                                                                                                                        
    
    /*private void printCustomers(String title, ResultSet resultSet) throws SQLException 
    {
        // custNr, name, preferAirline, birthDt, gender
        System.out.printf("%s\n", title);
        // your code
    }*/
    

    // Close the resultSet, statement, preparedStatement, and connect
    private void close() 
    {
        try 
        {
            if (resultSet != null) 
                resultSet.close();

            if (statement != null) 
                statement.close();
            
            if (preparedStatement != null) 
                preparedStatement.close();

            if (connect != null) 
                connect.close();
        } 
        catch (Exception e) 
        {

        }
    }

	private void printCustomers(String title, ResultSet resultSet) throws SQLException
	{
		System.out.printf("%s\n", title);
		System.out.printf("%-7s %-15s %-15s %-12s %-8s \n" , "custNr", "name", "preferAirline", "birthDt", "gender");

		while(resultSet.next())
		{
			String custStr = resultSet.getString("custNr"); 	//never null
			String nameStr = resultSet.getString("name");		//can be null
			String pairStr = resultSet.getString("preferAirline");	//can be null
			String btdtStr;						//can be null
			String gndrStr = resultSet.getString("gender");		//never null ->default U

			if (nameStr == null)
				nameStr = "---";
			if (pairStr == null)
				pairStr = "---";
			java.sql.Date bDate = resultSet.getDate("birthDt");
			if (bDate == null)
				btdtStr = "---";
			else
				btdtStr = bDate.toString().substring (0,10);

			System.out.printf("%-7s %-15s %-15s %-12s %-8s \n" , custStr, nameStr, pairStr, btdtStr, gndrStr);
		}
		System.out.printf("\n");
	}
}
