#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../source/file_reader.h"

const double DELTA = 0.0001;

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
    CreateExpectedDigits(TRAINING_LABELS_FILENAME);
    CreateImageArr(TRAINING_IMAGES_FILENAME);
}

// ------------------------------- READ LABELS TESTS ------------------------------------

TEST_CASE("Tests ReadLabelsFile: Nonexistant URL") {
    vector<int> vect_of_labels = CreateExpectedDigits("badurl.txt");
    REQUIRE(0 == vect_of_labels.size());
}

TEST_CASE("Tests ReadLabelsFile: Bad URL") {
    vector<int> vect_of_labels = CreateExpectedDigits(TRAINING_IMAGES_FILENAME);
    REQUIRE(0 == vect_of_labels.size());
}

TEST_CASE("Tests ReadLabelsFile: Vector Length") {
    vector<int> vect_of_labels = CreateExpectedDigits(TRAINING_LABELS_FILENAME);
    REQUIRE(5000 == vect_of_labels.size());
}

TEST_CASE("Tests ReadLabelsFile: Label Positions") {
    vector<int> vect_of_labels = CreateExpectedDigits(TRAINING_LABELS_FILENAME);
    REQUIRE(5 == vect_of_labels[0]);
    REQUIRE(1 == vect_of_labels[2162]);
    REQUIRE(2 == vect_of_labels[4999]);
}

// ------------------------------- READ IMAGE FILES TESTS ------------------------------------

TEST_CASE("Tests ReadImageFile: Nonexistant URL") {
    vector<vector<char>> image_vect = ReadImageFile("penguinpoppers.txt");
    REQUIRE(0 == image_vect.size());
}

TEST_CASE("Tests ReadImageFile: Bad URL Vector Length") {
    vector<vector<char>> image_vect = CreateImageArr(TRAINING_LABELS_FILENAME);
    REQUIRE(140000 == image_vect.size());
}

TEST_CASE("Tests ReadImageFile: Bad URL Vector Value") {
    vector<vector<char>> image_vect = CreateImageArr(TRAINING_LABELS_FILENAME);
    REQUIRE(0 == image_vect[0][0]);
}

TEST_CASE("Tests ReadImageFile: Length") {
    vector<vector<char>> image_vect = CreateImageArr(TRAINING_IMAGES_FILENAME);
    REQUIRE(140000 == image_vect.size());
}

TEST_CASE("Tests ReadImageFile: Image Position") {
    vector<vector<char>> image_vect = CreateImageArr(TRAINING_IMAGES_FILENAME);
    cout << image_vect[0][0] << endl;
    REQUIRE('+' == image_vect[72][5]);
    REQUIRE('#' == image_vect[235][13]);
    REQUIRE(' ' == image_vect[394][6]);
}