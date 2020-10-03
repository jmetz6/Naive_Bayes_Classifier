#include "../Headers/Libraries.h"
#include "../Headers/PreProcessor.h"

using namespace std;

string readData(string fileName);
string stripPunctuation(string data);
set<string> createVocabulary(string data);
vector<vector<int>> createFeatureSet(string data, set<string> vocabulary);
bool stringContainsDigit(string s);


PreProcessor::PreProcessor()
{
	trainingData = "";
	testingData = "";
	set<string> vocabulary = set<string>();
	vector<vector<int>> trainingFeatures = vector<vector<int>>();
	vector<vector<int>> testingFeatures = vector<vector<int>>();
}

void PreProcessor::run()
{
	//Pre-Process Training Section
	trainingData = readData(TRAINING_INPUT_FILENAME);
	trainingData = stripPunctuation(trainingData);

	//Pre-Process Testing Section
	testingData = readData(TESTING_INPUT_FILENAME);
	testingData = stripPunctuation(testingData);

	//Create Vocabulary
	vocabulary = createVocabulary(trainingData);

	//Create Feature Set
	trainingFeatures = createFeatureSet(trainingData, vocabulary);
	testingFeatures = createFeatureSet(testingData, vocabulary);
}

string readData(string fileName) {
	ifstream inFile("./Resources/" + fileName);
	string data = "";
	if (inFile.is_open()) {
		string line = "";
		while (getline(inFile, line)) {
			data += line + '\n';
		}
		inFile.close();
	}
	else {
		cerr << ("FILE ERROR: could not open file: '" + fileName + "' in the Resources folder") << endl;
		exit(-1);
	}
	return data;
}

string stripPunctuation(string data) {
	//convert data to lower case
	transform(data.begin(), data.end(), data.begin(), ::tolower);

	//remove punctuation
	replace(data.begin(), data.end(), '\'', '%');
	replace(data.begin(), data.end(), '.', '%');
	replace(data.begin(), data.end(), '?', '%');
	replace(data.begin(), data.end(), '!', '%');
	replace(data.begin(), data.end(), ',', '%');
	replace(data.begin(), data.end(), '"', '%');
	replace(data.begin(), data.end(), ':', '%');
	replace(data.begin(), data.end(), ';', '%');
	replace(data.begin(), data.end(), '(', '%');
	replace(data.begin(), data.end(), ')', '%');
	replace(data.begin(), data.end(), '{', '%');
	replace(data.begin(), data.end(), '}', '%');
	replace(data.begin(), data.end(), '&', '%');
	replace(data.begin(), data.end(), '*', '%');
	replace(data.begin(), data.end(), '-', '%');

	//remove placeholder '$'
	data.erase(remove(data.begin(), data.end(), '%'), data.end());
	
	return data;
}

bool stringContainsDigit(string s) {
	if (s.find("0") != string::npos) {
		return true;
	}

	if (s.find("1") != string::npos) {
		return true;
	}

	if (s.find("2") != string::npos) {
		return true;
	}

	if (s.find("3") != string::npos) {
		return true;
	}

	if (s.find("4") != string::npos) {
		return true;
	}

	if (s.find("5") != string::npos) {
		return true;
	}

	if (s.find("6") != string::npos) {
		return true;
	}

	if (s.find("7") != string::npos) {
		return true;
	}

	if (s.find("8") != string::npos) {
		return true;
	}

	if (s.find("9") != string::npos) {
		return true;
	}

	return false;
}

set<string> createVocabulary(string data) {
	istringstream iss(data);
	set<string> v = set<string>();
	

	string word;
	while (getline(iss, word, ' ')) {	
		if ((word.compare("") != 0) && (word.compare(" ") != 0) && (word.compare("\n") != 0) && (word.compare("\t") != 0) && !stringContainsDigit(word)) {
			word.erase(remove(word.begin(), word.end(), ' '), word.end());
			word.erase(remove(word.begin(), word.end(), '\n'), word.end());
			v.insert(word);
		}
	}



	return v;
}

vector<vector<int>> createFeatureSet(string data, set<string> vocabulary) {
	vector<vector<int>> f = vector<vector<int>>();

	istringstream iss(data);
	string line;
	while (getline(iss, line, '\n')) {
		vector<int> s = vector<int>();
		for (string v : vocabulary) {
			if (line.find(v) != string::npos) {
				//found
				s.push_back(1);
			}
			else {
				//not found
				s.push_back(0);
			}
		}

		if (line.find(" 0 ") != string::npos) {
			s.push_back(0); //classlabel = 0
		}
		else {
			s.push_back(1); //classlabel = 1
		}

		f.push_back(s);
	}

	return f;
}

void PreProcessor::toFile()
{
	ofstream trainingOut;
	ofstream testingOut;

	trainingOut.open(TRAINING_OUTPUT_FILENAME);
	testingOut.open(TESTING_OUTPUT_FILENAME);

	//For Testing 
	//trainingOut << trainingData; //TESTING
	//testingOut << testingData; //TESTING

	//Print Vocabulary
	for (string word : vocabulary) {
		trainingOut << word << ", ";
		testingOut << word << ", ";
	}
	trainingOut << "classlabel" << endl;
	testingOut << "classlabel" << endl;

	trainingOut << endl;
	testingOut << endl;

	for (vector<int> v : trainingFeatures) {
		for (int i : v) {
			trainingOut << i << ", ";
		}
		trainingOut << endl << endl;
	}

	for (vector<int> v : testingFeatures) {
		for (int i : v) {
			testingOut << i << ", ";
		}
		testingOut << endl << endl;
	}

	trainingOut.close();
	testingOut.close();
}

set<string> PreProcessor::getVocabulary()
{
	return vocabulary;
}

vector<vector<int>> PreProcessor::getTrainingFeatures()
{
	return trainingFeatures;
}

vector<vector<int>> PreProcessor::getTestingFeatures()
{
	return testingFeatures;
}
