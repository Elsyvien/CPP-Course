/*
Philipp Schmid
Max Staneker
*/


#pragma once
#include <algorithm>
#include <vector>

/**
 * @brief Comutes the Mean Squared Error.
 * You can assume that ground_truth.size() == prediction.size()
 * 
 * @param ground_truth Vector of ground truth values.
 * @param prediction Vector or predictions.
 * @return float The MSE value.
 */
float MSE(const std::vector<float>& ground_truth,
          const std::vector<float>& prediction);

/**
 * @brief Comutes the Mean Absolute Error.
 * You can assume that ground_truth.size() == prediction.size()
 * 
 * @param ground_truth Vector of ground truth values.
 * @param prediction Vector or predictions.
 * @return float The MAE value.
 */
float MAE(const std::vector<float>& ground_truth,
          const std::vector<float>& prediction);


// TODO 8.1.c: implement zip here!
template<typename T1, typename T2>
std::vector<std::pair<T1, T2>> zip (const std::vector<T1>& vec1, const std::vector<T2>& vec2) {
   if (vec1.size() == 0) return std::vector<std::pair<T1, T2>>();
    if (vec2.size() == 0) return std::vector<std::pair<T1, T2>>();
    if (vec1.size() != vec2.size()) return std::vector<std::pair<T1, T2>>();
    std::size_t N = vec1.size(); 
    std::vector<std::pair<T1, T2>> result(N);
    std::transform(vec1.begin(), vec1.end(), vec2.begin(), result.begin(),
                   [](T1 a, T2 b) { return std::make_pair(a, b); } );
    return result;
}
/**
 * @brief Generates a vector with integer values in the range [start, end[
 * Note: The list must be empty if start >= end
 * 
 * @param start The first value in the returned vector
 * @param end The upper limit of the range. This value is not included.
 * @return std::vector<int> The generated vector.
 */
std::vector<int> range(int start, int end);
