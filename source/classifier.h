#include "file_handler.h"

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

    public:
        // Sets up the Classifier, loads training data, etc
        void SetUp();

        // Calculates one posterior probability for a given digit
        double GetPosteriorProbability(vector<vector<char>> image, int digit);

        // Gets all the posterior probabilities for a single image
        vector<double> GetAllPosteriorProbabilities(vector<vector<char>> image);

        // Classify a single image
        int ClassifyImage(int starting_row);

        vector<int> get_expected_digits() { return expected_digits; };
};