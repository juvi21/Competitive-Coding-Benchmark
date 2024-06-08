import java.util.Scanner;

public class AnotherGame {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        int t = sc.nextInt();  // number of test cases
        
        for (int i = 0; i < t; i++) {
            int n = sc.nextInt();  // number of heaps
            long totalCoins = 0;  // to store the sum of coins in each heap
            
            for (int j = 0; j < n; j++) {
                totalCoins += sc.nextInt();
            }
            
            // Determine the winner
            if (totalCoins % 2 == 1) {
                System.out.println("first");
            } else {
                System.out.println("second");
            }
        }
        
        sc.close();
    }
}
