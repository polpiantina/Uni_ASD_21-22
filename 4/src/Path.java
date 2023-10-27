import java.util.ArrayList;
import java.util.HashMap;
import java.io.*;

public class Path {
	
	/**
	*	The method returns a HashMap containing the pair (String node name (value), Object Node), with Value, Previous and Distance as private attributes. Use getters to retrieve their values.
	*	This allows the user to get the distance of each node from the origin and reconstruct the path
	*	@param	graph 	requires <String,Double> types, cast values when loading the graph if necessary
	*	@param	origin 	is the starting node, should be a lowercase String in our example
	*	@return 		is a HashMap<String,Node> so it's easy to get the distance from the origin and reconstruct the path
	*/
	public static HashMap<String,Node> dijkstra(Graph<String,Double> graph, String origin) throws IOException {
		Heap<Node> queue = new Heap<>();
		ArrayList<String> graphNodes = graph.retrieveNodes();
		
		//	load graph into queue
		for(int i = 0; i < graphNodes.size(); i++) {
			queue.add(new Node(graphNodes.get(i)));
		}
		//set origin node distance to 0
		queue.lowerValue(new Node(origin), new Node(origin, null, 0.0));
		
		//	save the pair (nodeValue, Node) so it's easy to retrieve the origin-destination path with the distance
		HashMap<String,Node> distances = new HashMap<>();
		
		while(queue.size() > 0) {
			Node currentNode = queue.extractMin();
			ArrayList<String> adj = graph.retrieveAdjacentNodes(currentNode.getValue());
			
			//	if the node is popped from the queue it means it has the lowest possible distance from the origin, so I can add it to the hashmap
			distances.put(currentNode.getValue(), currentNode);
			
			for(int i = 0; i < adj.size(); i++) {	//  RELAX
			
				//	fake node needed for the if and the trick
				Node adjacentNode = new Node(adj.get(i));

				if(queue.contains(adjacentNode)) {
				
				//	start of trick - I created a fake node and use it to retrieve the real node from the queue so I can access the distance value
				//	get the value of the left child of the fake node I created (returns copy of itself from queue if it has no child)
					Node tempLeft = queue.getLeftChild(adjacentNode);
				//	if it didn't return itself I need to get its parent (returning to the copy of the fake node from the queue)
					if(adjacentNode.equals(tempLeft))		adjacentNode = tempLeft;
					else 									adjacentNode = queue.getParent(tempLeft);
				//	end of trick - adjacentNode now contains the values of the node I needed from the queue
					
				//	save the weight so that the code is easier to read
					Double weight = graph.retrieveLabel(currentNode.getValue(), adjacentNode.getValue());
					
					//  if(src.d + w(src,dest) < dest.d)
					if(Double.compare(currentNode.getDistance() + weight, adjacentNode.getDistance()) < 0) {		
					
						//	save the node so that the code is easier to read - value, previous, distance
						Node newAdjacentNode = new Node(adjacentNode.getValue(), currentNode.getValue(), currentNode.getDistance() + weight);
						//	update the node distance from origin - if I'm updating it, it's surely lower than before
						queue.lowerValue(adjacentNode, newAdjacentNode);
					}
				}
			}
		}
		//	return the hashmap with the lowest possible distances of each node from the origin
		return distances;
	}
	
//	version of the algorithm that uses a hashmap with distances rather than getting the values directly from the heap
	public static HashMap<String,Node> mapDijkstra(Graph<String,Double> graph, String origin) throws IOException {
		HashMap<String,Double> queueMap = new HashMap<>();
		Heap<Node> queue = new Heap<>();
		ArrayList<String> graphNodes = graph.retrieveNodes();
		
		//	load graph into queue
		for(int i = 0; i < graphNodes.size(); i++) {
			queue.add(new Node(graphNodes.get(i)));
			queueMap.put(graphNodes.get(i), Double.POSITIVE_INFINITY);
		}
		//set origin node distance to 0
		queue.lowerValue(new Node(origin), new Node(origin, null, 0.0));
		queueMap.replace(origin, 0.0);
		
		//	save the pair (nodeValue, Node) so it's easy to retrieve the origin-destination path with the distance
		HashMap<String,Node> distances = new HashMap<>();
		
		while(queue.size() > 0) {
			Node currentNode = queue.extractMin();
			ArrayList<String> adj = graph.retrieveAdjacentNodes(currentNode.getValue());
			
			//	if the node is popped from the queue it means it has the lowest possible distance from the origin, so I can add it to the hashmap
			distances.put(currentNode.getValue(), currentNode);
			
			for(int i = 0; i < adj.size(); i++) {	//  RELAX
			
				if(queueMap.containsKey(adj.get(i))) {
				
					//	save the value so that the code is easier to read
					Double weight = graph.retrieveLabel(currentNode.getValue(), adj.get(i));
					if(Double.compare(currentNode.getDistance() + weight, queueMap.get(adj.get(i))) < 0) {		//  if(u.d + w(u,v) < v.d)
					
						//	save the value so that the code is easier to read
						Node newAdjacentNode = new Node(adj.get(i), currentNode.getValue(), currentNode.getDistance() + weight);
						queue.lowerValue(new Node(adj.get(i)), newAdjacentNode);
						queueMap.replace(adj.get(i), newAdjacentNode.getDistance());
					}
				}
			}
			queueMap.remove(currentNode.getValue());
		}
		//	return the hashmap with the lowest possible distances of each node from the origin
		return distances;
	}
}
