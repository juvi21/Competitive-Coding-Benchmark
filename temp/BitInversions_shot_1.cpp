#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

// Segment structure to store the start and end of a segment
struct Segment {
    int start, end;
    Segment(int s, int e) : start(s), end(e) {}
    bool operator<(const Segment& other) const {
        return start < other.start;
    }
};

int main() {
    string bitString;
    cin >> bitString;
    int n = bitString.size();

    int m;
    cin >> m;

    vector<int> changes(m);
    for (int i = 0; i < m; ++i) {
        cin >> changes[i];
        changes[i]--; // Convert to 0-based index
    }

    // Initialize segments
    set<Segment> segments;
    int start = 0;
    while (start < n) {
        int end = start;
        while (end < n && bitString[end] == bitString[start]) {
            end++;
        }
        segments.insert(Segment(start, end - 1));
        start = end;
    }

    // Function to find the longest segment
    auto findLongestSegment = [&]() {
        int longest = 0;
        for (const auto& seg : segments) {
            longest = max(longest, seg.end - seg.start + 1);
        }
        return longest;
    };

    for (int i = 0; i < m; ++i) {
        int pos = changes[i];
        
        // Find the segment containing the position
        auto it = segments.lower_bound(Segment(pos, pos));
        if (it != segments.begin() && (it == segments.end() || it->start > pos)) {
            --it;
        }

        Segment currentSegment = *it;
        segments.erase(it);

        int start1 = currentSegment.start;
        int end1 = pos - 1;
        int start2 = pos + 1;
        int end2 = currentSegment.end;

        // Flip the bit
        bitString[pos] = (bitString[pos] == '0') ? '1' : '0';

        // Reinsert the segments if valid
        if (start1 <= end1) segments.insert(Segment(start1, end1));
        if (start2 <= end2) segments.insert(Segment(start2, end2));

        // Add the new single-bit segment
        segments.insert(Segment(pos, pos));

        // Merge adjacent segments if possible
        auto it1 = segments.find(Segment(start1, end1));
        auto it2 = segments.find(Segment(start2, end2));
        auto itMid = segments.find(Segment(pos, pos));
        
        if (it1 != segments.end() && itMid != segments.end() && bitString[end1] == bitString[pos]) {
            segments.insert(Segment(start1, pos));
            segments.erase(it1);
            segments.erase(itMid);
        } else if (it2 != segments.end() && itMid != segments.end() && bitString[start2] == bitString[pos]) {
            segments.insert(Segment(pos, end2));
            segments.erase(it2);
            segments.erase(itMid);
        }

        // Print the length of the longest segment
        cout << findLongestSegment() << " ";
    }

    return 0;
}
