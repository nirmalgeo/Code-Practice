def create_clique_graph(G, node1, n):
    if node1 not in G:
        G[node1] = {}
    for i in range(n):
        if i == node1:
            continue
        else:
            (G[node1])[i] = 1
    return G


G= {}
n= 5
for i in range(5):
    create_clique_graph(G,i,5)
print(G)
        
