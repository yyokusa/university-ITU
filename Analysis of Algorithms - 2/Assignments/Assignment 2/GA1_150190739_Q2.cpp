// Yasin Abdülkadir Yokuş - 150190739 - yokus19@itu.edu.tr

/* Wanted and achieved output:
Vertex 1 ---> Color 1
Vertex 2 ---> Color 2
Vertex 3 ---> Color 1
Vertex 4 ---> Color 3
Vertex 5 ---> Color 2
Vertex 6 ---> Color 4
Vertex 7 ---> Color 2

Number of different colors: 4
Time in ms.
*/


#include <iostream>
#include <vector>
#include <algorithm>

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


int main() {
    // set timer
    clock_t t = clock();
    // start operations

    // 7 nodes 7 colors
    vector<Colors> colors = {RED, CHERRY, CHERRY, CHERRY, CHERRY, CHERRY, CHERRY};

    
    for (size_t i = 1; i < g2.size(); i++)
    {
        vector<int> neighbor_colors = {};
        for (size_t j = 0; j < g2[0].size(); j++)
        {
            if (g2[i][j] == 1){
                // append neighbor colors
                neighbor_colors.push_back(colors[j]);
            }
        }
        
        // sort neighbor colors
        sort (neighbor_colors.begin(), neighbor_colors.end());
        bool colorSet = false;

        // // ***************************************************
        // for (auto &i : neighbor_colors)
        // {
        //     cout << i << ' ';
        // }
        // cout << endl;
        // // print results
        // for (size_t i = 0; i < g2.size(); i++)
        // {
        //     cout << colors[i] << ' ';
        // }
        // cout << endl;
        // // ***************************************************

        // check if a color exist before min, if exists then we are done
        if (neighbor_colors[0] != 1) {
            colors[i] = RED;
            colorSet = true;
            continue;                   // continue from outer loop
        }

        // check if empty color exist btw min and max
        for (size_t j = 0; j < neighbor_colors.size() - 1; j++)
        {
            if (neighbor_colors[j] + 1 < neighbor_colors[j + 1]) {
                colors[i] = (Colors)(neighbor_colors[j] + 1);
                colorSet = true;
                break;
            }
        }
        
        // if all above failed set max + 1 as new color value
        if (!colorSet) {
            colors[i] = (Colors)(neighbor_colors[neighbor_colors.size() - 1] + 1);
        }

    }
    
    // print results
    for (size_t i = 0; i < g2.size(); i++)
    {
        cout << "Vertex " << (i + 1) << " ---> " << "Color " << colors[i] << endl;
    }
    cout << endl;
    cout << "Number of different colors: " << *max_element(colors.begin(), colors.end()) << endl;
    
    // finish timing
    t = clock() - t;
    // print time
    const char *msg = "Time in ms. %f\n";
    printf(msg, 1000 * ((float) t) / CLOCKS_PER_SEC);
    
    return 0;
}


