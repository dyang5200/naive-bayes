#include "model.h"

using std::stod;

// Filenames for training and test files.
#define TRAINING_IMAGES_FILENAME "trainingimages"
#define TRAINING_LABELS_FILENAME "traininglabels"
#define TEST_IMAGES_FILENAME "testimages"
#define TEST_LABELS_FILENAME "testlabels"

// Converts a char into an integer
#define CHAR_TO_INT(c) (c -'0')

// Defines a new line
#define NEW_LINE "\r\n"

// Reads in (in order) the expected integer labels for each digit in the traininglabels file
vector<int> ReadLabelsFile(string file_name);

// Reads all the integers in the traininglabels file
vector<int> ReadAllIntegers(ifstream& input_file, vector<int> vect_of_labels);

// Reads in the trainingimages file
// Returns a 2D char array that contains information about the pixels of the entire file
vector<vector<char>> ReadImageFile(string file_name);

// Read all lines in a given ifstream
vector<vector<char>> ReadAllLines(ifstream& input_file, vector<vector<char>> training_images);

// Trains a model
Model TrainModel(string labels_filename, string images_filename);

// Saves the vector of data probabilities from a model to a file
void SaveToFile(string data_filename, string class_prob_filename);

// Saves the class probabilities to a different file
void SaveClassProbsToFile(Model model, string file_name);

// Loads a model
vector<vector<vector<double>>> LoadModel(string file_name);

// Loads the class probabilities
vector<double> LoadClassProbabilities(string file_name);