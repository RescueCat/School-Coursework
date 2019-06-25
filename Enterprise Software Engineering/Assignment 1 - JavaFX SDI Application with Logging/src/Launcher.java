import org.apache.log4j.BasicConfigurator;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.Pane;
import javafx.stage.Stage;

public class Launcher extends Application 
{	
	@Override
	public void start(Stage primaryStage) throws Exception 
	{	
		//Identify Controller for FXML file (you can do this in the xml file too!)
		MenuController menuController = MenuController.getInstance();
		
		//Create FXML loader with params
		FXMLLoader loader = new FXMLLoader(this.getClass().getResource("LauncherView.fxml"));	//link fxml file with loader
		loader.setController(menuController); 													//link controller with loader
		
		//Create Parent View
		Parent root = loader.load(); 															//link loader to parent view
		menuController.setRootPane((BorderPane) root);											//set layout style in controller
		
		//Create a scene
		Scene scene = new Scene(root, 1200, 500); 												//set stage view and dimensions
		primaryStage.setTitle("Main Menu");														//set stage name
		primaryStage.setScene(scene); 															//load scene into stage
		primaryStage.show(); 																	//Show stage to user
		
	}
	

	public static void main(String[] args)
	{
		//“CS 4743 Assignment 1 by <Jonathan Houston>
		BasicConfigurator.configure(); //configure log4j
		launch(args);
	}

}
