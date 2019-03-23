#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <math.h>

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::cin;
using std::ifstream;
using std::ofstream;

// K value for Laplace Smoothing
#define K 0.5
// Dimension of each image. Given to be 28.
#define DIM 28
// Total number of digits (0-9)
#define TOTAL_DIGITS 10
// Total number of images in testing file
#define NUM_IMAGES 5000
// Total number of lines in testing file
#define NUM_LINES NUM_IMAGES * DIM

class Model {
    private:
        // A 3D vector that contains data about the probabilities/counts of each digit
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

        // The probability that a pixel is black or gray
        double color_probability;

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

        vector<vector<vector<double>>> get_data() { return data; };

        vector<double> get_class_probabilities() { return class_probabilities; };

        void set_expected_digits(vector<int> input_digits) { expected_digits = input_digits; };

        void set_training_images(vector<vector<char>> input_vect) { training_images = input_vect; };
};