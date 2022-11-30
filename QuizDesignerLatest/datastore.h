#pragma once
#include <vector>
#include <fstream>
#include <time.h>

#define MAXQUES 15

using namespace std;

// this class is used to store the questions, question types, number of questions, etc.
// the stored info will be exported to a .csv file for the user to use as their quiz
// this class also is used to allow the user to open a previously generated Quiz Designer quiz .csv file and edit 
class DataStore { 
private:
	int numques; // number of questions in the quiz (1-15)
	string title; // quiz title
	vector<string> questions; // each element is a quiz question
	vector<string> types; // each type matches up with its corresponding quiz in questions vector
	vector<vector<string>> mult_ans;
	vector<int> ans_idx;

public:
	string getTitle(); // get quiz title
	void setTitle(string title); // set quiz title
	void setQuestion(string quest); // set question
	void setQuestions(vector<string> quests); // set question
	vector<string> getQues(); // get question at index i
	void removeQues(int i);
	void setType(string quest); // set question type for specified question
	void setTypes(vector<string> type);
	vector<string> getTypes(); // get question type for question at index i
	int getNumQues();
	void setNumQues(int n);

	void setMultAns(vector<string> answers, int clear);
	vector<vector<string>> getMultAns();
	void setAnsIdx(vector<int> ans);
	vector<int> getAnsIdx();

	void printTypes(); // print question types
	void printQues(); // print questions

	void pairSort(vector<string>& q, vector<string>& t);
	void pairSortInt(vector<string>& q, vector<int>& t);
	void fileWrite(DataStore d, vector<string> types, vector<string> quest);

	DataStore(); // default constructor
	~DataStore(); // destructor
};