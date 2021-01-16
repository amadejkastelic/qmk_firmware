#!/usr/bin/env python3

#use python3.8.4
import csv, sys, re

def main(args):
    for x in range(0, 5):
        for y in range(0, 12):
            print("ROW" + str(x) + "COL" + str(y)+",", end = '')

        print("")

if __name__ == "__main__":
    main(sys.argv)