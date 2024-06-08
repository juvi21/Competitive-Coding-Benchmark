import java.util.HashMap;
import java.util.Map;

public class BitSubstrings {

    public static void main(String[] args) {
        String s = "101"; // Example input

        int n = s.length();
        int[] result = new int[n + 1];

        // HashMap to store the frequency of prefix sums
        Map<Integer, Integer> prefixMap = new HashMap<>();
        prefixMap.put(0, 1); // Base case: prefix sum of 0 before starting

        int onesCount = 0;

        for (int i = 0; i < n; i++) {
            // Update the number of ones
            if (s.charAt(i) == '1') {
                onesCount++;
            }

            // Check for all possible k from 0 to current onesCount
            for (int k = 0; k <= onesCount; k++) {
                // If there exists a prefix with sum of (onesCount - k)
                if (prefixMap.containsKey(onesCount - k)) {
                    result[k] += prefixMap.get(onesCount - k);
                }
            }

            // Update the prefix map
            prefixMap.put(onesCount, prefixMap.getOrDefault(onesCount, 0) + 1);
        }

        // Print the results
        for (int res : result) {
            System.out.print(res + " ");
        }
    }
}
