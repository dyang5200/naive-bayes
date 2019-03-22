#include "classifier.h"


vector<vector<vector<double>>> UpdateDataVect(vector<vector<vector<double>>> data) {
    // for (int digit = 0; digit < TOTAL_DIGITS; digit++) {
    //     for (int i = 0; i < data[digit]; i++) {
    //         for (int j = 0; j < data[digit][i]; j++) {
                
    //         }
    //     }
    // }
}

vector<vector<double>> GetOnePosteriorProbability(vector<vector<char>> image, vector<vector<vector<double>>> data, int digit,
                                                    vector<double> class_prob) {
    vector<vector<double>> probabilities = vector<vector<double>>(DIM, vector<double>(DIM));

    for (int i = 0; i < image.size(); i++) {
        for (int j = 0; j < image[i].size(); j++) {
            if (image[i][j] == ' ') {
                probabilities[i][j] = 1.0 - data[digit][i][j];
            } else {
                probabilities[i][j] = data[digit][i][j];
            }
        }
    }

    double probability = class_prob[digit];

    for (int i = 0; i < probabilities.size(); i++) {
        for (int j = 0; j < probabilities[i].size(); j++) {
            
        }
    }

    return probabilities;
}

vector<vector<double>> GetAllPosteriorProbabilities() {

}

int main() {
    vector<int> expected_digits = ReadLabelsFile(TEST_LABELS_FILENAME);

    vector<vector<char>> all_images = ReadImageFile(TEST_IMAGES_FILENAME);



}