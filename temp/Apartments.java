import java.util.*;

public class Apartments {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Read n, m, and k
        int n = scanner.nextInt();
        int m = scanner.nextInt();
        int k = scanner.nextInt();

        // Read desired apartment sizes of applicants
        int[] applicants = new int[n];
        for (int i = 0; i < n; i++) {
            applicants[i] = scanner.nextInt();
        }

        // Read sizes of available apartments
        int[] apartments = new int[m];
        for (int i = 0; i < m; i++) {
            apartments[i] = scanner.nextInt();
        }

        // Sort both arrays
        Arrays.sort(applicants);
        Arrays.sort(apartments);

        // Two pointers technique
        int i = 0, j = 0;
        int count = 0;
        
        while (i < n && j < m) {
            if (apartments[j] < applicants[i] - k) {
                // Apartment is too small, move to the next apartment
                j++;
            } else if (apartments[j] > applicants[i] + k) {
                // Apartment is too big, move to the next applicant
                i++;
            } else {
                // Apartment is suitable
                count++;
                i++;
                j++;
            }
        }

        // Output the result
        System.out.println(count);

        scanner.close();
    }
}
