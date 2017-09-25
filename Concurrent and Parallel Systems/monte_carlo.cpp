#include <thread>
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

void monte_carlo_pi(unsigned int iterations)
{
	// Create a random engine
	auto millis = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

	default_random_engine e(static_cast<uint32_t>(millis.count()));

	// Create a distribution - we want doubles between 0.0 and 1.0
	uniform_real_distribution<double> distribution(0.0, 1.0);

	// Keep track of number of points in circle
	unsigned int in_circle = 0;
	// Iterate
	for (unsigned int i = 0; i < iterations; ++i)
	{
		// Generate random point
		auto x = distribution(e);
		auto y = distribution(e);
		// Get length of vector defined - use Pythagoras
		auto length = sqrt((x * x) + (y * y));
		// Check if in circle
		if (length <= 1.0)
			++in_circle;
	}
	// Calculate pi
	auto pi = (4.0 * in_circle) / static_cast<double>(iterations);
}

//int main()
//{
//	ofstream data("montecarlo.csv", ofstream::out);
//
//	for (unsigned int num_threads = 0; num_threads <= 6; ++num_threads)
//	{
//		auto total_threads = static_cast<unsigned int>(pow(2.0, num_threads));
//
//		cout << "Number of threads: " << total_threads << endl;
//
//		data << "num_threads_" << total_threads;
//		// Now execute 100 iterations
//		for (unsigned int iters = 0; iters < 100; ++iters)
//		{
//			cout << iters << endl;
//			// Get the start time
//			auto start = system_clock::now();
//			// We need to create total_threads threads
//			vector<thread> threads;
//			for (unsigned int n = 0; n < total_threads; ++n)
//			{
//				// Working in base 2 to make things a bit easier
//				threads.push_back(thread(monte_carlo_pi, static_cast<unsigned int>(pow(2.0, 24.0 - num_threads))));
//			}
//			// Join the threads
//			for (auto &t : threads)
//				t.join();
//			// Get the end time
//			auto end = system_clock::now();
//			// Get the total time
//			auto total = end - start;
//			// Convert to ms and output to file
//			data << ", " << duration_cast<milliseconds>(total).count();
//		}
//		data << endl;
//	}
//	// Close the file
//	data.close();
//	return 0;
//}