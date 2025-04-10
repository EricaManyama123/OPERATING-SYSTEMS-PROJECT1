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

// LRU Page Replacement
class LRUPageReplacement : public PageReplacement {
private:
    list<int> memoryList;
    unordered_map<int, list<int>::iterator> memoryMap;
    int capacity;
    int pageFaults;

public:
    LRUPageReplacement(int cap) : capacity(cap), pageFaults(0) {}

    void insertPage(int page) override {
        if (memoryMap.find(page) == memoryMap.end()) {
            pageFaults++;
            if (memoryList.size() == capacity) {
                int last = memoryList.back();
                memoryList.pop_back();
                memoryMap.erase(last);
            }
        } else {
            memoryList.erase(memoryMap[page]);
        }
        memoryList.push_front(page);
        memoryMap[page] = memoryList.begin();
    }

    void displayMemory() override {
        cout << "Memory: ";
        for (int page : memoryList) {
            cout << page << " ";
        }
        cout << endl;
    }

    int getPageFaults() override {
        return pageFaults;
    }
};

// Test/Driver Code
int main() {
    vector<int> pageRequests = {1, 2, 3, 4, 2, 1, 5, 2, 4, 5};
    int capacity;

    cout << "Enter memory capacity (number of frames): ";
    cin >> capacity;

    cout << "\n--- FIFO Page Replacement ---\n";
    FIFOPageReplacement fifo(capacity);
    for (int page : pageRequests) {
        fifo.insertPage(page);
        fifo.displayMemory();
    }
    cout << "Total Page Faults (FIFO): " << fifo.getPageFaults() << "\n";

    cout << "\n--- LRU Page Replacement ---\n";
    LRUPageReplacement lru(capacity);
    for (int page : pageRequests) {
        lru.insertPage(page);
        lru.displayMemory();
    }
    cout << "Total Page Faults (LRU): " << lru.getPageFaults() << "\n";

    return 0;
}
