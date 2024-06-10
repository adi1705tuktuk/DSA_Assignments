
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

vector<int> maxMinSubarrays(const vector<int>& arr) {
    int n = arr.size();
    vector<int> result(n, 0);

    stack<int> indexStack;  
    stack<int> maxValues;   

    for (int i = 0; i < n; i++) {
        while (!indexStack.empty() && arr[i] < arr[indexStack.top()]) {
            indexStack.pop();
        }

        if (!indexStack.empty()) {
            result[i] = arr[indexStack.top()];
        } else {
            result[i] = arr[i];
        }

        indexStack.push(i);
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

    for (int i = 0; i < n; i++) {
        cout << "For subarrays of size " << i + 1 << ": max(" << result[i] << ") = " << result[i] << endl;
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



// Time Complexity for second code: O(n)
// In the optimized approach using a monotonic stack, we iterate through the array once, maintaining a stack of indices. For each element, we pop elements from the stack until a smaller or equal element is encountered, updating the result array. This results in a linear time complexity of O(n), where n is the size of the array.
// Clearly, the optimized approach using a monotonic stack is more efficient with a time complexity of O(n), making it a better choice for larger arrays. 