import java.util.Scanner;

public class ArrayDescription {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int MOD = 1000000007;
        
        int n = scanner.nextInt();
        int m = scanner.nextInt();
        int[] x = new int[n];

        for (int i = 0; i < n; i++) {
            x[i] = scanner.nextInt();
        }

        long[][] dp = new long[n][m + 1];

        // Initialize the first row of dp table
        if (x[0] == 0) {
            for (int j = 1; j <= m; j++) {
                dp[0][j] = 1;
            }
        } else {
            dp[0][x[0]] = 1;
        }

        // Fill the dp table
        for (int i = 1; i < n; i++) {
            if (x[i] == 0) {
                for (int j = 1; j <= m; j++) {
                    dp[i][j] = (dp[i-1][j] + (j > 1 ? dp[i-1][j-1] : 0) + (j < m ? dp[i-1][j+1] : 0)) % MOD;
                }
            } else {
                int j = x[i];
                dp[i][j] = (dp[i-1][j] + (j > 1 ? dp[i-1][j-1] : 0) + (j < m ? dp[i-1][j+1] : 0)) % MOD;
            }
        }

        // Calculate the result
        long result = 0;
        for (int j = 1; j <= m; j++) {
            result = (result + dp[n-1][j]) % MOD;
        }

        System.out.println(result);
    }
}
