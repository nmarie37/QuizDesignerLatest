#pragma once
#include <vector>
#include <fstream>

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

public:
	string getTitle(); // get quiz title
	void setTitle(string title); // set quiz title
	void setQuestion(string quest); // set question
	string getQuestion(int i); // get question at index i
	void setType(string quest); // set question type for specified question
	string getType(int i); // get question type for question at index i
	int getNumQues();
	void setNumQues(int n);
	void printTypes(); // print question types
	void printQues(); // print questions

	DataStore(); // default constructor
	~DataStore(); // destructor
};