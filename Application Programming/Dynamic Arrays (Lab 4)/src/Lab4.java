import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

import Length.Foot;
import Length.Inch;
import Length.Length;
import Length.Meter;
import Length.Yard;

/**
 *The task is to read a file data.txt, which consists of one length on each line.
 *Each length should be stored in an appropriate Length object. All the 
 *Length objects should be stored in an ArrayList<Length>. Each Length object 
 *should be printed out. The minimum and maximum length should be printed out. 
 *Then, the sum of the Lengths should be printed out in different ways as shown
 *below.
 * @author Jonathan Houston
 *
 */
public class Lab4 {

	public static void main(String[] args) 
	{
		ArrayList<Length> lengths = new ArrayList<>();
		/** Assume that the name of the file is data.txt. In Eclipse, 
		 *  the file needs to be in the top directory of the project. 
		 *  Reading all the lengths in the file should be accomplished 
		 *  by a sequence of code like:
		*/
		Scanner in = null;
		try 
		{
			in = new Scanner(new File("data.txt"));
		} 
		catch (FileNotFoundException exception) 
		{
			throw new RuntimeException("failed to open data.txt");
		}
		
		
		while (in.hasNextDouble()) 
		{
			double value = in.nextDouble();
			String unit = in.next();

			if (unit.startsWith("m"))
				lengths.add(new Meter(value));
			else if (unit.startsWith("i"))
				lengths.add(new Inch(value));
			else if (unit.startsWith("f"))
				lengths.add(new Foot(value));
			else if (unit.startsWith("y"))
				lengths.add(new Yard(value));
			else
				System.out.println("Invalid unit input: " + unit);
		}
		in.close();
		
		
		for (Length i : lengths) {
			System.out.println(i);
		}
		System.out.println();

		int min = 0;
		int max = 0;
		for (int i = 1; i < lengths.size(); i++) {
			if (lengths.get(min).compareTo(lengths.get(i)) == 1)
				min = i;
			else if (lengths.get(max).compareTo(lengths.get(i)) == -1)
				max = i;
		}
		System.out.printf("Minimum is %s%n", lengths.get(min));
		System.out.printf("Maximum is %s%n", lengths.get(max));
		System.out.println();

		Meter meter = new Meter(0);
		Inch inch = new Inch(0);
		Foot foot = new Foot(0);
		Yard yard = new Yard(0);

		for (Length i : lengths) {
			meter.add(i);
			inch.add(i);
			foot.add(i);
			yard.add(i);
		}
		System.out.println("Sum of Lengths Adding from First to Last");
		System.out.println(meter);
		System.out.println(inch);
		System.out.println(foot);
		System.out.println(yard);
		System.out.println();

		meter = new Meter(0);
		inch = new Inch(0);
		foot = new Foot(0);
		yard = new Yard(0);

		for (int i = lengths.size() - 1; i >= 0; i--) {
			meter.add(lengths.get(i));
			inch.add(lengths.get(i));
			foot.add(lengths.get(i));
			yard.add(lengths.get(i));
		}

		System.out.println("Sum of Lengths Adding from Last to First");
		System.out.println(meter);
		System.out.println(inch);
		System.out.println(foot);
		System.out.println(yard);
		System.out.println();

	}

}
