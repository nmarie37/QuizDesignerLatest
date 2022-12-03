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
	int msg_clicked;
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

void DataStore::setMsgClicked(int i) {
	msg_clicked = i;
}
int DataStore::getMsgClicked() {
	return msg_clicked;
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

void DataStore::fileRead(DataStore& d, ifstream& f) {
	string lineBuf;
	string title;
	string course;
	int i = 0;
	vector<string> store_temp;
	while (f) {
		getline(f, title);
		d.setTitle(title);
		getline(f, lineBuf);

		for (int i = 0; i < 5; i++) {
			getline(f, lineBuf);
		}

		while (f) {
			getline(f, lineBuf);
			store_temp.push_back(lineBuf);
		}
	}

	for (int i = 0; i < store_temp.size(); i++) {
		std::cout << store_temp[i] << endl;
	}

	int max_cur = 0;
	int max_new = 0;
	string store_temp_s;
	vector<string> answers;
	vector<string> store_temp_ans = store_temp;
	vector<string> store_temp_copy = store_temp;
	for (int i = 0; i < store_temp.size(); i++) {
		std::cout << "max_cur: " << max_cur << endl;
		if (i == 1) {
			//d.setType(store_temp[i - 1]);
			if (store_temp[i - 1] == "Multiple Choice (Single Answer): ") {
				store_temp[i - 1].pop_back();
				store_temp[i - 1].pop_back();
				d.setType(store_temp[i - 1]);
				answers.push_back(store_temp_ans[i + 1].erase(0,3));
				answers.push_back(store_temp_ans[i + 2].erase(0,3));
				answers.push_back(store_temp_ans[i + 3].erase(0,3));
				answers.push_back(store_temp_ans[i + 4].erase(0,3));
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
			std::cout << "inside if (i == 1)" << endl;
			continue;
		}
		else if (isdigit(store_temp[i][0])) {
			//d.setType(store_temp[i - 1]);
			cout << "store_temp[i-1] = " << store_temp[i - 1] << endl;
			if (store_temp[i - 1] == "Multiple Choice (Single Answer): ") {
				//store_temp[i - 1] = "Multiple Choice (Single Answer)";
				store_temp[i - 1].pop_back();
				store_temp[i - 1].pop_back();
				d.setType(store_temp[i - 1]);
				answers.push_back(store_temp_ans[i + 1].erase(0,3));
				answers.push_back(store_temp_ans[i + 2].erase(0,3));
				answers.push_back(store_temp_ans[i + 3].erase(0,3));
				answers.push_back(store_temp_ans[i + 4].erase(0,3));
				std::cout << "answers[0] = " << answers[0] << endl;
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
				cout << "duplicate question type here" << endl;
				d.setType(d.getTypes().back());
				if (d.getTypes().back() == "Multiple Choice (Single Answer)") {
					answers.push_back(store_temp_ans[i + 1].erase(0, 3));
					std::cout << "answers[0] = " << answers[0] << endl;
					answers.push_back(store_temp_ans[i + 2].erase(0, 3));
					std::cout << "answers[1] = " << answers[1] << endl;
					answers.push_back(store_temp_ans[i + 3].erase(0, 3));
					std::cout << "answers[2] = " << answers[2] << endl;
					answers.push_back(store_temp_ans[i + 4].erase(0, 3));
					std::cout << "answers[3] = " << answers[3] << endl;
					
					d.setMultAns(answers, 1);
					answers.clear();
				}
			}
			d.setQuestion(store_temp_copy[i].erase(0, 3));
			store_temp_s = store_temp[i];
			max_new = store_temp_s[0] - '0';
			std::cout << "inside else if " << endl;
			if (max_new > max_cur) {
				max_cur = max_new;
				std::cout << "inside else if if" << endl;
			}
		}
	}

	std::cout << "store_temp[0] = " << store_temp[0] << endl; // this should be the first question type
	for (int i = 0; i < d.getQues().size(); i++) {
		std::cout << "Question " << i << ": " << d.getQues()[i] << endl;
	}
	
	std::cout << "store_temp_copy: " << endl;
	for (int i = 0; i < store_temp_copy.size(); i++) {
		std::cout<<store_temp_copy[i] << endl;
	}

	std::cout << "Mult choice answers: " << endl;
	for (int i = 0; i < d.getMultAns().size(); i++) {
		for (int j = 0; j < 4; j++) {
			std::cout << d.getMultAns()[i][j] << endl;
		}
		
	}

	d.setNumQues(max_cur);
	d.setTitle(title);
}

//void DataStore::fileWrite(DataStore d, vector<string> types, vector<string> quest) {
void DataStore::fileWrite(DataStore d) {
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
	std::cout << "std::cout d.getTitle(): " << d.getTitle() << endl;
	file << d.getTitle() << endl;
	file << "\nCourse:______________________" << endl;
	file << "\nName:_______________________" << endl;
	file <<"\n";

	cout << "types.size() before loop = " << types.size() << endl;

	int j = 0;
	int idx = 0;
	int q = 0;
	for (int i = 0; i < types.size(); i++) {
		cout << "types.size() = " << types.size() << endl;
		if (q < numques) {
			q++;
		}
		if (i == 0)
		{
			file << "\n";
			file << types[i] << ": " << endl;
			file << q << ". ";
			file << questions[i] << endl;
			
			if (types[i] == "True/False") {
				file << "True:___" << endl;
				file << "False:___\n" << endl;
			}
			else if (types[i] == "Multiple Choice (Single Answer)") {
				
				file << "a) " << d.getMultAns()[idx][0] << endl;
				file << "b) " << d.getMultAns()[idx][1] << endl;
				file << "c) " << d.getMultAns()[idx][2] << endl;
				file << "d) " << d.getMultAns()[idx][3] << endl;
				if (d.getMsgClicked()) {
					if (d.getAnsIdx().size() > 0) {
						idx = d.getAnsIdx()[j++];
					}
					else {
						idx++;
					}
				}
				else if (!d.getMsgClicked()){
					if (idx < (d.getAnsIdx().size())) {
						idx = d.getAnsIdx()[j++];
					}
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
				cout << " index i = " << i << ", questions[i] = " << questions[i] << endl;
				file << q << ". ";
				file << questions[i] << endl;
				if (types[i] == "True/False") {
					file << "True:___" << endl;
					file << "False:___" << endl;
				}
				else if (types[i] == "Multiple Choice (Single Answer)") {
					std::cout << "i > 0 idx: " << idx << endl;					
					file << "a) " << d.getMultAns()[idx][0] << endl;
					file << "b) " << d.getMultAns()[idx][1] << endl;
					file << "c) " << d.getMultAns()[idx][2] << endl;
					file << "d) " << d.getMultAns()[idx][3] << endl;
					if (d.getMsgClicked()) {
						if (d.getAnsIdx().size() > 0) {
							idx = d.getAnsIdx()[j++];
						}
						else {
							idx++;
						}
					}
					else if (!d.getMsgClicked()) {
						if (idx < (d.getAnsIdx().size())) {
							idx = d.getAnsIdx()[j++];
						}
					}

				}
				else if (types[i] == "Fill in the Blank") {
					file << "__________________________\n";
				}
			}
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
					if (d.getMsgClicked()) {
						if (d.getAnsIdx().size() > 0) {
							idx = d.getAnsIdx()[j++];
						}
						else {
							idx++;
						}
					}
					else if (!d.getMsgClicked()) {
						if (idx < (d.getAnsIdx().size())) {
							idx = d.getAnsIdx()[j++];
						}
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