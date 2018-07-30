import java.util.HashMap;
/**
 * A DualHashMap implements DualMap interface. A DualHashMap maintains a one-to-one mapping
 * between keys and value. A DualHashMap object should contains a HashMap from keys to values
 * and a HashMap from values to keys. A DualHashMap cannot contain duplicate keys or duplicate values.
 *
 */

public class DualHashMap<K, V> implements DualMap<K,V> 
{
	
	private HashMap<K, V> map;
	private HashMap<V, K> reverseMap;
	
	public DualHashMap()
	{
		super();
		map = new HashMap<K,V>();
		reverseMap = new HashMap<V,K>();
	}
	/**
     * Associates the specified value with the specified key in this dual hash map.
     * <p>
     * If the DualHashMap previously contained a mapping for the key or the value,
     * the old association(s) gets removed.
     * 
     * @param key
     *            key to be associated with the specified value.
     * @param value
     *            value to be associated with the specified key
     */
	public void put(K key, V value)
	{
		
		if (map.containsKey(key))
		{
			V entry = map.get(key);
			map.remove(key);
			reverseMap.remove(entry);
		}
			
		if (reverseMap.containsKey(value))
		{
			K entry = reverseMap.get(value);
			reverseMap.remove(value);
			map.remove(entry);
		}
		
		map.put(key, value);
		reverseMap.put(value, key);
	}
	/**
     * Removes the mapping from the key to the value from this dual hash map if it is
     * present. 
     * @param key
     *            key whose mapping to value is to be removed
     * @param value
     *            value whose mapping from key is to be removed
     */
	public void remove(K key, V value)
	{
		map.remove(key);
		reverseMap.remove(value);
	}
	
	/**
     * Returns the value that maps from the specified key, or null if this dual
     * hash map contains no mapping for the key.
     * 
     * @param key
     *            the key that maps to the value that should be returned
     * @return the value that maps from the specified key, or null if this dual
     *         map contains no mapping for the key
     */
	public V get(K key)
	{
		return map.get(key);
	}
	
	/**
     * Returns the key that maps to the specified value, or null if this dual
     * hash map contains no mapping for the value.
     * 
     * @param value
     *            the value that maps from the key that should be returned
     * @return the key that maps to the specified value, or null if this dual
     *         map contains no mapping for the value
     */
	public K reverseGet(V value)
	{
		return reverseMap.get(value);
	}
	
}