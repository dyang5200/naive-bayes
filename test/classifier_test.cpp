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

TEST_CASE("Tests GetPosteriorProb: Image = 0, Digit = 0") {
    classifier.SetUp();
    vector<vector<char>> image = classifier.CreateImageVector(28);
    double prob = classifier.GetPosteriorProb(image, 0);
    REQUIRE(AreEquivalent(-78.6579, prob));
}

TEST_CASE("Tests GetPosteriorProb: Image = 0, Digit = 3") {
    classifier.SetUp();
    vector<vector<char>> image = classifier.CreateImageVector(28);
    double prob = classifier.GetPosteriorProb(image, 3);
    REQUIRE(AreEquivalent(-110.002300991, prob));
}

// ------------------------------- GET ALL POSTERIOR PROBABILITIES TESTS ------------------------------------

TEST_CASE("Tests GetAllPosteriorProbs: Image = 0") {
    classifier.SetUp();
    vector<vector<char>> image = classifier.CreateImageVector(28);
    vector<double> probs = classifier.GetAllPosteriorProbs(image);
    REQUIRE(AreEquivalent(-78.6579, probs[0]));
    REQUIRE(AreEquivalent(-105.106, probs[8]));
}

TEST_CASE("Tests GetAllPosteriorProbs: Image = 9") {
    classifier.SetUp();
    vector<vector<char>> image = classifier.CreateImageVector(0);
    vector<double> probs = classifier.GetAllPosteriorProbs(image);
    REQUIRE(AreEquivalent(-70.6831, probs[9]));
}

// ------------------------------- CLASSIFIER TEST ----------------------------------------------------
TEST_CASE("Tests Classifer") {
    // REQUIRE(0.80 == percent_classified);
}