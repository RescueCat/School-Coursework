package cs3743;

import java.sql.SQLException;
import java.sql.ResultSet;

public class MySqlUtility 
{
    /**
    * Returns a string padded on the right with the specified character
    * to make the resulting length the specified total length.  
    * <p>
    * If the parameter str has a length that is already greater than the 
    * specified total length, the parameter str is simply returned.
    * 
    * @param str           string to be padded
    * @param iTotalLength  length of the resulting padded string
    * @param padChar       the pad character
    * @return              right padded string
    */
    public static String padRight(String str, int iTotalLength, char padChar)
    {
        if (str.length() < iTotalLength)
        { // smaller so pad it
            char [] charM = new char[iTotalLength];
            int i;
            for (i = 0; i < str.length(); i += 1)
                charM[i] = str.charAt(i);
            for (; i < iTotalLength; i += 1)
                charM[i] = padChar;
            str = new String(charM);
        }
        return str;
    }
    
    /**
    * Prints the contents of a result set which came from executing a select
    * statement.  
    * <p>
    * This first prints the title.  It then prints a column heading based on the
    * name of each column.  It then prints each tuple in the resultSet.
    * <p>
    * NULL values are printed as "NULL"
    *
    * If no rows were returned, it prints a message stating "No Results"
    *
    * @param title       title of the output
    * @param resultSet   JDBC resultSet from a select statement's execution
    */
    public static void printUtility(String title, ResultSet resultSet) throws SQLException 
    {
        String strVal = "";
        System.out.printf("%s\n", title);
        // Print the column heading 
        System.out.printf("    ");   // indent the output
        for (int i = 1; i <= resultSet.getMetaData().getColumnCount(); i  += 1)
        {
            String strColNm = resultSet.getMetaData().getColumnName(i);
            // The size of each column in the output is based on the larger
            // of the column name and the expected value length.
            int iColSize = resultSet.getMetaData().getPrecision(i);
            int iDispSize = resultSet.getMetaData().getColumnDisplaySize(i);
            if (iDispSize < iColSize)
                iColSize = iDispSize;
            int iNmSize = strColNm.length();
            if (iNmSize > iColSize)
                    iColSize = iNmSize;
            switch (resultSet.getMetaData().getColumnType(i))
            {
                case java.sql.Types.INTEGER:
                case java.sql.Types.SMALLINT:
                case java.sql.Types.BIGINT:
                     // Reduce the size if the column Size > 10
                     if (iNmSize <= 10 && iColSize > 10)
                         iColSize = 10;
                     break;
            }
            strColNm = padRight(strColNm, iColSize, '.');
            System.out.printf("%s ", strColNm);
        }
        System.out.printf("\n");
        
        // traverse through each tuple in the resultSet
        int iCount = 0;  // count the number of result rows
        while(resultSet.next())
        {
            // print each column in the tuple
            System.out.printf("    ");   // indent the output
            for (int i = 1; i <= resultSet.getMetaData().getColumnCount(); i  += 1)
            {
                // The size of each column in the output is based on the larger
                // of the column name and the expected value length.
                String strColNm = resultSet.getMetaData().getColumnName(i);
                int iColSize = resultSet.getMetaData().getPrecision(i);
                int iDispSize = resultSet.getMetaData().getColumnDisplaySize(i);
                if (iDispSize < iColSize)
                    iColSize = iDispSize;
                int iNmSize = strColNm.length();
                if (iNmSize > iColSize)
                    iColSize = iNmSize;
                // Check for null
                if (resultSet.getObject(i) == null)
                    strVal = "NULL";
                else
                {
                    switch (resultSet.getMetaData().getColumnType(i))
                    {
                        case java.sql.Types.INTEGER:
                        case java.sql.Types.SMALLINT:
                        case java.sql.Types.BIGINT:
                            int intVal = resultSet.getInt(i);
                            strVal = Integer.toString(intVal);
                            // Reduce the size if the column Size > 10
                            if (iNmSize <= 10 && iColSize > 10)
                                iColSize = 10;
                            break;
                        case java.sql.Types.VARCHAR:
                        case java.sql.Types.CHAR:
                           strVal = resultSet.getString(i);
                           break;
                        case java.sql.Types.DATE:
                           strVal = resultSet.getDate(i).toString();
                           break;
                        case java.sql.Types.TIME:
                           strVal = resultSet.getTime(i).toString();
                           break;
                        default:
                           System.out.printf("\n\tunknown type: %d\n", resultSet.getMetaData().getColumnType(i));
                    }
                }
                System.out.printf("%s ", padRight(strVal, iColSize, ' '));
            }
            System.out.printf("\n");
            iCount += 1;
        }
        if (iCount == 0)
            System.out.printf("    No results\n");
        else 
            System.out.printf("    %d Rows\n", iCount);
    }
    /**
    * Prints the column name, data type, and length for each column in a table.
    *
    * @param resultSet   JDBC resultSet from a select statement's execution
    */
    public static void writeMetaData(ResultSet resultSet) throws SQLException 
    {
        // We will show some metadata about a result set 
        // First, we will get the table name.  
        // For a join, we would have to look at multiple columns to get 
        // multiple table names.
        System.out.printf("Columns for table %s\n"
            , resultSet.getMetaData().getTableName(1));
        System.out.printf("%-16s  %-12s %s\n"
            ,"Column Name", "Data Type", "Size");
        // Loop through each column
        for  (int i = 1; i<= resultSet.getMetaData().getColumnCount(); i++)
        {
            String typeStr = resultSet.getMetaData().getColumnTypeName(i);
            System.out.printf("%-16s  %-12s %d\n"
                , resultSet.getMetaData().getColumnName(i)
                , typeStr
                , resultSet.getMetaData().getColumnDisplaySize(i));
        }
    }
}