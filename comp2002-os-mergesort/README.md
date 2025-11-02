# Assignment 3 - Parallel Merge Sort

* Authors: Hai Trung Do (a1899443), Tri Dung Nguyen (a1899360), Viet Bach Tran (a1901793)
* Group name: Group 80

## Overview

This project implements a multi-threaded parallel merge sort algorithm using the pthread library. The implementation recursively distributes sorting tasks across multiple threads up to a user-defined cutoff level, achieving substantial performance gains compared to traditional single-threaded sorting through concurrent execution of independent subarray operations.

## Manifest

* `mergesort.c` - Implementation of parallel and serial merge sort functions
* `mergesort.h` - Header file containing function prototypes, global variables, and data structure definitions
* `test-mergesort.c` - Testing program for performance benchmarking and correctness validation
* `Makefile` - Build configuration for compiling the project
* `README.md` - Project documentation (this file)

## Building the project

To compile the project, navigate to the project directory and run:

```bash
make
```

This will generate the `test-mergesort` executable. To remove compiled files and clean the directory:

```bash
make clean
```

## Features and usage

**Core Functions:**
- `mergesort()` - Sequential recursive merge sort serving as the base implementation once parallelization depth is exhausted
- `merge()` - Combines two pre-sorted subarrays into one sorted sequence via the auxiliary array B
- `parallel_mergesort()` - Spawns two child threads per recursion level to concurrently process left and right partitions
- `buildArgs()` - Packages array boundaries and depth information into structures for thread parameter passing

**Usage:**

**How It Works:**
- **Serial mode (cutoff=0)**: Executes conventional single-threaded recursive merge sort throughout
- **Parallel mode (cutoff>0)**: Spawns two child threads per level until reaching specified depth, then transitions to sequential sorting
- **Synchronization**: Parent threads invoke `pthread_join()` on both children, blocking until completion before executing merge phase
- **Memory management**: Argument structures are dynamically allocated per thread and freed immediately after use to maintain zero-leak operation

To run the program:

```bash
./test-mergesort <array_size> <cutoff_level> <random_seed>
```

**Parameters:**
- `array_size`: Total number of integer elements to sort (e.g., 100000000)
- `cutoff_level`: Maximum depth for thread spawning (0 = purely sequential, higher = more concurrency)
- `random_seed`: Integer seed for deterministic random array generation

**Example:**
```bash
./test-mergesort 100000000 0 1234    # Sequential baseline measurement
./test-mergesort 100000000 5 1234    # Parallel execution with 5-level threading
```

Processes 100 million integers. The first command establishes baseline performance, while the second uses 5 levels of multi-threading to achieve significant acceleration.

## Testing

### Correctness Testing

**Basic Functionality:**
- Tested with array sizes: 10, 100, 1,000, 10,000, and 100,000,000 elements
- Verified correct sorting using the built-in `is_sorted()` validation function
- Tested cutoff levels from 0 to 8
- All tests passed with 100% correctness

**Edge Cases:**
- Single-element and two-element arrays
- Already sorted arrays (best case)
- Reverse-sorted arrays (worst case)
- Arrays containing duplicate values
- Arrays with negative numbers
- Empty subarrays during recursive division

**Randomization Testing:**
- Multiple random seeds tested: 1234, 5678, 9999, 42, 12345
- Special patterns: ascending order, descending order, alternating values, uniform values
- Consistent correctness across all patterns and cutoff levels

### Performance Testing

Tested with 100,000,000 elements (seed 1234):

- **Cutoff 0** (serial): 17.10 seconds (baseline)
- **Cutoff 1**: 12.61 seconds (1.36x speedup)
- **Cutoff 2**: 5.40 seconds (**3.17x speedup**) - **Exceeds 2x requirement**
- **Cutoff 3**: 4.63 seconds (3.69x speedup)
- **Cutoff 4**: 3.41 seconds (5.01x speedup)
- **Cutoff 5**: 3.42 seconds (5.00x speedup)
- **Cutoff 6**: 3.34 seconds (5.12x speedup) - **Optimal performance**

The implementation exceeds the required 2x speedup at cutoff level 2 and achieves optimal performance (approximately 5x) at cutoff level 6. Performance gains diminish beyond this point due to thread creation overhead.

### Memory Validation

**Valgrind (Linux):**
```bash
valgrind --leak-check=full ./test-mergesort 1000 2 1234
```
Output: "All heap blocks were freed -- no leaks are possible"

**Leaks (macOS):**
```bash
leaks -atExit -- ./test-mergesort 1000 2 1234
```
Output: "0 leaks for 0 total leaked bytes"

All dynamic allocations in `buildArgs()` are properly released within `parallel_mergesort()`.

### Thread Synchronization Verification

- Confirmed correct `pthread_join()` operation across all cutoff configurations
- Zero race conditions detected throughout extensive manual testing
- No orphaned threads or deadlock situations encountered
- Manually validated thread safety with diverse combinations: array sizes from 1,000 to 100,000,000 and cutoff levels spanning 0-8

## Known Bugs

No known bugs identified. The implementation successfully passes all manual test cases and all visible Gradescope test cases at the time of submission. Sorting correctness has been verified across diverse array sizes and cutoff configurations.

## Reflection and Self Assessment

The most difficult aspect was grasping how `parallel_mergesort()` achieves recursion indirectly via `pthread_create()`, which differs fundamentally from traditional recursive calls. Balancing parallelism with performance required experimentation—excessive thread creation introduces overhead that eventually negates the benefits of concurrent execution.

Memory management across threads presented challenges. Each thread needed its argument structure properly allocated and deallocated to avoid leaks. We also discovered that `pthread_join()` serves as an essential coordination point, ensuring child threads complete their work before the parent proceeds to merge operations, thus eliminating potential race conditions.

We relied heavily on pthread documentation and the OSTEP textbook chapters covering concurrency fundamentals. The assignment's binary tree diagram was particularly valuable for visualizing thread hierarchy and understanding the cutoff mechanism.

Our development approach was incremental: validate the serial implementation first, then layer in parallelization. This methodology, combined with extensive manual testing across diverse inputs and cutoff values, helped us identify and resolve subtle threading issues early.

## Sources Used

1. Operating Systems: Three Easy Pieces - Chapters 26 and 27 (Concurrency and threads API)
- http://pages.cs.wisc.edu/~remzi/OSTEP/

2. pthread API man pages:
- pthread_create: https://man7.org/linux/man-pages/man3/pthread_create.3.html
- pthread_join: https://man7.org/linux/man-pages/man3/pthread_join.3.html

3. Memory leak detection tools:
- Valgrind documentation (Linux): https://valgrind.org/docs/manual/quick-start.html
- macOS leaks man page: https://www.manpagez.com/man/1/leaks/

4. Merge sort algorithm tutorial:
- HackerRank Merge Sort video: https://www.youtube.com/watch?v=4VqmGXwpLqc