package app;
import java.sql.Connection;
import java.sql.SQLException;

import org.apache.log4j.BasicConfigurator;
import org.apache.log4j.LogManager;
import org.apache.log4j.Logger;

import Controller.BookDetailController;
import Controller.MenuController;
import Model.CreateConnection;
import javafx.application.Application;
import javafx.application.Platform;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.Pane;
import javafx.stage.Stage;

public class Launcher extends Application 
{	
	private Connection conn;
	private static Logger Logger = LogManager.getLogger(Launcher.class);
	
	@Override
	public void start(Stage primaryStage) throws Exception 
	{	
		//Get Static Instance - Identify Controller for FXML file (you can do this in the xml file too!)
		MenuController menuController = MenuController.getInstance();
		
		//Identify Database Connection for Model
		menuController.setConnection(conn);
		
		//Create FXML loader with params
		FXMLLoader loader = new FXMLLoader(this.getClass().getResource("/View/LauncherView.fxml"));	//link fxml file with loader
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
	
	@Override
	public void init() throws SQLException
	{
		//Create connection
		try
		{
			Logger.info("Creating Connection");
			conn = CreateConnection.createNewConnection();
			Logger.info("Connection Create Successful.");
		}
		catch(SQLException e)
		{
			Logger.info("Could not connect to db: " + e.getMessage());
			Logger.info("Closing application");
			Platform.exit();
		}
	}
	
	@Override 
	public void stop() throws SQLException
	{
		Logger.info("App is closing.");
		Logger.info("Closing DB conection");
		conn.close();
	}

	public static void main(String[] args)
	{
		//“CS 4743 Assignment 1 by <Jonathan Houston>
		BasicConfigurator.configure(); //configure log4j
		launch(args);
	}

}
