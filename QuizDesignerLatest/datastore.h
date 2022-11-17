#pragma once
#include <vector>
#include <fstream>

using namespace std;

class datastore {
private:
	int numques;
	string title;
	vector<string> questions;
	vector<string> types;

public:
	string getTitle();
	void setTitle(string title);
	void setQuestion(string quest);
	string getQuestion(int i);
	void setType(string quest);
	string getType(int i);
	void printTypes();
	void printQues();

	datastore();
	~datastore();
};