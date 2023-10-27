import java.util.Collections;
import java.util.ArrayList;
import java.util.HashMap;
import java.io.*;

public class Main {
	public static void main(String[] args) {
		
		HashMap<String,Node> pathsMap;
		String origin = "torino";
		String destination = "catania";
			
		System.out.println("	----	OUTPUT EXPECTED FROM UNDIRECTED GRAPHS = ~1207.68		----\n");
		try {
			Graph<String,Double> undirectedGraph = new Graph<>(false);
			loadGraph(undirectedGraph, args[0]);
			System.out.println("Graph uses heap search");
			pathsMap = Path.dijkstra(undirectedGraph, origin);
			printMinDistance(pathsMap, origin, destination);
			System.out.print("Path followed to get from " + origin + " to "+ destination + " -> ");
			printMinPath(pathsMap, destination);
			System.out.println();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		try {
			Graph<String,Double> undirectedMapGraph = new Graph<>(false);
			loadGraph(undirectedMapGraph, args[0]);
			System.out.println("Graph uses map search");
			pathsMap = Path.mapDijkstra(undirectedMapGraph, origin);
			printMinDistance(pathsMap, origin, destination);
			System.out.print("Path followed to get from " + origin + " to "+ destination + " -> ");
			printMinPath(pathsMap, destination);
			System.out.println();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		
		
		System.out.println("\n	----	OUTPUT EXPECTED FROM DIRECTED GRAPHS = ~1251.35			----\n");

		try {
			Graph<String,Double> directedGraph = new Graph<>(true);
			loadGraph(directedGraph, args[0]);
			System.out.println("Graph uses heap search");
			pathsMap = Path.dijkstra(directedGraph, origin);
			printMinDistance(pathsMap, origin, destination);
			System.out.print("Path followed to get from " + origin + " to "+ destination + " -> ");
			printMinPath(pathsMap, destination);
			System.out.println();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		
		try {
			Graph<String,Double> directedMapGraph = new Graph<>(true);
			loadGraph(directedMapGraph, args[0]);
			System.out.println("Graph uses map search");
			pathsMap = Path.mapDijkstra(directedMapGraph, origin);
			printMinDistance(pathsMap, origin, destination);
			System.out.print("Path followed to get from " + origin + " to "+ destination + " -> ");
			printMinPath(pathsMap, destination);
			System.out.println();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
	}
	
	private static void loadGraph(Graph<String,Double> graph, String filename) {
		try{
			File file = new File(filename);
			BufferedReader buffer = new BufferedReader(new FileReader(file));
			String line;
			
			int rows = 0, nodesAdded = 0, edgesAdded = 0;
			try{
				while((line = buffer.readLine()) != null) {
					String[] lineFields = line.split(",");
					
					try {
						graph.addNode(lineFields[0]);
						nodesAdded++;
					} catch(IOException e) {
						//	e.printStackTrace();
					}
					
					try {
						graph.addNode(lineFields[1]);
						nodesAdded++;
					} catch(IOException e) {
						//	e.printStackTrace();
					}
					
					try {
						graph.addEdge(lineFields[0], lineFields[1], Double.valueOf(lineFields[2]));
						edgesAdded++;
					} catch(IOException e) {
						//	e.printStackTrace();
					}
					rows++;
				}
				if(graph.isDirect())			System.out.println("Graph is directed");
				else							System.out.println("Graph is undirected");
				if(rows == 56640)				System.out.println("Rows -> ok");
				else							System.out.println("Rows -> ERROR");
				if(nodesAdded == 18640)			System.out.println("Nodes -> ok");
				else							System.out.println("Nodes -> ERROR");
				if(graph.isDirect())
					if(edgesAdded == 56640)		System.out.println("Edges -> ok");
					else						System.out.println("Edges -> ERROR");
				else 
					if(edgesAdded == 48055)		System.out.println("Edges -> ok");
					else						System.out.println("Edges -> ERROR");
				//System.out.println();
							
				//  LOADED THE GRAPH, CHECKED IF THE NUMBERS OF EDGES / NODES LOADED IS CORRECT
			} catch (IOException e) {
				e.printStackTrace();
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
	}
	
	private static void printMinDistance(HashMap<String,Node> pathsMap, String origin, String destination) {
		System.out.println(origin + " -> " + destination + " - " + pathsMap.get(destination).getDistance()/1000 + " km");
	}
	
	private static void printMinPath(HashMap<String,Node> pathsMap, String destination) {
		ArrayList<String> list = new ArrayList<>();
		
		String temp = destination;
		while(temp != null) {
			list.add(temp);
			temp = pathsMap.get(temp).getPrevious();
		}
		
		Collections.reverse(list);
		System.out.println(list.toString());
	}
}
