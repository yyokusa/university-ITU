// Yasin Abdulkadir Yokus 150190739 yokus19@itu.edu.tr

#include <iostream>
#include <string>  // string
#include <cstdio> // printf
#include <ctime>  // clock_t, clock, CLOCKS_PER_SEC
#include <cstdlib> // strtoul
#include <vector> // vector
#include <fstream> // ifstream, ofstream
#include <sstream> // stringstream
#include <cctype> // tolower
#include <random> // distribution
#include <chrono> // system_clock
#include <queue> // system_clock

/* Color represents
 * white - undiscovered
 * gray - discovered
 * black - visited
 */
enum Color { white, gray, black };
/* Winner represents
 * player1 - player 1 wins
 * player2 - player 2 wins
 */
enum Winner {player1, player2};

/* Graph nodes
 * int number - node number
 * Color color - node color
 * int distance - distance to the created tree
 * Node* parent - parent node if exists
 * int shipNumber - if it is a part of ship then has ship number
 * int finishTime - finish time in DFS
 * std::vector<Node*> neighbors - 4 neighbors addreses
 */
struct Node {
    Node():
            number(-1),
            color(white),
            distance(std::round_toward_infinity),
            parent(nullptr),
            shipNumber(-1),
            finishTime(-1){}

    Node(const Node& rhs):
            number(rhs.number),
            color(rhs.color),
            distance(rhs.distance),
            parent(rhs.parent),
            shipNumber(rhs.shipNumber),
            finishTime(rhs.finishTime) {}

    Node& operator=(const Node& rhs) {
        shipNumber = rhs.shipNumber;
        number = rhs.number;
        color = rhs.color;
        distance = rhs.distance;
        parent = rhs.parent;
        finishTime = rhs.finishTime;
        return *this;
    }

    int number;
    Color color;
    int distance;
    Node* parent;
    int shipNumber;
    int finishTime;
    std::vector<Node*> neighbors;
};

/* Search Result for BFS
 * winner - winner player
 * p1NumberOfVisitedNodes - Number Of Visited Nodes for player 1
 * p2NumberOfVisitedNodes - Number Of Visited Nodes for player 2
 */
struct SearchResult {
    Winner winner;
    int p1NumberOfVisitedNodes = 0;
    int p2NumberOfVisitedNodes = 0;
};
// BFS and DFS function declarations
SearchResult bfs(std::vector<Node>& graph1, int s1, std::vector<Node>& graph2, int s2, int shipHitPointsPlayer1, int shipHitPointsPlayer2);
void dfs(std::vector<Node>& graph, int opponentShipHitPoints, int s, int& numberOfVisitedNodes, int& numberOfVisitedNodesResult);
void dfsVisit(std::vector<Node>& graph, Node* u, int& time, int& opponentShipHitPoints, int& numberOfVisitedNodes, int& numberOfVisitedNodesResult);

// Prints graph using adjacency list representation
/*
 * 0 -> 1 2
 * 1 -> 0 3
 * ....
 */
void printGraph(std::vector<Node> graph) {
    int gSize = graph.size();
    for (int i = 0; i < gSize; ++i) {
        std::cout << graph[i].number << " -> ";
        int neighborsSize = graph[i].neighbors.size();
        for (int j = 0; j < neighborsSize; ++j) {
            std::cout << graph[i].neighbors[j]->number << ' ';
        }
        std::cout << std::endl;
    }
}
// Prints graph depending on visited or not
/*
 * x - -
 * x - -
 * - - -
 */
void printGraphVisited(std::vector<Node> graph, int B) {
    int gSize = graph.size();
    for (int i = 0; i < gSize; ++i) {
        int gColor = graph[i].color;
        if (gColor == black) {
            std::cout << "x ";
        } else {
            std::cout << "- ";
        }
        if ((i+1) % B == 0) {
            std::cout << std::endl;
        }
    }
}

// Prints ship locations in graph depending on visited or not
/*
 * x - -
 * x - -
 * - - -
 */
void printShips(std::vector<Node> graph) {
    int gSize = graph.size();
    for (int i = 0; i < gSize; ++i) {
        if (graph[i].shipNumber != -1) {
            std::cout << graph[i].number;
            std::cout << std::endl;
        }
    }
}


int main(int argc, char *argv[]) {
    // check input count (./a.out P1 P2)
    if (argc != 3) {
        std::cout << "Missing arguments..." << std::endl;
        exit(EXIT_FAILURE);
    }
    // set timer
    clock_t t = clock();
    // start operations

    // store input file paths
    const std::string p1_setting(argv[1]); // first input file path
    const std::string p2_setting(argv[2]); // second input file path

    // reading files into memory
    std::ifstream inputFileStreamPlayer1;
    std::ifstream inputFileStreamPlayer2;
    // 	open files for reading
    inputFileStreamPlayer1.open(p1_setting, std::ifstream::in);
    inputFileStreamPlayer2.open(p2_setting, std::ifstream::in);

    // check if the file is open, exit with failure else
    if (!(inputFileStreamPlayer1.is_open())) {
        std::cout << "Could not open input file.";
        exit(EXIT_FAILURE);
    }

    // gather setting information per line
    std::string settingInfoLinePlayer1;
    std::string algorithmName;
    int xStart; // x loc start
    int yStart; // y loc start
    int B; // board size
    int N; // no of ships
    std::vector<int> intermediateInfo(4); // storing single ship coordinates
    int intermediateInfoIndex = 0;

    // start reading file
    std::getline(inputFileStreamPlayer1, algorithmName); // get algorithm name, dfs or bfs

    // read xStart, yStart, B, N
    while(intermediateInfoIndex < 4) {
        std::getline(inputFileStreamPlayer1, settingInfoLinePlayer1);
        std::stringstream settingLineInfoStream(settingInfoLinePlayer1);
        std::string settingInfoElement;
        while (std::getline(settingLineInfoStream, settingInfoElement, ' ')) {
            try {
                intermediateInfo[intermediateInfoIndex] = stoi(settingInfoElement);
                intermediateInfoIndex++;
            }
            catch (std::exception err) {
                std::cout << "Could not find integer";
            }
        }
    }
    // store xStart, yStart, B, N
    xStart = intermediateInfo[0];
    yStart = intermediateInfo[1];
    B = intermediateInfo[2]; // board size
    N = intermediateInfo[3]; // number of ships

    // create vector of Nodes, this is our graph
    // We only allocate memory space only for graph nodes here
    // All following operations use pointers for memory efficiency
    // Thus we have constant "number of nodes kept in memory"
    std::vector<Node>* graphPtr = new std::vector<Node>(B * B , Node());
    std::vector<Node> graph = *graphPtr;

    // fill graph with appropriate Nodes with neighbour addresses
    for (int i = 0; i < B; ++i) {
        for (int j = 0; j < B; ++j) {
            // set node number for node array elements
            graph[i * B + j].number = i * B + j;
            // set neigbors for nodes which are on board top, bottom, left, right outmost
            if (i == 0 || j == 0 || i == B - 1 || j == B - 1) {
                // 2 neighbors for corners
                if (i == 0 && j == 0) {
                    // following array elements represent neigbors // top, left, bottom, right
                    graph[i * B + j].neighbors.push_back(&graph[(i + 1) * B + j]);
                    graph[i * B + j].neighbors.push_back(&graph[i * B + j + 1]);
                } else if (i == 0 && j == B - 1) {
                    graph[i * B + j].neighbors.push_back(&graph[i * B + j - 1]);
                    graph[i * B + j].neighbors.push_back(&graph[(i + 1) * B + j]);
                } else if (i == B - 1 && j == 0) {
                    graph[i * B + j].neighbors.push_back(&graph[(i - 1) * B + j]);
                    graph[i * B + j].neighbors.push_back(&graph[i * B + j + 1]);
                } else if (i == B - 1 && j == B - 1) {
                    graph[i * B + j].neighbors.push_back(&graph[(i - 1) * B + j]);
                    graph[i * B + j].neighbors.push_back(&graph[i * B + j - 1]);
                } else if (i == 0) { // 3 neighbors for outmost tiles except corners
                    graph[i * B + j].neighbors.push_back(&graph[i * B + j - 1]);
                    graph[i * B + j].neighbors.push_back(&graph[(i + 1) * B + j]);
                    graph[i * B + j].neighbors.push_back(&graph[i * B + j + 1]);
                } else if (i == B - 1) {
                    graph[i * B + j].neighbors.push_back(&graph[(i - 1) * B + j]);
                    graph[i * B + j].neighbors.push_back(&graph[i * B + j - 1]);
                    graph[i * B + j].neighbors.push_back(&graph[i * B + j + 1]);
                } else if (j == 0) {
                    graph[i * B + j].neighbors.push_back(&graph[(i - 1) * B + j]);
                    graph[i * B + j].neighbors.push_back(&graph[(i + 1) * B + j]);
                    graph[i * B + j].neighbors.push_back(&graph[i * B + j + 1]);
                } else if (j == B - 1) {
                    graph[i * B + j].neighbors.push_back(&graph[(i - 1) * B + j]);
                    graph[i * B + j].neighbors.push_back(&graph[i * B + j - 1]);
                    graph[i * B + j].neighbors.push_back(&graph[(i + 1) * B + j]);
                }
            } else { // 4 neighbors otherwise
                graph[i * B + j].neighbors.push_back(&graph[(i - 1) * B + j]);
                graph[i * B + j].neighbors.push_back(&graph[i * B + j - 1]);
                graph[i * B + j].neighbors.push_back(&graph[(i + 1) * B + j]);
                graph[i * B + j].neighbors.push_back(&graph[i * B + j + 1]);
            }
        }
    }
    // ship counter for player 1
    int shipCounter = 0;
    // ship Hit Points for Player 1 depending on ship sizes
    int shipHitPointsPlayer1 = 0; // represents area that can be hit by opponent, for example 3 ships 3x3 = 9 area
    // store ship coordinates and place ships inside graph
    while(N >= shipCounter && std::getline(inputFileStreamPlayer1, settingInfoLinePlayer1)) {
        intermediateInfoIndex = 0;
        std::stringstream settingLineInfoStream(settingInfoLinePlayer1);
        std::string settingInfoElement;
        // store ship coordinates
        while (std::getline(settingLineInfoStream, settingInfoElement, ' ')) {
            try {
                intermediateInfo[intermediateInfoIndex] = stoi(settingInfoElement);
                intermediateInfoIndex++;
            }
            catch (std::exception err) {
                std::cout << "Could not find integer in place ships inside graph";
            }
        }
        // place a ship inside graph
        int startingX = intermediateInfo[0];
        int startingY = intermediateInfo[1];
        int finishingX = intermediateInfo[2];
        int finishingY = intermediateInfo[3];
        if (startingX == finishingX) {
            for (int i = startingY; i <= finishingY; ++i) {
                graph[B * startingX + i].shipNumber = shipCounter;
            }
            shipHitPointsPlayer1 += finishingY - startingY + 1;
        } else { // startingY == finishingY
            for (int i = startingX; i <= finishingX; ++i) {
                graph[B * i + startingY].shipNumber = shipCounter;
            }
            shipHitPointsPlayer1 += finishingX - startingX + 1;
        }
        shipCounter++;
    }
    // player 1 settings processing finishes

    // player 2 settings start

    // check if the file is open, exit with failure else
    if (!(inputFileStreamPlayer2.is_open())) {
        std::cout << "Could not open input file for player 2.";
        exit(EXIT_FAILURE);
    }
    // gather setting information per line
    std::string settingInfoLinePlayer2;
    std::string algorithmNamePlayer2;
    // x loc start
    int xStartPlayer2;
    // y loc start
    int yStartPlayer2;


    // get algorithm name, dfs or bfs
    std::getline(inputFileStreamPlayer2, algorithmNamePlayer2);

    // read xStart, yStart, B, N
    intermediateInfoIndex = 0;
    while(intermediateInfoIndex < 4) {
        std::getline(inputFileStreamPlayer2, settingInfoLinePlayer2);
        std::stringstream settingLineInfoStream(settingInfoLinePlayer2);
        std::string settingInfoElement;
        while (std::getline(settingLineInfoStream, settingInfoElement, ' ')) {
            try {
                intermediateInfo[intermediateInfoIndex] = stoi(settingInfoElement);
                intermediateInfoIndex++;
            }
            catch (std::exception err) {
                std::cout << "Could not find integer";
            }
        }
    }
    // store xStart, yStart, B, N
    xStartPlayer2 = intermediateInfo[0];
    yStartPlayer2 = intermediateInfo[1];
    B = intermediateInfo[2]; // board size
    N = intermediateInfo[3]; // number of ships

    // create vector of Nodes, this is our graph
    // We only allocate memory space only for graph nodes here
    // All following operations use pointers for memory efficiency
    // Thus we have constant "number of nodes kept in memory"
    std::vector<Node>* graphPtrPlayer2 = new std::vector<Node>(B * B , Node());
    std::vector<Node> graphPlayer2 = *graphPtrPlayer2;

    // fill graph with appropriate Nodes with neighbour addresses
    for (int i = 0; i < B; ++i) {
        for (int j = 0; j < B; ++j) {
            // set node number for node array elements
            graphPlayer2[i * B + j].number = i * B + j;
            // set neigbors for nodes which are on board top, bottom, left, right outmost
            if (i == 0 || j == 0 || i == B - 1 || j == B - 1) {
                // 2 neighbors for corners
                if (i == 0 && j == 0) {
                    // following array elements represent neigbors // top, left, bottom, right
                    graphPlayer2[i * B + j].neighbors.push_back(&graphPlayer2[(i + 1) * B + j]);
                    graphPlayer2[i * B + j].neighbors.push_back(&graphPlayer2[i * B + j + 1]);
                } else if (i == 0 && j == B - 1) {
                    graphPlayer2[i * B + j].neighbors.push_back(&graphPlayer2[i * B + j - 1]);
                    graphPlayer2[i * B + j].neighbors.push_back(&graphPlayer2[(i + 1) * B + j]);
                } else if (i == B - 1 && j == 0) {
                    graphPlayer2[i * B + j].neighbors.push_back(&graphPlayer2[(i - 1) * B + j]);
                    graphPlayer2[i * B + j].neighbors.push_back(&graphPlayer2[i * B + j + 1]);
                } else if (i == B - 1 && j == B - 1) {
                    graphPlayer2[i * B + j].neighbors.push_back(&graphPlayer2[(i - 1) * B + j]);
                    graphPlayer2[i * B + j].neighbors.push_back(&graphPlayer2[i * B + j - 1]);
                } else if (i == 0) {
                    // 3 neighbors for outmost tiles except corners
                    graphPlayer2[i * B + j].neighbors.push_back(&graphPlayer2[i * B + j - 1]);
                    graphPlayer2[i * B + j].neighbors.push_back(&graphPlayer2[(i + 1) * B + j]);
                    graphPlayer2[i * B + j].neighbors.push_back(&graphPlayer2[i * B + j + 1]);
                } else if (i == B - 1) {
                    graphPlayer2[i * B + j].neighbors.push_back(&graphPlayer2[(i - 1) * B + j]);
                    graphPlayer2[i * B + j].neighbors.push_back(&graphPlayer2[i * B + j - 1]);
                    graphPlayer2[i * B + j].neighbors.push_back(&graphPlayer2[i * B + j + 1]);
                } else if (j == 0) {
                    graphPlayer2[i * B + j].neighbors.push_back(&graphPlayer2[(i - 1) * B + j]);
                    graphPlayer2[i * B + j].neighbors.push_back(&graphPlayer2[(i + 1) * B + j]);
                    graphPlayer2[i * B + j].neighbors.push_back(&graphPlayer2[i * B + j + 1]);
                } else if (j == B - 1) {
                    graphPlayer2[i * B + j].neighbors.push_back(&graphPlayer2[(i - 1) * B + j]);
                    graphPlayer2[i * B + j].neighbors.push_back(&graphPlayer2[i * B + j - 1]);
                    graphPlayer2[i * B + j].neighbors.push_back(&graphPlayer2[(i + 1) * B + j]);
                }
            } else { // 4 neighbors otherwise
                graphPlayer2[i * B + j].neighbors.push_back(&graphPlayer2[(i - 1) * B + j]);
                graphPlayer2[i * B + j].neighbors.push_back(&graphPlayer2[i * B + j - 1]);
                graphPlayer2[i * B + j].neighbors.push_back(&graphPlayer2[(i + 1) * B + j]);
                graphPlayer2[i * B + j].neighbors.push_back(&graphPlayer2[i * B + j + 1]);
            }
        }
    }

    // ship counter for player 2
    int shipCounterPlayer2 = 0;
    // ship Hit Points for Player 2 depending on ship sizes
    // represents area that can be hit by opponent, for example 3 ships 3x3 = 9 area
    int shipHitPointsPlayer2 = 0;

    // store ship coordinates and place ships inside graph
    while(N >= shipCounterPlayer2 && std::getline(inputFileStreamPlayer2, settingInfoLinePlayer2)) {
        intermediateInfoIndex = 0;
        std::stringstream settingLineInfoStream(settingInfoLinePlayer2);
        std::string settingInfoElement;
        // store ship coordinates
        while (std::getline(settingLineInfoStream, settingInfoElement, ' ')) {
            try {
                intermediateInfo[intermediateInfoIndex] = stoi(settingInfoElement);
                intermediateInfoIndex++;
            }
            catch (std::exception err) {
                std::cout << "Could not find integer in place ships inside graph";
            }
        }
        // place a ship inside graph
        int startingX = intermediateInfo[0];
        int startingY = intermediateInfo[1];
        int finishingX = intermediateInfo[2];
        int finishingY = intermediateInfo[3];
        if (startingX == finishingX) {
            for (int i = startingY; i <= finishingY; ++i) {
                graphPlayer2[B * startingX + i].shipNumber = shipCounterPlayer2;
            }
            shipHitPointsPlayer2 += finishingY - startingY + 1;
        } else { // startingY == finishingY
            for (int i = startingX; i <= finishingX; ++i) {
                graphPlayer2[B * i + startingY].shipNumber = shipCounterPlayer2;
            }
            shipHitPointsPlayer2 += finishingX - startingX + 1;
        }
        shipCounterPlayer2++;
    }
    // player 2 settings processing finishes

    // detect which algoritm to use
    if (algorithmName.erase(algorithmName.size() - 1) == "BFS" && algorithmNamePlayer2.erase(algorithmNamePlayer2.size() - 1) == "BFS") {
        // print algorithm names
        std::cout << "The algorithm: Player1: " << algorithmName << ", Player2: " << algorithmNamePlayer2 << std::endl;
        // call bfs and store result inside bfsResults
        SearchResult bfsResult = bfs(graph, xStart*B + yStart, graphPlayer2, xStartPlayer2*B + yStartPlayer2, shipHitPointsPlayer1, shipHitPointsPlayer2);
        // detect winner
        std::string winner = bfsResult.winner == 0 ? "Player1" : "Player2";
        // print wanted information
        std::cout << "The number of visited nodes: Player1: " << bfsResult.p1NumberOfVisitedNodes << ", Player2: " << bfsResult.p2NumberOfVisitedNodes << std::endl;
        // print number of nodes kept in the memory
        std::cout << "The number of nodes kept in the memory: Player1: " << B * B << ", Player2: " << B * B << std::endl;
        // print winner
        std::cout << "The result: " << winner << " won!" << std::endl;
    } else {
        int numberOfVisitedNodesP1 = 0;
        int numberOfVisitedNodesP2 = 0;
        int numberOfVisitedNodesResultP1 = 0;
        int numberOfVisitedNodesResultP2 = 0;
        // call dfs and store results inside numberOfVisitedNodesResultPX
        dfs(graphPlayer2, shipHitPointsPlayer2, xStart*B + yStart, numberOfVisitedNodesP1, numberOfVisitedNodesResultP1); // player 1 attacks player 2
        dfs(graph, shipHitPointsPlayer1, xStart*B + yStart, numberOfVisitedNodesP2, numberOfVisitedNodesResultP2); // player 2 attacks player 1
        // print algorithm names
        std::cout << "The algorithm: Player1: " << algorithmName << ", Player2: " << algorithmNamePlayer2 << std::endl;
        // detect winner
        std::string winner = numberOfVisitedNodesResultP1 <= numberOfVisitedNodesResultP2 ? "Player1" : "Player2";
        // print number of visited nodes until win
        std::cout << "The number of visited nodes: Player1: " << numberOfVisitedNodesResultP1 << ", Player2: " << numberOfVisitedNodesResultP2 << std::endl;
        // print number of nodes kept in the memory
        std::cout << "The number of nodes kept in the memory: Player1: " << B * B << ", Player2: " << B * B << std::endl;
        // print winner
        std::cout << "The result: " << winner << " won!" << std::endl;
    }


    // close file streams
    inputFileStreamPlayer1.close();
    inputFileStreamPlayer2.close();

    // free memory allocated using new
    delete graphPtr;
    delete graphPtrPlayer2;

    // finish timing
    t = clock() - t;
    // print time
    const char *msg = "The running time: %fms\n";
    printf(msg, 1000 * ((float) t) / CLOCKS_PER_SEC);

    return 0;
}


// bfs algorithm takes both graphs, their starting node number and ship hit points per player
// simultaneously searches the graphs, note that player 1 win detection check is implemented
// returns as soon as finding a winner
SearchResult bfs(std::vector<Node>& graph1, int s1, std::vector<Node>& graph2, int s2, int shipHitPointsPlayer1, int shipHitPointsPlayer2) {
    SearchResult bfsResult;
    // each node in graph has already initialized with white color, inf distance, null parent

    // set starting node properties as discovered, distance 0 and parent nullptr
    graph1[s1].color = gray;
    graph1[s1].distance = 0;
    graph1[s1].parent = nullptr;
    graph2[s2].color = gray;
    graph2[s2].distance = 0;
    graph2[s2].parent = nullptr;

    std::queue<Node*> q1; // create empty queue
    std::queue<Node*> q2; // create empty queue
    q1.push(&graph1[s1]); // push elements into empty queue
    q2.push(&graph2[s2]); // push elements into empty queue

    // keep discovering until one of the queues are empty
    while (!(q1.empty()) && !(q2.empty())) {
        // represents u = dequeue(q)
        Node* u1 = q1.front();
        q1.pop();
        Node* u2 = q2.front();
        q2.pop();
        // visit all neighbors of u1 and u2
        // since boards and graphs are the same SIZE just use any of them
        for (unsigned int i = 0; i < u1->neighbors.size(); ++i) {
            // get a neighbor
            Node* v1 = u1->neighbors[i];
            Node* v2 = u2->neighbors[i];
            // check neighbor color
            if (v1->color == white) {
                v1->color = gray; // if neighbor not explored, explore
                // set related info
                v1->distance = u1->distance + 1;
                v1->parent = u1;
                // enqueue for further investigation
                q1.push(v1);
            }
            if (v2->color == white) {
                v2->color = gray;// if neighbor not explored, explore
                // set related info
                v2->distance = u2->distance + 1;
                v2->parent = u2;
                // enqueue for further investigation
                q2.push(v2);
            }
        }

        // first check player 1 attack on player 2

        // graph 2 represents board of player 2
        // hits received (BFS node visits) from player 1
        // thus, if shipHitPointsPlayer2 goes to 0 -> player 1 wins
        u2->color = black; // set node as visited
        bfsResult.p1NumberOfVisitedNodes++; // since player 1 is attacker, increase visited nodes number
        if (u2->shipNumber != -1) { // u2 is the node with ship property
            shipHitPointsPlayer2--; // player 2 took hit
            if (shipHitPointsPlayer2 <= 0) { // player lost all of its ships
                bfsResult.winner = player1; // declare winner
                return bfsResult; // return
            }
        }


        // graph 1 represents board of player 1
        // hits received (BFS node visits) from player 2
        // thus, if shipHitPointsPlayer1 goes to 0 -> player 2 wins
        u1->color = black; // set node as visited
//        printGraphVisited(graph1, 2);
        bfsResult.p2NumberOfVisitedNodes++; // since player 2 is attacker, increase visited nodes number
        if (u1->shipNumber != -1) { // u1 is the node with ship property
            shipHitPointsPlayer1--; // player 1 took hit
            if (shipHitPointsPlayer1 <= 0) {// player lost all of its ships
                bfsResult.winner = player2;// declare winner
                return bfsResult; // return
            }
        }
    }
    return bfsResult;
}


// dfs algorithm takes a graph, ship hit points per player, their starting node number,
// time, numberOfVisitedNodes and result params
// searches the node neighbors following depth first approach
void dfsVisit(std::vector<Node>& graph, Node* u, int& time, int& opponentShipHitPoints, int& numberOfVisitedNodes, int& numberOfVisitedNodesResult) {
    time += 1; // increase time by one
    u->distance = time; // set distance for current node
    u->color = gray; // set color

    numberOfVisitedNodes++; // increase visited nodes count
    if (u->shipNumber != -1) { // if node is a ship node
        opponentShipHitPoints--; // player hit the opponent ship
        if (opponentShipHitPoints <= 0) { // check opponent lost all ship hit points
            numberOfVisitedNodesResult = numberOfVisitedNodes; // set result for number Of Visited Nodes
        }
    }

    int neigborsSize = u->neighbors.size(); // find neigbors size
    for (int i = 0; i < neigborsSize; ++i) { // traverse neigbors
        Node* v = u->neighbors[i]; // pick neigbor
        if (v->color == white) { // check if unvisited
            v->parent = u; // set parent
            dfsVisit(graph, v, time, opponentShipHitPoints, numberOfVisitedNodes, numberOfVisitedNodesResult); // visit it
        }
    }
    u->color = black; // set as visited
    time += 1; // increase time
    u->finishTime = time; // set finish time
}

// dfs algorithm takes a graph, ship hit points per player, their starting node number,
// numberOfVisitedNodes and result params
// searches the graphs per player, note that player dfs called and numberOfVisitedNodesResult params are compared
void dfs(std::vector<Node>& graph, int opponentShipHitPoints, int s, int& numberOfVisitedNodes, int& numberOfVisitedNodesResult) {
    int time = 0; // global time among dfs and dfsVisit
    int gLength = graph.size();// graph size
    Node temp(graph[0]); // set starting node
    graph[0] = graph[s];
    graph[s] = temp;
    for (int i = 0; i < gLength; ++i) {
        Node* u = &graph[i];
        if (u->color == white) { // if node is unvisited, visit it
            // visit node
            dfsVisit(graph, u, time, opponentShipHitPoints, numberOfVisitedNodes, numberOfVisitedNodesResult);
            // update time
            time = u->finishTime;
        }
    }
}
