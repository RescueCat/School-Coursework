import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;


/**
 * Creation of the Controller is straight forward. We need a
 * place to store the current model/view (constructor)
 * and since the only thing this function does is switch panels
 * we just need a method that handles the information for switching.
 * The information will then be sent and handled by the model and
 * view respectively.
 */
public class PanelSwitcherController implements ActionListener 
{
	private PanelSwitcherModel model;
	private PanelSwitcherView view;
	
	/**
	 * Constructor, initializes current view/model.
	 * @param view the current View from PanelSwitcherView
	 * @param model the current Choice from the PanelSwitcherModel 
	 */
	public PanelSwitcherController(PanelSwitcherView view, PanelSwitcherModel model) 
	{	
		this.model = model;
		this.view = view;
	}
	
	/**
	 *  method for handling the switch event, will update our panel from 1 to 2
	 *  or vice versa and will update the view with the number (1 or 2).
	 *  @param e our switch event gathered from the view (gui)
	 */
	public void actionPerformed(ActionEvent e) 
	{
		String command = e.getActionCommand();
		if (command == "Switch Panels")
		{
			model.switchPanel();
			view.displayPanel(model.whichPanel());
		}
	}
}