import java.util.*;
import java.io.*;

public class Main {
    static class Event implements Comparable<Event> {
        int x, y1, y2, type;
        Event(int x, int y1, int y2, int type) {
            this.x = x;
            this.y1 = y1;
            this.y2 = y2;
            this.type = type;
        }
        public int compareTo(Event e) {
            return this.x - e.x;
        }
    }

    static class SegmentTree {
        int[] count, length;
        int[] yCoords;
        int n;

        SegmentTree(int[] yCoords) {
            this.yCoords = yCoords;
            this.n = yCoords.length;
            count = new int[4 * n];
            length = new int[4 * n];
        }

        void update(int start, int end, int l, int r, int idx, int val) {
            if (start >= r || end <= l) return;
            if (start >= l && end <= r) {
                count[idx] += val;
            } else {
                int mid = (start + end) / 2;
                update(start, mid, l, r, 2 * idx + 1, val);
                update(mid, end, l, r, 2 * idx + 2, val);
            }
            if (count[idx] > 0) {
                length[idx] = yCoords[end] - yCoords[start];
            } else if (end - start > 1) {
                length[idx] = length[2 * idx + 1] + length[2 * idx + 2];
            } else {
                length[idx] = 0;
            }
        }

        int query() {
            return length[0];
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(br.readLine().trim());
        List<Event> events = new ArrayList<>();
        Set<Integer> ySet = new HashSet<>();

        for (int i = 0; i < n; i++) {
            String[] tokens = br.readLine().trim().split(" ");
            int x1 = Integer.parseInt(tokens[0]);
            int y1 = Integer.parseInt(tokens[1]);
            int x2 = Integer.parseInt(tokens[2]);
            int y2 = Integer.parseInt(tokens[3]);
            events.add(new Event(x1, y1, y2, 1));
            events.add(new Event(x2, y1, y2, -1));
            ySet.add(y1);
            ySet.add(y2);
        }

        // Create sorted y-coordinate array
        int[] yCoords = ySet.stream().mapToInt(Integer::intValue).toArray();
        Arrays.sort(yCoords);

        // Create segment tree
        SegmentTree segmentTree = new SegmentTree(yCoords);

        // Sort events by x-coordinate
        Collections.sort(events);

        // Sweep line algorithm
        long totalArea = 0;
        int prevX = events.get(0).x;
        for (Event e : events) {
            int curX = e.x;
            int y1 = Arrays.binarySearch(yCoords, e.y1);
            int y2 = Arrays.binarySearch(yCoords, e.y2);
            totalArea += (long) segmentTree.query() * (curX - prevX);
            segmentTree.update(0, yCoords.length - 1, y1, y2, 0, e.type);
            prevX = curX;
        }

        System.out.println(totalArea);
    }
}
