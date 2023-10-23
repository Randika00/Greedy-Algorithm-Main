import math


def PrintPath(path):
    for i in path:
        print(i + 1, end=" ")


class WeightedGraph:
    def __init__(self, vertices):
        self.vertices = vertices
        self.graph = [[0 for column in range(vertices)] for row in range(vertices)]

    def GetMinimumInPath(self, path: list, src):
        minimum = 1000
        for i in range(len(path) - 1):
            minimum = min(self.graph[path[i]][path[i + 1]], minimum)
        return minimum

    def Dijkstra_max(self, src):
        dist = [float('-inf')] * self.vertices
        Q = [i for i in range(self.vertices)]
        dist[src] = 0
        path = {}
        while Q:
            u = max(Q, key=lambda x: dist[x])
            Q.remove(u)
            for v in range(self.vertices):
                if self.graph[u][v] > 0:
                    if dist[v] < dist[u] + self.graph[u][v]:
                        dist[v] = dist[u] + self.graph[u][v]
                        path[v] = path.get(u, [u]) + [v]
        return path


def take_input():
    foreign_students = int(input("Enter the number of foreign students : "))
    aiesec_students = int(input("Enter the number of AIESEC students : "))
    (N, R) = map(int, input().split())
    g = WeightedGraph(N)
    for i in range(R):
        (u, v, w) = map(int, input("Enter the C1 C2 P : ").split())
        g.graph[u - 1][v - 1] = w
    (src, dest, tourist) = map(int, input().split())
    path = g.Dijkstra_max(src - 1)
    PrintPath(path[dest - 1])
    number_of_trips = math.ceil((foreign_students + aiesec_students) / g.GetMinimumInPath(path[dest - 1], 0))
    print("\n")
    print(number_of_trips)
    return g


g = take_input()
