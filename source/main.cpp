#include "main.h"

int main() {
    Classifier classifier;
    classifier.SetUp();
    classifier.ClassifyAll(classifier);
    classifier.PrintConfusionMatrix();
}