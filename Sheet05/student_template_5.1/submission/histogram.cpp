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

  for (std::map<std::string, double>::const_iterator i = histogram.begin(); i != histogram.end(); i++) {
    histo_sorted.emplace(i->second, i->first);
  }

  for (std::multimap<double, std::string>::const_iterator i = histo_sorted.begin(); i != histo_sorted.end() && result.size() < n; i++) {
    result.emplace_back(i->first, i->second);
  }
  return result;
}
// TODO 5.1.c
// TODO 5.1.d