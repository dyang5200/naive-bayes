#include "main.h"

int main() {
    Classifier classifier;
    classifier.SetUp();
    vector<int> expected_digits = classifier.get_expected_digits();

    double correct = 0.0;

    for (int i = 0; i < expected_digits.size(); i++) {
        int classification = classifier.ClassifyImage(i * DIM);

        if (classification == expected_digits[i]) {
            correct++;
        }

        // cout << "MY CLASSIFICATION: " << classification << "         EXPECTED: " << expected_digits[i] << endl;
        // cout << "SIZE: " << expected_digits.size();
    }

    double percent_classified = correct / expected_digits.size();

    cout << "PERCENT: " << percent_classified << endl;
}