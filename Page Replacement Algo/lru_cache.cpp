#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

// Node structure for the doubly linked list
struct Node {
    int key;
    Node* prev;
    Node* next;
    Node(int k) : key(k), prev(nullptr), next(nullptr) {}
};

class LRUCache {
    int capacity;  // Maximum capacity of the cache
    unordered_map<int, Node*> cacheMap;  // Hash map to store key-node pairs
    Node* head;  // Pointer to the head (most recently used)
    Node* tail;  // Pointer to the tail (least recently used)
    int pageFaults;  // Count of page faults

    // Function to add a node at the front (most recently used position)
    void addNodeToFront(Node* node) {
        node->next = head;
        node->prev = nullptr;
        if (head != nullptr) {
            head->prev = node;
        }
        head = node;
        if (tail == nullptr) {
            tail = head;  // If the list was empty, tail is also the new node
        }
    }
    
    // Function to remove a node from the list
    void removeNode(Node* node) {
        if (node->prev != nullptr) {
            node->prev->next = node->next;
        } else {
            head = node->next;  // If node is the head, update the head
        }
        
        if (node->next != nullptr) {
            node->next->prev = node->prev;
        } else {
            tail = node->prev;  // If node is the tail, update the tail
        }
    }
    
    // Function to move a node to the front (most recently used position)
    void moveToFront(Node* node) {
        removeNode(node);
        addNodeToFront(node);
    }

public:
    LRUCache(int cap) {
        capacity = cap;
        head = nullptr;
        tail = nullptr;
        pageFaults = 0;  // Initialize page fault counter
    }
    
    // Function to simulate a page request from the reference string
    void requestPage(int key) {
        if (cacheMap.find(key) != cacheMap.end()) {
            // Key is already present, move the node to the front (most recently used)
            Node* node = cacheMap[key];
            moveToFront(node);
        } else {
            // Page fault occurs (key not found in cache)
            pageFaults++;
            
            // If the cache is full, remove the least recently used node (tail)
            if (cacheMap.size() == capacity) {
                cacheMap.erase(tail->key);  // Remove from map
                removeNode(tail);  // Remove from list
            }
            
            // Insert the new key
            Node* newNode = new Node(key);
            addNodeToFront(newNode);
            cacheMap[key] = newNode;
        }
    }
    
    // Function to get the total number of page faults
    int getPageFaults() {
        return pageFaults;
    }
    
    // Function to display the cache (for demonstration purposes)
    void displayCache() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->key << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() {
    int cacheSize;
    cout << "Enter cache size: ";
    cin >> cacheSize;
    
    LRUCache lru(cacheSize);  // Create LRU cache with the specified size
    
    int n;
    cout << "Enter number of pages in reference string: ";
    cin >> n;
    
    vector<int> referenceString(n);
    cout << "Enter the reference string (space-separated page numbers): ";
    for (int i = 0; i < n; i++) {
        cin >> referenceString[i];
    }
    
    // Process each page request
    for (int page : referenceString) {
        lru.requestPage(page);  // Simulate the page request
        lru.displayCache();     // Display current cache content after each request
    }
    
    // Output the total number of page faults
    cout << "Total page faults: " << lru.getPageFaults() << endl;
    
    return 0;
}
