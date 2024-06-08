import java.util.Scanner;

public class BinomialCoefficients {
    static final int MOD = 1000000007;
    static final int MAX = 1000000;
    static long[] fact = new long[MAX + 1];
    static long[] invFact = new long[MAX + 1];

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();

        // Precompute factorials and their inverses
        precomputeFactorials();

        // Process each query
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < n; i++) {
            int a = scanner.nextInt();
            int b = scanner.nextInt();
            sb.append(binomialCoefficient(a, b)).append("\n");
        }

        // Output all results
        System.out.print(sb.toString());
        scanner.close();
    }

    private static void precomputeFactorials() {
        fact[0] = 1;
        for (int i = 1; i <= MAX; i++) {
            fact[i] = fact[i - 1] * i % MOD;
        }

        invFact[MAX] = modInverse(fact[MAX], MOD);
        for (int i = MAX - 1; i >= 0; i--) {
            invFact[i] = invFact[i + 1] * (i + 1) % MOD;
        }
    }

    private static long modInverse(long a, int mod) {
        return power(a, mod - 2, mod);
    }

    private static long power(long a, long b, int mod) {
        long res = 1;
        while (b > 0) {
            if ((b & 1) == 1) {
                res = res * a % mod;
            }
            a = a * a % mod;
            b >>= 1;
        }
        return res;
    }

    private static long binomialCoefficient(int a, int b) {
        if (b > a) return 0;
        return fact[a] * invFact[b] % MOD * invFact[a - b] % MOD;
    }
}
