//import java.io.*;

public class Main {
	public static void main(String[] args){
		try {
			Heap<Integer> heap = new Heap<>();
			heap.add(23);
			heap.add(12);
			heap.add(22);
			heap.add(45);
			heap.add(6);
			heap.add(18);
			heap.add(28);
			heap.add(30);
			heap.add(78);
			heap.add(4);
			heap.add(1);
			heap.add(33);
			heap.add(11);
			heap.add(8);
			heap.add(90);
			heap.add(25);
			heap.add(17);
			
			System.out.println(heap.toString());
			
			System.out.println(heap.extractMin() + "\n" + heap.toString());
			
			heap.lowerValue(45, 3);
			System.out.println(heap.toString());
			
			System.out.println(heap.getParent(3));
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
