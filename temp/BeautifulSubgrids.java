import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;

public class BeautifulSubgrids {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        
        int n = Integer.parseInt(br.readLine());
        int[][] grid = new int[n][n];
        
        for (int i = 0; i < n; i++) {
            String line = br.readLine();
            for (int j = 0; j < n; j++) {
                grid[i][j] = line.charAt(j) - '0';
            }
        }
        
        long count = 0;

        // Iterate over all pairs of rows
        for (int row1 = 0; row1 < n; row1++) {
            for (int row2 = row1 + 1; row2 < n; row2++) {
                int commonBlackCols = 0;

                for (int col = 0; col < n; col++) {
                    if (grid[row1][col] == 1 && grid[row2][col] == 1) {
                        commonBlackCols++;
                    }
                }

                if (commonBlackCols > 1) {
                    count += (long) commonBlackCols * (commonBlackCols - 1) / 2;
                }
            }
        }
        
        System.out.println(count);
    }
}
