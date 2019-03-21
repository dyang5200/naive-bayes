#include <string>
#include <array>
#include <vector>
#include <iostream>
#include <fstream>

using std::string;
using std::array;
using std::vector;
using std::cout;
using std::endl;
using std::ifstream;
using std::cin;

// Dimension of each image. Given to be 28.
#define DIM 28

// Converts a char into an integer
#define CHAR_TO_INT(c) (c -'0')

// Filenames for training and test files.
#define TRAINING_IMAGES_FILENAME "trainingimages"
#define TRAINING_LABELS_FILENAME "traininglabels"
#define TEST_IMAGES_FILENAME "testimages"
#define TEST_LABELS_FILENAME "testlabels"


class Model {
    private:
        // A 4D array that contains data about each digit
        // First dimension: digit number 0-9
        // Second & Third dimension: 28x28 array of probabilities
        // Fourth dimension: color type 
        //                  0: ' ' / white
        //                  1: # / black
        //                  2: + / gray
        double training_data[1][DIM][DIM][1];

        // A 2D array that holds the pixel color values for the current number being inspected
        char curr_num[DIM][DIM];

    public:
        // Model default constructor.
        Model() = default;

        // Reads in (in order) the expected integer labels for each digit in the trainingimages file.
        vector<int> ReadLabels(string file_name);
};