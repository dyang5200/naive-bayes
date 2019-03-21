#include "naive_bayes_model.h"

vector<int> ReadLabels(string file_name) {
    // A vector that contains the expected labels for the digits in the training model.
    vector<int> vect_of_labels;

    ifstream input_file;
    input_file.open(file_name);

    if (input_file.is_open()) {
        while (!input_file.eof()) {
            // Read each line/integer from the expected integers file.
            string num;
            getline(input_file, num);

            // Add each number to vect_of_labels.
            char num_as_int = CHAR_TO_INT(num.at(0));
            vect_of_labels.push_back(num_as_int);
        }
        input_file.close();
    } else {
        cout << "Unable to open file" << endl;
    }
}

int main() {
    vector<int> vect_of_labels = ReadLabels(TRAINING_LABELS_FILENAME);

    return 0;
}