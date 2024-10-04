#!/usr/bin/env python3

import sys

if len(sys.argv) != 2:
  print('usage: to_uppercase.py <string>', file = sys.stderr)
  sys.exit(1)

string = sys.argv[ 1 ]
print(string.upper())