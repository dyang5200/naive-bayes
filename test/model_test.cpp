#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../source/model.h"

Model model;

// Creates a vector containing all the labels in a given file
// For ReadLabels testing purposes
vector<int> create_vect_of_labels(string file_name) {
    string url = "../source/";
    url += file_name;
    vector<int> vect_of_labels = model.ReadLabels(url);
    return vect_of_labels;
}

// Creates a 2D array containing info about the trainingimages file
// For ReadImageFiles testing purposes
char **create_image_arr(string file_name) {
    string url = "../source/";
    url += file_name;
    char **image_arr = model.ReadImageFile(url);
    return image_arr;
}

// ------------------------------- SET COUNT PER DIGIT TESTS -------------------------------

TEST_CASE("Tests SetCountPerDigit: TrainingLabels Not Initialized") {
    vector<int> count_per_digit = model.SetCountPerDigit();
    REQUIRE(10 == count_per_digit.size());
    REQUIRE(0 == count_per_digit[3]);
}

TEST_CASE("Tests SetCountPerDigit: Length") {
    vector<int> vect_of_labels = create_vect_of_labels(TRAINING_LABELS_FILENAME);
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

// ------------------------------- READ LABELS TESTS ------------------------------------

TEST_CASE("Tests ReadLabels: Nonexistant URL") {
    vector<int> vect_of_labels = create_vect_of_labels("badurl.txt");
    REQUIRE(0 == vect_of_labels.size());
}

TEST_CASE("Tests ReadLabels: Bad URL") {
    vector<int> vect_of_labels = create_vect_of_labels(TRAINING_IMAGES_FILENAME);
    REQUIRE(0 == vect_of_labels.size());
}

TEST_CASE("Tests ReadLabels: Vector Length") {
    vector<int> vect_of_labels = create_vect_of_labels(TRAINING_LABELS_FILENAME);
    REQUIRE(5000 == vect_of_labels.size());
}

TEST_CASE("Tests ReadLabels: Label Positions") {
    vector<int> vect_of_labels = create_vect_of_labels(TRAINING_LABELS_FILENAME);
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
    char **image_arr = create_image_arr(TRAINING_LABELS_FILENAME);
    REQUIRE(NULL == image_arr[0]);
}

TEST_CASE("Tests ReadImageFile: Image Position") {
    char **image_arr = create_image_arr(TRAINING_IMAGES_FILENAME);
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
    vector<int> vect_of_labels = create_vect_of_labels(TRAINING_LABELS_FILENAME);
    char **image_arr = create_image_arr(TRAINING_IMAGES_FILENAME);

    vector<vector<vector<double>>> data = model.IncrementPixelFrequency(0);
    REQUIRE(0 == data[5][0][0]);
    REQUIRE(0.5 == data[5][7][20]);
    REQUIRE(1 == data[5][7][16]);
}

TEST_CASE("Tests Increment Pixel Frequency: Multiple Images, Same Digit") {
    vector<int> vect_of_labels = create_vect_of_labels(TRAINING_LABELS_FILENAME);
    char **image_arr = create_image_arr(TRAINING_IMAGES_FILENAME);

    vector<vector<vector<double>>> data = model.IncrementPixelFrequency(0);
    data = model.IncrementPixelFrequency(11);
    REQUIRE(0 == data[5][0][0]);
    REQUIRE(2 == data[5][7][16]);
}

TEST_CASE("Tests Increment Pixel Frequency: Multiple Images, Different Digits") {
    vector<int> vect_of_labels = create_vect_of_labels(TRAINING_LABELS_FILENAME);
    char **image_arr = create_image_arr(TRAINING_IMAGES_FILENAME);

    vector<vector<vector<double>>> data = model.IncrementPixelFrequency(2);
    REQUIRE(0.5 == data[4][14][12]);
}