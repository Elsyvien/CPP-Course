#include "histogram.h"

#include <limits>
#include <map>
#include <string>
#include <utility>
#include <vector>

Histogram::Histogram(const std::vector<std::string> &words) {
  double normFactor = 1.0 / (double) words.size();
  for (size_t i = 0; i < words.size(); i++) {
    if (!histogram.contains(words[i])) { histogram[words[i]] = normFactor; } 
    else { histogram[words[i]] += normFactor; }
  }
}

size_t Histogram::size() const {
  std::map<std::string, double>::size_type map_size = histogram.size();
  size_t count = 0;
  for (auto i = histogram.begin(); i != histogram.end(); i++) {
    count++;
  }
  return count;
}

bool Histogram::contains(const std::string &word) const {
  if (histogram.contains(word)) { return true; }
  else { return false; }
}

double Histogram::probability(const std::string &word) const {
  if (histogram.contains(word)) { return histogram.at(word); }
  else { return 0.0; }
}

// TODO 5.1.b
std::vector<std::pair<double, std::string>> Histogram::most_common_words(const size_t n) const {
  std::multimap<double, std::string, std::greater<>> histo_sorted;
  std::vector<std::pair<double, std::string>> result;

  for (auto it = histogram.begin(); it != histogram.end(); it++) {
    const std::string& word = it->first; 
    double prob = it->second;           
    histo_sorted.insert({prob, word}); 
  }

  for (auto it = histo_sorted.begin(); it != histo_sorted.end(); it++) {
    if (result.size() >= n) {
      break; 
    }

    const auto& entry = *it;           
    double prob = entry.first;        
    const std::string& word = entry.second; 

    result.emplace_back(prob, word);
  }

  return result;
}
// TODO 5.1.c
double Histogram::dissimilarity(const Histogram &other) const {
  double sum = 0.0;
  int count = 0;
  for (auto it = histogram.begin(); it != histogram.end(); it++) {
    if (other.contains(it->first) == true) {
      count++;
      sum += std::abs(probability(it->first) - other.probability(it->first));
    }
  }

  if (count == 0) { return 0.0; }
  return (1.0 - (count / (double) size())) + (1.0 - (count / (double) other.size())) + sum;

}
// TODO 5.1.d
size_t Histogram::closest(const std::vector<Histogram> &others) const {
  std::multimap<double, size_t> candidateMap;
  for (auto i = 0; i < others.size(); i++) {
    double dissim = dissimilarity(others[i]);
    candidateMap.insert({dissim, i});
  }
  return candidateMap.begin()->second;
}