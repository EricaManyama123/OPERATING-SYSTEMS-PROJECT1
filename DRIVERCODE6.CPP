#include <iostream>
using namespace std;

const int MAX_FRAMES = 3;

void visualizeMemory(int memory[], int size) {
    cout << "Memory: ";
    for (int i = 0; i < MAX_FRAMES; i++) {
        if (i < size)
            cout << memory[i] << " ";
        else
            cout << "_ ";
    }
    cout << endl;
}

void simulateFIFO(int pages[], int n) {
    int memory[MAX_FRAMES];
    int pageFaults = 0;
    int index = 0;  // Points to the next frame to replace
    int count = 0;

    for (int i = 0; i < n; i++) {
        bool found = false;

        // Check if page already in memory
        for (int j = 0; j < count; j++) {
            if (memory[j] == pages[i]) {
                found = true;
                break;
            }
        }

        cout << "Accessing Page: " << pages[i] << endl;

        if (!found) {
            cout << "→ Page Fault Occurred!\n";
            memory[index] = pages[i];
            index = (index + 1) % MAX_FRAMES;

            if (count < MAX_FRAMES)
                count++;

            pageFaults++;
        } else {
            cout << "→ Page Hit\n";
        }

        visualizeMemory(memory, count);
        cout << "------------------------\n";
    }

    cout << "Total Page Faults: " << pageFaults << endl;
}

int main() {
    int pageRequests[] = {2, 3, 2, 1, 5, 2, 4, 5, 3, 2};
    int totalPages = sizeof(pageRequests) / sizeof(pageRequests[0]);

    simulateFIFO(pageRequests, totalPages);

    return 0;
}
