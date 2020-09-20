#include <iostream>
#include <vector>
#include <cstring>
#include <list>
#include <string>
#include <queue>
#include <unordered_map>
#include <ostream>

using namespace std;

void BuildAdj(vector<vector<int>>& adj, vector<int> taxi) {
    vector<pair<int, int>> edges;

    for (unsigned int i=0; i<taxi.size()-1; i+=2) {
        edges.push_back({taxi[i], taxi[i+1]});
    }

    for (auto e : edges) {
        adj[e.first].push_back(e.second);
        adj[e.second].push_back(e.first);
    }
}

void BFS(vector<vector<int>>& adj, int  s, int e, vector<int>& par) {
    queue<int> q;
    vector<int> res;
    unordered_map<int, int> visited;

    q.push(s);
    visited[s] = 1;

    while (!q.empty()) {
        int cmt = q.size();
        for (int i=0; i<cmt; i++)  {
            int cur = q.front();
            q.pop();
            for (auto a : adj[cur]) {
                if (visited[a]) continue;
                visited[a] = 1;
                par[a] = cur;
                q.push(a);
            }
        }
    }
}
bool path(vector<int>& par, int v1, int v2) {
    if (par[v2] != -1) {
        path(par, v1, par[v2]);
        cout<<"-"<<v2;
    }
    else {
        if (v2 == v1) {
            cout<<v1;
        }
        else {
            cerr<<"Error: Wrong edge"<<endl;
            exit(0);
            //return false;
        }
    }
    return true;
}
int main() {
    string start;
    int VertexNum = -1;
    vector<int> taxi;
    vector<vector<int>> adj;
    bool flag=true;
    while (getline(cin, start)) {
        if (start[0] == 'V') {
            cout<<start<<endl;
            flag=true;
            taxi.clear();
            adj.clear();
            string max_num = start.substr(2, 25);
            VertexNum = stoi(max_num);
        }
        else if (start[0] == 'E' && VertexNum > 0) {
            cout<<start<<endl;
            char buf[999];
            strcpy(buf, start.c_str());
            char delim[] = "E{<,>}";
            char *token = strtok(buf, delim);
            while (token != NULL) {
                token = (strtok(nullptr, delim));
                if (token == NULL) break;
                int a;
                sscanf(token, "%d", &a);
                taxi.push_back(a);
            }

            if (taxi.size()==0){cerr<<"Error"<<endl;
                continue;}
            for (unsigned int t=0;t<taxi.size();t++){
                if (taxi[t]>=VertexNum){
                    cerr<<"Error: wrong format"<<endl;
                    exit(0);
                    //flag=false;
                    //taxi.clear();
                    //break;
                }
            }
            if (!flag)continue;
            adj = vector<vector<int>>(VertexNum);
            BuildAdj(adj, taxi);
        }
        else if (start[0] == 's') {
            int s = -1;
            int e = -1;
            sscanf(&start[0], "s %d %d", &s, &e);
            if(s>=VertexNum || e>=VertexNum){
                cerr<<"Error: wrong s input"<<endl;
                exit(0);
                //continue;
            }
            vector<int> par(VertexNum, -1);
            BFS(adj, s, e, par);
            if(path(par, s, e)) cout<<endl;
            par.clear();
        }
    }
}
