import java.io.*;
import java.util.Scanner;

/**This class "keeps count of the number off lines, words, tokens, characters and bytes
 * in a file."
 */

public class FileCounts 
{
	private File file;
	private int lineCount;
	private int tokenCount;
	private int charCount;
	private int byteCount;
	private Scanner fileScan;
	private Scanner wordScan;
	FileInputStream fis = null;

	/**Reads trough file and updates counter values for lines, words, tokens, characters and bytes
	 * @param file - a text file that is processed.
	 */
	public FileCounts(File file) throws IOException
	{
		this.file = file;
		
		//counting characters
		BufferedReader reader = new BufferedReader(new FileReader(file));
		while (reader.read() != -1)
		{
			charCount++;
		}
		reader.close();

		//counting bytes
		fis = new FileInputStream(file);
		while (fis.read() != -1)
		{
			byteCount++;
		}
		fis.close();

		//counting lines and words
		fileScan = new Scanner(file);
		String line;
		while (fileScan.hasNextLine())
		{
			lineCount++;
			line = fileScan.nextLine();
			wordScan = new Scanner(line);
			while (wordScan.hasNext())
			{
				wordScan.next();
				tokenCount++;
			}
			wordScan.close();
		}
		fileScan.close();
	}
	/**Shows the number of lines in the file
	 * @return lineCount - number of lines
	 */
	public int lineCount()
	{
		return lineCount;
	}
	
	/**Shows the number of words in the file
	 *@return tokenCount - number of words
	 */
	public int tokenCount()
	{
		return tokenCount;
	}
	
	/**Shows the number of characters in the file
	 * @return charCount - number of characters
	 */
	public int charCount()
	{
		return charCount;
	}

	/**Shows the number of bytes in the file
	 * @return byteCount - number of bytes
	 */
	public int byteCount()
	{
		return byteCount;
	}
}