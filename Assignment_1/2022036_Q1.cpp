
#include <iostream>
using namespace std;

void towerOfHanoi(int n, char from_peg, char to_peg,
                    char temp_peg1, char temp_peg2)
{
    if (n == 0)
        return;
    if (n == 1)
    {
        cout << "T" << from_peg - 'A' + 1 << " -> T" << to_peg - 'A' + 1 << endl;
        return;
    }

    towerOfHanoi(n - 2, from_peg, temp_peg1, temp_peg2,
                                            to_peg);
    cout << "T" << from_peg - 'A' + 1 << " -> T" << temp_peg2 - 'A' + 1 << endl;

    cout << "T" << from_peg - 'A' + 1 << " -> T" << to_peg - 'A' + 1 << endl;

    cout << "T" << temp_peg2 - 'A' + 1 << " -> T" << to_peg - 'A' + 1 << endl;

    towerOfHanoi(n - 2, temp_peg1, to_peg, from_peg,
                                        temp_peg2);
}

int main()
{
    int n;
    cout << "Enter the number of disks: ";
    cin >> n;
    cout << "The sequence of steps are:-" << endl;
    towerOfHanoi(n, 'A', 'D', 'B', 'C');
    return 0;
}
