#include "stdafx.h"
#include "datastore.h"
#include <iostream>

using namespace std;


datastore::datastore() {
	int numques = 0;
	string title = "";
	vector<string> questions;
	vector<string> types;
}

datastore::~datastore() {};

string datastore::getTitle() {
	return title;
}

void datastore::setTitle(string title_s) {
	title = title_s;
	//quizzes.assign(i, name);
}

void datastore::setQuestion(string quest) {
	questions.push_back(quest);
}

string datastore::getQuestion(int i) {
	return questions[i];
}

void datastore::setType(string type) {
	types.push_back(type);
}
string datastore::getType(int i) {
	return types[i];
}

void datastore::printTypes() {
	for (int i = 0; i < types.size(); i++) {
		std::cout << types[i] << endl;
	}
}
void datastore::printQues() {
	for (int i = 0; i < questions.size(); i++) {
		std::cout << questions[i] << endl;
	}
}