#include <iostream>
#include <queue>
#include <unordered_map>
#include <list>
#include <vector>

using namespace std;

// Base class for page replacement
class PageReplacement {
public:
    virtual void insertPage(int page) = 0;
    virtual void displayMemory() = 0;
    virtual int getPageFaults() = 0;
};

// FIFO Page Replacement
class FIFOPageReplacement : public PageReplacement {
private:
    queue<int> memoryQueue;
    unordered_map<int, bool> memoryMap;
    int capacity;
    int pageFaults;

public:
    FIFOPageReplacement(int cap) : capacity(cap), pageFaults(0) {}

    void insertPage(int page) override {
        if (!memoryMap[page]) {
            pageFaults++;
            if (memoryQueue.size() == capacity) {
                int removed = memoryQueue.front();
                memoryQueue.pop();
                memoryMap[removed] = false;
            }
            memoryQueue.push(page);
            memoryMap[page] = true;
        }
    }

    void displayMemory() override {
        queue<int> temp = memoryQueue;
        cout << "Memory: ";
        while (!temp.empty()) {
            cout << temp.front() << " ";
            temp.pop();
        }
        cout << endl;
    }

    int getPageFaults() override {
        return pageFaults;
    }
};

