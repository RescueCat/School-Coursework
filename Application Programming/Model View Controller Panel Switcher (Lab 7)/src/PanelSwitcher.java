import javax.swing.*;

/**
 * You need to add an event handler that will switch the JPanels in the view
 * when the user clicks the button.
 * 
 * @author Tom Bylander
 */

public class PanelSwitcher 
{
	public static void main(String[] args) 
	{
   		PanelSwitcherModel model = new PanelSwitcherModel();
    	PanelSwitcherView view = new PanelSwitcherView();
		PanelSwitcherController controller = new PanelSwitcherController(view, model);
        
		view.register(controller);
		view.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    	view.setSize(400,300);
    	view.setVisible(true);
    	}

}
