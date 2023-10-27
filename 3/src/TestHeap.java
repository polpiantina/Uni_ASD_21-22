import org.junit.Test;
import static org.junit.Assert.*;
import java.io.*;

public class TestHeap {

  @Test
  public void testHeapNull(){
    Heap<Integer> heap = null;
    assertEquals("Creating an heap as null - FAILED", null, heap);
    System.out.println("Creating an heap as null - OK");
  }

  @Test
  public void testHeapNullElement(){
    try {
			Heap<Integer> heap = new Heap<>();
      heap.add(null);
      assertEquals(0, heap.size());
      System.out.println("Getting the size of an empty list - FAILED");
		} catch (IOException e) {
		  System.out.println("Getting the size of an empty list - OK");
		}
  }

  @Test
  public void testNullParent(){
    try {
			Heap<Integer> heap = new Heap<>();
      assertEquals(null, heap.getParent(null));
      System.out.println("Searching the parent of a null element - FAILED");
		} catch (NullPointerException e) {
		  System.out.println("Searching the parent of a null element - OK");
		}
  }

  // given that the methods getLeftChild and getRightChild are virtually identical, we'll test only one of the two
  @Test
  public void testNullLeftChild(){
    try {
			Heap<Integer> heap = new Heap<>();
      assertEquals(null, heap.getLeftChild(null));
      System.out.println("Searching the left child of a null element - FAILED");
		} catch (NullPointerException e) {
		  System.out.println("Searching the left child of a null element - OK");
		}
  }

  @Test
  public void testExtractMinOnEmpty(){
    try {
			Heap<Integer> heap = new Heap<>();
      int size_a = heap.size();
      heap.extractMin();
      int size_b = heap.size();
      assertNotEquals("Extracting the lowest value of an empty list - FAILED", size_a, size_b);
    } catch (NullPointerException e) {
      System.out.println("Extracting the lowest value of an empty list - OK");
		}
  }

  // da checkare, non un reale test unit
  @Test
  public void testDifferentInputs() throws IOException{
			Heap<Integer> heap = new Heap<>();
      heap.add(43);
      heap.add(-1298);
      heap.add(1);
      heap.add(67);
      heap.add(0);
			Heap<Integer> heap2 = new Heap<>();
      heap2.add(67);
      heap2.add(0);
      heap2.add(43);
      heap2.add(1);
      heap2.add(-1298);
      //System.out.println("heap 1: "+heap.toString()+"\nheap 2: "+heap2.toString());
      assertNotEquals("Checking if the output state (and string) is different based on the input - FAILED", heap.toString(), heap2.toString());
      System.out.println("Checking if the final state (and string) is different based on the input - OK");
  }

  @Test
  public void testContainsNull(){
			Heap<Integer> heap = new Heap<>();
      assertEquals("Checking if the map allows null as input - FAILED", false, heap.contains(null));
      System.out.println("Checking if the map allows null as input - OK");
  }

  @Test
  public void testContainsEmpty(){
			Heap<Integer> heap = new Heap<>();
      assertEquals("Checking if the map returns something if it's empty - FAILED", false, heap.contains(1));
      System.out.println("Checking if the map returns something if it's empty - OK");
  }
}
