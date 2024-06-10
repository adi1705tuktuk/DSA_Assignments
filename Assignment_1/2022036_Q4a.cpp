#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> maxMinSubarrays(const vector<int>& arr) {
    int n = arr.size();
    vector<int> result(n, 0);

    for (int size = 1; size <= n; size++) {
        int minValue = INT_MAX;
        for (int i = 0; i <= n - size; i++) {
            minValue = *min_element(arr.begin() + i, arr.begin() + i + size);
            result[size - 1] = max(result[size - 1], minValue);
        }
    }

    return result;
}

int main() {
    int n;
    cout << "Enter the size of the array: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter the elements of the array: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    vector<int> result = maxMinSubarrays(arr);
    
    cout << "Consider an array, Arr = [";
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) {
            cout << ", ";
        }
    }
    cout << "]." << endl;

    for (int size = 1; size <= n; size++) {
        cout << "For subarrays of size " << size << ": max(";
        for (int i = 0; i < size; i++) {
            cout << "min(" << arr[i];
            if (i < size - 1) {
                cout << "), ";
            } else {
                cout << ")";
            }
        }
        cout << ") = " << result[size - 1] << endl;
    }

    cout << "The resulting array is [";
    for (int i = 0; i < result.size(); i++) {
        cout << result[i];
        if (i < result.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]." << endl;

    return 0;
}




// Time Complexity for first code: O(n^2)
// In the brute force approach, for each subarray size, we iterate over all possible subarrays, and for each subarray, we find the minimum element. This results in a time complexity of O(n^2), where n is the size of the array.
// Optimized Approach using Monotonic Stack:

