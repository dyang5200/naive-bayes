#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using std::string;
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

class Model {
    private:
        // A 3D vector that contains data about each digit
        // First dimension: digit number 0-9
        // Second & Third dimension: 28x28 array of probabilities
        //                  0: white
        //                0.5: gray
        //                  1: black
        vector<vector<vector<double>>> data = vector<vector<vector<double>>>(TOTAL_DIGITS, vector<vector<double>>(DIM, vector<double>(DIM)));

        // A 2D vector that holds the pixel color values for the current number being inspected
        vector<vector<char>> training_images = vector<vector<char>>(NUM_IMAGES * DIM, vector<char>(DIM));

        // A vector containing all the expected numbers for the images.
        vector<int> expected_digits;

        // A vector with 10 positions (0-9) that contains the total number of each digit in the traininglabels file
        vector<int> count_per_digit = vector<int>(TOTAL_DIGITS);

        // A vecctor containing the class probabilities for each digit class
        vector<double> class_probabilities = vector<double>(TOTAL_DIGITS);

    public:
        // Model default constructor
        Model() = default;

        // Returns a vector that contains the total count of each digit in the traininglabels file
        vector<int> SetCountPerDigit();

        // Sets the entire data vector with values. Calls IncrementPixelFrequency on everything
        vector<vector<vector<double>>> SetDataVector();

        // Analyzes one image from the trainingimages data
        // starting_row: the row the image begins on
        vector<vector<vector<double>>> IncrementPixelFrequency(int digit_index);

        // Calculates the pixel color probabilities of each pixel in each class.
        vector<vector<vector<double>>> CalculatePixelProbability();
        
        // Calculates the probability of each class
        // P(class) = (# training examples where class = c ) / (total training examples)
        vector<double> CalculateClassProbability();

        // Returns the data 3D vector
        vector<vector<vector<double>>> get_data();

        // Sets the expected_digits vector
        void set_expected_digits(vector<int> input_digits);

        // Sets the training_images vector
        void set_training_images(vector<vector<char>> input_vect);
};