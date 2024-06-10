#include <bits/stdc++.h>

using namespace std;

#define mod 1e9+7
#define putyes cout<<"YES"<<endl
#define putno cout<<"NO"<<endl
#define int long long 


struct Stack {

    vector<int> s;

    void push(int x) { s.push_back(x); }

    bool empty() { return s.empty(); }
 
    int top() { 
        if(s.empty()){throw invalid_argument("Stack Empty");}
        else {return  s.back();}
    }
    
    void pop() { 
        if (!s.empty()) s.pop_back();   
        else {throw invalid_argument("Stack is Empty, Invalid Operation ");}
    }
 
};

void merge(pair<int, int>* arr, int l, int m, int r) {
    int i = l, j = m + 1;
    vector<pair<int, int>> temp(r - l + 1);

    for (int k = 0; k < temp.size(); k++) {
        if (i > m) {
            temp[k] = arr[j++];
        } else if (j > r) {
            temp[k] = arr[i++];
        } else if (arr[i].first < arr[j].first) {
            temp[k] = arr[i++];
        } else {
            temp[k] = arr[j++];
        }
    }

    for (int k = 0; k < temp.size(); k++) {
        arr[l + k] = temp[k];
    }
}


void mergeSort(pair<int, int>* arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}


bool checkequal(char a, char b){
    if(a == b) return true;
    return false;
}
int setzero(){return 0;}


vector<int> checkhealth(vector<int> h, int n){

   int count = setzero();
    for (int i = 0; i < n; i++) {
        if (h[i] > 0 ) count++;
    }

    vector<int> answer(count);

    int j = setzero();
    for (int i = 0; i < n; i++) {
        if (h[i] > 0) answer[j++] = h[i];

    }

    return answer;

    
}

vector<int> survivedRobotsHealths(vector<int>& pos, vector<int>& h, string d) {


    int n = pos.size();

    pair<int, int>* vectorpair= new pair<int, int>[n];

    for (int i = 0; i < n; i++) {
        vectorpair[i] = {pos[i], i};
    }
    
    mergeSort(vectorpair, 0, n - 1);
    
    
    Stack st;
    for (int i = 0; i < n; i++) {
        int ind = vectorpair[i].second;
        char dir = d[ind];

        if(dir != 'D'){
            st.push(ind);
        }
        else if (dir == 'D' && !checkequal('R','D')) {

            if (st.empty()) {
                st.push(ind);
            } 
            else if(!st.empty()) {
                if ( checkequal(d[st.top()],'R') &&  checkequal(h[st.top()],h[ind] && !checkequal('R','D'))) {
                    h[st.top()] = setzero();
                    st.pop();
                    h[ind] = setzero();
                }
                else {
                    while (!st.empty() && checkequal(d[st.top()],'R') && h[st.top()] < h[ind] && !checkequal('R','D') ) {
                        h[st.top()] = setzero();
                        st.pop();
                        h[ind]--;
                    }

                    if (!st.empty() && checkequal(d[st.top()],'R') && h[st.top()] > h[ind] && !checkequal('R','D')) {
                        h[st.top()]--;
                        h[ind] = setzero();
                    } 

                    else if (!st.empty() &&  checkequal(d[st.top()],'R') && h[st.top()] == h[ind] && !checkequal('R','D')) {
                        h[st.top()] = setzero();
                        h[ind] = setzero();
                        st.pop();
                    }
 
                    else {
                        st.push(ind);
                    }
                }
            }
        }
        else {
            st.push(ind);
        }
        
    }

    return checkhealth(h,n);
}



void solve(){

    int n;
    // cout << "Enter the number of robots: ";
    cin >> n;

    vector<int> pos(n), h(n);
    // cout << "Enter the positions of robots: ";
    for (int i = 0; i < n; i++) {
        cin >> pos[i];
    }

    // cout << "Enter the healths of robots: ";
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }

    string d;
    // cout << "Enter the team (R or D): ";
    cin >> d;

    vector<int> ans = survivedRobotsHealths(pos, h, d);

    // cout << "Output: ";
    for (int health : ans) {
        cout << health << " ";
    }
    cout << endl;

}


signed main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    
    solve();

    return 0;
}