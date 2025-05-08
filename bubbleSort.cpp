#include <iostream>
#include <vector>
#include <omp.h>
#include <climits>
using namespace std;

// Print function
void printArray(const vector<int>& arr, const string& msg) {
    cout << msg << ": ";
    for (int val : arr) {
        cout << val << " ";
    }
    cout << "\n";
}

// Sequential Bubble Sort
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Parallel Bubble Sort
void parallelBubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        #pragma omp parallel for
        for (int j = i % 2; j < n - 1; j += 2) {
            int thread_id = omp_get_thread_num();  // Get thread ID
            cout << "Thread " << thread_id << " processing index " 
            << j << " (value: " << arr[j] << ")" << endl;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}




int main() {
    int n;
    cin >> n;
    vector<int> original(n);
    for (int i = 0; i < n; i++) {
        cin >> original[i];
    }



    // Sequential Bubble Sort
    vector<int> bubbleArr = original;
    double start_time = omp_get_wtime();
    bubbleSort(bubbleArr);
    double end_time = omp_get_wtime();
    printArray(bubbleArr, "Sequential Bubble Sorted array");
    cout << "Time taken: " << (end_time - start_time) * 1000 << " milliseconds\n\n";

    // Parallel Bubble Sort
    vector<int> parBubbleArr = original;
    start_time = omp_get_wtime();
    parallelBubbleSort(parBubbleArr);
    end_time = omp_get_wtime();
    printArray(parBubbleArr, "Parallel Bubble Sorted array");
    cout << "Time taken: " << (end_time - start_time) * 1000 << " milliseconds\n\n";

    return 0;
}
