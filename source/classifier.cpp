#include "classifier.h"

void Classifier::SetUp() {
    expected_digits = ReadLabelsFile(TEST_LABELS_FILENAME);
    all_images = ReadImageFile(TEST_IMAGES_FILENAME);

    // class_prob = model.get_class_probabilities();
    // data = model.get_data();

    class_prob = LoadClassProbabilities(CLASS_PROB_FILE);
    data = LoadModel(DATA_FILE);
}

double Classifier::GetPosteriorProb(vector<vector<char>> image, int digit) {
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

    double probability = log10(class_prob[digit]);

    for (int i = 0; i < probabilities.size(); i++) {
        for (int j = 0; j < probabilities[i].size(); j++) {
            probability += log10(probabilities[i][j]);
        }
    }

    return probability;
}

vector<double> Classifier::GetAllPosteriorProbs(vector<vector<char>> image) {

    vector<double> posterior_probabilities = vector<double>(TOTAL_DIGITS);
    for (int digit = 0; digit < TOTAL_DIGITS; digit++) {
        posterior_probabilities[digit] = GetPosteriorProb(image, digit);
    }

    return posterior_probabilities;
}

vector<vector<char>> Classifier::CreateImageVector(int start_index) {
    vector<vector<char>> image = vector<vector<char>>(DIM, vector<char>(DIM));

    for (int i = start_index; i < start_index + DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            image[i - start_index][j] = all_images[i][j];
        }
    }

    return image;
}

int Classifier::ClassifyImage(int start_index) {
    vector<vector<char>> image = CreateImageVector(start_index);

    vector<double> posterior_probabilities = GetAllPosteriorProbs(image);

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