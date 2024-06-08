import java.util.Scanner;

public class BookShop {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int n = scanner.nextInt(); // number of books
        int x = scanner.nextInt(); // maximum total price
        
        int[] prices = new int[n];
        int[] pages = new int[n];
        
        for (int i = 0; i < n; i++) {
            prices[i] = scanner.nextInt();
        }
        
        for (int i = 0; i < n; i++) {
            pages[i] = scanner.nextInt();
        }
        
        // Dynamic programming array to keep track of maximum pages for each price
        int[] dp = new int[x + 1];
        
        // Process each book
        for (int i = 0; i < n; i++) {
            int price = prices[i];
            int page = pages[i];
            
            // Update dp array in reverse order to avoid using the same book more than once
            for (int j = x; j >= price; j--) {
                dp[j] = Math.max(dp[j], dp[j - price] + page);
            }
        }
        
        // The answer is the maximum number of pages we can get with total price up to x
        System.out.println(dp[x]);
        
        scanner.close();
    }
}
