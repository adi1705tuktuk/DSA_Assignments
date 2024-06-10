#include <iostream>
#include <vector>

using namespace std;

// Recursive Merge Sort
void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> left(n1);
    vector<int> right(n2);

    for (int i = 0; i < n1; i++)
        left[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        right[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void mergeSortRecursive(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortRecursive(arr, l, m);
        mergeSortRecursive(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Iterative Merge Sort
void mergeSortIterative(vector<int>& arr) {
    int n = arr.size();
    for (int curr_size = 1; curr_size <= n - 1; curr_size *= 2) {
        for (int left_start = 0; left_start < n - 1; left_start += 2 * curr_size) {
            int mid = min(left_start + curr_size - 1, n - 1);
            int right_end = min(left_start + 2 * curr_size - 1, n - 1);
            merge(arr, left_start, mid, right_end);
        }
    }
}

int main() {
    cout << "Input the array: ";
    string input;
    getline(cin, input);

    vector<int> arr;
    size_t pos = 0;
    while ((pos = input.find(',')) != string::npos) {
        arr.push_back(stoi(input.substr(0, pos)));
        input.erase(0, pos + 1);
    }
    arr.push_back(stoi(input));

    // Recursive Merge Sort
    mergeSortRecursive(arr, 0, arr.size() - 1);

    cout << "Sorted array by Recursion: ";
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i];
        if (i < arr.size() - 1)
            cout << ",";
    }
    cout << endl;

    // Iterative Merge Sort
    mergeSortIterative(arr);

    cout << "Sorted array by Iteration: ";
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i];
        if (i < arr.size() - 1)
            cout << ",";
    }
    cout << endl;

    return 0;
}

// Suppose the input array is: 9 12 4 6 2 8 11 5

// Iteration 1:
// Subarrays of size 1: [9] [12] [4] [6] [2] [8] [11] [5]
// Merging pairs: [9 12] [4 6] [2 8] [5 11]
// Merging pairs: [4 6 9 12] [2 5 8 11]

// Iteration 2:
// Subarrays of size 2: [4 6 9 12] [2 5 8 11]
// Merging pairs: [2 4 5 6 8 9 11 12]
// The final sorted array is: 2 4 5 6 8 9 11 12





