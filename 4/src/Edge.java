public class Edge <T, S> {
	
	private T startNode, endNode;
	private S label;
	
	public Edge(T startNode, T endNode, S label) {
		this.startNode = startNode;
		this.endNode = endNode;
		this.label = label;
	}
	
	public T getStartNode() {
		return this.startNode;
	}
	
	public T getEndNode() {
		return this.endNode;
	}
	
	public S getLabel() {
		return this.label;
	}
}
