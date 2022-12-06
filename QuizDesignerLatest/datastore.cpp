#include "stdafx.h"
#include <filesystem>
#include "datastore.h"
#include <string>
#include <iostream>

using namespace std;

DataStore::DataStore() { // initialize int and string member variables. Vector size will change dynamically as more questions are added by user
	int numques = 0; // number of questions in the quiz (1-15)
	string title = ""; // quiz title
	vector<string> questions; // each element is a quiz question
	vector<string> types; // each type matches up with its corresponding quiz in questions vector
	vector<vector<string>> mult_ans; // each multiple choice answer matches up with it's corresponding multiple choice question
	vector<string> mult_ques; // multiple choice questions
	vector<int> ans_idx; // multiple choice answer indices
	int msg_clicked; // flag for if New or Open quiz is clicked
}

DataStore::~DataStore() {}

string DataStore::getTitle() { // get quiz title
	return title;
}

void DataStore::setTitle(string title_s) { // set quiz title
	title = title_s;
}

void DataStore::setQuestion(string quest) { // push question into vector
	questions.push_back(quest);
}

void DataStore::setQuestions(vector<string> quests) { // set questions
	questions = quests;
}

vector<string> DataStore::getQues() {  // get question at index i
	return questions;
}

void DataStore::removeQues(int i) { // remove question i
	questions.erase(questions.begin() + i);
}

void DataStore::removeType(int i) { // remove type i
	types.erase(types.begin() + i);
}

void DataStore::setType(string type) { // push type into vector
	types.push_back(type);
}

void DataStore::setTypes(vector<string> type) { // set types
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

int DataStore::getNumQues() { // get number of questions
	return numques;
}
void DataStore::setNumQues(int n) { // set number of questions
	numques = n;
}

void DataStore::setMultAns(vector<string> answers, int clear) { // set or clear multiple choice answers
	if (clear == 0) {
		mult_ans.clear();
	}
	else {
		mult_ans.push_back(answers);
	}
}

void DataStore::setMultQues(string q) { // set multiple choice question
	mult_ques.push_back(q);
}

string DataStore::getMultQues(int i) { // get multiple choice questoin
	return mult_ques[i];
}

void DataStore::removeMultAns(int i) { // remove multiple choice answer
	mult_ans.erase(mult_ans.begin() + i);
	ans_idx.erase(ans_idx.begin() + i);
	mult_ques.erase(mult_ques.begin() + i);
}

vector<vector<string>> DataStore::getMultAns() { // get multiple choice answers
	return mult_ans;
}

void DataStore::setAnsIdx(vector<int> ans) { // set multiple choice answer index
	ans_idx = ans;
}

vector<int> DataStore::getAnsIdx() { // get muiltiple choice answer indices
	return ans_idx;
}

void DataStore::setMsgClicked(int i) { // set flag for new or open quiz clicked in main()
	msg_clicked = i;
}
int DataStore::getMsgClicked() { // get flag for new or open quiz clicked
	return msg_clicked;
}

void DataStore::pairSort(vector<string>& q, vector<string>& t) { // sort pair of string vectors based on q
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

void DataStore::pairSortInt(vector<string>& q, vector<int>& t) { // sort pair of string and int vectors based on q

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

void DataStore::fileRead(DataStore& d, ifstream& f) { // read quiz from file
	string lineBuf; // line buffer to read file line by line
	string title; // string to hold quiz title
	vector<string> store_temp; // temporarily store line
	while (f) {
		getline(f, title);
		d.setTitle(title); // store title into DataStore
		getline(f, lineBuf);

		for (int i = 0; i < 5; i++) { // skip these lines as we do not need to store them
			getline(f, lineBuf);
		}

		while (f) {
			getline(f, lineBuf);
			store_temp.push_back(lineBuf);
		}
	}

	int max_cur = 0; // keep track of current max number of questions so we can label question numbers properly
	int max_new = 0;
	// temporary variables so as to not corrupt the actual data while parsing
	string store_temp_s;
	vector<string> answers;
	vector<string> store_temp_ans = store_temp;
	vector<string> store_temp_copy = store_temp;
	vector<string> store_temp_mult = store_temp;
	// parse the data
	for (int i = 0; i < store_temp.size(); i++) {
		// first question
		if (i == 1) {
			if (store_temp[i - 1] == "Multiple Choice (Single Answer): ") {
				store_temp[i - 1].pop_back(); // remove the ": " at the end
				store_temp[i - 1].pop_back();
				d.setType(store_temp[i - 1]);
				answers.push_back(store_temp_ans[i + 1].erase(0,3)); // store answers without the "a) ", "b) " prefix, etc.
				answers.push_back(store_temp_ans[i + 2].erase(0,3));
				answers.push_back(store_temp_ans[i + 3].erase(0,3));
				answers.push_back(store_temp_ans[i + 4].erase(0,3));
				d.setMultQues(store_temp_mult[i].erase(0,3));
				d.setMultAns(answers, 1);
				answers.clear();
			}
			else if (store_temp[i - 1] == "Fill in the Blank: "){
				store_temp[i - 1].pop_back();
				store_temp[i - 1].pop_back();
				d.setType(store_temp[i - 1]);
			}
			else if (store_temp[i - 1] == "True/False: ") {
				store_temp[i - 1].pop_back();
				store_temp[i - 1].pop_back();
				d.setType(store_temp[i - 1]);
			}
			d.setQuestion(store_temp_copy[i].erase(0, 3));
			store_temp_s = store_temp[i];
			max_cur = store_temp_s[0] - '0';
			continue;
		}
		// we know we are at a question if the prefix is a number folowed by a period
		else if (isdigit(store_temp[i][0])) {
			if (store_temp[i - 1] == "Multiple Choice (Single Answer): ") {
				store_temp[i - 1].pop_back();
				store_temp[i - 1].pop_back();
				d.setType(store_temp[i - 1]);
				answers.push_back(store_temp_ans[i + 1].erase(0,3));
				answers.push_back(store_temp_ans[i + 2].erase(0,3));
				answers.push_back(store_temp_ans[i + 3].erase(0,3));
				answers.push_back(store_temp_ans[i + 4].erase(0,3));
				d.setMultQues(store_temp_mult[i].erase(0, 3));
				d.setMultAns(answers, 1);
				answers.clear();
			}
			else if (store_temp[i - 1] == "Fill in the Blank: ") {
				store_temp[i - 1].pop_back();
				store_temp[i - 1].pop_back();
				d.setType(store_temp[i - 1]);
			}
			else if (store_temp[i - 1] == "True/False: ") {
				store_temp[i - 1].pop_back();
				store_temp[i - 1].pop_back();
				d.setType(store_temp[i - 1]);
			}
			else if (store_temp[i - 1] == "") {
				d.setType(d.getTypes().back());

				if (d.getTypes().back() == "Multiple Choice (Single Answer)") {
					answers.push_back(store_temp_ans[i + 1].erase(0, 3));
					answers.push_back(store_temp_ans[i + 2].erase(0, 3));
					answers.push_back(store_temp_ans[i + 3].erase(0, 3));
					answers.push_back(store_temp_ans[i + 4].erase(0, 3));
					d.setMultQues(store_temp_mult[i].erase(0, 3));;
					d.setMultAns(answers, 1);
					answers.clear();
				}
			}
			d.setQuestion(store_temp_copy[i].erase(0, 3));
			store_temp_s = store_temp[i];
			max_new = store_temp_s[0] - '0';
			if (max_new > max_cur) {
				max_cur = max_new;
			}
		}
	}

	vector<int> setans_temp; // store multiple choice answers to temporarily sort if user clicked open
	for (int i = 0; i < d.getMultAns().size(); i++) {
		setans_temp.push_back(i);		
	}

	vector<string> multques_temp; // store multiple choice questions to temporarily sort if user clicked open
	for (int i = 0; i < setans_temp.size(); i++) {
		multques_temp.push_back(d.getMultQues(i));
	}
		if (multques_temp.size() > 1 && setans_temp.size() > 1) {
			d.pairSortInt(multques_temp, setans_temp);
		}

	// store these values to DataStore
	d.setAnsIdx(setans_temp);	
	d.setNumQues(max_cur);
	d.setTitle(title);
}


void DataStore::fileWrite(DataStore d) { // write quiz to file
	string filename = d.getTitle() + ".csv"; // grab title from DataStore
	ofstream file(filename); // use title to create filename: <title.csv>

	// write to file
	file << d.getTitle() << endl;
	file << "\nCourse:______________________" << endl;
	file << "\nName:_______________________" << endl;
	file <<"\n";

	int q = 0; // keep track of number of questions
	if (ans_idx.empty()) {
		ans_idx.push_back(0);
	}
	int* idx_ptr = &(ans_idx[0]); // pointer to first element in multiple choice answer indices
	int idx = *(idx_ptr); // dereference pointer
	for (int i = 0; i < types.size(); i++) {
		if (q < numques) {
			q++; // increment number of questions as we go until max configured is reached
		}
		// first question
		if (i == 0) {		
			file << "\n";
			file << types[i] << ": " << endl;
			file << q << ". ";
			file << questions[i] << endl;
			
			if (types[i] == "True/False") {
				file << "True:___" << endl;
				file << "False:___" << endl;
			}
			else if (types[i] == "Multiple Choice (Single Answer)") {
					file << "a) " << d.getMultAns()[idx][0] << endl;
					file << "b) " << d.getMultAns()[idx][1] << endl;
					file << "c) " << d.getMultAns()[idx][2] << endl;
					file << "d) " << d.getMultAns()[idx][3] << endl;

					idx = *(++idx_ptr); // increment multiple choice answer index
			}
			else if (types[i] == "Fill in the Blank") {
				file << "__________________________\n";
			}
		}
		// after first question
		else if (i > 0) {
			file << "\n";
			// if type of current question is the same as previous question
			if (types[i] == types[i - 1]) {
				file << q << ". ";
				file << questions[i] << endl;
				if (types[i] == "True/False") {
					file << "True:___" << endl;
					file << "False:___" << endl;
				}
				else if (types[i] == "Multiple Choice (Single Answer)") {
					file << "a) " << d.getMultAns()[idx][0] << endl;
					file << "b) " << d.getMultAns()[idx][1] << endl;
					file << "c) " << d.getMultAns()[idx][2] << endl;
					file << "d) " << d.getMultAns()[idx][3] << endl;

					idx = *(++idx_ptr); // increment multiple choice answer index
				}
				else if (types[i] == "Fill in the Blank") {
					file << "__________________________\n";
				}
			}
			// if this is a different type from previous question
			else {
				file << types[i] << ": " << endl;
				file << q << ". ";
				file << questions[i] << endl;
				if (types[i] == "True/False") {
					file << "True:___" << endl;
					file << "False:___" << endl;
				}
				else if (types[i] == "Multiple Choice (Single Answer)") {
					file << "a) " << d.getMultAns()[idx][0] << endl;
					file << "b) " << d.getMultAns()[idx][1] << endl;
					file << "c) " << d.getMultAns()[idx][2] << endl;
					file << "d) " << d.getMultAns()[idx][3] << endl;

					idx = *(++idx_ptr); // increment multiple choice answer index
				}
				else if (types[i] == "Fill in the Blank") {
					file << "__________________________\n";
				}
			}
		}
		
	}
	file.close(); // close the file
}