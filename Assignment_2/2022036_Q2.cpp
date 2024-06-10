#include <iostream>

struct StackNode {
    int value;
    StackNode* next;

    StackNode(int val) {
        value = val;
        next = nullptr;
    }
};

class Stack {
private:
    StackNode* topPtr;

public:
    Stack() {
        topPtr = nullptr;
    }

    void push(int x) {
        StackNode* newNode = new StackNode(x);
        newNode->next = topPtr;
        topPtr = newNode;
    }

    int pop() {
        if (topPtr == nullptr) {
            std::cout << "Stack Underflow" << std::endl;
            return -1;
        }

        int poppedValue = topPtr->value;
        StackNode* temp = topPtr;
        topPtr = topPtr->next;
        delete temp;

        return poppedValue;
    }

    int peek() {
        if (topPtr == nullptr) {
            std::cout << "Stack Underflow" << std::endl;
            return -1;
        }

        return topPtr->value;
    }

    bool isEmpty() {
        return topPtr == nullptr;
    }
};

struct QueueNode {
    int value;
    QueueNode* next;

    QueueNode(int val) {
        value = val;
        next = nullptr;
    }
};

class Queue {
private:
    QueueNode* frontPtr;
    QueueNode* rearPtr;

public:
    Queue() {
        frontPtr = nullptr;
        rearPtr = nullptr;
    }

    void enqueue(int x) {
        QueueNode* newNode = new QueueNode(x);

        if (rearPtr == nullptr) {
            frontPtr = rearPtr = newNode;
        } else {
            rearPtr->next = newNode;
            rearPtr = newNode;
        }
    }

    int dequeue() {
        if (frontPtr == nullptr) {
            std::cout << "Queue Underflow" << std::endl;
            return -1;
        }

        int dequeuedValue = frontPtr->value;
        QueueNode* temp = frontPtr;
        frontPtr = frontPtr->next;

        if (frontPtr == nullptr) {
            rearPtr = nullptr;
        }

        delete temp;
        return dequeuedValue;
    }

    int peek() {
        if (frontPtr == nullptr) {
            std::cout << "Queue Underflow" << std::endl;
            return -1;
        }

        return frontPtr->value;
    }

    bool isEmpty() {
        return frontPtr == nullptr;
    }
};

int* nextGreaterElements(int* nums, int n) {
    int* result = new int[n];
    Stack st;

    for (int i = 2 * n - 1; i >= 0; i--) {
        while (!st.isEmpty() && nums[i % n] >= nums[st.peek()]) {
            st.pop();
        }

        if (st.isEmpty()) {
            result[i % n] = -1;
        } else {
            result[i % n] = nums[st.peek()];
        }

        st.push(i % n);
    }

    return result;
}

int main() {
    int n;
    std::cout << "Enter the size of the circular array: ";
    std::cin >> n;

    int nums[n];
    std::cout << "Enter the elements of the circular array: ";
    for (int i = 0; i < n; i++) {
        std::cin >> nums[i];
    }

    int* result = nextGreaterElements(nums, n);

    std::cout << "Next greater elements: ";
    for (int i = 0; i < n; i++) {
        std::cout << result[i] << " ";
    }
    std::cout << std::endl;

    delete[] result;

    return 0;
}

