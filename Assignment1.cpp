#include <iostream>
#include <map>
#include <string>
using namespace std;

struct WeatherRecord {
    string date;
    string city;
    double temperature;
};

class WeatherStorageSparse {
private:
    int years[3] = {2020, 2021, 2022};
    string cities[3] = {"Delhi", "Mumbai", "Chennai"};

    map<string, double> sparseData;

    string makeKey(int year, string city) {
        return to_string(year) + "_" + city;
    }

public:
    void insertRecord(const WeatherRecord &record) {
        int year = stoi(record.date.substr(6,4));
        sparseData[makeKey(year, record.city)] = record.temperature;
    }

    void deleteRecord(string city, int year) {
        sparseData.erase(makeKey(year, city));
    }

    double retrieve(string city, int year) {
        string key = makeKey(year, city);
        if (sparseData.count(key)) return sparseData[key];
        return -9999;
    }

    void rowMajorAccess() {
        cout << "\nRow-major traversal:\n";
        for (int r = 0; r < 3; r++) {
            for (int c = 0; c < 3; c++) {
                string key = makeKey(years[r], cities[c]);
                if (sparseData.count(key))
                    cout << sparseData[key] << " ";
                else
                    cout << -9999 << " ";
            }
            cout << endl;
        }
    }

    void columnMajorAccess() {
        cout << "\nColumn-major traversal:\n";
        for (int c = 0; c < 3; c++) {
            for (int r = 0; r < 3; r++) {
                string key = makeKey(years[r], cities[c]);
                if (sparseData.count(key))
                    cout << sparseData[key] << " ";
                else
                    cout << -9999 << " ";
            }
            cout << endl;
        }
    }

    void handleSparseData() {
        cout << "\nSparse (missing) data locations:\n";
        for (int r = 0; r < 3; r++)
            for (int c = 0; c < 3; c++) {
                string key = makeKey(years[r], cities[c]);
                if (!sparseData.count(key))
                    cout << "Missing → Year: " << years[r] 
                         << ", City: " << cities[c] << endl;
            }
    }

    void analyzeComplexity() {
        cout << "\n-- Complexity Analysis --\n";
        cout << "Insert: O(log N) because of map\n";
        cout << "Delete: O(log N)\n";
        cout << "Retrieve: O(log N)\n";
        cout << "Traversal: O(R*C)\n";
        cout << "Space Complexity: O(K) where K = stored entries (sparse)\n";
    }
};

int main() {
    cout<<"Vignesh 2401720006\n";
    WeatherStorageSparse ws;

    ws.insertRecord({"01-05-2020", "Delhi", 42.5});
    ws.insertRecord({"12-06-2021", "Mumbai", 33.1});

    cout << "Retrieve Mumbai 2021: " << ws.retrieve("Mumbai", 2021) << endl;

    ws.rowMajorAccess();
    ws.columnMajorAccess();
    ws.handleSparseData();
    ws.analyzeComplexity();

    return 0;
}
