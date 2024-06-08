import java.util.Scanner;

public class BinarySubsequences {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        scanner.close();

        // Find the smallest k such that 2^k - 1 >= n
        int k = 1;
        while ((1 << k) - 1 < n) {
            k++;
        }

        // Generate any bit string of length k. For simplicity, we use '1's followed by '0's
        StringBuilder bitString = new StringBuilder();
        for (int i = 0; i < k; i++) {
            bitString.append((i & 1) == 0 ? '1' : '0'); // Alternating pattern
        }

        System.out.println(bitString.toString());
    }
}
