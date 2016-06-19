#Ring network

def build_ring_network(G, node1,node2):
    if node1 not in G:
        G[node1] = {}
   
    (G[node1])[node2] = 1
    (G[node1])[node2] = 0
    if node2 not in G:
        G[node2] = {}
    #(G[node2])[node1] = 1
    return G


G= {}
n=5
for i in range(n):
    G = build_ring_network(G,i , (i+1)%n)

print (G)
#print (G[1][1])
    


    
