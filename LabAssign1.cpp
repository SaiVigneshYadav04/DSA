#include <bits/stdc++.h>
using namespace std;

struct Item {
    int id;
    string name;
    int qty;
    float price;
};

class Inventory2 {
public:
    Item items[100];
    int n;
    int pq[100][2];
    vector<tuple<int,int,float>> sparse;

    Inventory2(){ n=0; }

    void addItemRecord(int id,string name,int qty,float price){
        items[n++]={id,name,qty,price};
    }

    void removeItemRecord(int id){
        for(int i=0;i<n;i++){
            if(items[i].id==id){
                for(int j=i;j<n-1;j++)items[j]=items[j+1];
                n--;
                break;
            }
        }
    }

    Item* searchByItem(int id){
        for(int i=0;i<n;i++)if(items[i].id==id)return &items[i];
        return NULL;
    }

    Item* searchByItem(string name){
        for(int i=0;i<n;i++)if(items[i].name==name)return &items[i];
        return NULL;
    }

    void managePriceQuantity(){
        for(int col=0;col<2;col++){
            for(int row=0;row<n;row++){
                pq[row][col]=(col==0?items[row].qty:items[row].price);
            }
        }
    }

    void optimizeSparseStorage(){
        sparse.clear();
        for(int i=0;i<n;i++){
            if(items[i].qty<=2){
                sparse.push_back(make_tuple(items[i].id,items[i].qty,items[i].price));
            }
        }
    }
};

int main(){
    cout<<"Vignesh 2401720006\n";

    Inventory2 inv;
    inv.addItemRecord(10,"Bread",10,20);
    inv.addItemRecord(20,"Butter",1,45);
    inv.addItemRecord(30,"Tea",3,35);
    inv.addItemRecord(40,"Salt",2,18);

    Item* f=inv.searchByItem("Butter");
    if(f)cout<<f->id<<"\n";

    inv.removeItemRecord(30);

    inv.managePriceQuantity();
    for(int i=0;i<inv.n;i++){
        cout<<inv.pq[i][0]<<" "<<inv.pq[i][1]<<"\n";
    }

    inv.optimizeSparseStorage();
    for(auto &t:inv.sparse){
        int id,qty; float price;
        tie(id,qty,price)=t;
        cout<<id<<" "<<qty<<" "<<price<<"\n";
    }
}
