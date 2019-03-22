#include "file_reader.h"

vector<int> ReadLabelsFile(string file_name) {
    // A vector that contains the expected labels for the digits in the training model
    vector<int> vect_of_labels;

    ifstream input_file;
    input_file.open(file_name);

    if (input_file.is_open()) {
        // Reads entire labels file
        vect_of_labels = ReadAllIntegers(input_file, vect_of_labels);
        input_file.close();

    } else {
        cout << "Unable to open file" << endl;
    }
    return vect_of_labels;
}

vector<int> ReadAllIntegers(ifstream& input_file, vector<int> vect_of_labels) {
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

    return vect_of_labels;
}

vector<vector<char>> ReadImageFile(string file_name) {
    // A 2D vector that contains information about all the images in the trainingimages file
    vector<vector<char>> training_images;

    ifstream input_file;
    input_file.open(file_name);

    if (input_file.is_open()) {
        // Reads entire images file
        training_images = vector<vector<char>>(NUM_IMAGES * DIM, vector<char>(DIM));
        training_images = ReadAllLines(input_file, training_images);
        input_file.close();
    } else {
        cout << "Unable to open file" << endl;
    }
    return training_images;
}

vector<vector<char>> ReadAllLines(ifstream& input_file, vector<vector<char>> training_images) {
    for (int line_num = 0; line_num < NUM_LINES; line_num++) {
        string line;
        getline(input_file, line);

        // If the length of the line does not equal the dimension
        if (line.length() != DIM) {
            continue;
        }

        // Fill in 2D array
        for (int col = 0; col < DIM; col++) {
            training_images[line_num][col] = line.at(col);
        }
    }
    return training_images;
}