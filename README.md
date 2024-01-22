# Parallel `std::sort` test program
This repo holds a simple test program to compare the memory usage of parallel `std::sort`, `tbb::parallel_sort` and sequential `std::sort`.

## Compilation
The following commands can be used to compile the test programs:
```bash
g++ -std=c++17 -O3 -pedantic -Wall -Wextra -Werror -o pstl_sort.out main.cpp -ltbb -DPSTL_SORT
g++ -std=c++17 -O3 -pedantic -Wall -Wextra -Werror -o tbb_sort.out main.cpp -ltbb -DTBB_SORT
g++ -std=c++17 -O3 -pedantic -Wall -Wextra -Werror -o seq_sort.out main.cpp -ltbb
```
These will generate the executables `pstl_sort.out`, `tbb_sort.out` and `seq_sort.out`.

## Usage
The test program can be run with the following command:
```bash
./pstl_sort.out <size>
```
Where `<size>` is the size of the array to be sorted.

## Example of results
An example of the results (and max. memory usage according to `/usr/bin/time`) is shown in the following table:

| Executable         | Size        | Time     | Max Resident Memory |
| ------------------ | ----------- | -------- | ------------------- |
| ./pstl_sort.out    | 33554432    | 0:00.23  | 423776k             |
| ./tbb_sort.out     | 33554432    | 0:00.44  | 143952k             |
| ./seq_sort.out     | 33554432    | 0:03.32  | 134836k             |
| ./pstl_sort.out    | 1073741824  | 0:05.68  | 14236656k           |
| ./tbb_sort.out     | 1073741824  | 0:13.02  | 4207680k            |
| ./seq_sort.out     | 1073741824  | 2:07.38  | 4198124k            |

In a system with the following specs:
* CPU: AMD EPYC 7551
* RAM: 256 GB DDR4
* OS: Debian 10.10
