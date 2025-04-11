#include <chrono>
#include<iostream>
#include<vector>
#include<fstream>

std::vector <int> inp(const std::string& filename = "input.txt"){
    std::ifstream infile(filename);
    if(!infile)std::cout<<"err";
    int n;
    infile>>n;
    std::vector<int> arr(n);
    for(int i=0;i<n;i++)infile>>arr[i];
    return arr;
}
void insertionSort(int arr[], int n)
{
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int main(void) {
    auto start = std::chrono::system_clock::now();

    std::vector<int> inputs = inp();


    insertionSort(inputs.data(), inputs.end() - inputs.begin());
    auto end = std::chrono::system_clock::now();
    std::cout<<std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms";
    return 0;
}
