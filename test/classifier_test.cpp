#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../source/classifier.h"

const double DELTA = 0.0001;

Classifier classifier;

// Returns true if the two given values are within DELTA value way from each other
bool AreEquivalent(double first, double second) {
    return fabs(first - second) < DELTA;
}

void Initialize() {

}

// ------------------------------- GET POSTERIOR PROBABILITY TESTS ------------------------------------

TEST_CASE("Tests GetPosterior Probability: ") {
    classifier.SetUp();
    vector<vector<char>> image = classifier.CreateImageVector(28);
    double prob = classifier.GetPosteriorProb(image, 0);
    REQUIRE(0.4 == prob);
}

// ------------------------------- CLASSIFIER TEST ----------------------------------------------------
TEST_CASE("Tests Classifer") {
    // REQUIRE(0.80 == percent_classified);
}