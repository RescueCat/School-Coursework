import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Lab02 {
	public static void main(String[] args) 
	{
		Scanner in = null;
		try 
		{
		    in = new Scanner(new File("data.txt"));
		} 
		catch (FileNotFoundException exception) 
		{
		    System.err.println("failed to open data.txt");
		    System.exit(1);
		}
		while (in.hasNext()) 
		{
		    String name = in.next();
		    List<Integer> grades = new ArrayList<>();
		    while (in.hasNextInt()) 
		    {
		        grades.add(in.nextInt());
		    }
		    testGrades(new Grades(name, grades));   
		}    
	}

	public static void testGrades(Grades grades) 
	{
	    System.out.println(grades.toString()); 
	    System.out.printf("\tName:    %s\n", grades.getName());
	    System.out.printf("\tLength:  %d\n", grades.length());
	    System.out.printf("\tAverage: %.2f\n", grades.average());
	    System.out.printf("\tMedian:  %.1f\n", grades.median());
	    System.out.printf("\tMaximum: %d\n", grades.maximum());
	    System.out.printf("\tMininum: %d\n", grades.minimum());
	}
	
}
