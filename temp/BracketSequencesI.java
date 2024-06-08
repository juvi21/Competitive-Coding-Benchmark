import java.util.Scanner;

public class BracketSequencesI {
    static final int MOD = 1000000007;

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        sc.close();

        if (n % 2 != 0) {
            // An odd length cannot form a valid bracket sequence
            System.out.println(0);
            return;
        }

        // Number of pairs of brackets
        int k = n / 2;

        // Array to store catalan numbers
        long[] catalan = new long[k + 1];

        // Initializing the first value
        catalan[0] = 1;

        // Calculate the catalan numbers using dynamic programming
        for (int i = 1; i <= k; i++) {
            catalan[i] = 0;
            for (int j = 0; j < i; j++) {
                catalan[i] = (catalan[i] + catalan[j] * catalan[i - 1 - j]) % MOD;
            }
        }

        // The answer is the k-th Catalan number
        System.out.println(catalan[k]);
    }
}
