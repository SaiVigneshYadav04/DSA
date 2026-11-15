#include <bits/stdc++.h>
using namespace std;

class Ticket{
public:
    int id,priority;
    string name,issue;
    Ticket *next;
    Ticket(int a,string b,string c,int p){id=a;name=b;issue=c;priority=p;next=NULL;}
};

class Node{
public:
    int c,e;
    Node *next;
    Node(int a,int b){c=a;e=b;next=NULL;}
};

class SystemB{
public:
    Ticket *start;
    stack<int> st;
    priority_queue<pair<int,int>> pr;
    int cq[20],f,r;
    Node *b1,*b2;

    SystemB(){
        start=NULL;
        f=r=-1;
        b1=b2=NULL;
    }

    void add(int id,string n,string s,int p){
        Ticket *t=new Ticket(id,n,s,p);
        if(!start) start=t;
        else{
            Ticket *c=start;
            while(c->next) c=c->next;
            c->next=t;
        }
        st.push(id);
        cout<<"Added "<<id<<"\n";
    }

    void undo(){
        if(st.empty()) return;
        int x=st.top(); st.pop();
        Ticket *c=start,*p=NULL;
        while(c&&c->id!=x){p=c;c=c->next;}
        if(!p) start=start->next;
        else p->next=c->next;
        cout<<"Undo Removed "<<x<<"\n";
    }

    void processP(){
        Ticket *c=start;
        while(c){
            pr.push({c->priority,c->id});
            c=c->next;
        }
        cout<<"Priority: ";
        while(!pr.empty()){
            cout<<pr.top().second<<" ";
            pr.pop();
        }
        cout<<"\n";
    }

    void en(int x){
        if((r+1)%20==f) return;
        if(f==-1) f=0;
        r=(r+1)%20;
        cq[r]=x;
    }

    void de(){
        if(f==-1) return;
        if(f==r){f=r=-1;return;}
        f=(f+1)%20;
    }

    void rr(){
        Ticket *c=start;
        while(c){
            en(c->id);
            c=c->next;
        }
        cout<<"RR: ";
        while(f!=-1){
            cout<<cq[f]<<" ";
            de();
        }
        cout<<"\n";
    }

    Node* addP(Node *h,int a,int b){
        Node *x=new Node(a,b);
        if(!h) return x;
        Node *t=h;
        while(t->next) t=t->next;
        t->next=x;
        return h;
    }

    void cmp(){
        Node *a=b1,*b=b2;
        while(a&&b){
            if(a->c!=b->c||a->e!=b->e){
                cout<<"Billing Not Same\n";
                return;
            }
            a=a->next; b=b->next;
        }
        if(a||b) cout<<"Billing Not Same\n";
        else cout<<"Billing Same\n";
    }
};

int main(){
    cout<<"Vignesh 2401720006\n";
    SystemB x;
    x.add(10,"X","P1",1);
    x.add(11,"Y","P2",2);
    x.undo();
    x.processP();
    x.rr();
    x.b1=x.addP(x.b1,5,3);
    x.b1=x.addP(x.b1,2,1);
    x.b2=x.addP(x.b2,5,3);
    x.b2=x.addP(x.b2,2,1);
    x.cmp();
    return 0;
}
