#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define int long long 

using namespace std;

int countChar(const string& str, char c) {
    return count(str.begin(), str.end(), c);
}

int calculateCost(int numSushi, const string& recipe, vector<int>& ingredients, vector<int>& prices) {

    int totalCost = 0;
    vector<int> ingredientsNeeded(3, 0); 

    ingredientsNeeded[0] = numSushi * countChar(recipe, 'B'); 
    ingredientsNeeded[1] = numSushi * countChar(recipe, 'S'); 
    ingredientsNeeded[2] = numSushi * countChar(recipe, 'C'); 

    for (int i = 0; i < 3; i++) {
        int needed = abs(ingredientsNeeded[i] - ingredients[i]);
        totalCost += needed * prices[i];
    }

    return totalCost;
}

signed main() {
    string recipe;
    vector<int> ingredients(3);
    vector<int> prices(3);
    int budget;

    cout << "Recipe: ";
    cin >> recipe;

    cout << "Number of bread, salmon, and corn(n_b, n_s, n_c): ";
    cin >> ingredients[0] >> ingredients[1] >> ingredients[2];

    cout << "Price of bread, salmon, and corn(n_b, n_s, n_c): ";
    cin >> prices[0] >> prices[1] >> prices[2];

    cout << "Amount(r): ";
    cin >> budget;

    int low = 0, high = budget + 1;  

    while (low < high) {
        int mid = low + (high - low) / 2;
        int cost = calculateCost(mid, recipe, ingredients, prices);

        if (cost <= budget) {
            low = mid + 1; 
        } else {
            high = mid;  
        }
    }

    cout << "OUTPUT: " << low - 1 << endl;

    return 0;
}
