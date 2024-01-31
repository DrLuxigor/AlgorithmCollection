from graphs.graphs import *

n_nodes = 3
graph = Graph()
for i in range(n_nodes):
    graph.nodes.append(Node(node_id=i+1, node_name=f'Node_{i+1}'))

graph.edges.append(Edge(1, 2, 1))
graph.edges.append(Edge(1, 3, 1))
graph.edges.append(Edge(1, 1, 1))

n1_neighbors = graph.neighbors(graph.nodes[0], return_ids=True)
n2_neighbors = graph.neighbors(graph.nodes[1], return_ids=True)
print(n1_neighbors)
print(n2_neighbors)
