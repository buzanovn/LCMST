#!/bin/bash

for taxicab_file in $1/*; do
  python3 converter.py "$taxicab_file" "$2/$(basename $taxicab_file)"
done;