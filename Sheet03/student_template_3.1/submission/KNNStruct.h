/*
Max Staneker
Philipp Schmid
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

struct DYNPoint {
	std::vector<float> data;

	// We use a static function to return a DYNPoint object (this pattern is sometimes called a "factory method")
	// We can mark functions as nodiscard to indicate that we must use the return value in some way (e.g, it doesn't get discarded as ).
	[[nodiscard]] static DYNPoint createRandomPoint(unsigned int size, int minimum=-5000, int maximum=5000) {
		DYNPoint p;
		float factor = (float) (maximum - minimum) / (float) RAND_MAX;
		if (size > 0 && minimum <= maximum) {
			for (int i = 0; i < size; i++) {
				p.data.push_back(((float) std::rand() * factor) + (float) minimum);
			}
		}
		return p;
	}
};

struct KNN {
	KNN(float(*_function_ptr_Distance)(const DYNPoint &, const DYNPoint &))
		: function_ptr_Distance(_function_ptr_Distance)
	{
	}

	std::vector<std::pair<DYNPoint, unsigned int>> trainingData{}; // default initialize on creation

	float(*function_ptr_Distance)(const DYNPoint &, const DYNPoint &) = 0;

	// just sets the training data (no actual training required)
	void TrainKNN(const std::vector<std::pair<DYNPoint, unsigned int>> &dataset) {
		trainingData.clear();
		trainingData = dataset;
	}

	static bool compareByDistance(const std::pair<float, unsigned int> &a, const std::pair<float, unsigned int> &b) {
		return a.first < b.first;
	}


	int classify(const unsigned int k, const DYNPoint &A) const {
		int class_label = -1;

		if (k && function_ptr_Distance && trainingData.size()) {
			//distance, class label
			std::vector<std::pair<float, unsigned int>> distancesLabels; 

			for (auto i = 0; i < trainingData.size(); i++) {
				float dist = function_ptr_Distance(A, trainingData[i].first);
				if (dist >= 0) {
					distancesLabels.emplace_back(dist, trainingData[i].second);
				}
			}

			std::sort(distancesLabels.begin(), distancesLabels.end(), compareByDistance);

			auto top = std::min(k, (unsigned int) (distancesLabels.size()));

			std::vector<int> labelCount; 
			auto maxCount = 0;
			auto topLabel = 0; 

			for (auto i = 0; i < top; i++) {
				auto label = distancesLabels[i].second;

				if (labelCount.size() <= label) {
					labelCount.resize(label + 1, 0);
				}

				labelCount[label]++;

				if (labelCount[label] > maxCount) {
					maxCount = labelCount[label];
					topLabel = label;
				}
			}
			class_label = topLabel;
		}
		return class_label;
	}
};

float DistanceManhattan(const DYNPoint &A, const DYNPoint &B) {
	if (A.data.size() != B.data.size() || A.data.empty()) { return -1;}
	float dist = 0.0f;

	for (auto i = 0; i < A.data.size(); i++) {
		dist += std::abs(A.data[i] - B.data[i]);
	}
	dist = dist / (float) (A.data.size());
	return dist;
}

float DistanceEuclid(const DYNPoint &A, const DYNPoint &B) {
	if (A.data.size() != B.data.size() || A.data.empty()) { return -1;}
	float dist = 0.0f;

	for (auto i = 0; i < A.data.size(); i++) {
		float currentDist = A.data[i] - B.data[i];
		dist += currentDist * currentDist;
	}
	dist = std::sqrt(dist / (float) (A.data.size()));
	return dist;
}

void createDataset(std::vector<std::pair<DYNPoint, unsigned int>> &dataset, const unsigned int amount, const unsigned int class_label,
				const unsigned int point_size, const int minimum, const int maximum) {

	if (amount > 0 && point_size>0 && minimum <= maximum) {
		
		for (unsigned int i = 0; i < amount; ++i) {
			DYNPoint p = DYNPoint::createRandomPoint(point_size, minimum, maximum);
			dataset.emplace_back(std::move(p), class_label);
		}

	}
}

void evaluateKNN(const std::vector<std::pair<DYNPoint, unsigned int>> &dataset, const KNN &Classifier, const unsigned int k) {
	if (!dataset.empty()) {
		float acc = 0;
		for (size_t i = 0; i < dataset.size(); i++) {
			if (static_cast<unsigned int>(Classifier.classify(k, dataset[i].first)) == dataset[i].second)
				acc++;
		}
		std::cout << "Accuracy: " << acc / float(dataset.size()) << std::endl;
	}
}









