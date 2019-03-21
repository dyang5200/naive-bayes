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

// ------------------------------- SET TOTAL DIGITS TESTS -------------------------------

TEST_CASE("Tests SetTotalDigits TrainingLabels Not Initialized") {
    vector<int> total_digits = model.SetTotalDigits();
    REQUIRE(10 == total_digits.size());
    REQUIRE(0 == total_digits[3]);
}

TEST_CASE("Tests SetTotalDigits Length") {
    vector<int> vect_of_labels = create_vect_of_labels(TRAINING_LABELS_FILENAME);
    vector<int> total_digits = model.SetTotalDigits();
    REQUIRE(10 == total_digits.size());
}

TEST_CASE("Tests SetTotalDigits Number of Digits") {
    vector<int> total_digits = model.SetTotalDigits();
    REQUIRE(479 == total_digits[0]);
    REQUIRE(563 == total_digits[1]);
    REQUIRE(488 == total_digits[2]);
    REQUIRE(493 == total_digits[3]);
    REQUIRE(535 == total_digits[4]);
    REQUIRE(434 == total_digits[5]);
    REQUIRE(501 == total_digits[6]);
    REQUIRE(550 == total_digits[7]);
    REQUIRE(462 == total_digits[8]);
    REQUIRE(495 == total_digits[9]);
}

// ------------------------------- READ LABELS TESTS ------------------------------------

TEST_CASE("Tests ReadLabels Nonexistant URL") {
    vector<int> vect_of_labels = create_vect_of_labels("badurl.txt");
    REQUIRE(0 == vect_of_labels.size());
}

TEST_CASE("Tests ReadLabels Bad URL") {
    vector<int> vect_of_labels = create_vect_of_labels(TRAINING_IMAGES_FILENAME);
    REQUIRE(0 == vect_of_labels.size());
}

TEST_CASE("Tests ReadLabels Vector Length") {
    vector<int> vect_of_labels = create_vect_of_labels(TRAINING_LABELS_FILENAME);
    REQUIRE(5000 == vect_of_labels.size());
}

TEST_CASE("Tests ReadLabels Label Positions") {
    vector<int> vect_of_labels = create_vect_of_labels(TRAINING_LABELS_FILENAME);
    REQUIRE(5 == vect_of_labels[0]);
    REQUIRE(1 == vect_of_labels[2162]);
    REQUIRE(2 == vect_of_labels[4999]);
}

// ------------------------------- READ IMAGE FILES TESTS ------------------------------------

TEST_CASE("Tests ReadImageFile Nonexistant URL") {
    char **image_arr = model.ReadImageFile("penguinpoppers.txt");
    REQUIRE(NULL == image_arr[0]);
}

TEST_CASE("Tests ReadImageFile Bad URL") {
    char **image_arr = create_image_arr(TRAINING_LABELS_FILENAME);
    REQUIRE(NULL == image_arr[0]);
}

// TEST_CASE("Tests ReadImageFile Image Position") {
//     char **image_arr = create_image_arr(TRAINING_IMAGES_FILENAME);
//     cout << image_arr[0][0] << endl;
//     REQUIRE(1 == 1);
//     REQUIRE('+' == image_arr[72][5]);
//     // REQUIRE(' ' == image_arr[72][5]);
//     // REQUIRE('#' == image_arr[72][5]);
// }