#!/bin/bash

echo "=== Building Project ==="
make clean
make
make tests

echo ""
echo "=== Quick Functionality Test ==="
./test-mergesort 100 0 1234
./test-mergesort 100 1 1234

echo ""
echo "=== Serial Validation ==="
./test_basic 100 0 1234

echo ""
echo "=== Boundary Tests ==="
./test_merge_boundary

echo ""
echo "=== Advanced Tests ==="
./test_merge_advanced

echo ""
echo "=== Stress Tests ==="
./test_merge_stress

echo ""
echo "=== Performance Test (this will take time) ==="
echo "Serial:"
./test-mergesort 100000000 0 1234
echo "Parallel cutoff=3:"
./test-mergesort 100000000 3 1234
echo "Parallel cutoff=5:"
./test-mergesort 100000000 5 1234

echo ""
echo "=== ALL TESTS COMPLETED ==="