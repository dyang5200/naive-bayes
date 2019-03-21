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
        return vect_of_labels;

    } else {
        cout << "Unable to open file" << endl;
    }

    return vect_of_labels;
}

// int main() {
//     vector<int> vect_of_labels = ReadLabels(TRAINING_LABELS_FILENAME);

//     cout << vect_of_labels.size() << endl;
//     return 0;
// }