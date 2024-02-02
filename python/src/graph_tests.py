from graphs.graphs import *

n_nodes = 5
graph = Graph()
for i in range(n_nodes):
    graph.nodes.append(Node(node_id=i+1, node_name=f'Node_{i+1}'))

graph.edges.append(Edge(1, 2, 3))
graph.edges.append(Edge(2, 1, 3))

graph.edges.append(Edge(2, 3, 3))
graph.edges.append(Edge(3, 2, 3))

graph.edges.append(Edge(3, 4, 3))
graph.edges.append(Edge(4, 3, 3))

graph.edges.append(Edge(4, 5, 3))
graph.edges.append(Edge(5, 4, 3))

graph.edges.append(Edge(2, 4, 4))
graph.edges.append(Edge(4, 2, 4))

mst = graph.kruskal_mst()

for edge in mst:
    print(f"{edge.source} - {edge.dest}: {edge.cost}")