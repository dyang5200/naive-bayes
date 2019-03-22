#include "model.h"

// Filenames for training and test files.
#define TRAINING_IMAGES_FILENAME "trainingimages"
#define TRAINING_LABELS_FILENAME "traininglabels"
#define TEST_IMAGES_FILENAME "testimages"
#define TEST_LABELS_FILENAME "testlabels"

// Reads in (in order) the expected integer labels for each digit in the traininglabels file
vector<int> ReadLabelsFile(string file_name);

// Reads all the integers in the traininglabels file
vector<int> ReadAllIntegers(ifstream& input_file, vector<int> vect_of_labels);

// Reads in the trainingimages file
// Returns a 2D char array that contains information about the pixels of the entire file
vector<vector<char>> ReadImageFile(string file_name);

// Read all lines in a given ifstream
vector<vector<char>> ReadAllLines(ifstream& input_file, vector<vector<char>> training_images);