#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib> 
#include <cmath>
//#include "function.h"
using namespace std;


int LomutoHigh(vector<int>& vec, int low, int high) {

    int pivot = vec[high];


    int i = (low - 1);

    for (int j = low; j < high; j++) {


        if (vec[j] <= pivot) {
            i++;
            swap(vec[i], vec[j]);
        }
    }

    swap(vec[i + 1], vec[high]);

    return (i + 1);
}
int HoareHigh(vector<int>& vec, int low, int high) {
    int pivot = vec[high];
    int i = low - 1;
    int j = high + 1;

    while (true) {
        do {
            i++;
        } while (i <= high && vec[i] < pivot);
        do {
            j--;
        } while (j >= low && vec[j] > pivot);
        if (i >= j)
            return j;
        swap(vec[i], vec[j]);
    }
}
void quickSortGH(vector<int>& vec, int low, int high) {


    if (low < high) {

        if (low < 0)
            return;
        int pi = HoareHigh(vec, low, high);


        quickSortGH(vec, low, pi);
        quickSortGH(vec, pi + 1, high);
    }
}
void quickSortLH(vector<int>& vec, int low, int high) {


    if (low < high) {
       
        int pi = LomutoHigh(vec, low, high);


        quickSortLH(vec, low, pi - 1);
        quickSortLH(vec, pi + 1, high);
    }
}

// останній

int randomPivot(vector<int>& vec, int low, int high) {
    int randomIndex = low + rand() % (high - low + 1);
    swap(vec[randomIndex], vec[high]);
    return high;
}
int LomutoRand(vector<int>& vec, int low, int high) {

    randomPivot(vec, low, high);
    int pivot = vec[high];

    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {


        if (vec[j] <= pivot) {
            i++;
            swap(vec[i], vec[j]);
        }
    }

    swap(vec[i + 1], vec[high]);

    return (i + 1);
}
int HoareRand(vector<int>& vec, int low, int high) {
    randomPivot(vec, low, high);
    int pivot = vec[high];
    int i = low - 1;
    int j = high + 1;

    while (true) {
        do {
            i++;
        } while (i <= high  && vec[i] < pivot);
        do {
            j--;
        } while (j >= low && vec[j] > pivot);
        if (i >= j)
            return j;
        swap(vec[i], vec[j]);
    }
}

void quickSortLRand(vector<int>& vec, int low, int high) {


    if (low < high) {


        int pi = LomutoHigh(vec, low, high);


        quickSortLH(vec, low, pi - 1);
        quickSortLH(vec, pi + 1, high);
    }
}
void quickSortGRand(vector<int>& vec, int low, int high) {


    if (low < high) {

        if (low < 0)
            return;
        int pi = HoareHigh(vec, low, high);



        quickSortGH(vec, low, pi);
        quickSortGH(vec, pi + 1, high);
    }
}

//рандомний

int medPivot(int a, int b, int c) {
    if ((a > b) == (a < c)) return a;
    else if ((b > a) == (b < c)) return b;
    else return c;
}
int HoareMed(vector<int>& vec, int low, int high) {
    int mid = low + (high - low) / 2;
    int pivot = medPivot(vec[low], vec[high], vec[mid]);
    int i = low - 1;
    int j = high + 1;

    while (true) {
        do {
            i++;
        } while (vec[i] < pivot && i <= high - 1);
        do {
            j--;
        } while (vec[j] > pivot && j >= low);
        if (i >= j)
            return j;
        swap(vec[i], vec[j]);
    }
}
int LomutoMed(vector<int>& vec, int low, int high) {

    int mid = low + (high - low) / 2;
    int pivot = medPivot(vec[low], vec[high], vec[mid]);
    if (vec[low] == pivot) {
        swap(vec[low], vec[high]);
    }
    else if (vec[low + (high - low) / 2] == pivot) {
        swap(vec[low + (high - low) / 2], vec[high]);
    }
    int i = (low - 1);

    for (int j = low; j < high; j++) {

    
            if (vec[j] <= pivot) {
                i++;
                swap(vec[i], vec[j]);
            }

        
    }

    swap(vec[i + 1], vec[high]);

    return (i + 1);
}



void quickSortHMed(vector<int>& vec, int low, int high) {


    if (low < high) {


        int pi = HoareMed(vec, low, high);


        quickSortHMed(vec, low, pi);
        quickSortHMed(vec, pi + 1, high);
    }
}
void quickSortLMed(vector<int>& vec, int low, int high) {


    if (low < high) {


        int pi = LomutoMed(vec, low, high);


        quickSortLMed(vec, low, pi-1);
        quickSortLMed(vec, pi + 1, high);
    }
}
//медіана трьох

int randomMedPivot(vector<int>& vec) {
    int n = vec.size();
    int i1 = rand() % n;
    int i2 = rand() % n;
    int i3 = rand() % n; 

    return medPivot(vec[i1], vec[i2], vec[i3]);
}
int HoareMedRand(vector<int>& vec, int low, int high) {
    int pivot = randomMedPivot(vec);
    int i = low - 1;
    int j = high + 1;

    while (true) {
        do {
            i++;
        } while (vec[i] < pivot && i <= high - 1);
        do {
            j--;
        } while (vec[j] > pivot && j >= low);
        if (i >= j)
            return j;
        swap(vec[i], vec[j]);
    }
}
int LomutoMedRand(vector<int>& vec, int low, int high) {
    int pivot = randomMedPivot(vec);
    int i = low - 1;

    for (int j = low; j <= high; j++) {
        if (vec[j] < pivot) {
            i++;
            swap(vec[i], vec[j]);
        }
    }

    for (int k = low; k <= high; k++) {
        if (vec[k] == pivot) return k;
    }
    return i + 1;
}
void quickSortHMedRand(vector<int>& vec, int low, int high) {


    if (low < high) {


        int pi = HoareMedRand(vec, low, high);


        quickSortHMedRand(vec, low, pi);
        quickSortHMedRand(vec, pi + 1, high);
    }
}
void quickSortLMedRand(vector<int>& vec, int low, int high) {


    if (low < high) {


        int pi = LomutoMedRand(vec, low, high);


        quickSortLMedRand(vec, low, pi - 1);
        quickSortLMedRand(vec, pi + 1, high);
    }
}

int main() {
   
    vector<int> Arr = {5,67,8,1232,7,1 };
    int n = Arr.size();
    for (int i : Arr) { cout << i; }
    cout << endl; 
    vector<int> clone1 = Arr;
    vector<int> clone2 = Arr;
    vector<int> clone3 = Arr;
    vector<int> clone4 = Arr;
    vector<int> clone5 = Arr;
    vector<int> clone6=  Arr;
    vector<int> clone7=  Arr;
    vector<int> clone8=  Arr;
     

    quickSortGH(clone1, 0, n - 1);
    quickSortLH(clone2, 0, n - 1);
    quickSortGRand(clone3, 0, n - 1);
    quickSortLRand(clone4, 0, n - 1);
    quickSortHMed(clone5, 0, n - 1);
    quickSortLMed(clone6, 0, n - 1);
    quickSortHMedRand(clone7, 0, n - 1);
    quickSortLMedRand(clone8, 0, n - 1);

    cout << "HoareHigh" << endl;
    for (int i : clone1) {
        cout << i << " ";
    }

    cout << "\n LomutoHigh" << endl;
    for (int i : clone2) {
        cout << i << " ";
    }
    cout << "\n HoareRand" << endl;
    for (int i : clone3) {
        cout << i << " ";
    }
    cout << "\n LomutoRand" << endl;
    for (int i : clone4) {
        cout << i << " ";
    }
    cout << "\n HoareMed" << endl;
    for (int i : clone5) {
        cout << i << " ";
    }
    cout << "\n LomutoMed" << endl;
    for (int i : clone6) {
        cout << i << " ";
    }
    cout << "\n HoareMedRand" << endl;
    for (int i : clone7) {
        cout << i << " ";
    }
    cout << "\n LomutoMedRand" << endl;
    for (int i : clone8) {
        cout << i << " ";
    }
  
    return 0;
}



