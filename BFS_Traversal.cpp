#include<bits/stdc++.h>
using namespace std;
#define pb push_back

void BFS(int size, vector<int> adj[],vector<int> &bfs)
{
    vector<bool> vis(size, false);
    // you can change to value of i if '0' as an vertex is not included
    for (int i = 0; i < size; ++i) {
        if (!vis[i]) {
            queue<int> qu;
            vis[i] = true;
            qu.push(i);
            while (!qu.empty()) {
                int a = qu.front();
                qu.pop();
                bfs.pb(a);
                for (auto it : adj[a]) {
                    if (!vis[it]) {
                        vis[it] = true;
                        qu.push(it);
                    }
                }
            }
        }
    }
}

int main()
{
    int size;cin>>size;
    vector<int> bfs;
    int no_of_edges;cin>>no_of_edges;
    vector<int> adj[size+1];
    for(int i=0;i<no_of_edges;i++){
        int x,y;cin>>x>>y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    BFS(size, adj, bfs);
    for(auto it:bfs){
        cout<<it<<" ";
    }
    cout<<endl;
}