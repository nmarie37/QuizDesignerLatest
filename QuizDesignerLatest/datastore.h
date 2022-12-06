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
	vector<vector<string>> mult_ans; // each multiple choice answer matches up with it's corresponding multiple choice question
	vector<string> mult_ques; // multiple choice questions
	vector<int> ans_idx; // multiple choice answer index
	int msg_clicked; // flag for if New or Open quiz is clicked

public:
	string getTitle(); // get quiz title
	void setTitle(string title); // set quiz title

	void setQuestion(string quest); // set question
	void setQuestions(vector<string> quests); // set questions
	vector<string> getQues(); // get question at index i
	void removeQues(int i); // remove question i

	void removeType(int i); // remove type i
	void setType(string quest); // set question type for specified question
	void setTypes(vector<string> type); // set types
	vector<string> getTypes(); // get question type for question at index i

	int getNumQues(); // get number of questions
	void setNumQues(int n); // set number of questions

	void setMultAns(vector<string> answers, int clear); // set or clear multiple choice answers
	void setMultQues(string q); // set multiple choice question
	string getMultQues(int i); // get multiple choice questoin
	void removeMultAns(int i); // remove multiple choice answer
	vector<vector<string>> getMultAns(); // get multiple choice answers

	void setAnsIdx(vector<int> ans); // set multiple choice answer index
	vector<int> getAnsIdx(); // get muiltiple choice answer indices

	void printTypes(); // print question types
	void printQues(); // print questions

	void pairSort(vector<string>& q, vector<string>& t); // sort pair of string vectors based on q
	void pairSortInt(vector<string>& q, vector<int>& t); // sort pair of string and int vectors based on q

	void fileWrite(DataStore d); // write quiz to file
	void fileRead(DataStore& d, ifstream& f); // read quiz from file

	void setMsgClicked(int i); // set flag for new or open quiz clicked in main()
	int getMsgClicked(); // get flag for new or open quiz clicked

	DataStore(); // default constructor
	~DataStore(); // destructor
};