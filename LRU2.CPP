#include <iostream>
#include <list>
#include <unordered_map>
using namespace std;

class LRUPageReplacement {
private:
    int capacity;
    list<int> pageList; // front = most recently used, back = least recently used
    unordered_map<int, list<int>::iterator> pageMap;
    int pageFaults;

public:
    LRUPageReplacement(int cap) {
        capacity = cap;
        pageFaults = 0;
    }

    void accessPage(int page) {
        // Page not in memory (Page Fault)
        if (pageMap.find(page) == pageMap.end()) {
            pageFaults++;

            // If memory is full, remove least recently used (last element)
            if (pageList.size() == capacity) {
                int lruPage = pageList.back();
                pageList.pop_back();
                pageMap.erase(lruPage);
            }
        } else {
            // Page is already in memory: remove it to update position
            pageList.erase(pageMap[page]);
        }

        // Insert page at the front (most recently used)
        pageList.push_front(page);
        pageMap[page] = pageList.begin();
    }

    void displayMemory() {
        cout << "Current Memory: ";
        for (int page : pageList) {
            cout << page << " ";
        }
        cout << endl;
    }

    int getPageFaultCount() const {
        return pageFaults;
    }
};

int main() {
    int capacity, n, page;
    
    cout << "Enter number of memory frames: ";
    cin >> capacity;

    cout << "Enter number of page requests: ";
    cin >> n;

    LRUPageReplacement lru(capacity);

    cout << "Enter page requests one by one:\n";
    for (int i = 0; i < n; ++i) {
        cin >> page;
        lru.accessPage(page);
        lru.displayMemory();
    }

    cout << "\nTotal Page Faults (LRU): " << lru.getPageFaultCount() << endl;

    return 0;
}
