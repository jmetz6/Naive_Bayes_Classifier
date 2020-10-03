#ifndef PRE_PROCESSOR_H
#define PRE_PROCESSOR_H

#include "./Libraries.h"

using namespace std;

static const string TRAINING_INPUT_FILENAME = "trainingSet.txt";
static const string TESTING_INPUT_FILENAME = "testSet.txt";
static const string TRAINING_OUTPUT_FILENAME = "preprocessed_train.txt";
static const string TESTING_OUTPUT_FILENAME = "preprocessed_test.txt";

class PreProcessor {
private:
	string trainingData;
	string testingData;
	set<string> vocabulary;
	vector<vector<int>> trainingFeatures;
	vector<vector<int>> testingFeatures;

public:
	//CONSTRUCTORS
	PreProcessor();

	//PROCEDURES
	void run();
	void toFile();

	//GETTERS
	set<string> getVocabulary();
	vector<vector<int>> getTrainingFeatures();
	vector<vector<int>> getTestingFeatures();

};

#endif