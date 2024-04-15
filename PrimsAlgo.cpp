#include<bits/stdc++.h>
using namespace std;

int spanningTree(int V,vector<vector<int>>adj[]){
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
    vector<int>vis(V,0);
    pq.push({0,0});
    int sum=1;
    while(!pq.empty()){
        auto it=pq.top();
        pq.pop();
        int node=it.second;
        int weight=it.first;
        if(vis[node]==1)continue;
        vis[node]=1;
        sum+=weight;
    }
}
int main(){
    
}
