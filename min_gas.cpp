#include <vector>
#include <iostream>
#include <climits>
#include <map>
using namespace std;

struct path {
    int cost;
    int day;
    int stored;
    path(){cost=-1;day=-1;stored=-5;}
    path(int c, int d, int s){cost = c; day = d; stored = s;}
};

path dp[100][100];

int find_min_cost(int day, int gas_stored, int* req, int N, int L, int C, int P){
  
    //dp
    if (dp[day][gas_stored].cost != -1){
        return dp[day][gas_stored].cost;
    }

    int minGas = req[day] - gas_stored;
    
    //base
    if (day == N - 1){
        int last_cost = 0;
        if (minGas < 0)  last_cost = 1000000;
        else if (minGas == 0) last_cost = gas_stored*C;
        else last_cost = P + gas_stored*C;
        dp[day][gas_stored] = path(last_cost, day+1, 0);
        return last_cost;
    }

    if (minGas < 0) minGas = 0;

    //recursive
    int min_cost = INT_MAX;
    for (int order_gas = minGas; order_gas <= (L + req[day]) - gas_stored; order_gas ++){
        int delivery = P;
        if (order_gas == 0) delivery = 0;
        int cost = delivery + gas_stored*C + find_min_cost(day+1, 
                                                           gas_stored + order_gas - req[day],
                                                           req, N, L, C, P);
        if (cost < min_cost){
            min_cost = cost;
            dp[day][gas_stored] = path(min_cost, day+1, gas_stored + order_gas - req[day]);
        }
    }

    return min_cost;
}

int main(){

    int N = 15;
    int sample[N] = {4, 3, 1, 4, 2, 2, 4, 3, 1, 6, 6, 1, 5, 5, 5};
    int C = 4;
    int P = 17;
    int L = 6;
    int answer = find_min_cost(0, 0, sample, N, L, C, P); 
    cout << answer << endl;
    
    int day = 0;
    int stored = 0;
    vector< pair<int, int> > output;
    while (day < N-1 ){
        int old = stored;
        path newPath = dp[day][stored];
        day = newPath.day;
        stored = newPath.stored;
        if (stored - old + sample[day-1] != 0)
            output.push_back(make_pair(day, stored-old+sample[day-1]));
    }
    cout << output.size() << endl;
    for (pair<int, int> p : output)
        cout << p.first << " " << p.second << endl;
    
    return 0;    
}
