// NaiveBayes.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "../Headers/Libraries.h"
#include "../Headers/PreProcessor.h"
#include "../Headers/Classifier.h"

using namespace std;

int main() {
	cout << "Pre-Processing... ";
	PreProcessor preProcessor = PreProcessor();
	preProcessor.run();
	preProcessor.toFile();
	cout << "Done." << endl;

	Classifier classifier = Classifier(preProcessor.getVocabulary(), preProcessor.getTrainingFeatures(), preProcessor.getTestingFeatures());
	cout << "Training" << endl;
	classifier.runTraining();
	cout << "Done." << endl;
	cout << "Testing" << endl;
	classifier.runTesting();
	cout << "Done." << endl << endl;
	cout << "Results - " << endl;
	classifier.displayResults();
}
