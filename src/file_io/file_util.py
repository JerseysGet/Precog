import os
import networkx as nx
from datetime import date
from dateutil.relativedelta import relativedelta


def create_ancestors(file_path: str):
    """Create ancestor directories if they don't exist"""
    os.makedirs(os.path.dirname(file_path), exist_ok=True)


def write_graph(graph, file_path):
    """Write graph to file_path in node count, edge count, edge list format.
    Creates the parent directories if the do not exist"""
    mp = {}
    ptr = 0
    for node in graph.nodes:
        mp[node] = ptr
        ptr += 1

    create_ancestors(file_path)
    with open(file_path, "w") as file:
        file.write(f"{graph.number_of_nodes()} {graph.number_of_edges()}\n")
        for edge in graph.edges:
            file.write(f"{mp[edge[0]]} {mp[edge[1]]}\n")


def read_date_input(graph_input_path, date_input_path):
    node_set = set()
    with open(graph_input_path, "r") as graph_input:
        (nodect, edgect) = map(int, graph_input.readline().split())
        for line in graph_input.readlines():
            (u, v) = map(int, line.split())
            node_set.add(u)
            node_set.add(v)
        
    ret = {}
    with open(date_input_path, "r") as date_input:
        for line in date_input.readlines():
            (node, date_str) = line.split()
            node = int(node)
            (year, month, day) = map(int, date_str.split("-"))
            if node in node_set:
                ret[node] = date(year, month, day)
    return ret


def add_past_nodes_to_map(total_graph, date_map):
    for node in total_graph.nodes:
        if node not in date_map:
            date_map[node] = date.min


def next_month(Date):
    next_date = Date + relativedelta(months=1)
    return next_date

def prev_month(Date):
    next_date = Date - relativedelta(months=1)
    return next_date

def read_graph(path):
    with open(path, "r") as file:
        (nodect, edgect) = map(int, file.readline().split())
        ret = nx.empty_graph(nodect, create_using=nx.DiGraph())
        for line in file.readlines():
            (u, v) = map(int, line.split())
            ret.add_edge(u, v)
    return ret

def read_nodes_edges(path):
    with open(path, "r") as file:
        (nodect, edgect) = map(int, file.readline().split())
    return (nodect, edgect)