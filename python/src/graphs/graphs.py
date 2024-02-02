class Graph:
    def __init__(self):
        self.nodes = []
        self.edges = []

    def neighbors(self, node, return_ids=False):
        ids = [e.dest for e in self.edges if e.source == node.id]
        if return_ids:
            return ids
        return [n for n in self.nodes if n.id in ids]

    def find_parent(self, parent, i):
        if parent[i] == i:
            return i
        return self.find_parent(parent, parent[i])

    def union(self, parent, rank, x, y):
        root_x = self.find_parent(parent, x)
        root_y = self.find_parent(parent, y)

        if rank[root_x] < rank[root_y]:
            parent[root_x] = root_y
        elif rank[root_x] > rank[root_y]:
            parent[root_y] = root_x
        else:
            parent[root_y] = root_x
            rank[root_x] += 1

    def kruskal_mst(self):
        result = []
        self.edges = sorted(self.edges, key=lambda edge: edge.cost)

        parent = {}
        rank = {}

        for node in self.nodes:
            parent[node.id] = node.id
            rank[node.id] = 0

        for edge in self.edges:
            source_root = self.find_parent(parent, edge.source)
            dest_root = self.find_parent(parent, edge.dest)

            if source_root != dest_root:
                result.append(edge)
                self.union(parent, rank, source_root, dest_root)

        return result


class Node:
    def __init__(self, node_id, node_name):
        self.id = node_id
        self.name = node_name


class Edge:
    def __init__(self, source, dest, cost):
        self.source = source
        self.dest = dest
        self.cost = cost
