import java.io.*;
import java.util.*;

/**
 * Test the implementation of DualMap
 * 
 * @author Tom Bylander
 */
public class DualMapTest 
{
    public static void main(String[] args) 
    {
        monthsTest();
        daysTest();
        numbersTest();
    }

    public static void monthsTest() 
    {
    	String[] months1 = { "January", "February", "March", "April", "May",
                "June", "July", "August", "September", "October", "November",
                "December" };
        String[] months2 = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul",
                "Aug", "Sep", "Oct", "Nov", "Dec" };

        DualMap<String, String> testdm = new DualHashMap<String, String>();

        for (int i = 0; i < months1.length; i++) 
        {
            testdm.put(months1[i], months2[i]);
        }

        // This should print:
        // Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec
        for (String s : months1) 
        {
            System.out.print(testdm.get(s) + " ");
        }
        System.out.println();

        // This should print:
        // January February March April May June July August September October
        // November December
        for (String s : months2) 
        {
            System.out.print(testdm.reverseGet(s) + " ");
        }
        System.out.println();

        for (int i = 0; i < months1.length; i += 2) 
        {
            testdm.remove(months1[i], months2[i]);
        }

        // This should print:
        // null Feb null Apr null Jun null Aug null Oct null Dec
        for (String s : months1) 
        {
            System.out.print(testdm.get(s) + " ");
        }
        System.out.println();

        // This should print:
        // null February null April null June null August null October null
        // December
        for (String s : months2) 
        {
            System.out.print(testdm.reverseGet(s) + " ");
        }
        System.out.println();
    }

    public static void daysTest() 
    {
        String[] days1 = { "Sunday", "Monday", "Tuesday", "Wednesday",
                "Thursday", "Friday", "Saturday" };
        String[] days2 = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
        String[] days3 = { "U", "M", "T", "W", "R", "F", "S" };

        DualMap<String, String> testdm = new DualHashMap<String, String>();

        for (int i = 0; i < days1.length; i++) 
        {
            testdm.put(days1[i], days2[i]);
            testdm.put(days2[i], days3[i]);
        }

        // This should print:
        // U M T W R F S
        for (String s : days2) 
        {
            System.out.print(testdm.get(s) + " ");
        }
        System.out.println();

        // This should print:
        // Sunday Monday Tuesday Wednesday Thursday Friday Saturday
        for (String s : days2) 
        {
            System.out.print(testdm.reverseGet(s) + " ");
        }
        System.out.println();

        for (int i = 0; i < days1.length; i++) 
        {
            testdm.put(days1[i], days3[i]);
        }

        // This should print:
        // null null null null null null null
        for (String s : days2) 
        {
            System.out.print(testdm.get(s) + " ");
        }
        System.out.println();

        // This should print:
        // null null null null null null null
        for (String s : days2) 
        {
            System.out.print(testdm.reverseGet(s) + " ");
        }
        System.out.println();

        // This should print:
        // U M T W R F S
        for (String s : days1) 
        {
            System.out.print(testdm.get(s) + " ");
        }
        System.out.println();

        // This should print:
        // Sunday Monday Tuesday Wednesday Thursday Friday Saturday
        for (String s : days3) 
        {
            System.out.print(testdm.reverseGet(s) + " ");
        }
        System.out.println();

    }

    public static void numbersTest() 
    {
        Scanner scan = null;
        try 
        {
            scan = new Scanner(new File("numbers.txt"));
        } 
        catch (FileNotFoundException e) 
        {
            throw new RuntimeException("unable to open numbers.txt");
        }

        DualMap<Integer, List<String>> testdm = new DualHashMap<Integer, List<String>>();

        while (scan.hasNextLine()) 
        {
            int n = scan.nextInt();
            String s = scan.nextLine();
            Scanner scanline = new Scanner(s);
            List<String> list = new ArrayList<String>();
            while (scanline.hasNext()) 
            {
                list.add(scanline.next());
            }
            scanline.close();
            testdm.put(n, list);
        }

        scan.close();

        Random random = new Random();
        // should print 10 random numbers as Lists of Strings
        for (int i = 0; i < 10; i++) 
        {
            System.out.println(testdm.get(random.nextInt(32769)));
        }

        // should print 10 semi-random numbers as Integers
        for (int i = 0; i < 10; i++) 
        {
            List<String> part1 = testdm.get(1 + random.nextInt(31));
            List<String> part2 = testdm.get(1 + random.nextInt(999));
            // Need to create a new list to avoid damaging the Lists
            // in the DualMap.
            List<String> list = new ArrayList<String>();
            for (String s : part1)
                list.add(s);
            list.add("thousand");
            for (String s : part2)
                list.add(s);
            System.out.print(testdm.reverseGet(list) + " ");
        }
        System.out.println();
    }
}
