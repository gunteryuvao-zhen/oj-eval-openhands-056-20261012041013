#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an interval
struct Interval {
    int l, r;
    
    Interval(int left, int right) : l(left), r(right) {}
    
    // Define ordering for set
    bool operator<(const Interval& other) const {
        return l < other.l;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    // Use a set to store intervals, ordered by left endpoint
    set<Interval> intervals;
    
    for (int i = 0; i < n; i++) {
        char op;
        cin >> op;
        
        if (op == 'A') {
            int l, r;
            cin >> l >> r;
            
            // Find all intervals that overlap with [l, r]
            // An interval [a, b] overlaps with [l, r] if a <= r and l <= b
            vector<Interval> toRemove;
            
            // Find the first interval with left endpoint >= l - (max_length)
            // Since r <= 10^5, we can use l as a starting point
            auto it = intervals.lower_bound(Interval(l - 100000, l - 100000));
            
            // Check all potential overlapping intervals
            while (it != intervals.end()) {
                if (it->l > r) break; // No more overlaps possible
                
                // Check if current interval overlaps with [l, r]
                if (it->r >= l) { // Overlap condition: it->l <= r && it->r >= l
                    toRemove.push_back(*it);
                }
                ++it;
            }
            
            // Remove all overlapping intervals
            for (const auto& interval : toRemove) {
                intervals.erase(interval);
            }
            
            // Add the new mandatory class as an activity
            intervals.insert(Interval(l, r));
            
            // Output the number of deleted activities
            cout << toRemove.size() << '\n';
        } else if (op == 'B') {
            // Output the current number of activities
            cout << intervals.size() << '\n';
        }
    }
    
    return 0;
}