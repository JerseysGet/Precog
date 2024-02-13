"""
USAGE: Pass graph filename and date map file name in that order as command line arguments
OUTPUT: Generates a graph input file which parses cit-HepPh.txt as an edge list, and a
        date input file which parses cit-HepPh-dates.txt as a mapping between nodes and 
        their publication dates5 8 2 3 100 2

"""

import sys


if len(sys.argv) < 3:
    print("Expected output filenames as command line arguments")
    exit(1)

graph_file_name = sys.argv[1]
with open("./dataset/cit-HepPh.txt", "r") as edge_list_file, open(
    graph_file_name, "w"
) as graph_file:
    for line in edge_list_file.readlines():
        line = line.strip()
        if line.startswith("# Nodes"):
            node_ct = line.split()[2]
            edge_ct = line.split()[4]
            graph_file.write(f"{node_ct} {edge_ct}\n")
        elif line.startswith("#"):
            continue
        else:
            from_id, to_id = line.split()
            # graph_file.write(f"{from_id} {to_id}\n")
            graph_file.write(line + '\n')


date_map_file_name = sys.argv[2]
with open("./dataset/cit-HepPh-dates.txt", "r") as date_file, open(
    date_map_file_name, "w"
) as date_map_file:
    for line in date_file.readlines():
        line = line.strip()
        if line.startswith("#"):  # Ignore comments
            continue
        elif line.startswith("11"):  # Ignore cross linked papers
            continue

        paper, date = line.split()
        date_map_file.write(f"{paper} {date}\n")
