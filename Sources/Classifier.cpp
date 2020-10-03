#include "../Headers/Libraries.h"
#include "../Headers/Classifier.h"

using namespace std;

double calculateParameter(int featureValue, int classLabelValue, vector<vector<int>> features, int featurePosition, int countCL);
double getProbabilityFromParams(map<string, parameter> params, string name, int featureValue, int classLabelValue);
double calculateCorrectness(vector<int> testResults, vector<vector<int>> testingFeatures);
int getLastElement(vector<int> list);
int getCLTotalTrue(vector<vector<int>> features);
map<string, parameter> constructParameters(vector<vector<int>> features, set<string> vocabulary, int countCLTrue, int countCLFalse);

Classifier::Classifier(set<string> vocabulary, vector<vector<int>> trainingFeatures, vector<vector<int>> testingFeatures)
{
	this->vocabulary = vocabulary;
	this->trainingFeatures = trainingFeatures;
	this->testingFeatures = testingFeatures;
}

void Classifier::runTraining()
{
	//Calculate class label values
	countCLTrue = getCLTotalTrue(trainingFeatures);
	countCLFalse = vocabulary.size() - countCLTrue;
	percentCLTrue = (double)countCLTrue / (double)vocabulary.size();
	percentCLFalse = 1 - percentCLTrue;
	//Calculate and Construct the parameters
	parameters = constructParameters(trainingFeatures, vocabulary, countCLTrue, countCLFalse);
}

int getCLTotalTrue(vector<vector<int>> features)
{
	int total = 0;
	int trueTotal = 0;

	vector<vector<int>>::iterator itr;

	for (itr = features.begin(); itr < features.end(); itr++) {
		total++;
		int last = getLastElement(*itr);
		if (last == 1) {
			trueTotal++;
		}
	}
	return trueTotal;
}

int getLastElement(vector<int> list) {
	return list.back();
}

map<string, parameter> constructParameters(vector<vector<int>> features, set<string> vocabulary, int countCLTrue, int countCLFalse) {
	map<string, parameter> ps = map<string, parameter>();

	int vocabSize = vocabulary.size();
	set<string>::iterator vocabItr = vocabulary.begin();
	for (int i = 0; i < vocabSize; i++) {
		parameter p; 
		p.name = *vocabItr;
		p.pOfFalseFalse = calculateParameter(0, 0, features, i, countCLFalse);
		p.pOfFalseTrue = calculateParameter(0, 1, features, i, countCLTrue);
		p.pOfTrueFalse = calculateParameter(1, 0, features, i, countCLFalse);
		p.pOfTrueTrue = calculateParameter(1, 1, features, i, countCLTrue);
		ps[(*vocabItr)] = p;
		vocabItr++;
	}

	return ps;
}

double calculateParameter(int featureValue, int classLabelValue, vector<vector<int>> features, int featurePosition, int countCL) {
	int count = 0;
	for (vector<int> f : features) {
		if (f[featurePosition] == featureValue && f.back() == classLabelValue) {
			count++;
		}
	}
	//using uniform dirichlet priors (number of values a feature can take on is 2 (true or false))
	return ((double)(count + 1) / (double)(countCL + 2));
}

void Classifier::runTesting()
{
	int vocabSize = vocabulary.size();
	for (vector<int> f : testingFeatures) {
		//classlabel = true case
		double sum = 0;
		set<string>::iterator vocabItr = vocabulary.begin();
		for (int i = 0; i < vocabSize; i++) {
			sum += log(getProbabilityFromParams(parameters, *vocabItr, f[i], 1));
			vocabItr++;
		}
		double arg = log(percentCLTrue) + sum;
		if (arg >= (0.5)) {
			testResults.push_back(1);
		}
		else {
			testResults.push_back(0);
		}
	}

}

double getProbabilityFromParams(map<string, parameter> params, string name, int featureValue, int classLabelValue) {

	if (featureValue == 0 && classLabelValue == 0) {
		return params[name].pOfFalseFalse;
	}
	if (featureValue == 0 && classLabelValue == 1) {
		return params[name].pOfFalseTrue;
	}
	if (featureValue == 1 && classLabelValue == 0) {
		return params[name].pOfTrueFalse;
	}
	if (featureValue == 1 && classLabelValue == 1) {
		return params[name].pOfTrueTrue;
	}
	
	return -1;
}

void Classifier::displayResults()
{
	//For Testing
	/*for (parameter p : parameters) {
		cout << p.name << ": " << p.pOfFalseFalse << ", " << p.pOfFalseTrue << ", " << p.pOfTrueFalse << ", " << p.pOfTrueTrue << endl;
	}*/

	double percentCorrect = calculateCorrectness(testResults, testingFeatures);
	cout << "Accuracy: " << percentCorrect << endl;

}

double calculateCorrectness(vector<int> testResults, vector<vector<int>> testingFeatures) {
	int total = 0;
	int correct = 0;

	for (int i = 0; i < testResults.size(); ++i) {
		total++;
		vector<int> f = testingFeatures[i];
		if (testResults[i] == f.back()) {
			correct++;
		}
	}

	return ((double)correct / (double)total);
}