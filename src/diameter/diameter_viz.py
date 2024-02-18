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

diameters = []
dates = []
with open(COMPUTED_FILE, "r") as cc_file:
    for line in cc_file.readlines():
        (date, nodect, diameter) = line.split()
        nodect = int(nodect)
        diameter = int(diameter)
        date = datetime.strptime(date, "./dataset/pretime/%Y-%m")
        diameters.append(diameter)
        dates.append(date)


plt.figure(num="Diameter vs Time")
plt.plot(dates, diameters, label="diameter")
plt.legend()
plt.title("Diameter vs Time")
plt.savefig("images/diameter.png")
plt.show()
