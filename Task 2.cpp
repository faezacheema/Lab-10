#include <iostream>
using namespace std;

// Generic heap: isMax = true -> max heap, false -> min heap
class Heap {
    int* data;
    int size;
    bool isMax;
    bool before(int a, int b) { return isMax ? a > b : a < b; }
public:
    Heap(int cap, bool max) : size(0), isMax(max) { data = new int[cap]; }
    ~Heap() { delete[] data; }
    int getSize() { return size; }
    int top() { return data[0]; }

    void push(int v) {
        int i = size++;
        data[i] = v;
        while (i > 0 && before(data[i], data[(i - 1) / 2])) {
            int p = (i - 1) / 2;
            int t = data[p]; data[p] = data[i]; data[i] = t;
            i = p;
        }
    }
    int pop() {
        int root = data[0];
        data[0] = data[--size];
        int i = 0;
        while (true) {
            int best = i, l = 2 * i + 1, r = 2 * i + 2;
            if (l < size && before(data[l], data[best])) best = l;
            if (r < size && before(data[r], data[best])) best = r;
            if (best == i) break;
            int t = data[i]; data[i] = data[best]; data[best] = t;
            i = best;
        }
        return root;
    }
};

// Running median: lower half in max heap, upper half in min heap
class MedianTracker {
    Heap low, high;
public:
    MedianTracker(int cap) : low(cap, true), high(cap, false) {}
    void add(int x) {
        if (low.getSize() == 0 || x <= low.top()) low.push(x);
        else high.push(x);
        // rebalance so sizes differ by at most 1 (low may hold the extra)
        if (low.getSize() > high.getSize() + 1) high.push(low.pop());
        else if (high.getSize() > low.getSize()) low.push(high.pop());
    }
    double median() {
        if (low.getSize() > high.getSize()) return low.top();
        return (low.top() + high.top()) / 2.0;
    }
    int lowTop() { return low.top(); }
    int highTop() { return high.getSize() ? high.top() : -1; }
    int lowSize() { return low.getSize(); }
    int highSize() { return high.getSize(); }
};

int main() {
    int waits[] = { 45, 20, 60, 15, 30, 90, 10, 55 };
    int n = 8;
    const double THRESHOLD = 35.0;
    MedianTracker mt(n);
    cout << "=== Task 2: ER Wait-Time Monitor (Max Heap + Min Heap) ===\n";
    cout << "Arrival | Wait | LowMax | HighMin | Median | Status\n";
    for (int i = 0; i < n; i++) {
        mt.add(waits[i]);
        double m = mt.median();
        cout << "   " << i + 1 << "    |  " << waits[i] << "  |   " << mt.lowTop()
            << "   |   ";
        if (mt.highSize()) cout << mt.highTop(); else cout << "-";
        cout << "    |  " << m << "  | "
            << (m > THRESHOLD ? "ALERT: call extra staff" : "Normal") << endl;
    }
    return 0;
}
