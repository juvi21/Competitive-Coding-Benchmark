import java.util.*;

public class RectangleUnionArea {

    static class Event implements Comparable<Event> {
        int x, y1, y2, type;
        Event(int x, int y1, int y2, int type) {
            this.x = x;
            this.y1 = y1;
            this.y2 = y2;
            this.type = type;
        }
        @Override
        public int compareTo(Event other) {
            if (this.x != other.x) return this.x - other.x;
            return this.type - other.type;
        }
    }

    static class SegmentTree {
        int[] count;
        int[] length;
        int[] yCoords;

        public SegmentTree(int n, int[] yCoords) {
            this.count = new int[4 * n];
            this.length = new int[4 * n];
            this.yCoords = yCoords;
        }

        public void update(int node, int start, int end, int l, int r, int value) {
            if (start > end || start > r || end < l) return;
            if (start >= l && end <= r) {
                count[node] += value;
            } else {
                int mid = (start + end) / 2;
                update(2 * node, start, mid, l, r, value);
                update(2 * node + 1, mid + 1, end, l, r, value);
            }
            if (count[node] > 0) {
                length[node] = yCoords[end + 1] - yCoords[start];
            } else if (start == end) {
                length[node] = 0;
            } else {
                length[node] = length[2 * node] + length[2 * node + 1];
            }
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        Event[] events = new Event[2 * n];
        Set<Integer> ySet = new HashSet<>();

        for (int i = 0; i < n; i++) {
            int x1 = scanner.nextInt();
            int y1 = scanner.nextInt();
            int x2 = scanner.nextInt();
            int y2 = scanner.nextInt();
            events[2 * i] = new Event(x1, y1, y2, 1);
            events[2 * i + 1] = new Event(x2, y1, y2, -1);
            ySet.add(y1);
            ySet.add(y2);
        }

        int[] yCoords = ySet.stream().sorted().mapToInt(Integer::intValue).toArray();
        Map<Integer, Integer> yIndex = new HashMap<>();
        for (int i = 0; i < yCoords.length; i++) {
            yIndex.put(yCoords[i], i);
        }

        Arrays.sort(events);

        SegmentTree segmentTree = new SegmentTree(yCoords.length, yCoords);
        long totalArea = 0;
        for (int i = 0; i < events.length; i++) {
            if (i > 0) {
                totalArea += (long) segmentTree.length[1] * (events[i].x - events[i - 1].x);
            }
            segmentTree.update(1, 0, yCoords.length - 2, yIndex.get(events[i].y1), yIndex.get(events[i].y2) - 1, events[i].type);
        }

        System.out.println(totalArea);
    }
}
