#include <iostream>
using namespace std;

class MaxHeap {
    int* data;
    int size, capacity;
    void swapVals(int& a, int& b) { int t = a; a = b; b = t; }
public:
    MaxHeap(int cap) : size(0), capacity(cap) { data = new int[cap]; }
    ~MaxHeap() { delete[] data; }

    void print() {
        cout << "[ ";
        for (int i = 0; i < size; i++) cout << data[i] << " ";
        cout << "]";
    }

    // Insert: place at end, then sift-up
    void insert(int value) {
        if (size == capacity) { cout << "Heap full\n"; return; }
        int i = size++;
        data[i] = value;
        int swaps = 0;
        while (i > 0 && data[(i - 1) / 2] < data[i]) {
            swapVals(data[(i - 1) / 2], data[i]);
            i = (i - 1) / 2;
            swaps++;
        }
        cout << "Insert " << value << " -> swaps: " << swaps << " -> ";
        print();
        cout << endl;
    }

    // Sift-down within first n elements
    static void siftDown(int arr[], int n, int i) {
        while (true) {
            int largest = i, l = 2 * i + 1, r = 2 * i + 2;
            if (l < n && arr[l] > arr[largest]) largest = l;
            if (r < n && arr[r] > arr[largest]) largest = r;
            if (largest == i) break;
            int t = arr[i]; arr[i] = arr[largest]; arr[largest] = t;
            i = largest;
        }
    }

    // Heap sort on a copy of the heap array
    void heapSort() {
        int* a = new int[size];
        for (int i = 0; i < size; i++) a[i] = data[i];
        for (int end = size - 1; end > 0; end--) {
            int t = a[0]; a[0] = a[end]; a[end] = t;
            siftDown(a, end, 0);
        }
        cout << "Sorted (ascending): [ ";
        for (int i = 0; i < size; i++) cout << a[i] << " ";
        cout << "]\n";
        delete[] a;
    }
};

int main() {
    int values[] = { 25, 40, 15, 60, 35, 10, 70, 50 };
    int n = 8;
    MaxHeap h(n);
    cout << "=== Task 1: Max Heap Insertion + Heap Sort ===\n";
    for (int i = 0; i < n; i++) h.insert(values[i]);
    cout << "Final max heap: ";
    h.print();
    cout << endl;
    h.heapSort();
    return 0;
}
