#include "classifier.h"

void Classifier::SetUp() {
    expected_digits = ReadLabelsFile(TEST_LABELS_FILENAME);
    all_images = ReadImageFile(TEST_IMAGES_FILENAME);
    class_prob = LoadClassProbabilities(CLASS_PROB_FILE);
    data = LoadModel(DATA_FILE);

    // Set count_per_digits
    for (int i = 0; i < expected_digits.size(); i++) {
        int expected = expected_digits[i];
        count_per_digit[expected] = count_per_digit[expected] + 1;
    }
}

double Classifier::GetPosteriorProb(vector<vector<char>> image, int digit) {
    // Calculate the probability of each pixel being the color that it is
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

    // Calculate the posterior probability: p(class) * p(pixel 1 color | class) * p(pixel 2 color | class) . . .
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

int Classifier::ClassifyImage(int start_index, int expected) {
    vector<vector<char>> image = CreateImageVector(start_index);
    vector<double> posterior_probabilities = GetAllPosteriorProbs(image);

    // Classify an image with the digit that corresponds to the maximum posterior probability
    double max_prob = posterior_probabilities[0];
    int digit_classified = 0;
    for (int i = 1; i < posterior_probabilities.size(); i++) {
        if (posterior_probabilities[i] > max_prob) {
            max_prob = posterior_probabilities[i];
            digit_classified = i;
        }
    }

    double previous_count = classifications[expected][digit_classified];
    classifications[expected][digit_classified] = previous_count + 1.0;

    return digit_classified;
}

vector<vector<double>> Classifier::CreateConfusionMatrix() {
    vector<vector<double>> confusion_matrix = vector<vector<double>>(TOTAL_DIGITS, vector<double>(TOTAL_DIGITS));
    for (int i = 0; i < classifications.size(); i++) {
        for (int j = 0; j < classifications[i].size(); j++) {
            confusion_matrix[i][j] = classifications[i][j] / count_per_digit[i];
        }
    }
    return confusion_matrix;
}

void Classifier::PrintConfusionMatrix() {
    // Round to 4 decimal points for each value
    cout << std::fixed;
    cout << std::setprecision(4);

    for (int i = 0; i < confusion_matrix.size(); i++) {
        for (int j = 0; j < confusion_matrix[i].size(); j++) {
            cout << confusion_matrix[i][j] << "    ";
        }
        cout << endl;
    }
}

double Classifier::ClassifyAll(Classifier classifier) {
    // Keep track of the correct number of classifications
    double correct = 0.0;
    for (int i = 0; i < expected_digits.size(); i++) {
        int classification = classifier.ClassifyImage(i * DIM, expected_digits[i]);
        if (classification == expected_digits[i]) {
            correct++;
        }
    }

    confusion_matrix = classifier.CreateConfusionMatrix();

    double percent_accurate = correct / expected_digits.size();
    return percent_accurate;
}