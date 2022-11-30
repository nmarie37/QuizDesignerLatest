#include "stdafx.h"
#include <filesystem>
#include "datastore.h"
#include <string>
#include <iostream>



using namespace std;


DataStore::DataStore() { // initialize int and string member variables. Vector size will change dynamically as more questions are added by user
	int numques = 0;
	string title = "";
	vector<string> questions;
	vector<string> types;
	vector<vector<string>> mult_ans;
	vector<int> ans_idx;
}

DataStore::~DataStore() {}

string DataStore::getTitle() {
	return title;
}

void DataStore::setTitle(string title_s) {
	title = title_s;
}

void DataStore::setQuestion(string quest) { // push question into vector
	questions.push_back(quest);
}

void DataStore::setQuestions(vector<string> quests) {
	questions = quests;
}

vector<string> DataStore::getQues() {  // get question at index i
	return questions;
}

void DataStore::removeQues(int i) {
	questions.erase(questions.begin() + i);
}

void DataStore::setType(string type) { // push type into vector
	types.push_back(type);
}

void DataStore::setTypes(vector<string> type) {
	types = type;
}

vector<string> DataStore::getTypes() {  // get question type at index i
	return types;
}

void DataStore::printTypes() { // loop through all question types and print
	for (int i = 0; i < types.size(); i++) {
		std::cout << types[i] << endl;
	}
}
void DataStore::printQues() { // loop through all questions and print
	for (int i = 0; i < questions.size(); i++) {
		std::cout << questions[i] << endl;
	}
}

int DataStore::getNumQues() {
	return numques;
}
void DataStore::setNumQues(int n) {
	numques = n;
}

void DataStore::setMultAns(vector<string> answers, int clear) {
	if (clear == 0) {
		mult_ans.clear();
	}
	else {
		mult_ans.push_back(answers);
	}
}
vector<vector<string>> DataStore::getMultAns() {
	return mult_ans;
}

void DataStore::setAnsIdx(vector<int> ans) {
	ans_idx = ans;
}

vector<int> DataStore::getAnsIdx() {
	return ans_idx;
}

void DataStore::pairSort(vector<string>& q, vector<string>& t) {
	pair<string, string> pairs[MAXQUES];

	for (int i = 0; i < q.size(); i++) {
		pairs[i].first = q[i];
		pairs[i].second = t[i];
	}

	std::sort(pairs, pairs + q.size());

	for (int i = 0; i < q.size(); i++) {
		q[i] = pairs[i].first;
		t[i] = pairs[i].second;
	}
}

void DataStore::pairSortInt(vector<string>& q, vector<int>& t) {
	pair<string, int> pairs[MAXQUES];

	for (int i = 0; i < q.size(); i++) {
		pairs[i].first = q[i];
		pairs[i].second = t[i];
	}

	std::sort(pairs, pairs + q.size());

	for (int i = 0; i < q.size(); i++) {
		q[i] = pairs[i].first;
		t[i] = pairs[i].second;
	}
}

void DataStore::fileWrite(DataStore d, vector<string> types, vector<string> quest) {
	//std::filesystem::path cwd = std::filesystem::current_path() / "filename.txt";
	//string filename = d.getTitle() + "_" + d.getTime() + ".csv";
	std::cout << "contents of d.getMultAns(): " << endl;
	for (int i = 0; i < d.getMultAns().size(); i++) {
		for (int j = 0; j < d.getMultAns()[i].size(); j++) {
			std::cout << d.getMultAns()[i][j] << endl;
		}
	}
	string filename = d.getTitle() + ".csv";
	ofstream file(filename);
	//cout << "cwd: " << cwd.string() << endl;
	std::cout << "Writing to file..." << endl;
	file << d.getTitle() << endl;
	file << "\nCourse:______________________" << endl;
	file << "\nName:_______________________" << endl;
	file <<"\n";

	int j = 0;
	int idx = 0;
	int q = 0;
	for (int i = 0; i < types.size(); i++) {
		if (q < numques) {
			q++;
		}
		if (i == 0)
		{
			file << "\n";
			file << types[i] << ": " << endl;
			file << q << ". ";
			file << quest[i] << endl;
			
			if (types[i] == "True/False") {
				file << "True:___" << endl;
				file << "False:___\n" << endl;
			}
			else if (types[i] == "Multiple Choice (Single Answer)") {
				file << "a) " << d.getMultAns()[0][0] << endl;
				file << "b) " << d.getMultAns()[0][1] << endl;
				file << "c) " << d.getMultAns()[0][2] << endl;
				file << "d) " << d.getMultAns()[0][3] << endl;
				if (idx < (d.getAnsIdx().size() - 1)) {
					idx = d.getAnsIdx()[++j];
				}
				
			}
			else if (types[i] == "Fill in the Blank") {
				file << "__________________________\n";
			}

		}
		else if (i > 0)
		{
			file << "\n";
			if (types[i] == types[i - 1]) {
				file << q << ". ";
				file << quest[i] << endl;
				if (types[i] == "True/False") {
					file << "True:___" << endl;
					file << "False:___\n" << endl;
				}
				else if (types[i] == "Multiple Choice (Single Answer)") {
					std::cout << "i > 0 idx: " << idx << endl;
					file << "a) " << d.getMultAns()[idx][0] << endl;
					file << "b) " << d.getMultAns()[idx][1] << endl;
					file << "c) " << d.getMultAns()[idx][2] << endl;
					file << "d) " << d.getMultAns()[idx][3] << endl;
					if (idx < (d.getAnsIdx().size() - 1)) {
						idx = d.getAnsIdx()[++j];
					}
				}
				else if (types[i] == "Fill in the Blank") {
					file << "__________________________\n";
				}
			}
			else {
				file << types[i] << ": " << endl;
				file << q << ". ";
				file << quest[i] << endl;
				if (types[i] == "True/False") {
					file << "True:___" << endl;
					file << "False:___\n" << endl;
				}
				else if (types[i] == "Multiple Choice (Single Answer)") {
					file << "a) " << d.getMultAns()[idx][0] << endl;
					file << "b) " << d.getMultAns()[idx][1] << endl;
					file << "c) " << d.getMultAns()[idx][2] << endl;
					file << "d) " << d.getMultAns()[idx][3] << endl;
					if (idx < (d.getAnsIdx().size() - 1)) {
						idx = d.getAnsIdx()[++j];
					}
				}
				else if (types[i] == "Fill in the Blank") {
					file << "__________________________\n";
				}
			}
		}
		
	}
	file.close();
	std::cout << "File closed!" << endl;
}