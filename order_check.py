import argparse

parser = argparse.ArgumentParser()
parser.add_argument('header')
args = parser.parse_args()

entrypoints = None
with open(args.header) as header:
    entrypoints = [line.strip() for line in header.readlines()]

for i, _ in enumerate(entrypoints):
    # Can't compare the first one with the previous
    if i == 0:
        continue
    if entrypoints[i - 1] > entrypoints[i]:
        print('ERROR: ' + entrypoints[i] + ' should come before ' + entrypoints[i - 1])
        exit(1)
