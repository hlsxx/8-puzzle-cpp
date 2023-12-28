#include <map>
#include <queue>
#include <vector>
#include <iostream>

class Graph {
private:
  std::vector<std::vector<int>> adjList;
  std::map<int, bool> visited;

public:
  Graph(int nodesCount) {
    this->adjList.resize(nodesCount);
  }

  void addEdge(int parent, int current){
    this->adjList[parent].push_back(current);
  }

  void BFS(int curentNode) {
    // Create queue for nodes
    std::queue<int> queue;

    // Set node as visited
    this->visited[curentNode] = true;

    // Push into queue
    queue.push(curentNode);

    // Loop through queue
    while (!queue.empty()) {
      // Get first node from queue
      curentNode = queue.front();

      std::cout << curentNode << "\n";
      // Pop from queue node
      queue.pop();

      // Loop poped node neighbors
      for(auto neighbor: this->adjList[curentNode]) {
        // If not visisted push into queue and set as visited
        if (!this->visited[neighbor]) {
          visited[neighbor] = true;
          queue.push(neighbor);
        }
      }
    }
  }
};

int main() {
  Graph graph = Graph(7);

  // Test case
  graph.addEdge(0, 1);
  graph.addEdge(0, 2);
  graph.addEdge(0, 3);
  graph.addEdge(1, 4);
  graph.addEdge(2, 5);
  graph.addEdge(3, 6);
  graph.addEdge(4, 5);
  graph.addEdge(6, 5);

  graph.BFS(0);
}


