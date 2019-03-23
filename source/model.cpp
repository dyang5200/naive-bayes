#include "model.h"

vector<int> Model::SetCountPerDigit() {
    // If traininglabels was not analyzed yet
    if (expected_digits.size() == 0) {
        return count_per_digit;
    }

    // initialize count_per_digit vector
    for (int i = 0; i < TOTAL_DIGITS; i++) {
        count_per_digit[i] = 0;
    }

    // Increment each value in count_per_digit
    for (int i = 0; i < expected_digits.size(); i++) {
        int digit = expected_digits[i];
        count_per_digit[digit] += 1;
    }

    return count_per_digit;
}

vector<vector<vector<double>>> Model::SetDataVector() {
    for (int i = 0; i < NUM_IMAGES; i++) {
        IncrementPixelFrequency(i);
    }
    return data;
}

vector<vector<vector<double>>> Model::IncrementPixelFrequency(int digit_index) {
    // The digit the integer is expected to be
    int expected_num = expected_digits[digit_index];

    // The row # in trainingimages to start on
    int starting_row = digit_index * DIM;

    // Iterate through image. Add 1.0 if black, 0.5 if grey, and 0 if white.
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            if (training_images[starting_row + i][j] == '#') {
                data[expected_num][i][j] = data[expected_num][i][j] + 1.0;
            } else if (training_images[starting_row + i][j] == '+') {
                data[expected_num][i][j] = data[expected_num][i][j] + 0.5;
            }
        }
    }

    return data;
}

vector<vector<vector<double>>> Model::CalculatePixelProbability() {
    for (int digit = 0; digit < TOTAL_DIGITS; digit++) {
        for (int i = 0; i < DIM; i++) {
            for (int j = 0; j < DIM; j++) {
                data[digit][i][j] = (data[digit][i][j] + K) / (count_per_digit[digit] + (2 * K));
            }
        }
    }
    return data;
}

vector<double> Model::CalculateClassProbability() {
    for (int digit = 0; digit < TOTAL_DIGITS; digit++) {
        double count = count_per_digit[digit];
        class_probabilities[digit] = count / NUM_IMAGES;
    }
    return class_probabilities;
}