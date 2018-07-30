package Length;

/**
 * Meter is an object and is inherited by the length Package. 
 * It has a unit of measure and a length. 
 * It can be added to any other length right away. (no conversion)
 */

public class Meter extends Length 
{
	
	/**
	 * Store length Here
	 */

	public Meter(double length) 
	{
		super(length);
	}

	/**
     	 * This will add the other length to this length object
     	 */

	@Override
	public void add(Length other) 
	{
		super.setLength(other.toMeters() + this.toMeters());	
	}

	/**
     	 * Returns the name (with unit). If the unit is exactly 1
	 * it will return "meter" instead of "meters".
     	 */

	@Override
	public String getUnit() {
		return super.getLength() == 1.0 ? "meter" : "meters";
	}

	@Override
	public double toMeters() {
		return super.getLength();
	}

}