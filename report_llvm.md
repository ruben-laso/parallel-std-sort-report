# Title
[PSTL] High memory usage for parallel `std::sort`

# Description
The memory usage of parallel `std::sort` is very high compared to the sequential version and even other parallel implementations.
The code in this [repo]() is a simple test case to compare the memory usage of parallel `std::sort`, `tbb::parallel_sort` and sequential `std::sort`.
The test case has been replicated in several systems with versions of GCC 10, 11 and 12.

An example of the results (and max. memory usage according to `/usr/bin/time`) is shown in the following table:

| Executable         | Size        | Time     | Max Resident Memory |
| ------------------ | ----------- | -------- | ------------------- |
| ./pstl_sort.out    | 33554432    | 0:00.23  | 423776k             |
| ./tbb_sort.out     | 33554432    | 0:00.44  | 143952k             |
| ./seq_sort.out     | 33554432    | 0:03.32  | 134836k             |
| ./pstl_sort.out    | 1073741824  | 0:05.68  | 14236656k           |
| ./tbb_sort.out     | 1073741824  | 0:13.02  | 4207680k            |
| ./seq_sort.out     | 1073741824  | 2:07.38  | 4198124k            |

*Note: specs and details of the benchmark are in the aforementioned [repo]().*

In the example, the parallel `std::sort` (pstl_sort) uses ~3 times more memory than the `tbb::parallel_sort` (tbb_sort) and the sequential `std::sort` (seq_sort).
It also runs faster, though.

Despite the [docs](https://github.com/llvm/llvm-project/blob/main/pstl/README.md) saying that `std::sort`` "require additional O(n) memory space for parallel execution", it seems that the memory overhead is higher than what would be expected.

Is that high memory usage a deliberate trade-off for performance?
Is the algorithm still in development to improve memory usage?