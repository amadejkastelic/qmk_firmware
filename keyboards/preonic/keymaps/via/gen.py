#!/usr/bin/env python3

#use python3.8.4
import csv, sys, re

def main(args):
    for y in range(0, 12):
        for x in range(0, 5):
            print("case " +  "ROW" + str(x) + "COL" + str(y) + ":")
            print('    SEND_STRING("");')
            print("    SEND_STRING(SS_TAP(X_ENTER));")
            print("    return false;")
            print("    break;")

if __name__ == "__main__":
    main(sys.argv)