import java.util.*;

public class BuildingRoads {
    // Adjacency list to represent the graph
    private static List<List<Integer>> adjList;
    // Visited array to keep track of visited cities
    private static boolean[] visited;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt(); // Number of cities
        int m = scanner.nextInt(); // Number of roads
        
        adjList = new ArrayList<>();
        for (int i = 0; i <= n; i++) {
            adjList.add(new ArrayList<>());
        }

        // Read the roads and build the graph
        for (int i = 0; i < m; i++) {
            int a = scanner.nextInt();
            int b = scanner.nextInt();
            adjList.get(a).add(b);
            adjList.get(b).add(a);
        }

        // Initialize visited array
        visited = new boolean[n + 1];

        // List to store the representative city of each connected component
        List<Integer> components = new ArrayList<>();

        for (int i = 1; i <= n; i++) {
            if (!visited[i]) {
                // If the city is not visited, it's a new component
                components.add(i);
                // Perform DFS to mark all cities in this component as visited
                dfs(i);
            }
        }

        // Number of new roads needed is the number of components - 1
        int k = components.size() - 1;
        System.out.println(k);

        // Connect the components with new roads
        for (int i = 1; i < components.size(); i++) {
            System.out.println(components.get(i - 1) + " " + components.get(i));
        }
        
        scanner.close();
    }

    // DFS function to traverse the graph
    private static void dfs(int node) {
        Stack<Integer> stack = new Stack<>();
        stack.push(node);
        while (!stack.isEmpty()) {
            int current = stack.pop();
            if (!visited[current]) {
                visited[current] = true;
                for (int neighbor : adjList.get(current)) {
                    if (!visited[neighbor]) {
                        stack.push(neighbor);
                    }
                }
            }
        }
    }
}
