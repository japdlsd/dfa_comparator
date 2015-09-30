#!/bin/bash

for in_file in tests/*.in; do
    out_file=`echo "$in_file" | sed 's|.in$|.out|'`
    echo $in_file
    ./demo.bin < "$in_file" > tmp_output
    diff -q "tmp_output" "$out_file"
done

rm tmp_output
