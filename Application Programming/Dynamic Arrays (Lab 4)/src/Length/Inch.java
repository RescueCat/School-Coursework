package Length;

/**
 * Inch is an object and is inherited by the length package. 
 * It has a unit of measure and a length. 
 * It can be converted to meters and added to other Lengths.
 *
 */

public class Inch extends Length {

	/**
	 * Conversion unit inches to meters.
	 */

	public static final double METERS_PER_INCH = 0.0254;

	/**
     	* Store length here
     	*/ 

	public Inch(double length) 
	{
		super(length);
		
	}

	/**
     	* This will add the other length to this length object.
     	* 
     	*/

	@Override
	public void add(Length other) 
	{
		super.setLength((other.toMeters() + this.toMeters()) / METERS_PER_INCH);
	}

	/**
     	 * Returns the name (with unit). If the unit is exactly 1
	 * it will return "inch" instead of "inches".
     	 */

	@Override
	public String getUnit() 
	{
		return super.getLength() == 1.0 ? "inch" : "inches";
	}

	@Override
	public double toMeters() 
	{
		return super.getLength() * METERS_PER_INCH;
	}

}