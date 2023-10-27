public class Node implements Comparable<Node>{
	
	private String value, previous;
	private Double distance;
	
	public Node(String value) {
		this.value = value;
		this.previous = null;
		this.distance = Double.POSITIVE_INFINITY;
	}
	
	public Node(String value, String previous, Double distance) {
		this.value = value;
		this.previous = previous;
		this.distance = distance;
	}
	
	public String getValue() {
		return this.value;
	}
	
	public String getPrevious() {
		return this.previous;
	}
	
	public Double getDistance() {
		return this.distance;
	}
	
	public void setPrevious(String newPrevious) {
		this.previous = newPrevious;
	}
	
	public void setDistance(Double newDistance) {
		this.distance = newDistance;
	}
	
	public int compareTo(Node n) {	//  always compare nodes based on their distance, not the rest of the attributes
		if(this.distance == null || n.getDistance() == null) throw new NullPointerException();
		if(Double.compare(this.distance, n.getDistance()) < 0)			return -1;
		else if(Double.compare(this.distance, n.getDistance()) > 0)		return  1;
		else															return  0;
	}
	
	@Override
	public String toString() {
		return "value: " + this.value + "\nprevious: " + this.previous + "\ndistance: " + this.distance;
	}
	
	//  -  WITH THE FOLLOWING METHODS WE CAN COMPARE TWO OBJECTS AND IT WILL TELL US THEY'RE THE SAME OBJECT (IF THEIR VALUE IS EQUAL)  -
	
	@Override
	public int hashCode() {
		return this.value.hashCode();
	}
	
	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		
		Node other = (Node) obj;
		if (!this.value.equals(other.getValue()))
			return false;
		return true;
	}
}
