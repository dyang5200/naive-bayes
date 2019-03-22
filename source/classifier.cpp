#include "classifier.h"

int main() {
    Model model;

    vector<int> expected_digits = ReadLabels(TRAINING_LABELS_FILENAME);
    model.set_expected_digits(expected_digits);

    vector<vector<char>> training_images = ReadImageFile(TRAINING_IMAGES_FILENAME);
    model.set_training_images(training_images);

    model.SetCountPerDigit();
    model.SetDataVector();
    model.CalculatePixelProbability();
    model.CalculateClassProbability();

}