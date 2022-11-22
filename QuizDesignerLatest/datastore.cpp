#include "stdafx.h"
#include "datastore.h"
#include <iostream>

using namespace std;


DataStore::DataStore() { // initialize int and string member variables. Vector size will change dynamically as more questions are added by user
	int numques = 0;
	string title = "";
	vector<string> questions;
	vector<string> types;
}

DataStore::~DataStore() {};

string DataStore::getTitle() {
	return title;
}

void DataStore::setTitle(string title_s) {
	title = title_s;
	//quizzes.assign(i, name);
}

void DataStore::setQuestion(string quest) { // push question into vector
	questions.push_back(quest);
}

string DataStore::getQuestion(int i) {  // get question at index i
	return questions[i];
}

void DataStore::setType(string type) { // push type into vector
	types.push_back(type);
}
string DataStore::getType(int i) {  // get question type at index i
	return types[i];
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