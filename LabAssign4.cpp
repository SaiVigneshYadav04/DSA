#include <bits/stdc++.h>
using namespace std;

struct Building{
    int id;
    string name;
    string location;
};

struct Node{
    Building b;
    Node *left,*right;
    int height;
    Node(Building x){ b=x; left=right=nullptr; height=1; }
};

class CampusPlanner{
    vector<Node*> bst_nodes;
    Node* avl_root=nullptr;
    vector<Building> buildings;
    int V;
public:
    vector<vector<pair<int,int>>> adjList;
    vector<pair<int,int>> edges;

    CampusPlanner(int n){ V=n; adjList.resize(n); }

    Node* insertBST(Node* root, Building b){
        if(!root) return new Node(b);
        if(b.id<root->b.id) root->left=insertBST(root->left,b);
        else root->right=insertBST(root->right,b);
        return root;
    }

    int height(Node* n){ return n? n->height:0; }
    int balance(Node* n){
        int lh=n->left?height(n->left):0;
        int rh=n->right?height(n->right):0;
        return lh-rh;
    }
    Node* rotateLeft(Node* x){
        Node* y=x->right; Node* T=y->left;
        y->left=x; x->right=T;
        x->height=max(height(x->left),height(x->right))+1;
        y->height=max(height(y->left),height(y->right))+1;
        return y;
    }
    Node* rotateRight(Node* y){
        Node* x=y->left; Node* T=x->right;
        x->right=y; y->left=T;
        y->height=max(height(y->left),height(y->right))+1;
        x->height=max(height(x->left),height(x->right))+1;
        return x;
    }
    Node* insertAVL(Node* node, Building b){
        if(!node) return new Node(b);
        if(b.id<node->b.id) node->left=insertAVL(node->left,b);
        else node->right=insertAVL(node->right,b);
        node->height=1+max(height(node->left),height(node->right));
        int bf=balance(node);
        if(bf>1 && b.id<node->left->b.id) return rotateRight(node);
        if(bf<-1 && b.id>node->right->b.id) return rotateLeft(node);
        if(bf>1 && b.id>node->left->b.id){ node->left=rotateLeft(node->left); return rotateRight(node);}
        if(bf<-1 && b.id<node->right->b.id){ node->right=rotateRight(node->right); return rotateLeft(node);}
        return node;
    }

    void inorder(Node* root){ if(!root) return; inorder(root->left); cout<<root->b.id<<" "<<root->b.name<<" "<<root->b.location<<"\n"; inorder(root->right);}
    void preorder(Node* root){ if(!root) return; cout<<root->b.id<<" "<<root->b.name<<" "<<root->b.location<<"\n"; preorder(root->left); preorder(root->right);}
    void postorder(Node* root){ if(!root) return; postorder(root->left); postorder(root->right); cout<<root->b.id<<" "<<root->b.name<<" "<<root->b.location<<"\n";}

    void addBuilding(){
        Building b;
        cout<<"Enter BuildingID (int): "; cin>>b.id;
        cout<<"Enter BuildingName (string): "; cin>>b.name;
        cout<<"Enter LocationDetails (string): "; cin>>b.location;
        buildings.push_back(b);
        if(bst_nodes.empty()) bst_nodes.push_back(insertBST(nullptr,b));
        else bst_nodes[0]=insertBST(bst_nodes[0],b);
        avl_root=insertAVL(avl_root,b);
    }

    void treeTraversals(){
        cout<<"BST Inorder:\n"; inorder(bst_nodes[0]);
        cout<<"BST Preorder:\n"; preorder(bst_nodes[0]);
        cout<<"BST Postorder:\n"; postorder(bst_nodes[0]);
        cout<<"AVL Inorder:\n"; inorder(avl_root);
        cout<<"AVL Preorder:\n"; preorder(avl_root);
        cout<<"AVL Postorder:\n"; postorder(avl_root);
    }

    void addEdge(){
        int u,v,w; 
        cout<<"Enter edge from building index (int 0-based): "; cin>>u;
        cout<<"Enter edge to building index (int 0-based): "; cin>>v;
        cout<<"Enter weight (int): "; cin>>w;
        adjList[u].push_back({v,w});
        adjList[v].push_back({u,w});
        edges.push_back({u,v});
        edges.push_back({v,u});
    }

    void dijkstra(int src){
        vector<int> dist(V,INT_MAX); dist[src]=0;
        set<pair<int,int>> s; s.insert({0,src});
        while(!s.empty()){
            auto it=*s.begin(); s.erase(s.begin());
            int u=it.second;
            for(auto p:adjList[u]){
                int v=p.first,w=p.second;
                if(dist[v]>dist[u]+w){
                    s.erase({dist[v],v});
                    dist[v]=dist[u]+w;
                    s.insert({dist[v],v});
                }
            }
        }
        for(int i=0;i<V;i++) cout<<"Distance from "<<src<<" to "<<i<<" = "<<dist[i]<<"\n";
    }

    void kruskal(){
        vector<tuple<int,int,int>> edgeList;
        for(int i=0;i<V;i++)
            for(auto p:adjList[i]) if(i<p.first) edgeList.push_back({p.second,i,p.first});
        sort(edgeList.begin(),edgeList.end());
        vector<int> parent(V),rank(V,0);
        for(int i=0;i<V;i++) parent[i]=i;
        function<int(int)> find=[&](int x){ return parent[x]==x?x:(parent[x]=find(parent[x]));};
        auto unite=[&](int x,int y){
            int xr=find(x),yr=find(y);
            if(rank[xr]<rank[yr]) parent[xr]=yr;
            else if(rank[xr]>rank[yr]) parent[yr]=xr;
            else { parent[yr]=xr; rank[xr]++; }
        };
        cout<<"Kruskal MST edges:\n";
        for(auto t:edgeList){
            int w,u,v; tie(w,u,v)=t;
            if(find(u)!=find(v)){ cout<<u<<"-"<<v<<" w="<<w<<"\n"; unite(u,v);}
        }
    }

    void expressionTree(){
        string expr; 
        cout<<"Enter arithmetic expression in postfix (space separated): ";
        cin.ignore(); getline(cin,expr);
        stack<Node*> st;
        struct Node{ string val; Node* l; Node* r; Node(string v){val=v;l=r=nullptr;}};
        stringstream ss(expr); string tok;
        stack<Node*> s;
        while(ss>>tok){
            if(tok=="+"||tok=="-"||tok=="*"||tok=="/"){
                Node* r=s.top(); s.pop();
                Node* l=s.top(); s.pop();
                Node* n=new Node(tok); n->l=l; n->r=r; s.push(n);
            } else s.push(new Node(tok));
        }
        function<int(Node*)> eval=[&](Node* root){
            if(!root->l && !root->r) return stoi(root->val);
            int l=eval(root->l), r=eval(root->r);
            if(root->val=="+") return l+r;
            if(root->val=="-") return l-r;
            if(root->val=="*") return l*r;
            if(root->val=="/") return l/r;
            return 0;
        };
        cout<<"Evaluated value: "<<eval(s.top())<<"\n";
    }
};

int main(){
    cout<<"Vignesh 2401720006\n";
    int n; cout<<"Enter number of buildings (int): "; cin>>n;
    CampusPlanner cp(n);
    while(true){
        cout<<"\n--- Campus Planner ---\n";
        cout<<"1 Add Building\n2 Tree Traversals\n3 Add Graph Edge\n4 Dijkstra\n5 Kruskal\n6 Expression Tree\n7 Exit\nEnter choice (int): ";
        int ch; cin>>ch;
        if(ch==1) cp.addBuilding();
        else if(ch==2) cp.treeTraversals();
        else if(ch==3) cp.addEdge();
        else if(ch==4){ int src; cout<<"Enter source building index (int): "; cin>>src; cp.dijkstra(src);}
        else if(ch==5) cp.kruskal();
        else if(ch==6) cp.expressionTree();
        else break;
    }
}
