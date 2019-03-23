#include "main.h"

int main() {
    Classifier classifier;
    classifier.SetUp();
    double percent_correct = classifier.ClassifyAll(classifier);
    classifier.PrintConfusionMatrix();

    cout << endl << "Percent Correct: " << percent_correct << endl;
}