#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <string>
using namespace std;

struct Metrics {
    int comparisons = 0;
    int swaps = 0;
};
string PivotName(int pivotMethod) {
    if (pivotMethod == 0) {
        return "Last Element";
    }
    else if (pivotMethod == 1) {
        return "Random Element";
    }
    else if (pivotMethod == 2) {
        return "Median of First, Last, and Middle Elements";
    }
    else {
        return "Median of Three Random Elements";
    }
}
int lomutoPartition(vector<int>& arr, int low, int high, Metrics& metrics) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        metrics.comparisons++;
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
            metrics.swaps++;
        }
    }
    swap(arr[i + 1], arr[high]);
    metrics.swaps++;
    return i + 1;
}

int hoarePartition(vector<int>& arr, int low, int high, Metrics& metrics) {
    int pivot = arr[low];
    int i = low - 1;
    int j = high + 1;
    while (true) {
        do {
            metrics.comparisons++;
            i++;
        } while (arr[i] < pivot);

        do {
            metrics.comparisons++;
            j--;
        } while (arr[j] > pivot);

        if (i >= j) return j;

        swap(arr[i], arr[j]);
        metrics.swaps++;
    }
}

int choosePivot(const vector<int>& arr, int low, int high, int method) {
    if (method == 0) {
        return high; //останній
    }
    else if (method == 1) {
        return low + rand() % (high - low + 1); //рандомний
    }
    else if (method == 2) {
        int mid = low + (high - low) / 2;
        vector<int> vals = { arr[low], arr[mid], arr[high] };
        sort(vals.begin(), vals.end());//теж наче квіксорт))
        if (vals[1] == arr[low]) return low;
        if (vals[1] == arr[mid]) return mid;
        return high;//медіана трьох
    }
    else if (method == 3) {
        vector<int> indices = { low + rand() % (high - low + 1),
                               low + rand() % (high - low + 1),
                               low + rand() % (high - low + 1) };
        vector<int> vals = { arr[indices[0]], arr[indices[1]], arr[indices[2]] };
        sort(vals.begin(), vals.end());
        if (vals[1] == arr[indices[0]]) return indices[0];
        if (vals[1] == arr[indices[1]]) return indices[1];
        return indices[2]; //медіана трьох рандомних
    }
    return high; 
}

void quickSort(vector<int>& arr, int low, int high, Metrics& metrics, int partitionScheme, int pivotMethod) {
    if (low < high) {
        int pivotIdx = choosePivot(arr, low, high, pivotMethod);
        swap(arr[pivotIdx], arr[high]);
        metrics.swaps++;

        int p;
        if (partitionScheme == 0) {
            p = lomutoPartition(arr, low, high, metrics);
            quickSort(arr, low, p - 1, metrics, partitionScheme, pivotMethod);
            quickSort(arr, p + 1, high, metrics, partitionScheme, pivotMethod);
        }
        else {
            p = hoarePartition(arr, low, high, metrics);
            quickSort(arr, low, p, metrics, partitionScheme, pivotMethod);
            quickSort(arr, p + 1, high, metrics, partitionScheme, pivotMethod);
        }
    }
}

void runQuickSort(vector<int> arr, int partitionScheme, int pivotMethod) {
    Metrics metrics;
    auto start = chrono::high_resolution_clock::now();
    quickSort(arr, 0, arr.size() - 1, metrics, partitionScheme, pivotMethod);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << "Partition Scheme: " << (partitionScheme == 0 ? "Lomuto" : "Hoare")
        << ", Pivot Method: " << PivotName(pivotMethod) << endl;
    cout << "Time: " << elapsed.count() << " seconds" << endl;
    cout << "Comparisons: " << metrics.comparisons << endl;
    cout << "Swaps: " << metrics.swaps << endl;
    cout << endl;
}

int main() {
    srand(time(0));
    
    vector<int> arr = { 1, 3, 2, 1, 2, 3, 3, 1, 2, 3, 1, 2, 2, 3, 1, 2, 3, 1, 3, 1, 2, 3, 1, 2, 3, 3, 1, 2, 1, 3, 2, 1 };
    cout << "Array: ";
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " "; 
    }
    cout << endl;
    for (int partitionScheme = 0; partitionScheme <= 1; partitionScheme++) {
        for (int pivotMethod = 0; pivotMethod <= 3; pivotMethod++) {
            runQuickSort(arr, partitionScheme, pivotMethod);
        }
    }

    return 0;
}
