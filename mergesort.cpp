#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

void printArray(const vector<int>& arr, const string& label) {
    cout << label << ": ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

// Merge function for Merge Sort
void merge(vector<int>& arr, int l, int m, int r) {
    vector<int> left(arr.begin() + l, arr.begin() + m + 1);
    vector<int> right(arr.begin() + m + 1, arr.begin() + r + 1);
    int i = 0, j = 0, k = l;
    while (i < left.size() && j < right.size())
        arr[k++] = (left[i] <= right[j]) ? left[i++] : right[j++];
    while (i < left.size()) arr[k++] = left[i++];
    while (j < right.size()) arr[k++] = right[j++];
}

// Sequential Merge Sort
void mergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Parallel Merge Sort
void parallelMergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                cout << "Thread " << omp_get_thread_num() << " processing range: " << l << " to " << m << endl;
                parallelMergeSort(arr, l, m);
            }

            #pragma omp section
            {
                cout << "Thread " << omp_get_thread_num() << " processing range: " << m + 1 << " to " << r << endl;
                parallelMergeSort(arr, m + 1, r);
            }
        }
        merge(arr, l, m, r);
    }
}

int main() {
    int n;
    cout << "Enter the size of the array: ";
    cin >> n;

    vector<int> original(n);
    for (int i = 0; i < n; ++i) {
        cout << "Enter element " << i + 1 << ": ";
        cin >> original[i];
    }

    cout << "\nOriginal array: ";
    for (int num : original)
        cout << num << " ";
    cout << "\n\n";


    // Sequential Merge Sort
    vector<int> mergeArr = original;
    double start_time = omp_get_wtime();
    mergeSort(mergeArr, 0, n - 1);
    double end_time = omp_get_wtime();
    printArray(mergeArr, "Sequential Merge Sorted array");
    cout << "Time taken: " << (end_time - start_time) * 1000 << " milliseconds\n\n";

    // Parallel Merge Sort
    vector<int> parallelMergeArr = original;
    start_time = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        {
            cout << "Starting parallel merge sort..." << endl;
            parallelMergeSort(parallelMergeArr, 0, n - 1);
        }
    }
    end_time = omp_get_wtime();
    printArray(parallelMergeArr, "Parallel Merge Sorted array");
    cout << "Time taken: " << (end_time - start_time) * 1000 << " milliseconds\n";

    return 0;
}