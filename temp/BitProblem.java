import java.util.*;

public class BitProblem {
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int n = scanner.nextInt();
        int[] arr = new int[n];
        for (int i = 0; i < n; i++) {
            arr[i] = scanner.nextInt();
        }
        scanner.close();
        
        int maxVal = 1000000;
        
        // Precompute counts of each number in the array
        int[] count = new int[maxVal + 1];
        for (int i = 0; i < n; i++) {
            count[arr[i]]++;
        }
        
        // Precompute the prefix sums for the bitwise AND and OR operations
        int[] prefixAnd = new int[maxVal + 1];
        int[] prefixOr = new int[maxVal + 1];
        
        for (int i = 1; i <= maxVal; i++) {
            for (int j = i; j <= maxVal; j += i) {
                prefixAnd[i] += count[j];
            }
        }
        
        for (int i = 1; i <= maxVal; i++) {
            for (int j = i; j <= maxVal; j += i) {
                if ((i & j) != 0) {
                    prefixOr[i] += count[j];
                }
            }
        }
        
        // Calculate results for each element in the array
        for (int i = 0; i < n; i++) {
            int x = arr[i];
            int countXOr = 0;
            
            for (int j = 1; j <= maxVal; j++) {
                if ((x & j) != 0) {
                    countXOr += count[j];
                }
            }
            
            System.out.println(prefixAnd[x] + " " + count[arr[i]] + " " + countXOr);
        }
    }
}
