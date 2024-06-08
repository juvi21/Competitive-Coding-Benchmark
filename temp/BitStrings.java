import java.util.Scanner;

public class BitStrings {
    // Define the modulo value
    private static final int MOD = 1000000007;

    // Function to perform modular exponentiation
    private static long modularExponentiation(long base, long exp, int mod) {
        long result = 1;
        while (exp > 0) {
            if ((exp & 1) == 1) {
                result = (result * base) % mod;
            }
            base = (base * base) % mod;
            exp >>= 1;
        }
        return result;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        sc.close();

        // Calculate 2^n % MOD
        long result = modularExponentiation(2, n, MOD);

        // Print the result
        System.out.println(result);
    }
}
