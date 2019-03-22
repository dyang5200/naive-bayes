#include "classifier.h"

double GetOnePosteriorProbability(vector<vector<char>> image, vector<vector<vector<double>>> data, int digit, double class_prob) {
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

    double probability = log2(class_prob);

    for (int i = 0; i < probabilities.size(); i++) {
        for (int j = 0; j < probabilities[i].size(); j++) {
            probability *= log2(probabilities[i][j]);
        }
    }

    return probability;
}

vector<double> GetAllPosteriorProbabilities(vector<vector<char>> image, vector<vector<vector<double>>> data, vector<double> class_prob) {

    vector<double> posterior_probabilities = vector<double>(TOTAL_DIGITS);
    for (int digit = 0; digit < TOTAL_DIGITS; digit++) {
        posterior_probabilities[digit] = GetOnePosteriorProbability(image, data, digit, class_prob[digit]);
    }

    return posterior_probabilities;
}

int ClassifyImage(vector<vector<char>> all_images, int starting_row, vector<vector<vector<double>>> data, vector<double> class_prob) {
    vector<vector<char>> image = vector<vector<char>>(DIM, vector<char>(DIM));

    for (int i = starting_row; i < starting_row + DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            image[i - starting_row][j] = all_images[i][j];
        }
    }

    vector<double> posterior_probabilities = GetAllPosteriorProbabilities(image, data, class_prob);

    double max_prob = posterior_probabilities[0];
    int most_possible_int = 0;
    for (int i = 1; i < posterior_probabilities.size(); i++) {
        if (posterior_probabilities[i] > max_prob) {
            max_prob = posterior_probabilities[i];
            most_possible_int = i;
        }
    }

    return most_possible_int;
}

int main() {
    vector<int> expected_digits = ReadLabelsFile(TEST_LABELS_FILENAME);
    vector<vector<char>> all_images = ReadImageFile(TEST_IMAGES_FILENAME);

    TrainModel(TRAINING_LABELS_FILENAME, TRAINING_IMAGES_FILENAME);

    SaveToFile("data.txt", "class_prob.txt");

    vector<double> class_prob = LoadClassProbabilities("class_prob.txt");
    vector<vector<vector<double>>> data = LoadModel("data.txt");

    double correct = 0.0;

    for (int i = 0; i < expected_digits.size(); i++) {
        int classification = ClassifyImage(all_images, i * DIM, data, class_prob);

        if (classification == expected_digits[i]) {
            correct++;
        }

        cout << "MY CLASSIFICATION: " << classification << "         EXPECTED: " << expected_digits[i] << endl;
        cout << "SIZE: " << expected_digits.size();
    }

    double percent_classified = correct / expected_digits.size();

    cout << "PERCENT: " << percent_classified << endl;
}