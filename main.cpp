//lab 26 ds races pt 2?
// Run the experiment 15 times
// and output the average run times of all the races.
// You're using a 2-D array to store your data in Lab 25
// make it a 3-D array here. The second cube would hold counter variables
// and just subtotal the variables that are being recorded in the first cube

#include <iostream>
#include <set>
#include <list>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
using namespace std;
using namespace std::chrono;


int main() {
    const int NUMSIM = 15; //number of simulations = 15;

    //turn this 2d array into 3d array?
    int result[4][3] = {0}; // 4 = 4 actions, 3 = 3 data structures
    int results[4][3][NUMSIM] = {0}; // 4 actions 3 data structures 15 simulations

    cout << "Number of simulations: 15\n";
    cout << "Operation\tVector\tList\tSet\n";

    //loop this whole thing 15 times and find average 
    //then cout average times
    for (int simulations = 0; simulations < NUMSIM; simulations++) {
        ifstream fin("codes.txt");
        string line;
        vector<string> vect;
        list<string> lists;
        set<string> sets;

        //reading string elements-------race 1
        while (getline(fin, line)){
            auto readS = high_resolution_clock::now();
            vect.push_back(line);
            auto readE = high_resolution_clock::now();
            results[0][0][simulations] += duration_cast<microseconds>(readE - readS).count();
            //first action and first structure

            readS = high_resolution_clock::now();
            lists.push_back(line);
            readE = high_resolution_clock::now();
            result[0][1] += duration_cast<microseconds>(readE- readS).count();
            //first action second structure

            readS = high_resolution_clock::now();
            sets.insert(line);
            readE = high_resolution_clock::now();
            result[0][2] += duration_cast<microseconds>(readE - readS).count();
            //first action third structure
        }
        cout << "Read\t\t" << result[0][0] << "\t" << result[0][1] << "\t" << result[0][2] << endl; 

        //sorting string elements-------race 2
        //set is sorted by default
        result[1][2] = -1;
        auto sorts = high_resolution_clock::now();
        lists.sort();
        auto sortend = high_resolution_clock::now();
        result[1][1] += duration_cast<microseconds>(sortend - sorts).count();
        //second action second structure

        sorts = high_resolution_clock::now();
        sort(vect.begin(), vect.end());
        sortend = high_resolution_clock::now();
        result[1][0] += duration_cast<microseconds>(sortend - sorts).count();
        //second action first structure
        cout << "Sort\t\t" << result[1][0] << "\t" << result[1][1] << "\t" << result[1][2] << endl;
    
        //inserting "TESTCODE"--------race 3
        auto start = high_resolution_clock::now();
        int vectorindex = vect.size() / 2;
        vect.insert(vect.begin() + vectorindex, "TESTCODE");
        auto end = high_resolution_clock::now();
        result[2][0] += duration_cast<microseconds>(end - start).count();
        //third action first structure

        start = high_resolution_clock::now();
        int listindex = lists.size() / 2;
        auto i = lists.begin(); 
        advance(i, listindex);
        lists.insert(i, "TESTCODE");
        end = high_resolution_clock::now();
        result[2][1] += duration_cast<microseconds>(end - start).count();
        //third action second structure

        start = high_resolution_clock::now();
        sets.insert("TESTCODE");
        end = high_resolution_clock::now();
        result[2][2] += duration_cast<microseconds>(end - start).count();
        //third action third structure
        cout << "Insert\t\t" << result[2][0] << "\t" << result[2][1] << "\t" << result[2][2] << endl;

        //deleting "TESTCODE" ------race 4
        start = high_resolution_clock::now();
        vect.erase(vect.begin() + vect.size() / 2);
        end = high_resolution_clock::now();
        result[3][0] += duration_cast<microseconds>(end - start).count();

        start = high_resolution_clock::now();
        auto j = lists.begin();
        advance(j, listindex);
        lists.erase(j);
        end = high_resolution_clock::now();
        result[3][1] += duration_cast<microseconds>(end - start).count();

        start = high_resolution_clock::now();
        sets.erase("TESTCODE");
        end = high_resolution_clock::now();
        result[3][2] += duration_cast<microseconds>(end - start).count();
        cout << "Delete\t\t" << result[3][0] << "\t" << result[3][1] << "\t" << result[3][2] << endl;
    }

    return 0;
}

/* syntax examples:
auto start = high_resolution_clock::now()
auto end = high_resolution_clock::now()
auto duration = duration_cast<milliseconds>(end - start)
duration.count() references elapsed milliseconds
*/