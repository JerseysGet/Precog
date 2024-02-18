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

max_in = []
max_out = []
avg = []
dates = []
with open(COMPUTED_FILE, "r") as cc_file:
    for line in cc_file.readlines():
        (date, nodect, maxin, maxout, average) = line.split()
        date = datetime.strptime(date, "./dataset/pretime/%Y-%m")
        average = float(average)
        nodect = int(nodect)
        maxin = int(maxin)
        maxout = int(maxout)
        maxin /= (nodect - 1)
        maxout /= (nodect - 1)
        average /= (nodect - 1)
        dates.append(date)
        max_in.append(maxin)
        max_out.append(maxout)
        avg.append(average)

plt.figure(num="Maximum degree centrality vs time")
# plt.plot(dates, max_in, label="Maximum in-degree")
# plt.plot(dates, max_out, label="Maximum out-degree")
plt.plot(dates, avg, label="Average degree")
plt.legend()
plt.savefig("images/d_centrality.png")
plt.show()