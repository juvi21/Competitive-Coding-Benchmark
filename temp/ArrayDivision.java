import java.util.Scanner;

public class ArrayDivision {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        int k = scanner.nextInt();
        int[] array = new int[n];
        
        for (int i = 0; i < n; i++) {
            array[i] = scanner.nextInt();
        }
        
        System.out.println(minimizeMaxSubarraySum(array, n, k));
    }
    
    private static long minimizeMaxSubarraySum(int[] array, int n, int k) {
        long left = 0;
        long right = 0;
        
        for (int num : array) {
            left = Math.max(left, num);
            right += num;
        }
        
        while (left < right) {
            long mid = left + (right - left) / 2;
            if (canDivide(array, n, k, mid)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        
        return left;
    }
    
    private static boolean canDivide(int[] array, int n, int k, long maxSum) {
        int subarrayCount = 1;
        long currentSum = 0;
        
        for (int num : array) {
            if (currentSum + num > maxSum) {
                subarrayCount++;
                currentSum = num;
                if (subarrayCount > k) {
                    return false;
                }
            } else {
                currentSum += num;
            }
        }
        
        return true;
    }
}
