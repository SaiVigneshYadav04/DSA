#include <iostream>
#include <string>
using namespace std;

struct Student {
    int id;
    string name;
    int marks;
    string course;
    bool used;
};

Student hashTable[20];

int hashFunc(int id) {
    return id % 20;
}

void insertStudent(Student s) {
    int h = hashFunc(s.id);
    while (hashTable[h].used) h = (h + 1) % 20;
    hashTable[h] = s;
    hashTable[h].used = true;
}

Student* sequentialSearch(Student arr[], int n, int id) {
    for (int i = 0; i < n; i++)
        if (arr[i].id == id) return &arr[i];
    return nullptr;
}

Student* binarySearch(Student arr[], int n, int id) {
    int l = 0, r = n-1;
    while (l <= r) {
        int m = (l+r)/2;
        if (arr[m].id == id) return &arr[m];
        else if (arr[m].id < id) l = m+1;
        else r = m-1;
    }
    return nullptr;
}

void heapify(Student arr[], int n, int i) {
    int largest = i, l = 2*i+1, r = 2*i+2;
    if (l<n && arr[l].marks > arr[largest].marks) largest = l;
    if (r<n && arr[r].marks > arr[largest].marks) largest = r;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(Student arr[], int n) {
    for (int i = n/2-1; i>=0; i--) heapify(arr,n,i);
    for (int i = n-1; i>=0; i--) {
        swap(arr[0],arr[i]);
        heapify(arr,i,0);
    }
}

int partitionQ(Student arr[], int low, int high) {
    int p = arr[high].marks;
    int i = low-1;
    for (int j=low;j<high;j++)
        if (arr[j].marks <= p) { i++; swap(arr[i],arr[j]); }
    swap(arr[i+1],arr[high]);
    return i+1;
}

void quickSort(Student arr[], int low, int high) {
    if (low < high) {
        int pi = partitionQ(arr,low,high);
        quickSort(arr,low,pi-1);
        quickSort(arr,pi+1,high);
    }
}

int getMax(Student arr[], int n) {
    int mx = arr[0].id;
    for (int i=1;i<n;i++) if (arr[i].id > mx) mx = arr[i].id;
    return mx;
}

void countSort(Student arr[], int n, int exp) {
    Student out[20];
    int count[10] = {0};
    for (int i=0;i<n;i++) count[(arr[i].id/exp)%10]++;
    for (int i=1;i<10;i++) count[i]+=count[i-1];
    for (int i=n-1;i>=0;i--) {
        out[count[(arr[i].id/exp)%10]-1] = arr[i];
        count[(arr[i].id/exp)%10]--;
    }
    for (int i=0;i<n;i++) arr[i]=out[i];
}

void radixSort(Student arr[], int n) {
    int m = getMax(arr,n);
    for (int exp=1;m/exp>0;exp*=10) countSort(arr,n,exp);
}

int main() {
    cout << "Vignesh 2401720006\n";
    Student arr[4] = {
        {3,"A",88,"C",false},
        {1,"B",76,"C",false},
        {5,"C",91,"D",false},
        {2,"D",65,"E",false}
    };
    for (int i=0;i<4;i++) insertStudent(arr[i]);
    Student* s1 = sequentialSearch(arr,4,5);
    if (s1) cout << s1->name << " " << s1->marks << "\n";
    Student* s2 = binarySearch(arr,4,3);
    if (s2) cout << s2->name << " " << s2->marks << "\n";
    heapSort(arr,4);
    cout << arr[0].marks << " ";
    quickSort(arr,0,3);
    cout << arr[0].marks << " ";
    radixSort(arr,4);
    cout << arr[0].id << "\n";
}

