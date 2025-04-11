#include <chrono>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

vector<int> inp(const string& fn = "input.txt") {
    ifstream in(fn);
    if (!in) {
        cerr << "Error: Could not open file " << fn << endl;
        return {};
    }
    int n;
    in >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) in >> a[i];
    return a;
}

void insort(int a[], int n) {
    for (int i = 1; i < n; ++i) {
        int k = a[i], j = i - 1;
        while (j >= 0 && a[j] > k) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = k;
    }
}

void merge(int a[], int b, int m, int e) {
    int n1 = m - b + 1, n2 = e - m;
    int l[n1], r[n2];
    for (int i = 0; i < n1; i++) l[i] = a[b + i];
    for (int j = 0; j < n2; j++) r[j] = a[m + 1 + j];
    int i = 0, j = 0, k = b;
    while (i < n1 && j < n2) a[k++] = (l[i] <= r[j]) ? l[i++] : r[j++];
    while (i < n1) a[k++] = l[i++];
    while (j < n2) a[k++] = r[j++];
}

void msort(int a[], int b, int e) {
    if (b < e) {
        int m = b + (e - b) / 2;
        msort(a, b, m);
        msort(a, m + 1, e);
        merge(a, b, m, e);
    }
}

int main(int argc, char* argv[]) {

    vector<int> in = inp(argv[1]);
    if (in.empty()) return 1;  // Exit if input is invalid.
    ofstream out("output"+string(argv[2])+".txt", std::ios::app);
    if (!out) {
        cerr << "Error: Could not open output file." << endl;
        return 1;
    }
    auto st = chrono::system_clock::now();

    msort(in.data(), 0, in.size() - 1);

    auto et = chrono::system_clock::now();

    out <<argv[2]<<" "<< chrono::duration_cast<chrono::milliseconds>(et - st).count() << "ms\n";

    return 0;
}
