#!/bin/bash

make i
for i in {1..48}
do
   time ./i < I_$i.in | diff I_$i.sol -
   echo ""
   echo "teste : $i"
   echo ""
done