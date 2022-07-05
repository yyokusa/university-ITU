// Yasin Abdülkadir Yokuş - 150190739 - yokus19@itu.edu.tr

/* Output:
Vertex 30 ---> Color 1
Checking 10 ---> true
Vertex 10 ---> Color 1
Checking 27 ---> false
Checking 17 ---> true
Vertex 17 ---> Color 1
Checking 22 ---> true
Vertex 22 ---> Color 1
Checking 32 ---> false
Checking 7 ---> true
Vertex 7 ---> Color 1
Checking 26 ---> false
Checking 9 ---> false
Checking 18 ---> false
Checking 11 ---> false
Checking 24 ---> true
Vertex 24 ---> Color 1
Checking 23 ---> false
Checking 6 ---> false
Checking 33 ---> false
Checking 16 ---> false
Checking 4 ---> true
Vertex 4 ---> Color 1
Checking 20 ---> false
Checking 19 ---> false
Checking 31 ---> false
Checking 21 ---> false
Checking 15 ---> true
Vertex 15 ---> Color 1
Checking 13 ---> true
Vertex 13 ---> Color 1
Checking 12 ---> false
Checking 25 ---> false
Checking 8 ---> false
Checking 34 ---> false
Checking 2 ---> true
Vertex 2 ---> Color 1
Checking 29 ---> false
Checking 28 ---> true
Vertex 28 ---> Color 1
Checking 1 ---> false
Checking 14 ---> false
Checking 5 ---> false
Checking 3 ---> false
Checking 35 ---> false
Vertices 30,10,17,22,7,24,4,15,13,2,28 are dropped!!

Vertex 27 ---> Color 2
Checking 32 ---> true
Vertex 32 ---> Color 2
Checking 26 ---> false
Checking 9 ---> true
Vertex 9 ---> Color 2
Checking 18 ---> false
Checking 11 ---> true
Vertex 11 ---> Color 2
Checking 23 ---> true
Vertex 23 ---> Color 2
Checking 6 ---> true
Vertex 6 ---> Color 2
Checking 33 ---> false
Checking 16 ---> false
Checking 20 ---> false
Checking 19 ---> false
Checking 31 ---> false
Checking 21 ---> true
Vertex 21 ---> Color 2
Checking 12 ---> false
Checking 25 ---> true
Vertex 25 ---> Color 2
Checking 8 ---> false
Checking 34 ---> true
Vertex 34 ---> Color 2
Checking 29 ---> true
Vertex 29 ---> Color 2
Checking 1 ---> true
Vertex 1 ---> Color 2
Checking 14 ---> true
Vertex 14 ---> Color 2
Checking 5 ---> false
Checking 3 ---> true
Vertex 3 ---> Color 2
Checking 35 ---> false
Vertices 27,32,9,11,23,6,21,25,34,29,1,14,3 are dropped!!

Vertex 26 ---> Color 3
Checking 18 ---> true
Vertex 18 ---> Color 3
Checking 33 ---> true
Vertex 33 ---> Color 3
Checking 16 ---> true
Vertex 16 ---> Color 3
Checking 20 ---> true
Vertex 20 ---> Color 3
Checking 19 ---> false
Checking 31 ---> true
Vertex 31 ---> Color 3
Checking 12 ---> true
Vertex 12 ---> Color 3
Checking 8 ---> true
Vertex 8 ---> Color 3
Checking 5 ---> true
Vertex 5 ---> Color 3
Checking 35 ---> true
Vertex 35 ---> Color 3
Vertices 26,18,33,16,20,31,12,8,5,35 are dropped!!

Vertex 19 ---> Color 4
Vertices 19 are dropped!!

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
enum Colors {RED=1, GREEN, BLUE, YELLOW, PURPLE, CHERRY, ORANGE, BROWN};

// 35 by 35 adjacency matrix representation of a graph
//                          1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35
vector<vector<int> > g2 = {{0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0}, // 18
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0}, // 23
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0}, // 28
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0}, // 29
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0}, // 30
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0}, // 31
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0}, // 32
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0}, // 33
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1}, // 34
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0}};
//                          1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35



// calculate and return degrees
vector<pair<int, int>> calculateDegreesOfVertices(vector<vector<int> > &g2) {
    // index -> vertice number, value -> degree
    vector<pair<int, int>> degrees = {};

    for (size_t i = 0; i < g2.size(); i++)
    {
        int init = 0;
        degrees.push_back(make_pair(i + 1, std::accumulate(g2[i].begin(),g2[i].end(), init)));
    }

    // (vertice number, degree)
    return degrees; // (1, 3) (2, 3) (3, 4) (4, 5) (5, 3) (6, 4) (7, 2)
}

// sort vertices by their descending degree and return pairs
vector<pair<int, int>> degressInDescendingOrder(vector<pair<int, int>> &degrees) {
    sort(degrees.begin(), degrees.end(), 
         [](pair<int, int> a, pair<int, int> b) {return a.second > b.second; });

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
    vector<Colors> colors = {
        BROWN, BROWN, BROWN, BROWN, BROWN, BROWN, BROWN,
        BROWN, BROWN, BROWN, BROWN, BROWN, BROWN, BROWN,
        BROWN, BROWN, BROWN, BROWN, BROWN, BROWN, BROWN,
        BROWN, BROWN, BROWN, BROWN, BROWN, BROWN, BROWN,
        BROWN, BROWN, BROWN, BROWN, BROWN, BROWN, BROWN,
        };
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


