/**
 * This is the model of this MVC implementation of a calculator.
 * It performs the functions of the calculator and keeps track
 * of what the user has entered.
 * 
 * @author Tom Bylander
 */
public class CalculatorModel 
{
 /**
  * This is the numeric value of the number the user is entering,
  * or the number that was just calculated.
  */
	private double displayValue;
    
    /**
     * This is the previous value entered or calculated.
     */
	private double internalValue;
 
 /**
  * This is the String corresponding to what the user.
  * is entering
  */
	private String displayString;
 
 /**
  * This is the last operation entered by the user.
  */
	private String operation;
 
 /**
  * This is true if the next digit entered starts a new value.
  */
	private boolean start;
 
 /**
     * This is true if a decimal dot has been entered for the current value.
     */
    private boolean dot;

 /**
  * Initializes the instance variables.
  */
    public CalculatorModel() 
    {
    	displayValue = 0.0;
    	displayString = "" + displayValue;
    	internalValue = 0;
    	dot = false;
    	start = true;
    	operation = "";
    }

 /**
  * @return the String value of what was just calculated
  * or what the user is entering
  */
    public String getValue() 
    {
    	return displayString;
    }
    //for new reset button
    public void reset()
    {
    	displayValue = 0.0;
    	displayString = "" + displayValue;
    	internalValue = 0;
    	dot = false;
    	start = true;
    	operation = "";
    }
    
    //for new factorial button
    public double factorial(double n)
    {
    	if(n == 1 || n == 0)
    		return 1;
    	else
    	{
    		return factorial(n-1)*n;
    	}
    }

 /**
  * Updates the values maintained by the calculator based on the
  * button that the user has just clicked.
  * 
  * @param text is the name of the button that the user has just clicked
  */
    public void update(String text) 
    {
    	if (start && text.length() == 1 && "0123456789".indexOf(text) >= 0) 
    	{ 
    		internalValue = displayValue;
    		displayValue = 0;
    		displayString = "";
    		start = false;
    		dot = false;
    	}
    	if (text.length() == 1 && "0123456789".indexOf(text) >= 0) 
    	{
    		displayString += text;
    		displayValue = Double.valueOf(displayString);
    	} 
    	else if (text.equals(".")) 
    	{
    		if (! dot) 
    		{ 
    			dot = true; 
    			if (displayString.equals("")) 
    			{
    				displayString = "0";
    			}
    			displayString += ".";
    		}
    	} 
    	else if(text.equals("CLEAR"))
    	{
    		reset();
    	}
    	else if(text.equals("+/-"))
    	{
    		displayValue = displayValue * (-1);
    		displayString = "" + displayValue;
    		internalValue = displayValue;
    	}
    	else 
    	{
    		if (operation.equals("+")) 
    		{
    			displayValue = internalValue + displayValue;
    		} 
    		else if (operation.equals("-")) 
    		{
    			displayValue = internalValue - displayValue;
    		} 
    		else if (operation.equals("*")) 
    		{
    			displayValue = internalValue * displayValue;
    		} 
    		else if (operation.equals("/")) 
    		{
    			displayValue = internalValue / displayValue;
    		}
    		else if (text.equals("x^2")) //new square function
    		{
    			if(displayValue == 0)
    				displayValue = Math.pow(internalValue, 2);
    			else
    				displayValue = Math.pow(displayValue, 2);
    		}
    		else if (text.equals("1/x")) //new inverse function
    		{
    			if(displayValue == 0)
    				displayValue = 1/internalValue;
    			else 
    				displayValue = 1/displayValue;
    		}
    		else if (text.equals("n!")) //factorial function
    		{
    			if (displayValue == 0)
    				displayValue = factorial(internalValue);
    			else 
    				displayValue = factorial(displayValue);
    		}
    		else if (text.equals("log")) //new log function
    		{
				if (displayValue == 0)
					displayValue = Math.log10(internalValue);
				else 
					displayValue = Math.log10(displayValue);
    		}
    		else if (text.equals("ln")) //new natural log function
    		{
    			if (displayValue == 0)
    				displayValue = Math.log(internalValue);
 				else 
 					displayValue = Math.log(displayValue);
    		}
    		else if (text.equals("sqrt")) //new sqrt function
    		{
				if (displayValue == 0)
					displayValue = Math.sqrt(internalValue);
				else 
					displayValue = Math.sqrt(displayValue);
    		}
    		else if (text.equals("e^x"))//new exp function
    		{
				if (displayValue == 0)
					displayValue = Math.exp(internalValue);
				else 
					displayValue = Math.exp(displayValue);
			}
    		
    		displayString = "" + displayValue;
    		operation = text;
    		start = true;
    	}
    }
}