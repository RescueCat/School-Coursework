import java.awt.*;
import java.util.ArrayList;


public class DemoModel 
{

	/** 
	 * An arrayList of java.awt.Point references 
	 */
	private ArrayList<Point> points;
	
	/** 
	 * An arrayList of java.awt.Color references 
	 */
	private ArrayList<Color> pointsColor;
	/** 
	 * The color selected by the user 
	 */
	private Color selectedColor;
	
	public DemoModel() 
	{
		
		points = new ArrayList<Point>();
		pointsColor = new ArrayList<Color>();
		selectedColor = Color.CYAN;
	}
	
	/**
	 * Add a Point to the points array.
	 * @param point the Point to be added to points.
	 */
	public void addPoint(Point point) 
	{
		points.add(point);
		pointsColor.add(getSelectedColor());
	}
	
	/**
	 * Returns point at index i.
	 * Returns null if no such point exists.
	 * @param i
	 */
	public Point getPoint(int i) 
	{
		if (i >= 0 && i < points.size()) 
		{
			// probably should return a new point so that the return
			// value cannot be used to change the array element
			return points.get(i);
		}
		return null;
	}
	
	/** 
	 * Returns color of the point at index n.
	 * Returns null if no such points exists.
	 * @param n 
	 */
	public Color getColor(int n){
		if (n >= 0 && n < pointsColor.size())
		{
			return pointsColor.get(n);
		}
		return null;
	}
	
	/**
	 * Store the color that the user selected.
	 * @param color the color selected by the user
	 */
	public void setSelectedColor(Color color) 
	{
		selectedColor = color;
	}
	
	/**
	 * @return the color selected by the user
	 */
	public Color getSelectedColor() 
	{
		return selectedColor;
	}
} 