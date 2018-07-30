import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;

public class DemoMVC 
{
	
	/**
	 * main method 
	 */
	public static void main(String[] args) 
	{
		DemoModel model = new DemoModel();
		DemoView view = new DemoView(model);
		DemoController controller = new DemoController(model, view);
		
		view.registerListener(controller);
		
		view.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		view.setSize(400, 300);
		view.setVisible(true);
	}
}
