#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../source/classifier.h"

const double DELTA = 0.001;

Classifier classifier;

// Returns true if the two given values are within DELTA value way from each other
bool AreEquivalent(double first, double second) {
    return fabs(first - second) < DELTA;
}

// Returns true if the first number is greater than the second. False otherwise
bool IsGreaterThan(double first, double second) {
    if (first > second) {
        return true;
    }
    return false;
}

// Initializes classifier
vector<vector<char>> Initialize(int starting_index) {
    classifier.SetUp();
    vector<vector<char>> image = classifier.CreateImageVector(starting_index);
    return image;
}

// ------------------------------- GET POSTERIOR PROBABILITY TESTS ------------------------------------

TEST_CASE("Tests GetPosteriorProb: Image = 0, Digit = 0") {
    vector<vector<char>> image = Initialize(28);
    double prob = classifier.GetPosteriorProb(image, 0);
    REQUIRE(AreEquivalent(-78.65751270, prob));
}

TEST_CASE("Tests GetPosteriorProb: Image = 0, Digit = 3") {
    vector<vector<char>> image = Initialize(28);
    double prob = classifier.GetPosteriorProb(image, 3);
    REQUIRE(AreEquivalent(-110.002300991, prob));
}

TEST_CASE("Tests GetPosteriorProb: Image = 9, Digit = 5") {
    vector<vector<char>> image = Initialize(0);
    double prob = classifier.GetPosteriorProb(image, 5);
    REQUIRE(AreEquivalent(-91.87296, prob));
}

// ------------------------------- GET ALL POSTERIOR PROBABILITIES TESTS ------------------------------------

TEST_CASE("Tests GetAllPosteriorProbs: Image = 0") {
    vector<vector<char>> image = Initialize(28);
    vector<double> probs = classifier.GetAllPosteriorProbs(image);
    REQUIRE(AreEquivalent(-78.6579, probs[0]));
    REQUIRE(AreEquivalent(-105.106, probs[8]));
}

TEST_CASE("Tests GetAllPosteriorProbs: Image = 9") {
    vector<vector<char>> image = Initialize(0);
    vector<double> probs = classifier.GetAllPosteriorProbs(image);
    REQUIRE(AreEquivalent(-70.6831, probs[9]));
}

// ------------------------------- CLASSIFY IMAGE TESTS ---------------------------------------------

TEST_CASE("Tests ClassifyImage: Image = 0") {
    Classifier newClassifier;
    newClassifier.SetUp();
    int classification = newClassifier.ClassifyImage(27, 0);
    REQUIRE(0 == classification);
}

TEST_CASE("Tests ClassifyImage: Image = 2") {
    Classifier newClassifier;
    newClassifier.SetUp();
    int classification = newClassifier.ClassifyImage(56, 2);
    REQUIRE(2 == classification);
}

// ------------------------------- CREATE CONFUSION MATRIX TESTS ---------------------------------------------

TEST_CASE("Tests CreateConfusionMatrix: Select Values") {
    Classifier newClassifier;
    newClassifier.SetUp();
    newClassifier.ClassifyAll(newClassifier);
    vector<vector<double>> confusion_matrix = newClassifier.get_confusion_matrix();
    REQUIRE(AreEquivalent(0.8889, confusion_matrix[0][0]));
    REQUIRE(AreEquivalent(0.8400, confusion_matrix[3][3]));
    REQUIRE(AreEquivalent(0.01087, confusion_matrix[5][7]));
    REQUIRE(AreEquivalent(0.0, confusion_matrix[0][9]));
}

// ----------------------------------- CLASSIFIER TEST ------------------------------------------------

TEST_CASE("Tests Classifer") {
    classifier.SetUp();
    double percent_accurate = classifier.ClassifyAll(classifier);
    REQUIRE(IsGreaterThan(percent_accurate, 0.7));
}