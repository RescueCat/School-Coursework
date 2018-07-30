import java.util.Arrays;

/**
 * This class synchronizes threads and sorts it's values.
 * 
 */
public class SortingThread implements Runnable
{
	private int threadNumber;
	private int[] arrayOfValues;
	private SortingBuffer buffer;
	
	public SortingThread(int i, int[] array, SortingBuffer buffer)
	{
		threadNumber = i;
		arrayOfValues = array;
		this.buffer = buffer;
	}
	/**
	 * This method first prints out unsynchronized values and then prints
	 * out synchronized values of threads.
	 */
	public void run()
	{
		Arrays.sort(arrayOfValues);
		for(int k : arrayOfValues)
		{
			System.out.printf("%d unsynchronized %d\n", threadNumber,k);
		}
		try
		{
			for(int c : arrayOfValues)
			{
				buffer.waitUntilMinimum(threadNumber,c);
				System.out.printf("%d synchronized %d\n", threadNumber, c );
			}
			buffer.finished(threadNumber);
		}
		catch (InterruptedException e) 
		{
				System.err.println(e);
		}	
	}
}