#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../source/file_handler.h"

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

Model SetUpAndTrainModel() {
    string label_url = "../source/";
    label_url += TRAINING_LABELS_FILENAME;

    string image_url = "../source/";
    image_url += TRAINING_IMAGES_FILENAME;

    Model model = TrainModel(label_url, image_url);
    return model;
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

// ------------------------------- TRAIN MODEL TESTS ------------------------------------

TEST_CASE("Tests TrainModel: Data Vector Size") {
    Model model = SetUpAndTrainModel();
    vector<vector<vector<double>>> data = model.get_data();
    REQUIRE(10 == data.size());
    REQUIRE(28 == data[0].size());
    REQUIRE(28 == data[0][0].size());
}

TEST_CASE("Tests TrainModel: Data Vector Values") {
    Model model = SetUpAndTrainModel();
    vector<vector<vector<double>>> data = model.get_data();
    REQUIRE(AreEquivalent(0.0, data[0][0][0]));
    REQUIRE(AreEquivalent(0.68037, data[4][12][18]));
}

TEST_CASE("Tests TrainModel: Class Probabilities Vector Size") {
    Model model = SetUpAndTrainModel();
    vector<double> class_prob = model.get_class_probabilities();
    REQUIRE(10 == class_prob.size());
}

TEST_CASE("Tests TrainModel: Class Probabilities Vector Values") {
    Model model = SetUpAndTrainModel();
    vector<double> class_prob = model.get_class_probabilities();
    REQUIRE(AreEquivalent(0.11, class_prob[7]));
    REQUIRE(AreEquivalent(0.107, class_prob[4]));
}

// ------------------------------- LOAD CLASS PROBABILITIES TESTS ------------------------------------

TEST_CASE("Tests LoadClassProbabilities: Vector Size") {
    Model model = SetUpAndTrainModel();
    SaveClassProbsToFile(model, "class_prob.txt");
    vector<double> class_prob = LoadClassProbabilities("class_prob.txt");
    REQUIRE(10 == class_prob.size());
}

TEST_CASE("Tests LoadClassProbabilities: Vector Values") {
    Model model = SetUpAndTrainModel();
    vector<double> class_prob = LoadClassProbabilities("class_prob.txt");
    REQUIRE(AreEquivalent(0.11, class_prob[7]));
    REQUIRE(AreEquivalent(0.107, class_prob[4]));
}

// ------------------------------- LOAD MODEL TESTS ---------------------------------------------------

TEST_CASE("Tests LoadModel: Vector Size") {
    Model model = SetUpAndTrainModel();
    vector<vector<vector<double>>> data = LoadModel("data.txt");
    REQUIRE(10 == data.size());
    REQUIRE(28 == data[0].size());
    REQUIRE(28 == data[0][0].size());

}

TEST_CASE("Tests LoadModel: Vector Values") {
    Model model = SetUpAndTrainModel();
    SaveToFile("data.txt", "class_prob.txt");
    vector<vector<vector<double>>> data = LoadModel("data.txt");
    REQUIRE(AreEquivalent(0.3486, data[0][15][10]));
}
