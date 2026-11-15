#include <bits/stdc++.h>
using namespace std;

struct Zone {
    string name;
    Zone* left;
    Zone* right;
    Zone(string n):name(n),left(NULL),right(NULL){}
};

Zone* insertZone(Zone* root,string k){
    if(!root)return new Zone(k);
    if(k<root->name)root->left=insertZone(root->left,k);
    else if(k>root->name)root->right=insertZone(root->right,k);
    return root;
}

class SmartCity2 {
public:
    int n;
    vector<vector<int>> adj;
    Zone* root=NULL;

    SmartCity2(int x){
        n=x;
        adj.assign(n,vector<int>(n,1e9));
        for(int i=0;i<n;i++)adj[i][i]=0;
    }

    void addZone(string z){
        root=insertZone(root,z);
    }

    void addRoad(int u,int v,int w){
        adj[u][v]=w;
    }

    vector<vector<int>> floyd(){
        vector<vector<int>> dist=adj;
        for(int k=0;k<n;k++)
            for(int i=0;i<n;i++)
                for(int j=0;j<n;j++)
                    dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
        return dist;
    }

    int prim(){
        vector<int> key(n,1e9),vis(n,0);
        key[0]=0;
        int cost=0;
        for(int c=0;c<n;c++){
            int u=-1;
            for(int i=0;i<n;i++)
                if(!vis[i]&&(u==-1||key[i]<key[u]))u=i;
            vis[u]=1;
            cost+=key[u];
            for(int v=0;v<n;v++)
                if(adj[u][v]<key[v])key[v]=adj[u][v];
        }
        return cost;
    }
};

int main(){
    cout<<"Vignesh 2401720006\n";
    SmartCity2 sc(5);

    sc.addZone("Residential");
    sc.addZone("Tech");
    sc.addZone("Market");
    sc.addZone("Commercial");
    sc.addZone("Industrial");

    sc.addRoad(0,1,5);
    sc.addRoad(0,2,3);
    sc.addRoad(1,3,8);
    sc.addRoad(2,3,2);
    sc.addRoad(3,4,7);

    auto dist=sc.floyd();
    cout<<dist[0][4]<<"\n";
    cout<<sc.prim()<<"\n";
}
