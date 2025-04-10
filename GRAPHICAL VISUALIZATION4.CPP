#include <iostream>
#include <vector>
using namespace std;

// Function to print memory blocks as visualization
void visualizeMemory(const vector<int>& memory, int frameSize) {
    cout << "\nMemory Frame:\n";
    for (int i = 0; i < frameSize; ++i) {
        cout << "+-----";
    }
    cout << "+\n";

    for (int i = 0; i < frameSize; ++i) {
        if (i < memory.size())
            cout << "|  " << memory[i] << "  ";
        else
            cout << "|     ";
    }
    cout << "|\n";

    for (int i = 0; i < frameSize; ++i) {
        cout << "+-----";
    }
    cout << "+\n";
}
