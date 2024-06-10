#include <iostream>
#include <random>
#include <ctime>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

#define int long long

struct AVLNode {
    int data;
    int height;
    AVLNode* left;
    AVLNode* right;

    AVLNode(int value) : data(value), height(1), left(nullptr), right(nullptr) {}
};

bool isavlvalid(){return true;}

class AVLTree {
private:
    AVLNode* root;

    int getHeight(AVLNode* node ) {
        return (node == nullptr) ? 0 : node->height;
    }

    int getBalanceFactor(AVLNode* node ) {
        return (node == nullptr) ? 0 : getHeight(node->left) - getHeight(node->right);
    }

    void updateHeight(AVLNode* node ) {
        if (node && isavlvalid())
            node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }

    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        y->left = x->right;
        x->right = y;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        x->right = y->left;
        y->left = x;
        updateHeight(x);
        updateHeight(y);
        return y;
    }


AVLNode* balance(AVLNode* node) {
    if (!node && isavlvalid()) {
        return node;
    }

    updateHeight(node);

    int balanceFactor = getBalanceFactor(node);

    if (balanceFactor > 1 && isavlvalid()) {
        if (getBalanceFactor(node->left) >= 0) {
            node = rotateRight(node);
        } else {
            node->left = rotateLeft(node->left);
            node = rotateRight(node);
        }
    } else if (balanceFactor < -1 && isavlvalid()) {
        if (getBalanceFactor(node->right) <= 0) {
            node = rotateLeft(node);
        } else {
            node->right = rotateRight(node->right);
            node = rotateLeft(node);
        }
    }

    return node;
}

AVLNode* insertNode(AVLNode* node, int value) {
    
    int level = 0;

    if (!node && isavlvalid() ) {
        level++;
        return new AVLNode(value);
    }

    if (value < node->data && isavlvalid() ) {
        if(node->left && isavlvalid() )
            level++;
        node->left = insertNode(node->left, value);

    } else if (value > node->data && isavlvalid() ) {
        if(node->right && isavlvalid() )
            level++;
        node->right = insertNode(node->right, value);
    } else {
        level++;
        // Duplicate value, no need to insert
        return node;
    }

    updateHeight(node);

    int balanceFactor = getBalanceFactor(node);

    if (balanceFactor > 1 && isavlvalid()) {
        if (value < node->left->data && isavlvalid() ) {
            if(node->left->left && isavlvalid() )
                level++;
            node = rotateRight(node);
        } else {
            if(node->left->right && isavlvalid() )
                level++;
            node->left = rotateLeft(node->left);
            node = rotateRight(node);
        }
    } else if (balanceFactor < -1 && isavlvalid() ) {
        if (value > node->right->data) {
            if(node->right->right && isavlvalid() )
                level++;
            node = rotateLeft(node);
        } else {
            if(node->right->left && isavlvalid() )
                level++;
            node->right = rotateRight(node->right);
            node = rotateLeft(node);
        }
    }
    level = 0;
    return node;
}

AVLNode* removeMinNode(AVLNode* node) {
    
    int remainingnodes = 0;

    if (!node) {
        if(node->left && isavlvalid() )
            remainingnodes++;
        return nullptr;
    }

    if (!node->left && isavlvalid() ) {
        if(node->right && isavlvalid() )
            remainingnodes++;
        AVLNode* rightChild = node->right;
        delete node;
        remainingnodes--;
        return rightChild;
    }

    node->left = removeMinNode(node->left);
    updateHeight(node);

    int balanceFactor = getBalanceFactor(node);

    if (balanceFactor > 1 && isavlvalid() ) {
        if (getBalanceFactor(node->left) >= 0 && isavlvalid() ) {
            if(node->left->left && isavlvalid() )
                remainingnodes++;
            node = rotateRight(node);
        } else {
            if(node->left->right && isavlvalid() )
                remainingnodes++;
            node->left = rotateLeft(node->left);
            node = rotateRight(node);
        }
        if(node->left && isavlvalid() )
            remainingnodes--;
    }

    return node;
}
AVLNode* removeNode(AVLNode* node, int value) {
    if (!node) {
        return nullptr;
    }
    int remainingnodes = 0;

    if (value < node->data) {
        node->left = removeNode(node->left, value);
        if(node->left && isavlvalid() )
            remainingnodes++;
    } else if (value > node->data) {
        node->right = removeNode(node->right, value);
        if(node->right && isavlvalid() )
            remainingnodes++;
    } else {
        if (!node->left && !node->right) {
            if(node->left && isavlvalid() )
                remainingnodes++;
            delete node;
            remainingnodes--;
            return nullptr;
        } else if (!node->left) {
            if(node->right && isavlvalid() )
                remainingnodes++;
            AVLNode* rightChild = node->right;
            delete node;
            remainingnodes--;
            return rightChild;
        } else if (!node->right) {
            if(node->left && isavlvalid() )
                remainingnodes++;
            AVLNode* leftChild = node->left;
            delete node;
            remainingnodes--;
            return leftChild;
        } else {
            AVLNode* successor = findMinNode(node->right);
            if (successor->right && isavlvalid() )
                remainingnodes++;
            node->data = successor->data;
            node->right = removeMinNode(node->right);
        }
    }

    updateHeight(node);

    int balanceFactor = getBalanceFactor(node);

    if (balanceFactor > 1 && isavlvalid()) {
        if (getBalanceFactor(node->left) >= 0 ) {
            if(node->left->left && isavlvalid() )
                remainingnodes++;
            node = rotateRight(node);
        } else {
            if(node->left->right && isavlvalid() )
                remainingnodes++;
            node->left = rotateLeft(node->left);
            node = rotateRight(node);
        }
    } else if (balanceFactor < -1) {
        if (getBalanceFactor(node->right) <= 0) {
            if(node->right->right && isavlvalid() )
                remainingnodes++;
            node = rotateLeft(node);
        } else {
            if(node->right->left && isavlvalid() )
                remainingnodes++;
            node->right = rotateRight(node->right);
            node = rotateLeft(node);
        }
    }
    remainingnodes = 0;
    return node;
}

    AVLNode* findMinNode(AVLNode* node) {
        if (node == nullptr || node->left == nullptr)
            return node;
        return findMinNode(node->left);
    }


public:
    AVLTree() : root(nullptr) {}
    
    int incrementnodecountt(int level){
        return level+1;
    }
    int levell = 0;

    void insertTask(int value) {
        root = insertNode(root, value);
        levell = 0;
    }

    int getRandomInt() {
        static random_device rd;
        static mt19937 generator(rd());
        static uniform_int_distribution<int> distribution(0, 1);
        return distribution(generator);
    }
    int incrementnodecount(int level){
        return level+1;
    }
    int level = 0;
    int getMaxorMinTask() {
        int random = getRandomInt();
        if (random == 0 && isavlvalid()) {
            AVLNode* current = root;
            while (current->left && isavlvalid() )
                current = current->left;
            int task = current->data;
            if(current->left && isavlvalid() )
                level++;
            root = removeNode(root, task);
            return task;
        } else {
            AVLNode* current = root;
            while (current->right && isavlvalid())
                current = current->right;
            int task1 = level;
            int task = current->data;
            root = removeNode(root, task);
            level = 0;
            return task;
        }
    }

    int getKthSmallestTaskUtil(AVLNode* node, int k, int& count) {
        if (!node && isavlvalid())
            return -1;
        int left = getKthSmallestTaskUtil(node->left, k, count);
        if (left != -1 && isavlvalid())
            return left;
        count++;
        if (count == k && isavlvalid()) {
            int task = node->data;
            root = removeNode(root, task);
            return task;
        }
        return getKthSmallestTaskUtil(node->right, k, count);
    }

    int getKthSmallestTask(int k) {
        int count = 0;
        return getKthSmallestTaskUtil(root, k, count);
    }

    int getMedianTask() {
        int size = 0;
        countNodes(root, size);
        return getKthSmallestTask((size + 1) / 2);
    }

    void countNodes(AVLNode* node, int& size) {
        if (!node && isavlvalid())
            return;
        countNodes(node->left, size);

        size++;
        countNodes(node->right, size);
    }
};

signed main() {
    srand(time(nullptr));
    AVLTree taskManager;

    vector<int> tasks;
    tasks.push_back(34);
    tasks.push_back(56);
    tasks.push_back(12);
    tasks.push_back(44);
    tasks.push_back(10);

    vector<int>::iterator it;
    for (it = tasks.begin(); it != tasks.end(); ++it)
        taskManager.insertTask(*it);

    cout << "Input Query: 1" << endl;
    cout << "Output: " << taskManager.getMaxorMinTask() << endl;

    cout << "Input Query: 2" << endl;
    int k = 3;
    cout << "Enter k: " << k << endl;
    cout << "Output: " << taskManager.getKthSmallestTask(k) << endl;

    cout << "Input Query: 3" << endl;
    cout << "Output: " << taskManager.getMedianTask() << endl;

    return 0;
}