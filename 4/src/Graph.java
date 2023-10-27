import java.util.ArrayList;
import java.util.HashMap;
import java.util.Set;
import java.io.*;

/**
 *	This class allows the creation and use of graphs. I chose to use Edge<T,S> as a support class rather than Node<T,S> so that the method retrieveEdges
 *	can return its elements in a simple ArrayList<Edge<T,S>> rather than a HashMap<T,<HashMap<T,S>>, with the inner HashMap coming from the object Node.
 *	I chose to return an ArrayList for every retrieveSomething method for consistency rather than returning values in different data structures just "because
 *	they were convenient".
 */

public class Graph <T extends Comparable<T>, S> {
	
	private boolean direct;
	private HashMap<T, ArrayList<Edge<T,S>>> nodes;
	
	//	O(1)
	public Graph(boolean direct) {
		this.direct = direct;
		nodes = new HashMap<>();
	}
	
	//	O(1)
	public void addNode(T val) throws IOException {
		if(this.nodes.putIfAbsent(val, new ArrayList<Edge<T,S>>()) != null)
			throw new IOException("cannot add the same element more than once (" + val + ")");
	}
	
	//	O(1)
	public void addEdge(T startNode, T endNode, S label) throws IOException {
		if(this.containsEdge(startNode, endNode))
			throw new IOException("cannot add more than one edge from staring node to end node (" + startNode + " -> " + endNode + ")");
		this.nodes.get(startNode).add(new Edge<T,S>(startNode, endNode, label));
		
		//	in an undirected graph the edges need to be doubled
		if(!direct)	{
			if(this.containsEdge(endNode, startNode))
				throw new IOException("cannot add more than one edge from staring node to end node (" + endNode + " -> " + startNode + ")");
			this.nodes.get(endNode).add(new Edge<T,S>(endNode, startNode, label));
		}
	}
	
	//	O(1)
	public boolean isDirect() {
		return this.direct;
	}
	
	//	O(1)
	public boolean containsNode(T node) {
		return this.nodes.get(node) != null;
	}
	
	//	O(1)*
	public boolean containsEdge(T startNode, T endNode) throws RuntimeException {
		if(!this.containsNode(startNode))
			throw new RuntimeException("cannot find starting node (" + startNode+ ")");
			
		for(int i = 0; i < this.nodes.get(startNode).size(); i++)
			if(this.nodes.get(startNode).get(i).getEndNode().compareTo(endNode) == 0)
				return true;
		return false;
	}
	
	//	O(n)
	public void deleteNode(T node) throws RuntimeException {
		if(!this.containsNode(node))
			throw new RuntimeException("cannot find node (" + node + ")");
			
		Set<T> keySet = this.nodes.keySet();
		for(T key : keySet) {
			try {
				deleteEdge(key, node);
			} catch (Exception e) {
				// nothing to print here
			}
		}
		this.nodes.remove(node);
	}
	
	//	O(1)*
	public void deleteEdge(T startNode, T endNode) throws RuntimeException {
		if(!this.containsNode(startNode)) throw new RuntimeException("cannot find starting node (" + startNode + ")");
			
		for(int i = 0; i < this.nodes.get(startNode).size(); i++) {
			if(this.nodes.get(startNode).get(i).getEndNode().compareTo(endNode) == 0) {
				this.nodes.get(startNode).remove(i);
				return;
			}
		}
		throw new RuntimeException("cannot find edge (" + startNode + " -> " + endNode + ")");
	}
	
	//	O(1)
	public int sizeNodes() {
		return nodes.size();
	}
	
	//	O(n)
	public int sizeEdges() {
		int numEdges = 0;
		Set<T> keySet = this.nodes.keySet();
		for(T key : keySet) 
			numEdges += this.nodes.get(key).size();
		return this.direct ? numEdges : numEdges/2;			// in non-direct graphs edges are doubled
	}
	
	//	O(n)
	public ArrayList<T> retrieveNodes() {
		ArrayList<T> nodesList = new ArrayList<>();
		
		Set<T> keySet = this.nodes.keySet();
		for(T key : keySet) {
			nodesList.add(key);
		}
		return nodesList;
	}
	
	//	O(n)
	public ArrayList<Edge<T,S>> retrieveEdges() {
		ArrayList<Edge<T,S>> edges = new ArrayList<>();
		
		Set<T> keySet = this.nodes.keySet();
		for(T key : keySet) {
			for(int i = 0; i < this.nodes.get(key).size(); i++) {
				edges.add(this.nodes.get(key).get(i));
			}
		}
		return edges;
	}
	
	//	O(1)* - method isn't needed, added for consistency and it makes sense considering how the class was built 
	public ArrayList<Edge<T,S>> retrieveAdjacentEdges(T node) {	//
		if(!this.containsNode(node))
			throw new RuntimeException("cannot find starting node (" + node + ")");
		
		ArrayList<Edge<T,S>> adjacents = new ArrayList<>();
		for(int i = 0; i < this.nodes.get(node).size(); i++) {
			adjacents.add(this.nodes.get(node).get(i));
		}
		return adjacents;
	}
	
	//	O(1)*
	public ArrayList<T> retrieveAdjacentNodes(T node) throws RuntimeException {
		if(!this.containsNode(node))
			throw new RuntimeException("cannot find starting node (" + node + ")");
		
		ArrayList<T> adjacents = new ArrayList<>();
		for(int i = 0; i < this.nodes.get(node).size(); i++) {
			adjacents.add(this.nodes.get(node).get(i).getEndNode());
		}
		return adjacents;
	}
	
	//	O(1)*
	public S retrieveLabel(T startNode, T endNode) throws RuntimeException {
		if(!this.containsNode(startNode))
			throw new RuntimeException("cannot find starting node (" + startNode + ")");
		
		for(int i = 0; i < this.nodes.get(startNode).size(); i++) {
			if(this.nodes.get(startNode).get(i).getEndNode().compareTo(endNode) == 0)
				return this.nodes.get(startNode).get(i).getLabel();
		}
		
		throw new RuntimeException("cannot find edge (" + startNode + " -> " + endNode + ")");
	}
	
}
