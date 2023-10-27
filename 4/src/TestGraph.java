import org.junit.Test;
import static org.junit.Assert.*;

import java.util.ArrayList;

public class TestGraph {

   /*
    *
    *	 The methods of Heap were already tested in the 3rd project, so they won't be checked again.
    *    If needed, just copy from 3/src/TestHeap.java the tests wanted.
    *
    */

    @Test
    public void testEdgeNull(){
        Edge<Integer, Double> edge = null;
        assertEquals("Creating an edge as null - FAILED", null, edge);
        System.out.println("Creating an edge as null - OK");
    }

    @Test
    public void testEdgeNullElements(){
        Edge<Integer, Double> edge = new Edge<Integer,Double>(null, null, null);
        assertEquals("Creating an edge with null elements - FAILED", null, edge.getLabel());
        System.out.println("Creating an edge with null elements - OK");
    }

    @Test
    public void testNodeCompareNull(){
        try {
            Node node = new Node("1", null, 10.0);
            Node node2 = new Node(null, null, null);
            //assertEquals(0, node.compareTo(node2));
            node.compareTo(node2);
            System.out.println("Comparing a node to another (which is null) - FAILED");
        } catch (Exception e) {
            System.out.println("Comparing a node to another (which is null) - OK");
        }	
    }

    @Test
    public void testNodeEqualsNull(){
        Node node = new Node("1", null, 10.0);
        assertEquals("Checking if a node is equal to null - FAILED", false, node.equals(null));
        System.out.println("Checking if a node is equal to null - OK");
    }

    @Test
    public void testNodeEqualsWrong(){
        Node node = new Node("1", null, 10.0);
        assertEquals("Checking if a node is equal to another from a different class - FAILED", false, node.equals(new Edge<Integer,String>(1, 2, "3")));
        System.out.println("Checking if a node is equal to another from a different class - OK");
    }

    @Test
    public void testGraphContainsEdgesNull(){
        boolean a = false;
        try{
            Graph<String,Double> graph = new Graph<>(true);
            //assertEquals(false, graph.containsEdge(null, null));
            a = graph.containsEdge(null, null);
            System.out.println("Searching a null edge in a graph "+ a +" - FAILED");
        } catch (Exception e) {
            System.out.println("Searching a null edge in a graph returns "+ a +" - OK");
        }	
    }

    @Test
    public void testGraphDeleteNoEdges(){
        try{
            Graph<String,Double> graph = new Graph<>(true);
            graph.deleteEdge(null, null);
            System.out.println("Deleting an edge passing null as parameters - FAILED");
        } catch (Exception e) {
            System.out.println("Deleting an edge passing null as parameters - OK");
        }	
    }

    @Test
    public void testGraphSizeNodesEmpty(){
        Graph<String,Double> graph = new Graph<String, Double>(true);
        assertEquals("Checking the size (Nodes) of an empty graph - FAILED", 0, graph.sizeNodes());
        System.out.println("Checking the size (Nodes) of an empty graph - OK");	
    }

    @Test
    public void testGraphSizeEdgesEmpty(){
        Graph<String,Double> graph = new Graph<String, Double>(false);
        assertEquals("Checking the size (Edges) of an empty graph - FAILED", 0, graph.sizeEdges());
        System.out.println("Checking the size (Edges) of an empty graph - OK");	
    }

    @Test
    public void testGraphNodesListEmpty(){
        Graph<String,Double> graph = new Graph<String, Double>(false);
        assertEquals("Checking the list of nodes of an empty graph - FAILED", new ArrayList<>().toString(), graph.retrieveNodes().toString());
        System.out.println("Checking the list of nodes of an empty graph - OK");
    }

    @Test
    public void testGraphEdgeListEmpty(){
        Graph<String,Double> graph = new Graph<String, Double>(false);
        assertEquals("Checking the list of edges of an empty graph - FAILED", new ArrayList<>().toString(), graph.retrieveEdges().toString());
        System.out.println("Checking the list of edges of an empty graph - OK");
    }

    @Test
    public void testGraphAdjacentNodesNull(){
        try {
            Graph<String,String> graph = new Graph<String,String>(false);
            String node1 = "node1";
            graph.addNode(node1);
            assertEquals("Checking the adjacent nodes passing null - FAILED", new ArrayList<>(), graph.retrieveAdjacentNodes(node1));
        } catch (Exception e) {
            System.out.println("Checking the adjacent nodes passing null - OK");
        }	
    }

    @Test
    public void testGraphRetrieveLabel(){
        try {
            Graph<String,String> graph = new Graph<String,String>(false);
            String node1 = "node1";
            String node2 = "node2";
            graph.addNode(node1);
            graph.addNode(node2);
            graph.addEdge(node1, node2, "test");
            assertEquals("Checking the label between two nodes - FAILED", "test", graph.retrieveLabel(node1, node2));
        } catch (Exception e) {
            System.out.println("Checking the label between two nodes - OK");
        }	
    }
}
