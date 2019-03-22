#include "model.h"

vector<int> Model::SetExpectedDigits(string file_name) {
    // A vector that contains the expected labels for the digits in the training model.
    vector<int> vect_of_labels;

    ifstream input_file;
    input_file.open(file_name);

    if (input_file.is_open()) {

        while (!input_file.eof()) {
            // Read each line/integer from the expected integers file.
            string num;
            getline(input_file, num);

            // Continue to next line if there is an empty line or if the line does not contain one digit
            if (num.length() != 1) {
                continue;
            }

            // Add each number to vect_of_labels.
            char num_as_int = CHAR_TO_INT(num.at(0));
            vect_of_labels.push_back(num_as_int);
        }
        expected_digits = vect_of_labels;
        input_file.close();

    } else {
        cout << "Unable to open file" << endl;
    }

    return vect_of_labels;
}

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

char** Model::ReadImageFile(string file_name) {
    // A 2D char array that contains information about all the images in the trainingimages file
    char **image_arr = new char *[NUM_IMAGES * DIM];

    string line;
    ifstream input_file;
    input_file.open(file_name);

    if (input_file.is_open()) {

        // Read line for every line in the file
        for (int line_num = 0; line_num < NUM_LINES; line_num++) {
            getline(input_file, line);

            // If the length of the line does not equal the dimension
            if (line.length() != DIM) {
                continue;
            }

            // Fill in 2D array
            image_arr[line_num] = new char[DIM];
            for (int col = 0; col < DIM; col++) {
                training_images[line_num][col] = line.at(col);
                image_arr[line_num][col] = line.at(col);
            }
        }
        input_file.close();

    } else {
        cout << "Unable to open file" << endl;
    }
    return image_arr;
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

vector<vector<vector<double>>> Model::SetDataVector() {
    for (int i = 0; i < NUM_IMAGES; i++) {
        IncrementPixelFrequency(i);
    }
    return data;
}

vector<vector<vector<double>>> Model::CalculatePixelProbability() {
    for (int digit = 0; digit < TOTAL_DIGITS; digit++) {
        for (int i = 0; i < DIM; i++) {
            for (int j = 0; j < DIM; j++) {
                data[digit][i][j] = data[digit][i][j] / count_per_digit[digit];
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

vector<vector<vector<double>>> Model::get_data() {
    return data;
}