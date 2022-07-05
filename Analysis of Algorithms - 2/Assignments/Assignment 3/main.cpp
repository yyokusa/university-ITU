// Yasin Abdulkadir Yokus 150190739 yokus19@itu.edu.tr
// !!!! Please compile with "g++ -std=c++11 -Werror -Wall main.cpp -o homework3" !!!!
#include <iostream>
#include <string>  // string
#include <cstdlib> // strtoul
#include <vector> // vector
#include <fstream> // ifstream, ofstream
#include <sstream> // stringstream
#include <queue> // system_clock
#include <limits>
#include <map>
#include <iomanip>
#include <algorithm>

// for bfs - undiscovered, discovered, visited in order
enum COLOR {WHITE, GRAY, BLACK};

// represents an edge of a graph
struct Edge {
    int capacity = 0;        // max flow capacity
    double probability = 0;  // probability of destruction
    int flow = 0;            // flow through edge
};

// represents a vertex of a graph
struct Vertex {               // used on - aim
    int distance = 0;         // for bfs - distance from source node
    COLOR color = WHITE;      // for bfs - color (explained in "enum COLOR")
    Vertex* parent = nullptr; // for bfs - general bfs and path construction
};

/* Graph Data Structure
 * Representation using adjacency matrix for weighted edges
 * How to store vertexes can be differ (From reference book) -> we chose vector
 */
struct Graph {
    Graph(int cardinalityOfVertices) {
        edges = std::vector<std::vector<Edge> >(cardinalityOfVertices, std::vector<Edge>(cardinalityOfVertices, Edge()));
        vertexes = std::vector<Vertex>(cardinalityOfVertices, Vertex());
        this->cardinalityOfVertices = cardinalityOfVertices;
    }
    std::vector<std::vector<Edge> > edges;
    std::vector<Vertex> vertexes;
    int cardinalityOfVertices;
};


void printGraph(Graph& graph);
int findFlowFInG(Graph& graph);
Graph* get_residual_graph(Graph& graph);
int find_path_index(Graph& g, Vertex& fv);
std::vector<Vertex*>* adjacents_list(Graph& graph, Vertex& u);
void ford_fulkerson(Graph& graph, int sourceNode, int destNode);
std::pair<bool, std::vector<Vertex*> > bfs(Graph& graph, Vertex& s, Vertex& t);
std::vector<std::pair<int, int> > find_edges_along_path(Graph& , std::vector<Vertex *>);
void readFileIntoGraph(Graph& graph, const int cardinalityOfVertices, std::ifstream& inputFileStream);
int find_min_residual_capacity_along_path(Graph& graph, std::vector<Vertex *> path_vertexes_from_end_to_source);
std::vector<std::vector<bool>> get_combinations(int numberOfElements);
std::vector<std::pair<int, int> > getPossibleRemovingCoords(Graph& graph);
void findFordFulkersonIterationResult(std::map<int, double >& ffir, std::vector<std::pair<int, int> >& prc,
                                      std::vector<std::vector<bool>>& combinations, Graph& graph,
                                      int sourceNode, int destNode);


int main(int argc, char *argv[]) {
    // check input count (./homework3 [input file] [src node] [dst node])
    if (argc != 4) {
        std::cout << "Missing arguments..." << std::endl;
        exit(EXIT_FAILURE);
    }

    // set printing format
    std::cout << std::fixed;
    std::cout << std::setprecision(2);

    // store input file path
    const std::string inputFile(argv[1]); // input file path
    const int sourceNode = atoi(argv[2]); // src_node
    const int destNode = atoi(argv[3]); // dst_node

    // reading file into memory
    std::ifstream inputFileStream;

    // 	open file for reading
    inputFileStream.open(inputFile, std::ifstream::in);

    // check if the file is open, exit with failure else
    if (!(inputFileStream.is_open())) {
        std::cout << "Could not open input file.";
        exit(EXIT_FAILURE);
    }

    // read cardinality of vertices
    std::string valueAsString;
    std::getline(inputFileStream, valueAsString);
    const int cardinalityOfVertices = atoi(valueAsString.c_str());


    // create the original graph
    Graph graph(cardinalityOfVertices);
    // read file into graph
    readFileIntoGraph(graph, cardinalityOfVertices, inputFileStream);

    // close file streams
    inputFileStream.close();

    // holds the result of algorithm inside a map ds --> (key)maximum flow and (value)probability pairs
    std::map<int, double > fordFulkersonIterationResults;
    // holds coordinates of the edges with probabilities greater than 0
    std::vector<std::pair<int, int> > possibleRemovingCoords = getPossibleRemovingCoords(graph);
    // get all combinations of edge removal cases
    std::vector<std::vector<bool>> combinations = get_combinations(possibleRemovingCoords.size());
    // run the main FordFulkersonIterationResult iteratively on every combination to find the result
    findFordFulkersonIterationResult(fordFulkersonIterationResults, possibleRemovingCoords,
                                     combinations, graph, sourceNode, destNode);

    // set expected max flow as 0.0
    auto expectedMaxFlow = 0.0;
    for (auto it = fordFulkersonIterationResults.begin(); it != fordFulkersonIterationResults.end(); ++it) {
        std::cout << "Probability of occurence: " << it->second
                  << ", Maximum Flow: " << it->first << std::endl;
        // fill expected max flow
        expectedMaxFlow += (it->first * it->second);
    }
    
    // print final result
    std::cout << "Expected Maximum Flow from node " << sourceNode << " to node " << destNode
        << ": " << expectedMaxFlow << std::endl;
    return 0;
}



/*
 * This function calculated Ford Fulkerson algorithm result for every single case of
 * edge removal combinations.
 * Then it creates a result data structure to store max flow and their probability.
 * Same max flow probabilities are summed up according to wanted specification.
 *
 * Results are stored in fordFulkersonIterationResults and used for printing in main.
 *
 * ffir: fordFulkersonIterationResults
 * prc : possibleRemovingCoords
 */
void findFordFulkersonIterationResult(std::map<int, double >& ffir, std::vector<std::pair<int, int> >& prc,
                                      std::vector<std::vector<bool>>& combinations, Graph& graph,
                                      int sourceNode, int destNode) {
    for (unsigned int i = 0; i < combinations.size(); ++i) {
        Graph tempGraph = graph;
        std::vector<bool> combination = combinations[i];

        // prob of this max flow case would be equal to: (1 - edge_prob) x (1 - edge_prob) ... for true values in comb
        double probOfComb = 1;

        for (unsigned int j = 0; j < combination.size(); ++j) {
            std::pair<int, int> coords = prc[j];
            if (combination[j] == false) { // false ones are disconnected
                probOfComb *= (tempGraph.edges[coords.first][coords.second].probability);
                tempGraph.edges[coords.first][coords.second].capacity = 0;
                tempGraph.edges[coords.first][coords.second].flow = 0;
            } else {
                probOfComb *= (1 - tempGraph.edges[coords.first][coords.second].probability);
            }
        }
        ford_fulkerson(tempGraph, sourceNode, destNode);
        int maxFlow = findFlowFInG(tempGraph);

        std::pair<std::map<int, double>::iterator, bool> mapCheckRet;
        mapCheckRet = ffir.insert(std::make_pair(maxFlow, probOfComb));
        if (mapCheckRet.second == false) { // maxFlow value already exists
            mapCheckRet.first->second += probOfComb; // probOfComb is the new prob with the same maxFlow
        }
    }
}




/*
 * Find the flow in a given graph
 * From reference book.
 * Corollary 26.5
 * The value of any flow f in a flow network G is bounded from above by the capacity of any cut of G
 */
int findFlowFInG(Graph& graph) {
    int maxFlow = 0;
    // find outgoing flow from a vertex to all others
    for (auto& edge: graph.edges[0]) {
        maxFlow += edge.flow;
    }
    return maxFlow;
}


/*
 * Builds a residual graph using residual capacity formula
 * given in the reference book.
 */
Graph* get_residual_graph(Graph& graph) {
    // create a new graph
    Graph* residual_graph = new Graph(graph.cardinalityOfVertices);

    // vertex sizes for iteration
    int rowCount = graph.cardinalityOfVertices;
    int colCount = graph.cardinalityOfVertices;

    for (int i = 0; i < rowCount; ++i) {
        for (int j = 0; j < colCount; ++j) {
            // get edge from the original graph
            Edge& edge = graph.edges[i][j];

            // edge is an element of the original graph
            if (edge.capacity != 0)
                residual_graph->edges[i][j].capacity = edge.capacity - edge.flow;
            else {
                // edge is NOT an element of the original graph
                Edge& reverse_edge = graph.edges[j][i];
                // REVERSE edge is an element of the original graph
                if (reverse_edge.capacity != 0)
                    residual_graph->edges[i][j].capacity = (reverse_edge.flow);
                else // OTHERS
                    residual_graph->edges[i][j].capacity = 0;
            }
        }
    }

    return residual_graph;
}


/*
 * Get possible removable edge coordinates from the graph created
 * from given input file.
 */
std::vector<std::pair<int, int> > getPossibleRemovingCoords(Graph& graph) {
    std::vector<std::pair<int, int> > result;
    int size = graph.cardinalityOfVertices;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (graph.edges[i][j].probability != 0) {
                result.push_back(std::make_pair(i, j));
            }
        }
    }
    return result;
}


/*
 * Get combinations to be used for edge deletions.
 */
std::vector<std::vector<bool>> get_combinations(int numberOfElements) {
    // vector to store all combinations
    std::vector<std::vector<bool>> result;
    // create 0 to n combinations of n numbers
    for (int i = 0; i <= numberOfElements; i++) {
        // start with all true vector
        std::vector<bool> v(numberOfElements, true);
        // set number of edges to be destruct in a given combination
        std::fill(v.begin(), v.begin() + i, false);
        // sort the array (for next_permutation to work)
        sort(v.begin(), v.end());
        do {
            // gather all cominations for a given i
            result.push_back(v);
        } while(next_permutation(v.begin(), v.end()));
    }
    return result;
}


/*
 * ford fulkerson max flow algorithm implemented from pseudocode given in reference book.
 *
 * given a graph, find and return max flow from source node to destination node.
 *
 */
void ford_fulkerson(Graph& graph, int sourceNode, int destNode) {

    // set all edge flows as zero
    for (auto& edges_list: graph.edges) {
        for (auto& edge: edges_list) {
            edge.flow = 0;
        }
    }

    // find residual graph of given graph
    Graph* residualGraphPtr = get_residual_graph(graph);
    Graph residualGraph = *residualGraphPtr;

    // find source and destionation vertices on residualGraph using given program paramaters sourceNode an destNode
    Vertex& s = residualGraph.vertexes[sourceNode - 1];
    Vertex& t = residualGraph.vertexes[destNode - 1];

    // call BFS to check if a path exists from s to t
    std::pair<bool, std::vector<Vertex*> > resultOfBfs = bfs(residualGraph, s, t);

    // continue if there is a path p from s to t in the residual network G_f
    while (resultOfBfs.first) {
        // extract the path on residual network
        std::vector<Vertex *> path_vs_from_t_to_s = resultOfBfs.second;
        // find minimum residual capacity along the extracted path
        auto min_res_cap = find_min_residual_capacity_along_path(residualGraph, path_vs_from_t_to_s);
        // find edges along the residual path
        std::vector<std::pair<int, int>> edges_along_res_path = find_edges_along_path(residualGraph, path_vs_from_t_to_s);

        // modify the flows of edge flows along the residual path in original graph using minimum residual capacity
        for (auto& p: edges_along_res_path) {
            if (graph.edges[p.first][p.second].capacity != 0) {
                graph.edges[p.first][p.second].flow = graph.edges[p.first][p.second].flow + min_res_cap;
            } else {
                graph.edges[p.second][p.first].flow = graph.edges[p.second][p.first].flow - min_res_cap;
            }
        }

        // delete dynamically created residual graph
        delete residualGraphPtr;

        // get residual graph for the updated original graph
        residualGraphPtr = get_residual_graph(graph);
        residualGraph = *residualGraphPtr;
        // call bfs with the same goal as the initial call
        resultOfBfs = bfs(residualGraph, s, t);
    }
    // ford-fulkerson end
}


/*
 * Given a vertex, find its index in vertexes property of Graph.
 */
int find_path_index(Graph& g, Vertex& fv) {
    int counter = 0;
    for (auto& v: g.vertexes) {
        if (&v == &fv) {
            return counter;
        }
        counter++;
    }
    return -1;
}


/*
 * Finds minimum residual capacity along a path
 */
int find_min_residual_capacity_along_path(Graph& graph, std::vector<Vertex *> path_vertexes_from_end_to_source) {
    auto min_residual_capacity = std::numeric_limits<int>::max();
    for (unsigned int i = 0; i < path_vertexes_from_end_to_source.size() - 1; ++i) {
        auto index2 = find_path_index(graph, *(path_vertexes_from_end_to_source[i]));
        auto index1 = find_path_index(graph, *(path_vertexes_from_end_to_source[i + 1]));
        auto residual_capacity = graph.edges[index1][index2].capacity;
        if (residual_capacity < min_residual_capacity) {
            min_residual_capacity = residual_capacity;
        }
    }
    return min_residual_capacity;
}


/*
 * Given the path extracted from BFS algorithm, find edges along the path.
 *
 * Path consists of vertexes.
 * This func. builds pair of vertex numbers which represent edges.
 */
std::vector<std::pair<int, int> > find_edges_along_path(Graph& graph, std::vector<Vertex *> path_vertexes_from_end_to_source) {
    std::vector< std::pair<int, int> > edges_along_path;
    for (unsigned int i = 0; i < path_vertexes_from_end_to_source.size() - 1; ++i) {
        auto index2 = find_path_index(graph, *(path_vertexes_from_end_to_source[i]));
        auto index1 = find_path_index(graph, *(path_vertexes_from_end_to_source[i + 1]));
        edges_along_path.push_back(std::make_pair(index1, index2));
    }

    return edges_along_path;
}


/*
 * helper for BFS
 * Given a vertex finds its adjacent vertexes.
 */
std::vector<Vertex*>* adjacents_list(Graph& graph, Vertex& u) {
    // find the index number of the given vertex
    int vertexNumber = 0;
    for (auto& v: graph.vertexes) {
        if (&u == &v) {
            break;
        }
        vertexNumber++;
    }

    // extract vertex's adjacent vertexes using edge matrix
    int vertexNumberCounter = 0;
    int idxCounter = 0;
    std::vector<Vertex*> vertexes(graph.vertexes.size());
    for (auto& edge: graph.edges[vertexNumber]) {
        if (edge.capacity != 0) {
            vertexes[idxCounter++] = &(graph.vertexes[vertexNumberCounter]);
        }
        vertexNumberCounter++;
    }

    auto ret = new std::vector<Vertex*>(vertexes);
    ret->assign(vertexes.begin(), vertexes.begin() + idxCounter);
    return ret;
}


/*
 * Breadth first search algorithm implemented from pseudocode
 * given in the reference book.
 *
 * Main goal of bfs for max flow algorithm is that
 * if t is reachable from s
 * then extract the path.
 *
 * graph -> graph to initialize search
 * s -> source vertex
 * t -> destination vertex
 */
std::pair<bool, std::vector<Vertex*> > bfs(Graph& graph, Vertex& s, Vertex& t) {
    for (auto& u: graph.vertexes) {
        u.color = WHITE;
        u.distance = std::numeric_limits<int>::max();
        u.parent = nullptr;
    }
    s.color = GRAY;
    s.distance = 0;
    s.parent = nullptr;
    std::queue<Vertex*> Q;
    Q.push(&s);
    while (!(Q.empty())) {
        Vertex& u = *(Q.front());
        Q.pop();
        std::vector<Vertex *>* adjacents_list_for_u = adjacents_list(graph, u);
        for (auto& v: *adjacents_list_for_u) {
            if (v->color == WHITE) {
                v->color = GRAY;
                v->distance = u.distance + 1;
                v->parent = &u;
                Q.push(v);
            }
        }
        delete adjacents_list_for_u; // free allocated memory
        u.color = BLACK;
    }

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // main goal of bfs for max flow algorithm
    if (!(t.distance == std::numeric_limits<int>::max())) { // there is a path from s to t
        // t is reachable from s
        // extract the path
        Vertex* temp = &t;
        std::vector<Vertex*> path;
        path.push_back(temp);
        while (temp->parent != nullptr) {
            temp = (*temp).parent;
            path.push_back(temp);
        }
       return std::make_pair(true, path);
    }
    return std::make_pair(false, std::vector<Vertex*>());
}


/*
 * This is a helper function to print the file read
 * from the graph it is stored in.
 *
 * This function is only used for debugging during the
 * starting phase of development.
 */
void printGraph(Graph& graph) {
    // print weights of edges
    for (unsigned int i = 0; i < graph.edges.size(); i++) {
        for (unsigned int j = 0; j < graph.edges.size(); j++) {
            std::cout << graph.edges[i][j].capacity << " ";
            if ((j + 1) % 4 == 0) {
                std::cout << std::endl;
            }
        }
    }

    // print probs of edges
    std::cout << "Start probs ..." << std::endl;
    for (unsigned int i = 0; i < graph.edges.size(); i++) {
        for (unsigned int j = 0; j < graph.edges.size(); j++) {
            std::cout << graph.edges[i][j].probability << " ";
            if ((j + 1) % 4 == 0) {
                std::cout << std::endl;
            }
        }
    }

}


/*
 * This function reads input file into a graph.
 */
void readFileIntoGraph(Graph& graph, const int cardinalityOfVertices, std::ifstream& inputFileStream) {
    int graph_row_index_counter = 0;
    int graph_col_index_counter = 0;
    bool edgeValues = true; // if (edgeValue == False) then reading probabilities

    // read file into graph
    std::string edgesInfoLine;
    while(std::getline(inputFileStream, edgesInfoLine)) {
        if (edgesInfoLine == "") { // Values are read, start reading probabilities
            edgeValues = false;
            graph_row_index_counter = 0;
            continue;
        }
        if (edgeValues) {
            std::stringstream lineInfoStream(edgesInfoLine);
            std::string edgeInfoElement;
            while (std::getline(lineInfoStream, edgeInfoElement, ' ')) {
                try {
                    graph.edges[graph_row_index_counter][graph_col_index_counter].capacity = stoi(edgeInfoElement);
                    graph_col_index_counter++;
                }
                catch (std::exception err) {
                    std::cout << "Could not find integer";
                }
                if (graph_col_index_counter == cardinalityOfVertices) {
                    graph_col_index_counter = 0;
                }
            }
        } else {
            std::stringstream lineInfoStream(edgesInfoLine);
            std::string edgeInfoElement;
            while (std::getline(lineInfoStream, edgeInfoElement, ' ')) {
                try {
                    graph.edges[graph_row_index_counter][graph_col_index_counter].probability = stod(edgeInfoElement);
                    graph_col_index_counter++;
                }
                catch (std::exception err) {
                    std::cout << "Could not find double value";
                }
                if (graph_col_index_counter == cardinalityOfVertices) {
                    graph_col_index_counter = 0;
                }
            }
        }
        graph_row_index_counter++;
        edgesInfoLine = "";
    }
}
