import sys

sys.path.insert(0, "src")

import matplotlib.pyplot as plt
from datetime import datetime
from pathlib import Path

if len(sys.argv) != 2:
    print("Expected 1 filename as command line arguments, found", sys.argv)
    exit(1)

COMPUTED_PATH = sys.argv[1]
COMPUTED_FILE = Path(COMPUTED_PATH)

if not COMPUTED_FILE.exists():
    print(f"{COMPUTED_PATH} does not exist. Try running ./b_centrality.sh first")
    exit(1)

centr = []
dates = []
with open(COMPUTED_FILE, "r") as cc_file:
    for line in cc_file.readlines():
        (date, centrality) = line.split()
        date = datetime.strptime(date, "./dataset/pretime/%Y-%m")
        centrality = float(centrality)
        centr.append(centrality)
        dates.append(date)

plt.figure(num="Maximum betweenness centrality vs time")
plt.plot(dates, centr, label="Maximum betweenness centrality vs time")
plt.legend()
plt.savefig("images/b_centrality.png")
plt.show()