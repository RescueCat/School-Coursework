import java.awt.Graphics;
import java.awt.Point;
import javax.swing.JPanel;

public class PaintPanel extends JPanel 
{
    	/** 
     	* The model of this MVC example (it stores the points) 
     	*/
	private DemoModel model;

	/**
	 * Store the model that holds the points to be drawn.
	 * @param model
	 */
	public PaintPanel(DemoModel model) 
	{
		this.model = model;
	} // end PaintPanel constructor

	/**
	 * Draw ovals in a 4-by-4 bounding box at specified locations on
	 * the panel.
	 */
	public void paintComponent(Graphics g) 
	{
		super.paintComponent(g); // clears drawing area
		int i = 0;
		Point point = model.getPoint(0);
		
		while (point != null)	
		{
			g.setColor(model.getColor(i));
			g.fillOval(point.x, point.y, 4, 4);
			i++;
			point = model.getPoint(i);
		}
	} 
} 