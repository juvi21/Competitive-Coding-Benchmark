import java.util.Scanner;

public class AppleDivision {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        int[] weights = new int[n];
        for (int i = 0; i < n; i++) {
            weights[i] = scanner.nextInt();
        }
        scanner.close();
        
        long totalSum = 0;
        for (int weight : weights) {
            totalSum += weight;
        }

        long minDifference = Long.MAX_VALUE;
        
        // There are 2^n possible subsets
        int totalSubsets = 1 << n;
        
        for (int i = 0; i < totalSubsets; i++) {
            long subsetSum = 0;
            for (int j = 0; j < n; j++) {
                if ((i & (1 << j)) != 0) {
                    subsetSum += weights[j];
                }
            }
            long currentDifference = Math.abs((totalSum - subsetSum) - subsetSum);
            minDifference = Math.min(minDifference, currentDifference);
        }
        
        System.out.println(minDifference);
    }
}
