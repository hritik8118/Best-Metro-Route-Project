
# Best Metro Route

The provided C++ code implements a Graph class called Graph_Metro, which represents a metro map. It uses an adjacency list representation using an unordered map to store the vertices and their neighboring vertices. The class provides various functionalities to manipulate and analyze the metro map, including adding and removing vertices, adding and removing edges, checking for the existence of a vertex or edge, finding the number of vertices and edges, displaying the metro map, finding the shortest distance and time between two stations using Dijkstra's algorithm, finding the minimum spanning tree of the metro map, and printing the list of stations with their codes.

It provides a convenient way to add, remove, and analyze vertices and edges in the metro map. Additionally, it includes algorithms for finding the shortest distance and time between two stations, as well as finding the minimum spanning tree of the metro map. Created a user-friendly interface to input source and destination stations, visualize optimal routes, and display estimated
travel time and transfers




## Time Complexity 
addVertex, removeVertex, containsVertex, addEdge, removeEdge, containsEdge: These operations have an average time complexity of O(1) since they rely on unordered maps for efficient vertex and edge lookups.

numVertex, numEdges: These operations iterate over the vertices and edges, respectively, which takes O(V + E) time, where V is the number of vertices and E is the number of edges.

displayMap, displayStations, hasPath: These operations involve iterating over the vertices and their neighbors, resulting in a time complexity of O(V + E).

dijkstra: The time complexity of this function is O((V + E)logV), where V is the number of vertices and E is the number of edges. This is because it uses a priority queue (implemented as a heap) to select the next vertex with the minimum cost. Each vertex is processed at most once, and inserting and extracting the minimum element from the priority queue takes logarithmic time.

getMinimumDistance: This function uses a breadth-first search (BFS) algorithm to find the minimum distance between two vertices. The time complexity is O(V + E), as each vertex and edge is visited once.

printCodelist: This function iterates over the vertices and performs string manipulations. The time complexity is O(V), where V is the number of vertices.

## Space Complexity
The space complexity of the code is determined by the storage of vertices, edges, and auxiliary data structures:

The space required for storing vertices and their neighbors is O(V + E), where V is the number of vertices and E is the number of edges.

The space required for storing the priority queue in dijkstra is O(V), as it stores at most V vertices.

The space required for storing the queue in getMinimumDistance is O(V), as it stores at most V vertices.

Additional space is used for auxiliary variables, such as strings and maps, but their space requirements are minimal compared to the main data structures.

Therefore, the overall space complexity of the code is O(V + E).
## REQUIREMENTS
The project can run on any online or offline Integrated Development Environment (IDE).