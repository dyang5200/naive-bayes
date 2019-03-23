#include "file_handler.h"

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

Model TrainModel(string labels_filename, string images_filename) {
    Model model;

    vector<int> expected_digits = ReadLabelsFile(labels_filename);
    model.set_expected_digits(expected_digits);

    vector<vector<char>> training_images = ReadImageFile(images_filename);
    model.set_training_images(training_images);

    model.SetCountPerDigit();
    model.SetDataVector();
    model.CalculatePixelProbability();
    model.CalculateClassProbability();

    return model;
}

void SaveToFile(string data_filename, string class_prob_filename) {
    ofstream output_file(data_filename);

    if (output_file.is_open()) {
        Model model = TrainModel(TRAINING_LABELS_FILENAME, TRAINING_IMAGES_FILENAME);
        vector<vector<vector<double>>> data = model.get_data();

        SaveClassProbsToFile(model, class_prob_filename);

        for (int digit = 0; digit < data.size(); digit++) {
            for (int i = 0; i < data[digit].size(); i++) {
                for (int j = 0; j < data[digit][i].size(); j++) {
                    output_file << data[digit][i][j] << NEW_LINE;
                }
            }
        }

        output_file.close();
    } else {
        cout << "Unable to open output file" << endl;
    }
}

void SaveClassProbsToFile(Model model, string file_name) {
    ofstream output_file(file_name);

    if (output_file.is_open()) {

        vector<double> class_prob = model.get_class_probabilities();
        for (int i = 0; i < class_prob.size(); i++) {
            output_file << class_prob[i] << NEW_LINE;
        }

    } else {
        cout << "Unable to open output file" << endl;
    }
}

vector<vector<vector<double>>> LoadModel(string file_name) {
    ifstream input_file;
    input_file.open(file_name);

    vector<vector<vector<double>>> data;

    if (input_file.is_open()) {
        data = vector<vector<vector<double>>>(TOTAL_DIGITS, vector<vector<double>>(DIM, vector<double>(DIM)));
        int total_lines = TOTAL_DIGITS * DIM * DIM;
        for (int line_n = 0; line_n < total_lines; line_n++) {
            string line;
            getline(input_file, line);
            if (line.length() == 0) {
                continue;
            }
            double prob = std::stod(line);

            // The digit is (current line number) / (784) since each digit contains 784 probabilities (one for each pixel)
            int digit = line_n / (DIM * DIM);
            // The total index of the rows in columns in a 1D array would be:
            int rc_index = line_n % (DIM * DIM);
            // Indeces of row and col in 2D array
            int row = rc_index / DIM;
            int col = rc_index % DIM;

            data[digit][row][col] = prob;
        }
        
        input_file.close();

    } else {
        cout << "Unable to open file" << endl;
    }

    return data;
}

vector<double> LoadClassProbabilities(string file_name) {
    ifstream input_file;
    input_file.open(file_name);
    
    vector<double> class_prob;

    if (input_file.is_open()) {
        class_prob = vector<double>(TOTAL_DIGITS);
        for (int i = 0; i < class_prob.size(); i++) {
            string line;
            getline(input_file, line);
            double prob = stod(line);
            class_prob[i] = prob;
        }
        input_file.close();
    } else {
        cout << "Unable to open file" << endl;
    }
    return class_prob;
}