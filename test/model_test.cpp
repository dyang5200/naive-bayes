#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../source/model.h"

const double EPSILON = 0.0001;

Model model;

// Creates a vector containing all the labels in a given file
// For SetExpectedDigits testing purposes
vector<int> CreateExpectedDigits(string file_name) {
    string url = "../source/";
    url += file_name;
    vector<int> vect_of_labels = model.SetExpectedDigits(url);
    return vect_of_labels;
}

// Creates a 2D array containing info about the trainingimages file
// For ReadImageFiles testing purposes
char **CreateImageArr(string file_name) {
    string url = "../source/";
    url += file_name;
    char **image_arr = model.ReadImageFile(url);
    return image_arr;
}

// Initializes the training
void InitializeTraining() {
    CreateExpectedDigits(TRAINING_LABELS_FILENAME);
    CreateImageArr(TRAINING_IMAGES_FILENAME);
}

bool AreEquivalent(double first, double second) {
    return fabs(first - second) < EPSILON;
}

// ------------------------------- SET COUNT PER DIGIT TESTS -------------------------------

TEST_CASE("Tests SetCountPerDigit: TrainingLabels Not Initialized") {
    vector<int> count_per_digit = model.SetCountPerDigit();
    REQUIRE(10 == count_per_digit.size());
    REQUIRE(0 == count_per_digit[3]);
}

TEST_CASE("Tests SetCountPerDigit: Length") {
    vector<int> vect_of_labels = CreateExpectedDigits(TRAINING_LABELS_FILENAME);
    vector<int> count_per_digit = model.SetCountPerDigit();
    REQUIRE(10 == count_per_digit.size());
}

TEST_CASE("Tests SetCountPerDigit: Number of Digits") {
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

// ------------------------------- SET EXPECTED DIGITS TESTS ------------------------------------

TEST_CASE("Tests SetExpectedDigits: Nonexistant URL") {
    vector<int> vect_of_labels = CreateExpectedDigits("badurl.txt");
    REQUIRE(0 == vect_of_labels.size());
}

TEST_CASE("Tests SetExpectedDigits: Bad URL") {
    vector<int> vect_of_labels = CreateExpectedDigits(TRAINING_IMAGES_FILENAME);
    REQUIRE(0 == vect_of_labels.size());
}

TEST_CASE("Tests SetExpectedDigits: Vector Length") {
    vector<int> vect_of_labels = CreateExpectedDigits(TRAINING_LABELS_FILENAME);
    REQUIRE(5000 == vect_of_labels.size());
}

TEST_CASE("Tests SetExpectedDigits: Label Positions") {
    vector<int> vect_of_labels = CreateExpectedDigits(TRAINING_LABELS_FILENAME);
    REQUIRE(5 == vect_of_labels[0]);
    REQUIRE(1 == vect_of_labels[2162]);
    REQUIRE(2 == vect_of_labels[4999]);
}

// ------------------------------- READ IMAGE FILES TESTS ------------------------------------

TEST_CASE("Tests ReadImageFile: Nonexistant URL") {
    char **image_arr = model.ReadImageFile("penguinpoppers.txt");
    REQUIRE(NULL == image_arr[0]);
}

TEST_CASE("Tests ReadImageFile: Bad URL") {
    char **image_arr = CreateImageArr(TRAINING_LABELS_FILENAME);
    REQUIRE(NULL == image_arr[0]);
}

TEST_CASE("Tests ReadImageFile: Image Position") {
    char **image_arr = CreateImageArr(TRAINING_IMAGES_FILENAME);
    cout << image_arr[0][0] << endl;
    REQUIRE(1 == 1);
    REQUIRE('+' == image_arr[72][5]);
    // REQUIRE(' ' == image_arr[72][5]);
    // REQUIRE('#' == image_arr[72][5]);
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
    CreateExpectedDigits(TRAINING_LABELS_FILENAME);
    model.SetCountPerDigit();
    vector<vector<vector<double>>> data = model.CalculatePixelProbability();

    REQUIRE(AreEquivalent(0.2704, data[0][16][23]));
    REQUIRE(AreEquivalent(0.1653, data[3][11][10]));
    REQUIRE(AreEquivalent(0.0, data[8][24][25]));
}

// ------------------------------- CALCULATE CLASS PROBABILITY TESTS ------------------------------------

TEST_CASE("Tests CalculateClassProbability: Probabilities") {
    CreateExpectedDigits(TRAINING_LABELS_FILENAME);
    model.SetCountPerDigit();
    vector<double> class_prob = model.CalculateClassProbability();

    REQUIRE(AreEquivalent(0.0958, class_prob[0]));
    REQUIRE(AreEquivalent(0.1126, class_prob[1]));
    REQUIRE(AreEquivalent(0.0868, class_prob[5]));
}

TEST_CASE("Tests CalculateClassProbability: Total Probabilities") {
    CreateExpectedDigits(TRAINING_LABELS_FILENAME);
    model.SetCountPerDigit();
    vector<double> class_prob = model.CalculateClassProbability();

    double total_prob = 0;
    for (int i = 0; i < class_prob.size(); i++) {
        total_prob += class_prob[i];
    }

    REQUIRE(AreEquivalent(1.0, total_prob));
}