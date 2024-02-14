import sys
sys.path.insert(0, 'src')

import os 
import file_io.file_util as fu
import matplotlib.pyplot as plt
import numpy as np
from sklearn.linear_model import LinearRegression

# print(os.listdir('./dataset/pretime'))
PREFIX = './dataset/pretime'
nodes = []
edges = []
for file_path in sorted(os.listdir('./dataset/pretime')):
    print(f"Reading {file_path}...")
    (nodect, edgect) = fu.read_nodes_edges(f"{PREFIX}/{file_path}")
    nodes.append(nodect)
    edges.append(edgect)
    
# print(nodes)    
# print(edges)

log10_nodes = np.log10(np.array(nodes))
log10_edges = np.log10(np.array(edges))

lin_reg_model = LinearRegression()
lin_reg_model.fit(log10_nodes.reshape(-1, 1), log10_edges)

lineX = np.array([3.5, 4.5])
lineY = lin_reg_model.predict(lineX.reshape(-1, 1))
lineY = [ pow(10, y) for y in lineY ]
lineX = [ pow(10, x) for x in lineX ]

print(lin_reg_model.intercept_, lin_reg_model.coef_)

exponent = "{" + f"{lin_reg_model.coef_[0]:0.2f}" + "}"
r_squared_text = f"$R^2 = {lin_reg_model.score(log10_nodes.reshape(-1, 1), log10_edges):0.3f}$"

plt.plot(nodes, edges, label='edges')
plt.plot(lineX, lineY, label=f"${pow(10, lin_reg_model.intercept_):.2g} x ^{exponent}$\n{r_squared_text}")

print("R^2 = ", lin_reg_model.score(log10_nodes.reshape(-1, 1), log10_edges))

plt.yscale('log', base=10)
plt.xscale('log', base=10)
plt.xticks([pow(10, i) for i in range(3, 7)])
plt.yticks([pow(10, i) for i in range(3, 7)])
plt.ylabel('Number of edges')
plt.xlabel('Number of vertices')
plt.ylabel('Number of edges')
plt.legend()
plt.figure()

plt.plot(nodes, edges, label='edges')
plt.xlabel('Number of vertices')
plt.ylabel('Number of edges')
plt.legend()

plt.show()