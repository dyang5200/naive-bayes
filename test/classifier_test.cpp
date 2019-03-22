#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../source/classifier.h"

const double DELTA = 0.0001;

Classifier classifier;

// Returns true if the two given values are within DELTA value way from each other
bool AreEquivalent(double first, double second) {
    return fabs(first - second) < DELTA;
}

// Initializes everything
void Initialize() {
    vector<int> expected_digits = ReadLabelsFile(TEST_LABELS_FILENAME);
    vector<vector<char>> all_images = ReadImageFile(TEST_IMAGES_FILENAME);

    vector<double> class_prob = LoadClassProbabilities("class_prob.txt");
    vector<vector<vector<double>>> data = LoadModel("data.txt");
}

// ------------------------------- GET ONE POSTERIOR PROBABILITY TESTS ------------------------------------

TEST_CASE("Tests Classifer") {
    REQUIRE(0.80 == percent_classified);
}