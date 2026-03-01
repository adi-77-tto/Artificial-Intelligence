#include <iostream>
#include <vector>
using namespace std;

bool isSolvable(vector<int> &puzzle)
{
    int invCount = 0;

    // Count inversions
    for (int i = 0; i < 9; i++)
    {
        for (int j = i + 1; j < 9; j++)
        {
            if (puzzle[i] && puzzle[j] && puzzle[i] > puzzle[j])
                invCount++;
        }
    }
    // If inversion count is even -> solvable
    return (invCount % 2 == 0);
}

int main()
{
    vector<int> puzzle(9);

    cout << "Enter puzzle elements (use 0 for blank):\n";
    for (int i = 0; i < 9; i++)
        cin >> puzzle[i];

    if (isSolvable(puzzle))
        cout << "Puzzle is Solvable\n";
    else
        cout << "Puzzle is NOT Solvable\n";

    return 0;
}