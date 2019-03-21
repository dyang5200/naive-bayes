#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../source/model.h"

Model model;

vector<int> create_vect_of_labels(string file_name) {
    string url = "../source/";
    url += file_name;
    vector<int> vect_of_labels = model.ReadLabels(url);
    return vect_of_labels;
}

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