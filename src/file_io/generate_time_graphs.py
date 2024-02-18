import file_util
import networkx as nx
import sys
import datetime


def get_total_graph(graph_input_path, date_map):
    ret = nx.DiGraph()

    for node, date in date_map.items():
        ret.add_node(node)

    with open(graph_input_path, "r") as graph_input:
        (nodect, edgect) = map(int, graph_input.readline().split())
        ct = 0
        for line in graph_input.readlines():
            (u, v) = line.split()
            ret.add_edge(int(u), int(v))

    return ret


def get_pretime_graph(total_graph, date, date_map):
    """Returns the subgraph with all nodes <= date"""
    ret = nx.DiGraph()

    for node in date_map:
        if date_map[node] > date:
            continue
        ret.add_node(node)

    for u, v in total_graph.edges:
        if date_map[u] > date or date_map[v] > date:
            # print(u, v, date_map[u], date_map[v])
            continue
        ret.add_edge(u, v)
    return ret


if len(sys.argv) != 4:
    print("Expected 3 filenames as command line arguments, found", sys.argv)
    exit(1)

graph_input_path = sys.argv[1]
date_input_path = sys.argv[2]
graph_output_dir = sys.argv[3]

date_map = file_util.read_date_input(graph_input_path, date_input_path)
total_graph = get_total_graph(graph_input_path, date_map)
earliest_date = file_util.prev_month(min(list(date_map.values())))
latest_date = file_util.next_month(max(list(date_map.values())))

earliest_date = earliest_date.replace(day=1)
latest_date = latest_date.replace(day=1)

file_util.add_past_nodes_to_map(total_graph, date_map)



date_itr = earliest_date
while date_itr <= latest_date:
    pretime_graph = get_pretime_graph(total_graph, date_itr, date_map)
    print("Printing", date_itr, pretime_graph, "...")
    file_util.write_graph(
        pretime_graph, graph_output_dir + "/" + date_itr.strftime("%Y-%m")
    )
    date_itr = file_util.next_month(date_itr)
