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
#define TOTAL_DIGITS 10
#define NUM_IMAGES 5000
#define NUM_LINES NUM_IMAGES * DIM

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
        //                  0: white
        //                  1: black or grey
        double data[TOTAL_DIGITS][DIM][DIM][1];

        // A 2D array that holds the pixel color values for the current number being inspected
        char training_images[NUM_IMAGES * DIM][DIM];

        // A vector containing all the expected numbers for the images.
        vector<int> expected_digits;

        // A vector with 10 positions (0-9) that contains the total number of each digit in the traininglabels file
        vector<int> total_digits = vector<int>(TOTAL_DIGITS);

    public:
        enum Digits {
            Zero = 0, One = 1, Two = 2, Three = 3, Four = 4,
            Five = 5,  Six = 6, Seven = 7, Eight = 8, Nine = 9
        };
        
        // Model default constructor
        Model() = default;

        // Reads in (in order) the expected integer labels for each digit in the trainingimages file
        vector<int> ReadLabels(string file_name);

        // Returns a vector that contains the total count of each digit in the traininglabels file
        vector<int> SetTotalDigits();

        // Reads in the trainingimages file
        // Returns a 2D char array that contains information about the pixels of the entire file
        char **ReadImageFile(string file_name);

        // Analyzes one image from the trainingimages data
        // starting_row: the row the image begins on
        int AnalyzeImage(int starting_row);
};