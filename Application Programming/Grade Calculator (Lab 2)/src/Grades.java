import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Grades {

	private String name;
	private List<Integer> grades;
	private List<Integer> sortedGrades;
	
	public Grades(String n, List<Integer> g)
	{
		name = n;
		grades = g;
		sortedGrades = new ArrayList<>(g);
		Collections.sort(sortedGrades);
	}
	
	public String toString()
	{
		return name + " " + grades;
	}
	
	public String getName()
	{
		return name;
	}
	
	public int length()
	{
		return grades.size();
	}
	
	public float average()
	{
		int sum = 0;
		for (Integer grade: grades)
		{
			sum += grade;
		}
		return (float)sum / grades.size();
	}
	
	public double median()
	{
		int midIndex = (int) Math.ceil(sortedGrades.size() / 2.0);
		if (sortedGrades.size() % 2 == 0)
			return (sortedGrades.get((int)midIndex) + sortedGrades.get((int)midIndex - 1)) / 2.0;
		else
			return sortedGrades.get((int)midIndex - 1);
	}
	
	public int maximum()
	{
		return sortedGrades.get(sortedGrades.size() - 1);
	}
	
	public int minimum()
	{
		return sortedGrades.get(0);
	}
}
