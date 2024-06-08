import java.util.Scanner;

public class BookShopII {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int n = scanner.nextInt();
        int x = scanner.nextInt();
        
        int[] prices = new int[n];
        int[] pages = new int[n];
        int[] copies = new int[n];
        
        for (int i = 0; i < n; i++) {
            prices[i] = scanner.nextInt();
        }
        
        for (int i = 0; i < n; i++) {
            pages[i] = scanner.nextInt();
        }
        
        for (int i = 0; i < n; i++) {
            copies[i] = scanner.nextInt();
        }
        
        int[] dp = new int[x + 1];
        
        for (int i = 0; i < n; i++) {
            for (int c = 1; c <= copies[i]; c++) {
                for (int j = x; j >= prices[i]; j--) {
                    dp[j] = Math.max(dp[j], dp[j - prices[i]] + pages[i]);
                }
            }
        }
        
        System.out.println(dp[x]);
    }
}
