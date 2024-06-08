import java.util.Scanner;

public class ApplesAndBananas {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        // Read k, n, m
        int k = sc.nextInt();
        int n = sc.nextInt();
        int m = sc.nextInt();
        
        // Read apples weights
        int[] apples = new int[n];
        for (int i = 0; i < n; i++) {
            apples[i] = sc.nextInt();
        }
        
        // Read bananas weights
        int[] bananas = new int[m];
        for (int i = 0; i < m; i++) {
            bananas[i] = sc.nextInt();
        }

        // Frequency arrays
        int[] appleCount = new int[k + 1];
        int[] bananaCount = new int[k + 1];
        
        // Fill frequency arrays
        for (int i = 0; i < n; i++) {
            appleCount[apples[i]]++;
        }
        
        for (int i = 0; i < m; i++) {
            bananaCount[bananas[i]]++;
        }
        
        // Result array for sums from 2 to 2k
        int[] result = new int[2 * k + 1];
        
        // Calculate the number of ways for each possible sum
        for (int i = 1; i <= k; i++) {
            for (int j = 1; j <= k; j++) {
                result[i + j] += appleCount[i] * bananaCount[j];
            }
        }
        
        // Print the results for sums from 2 to 2k
        for (int w = 2; w <= 2 * k; w++) {
            System.out.print(result[w] + " ");
        }
    }
}
