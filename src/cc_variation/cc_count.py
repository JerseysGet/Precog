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
    print(f"{COMPUTED_PATH} does not exist. Try running ./cc.sh first")
    exit(1)

scc_counts = []
largest_scc = []
wcc_counts = []
largest_wcc = []
dates = []
with open(COMPUTED_FILE, "r") as cc_file:
    for line in cc_file.readlines():
        (date, nodect, scc_ct, largest_scc_size, wcc_ct, largest_wcc_size) = (
            line.split()
        )
        nodect = int(nodect)
        scc_ct = int(scc_ct)
        largest_scc_size = int(largest_scc_size)
        wcc_ct = int(wcc_ct)
        largest_wcc_size = int(largest_wcc_size)
        date = datetime.strptime(date, "./dataset/pretime/%Y-%m")

        scc_counts.append(scc_ct)
        wcc_counts.append(wcc_ct)

        largest_scc.append(largest_scc_size / nodect)
        largest_wcc.append(largest_wcc_size / nodect)

        dates.append(date)

        

plt.figure(num="SCC Count vs Time")
plt.plot(dates, scc_counts, label="scc_count")
plt.legend()
plt.title("SCC Count vs Time")
plt.savefig("images/scc_count.png")


plt.figure(num="WCC Count vs Time")
plt.plot(dates, wcc_counts, label="wcc_count")
plt.legend()
plt.title("WCC Count vs Time")
plt.savefig("images/wcc_count.png")

plt.figure(num="Fraction in largest SCC/WCC")
plt.plot(dates, largest_scc, label="Fraction in largest scc")
plt.plot(dates, largest_wcc, label="Fraction in largest wcc")
plt.legend()
plt.title("Fraction in largest SCC/WCC")
plt.savefig("images/scc_wcc_fraction.png")

plt.show()