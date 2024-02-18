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
    print(f"{COMPUTED_PATH} does not exist. Try running ./louvain.sh first")
    exit(1)

sizes = []
# absolute_largest = []
# relative_largest = []
dates = []

with open(COMPUTED_FILE, "r") as cc_file:
    for line in cc_file.readlines():
        (date, nodect, size, max_size) = line.split()
        date = datetime.strptime(date, "./dataset/pretime/%Y-%m")
        nodect = int(nodect)
        size = int(size)
        max_size = int(max_size)

        sizes.append(size)
        dates.append(date)



plt.figure(num="Number of communities vs Time")
plt.plot(dates, sizes, label="Communitites")
plt.legend()
plt.title("Communities vs Time")
plt.savefig("images/louvain.png")
plt.show()
