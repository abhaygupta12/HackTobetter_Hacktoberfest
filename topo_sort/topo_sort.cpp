#include<bits/stdc++.h>
using namespace std;

vector<int> topoBFS(vector<int> adj[],int V)
{
    vector<int> topo;
    vector<int> ind(V+1,0);
    for(int i=0;i<V;i++)
    {
        for(auto it: adj[i]) ind[it]++;
    }
    queue<int> q;
    for(int i=0;i<V;i++)
    {
        if(ind[i] == 0) q.push(i);
    }

    while(!q.empty())
    {
        int node = q.front();
        q.pop();
        topo.push_back(node);
        for(auto i: adj[node]){
            ind[i]--;
            if(ind[i] == 0){
                q.push(i);
            }
        }
    }
    return topo;
}

int main()
{
    // V = vertices of graph, E = edges in graph
    int V,E;
    cin>>V>>E;
    vector<int> adj[V];
    // creating a directed graph 
    for(int i=0;i<E;i++)
    {
        int x,y;
        cin>>x>>y;
        adj[x].push_back(y);   
    }
    
    vector<int> topo_ans = topoBFS(adj,V);
    for(auto i: topo_ans) cout<<i<<" ";
    return 0; 
}