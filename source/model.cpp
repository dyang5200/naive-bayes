#include "model.h"

vector<int> Model::ReadLabels(string file_name) {
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
        input_file.close();

    } else {
        cout << "Unable to open file" << endl;
    }

    return vect_of_labels;
}

char** Model::ReadImageFile(string file_name) {
    // A 2D char array that contains information about all the images in the trainingimages file
    char **image_arr = new char *[NUM_IMAGES * DIM];

    string line;
    ifstream input_file;
    input_file.open(TRAINING_IMAGES_FILENAME);

    if (input_file.is_open()) {

        // Read line for every line in the file
        for (int line_num = 0; line_num < NUM_LINES; line_num++) {
            getline(input_file, line);

            if (line.length() != DIM) {
                continue;
            }
            
            // Fill in 2D array
            image_arr[line_num] = new char[DIM];
            for (int col = 0; col < DIM; col++) {
                image_arr[line_num][col] = line.at(col);
            }
        }
        input_file.close();

    } else {
        cout << "Unable to open file" << endl;
    }
    return image_arr;
}

// int main() {
//     char **num = ReadFile(TRAINING_IMAGES_FILENAME);
    
//     for (int i = 0; i < NUM_IMAGES * DIM; i++) {
//         for (int j = 0; j < DIM; j++) {
//             cout << num[i][j];
//         }
//         cout << endl;
//     }

//     for (int i = 0; i < NUM_IMAGES * DIM; i++) {
//         delete[] num[i];
//     }
//     delete[] num;

//     return 0;
// }