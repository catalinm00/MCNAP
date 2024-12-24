#!/bin/python3
import sys
import hashlib

input = sys.argv[1]
numOfReducers = int(sys.argv[2])

splits = [open(f"{input}_output{i}", "wt") for i in range(numOfReducers)]
for line in sys.stdin:
    key, value = line.split("\t")
    splitIndex = int(hashlib.sha1(key.encode()).hexdigest(),16)%len(splits)
    splits[splitIndex].write(f"{key}\t{value}")

for split in splits: split.close()
