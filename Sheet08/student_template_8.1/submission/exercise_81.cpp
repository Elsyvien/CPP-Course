#include "exercise_81.h"
#include <algorithm>
#include <cstddef>
#include <vector>
#include <numeric>


float MSE(const std::vector<float>& ground_truth,
          const std::vector<float>& prediction) {
  if (ground_truth.size() == 0) return 0;
  if (prediction.size() == 0) return 0;
  if (ground_truth.size() != prediction.size()) return 0;

  std::size_t N = ground_truth.size();
  std::vector<float> square(N);
  std::transform(ground_truth.begin(), ground_truth.end(), prediction.begin(), square.begin(),
                  [](float a, float b) {return (a - b) * (a - b);});
  float sum = std::accumulate(square.begin(), square.end(), 0.f);
  return sum / N;
}

float MAE(const std::vector<float>& ground_truth,
          const std::vector<float>& prediction) {
  // TODO: 8.1.a)
  if (ground_truth.size() == 0) return 0;
  if (prediction.size() == 0) return 0;
  if (ground_truth.size() != prediction.size()) return 0;

  std::size_t N = ground_truth.size();
  std::vector<float> diffTemp(N);
  std::transform(ground_truth.begin(), ground_truth.end(), prediction.begin(), diffTemp.begin(),
              [](float a, float b) {return std::abs(a - b);});
  float sum = std::accumulate(diffTemp.begin(), diffTemp.end(), 0.0f);
  float result = sum / N;
  return result;
}

std::vector<int> range(int start, int end) {
  // TODO: 8.1.d)
  return std::vector<int>();
}

