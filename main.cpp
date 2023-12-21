#include "EA.h"
#include "EA2.h"
#include "Greedy.h"

using namespace std;

int main() {

    if(debug) cerr << "building graph" << endl;
    vector<int> generation = {10, 100, 1000, 10000, 100000};

    Graph graph(20, 15, 10000);
    for(auto gen : generation) {
        
        double greedy_res = 0, my_res = 0, my_res2 = 0;
        int avg = 20;
        
        #pragma omp parallel for
        for(int a = 0; a < avg; a++) {
            int round = 12;
            vector<ll> result(round);
            #pragma omp parallel for
            for(int r = 0; r < round; r++) {
                EA myalgo(graph);
                result[r] = myalgo.one_plus_one(gen);
            }
            my_res += *max_element(result.begin(), result.end());


            int round2 = 12;
            vector<ll> result2(round2);
            #pragma omp parallel for
            for(int r = 0; r < round2; r++) {
                EA2 myalgo2(graph);
                result2[r] = myalgo2.one_plus_one(gen);
            }

            my_res2 += *max_element(result2.begin(), result2.end());


            Greedy greedy(graph);
            greedy_res += greedy.solve();
        }
        cout << gen << " " << (ll)my_res / avg << " " << (ll)my_res2 / avg<< " " << (ll)greedy_res / avg << endl;
    }
}
