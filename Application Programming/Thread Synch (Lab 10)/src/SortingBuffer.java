import java.util.Arrays;
/**
 * The idea of this class is to get a value from each thread, and 
 * have each thread wait until its value becomes the minimum.
 * 
 * @author Tom Bylander
 */
public class SortingBuffer 
{
    /**
     * The number of threads to help synchronize
     */
    private int numberOfThreads;

    /**
     * The current value from each thread
     */
    private int[] currentValue;

    /**
     * Initialize numberOfThreads and current values for each thread.
     * 
     * @param numberOfThreads
     */
    public SortingBuffer(int numberOfThreads) 
    {
        this.numberOfThreads = numberOfThreads;
        currentValue = new int[numberOfThreads];
        // Use a sentinel value to initialize array
        Arrays.fill(currentValue, Integer.MIN_VALUE);
    }

    /**
     * Store the value from this thread. Wait until the value is the minimum
     * from all the threads. Return when the value becomes the minimum.
     * <p>
     * It's not a very efficient way to compute the minimum, but it is
     * straightforward.
     * 
     * @param thread
     * @param value
     */
    public synchronized void waitUntilMinimum(int thread, int value) throws InterruptedException 
    {
        currentValue[thread] = value;
        notifyAll();
        int min;
        do 
        {
            min = currentValue[0];
            for (int i = 1; i < numberOfThreads; i++) 
            {
                if (currentValue[i] < min)
                    min = currentValue[i];
            }
            if (min < value)
                wait();
        } 
        while (min < value);
        return;
    }

    /**
     * Indicates that the the thread is done with this object.
     * 
     * @param thread
     */
    public synchronized void finished(int thread) 
    {
        // Use a sentinel value to indicate that the thread is done with this
        // object.
        currentValue[thread] = Integer.MAX_VALUE;
        notifyAll();
    }
}
