#include <iostream>
#include <stack> 
#include <queue>
#include <vector>
#include <sstream>
#include <unordered_set> 

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* createTree(vector<string>& arr) {
    if (arr.empty()){
        return nullptr;
    }

    vector<TreeNode*> nodes;
    for (const auto& val : arr) {
        if (val == "N"){
            nodes.push_back(nullptr);
        }
        else{
            nodes.push_back(new TreeNode(stoi(val)));
        }

    }

    for (int i = 0; i < arr.size(); ++i) {
        if (nodes[i] != nullptr) {
            int leftIndex = 2 * i + 1;
            int rightIndex = 2 * i + 2;
            if (leftIndex < arr.size() && nodes[leftIndex] != nullptr){
                nodes[i]->left = nodes[leftIndex];
            }
            if (rightIndex < arr.size() && nodes[rightIndex] != nullptr){
                nodes[i]->right = nodes[rightIndex];
            }


        }
    }

    return nodes[0];
}


void inorderTraversal(TreeNode* node) {
    vector<int> result;
    stack<TreeNode*> st;
    TreeNode* curr = node;

    while (curr != nullptr || !st.empty()) {
        while (curr != nullptr) {
            st.push(curr);
            curr = curr->left;
        }

        curr = st.top();
        st.pop();
        result.push_back(curr->val);
        curr = curr->right;
    }

    for (int val : result) {
        cout << val << " ";
    }
}

void addEdge(vector<vector<int> >& graph, int u, int v) {
    graph[u].push_back(v);
    graph[v].push_back(u);
}

void createGraph(TreeNode* root, vector<vector<int> >& graph, vector<bool>& visited) {
    stack<TreeNode*> st;

    if (root) {
        st.push(root);
        visited[root->val] = true;
    }

    while (!st.empty()) {
        TreeNode* curr = st.top();
        st.pop();

        if (curr->left) {
            if (!visited[curr->left->val]) {
                visited[curr->left->val] = true;
                st.push(curr->left);
                addEdge(graph, curr->val, curr->left->val);
            }
        }

        if (curr->right) {
            if (!visited[curr->right->val]) {
                visited[curr->right->val] = true;
                st.push(curr->right);
                addEdge(graph, curr->val, curr->right->val);
            }
        }
    }
}


void bfs(const vector<vector<int> >& graph, int startNode) {
    vector<bool> visited(graph.size(), false);
    queue<int> q;
    q.push(startNode);
    visited[startNode] = true;

    int levelSize = 1; 

    while (!q.empty()) {
        vector<int> levelNodes;
        while (levelSize--) {
            int node = q.front();
            q.pop();

            levelNodes.push_back(node);

            for (int neighbor : graph[node]) {
                if (!visited[neighbor]) {
                    q.push(neighbor);
                    visited[neighbor] = true;
                }
            }
        }

        for (int i = 0; i < levelNodes.size(); ++i) {
            cout << levelNodes[i];
            if (i < levelNodes.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
        levelSize = q.size();
    }
}



int max_value(const vector<string>& arr) {
    int max_val = INT_MIN;
    vector<int> values;

    for (const string& str : arr) {
        if (str != "N") {
            values.push_back(stoi(str));
        }
    }

    if (!values.empty()) {
        max_val = *max_element(values.begin(), values.end());
    }

    return max_val;
}

vector<vector<int> > initialise_graph(const vector<string>& arr) {
    unordered_set<int> uniqueValues; 
    int maxValue = INT_MIN;

    for (const string& str : arr) {
        if (str != "N") {
            int value = stoi(str);
            uniqueValues.insert(value);
            maxValue = max(maxValue, value);
        }
    }

    vector<vector<int> > graph(maxValue + 1);
    return graph;
}


int main() {
    string input = "12 13 10 N N 14 15 N N N N 21 24 22 23";
    istringstream iss(input);
    vector<string> arr;
    string val;
    while (iss >> val) {
        arr.push_back(val);
    }
    TreeNode* root = createTree(arr);
    int no_of_nodes = max_value( arr);
    vector<bool> visited(no_of_nodes, false);
    vector<vector<int> >graph =  initialise_graph( arr);
    createGraph(root , graph, visited);
    bfs(graph, 14);


    return 0;
}
