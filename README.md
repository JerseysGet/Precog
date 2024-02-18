# Analyzing citation networks

## Programming Tasks

### Tasks not done:
- Partially done Task 2.1: Only implemented one algorithm, as I was unable to implement Leiden in time, and Girvan–Newman would take too long to run on my system
- Bonus Task

### [Requirements](https://github.com/JerseysGet/Precog/blob/main/requirements.txt)
Clone the repo, and in the `Precog` directory,
Install the requirements by running:
```bash
pip install -r requirements.txt
```

### Running the project
The results of the data analysis have already been computed in [dataset/computed](https://github.com/JerseysGet/Precog/tree/main/dataset/computed), running the scripts given below would directly generate the plots. However, to process the data again, do the following:
1. Parse the dataset (raw data located in in [`dataset/raw`](https://github.com/JerseysGet/Precog/tree/main/dataset/raw))
```bash
./parse_input.sh
```
2. Delete the contents of [dataset/computed](https://github.com/JerseysGet/Precog/tree/main/dataset/computed) (only if you want to process the data again)
```@
rm dataset/computed/*
```

3. Task 1: The following scripts are relevant to Task 1
    1. Variation of Edges vs Nodes `./edges_vs_nodes.sh`
    2. Variation of Diameter over time `./diameter.sh` (this might take some time to run)
    3. Variation of various connected components with time `./cc.sh`
    4. Variation of maximum betweenness centrality with time `./b_centrality.sh` (this will take a lot of time to run)
    5. Variation of maximum degree centrality with time `./d_centrality.sh`

4. Task 2: The following scripts are relevant to Task 2
    1. Louvain community detection, number of communitites vs time `./louvain.sh` 
## Report
## Task 1
### 1. Edges vs Nodes
![edges_vs_nodes.png](https://github.com/JerseysGet/Precog/blob/main/images/edges_vs_vertices.png)
![edges_vs_nodes_log.png](https://github.com/JerseysGet/Precog/blob/main/images/edges_vs_vertices_log.png)

We can observe an almost straight line in the log-log plot of number of edges vs number of nodes, which means that the number of edges follows a power law distribution with the number of nodes, with the exponent being `~1.88`. 

This implies that the average degree of the graph _increases_ with time and also follows a power law distriibution with exponent `~0.88` (because the total number of edges is equal to the total out degree), and hints toward the overall densification of the network with time. This pattern is recurring among all the 5 parameters.

The equation for the orange plot was obtained through linear regression on the log-log plot, which gave an `R^2` value of about `~0.997`

I used `scikit-learn` for the linear regression.


### 2. Variation of connected components
![wcc_count.png](https://github.com/JerseysGet/Precog/blob/main/images/wcc_count.png) 
![scc_count.png](https://github.com/JerseysGet/Precog/blob/main/images/scc_count.png)

The number of weakly connected components ended up decreasing with time, and this is explained by the papers 'bridging' the gap between unrelated fields quite often.

I suspect that the initial increase is probably due to the earlier papers only citing papers from _before_ 1992, which is when the dataset begins, and hence they appear as separate WCC's.

The number of strongly connected components however mostly increases with time, and this is because ideally, a citation network contains no cycles, however as papers are revised, later versions of papers (post publication) might refer papers that appear to have been from the future, thereby possibly creating a cycle.

This is however quite rare, and thus the number of SCCs would almost always increase.

![scc_wcc_fraction.png](https://github.com/JerseysGet/Precog/blob/main/images/scc_wcc_fraction.png)

The fraction of nodes in the largest WCC steadily increases, and this shows that most new papers merge into the largest WCC, and by the year 2000, almost every paper is a part of the largest WCC. The initial dip is probably due to the later start year of the dataset.

The fraction of nodes in the largest SCC increases more erractically, and the sudden increase towards the end mirrors the sudden decrease in the number of SCCs around the same time. This probably points to a large number of SCCs merging into one around this time.


### 3. Variation of Diameter with time

![diameter.png](https://github.com/JerseysGet/Precog/blob/main/images/diameter.png)

The (undirected) diameter of the graph tends to decrease with time, and this shows the densification of the graph, and it is quite similar to the [six degrees of separation](https://en.wikipedia.org/wiki/Six_degrees_of_separation) or [small world phenomenon](https://en.wikipedia.org/wiki/Small-world_experiment).

The largest distance between the nodes decreases with time, and this is probably due to:
1. Most papers are a part of the largest WCC anyway, and the longest path in the largest WCC would usually get cut by the new papers, preventing the formation of long chains
2. Papers that are not a part of the largest WCC end up merging with the largest WCC before they could ever grow long enough.

It is interesting to note that the diameter has a similar peak as the number of WCCs, just a lagging by 1-2 years.

#### 3.1 Computing the Diameter
Because the graph is not acyclic, computing the diameter becomes much more computationally intensive. I have computed the diameter by exhaustive breadth first search, with the search being started from half of the nodes at random.

Despite only searching half the nodes exhaustively, this was quite slow, so I ended up using [OpenMP](https://www.openmp.org/) to parallelize the breadth first search, as the separate searches were competely independent of each other. This resulted in about a `~4.5x` speedup.

### 4. Variation of maximum degree centrality with time

![d_centrality.png](https://github.com/JerseysGet/Precog/blob/main/images/d_centrality.png)

Degree centrality is of a vertex is defined as the degree of that vertex, so for directed graphs there is in-degree centrality and out-degree centrality. The values in the plot are also normalized by dividing by the maximum possible degree centrality (number of nodes minus 1), this is done as to offset any effect of the increase in overall size of the graph.

I have also plotted the average degree centrality (average in-degree centrality = average out-degree centrality, as they are both related to the total number of edges), although it is miniscule incomparison to the maximum.

1. The most cited paper is cited more than the number of citations of the paper that cites the most number of papers, across almost all point of time.
This makes sense, as it would be quite strange for a paper to cite an absurd amount of other papers, but it is not unusual for a few great papers to be highly cited.

2. Overtime, the graph becomes more central
This suggests that the citation network becomes more 'tightly knit', and I suspect that it is due to the increasing influence of the main WCC.

### 5. Variation of maximum betweeness centrality with time

![b_centrality.png](https://github.com/JerseysGet/Precog/blob/main/images/b_centrality.png)

Betweeness centrality of a vertex is defined as the sum of fraction of shortest paths over all pairs of paths. Loosely speaking, it tells how much of a 'bridge' (articulation point, really) a given vertex is. This is definitely a better centrality measure in the contex of the citation graph, as it very clearly shows the increase in centrality of the graph with time.
The most influential nodes become more influential over time, as they further 'bridge' the new papers that come up.
Note that the betweeness centrality was computed on the undirected graph.

#### 5.1 Computing the betweeness centrality
Betweeness centrality is the most computationally demanding mertric to compute. I have implemented betweeness centrality through [Brandes's Algorithm](http://snap.stanford.edu/class/cs224w-readings/brandes01centrality.pdf), which utilizes an efficient dynamic programming based approach on the BFS DAG (tree in the case of undirected graph) obtained, resulting in a linear time evalutaion of the contribution of a given source.
The overall complexity of the algorithm is `O(mn)`, where `m` is the number of edges and `n` is the number of nodes.

Just with this implementation, this took atleast `3` hours to run, and I never really let it run fully. Using subsets of the graph chosen uniformly at random as potential sources (analogous to what I did to compute the diameter) gave 'funny' results, and it was clear that the important sources were not being 'hit' some of the time (which resulted in erratic variation with time)

To speed things up whilst not resorting to using partial data, I used [OpenMP](https://www.openmp.org/) to parallelize the source breadth first searches again, as this entire section of BFS + Dynamic programming was independent for each source. This resulted in around a `~6x` speedup for the largest graph.

Still, this took `102` minutes to fully run on my machine.

## Task 2

### Louvain Algorithm for community detection

![louvain.png](https://github.com/JerseysGet/Precog/blob/main/images/louvain.png)

Louvain Algorithm for community detection is a greedy heuristic algorithm, which attempts to maximize the [modularity](https://en.wikipedia.org/wiki/Modularity_(networks)) of a partition of the graph.
Maximizing the modularity of a graph is NP-Hard, and thus the Louvain Algorithm uses a greedy heuristic, basically choosing to place a vertex in the communinity that maximizes the overall modularity of the graph, and iteratively doing this untill a maxima of modularity is obtained.

The algorithm greedily picks the best community for each vertex (this is done in a random order) and assigns it to that community.

The communitites formed are collapsed into a single vertex, and the process is repeated till there is no increase in modularity.

The algorithm runs quite fast, empirically observed `O(n log n)`. This feels intuitive, as the size of the graph would roughly half in each iteration, similar to [Boruvka's algorithm for MST](https://en.wikipedia.org/wiki/Bor%C5%AFvka%27s_algorithm),

However, due Louvain's algorithm occasionally returns quite unreliable values (about 25% of the time just detects disconnected components). This is fixed in the Leiden algorithm for community detection.

Temporal community detection plot is virtually identical to the plot of number of WCCs, and this shows that the algorithm tends to detect disconnected components (WCCs), with some slight disparity.

Another community detection algorithm (which does not rely on the modularity metric) I considered implementing was the Girvan–Newman for community detection, as it relied on calculating the 'edge-betweenness' which is defined similarly to vertex-betweenness. Loosely speaking, the algorithm calculates the edge betweenness (using a slight modification of the Dynamic programming in Brandes's Algorithm), removes the most influential edge, and repeats the process.
The recalculation of edge-betweenness in each iteration is however extremely expensive, and this would probably just take forever to run on my machine even on a subset of the data.
