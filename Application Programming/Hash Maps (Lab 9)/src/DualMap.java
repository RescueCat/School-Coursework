/**
 * A DualMap maintains a one-to-one mapping between keys and value. A DualMap
 * object should contain a Map from keys to values and a Map from values to
 * keys. A DualMap cannot contain duplicate keys or duplicate values.
 * 
 * @author Tom Bylander
 */
public interface DualMap<K, V> 
{
	/**
     * Associates the specified value with the specified key in this dual map.
     * After dualmap.put(key, value) is performed, then dualmap.get(key) should
     * return value and dualmap.reverseGet(value) should return key.
     * <p>
     * If the dual map previously contained a mapping for the key or the value,
     * the old association(s) should be removed.
     * 
     * @param key
     *            key to be associated with the specified value.
     * @param value
     *            value to be associated with the specified key
     */
    public void put(K key, V value);

    /**
     * Removes the mapping from the key to the value from this dual map if it is
     * present. After dualmap.put(key, value) and dualmap.remove(key, value),
     * then dualmap.get(key) should return null and dualmap.reverseGet(value)
     * should return null.
     * 
     * @param key
     *            key whose mapping to value is to be removed
     * @param value
     *            value whose mapping from key is to be removed
     */
    public void remove(K key, V value);

    /**
     * Returns the value that maps from the specified key, or null if this dual
     * map contains no mapping for the key.
     * 
     * @param key
     *            the key that maps to the value that should be returned
     * @return the value that maps from the specified key, or null if this dual
     *         map contains no mapping for the key
     */
    public V get(K key);

    /**
     * Returns the key that maps to the specified value, or null if this dual
     * map contains no mapping for the value.
     * 
     * @param value
     *            the value that maps from the key that should be returned
     * @return the key that maps to the specified value, or null if this dual
     *         map contains no mapping for the value
     */
    public K reverseGet(V value);

}
