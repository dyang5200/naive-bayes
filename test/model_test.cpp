#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../source/file_handler.h"

const double DELTA = 0.0001;

Model model;

// Returns true if the two given values are within DELTA value way from each other
bool AreEquivalent(double first, double second) {
    return fabs(first - second) < DELTA;
}

// Creates a vector containing all the labels in a given file
// For ReadLabelsFile testing purposes
vector<int> CreateExpectedDigits(string file_name) {
    string url = "../source/";
    url += file_name;
    vector<int> vect_of_labels = ReadLabelsFile(url);
    return vect_of_labels;
}

// Creates a 2D array containing info about the trainingimages file
// For ReadImageFiles testing purposes
vector<vector<char>> CreateImageArr(string file_name) {
    string url = "../source/";
    url += file_name;
    vector<vector<char>> image_vect = ReadImageFile(url);
    return image_vect;
}

// Initializes the training
void InitializeTraining() {
    model.set_expected_digits(CreateExpectedDigits(TRAINING_LABELS_FILENAME));
    model.set_training_images(CreateImageArr(TRAINING_IMAGES_FILENAME));
}

// ------------------------------- SET COUNT PER DIGIT TESTS --------------------------------------

TEST_CASE("Tests SetCountPerDigit: TrainingLabels Not Initialized") {
    vector<int> count_per_digit = model.SetCountPerDigit();
    REQUIRE(10 == count_per_digit.size());
    REQUIRE(0 == count_per_digit[3]);
}

TEST_CASE("Tests SetCountPerDigit: Length") {
    InitializeTraining();
    vector<int> count_per_digit = model.SetCountPerDigit();
    REQUIRE(10 == count_per_digit.size());
}

TEST_CASE("Tests SetCountPerDigit: Number of Digits") {
    InitializeTraining();
    vector<int> count_per_digit = model.SetCountPerDigit();
    REQUIRE(479 == count_per_digit[0]);
    REQUIRE(563 == count_per_digit[1]);
    REQUIRE(488 == count_per_digit[2]);
    REQUIRE(493 == count_per_digit[3]);
    REQUIRE(535 == count_per_digit[4]);
    REQUIRE(434 == count_per_digit[5]);
    REQUIRE(501 == count_per_digit[6]);
    REQUIRE(550 == count_per_digit[7]);
    REQUIRE(462 == count_per_digit[8]);
    REQUIRE(495 == count_per_digit[9]);
}

// ------------------------------- INCREMENT PIXEL FREQUENCY TESTS ------------------------------------

TEST_CASE("Tests Increment Pixel Frequency: Array Size") {
    vector<vector<vector<double>>> data = model.get_data();
    REQUIRE(10 == data.size());
    REQUIRE(28 == data[0].size());
    REQUIRE(28 == data[0][0].size());
}

TEST_CASE("Tests Increment Pixel Frequency: One Image") {
    InitializeTraining();
    vector<vector<vector<double>>> data = model.IncrementPixelFrequency(0);
    REQUIRE(0 == data[5][0][0]);
    REQUIRE(0.5 == data[5][7][20]);
    REQUIRE(1 == data[5][7][16]);
}

TEST_CASE("Tests Increment Pixel Frequency: Multiple Images, Same Digit") {
    InitializeTraining();
    vector<vector<vector<double>>> data = model.IncrementPixelFrequency(0);
    data = model.IncrementPixelFrequency(11);
    REQUIRE(0 == data[5][0][0]);
    REQUIRE(2 == data[5][7][16]);
}

TEST_CASE("Tests Increment Pixel Frequency: Multiple Images, Different Digits") {
    InitializeTraining();
    vector<vector<vector<double>>> data = model.IncrementPixelFrequency(2);
    REQUIRE(0.5 == data[4][14][12]);
}

// ------------------------------- SET DATA VECTOR TESTS --------------------------------------------------

TEST_CASE("Tests SetDataVector: Random Pixel Counts") {
    InitializeTraining();
    vector<vector<vector<double>>> data = model.SetDataVector();
    REQUIRE(0 == data[1][3][3]);
    REQUIRE(246 == data[5][7][16]);
    REQUIRE(305 == data[7][15][15]);
}

// ------------------------------- CALCULATE PIXEL PROBABILITY TESTS ------------------------------------

TEST_CASE("Tests CalculatePixelProbability: Probabilities") {
    InitializeTraining();
    model.SetCountPerDigit();
    vector<vector<vector<double>>> data = model.CalculatePixelProbability();

    REQUIRE(AreEquivalent(0.2704, data[0][16][23]));
    REQUIRE(AreEquivalent(0.1653, data[3][11][10]));
    REQUIRE(AreEquivalent(0.0, data[8][24][25]));
}

// ------------------------------- CALCULATE CLASS PROBABILITY TESTS ------------------------------------

TEST_CASE("Tests CalculateClassProbability: Probabilities") {
    InitializeTraining();
    model.SetCountPerDigit();
    vector<double> class_prob = model.CalculateClassProbability();

    REQUIRE(AreEquivalent(0.0958, class_prob[0]));
    REQUIRE(AreEquivalent(0.1126, class_prob[1]));
    REQUIRE(AreEquivalent(0.0868, class_prob[5]));
}

TEST_CASE("Tests CalculateClassProbability: Total Probabilities") {
    InitializeTraining();
    model.SetCountPerDigit();
    vector<double> class_prob = model.CalculateClassProbability();

    double total_prob = 0;
    for (int i = 0; i < class_prob.size(); i++) {
        total_prob += class_prob[i];
    }

    REQUIRE(AreEquivalent(1.0, total_prob));
}