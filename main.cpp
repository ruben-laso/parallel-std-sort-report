#include <algorithm>
#include <chrono>
#include <execution>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

#ifdef TBB_SORT
#include <tbb/parallel_sort.h>
#endif

template<typename F>
auto measure(const F && func)
{
	const auto start = std::chrono::high_resolution_clock::now();
	func();
	const auto end = std::chrono::high_resolution_clock::now();

	return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

template<typename Container>
auto do_sort(Container & v)
{
#ifdef PSTL_SORT
	std::sort(std::execution::par, v.begin(), v.end());
#elif TBB_SORT
	tbb::parallel_sort(v.begin(), v.end());
#else
	std::sort(v.begin(), v.end());
#endif
}

int main(const int argc, const char * const argv[])
{
	// Create a large vector of random integers
	std::size_t SIZE = 1 << 30;

	if (argc > 1) { SIZE = std::stoull(argv[1]); }

	std::cout << "Generating " << SIZE << " random integers..." << std::flush;

	// Random number generator
	std::random_device                         rd;
	std::mt19937                               rng(rd());
	std::uniform_int_distribution<std::size_t> dist(0, SIZE);

	auto generator = [&]() {
		return dist(rng);
	};

	std::vector<int> v(SIZE);
	const auto       generate_ms = measure([&]() { std::generate(v.begin(), v.end(), generator); });

	std::cout << " Done in " << generate_ms << " ms" << '\n';

	// Sort the vector
	std::cout << "Sorting the vector..." << std::flush;

	const auto sort_ms = measure([&v]() { do_sort(v); });

	std::cout << " Done in " << sort_ms << " ms" << '\n';

	// Check if the vector is sorted
	if (not std::is_sorted(v.begin(), v.end())) { std::cerr << "Vector is not sorted!\n"; }

	// Print something so the compiler doesn't omit the calculations
	const auto idx = generator();
	std::cout << "v[" << idx << "]: " << v[idx] << '\n';

	return 0;
}