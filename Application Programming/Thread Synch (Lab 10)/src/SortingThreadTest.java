import java.util.*;
import java.util.concurrent.*;

/**
 * Test SortingThread code.
 * 
 * @author Tom Bylander
 */
public class SortingThreadTest 
{
	public static void main(String[] args) 
	{
		ExecutorService application = Executors.newCachedThreadPool();
		int alength = 10;
		int[] array0 = new int[alength];
		int[] array1 = new int[alength];
		Random random = new Random();
		for (int i = 0; i < alength; i++) 
		{
			array0[i] = random.nextInt(alength);
			array1[i] = random.nextInt(alength);
		}

		SortingBuffer buffer = new SortingBuffer(2);
		application.execute(new SortingThread(0, array0, buffer));
		application.execute(new SortingThread(1, array1, buffer));
		application.shutdown();
	}
}
