package Length;

/**
 * Foot is an object and is inherited by the length Package. 
 * It has a unit of measure and a length. 
 * It can be converted to Meters and added to other Lengths.
 */

public class Foot extends Length 
{
	
	/**
	 * Conversion unit feet to meters.
	 */

	public static final double METERS_PER_FOOT = 0.3048;

	/**
	 * Store length Here
	 */

	public Foot(double length) 
	{
		super(length);
	}

	/**
     	 * This will add the other length to this length object
     	 */

	@Override
	public void add(Length other) 
	{
		super.setLength((other.toMeters() + this.toMeters()) / METERS_PER_FOOT);
	}

	/**
     	 * Returns the name (with unit). If the unit is exactly 1
	 * it will return "foot" instead of "feet".
     	 */
	
	@Override
	public String getUnit() 
	{
		return super.getLength() == 1.0 ? "foot" : "feet";
	}

	@Override
	public double toMeters() 
	{
		return super.getLength() * METERS_PER_FOOT;
	}

}