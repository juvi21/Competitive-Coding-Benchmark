import java.util.*;

public class UnionAreaOfRectangles {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        List<Event> events = new ArrayList<>();
        Set<Integer> yCoords = new TreeSet<>();
        
        for (int i = 0; i < n; i++) {
            int x1 = sc.nextInt();
            int y1 = sc.nextInt();
            int x2 = sc.nextInt();
            int y2 = sc.nextInt();
            events.add(new Event(x1, y1, y2, 1));
            events.add(new Event(x2, y1, y2, -1));
            yCoords.add(y1);
            yCoords.add(y2);
        }

        List<Integer> yList = new ArrayList<>(yCoords);
        Collections.sort(yList);
        Map<Integer, Integer> yMap = new HashMap<>();
        for (int i = 0; i < yList.size(); i++) {
            yMap.put(yList.get(i), i);
        }

        Collections.sort(events);

        SegmentTree segmentTree = new SegmentTree(yList.size());
        long totalArea = 0;
        int prevX = events.get(0).x;

        for (Event event : events) {
            int currX = event.x;
            totalArea += (long) segmentTree.query() * (currX - prevX);
            segmentTree.update(yMap.get(event.y1), yMap.get(event.y2), event.type);
            prevX = currX;
        }

        System.out.println(totalArea);
    }
}

class Event implements Comparable<Event> {
    int x, y1, y2, type;

    Event(int x, int y1, int y2, int type) {
        this.x = x;
        this.y1 = y1;
        this.y2 = y2;
        this.type = type;
    }

    public int compareTo(Event other) {
        if (this.x != other.x) {
            return this.x - other.x;
        }
        return this.type - other.type; // Ensure start event comes before end event at same x
    }
}

class SegmentTree {
    private int[] count, length;
    private int n;

    SegmentTree(int n) {
        this.n = n;
        count = new int[4 * n];
        length = new int[4 * n];
    }

    public void update(int l, int r, int type) {
        update(0, 0, n - 1, l, r - 1, type);
    }

    private void update(int node, int start, int end, int l, int r, int type) {
        if (start > r || end < l) {
            return;
        }
        if (start >= l && end <= r) {
            count[node] += type;
        } else {
            int mid = (start + end) / 2;
            update(2 * node + 1, start, mid, l, r, type);
            update(2 * node + 2, mid + 1, end, l, r, type);
        }
        if (count[node] > 0) {
            length[node] = end - start + 1;
        } else if (start == end) {
            length[node] = 0;
        } else {
            length[node] = length[2 * node + 1] + length[2 * node + 2];
        }
    }

    public int query() {
        return length[0];
    }
}
