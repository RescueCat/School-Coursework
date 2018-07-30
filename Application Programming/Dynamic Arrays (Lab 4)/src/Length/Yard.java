package Length;

/**
 * Yard is an object and is inherited by the length Package. 
 * It has a unit of measure and a length. 
 * It can be converted to Meters and added to other Lengths.
 */

public class Yard extends Length 
{
	
	/**
	 * Conversion unit yards to meters.
	 */

	public static final double METERS_PER_YARD = 0.9144;

	/**
	 * Store length Here
	 */

	public Yard(double length) 
	{
		super(length);
	}

	/**
     	 * This will add the other length to this length object
     	 */

	@Override
	public void add(Length other) 
	{
		super.setLength((other.toMeters() + this.toMeters()) / METERS_PER_YARD);
	}

	/**
     	 * Returns the name (with unit). If the unit is exactly 1
	 * it will return "yards" instead of "yards".
     	 */

	@Override
	public String getUnit() {
		return super.getLength() == 1.0 ? "yard" : "yards";
	}

	@Override
	public double toMeters() {
		return super.getLength() * METERS_PER_YARD;
	}

}
