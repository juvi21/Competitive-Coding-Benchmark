import java.util.*;

public class BitInversions {
    
    static class Interval implements Comparable<Interval> {
        int start, end;
        
        Interval(int start, int end) {
            this.start = start;
            this.end = end;
        }
        
        int length() {
            return end - start + 1;
        }
        
        @Override
        public int compareTo(Interval other) {
            if (this.start != other.start) {
                return Integer.compare(this.start, other.start);
            }
            return Integer.compare(this.end, other.end);
        }
    }
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        char[] bits = scanner.next().toCharArray();
        int n = bits.length;
        int m = scanner.nextInt();
        int[] changes = new int[m];
        for (int i = 0; i < m; i++) {
            changes[i] = scanner.nextInt() - 1; // Convert to 0-based index
        }
        scanner.close();
        
        TreeSet<Interval> intervals = new TreeSet<>();
        int maxLength = 0;
        
        // Initialize intervals
        int start = 0;
        for (int i = 1; i <= n; i++) {
            if (i == n || bits[i] != bits[start]) {
                Interval interval = new Interval(start, i - 1);
                intervals.add(interval);
                maxLength = Math.max(maxLength, interval.length());
                start = i;
            }
        }
        
        // Process changes
        StringBuilder result = new StringBuilder();
        for (int changeIdx : changes) {
            bits[changeIdx] = (bits[changeIdx] == '0') ? '1' : '0';
            Interval left = intervals.floor(new Interval(changeIdx, changeIdx));
            Interval right = intervals.ceiling(new Interval(changeIdx, changeIdx));
            
            if (left != null && left.end < changeIdx) left = null;
            if (right != null && right.start > changeIdx) right = null;
            
            if (left != null) intervals.remove(left);
            if (right != null) intervals.remove(right);
            
            if (left != null && right != null && bits[left.end] == bits[right.start] && left.end + 1 == right.start) {
                Interval merged = new Interval(left.start, right.end);
                intervals.add(merged);
                maxLength = Math.max(maxLength, merged.length());
            } else {
                if (left != null) {
                    Interval newLeft = new Interval(left.start, changeIdx - 1);
                    if (newLeft.length() > 0) {
                        intervals.add(newLeft);
                        maxLength = Math.max(maxLength, newLeft.length());
                    }
                    Interval newSingle = new Interval(changeIdx, changeIdx);
                    intervals.add(newSingle);
                    maxLength = Math.max(maxLength, newSingle.length());
                }
                if (right != null) {
                    Interval newRight = new Interval(changeIdx + 1, right.end);
                    if (newRight.length() > 0) {
                        intervals.add(newRight);
                        maxLength = Math.max(maxLength, newRight.length());
                    }
                    Interval newSingle = new Interval(changeIdx, changeIdx);
                    intervals.add(newSingle);
                    maxLength = Math.max(maxLength, newSingle.length());
                }
                if (left == null && right == null) {
                    Interval newSingle = new Interval(changeIdx, changeIdx);
                    intervals.add(newSingle);
                    maxLength = Math.max(maxLength, newSingle.length());
                }
            }
            
            result.append(maxLength).append(" ");
        }
        
        System.out.println(result.toString().trim());
    }
}
