#include <iostream>
#include <vector>
using namespace std;

bool isSolvable(vector<int> &puzzle)
{
    int invCount = 0;
    int blankRowFromBottom;

    // Count inversions
    for (int i = 0; i < 16; i++)
    {
        for (int j = i + 1; j < 16; j++)
        {
            if (puzzle[i] && puzzle[j] && puzzle[i] > puzzle[j])
                invCount++;
        }
    }

    // Find blank row from bottom
    for (int i = 0; i < 16; i++)
    {
        if (puzzle[i] == 0)
        {
            int rowFromTop = i / 4;
            blankRowFromBottom = 4 - rowFromTop;
            break;
        }
    }

    // Check rule
    return ((invCount + blankRowFromBottom) % 2 == 1);
}

int main()
{
    vector<int> puzzle(16);

    cout << "Enter puzzle elements (use 0 for blank):\n";
    for (int i = 0; i < 16; i++)
        cin >> puzzle[i];

    if (isSolvable(puzzle))
        cout << "Puzzle is Solvable\n";
    else
        cout << "Puzzle is NOT Solvable\n";

    return 0;
}