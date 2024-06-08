import java.util.*;

public class AcyclicGraphEdges {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        int m = scanner.nextInt();
        
        List<List<Integer>> adj = new ArrayList<>();
        List<int[]> edges = new ArrayList<>();
        
        for (int i = 0; i <= n; i++) {
            adj.add(new ArrayList<>());
        }
        
        for (int i = 0; i < m; i++) {
            int a = scanner.nextInt();
            int b = scanner.nextInt();
            adj.get(a).add(b);
            adj.get(b).add(a);
            edges.add(new int[]{a, b});
        }
        
        int[] inDegree = new int[n + 1];
        List<Integer> topoOrder = topologicalSort(n, adj, inDegree);
        
        if (topoOrder.size() != n) {
            System.out.println("Graph is not acyclic");
            return;
        }
        
        Map<Integer, Integer> position = new HashMap<>();
        for (int i = 0; i < topoOrder.size(); i++) {
            position.put(topoOrder.get(i), i);
        }
        
        for (int[] edge : edges) {
            int a = edge[0];
            int b = edge[1];
            if (position.get(a) < position.get(b)) {
                System.out.println(a + " " + b);
            } else {
                System.out.println(b + " " + a);
            }
        }
    }
    
    private static List<Integer> topologicalSort(int n, List<List<Integer>> adj, int[] inDegree) {
        List<Integer> order = new ArrayList<>();
        Queue<Integer> queue = new LinkedList<>();
        
        for (int i = 1; i <= n; i++) {
            for (int v : adj.get(i)) {
                inDegree[v]++;
            }
        }
        
        for (int i = 1; i <= n; i++) {
            if (inDegree[i] == 0) {
                queue.offer(i);
            }
        }
        
        while (!queue.isEmpty()) {
            int u = queue.poll();
            order.add(u);
            
            for (int v : adj.get(u)) {
                inDegree[v]--;
                if (inDegree[v] == 0) {
                    queue.offer(v);
                }
            }
        }
        
        return order;
    }
}
