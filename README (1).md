
# Best Metro Route

The provided C++ code implements a Graph class called Graph_Metro, which represents a metro map. It uses an adjacency list representation using an unordered map to store the vertices and their neighboring vertices. The class provides various functionalities to manipulate and analyze the metro map, including adding and removing vertices, adding and removing edges, checking for the existence of a vertex or edge, finding the number of vertices and edges, displaying the metro map, finding the shortest distance and time between two stations using Dijkstra's algorithm, finding the minimum spanning tree of the metro map, and printing the list of stations with their codes.

It provides a convenient way to add, remove, and analyze vertices and edges in the metro map. Additionally, it includes algorithms for finding the shortest distance and time between two stations, as well as finding the minimum spanning tree of the metro map. Created a user-friendly interface to input source and destination stations, visualize optimal routes, and display estimated travel time.



## Time Complexity

The time complexity of the code also depends on the size of the input and the number of vertices and edges in the graph.
The time complexity of various operations in the Graph_Metro class is as follows:
Adding a vertex (add_a_Vertex): O(1)
Removing a vertex (remove_a_Vertex): O(E)
Adding an edge (add_a_Edge): O(1)
Removing an edge (remove_a_Edge): O(1)
Checking if an edge exists (check_if_containsEdge): O(1)
Finding the number of vertices (numVertex): O(1)
Finding the number of edges (num_of_Edges): O(V)
Displaying the map (display_the_Map): O(V + E)
Displaying all stations (display_all_Stations): O(V)
Checking if there is a path between two vertices (if_hasPath): O(V + E)
Dijkstra's algorithm (dijkstra): O((V + E) log V)
Finding the minimum distance (getMinimumDistance): O(V + E)
Finding the minimum distance vertex (getMinimumDistanceVertex): O(V)
Finding the minimum spanning tree (findMinimumSpanningTree): O(V^2)
## Space Complexity

The space complexity of the code depends on the size of the input and the number of vertices and edges in the graph.
The space complexity of the Graph_Metro class is O(V + E), where V is the number of vertices and E is the number of edges in the graph.
The space complexity of the unordered_map used to store vertices (vtces) is O(V), where V is the number of vertices.
The space complexity of each Vertex object is O(E), where E is the number of edges connected to that vertex.
The space complexity of other data structures used, such as queues, vectors, and priority queues, depends on the specific operations and their usage in the code.


## REQUIREMENTS

The project can run on any online or offline Integrated Development Environment (IDE).