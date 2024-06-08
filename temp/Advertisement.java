import java.util.Scanner;
import java.util.Stack;

public class Advertisement {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        int[] heights = new int[n];
        
        for (int i = 0; i < n; i++) {
            heights[i] = scanner.nextInt();
        }
        
        System.out.println(maxRectangleArea(heights));
    }
    
    public static int maxRectangleArea(int[] heights) {
        Stack<Integer> stack = new Stack<>();
        int maxArea = 0;
        int index = 0;
        
        while (index < heights.length) {
            if (stack.isEmpty() || heights[stack.peek()] <= heights[index]) {
                stack.push(index++);
            } else {
                int height = heights[stack.pop()];
                int width = stack.isEmpty() ? index : index - stack.peek() - 1;
                maxArea = Math.max(maxArea, height * width);
            }
        }
        
        while (!stack.isEmpty()) {
            int height = heights[stack.pop()];
            int width = stack.isEmpty() ? index : index - stack.peek() - 1;
            maxArea = Math.max(maxArea, height * width);
        }
        
        return maxArea;
    }
}
