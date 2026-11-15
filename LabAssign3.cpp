#include <bits/stdc++.h>
using namespace std;

class Student{
public:
    int id;
    string name;
    float grade;
    string course;
};

class HashTable{
public:
    int size;
    vector<Student> table;
    vector<bool> used;
    HashTable(int s){
        size=s;
        table.resize(s);
        used.assign(s,false);
    }
    int hashFunc(int id){
        return id%size;
    }
    void insert(Student s){
        int h=hashFunc(s.id);
        int i=0;
        while(true){
            int index=(h+i*i)%size;
            if(!used[index]){
                table[index]=s;
                used[index]=true;
                return;
            }
            i++;
        }
    }
};

vector<Student> A;

int seqSearch(string n){
    for(int i=0;i<A.size();i++) if(A[i].name==n) return i;
    return -1;
}

int binSearch(int id){
    int l=0,r=A.size()-1;
    while(l<=r){
        int m=(l+r)/2;
        if(A[m].id==id) return m;
        if(A[m].id<id) l=m+1;
        else r=m-1;
    }
    return -1;
}

void bubble(){
    for(int i=0;i<A.size();i++)
        for(int j=0;j+1<A.size();j++)
            if(A[j].grade>A[j+1].grade)
                swap(A[j],A[j+1]);
}

void insertion(){
    for(int i=1;i<A.size();i++){
        Student v=A[i];
        int j=i-1;
        while(j>=0 && A[j].grade>v.grade){
            A[j+1]=A[j];
            j--;
        }
        A[j+1]=v;
    }
}

void mergeSort(int l,int r){
    if(l>=r)return;
    int m=(l+r)/2;
    mergeSort(l,m);
    mergeSort(m+1,r);
    vector<Student> t;
    int i=l,j=m+1;
    while(i<=m || j<=r){
        if(j>r || (i<=m && A[i].grade<=A[j].grade)) t.push_back(A[i++]);
        else t.push_back(A[j++]);
    }
    for(int k=0;k<t.size();k++) A[l+k]=t[k];
}

int part(int l,int r){
    float p=A[r].grade;
    int i=l;
    for(int j=l;j<r;j++){
        if(A[j].grade<p){
            swap(A[i],A[j]);
            i++;
        }
    }
    swap(A[i],A[r]);
    return i;
}

void quickS(int l,int r){
    if(l>=r)return;
    int p=part(l,r);
    quickS(l,p-1);
    quickS(p+1,r);
}

void heapify(int n,int i){
    int mx=i;
    int l=2*i+1,r=2*i+2;
    if(l<n && A[l].grade>A[mx].grade) mx=l;
    if(r<n && A[r].grade>A[mx].grade) mx=r;
    if(mx!=i){
        swap(A[i],A[mx]);
        heapify(n,mx);
    }
}

void heapSort(){
    int n=A.size();
    for(int i=n/2-1;i>=0;i--) heapify(n,i);
    for(int i=n-1;i>=0;i--){
        swap(A[0],A[i]);
        heapify(i,0);
    }
}

void print(){
    cout<<"ID   Name   Grade   Course\n";
    for(auto &s:A){
        cout<<s.id<<"   "<<s.name<<"   "<<s.grade<<"   "<<s.course<<"\n";
    }
}

int main(){
    cout<<"Vignesh 2401720006\n";

    HashTable ht(50);

    while(true){
        cout<<"\n--- Student Performance Tracker ---\n";
        cout<<"1 Add Student\n";
        cout<<"2 Search by Name\n";
        cout<<"3 Search by ID\n";
        cout<<"4 Bubble Sort\n";
        cout<<"5 Insertion Sort\n";
        cout<<"6 Merge Sort\n";
        cout<<"7 Quick Sort\n";
        cout<<"8 Heap Sort\n";
        cout<<"9 Display Records\n";
        cout<<"10 Exit\n";
        cout<<"Enter choice (int): ";

        int c;
        cin>>c;

        if(c==1){
            Student s;
            cout<<"Enter StudentID (int): ";
            cin>>s.id;
            cout<<"Enter StudentName (string): ";
            cin>>s.name;
            cout<<"Enter Grade (float): ";
            cin>>s.grade;
            cout<<"Enter Course (string): ";
            cin>>s.course;

            A.push_back(s);
            ht.insert(s);
        }
        else if(c==2){
            string n;
            cout<<"Enter Name (string): ";
            cin>>n;
            int i=seqSearch(n);
            if(i==-1) cout<<"Not Found\n";
            else cout<<"Found: "<<A[i].id<<" "<<A[i].grade<<" "<<A[i].course<<"\n";
        }
        else if(c==3){
            int id;
            cout<<"Enter ID (int): ";
            cin>>id;
            sort(A.begin(),A.end(),[](Student a,Student b){return a.id<b.id;});
            int i=binSearch(id);
            if(i==-1) cout<<"Not Found\n";
            else cout<<"Found: "<<A[i].name<<" "<<A[i].course<<"\n";
        }
        else if(c==4){ bubble(); }
        else if(c==5){ insertion(); }
        else if(c==6){ mergeSort(0,A.size()-1); }
        else if(c==7){ quickS(0,A.size()-1); }
        else if(c==8){ heapSort(); }
        else if(c==9){ print(); }
        else break;
    }
