#include <iostream>
#include <cstring>
using namespace std;

struct Patient {
    int id;
    char name[30];
    char date[15];
    char treatment[50];
    Patient* next;
};

Patient* head = nullptr;

void insertPatient(int id, const char name[], const char date[], const char treat[]) {
    Patient* p = new Patient{id, "", "", "", nullptr};
    strcpy(p->name, name);
    strcpy(p->date, date);
    strcpy(p->treatment, treat);

    p->next = head;
    head = p;
}

Patient* retrievePatient(int id) {
    Patient* c = head;
    while (c) {
        if (c->id == id) return c;
        c = c->next;
    }
    return nullptr;
}

char undoStack[20][50];
int top = -1;

void pushUndo(const char msg[]) {
    strcpy(undoStack[++top], msg);
}

void undoAdmission() {
    if (top >= 0)
        cout << "Undo: " << undoStack[top--] << endl;
}

struct PQ {
    int arr[20];
    int pri[20];
    int size = 0;
} pq;

void enqueuePQ(int id, int pr) {
    int i = pq.size++;
    pq.arr[i] = id;
    pq.pri[i] = pr;
}

int dequeuePQ() {
    int maxIdx = 0;
    for (int i = 1; i < pq.size; i++)
        if (pq.pri[i] > pq.pri[maxIdx])
            maxIdx = i;

    int val = pq.arr[maxIdx];

    for (int i = maxIdx; i < pq.size - 1; i++) {
        pq.arr[i] = pq.arr[i+1];
        pq.pri[i] = pq.pri[i+1];
    }
    pq.size--;
    return val;
}

struct Poly {
    int coeff;
    int power;
    Poly* next;
};

Poly* addTerm(Poly* p, int c, int pw) {
    Poly* n = new Poly{c, pw, nullptr};
    n->next = p;
    return n;
}

int evaluatePoly(Poly* p, int x) {
    int sum = 0;
    while (p) {
        int term = p->coeff;
        for (int i = 0; i < p->power; i++) term *= x;
        sum += term;
        p = p->next;
    }
    return sum;
}

int stack2[20];
int top2 = -1;

void push2(int x) { stack2[++top2] = x; }
int pop2() { return stack2[top2--]; }

int evalPostfix(const char exp[]) {
    for (int i = 0; exp[i]; i++) {
        char c = exp[i];
        if (isdigit(c)) push2(c - '0');
        else {
            int b = pop2();
            int a = pop2();
            switch (c) {
                case '+': push2(a + b); break;
                case '-': push2(a - b); break;
                case '*': push2(a * b); break;
            }
        }
    }
    return pop2();
}

int main() {
    cout<<"Vignesh 2401720006\n";
    insertPatient(1, "Vignesh", "01/01/2024", "Scan");
    pushUndo("Inserted Patient 1");

    insertPatient(2, "Itachi", "02/01/2024", "X-Ray");
    pushUndo("Inserted Patient 2");

    undoAdmission();

    enqueuePQ(101, 2);
    enqueuePQ(102, 5);
    cout << "Emergency treated: " << dequeuePQ() << endl;

    Poly* bill = nullptr;
    bill = addTerm(bill, 500, 1); // 500x
    bill = addTerm(bill, 200, 0); // +200

    cout << "Billing total: " << evaluatePoly(bill, 3) << endl;

    cout << "Inventory value: " << evalPostfix("23*54*+") << endl;

    return 0;
}
