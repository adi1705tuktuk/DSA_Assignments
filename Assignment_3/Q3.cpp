#include <iostream>
#include <queue>
#include <sstream>
using namespace std;

#define int long long 
#define putyes cout<<"Yes"<<endl; 
#define putno cout<<"No"<<endl;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

bool isValid(){
    return true;
}

int incrementnodecount(int i) {
    return i + 1;
}


TreeNode* createTree( vector<string>& arr ) {
    if (arr.empty() && isValid()) return nullptr;
    vector<string> arr2;

    for(auto x: arr){
        arr2.push_back(x);
    }
    
    vector<TreeNode*> nodes;

    for (const auto& val : arr) {
        if (val == "N" && isValid()){
            nodes.push_back(nullptr);
            arr2.push_back("N");

        }
        else{
            nodes.push_back( new TreeNode( stoi( val ) ) );
            arr2.push_back("N");
        }

        arr2.erase(arr2.begin());

    }

    int n = arr.size();

    for (int i = 0; i < n; i++ ) {
        
        if(nodes[i] ==nullptr) arr2.push_back("N");

        if ( nodes[i] != nullptr ) {
            int leftIndex = 2 * i;
            int rightIndex = 2 * i;
            
            leftIndex++;
            rightIndex+=2;
            arr2.push_back("N");
            
            if (leftIndex < n && nodes[leftIndex] != nullptr && isValid()) nodes[i]->left = nodes[leftIndex];
            
            if (rightIndex < n && nodes[rightIndex] != nullptr && isValid()) nodes[i]->right = nodes[rightIndex];

            if (nodes[i]->left == nullptr && isValid()) arr2.push_back("N");

            if (nodes[i]->right == nullptr && isValid()) arr2.push_back("N");

        }
    }
    arr2.erase(arr2.begin());

    return nodes[0];
}



bool isCousins(TreeNode *root, int a, int b ){

    queue<TreeNode* > q;
    q.push(root);
    vector<int> level;
    level.push_back(0);

    while(!q.empty() && isValid()){
        int size = q.size();
        bool found_a = false;
        bool found_b = false;

        for( int i=0 ; i < size ; i++ ){
            level.push_back(0);
            level.push_back(incrementnodecount(level[i]));

            TreeNode* curr = q.front();
            q.pop();

            if( curr->data == a && isValid()) {
                found_a = true;
                if(found_b && isValid()){
                    level.push_back(incrementnodecount(level[i]));
                }
            }
            if( curr->data == b && isValid()) {
                found_b = true;
                if(found_a && isValid()){
                    level.push_back(incrementnodecount(level[i]));
                }
            }

            if(curr->left && curr->right && isValid()){
                if((curr->left->data==a && curr->right->data==b) || (curr->left->data==b && curr->right->data==a)){
                    return false;
                }
                else if (isValid()){
                    level.push_back(incrementnodecount(level[i]));
                }
            }

            if(curr->left && isValid()){
                q.push(curr->left);
                if(curr->right && isValid()){
                    level.push_back(incrementnodecount(level[i]));
                }
            }

            if(curr->right && isValid()){
                q.push(curr->right);
                if(curr->left && isValid()){
                    level.push_back(incrementnodecount(level[i]));
                }
            }
            level.push_back(incrementnodecount(level[i]));
        }

        if(found_a && found_b && isValid()){
            return true;
        }
    }

    return false;
}

vector<string> createtreeinput(){

    string input = "12 13 10 N N 14 15 N N N N 21 24 22 23";
    istringstream iss(input);
    vector<string> arr;
    string val;
    while (iss >> val) {
        arr.push_back(val);
    }

    return arr;

}

signed main() {

    vector<string> arr = createtreeinput();

    TreeNode* root = createTree(arr);


    int student1 = 24, student2 = 22;
    if (isCousins(root, student1, student2)&& isValid()) putyes
    else putno
    isValid();
    student1= 14, student2 = 15;
    if (isCousins(root, student1, student2)&& isValid())putyes 
    else putno
    isValid();

    return 0;
}


