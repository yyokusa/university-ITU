// Yasin Abdülkadir Yokuş - 150190739 - yokus19@itu.edu.tr

/* Output:
Vertex 4 ---> Color 1
Checking 6 ---> false
Checking 3 ---> false
Checking 1 ---> false
Checking 5 ---> false
Checking 2 ---> false
Checking 7 ---> currNeighborIndex, colors[currNeighborIndex]: 6 6
currNeighborIndex, colors[currNeighborIndex]: 6 1
true
Vertex 7 ---> Color 1
Vertices 4,7 are dropped!!

Vertex 6 ---> Color 2
Checking 3 ---> false
Checking 1 ---> currNeighborIndex, colors[currNeighborIndex]: 0 6
currNeighborIndex, colors[currNeighborIndex]: 0 2
true
Vertex 1 ---> Color 2
Checking 5 ---> false
Checking 2 ---> false
Vertices 6,1 are dropped!!

Vertex 3 ---> Color 3
Checking 5 ---> currNeighborIndex, colors[currNeighborIndex]: 4 6
currNeighborIndex, colors[currNeighborIndex]: 4 3
true
Vertex 5 ---> Color 3
Checking 2 ---> false
Vertices 3,5 are dropped!!

Vertex 2 ---> Color 4
Vertices 2 are dropped!!

Well done!! All the vertices are colored.
Min color num:4

Time in ms.
*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib> // exit
#include <numeric> // accumulate
#include <set>


using namespace std;

// color 1, color 2, color 3, ... 
enum Colors {RED=1, GREEN, BLUE, YELLOW, PURPLE, CHERRY};

// 7 by 7 adjacency matrix representation of a graph
vector<vector<int> > g2 = {{0, 1, 0, 1, 1, 0, 0},
                            {1, 0, 1, 1, 0, 0, 0},
                            {0, 1, 0, 1, 0, 1, 1},
                            {1, 1, 1, 0, 1, 1, 0},
                            {1, 0, 0, 1, 0, 1, 0},
                            {0, 0, 1, 1, 1, 0, 1},
                            {0, 0, 1, 0, 0, 1, 0}};


// calculate and return degrees
vector<pair<int, int>> calculateDegreesOfVertices(vector<vector<int> > &g2) {
    // index -> vertice number, value -> degree
    vector<pair<int, int>> degrees = {};

    for (size_t i = 0; i < g2.size(); i++)
    {
        int init = 0;
        degrees.push_back(make_pair(i + 1, std::accumulate(g2[i].begin(),g2[i].end(), init)));
    }
    
    // for (size_t i = 0; i < g2.size(); i++)
    // {
    //     cout << '(' << degrees[i].first << ", " << degrees[i].second << ") ";
    // }
    // cout << endl;

    // (vertice number, degree)
    return degrees; // (1, 3) (2, 3) (3, 4) (4, 5) (5, 3) (6, 4) (7, 2)
}

// sort vertices by their descending degree and return pairs
vector<pair<int, int>> degressInDescendingOrder(vector<pair<int, int>> &degrees) {
    sort(degrees.begin(), degrees.end(), 
         [](pair<int, int> a, pair<int, int> b) {return a.second > b.second; });
    
    // for (size_t i = 0; i < g2.size(); i++)
    // {
    //     cout << '(' << degrees[i].first << ", " << degrees[i].second << ") ";
    // }
    // cout << endl;

    // (vertice number, degree)
    return degrees; // (4, 5) (6, 4) (3, 4) (1, 3) (5, 3) (2, 3) (7, 2)
}

// is the vertex with vertexIndex neighbor to any other non-neighbors of the function caller vertex? 
// if yes dont color them as same
bool isAdjacent(vector<int> droppedVertices, int vertexIndex) {
    for (size_t i = 0; i < droppedVertices.size(); i++)
    {
        if (g2[vertexIndex][droppedVertices[i]] == 1) {
            return false;
        }
    }
    return true;
}

int main() {
    // set timer
    clock_t t = clock();
    // start operations
    
    int numberOfVertices = g2.size();
    // step 1
    vector<pair<int, int>> degrees = calculateDegreesOfVertices(g2);
    // step 2
    vector<pair<int, int>> degree_list = degressInDescendingOrder(degrees); // (vertice number, degree)
    // int degreeListSize = degree_list.size();
    // step 3
    vector<Colors> colors = {CHERRY, CHERRY, CHERRY, CHERRY, CHERRY, CHERRY, CHERRY};
    Colors lastUsedColor = RED;
    // Step-4
    // Color the NON-neighbors of selected vertice as the same color then set the selected vertice as explored
    set<int> droppedVertices = {};
    for (size_t i = 0; i < numberOfVertices; i++)
    {
        int currVerticeIndex = degree_list[i].first - 1;
        if (droppedVertices.find(currVerticeIndex) != droppedVertices.end()) { continue; }

        colors[currVerticeIndex] = lastUsedColor;                           // step 3

        cout << "Vertex " << (currVerticeIndex + 1) << " ---> Color " << lastUsedColor << endl;
        
        vector<int> iterationDroppedVertices = {currVerticeIndex};
        droppedVertices.insert(currVerticeIndex);

        for (size_t j = 0; j < numberOfVertices; j++)
        {
            int currNeighborIndex = degree_list[j].first - 1;
            if (droppedVertices.find(currNeighborIndex) == droppedVertices.end()) {

                cout << "Checking " <<  currNeighborIndex + 1 << " ---> ";
                if (g2[currVerticeIndex][currNeighborIndex] == 0 && isAdjacent(iterationDroppedVertices, currNeighborIndex)) {                                   // step 4
                    // colors[currNeighborIndex] = colors[currVerticeIndex];
                    colors[currNeighborIndex] = lastUsedColor;
                    droppedVertices.insert(currNeighborIndex);
                    iterationDroppedVertices.push_back(currNeighborIndex);
                    cout << "true" << endl;
                    cout << "Vertex " << (currNeighborIndex + 1) << " ---> Color " << lastUsedColor << endl;
                    continue;
                }
                cout << "false" << endl;
            }
        }

        // print dropped vertices
        cout << "Vertices ";
        if (iterationDroppedVertices.size() >= 2) {
            size_t k = 0;
            for (k = 0; k <= iterationDroppedVertices.size() - 2; k++)
            {
                cout << iterationDroppedVertices[k] + 1 << ",";
            }
            cout << iterationDroppedVertices[k] + 1;
        } else {
            cout << iterationDroppedVertices[0] + 1 ;
        }
        cout << " are dropped!!" << endl << endl;

        // update last used color
        lastUsedColor = (Colors)((int)lastUsedColor + 1);
    }
    
    cout << "Well done!! All the vertices are colored." << endl;
    cout << "Min color num:" << *max_element(colors.begin(), colors.end()) << endl << endl;
    
    
    // finish timing
    t = clock() - t;
    // print time
    const char *msg = "Time in ms. %f\n";
    printf(msg, 1000 * ((float) t) / CLOCKS_PER_SEC);
    
    
    // cout << "Colors : " << endl;
    // for (size_t i = 0; i < colors.size(); i++)
    // {
    //     cout << colors[i] << ' ';
    // }
    // cout << endl;

    return 0;
}


