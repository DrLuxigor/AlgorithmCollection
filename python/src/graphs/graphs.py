class Graph:
    def __init__(self):
        self.nodes = []
        self.edges = []

    def neighbors(self, node, return_ids=False):
        ids = [e.dest for e in self.edges if e.source == node.id]
        if return_ids:
            return ids
        return [n for n in self.nodes if n.id in ids]

    def min_spanning_tree(self):
        return


class Node:
    def __init__(self, node_id, node_name):
        self.id = node_id
        self.name = node_name


class Edge:
    def __init__(self, source, dest, cost):
        self.source = source
        self.dest = dest
        self.cost = cost
