import java.util.Scanner;

public class BracketSequencesII {
    private static final int MOD = 1000000007;

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        String prefix = sc.next();
        int k = prefix.length();

        // Calculate initial balance of the prefix and validate it
        int balance = 0;
        for (char c : prefix.toCharArray()) {
            if (c == '(') {
                balance++;
            } else {
                balance--;
            }
            if (balance < 0) {
                System.out.println(0);
                return;
            }
        }

        // Dynamic programming array
        int[][] dp = new int[n + 1][n + 1];
        dp[k][balance] = 1;

        for (int i = k; i < n; i++) {
            for (int j = 0; j <= n; j++) {
                if (dp[i][j] > 0) {
                    if (j + 1 <= n) {
                        dp[i + 1][j + 1] = (dp[i + 1][j + 1] + dp[i][j]) % MOD;
                    }
                    if (j - 1 >= 0) {
                        dp[i + 1][j - 1] = (dp[i + 1][j - 1] + dp[i][j]) % MOD;
                    }
                }
            }
        }

        // The answer is the number of ways to have a balance of 0 at position n
        System.out.println(dp[n][0]);
    }
}
