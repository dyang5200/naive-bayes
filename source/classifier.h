#include "file_handler.h"
#include <iomanip>

#define DATA_FILE "data.txt"
#define CLASS_PROB_FILE "class_prob.txt"

class Classifier {
    private:
        // Contains the list of expected digits from the testlabels file
        vector<int> expected_digits = vector<int>(TOTAL_DIGITS);

        // A vector containing information about all images from the testimages file
        vector<vector<char>> all_images = vector<vector<char>>(expected_digits.size(), vector<char>(DIM));

        // A vector containing the class probability of each digit from training file
        vector<double> class_prob = vector<double>(TOTAL_DIGITS);

        // Contains the data from the training file
        vector<vector<vector<double>>> data = vector<vector<vector<double>>>(TOTAL_DIGITS, vector<vector<double>>(DIM, vector<double>(DIM)));

        // A vector containing the classifications of each integer
        // [digit expected][digit classified]
        vector<vector<double>> classifications = vector<vector<double>>(TOTAL_DIGITS, vector<double>(TOTAL_DIGITS));

        // The number of labels per each digit in testlabels file
        vector<double> count_per_digit = vector<double>(TOTAL_DIGITS);

        // Confusion matrix
        vector<vector<double>> confusion_matrix = vector<vector<double>>(TOTAL_DIGITS, vector<double>(TOTAL_DIGITS));

    public:
        // Sets up the Classifier, loads training data, etc
        void SetUp();

        // Calculates one posterior probability for a given digit
        double GetPosteriorProb(vector<vector<char>> image, int digit);

        // Gets all the posterior probabilities for a single image
        vector<double> GetAllPosteriorProbs(vector<vector<char>> image);

        // Creates a 2D vector representing a single image
        vector<vector<char>> CreateImageVector(int start_index);

        // Classify a single image
        int ClassifyImage(int start_index, int expected);

        // Creates the confusion matrix to show how accurate the model is
        vector<vector<double>> CreateConfusionMatrix();

        // Prints the confusion matrix
        void PrintConfusionMatrix();

        // Classifies all images in the testimages file. Returns the percentage of correct classifications
        double ClassifyAll(Classifier classifier);

        vector<int> get_expected_digits() { return expected_digits; };

        vector<vector<char>> get_all_images() { return all_images; };

        vector<vector<double>> get_confusion_matrix() { return confusion_matrix; };
};