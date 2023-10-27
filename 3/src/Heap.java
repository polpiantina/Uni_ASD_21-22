import java.util.ArrayList;
import java.util.HashMap;
import java.io.*;

/**
 *	This class allows the creation and use of a min-heap with generic types. 
 *	All basic operations are public, some other useful methods are private. They are not accessible as they simply smooth out the rest of the operations and
 *	would allow the user to get a more direct access to the elements. There is no method to get an element knowing its position in the ArrayList.
 *	The method moveUp() swaps an element with its parent. I decided to implement it this way because I find it easier to get a gist of what and why the swaps
 *	are happening where they're called. Since we can easily get the parent of an element, removing the second parameter makes sure we can't make mistakes by 
 *	swapping elements that should never be swapped.
 */

public class Heap <T extends Comparable<T>> {

	private ArrayList<T> list;
	private HashMap<T, Integer> map;	//	element -> position (in the list)
	
	//	O(1)
	public Heap() {
		this.list = new ArrayList<>();
		this.map = new HashMap<>();
	}
	
	//	O(log n)
	public void add(T elem) throws IOException {
		if(elem == null) throw new IOException("cannot add a null element");
		if(this.map.putIfAbsent(elem, this.size()) != null)
			throw new IOException("cannot add the same element more than once (" + elem + ")");
		
		//	add at end of list
		this.list.add(elem);
		
		//	no need to check if it's the root, because parent of root is the root itself (==)
		while(elem.compareTo(this.getParent(elem)) < 0){
			//	no need to heapify, the new value can only go up
			moveUp(elem);
		}
	}
	
	//	O(1)
	public int size() {
		return this.list.size();
	}
	
	//	O(1)
	public T getParent(T elem) {
		int pos = this.getElementIndex(elem);
		return this.list.get(this.getParentIndex(pos));
	}
	
	//	O(1)
	public T getLeftChild(T elem) {
		int pos = this.getElementIndex(elem);
		return this.list.get(this.getLeftChildIndex(pos));
	}
	
	//	O(1)
	public T getRightChild(T elem) {
		int pos = this.getElementIndex(elem);
		return this.list.get(this.getRightChildIndex(pos));
	}
	
	//	O(log n)
	//	remove the lowest value and return it
	public T extractMin() {
		if(this.size() == 0) throw new NullPointerException("trying to remove the lowest value from an empty list");
		T first = this.list.get(0);
		
		this.map.replace(this.list.get(this.size()-1), 0);
		this.map.remove(first);

		this.list.set(0, this.list.get(this.size()-1));
		this.list.remove(this.size()-1);
		
		this.minHeapify(0);
		return first;
	}
	
	//	O(log n)
	//	replace elem with an elem of lower value
	public void lowerValue(T oldElem, T newElem) throws IOException {
		if(newElem.compareTo(oldElem) > 0)	
			throw new IOException("initial value is lower than desired value (" + oldElem + " < " + newElem + ")");
		if(newElem.compareTo(oldElem) == 0)	
			throw new IOException("initial value is equal to desired value (" + oldElem + " = " + newElem + ")");
		
		int pos = this.getElementIndex(oldElem);
		this.map.remove(oldElem);
		if(this.map.putIfAbsent(newElem, pos) != null)
			throw new IOException("cannot add the same element more than once (" + newElem + ")");
			
		this.list.set(pos, newElem);
		
		//  no need to check if it's the root, because parent of root is the root itself (==)
		while(newElem.compareTo(this.getParent(newElem)) < 0){
			//	no need to heapify, the new value can only go up because it's lower than before
			moveUp(newElem);
		}
	}
	
	//  -  SUPPORT METHODS  -
	
	@Override
	public String toString() {
		return this.list.toString();
	}
	
	public boolean contains(T elem) {
		return this.map.get(elem) != null;
	}
	
	private int getParentIndex(int child) {
		//	-1/2 is still 0 in int, so no check needed for parent of root
		int parent = (child - 1) / 2;
		return parent;
	}
	
	private int getLeftChildIndex(int parent) {
		int child = (parent * 2) + 1;
		//	if the child doesn't exist, return the node itself
		if(child > this.size() - 1)	return parent;
		return child;
	}
	
	private int getRightChildIndex(int parent) {
		int child = (parent * 2) + 2;
		//	if the child doesn't exist, return the node itself
		if(child > this.size() - 1)	return parent;	
		return child;
	}
	
	private int getElementIndex(T elem){
		if (!this.contains(elem) || elem == null)	
			throw new NullPointerException("tried to access element not in the array (" + elem + ")");
		int pos = this.map.get(elem);
		return pos;
	}
	
	//	from the book, adapted from max Heap - 6.2  -  left, right and parent are indexes
	private void minHeapify(int parent) {			
		if(this.size() <= 1)	return;
		int left = this.getLeftChildIndex(parent);
		int right = this.getRightChildIndex(parent);
		int smallest = parent;
		
		if(left != - 1 && this.list.get(left).compareTo(this.list.get(parent)) < 0)
			smallest = left;
		if(right != - 1 && this.list.get(right).compareTo(this.list.get(smallest)) < 0)
			smallest = right;
			
		if(smallest != parent) {
			this.moveUp(this.list.get(smallest));
			this.minHeapify(smallest);
		}
	}
	
	//	swap elem with its parent
	private void moveUp(T elem) {
		int elemPos = this.getElementIndex(elem);
		if(elemPos == 0)	return;
		int parentPos = this.getParentIndex(elemPos);
		T parent = this.list.get(parentPos);
		
		this.list.set(parentPos, elem);		//  change value of parent (to elem)
		this.list.set(elemPos, parent);		//  change value of elem (to parent)
		
		//  same as above, in HashMap
		this.map.replace(elem, parentPos);
		this.map.replace(parent, elemPos);
	}
}
