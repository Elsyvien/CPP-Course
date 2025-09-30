/*
Philipp Schmid: 5703070
Max Staneker: 7018590
*/
#include "exercise_09_3.h"

#include <algorithm>
#include <chrono>
#include <execution>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>

using namespace std;

vector<double> get_vector_of_random_numbers() {
  // First create an instance of an engine.
  random_device rnd_device;
  // Specify the engine and distribution.
  mt19937 mersenne_engine{rnd_device()}; // Generates random integers
  uniform_int_distribution<int> dist{0, 1000000};

  auto gen = [&dist, &mersenne_engine]() { return dist(mersenne_engine); };

  vector<double> vec(1e6);
  generate(begin(vec), end(vec), gen);
  return vec;
}

vector<double> sequential_sort(vector<double> &data) {
  // TODO STUDENT

  //sorts in the normal way(serial) and uses 1 thread only, so its slower on big data
  sort(data.begin(), data.end());
  return data;
}

vector<double> parallel_sort(vector<double> &data) {
  // TODO STUDENT

  //with execution::par, it can use multiple threads to sort faster(many cpu cores work at the same time)
  sort(execution::par, data.begin(), data.end());
  return data;
}

vector<double> sequential_transform(vector<double> &data, double (*function)(double)) {
  // TODO STUDENT

  //only 1 thread works, so it is slower for expensive functions
  transform(data.begin(), data.end(), data.begin(), function);
  return data;
}

vector<double> parallel_transform(vector<double> &data, double (*function)(double)) {
  // TODO STUDENT

  //with execution::par, multiple threads can apply the function at the same time (useful if the function is expensive)
  transform(execution::par, data.begin(), data.end(), data.begin(), function);
  return data;
}

/*
Do we see a speedup?
Yes, we can see that the parallel version is faster than the serial one.
Sort was about 6x faster and transform about 7x faster.
Thats because execution::par uses many CPU cores at the same time.

Our output: 
Serial sort executed in: 323.692
Parallel sort executed in: 53.8811
Parallel sort was 269.811 ms faster.
Serial transform executed in: 50.8278
Parallel transform executed in: 7.00841
Parallel transform was 43.8194 ms faster.

On Infomark, we get 1 Test failed (REQUIRE( duration_parallel_ms * 2 < duration_sequential_ms )),
but on our machines its working fine and this test shouldn`t fail
*/