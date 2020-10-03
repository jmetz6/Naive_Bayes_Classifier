#ifndef CLASSIFER_H
#define CLASSIFER_H

using namespace std;

typedef struct parameter {
	string name;
	double pOfFalseFalse;
	double pOfFalseTrue;
	double pOfTrueFalse;
	double pOfTrueTrue;
} parameter;

class Classifier {
private:
	set<string> vocabulary;
	vector<vector<int>> trainingFeatures;
	vector<vector<int>> testingFeatures;
	map<string, parameter> parameters;
	vector<int> testResults;

	int countCLTrue;
	int countCLFalse;
	double percentCLTrue;
	double percentCLFalse;

public:
	Classifier(set<string> vocabulary, vector<vector<int>> trainingFeatures, vector<vector<int>> testingFeatures);
	void runTraining();
	void runTesting();
	void displayResults();

};

#endif
