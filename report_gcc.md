# `std::sort` report

# Slurm report
Fill in [here](https://gcc.gnu.org/bugzilla/enter_bug.cgi)

# Report content

* Component: libstdc++

* Version: 12.3.0

* Summary:
High memory usage for parallel `std::sort`

* Description:
The memory usage of parallel `std::sort` is very high compared to the sequential version and even other parallel implementations.
The attached code is a simple test case to compare the memory usage of parallel `std::sort`, `tbb::parallel_sort` and sequential `std::sort`.
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

In the example, the parallel `std::sort` (pstl_sort) uses ~3 times more memory than the `tbb::parallel_sort` (tbb_sort) and the sequential `std::sort` (seq_sort).
It also runs faster, though.

Despite the [docs](https://github.com/llvm/llvm-project/blob/main/pstl/README.md) saying that `std::sort`` "require additional O(n) memory space for parallel execution", it seems that the memory overhead is higher than what would be expected.

Is that high memory usage a deliberate trade-off for performance?
Is the algorithm still in development to improve memory usage?

* Notes of the benchmark:
	* System specs in the example:
	* CPU: AMD EPYC 7551
	* RAM: 256 GB DDR4
	* OS: Debian 10.10

	* Compilation with:
```bash
g++ -std=c++17 -O3 -pedantic -Wall -Wextra -Werror -o pstl_sort.out main.cpp -ltbb -DPSTL_SORT
g++ -std=c++17 -O3 -pedantic -Wall -Wextra -Werror -o tbb_sort.out main.cpp -ltbb -DTBB_SORT
g++ -std=c++17 -O3 -pedantic -Wall -Wextra -Werror -o seq_sort.out main.cpp -ltbb
```


# Issue in the GCC Bugzilla

Bug [113504](https://gcc.gnu.org/bugzilla/show_bug.cgi?id=113504) has been successfully created.

Email sent to:
`gcc-bugs@gcc.gnu.org, saifi.khan@nishan.io`

-> Redirected to LLVM's GitHub https://github.com/llvm/llvm-project/tree/main/pstl.

# Issue in the LLVM GitHub

