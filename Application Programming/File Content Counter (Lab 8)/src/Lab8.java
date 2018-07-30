import java.io.*;
import javax.swing.*;

/**
 * This program will "get a file from the user and display the number
 * of lines, tokens, characters and bytes in the file. Here are some Unicode
 * characters so the number of characters in this file will be different from
 * the number of bytes.
 * 
 * Both Lech Wałęsa and အောင်ဆန်းစုကြည် have won the Nobel Peace Prize.
 * 
 * @author Tom Bylander
 */

public class Lab8
{
	/**
	 * Main method for Lab 8.
	 */

	//Variable for while loop, initially set to false to enter loop
	static boolean opened = false;

	public static void main(String[] args) throws IOException
	{
		// These statements should be be into a loop that runs until all the
		// statements execute without an exception.

		while (!opened)
		{
			try
			{
				File file = getFileFromUser();
				FileCounts counter = new FileCounts(file);
				System.out.println(file);
				System.out.printf("%d lines\n", counter.lineCount());
				System.out.printf("%d tokens\n", counter.tokenCount());
				System.out.printf("%d characters\n", counter.charCount());
				System.out.printf("%d bytes\n", counter.byteCount());
			}
			catch (FileNotFoundException fileNotFoundException)
			{
				System.err.println(fileNotFoundException);
			}
		}
}


	/**
	* Asks the user for a file name using the GUI.
	*
	* This is a modification of getFileOrDirectory from FileChooserDemo so it
	* throws exceptions rather than exits when a problem is encountered. It
	* also starts the GUI at the current directory.
	*
	* @return the file selected by the user
	* @throws FileNotFoundException
	*/

	private static File getFileFromUser() throws FileNotFoundException
	{
		// display file dialog, so user can choose file or directory to open
		JFileChooser fileChooser = new JFileChooser(".");
		fileChooser.setFileSelectionMode(JFileChooser.FILES_AND_DIRECTORIES);
		int result = fileChooser.showOpenDialog(null);
		
		// if user clicked Cancel button on dialog, throw exception
		if (result == JFileChooser.CANCEL_OPTION)
		{
			throw new FileNotFoundException("User selected cancel");
		}
		File fileName = fileChooser.getSelectedFile(); // get File

		// display error and throw exception if invalid
		if ((fileName == null) || (fileName.getName().equals("")) || (!fileName.exists()) || (fileName.isDirectory()))
		{
			JOptionPane.showMessageDialog(null, "Invalid Name", "Invalid Name",JOptionPane.ERROR_MESSAGE);
			throw new FileNotFoundException("Invalid Name: " + fileName);
		} // end if
	
		//variable for loop to exit
		opened = true;
		return fileName;
		
		
	} // end method getFileFromUser
}
