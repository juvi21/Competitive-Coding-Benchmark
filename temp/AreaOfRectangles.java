import java.util.*;

public class AreaOfRectangles {

    static class Event implements Comparable<Event> {
        int x;
        int y1, y2;
        int type; // 1 for start, -1 for end

        public Event(int x, int y1, int y2, int type) {
            this.x = x;
            this.y1 = y1;
            this.y2 = y2;
            this.type = type;
        }

        @Override
        public int compareTo(Event other) {
            if (this.x != other.x) {
                return this.x - other.x;
            }
            return this.type - other.type;
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        List<Event> events = new ArrayList<>();

        for (int i = 0; i < n; i++) {
            int x1 = scanner.nextInt();
            int y1 = scanner.nextInt();
            int x2 = scanner.nextInt();
            int y2 = scanner.nextInt();
            events.add(new Event(x1, y1, y2, 1)); // start event
            events.add(new Event(x2, y1, y2, -1)); // end event
        }

        Collections.sort(events);

        TreeMap<Integer, Integer> activeIntervals = new TreeMap<>();
        long totalArea = 0;
        int prevX = events.get(0).x;

        for (Event event : events) {
            int currentX = event.x;
            long activeLength = 0;
            int prevY = Integer.MIN_VALUE;

            // Calculate the current total y-length covered by active intervals
            for (Map.Entry<Integer, Integer> entry : activeIntervals.entrySet()) {
                int y = entry.getKey();
                int count = entry.getValue();
                if (count > 0) {
                    if (prevY != Integer.MIN_VALUE) {
                        activeLength += y - prevY;
                    }
                    prevY = y;
                }
            }

            // Update the total area covered so far
            totalArea += activeLength * (currentX - prevX);

            // Update the active intervals based on the current event
            int y1 = event.y1;
            int y2 = event.y2;
            if (event.type == 1) {
                activeIntervals.put(y1, activeIntervals.getOrDefault(y1, 0) + 1);
                activeIntervals.put(y2, activeIntervals.getOrDefault(y2, 0) - 1);
            } else {
                activeIntervals.put(y1, activeIntervals.get(y1) - 1);
                activeIntervals.put(y2, activeIntervals.get(y2) + 1);
            }

            prevX = currentX;
        }

        System.out.println(totalArea);
        scanner.close();
    }
}
