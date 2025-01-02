#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <set>

using namespace std;

unordered_map<char, vector<char>> createGraph(const vector<vector<int>> &matrix, const vector<char> &nodes) {
    unordered_map<char, vector<char>> graph;
    for (size_t i = 0; i < nodes.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            if (matrix[i][j] == 1) {
                graph[nodes[i]].push_back(nodes[j]);
            }
        }
    }
    return graph;
}

vector<char> bfs(const unordered_map<char, vector<char>> &graph, char start) {
    vector<char> visited;
    queue<char> q;
    set<char> seen;

    q.push(start);
    seen.insert(start);

    while (!q.empty()) {
        char node = q.front();
        q.pop();
        visited.push_back(node);

        for (char neighbor : graph.at(node)) {
            if (seen.find(neighbor) == seen.end()) {
                q.push(neighbor);
                seen.insert(neighbor);
            }
        }
    }

    return visited;
}

vector<char> dfs(const unordered_map<char, vector<char>> &graph, char start) {
    vector<char> visited;
    set<char> visitedSet;
    vector<char> stack = {start};

    while (!stack.empty()) {
        char node = stack.back();
        stack.pop_back();

        if (visitedSet.find(node) == visitedSet.end()) {
            visitedSet.insert(node);
            visited.push_back(node);

            for (auto it = graph.at(node).rbegin(); it != graph.at(node).rend(); ++it) {
                if (visitedSet.find(*it) == visitedSet.end()) {
                    stack.push_back(*it);
                }
            }
        }
    }

    return visited;
}

int main() {
    vector<char> nodes = {'a', 'b', 'c', 'd', 'e', 'g', 'h'};
    vector<vector<int>> matrix = {
        {0, 1, 0, 1, 1, 0, 1},
        {0, 0, 1, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 1},
        {1, 0, 1, 0, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 1},
        {1, 1, 1, 0, 1, 0, 1},
        {0, 0, 0, 0, 1, 0, 0}
    };

    unordered_map<char, vector<char>> graph = createGraph(matrix, nodes);

    cout << "Graph:" << endl;
    for (const auto &pair : graph) {
        cout << pair.first << ": ";
        for (char neighbor : pair.second) {
            cout << neighbor << " ";
        }
        cout << endl;
    }

    char startNode = 'a';
    cout << "\nBFS " << startNode << ": ";
    vector<char> bfsResult = bfs(graph, startNode);
    for (char node : bfsResult) {
        cout << node << " ";
    }

    cout << "\nDFS " << startNode << ": ";
    vector<char> dfsResult = dfs(graph, startNode);
    for (char node : dfsResult) {
        cout << node << " ";
    }

    return 0;
}
