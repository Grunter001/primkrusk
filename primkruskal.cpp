#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v;
    double weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

vector<int> parentSet;
vector<int> rankSet;

void makeSet(int n){
    parentSet.resize(n);
    rankSet.assign(n, 0);
    for(int i = 0; i < n; i++) parentSet[i] = i;
}

int findSet(int i){
    if(parentSet[i] == i) return i;
    return parentSet[i] = findSet(parentSet[i]);
}

void unionSet(int i, int j){
    int rootI = findSet(i);
    int rootJ = findSet(j);
    if(rootI != rootJ){
        if(rankSet[rootI] < rankSet[rootJ]){
            parentSet[rootI] = rootJ;
        }else if(rankSet[rootI] > rankSet[rootJ]){
            parentSet[rootJ] = rootI;
        }else{
            parentSet[rootJ] = rootI;
            rankSet[rootI]++;
        }
    }
}

double dist(double x1, double y1, double x2, double y2){
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

double kruskal(const vector<double>& X, const vector<double>& Y){
    int n = X.size();
    vector<Edge> edges;
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            edges.push_back({i, j, dist(X[i], Y[i], X[j], Y[j])});
        }
    }
    sort(edges.begin(), edges.end());
    makeSet(n);
    
    double minCost = 0.0;
    for(const auto& edge : edges){
        if(findSet(edge.u) != findSet(edge.v)){
            minCost += edge.weight;
            unionSet(edge.u, edge.v);
        }
    }
    return minCost;
}

double prim(const vector<double>& X, const vector<double>& Y){
    int n = X.size();
    if(n == 0) return 0.0;
    
    vector<double> minEdge(n, 1e9);
    vector<bool> inMST(n, false);
    minEdge[0] = 0.0;
    double minCost = 0.0;
    
    for(int i = 0; i < n; i++){
        int u = -1;
        for(int j = 0; j < n; j++){
            if(!inMST[j] && (u == -1 || minEdge[j] < minEdge[u])){
                u = j;
            }
        }
        
        inMST[u] = true;
        minCost += minEdge[u];
        
        for(int v = 0; v < n; v++){
            if(!inMST[v]){
                double d = dist(X[u], Y[u], X[v], Y[v]);
                if(d < minEdge[v]){
                    minEdge[v] = d;
                }
            }
        }
    }
    return minCost;
}

int main(){
    int cases;
    if(cin >> cases){
        bool first = true;
        while(cases--){
            int n;
            cin >> n;
            vector<double> X(n), Y(n);
            for(int i = 0; i < n; i++){
                cin >> X[i] >> Y[i];
            }
            
            if(!first) cout << "\n";
            first = false;
            
            cout << fixed << setprecision(2) << kruskal(X, Y) << "\n";
            // Para Prim: cout << fixed << setprecision(2) << prim(X, Y) << "\n";
        }
    }
    return 0;
}