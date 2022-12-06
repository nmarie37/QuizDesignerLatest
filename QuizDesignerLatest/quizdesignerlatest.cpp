#include "stdafx.h"
#include <filesystem>
#include <string>
#include <ctype.h>
#include "quizdesignerlatest.h"
#include "addquestdialog.h"
#include "multchoicedialog.h"
#include "datastore.h"

#include <iostream>

using namespace std;

#define MAXQUES 15 // constant for max number of allowed questions

DataStore d; // define instance of DataStore object to use globally in this file

QuizDesignerLatest::QuizDesignerLatest(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this); // create instances of Qt widgets
}

QuizDesignerLatest::~QuizDesignerLatest()
{}

static int i = 0; // counter to keep track of number of generated questions; static to retain value outsode of function scope
static int ans_i = 0; // counter to keep track of multiple choice answers


void QuizDesignerLatest::loadQuiz() { // function for when user clicked Open
    QFileDialog dialog(this); // instance of QFileDialog
    dialog.setFileMode(QFileDialog::ExistingFile); // opens Windows file explorer
    QString filename = dialog.getOpenFileName(this, "Select a File"); 
    string filename_s = filename.toLocal8Bit().constData(); // convert from QString to string for handling
    QFileInfo fileTitle(filename);
    QString base = fileTitle.baseName();
    ui.titleLabel_2->setStyleSheet("font: bold");
    ui.titleLabel_2->setText("Loaded Title: " + base);

    QFile file(filename); 
    ifstream f;
    f.open(filename_s, ios::in); // open selected file
    if (f.is_open()) {
        std::cout << "File is open and ready \n";
    }
    else {
        std::cout << "File not found! \n";
        return;
    }
        
    // ensure the file exists
    if (!file.exists()) {
        qCritical() << "File not found";
    }
    
    if (!file.open(QIODevice::ReadOnly)) {
        qCritical() << file.errorString();
    }
    
    d.fileRead(d, f); // read in all contents of file. Parse and store into DataStore object
    f.close(); // close file when finished

    // display questions pulled in from user-imported quiz in GUI
    for (int i = 0; i < d.getQues().size(); i++) {
        if (!QString::fromStdString(d.getQues()[i]).isEmpty()) {
            QListWidgetItem* item = new QListWidgetItem("Question: " + QString::fromStdString(d.getQues()[i]), ui.qlistWidget); // enter question number from counter here, i.e. "Question 1:"
            item->setData(Qt::UserRole, QString::fromStdString(d.getQues()[i]));
            ui.qlistWidget->setCurrentItem(item);
        }
        else { // otherwise, add empty item to list
            QListWidgetItem* item = new QListWidgetItem(" ", ui.qlistWidget); // enter question number from counter here, i.e. "Question 1:"
            item->setData(Qt::UserRole, QString::fromStdString(d.getQues()[i]));
            ui.qlistWidget->setCurrentItem(item);
        }
    }
}


void QuizDesignerLatest::on_exportButton_clicked() { // function for when user clicks Export to export their quiz to a .csv file
    QString title = ui.titleEdit->text(); // grab the title from GUI
    d.setTitle(title.toLocal8Bit().constData()); // store title in DataStore object

    vector<string> getTypes_temp;
    vector<string> getQues_temp;
    getTypes_temp = d.getTypes(); // temporary vector for question types
    getQues_temp = d.getQues(); // temporary vector for questions

    vector<string> mult_choice_ques; // vector to store only multiple choice questions BEFORE sorting

    // store only multiple choice questions
    for (int i = 0; i < getTypes_temp.size(); i++) {
        if (getTypes_temp[i] == "Multiple Choice (Single Answer)") {
            mult_choice_ques.push_back(getQues_temp[i]);
            d.setMultQues(getQues_temp[i]);
        }
        else {
            continue;
        }
    }

    // sort questions based on question type
    d.pairSort(getTypes_temp, getQues_temp);

    d.setQuestions(getQues_temp); // set sorted questions
    d.setTypes(getTypes_temp); // set sorted question types

    vector<vector<string>> mult_choice_ans_temp = d.getMultAns(); // temp multiple choice answers
    vector<vector<string>> mult_choice_sorted; // sort multiple choice answers

    if (d.getMsgClicked()) { // if open was clicked in main()
        vector<int> ans_idx_temp; // temp for multiple choice answer index
        for (i = 0; i < d.getMultAns().size(); i++) {
            ans_idx_temp.push_back(i);
        }
        // sort multiple choice answers based on multiple choice questions order
        if (mult_choice_ques.size() > 1 && ans_idx_temp.size() > 1) { // ensure there are at least two questions to sort
            d.pairSortInt(mult_choice_ques, ans_idx_temp);
        }

        d.setAnsIdx(ans_idx_temp); // store multiple choice answer indices sorted according to multiple choice question

        if (!d.getMsgClicked() && (d.getMultAns().size() > 0)) {
            vector<string> blank;
            d.setMultAns(blank, 0); // clears setMultAns
            for (int i = 0; i < ans_idx_temp.size(); i++) {
                d.setMultAns(mult_choice_ans_temp[ans_idx_temp[i]], 1);
            }
        }


        //QMessageBox fileOverwriteMsgBox;  // creat message box to pop-up
        //fileOverwriteMsgBox.setWindowTitle("File Export");
        //fileOverwriteMsgBox.setText(title + " Exported Successfully!");  // set message box title
        //fileOverwriteMsgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Close);
        //fileOverwriteMsgBox.exec();

    }
    else { // if new was clicked in main()
        vector<int> ans_temp; // temp multiple choice answer vector

        // keep track of answers based on index; use these indices later when sorting to identify answers properly
        for (int i = 0; i < ans_i; i++) {
            ans_temp.push_back(i); // should create vector that holds 0...number of mult choice ques - 1
        }
        // sort multiple choice answers based on multiple choice questions order
        if (mult_choice_ques.size() > 1 && ans_temp.size() > 1) {
            d.pairSortInt(mult_choice_ques, ans_temp);
        }

        if (d.getMsgClicked() && (d.getMultAns().size() > 0)) {
            vector<string> blank;
            d.setMultAns(blank, 0); // clears setMultAns
            for (int i = 0; i < ans_temp.size(); i++) {
                d.setMultAns(mult_choice_ans_temp[ans_temp[i]], 1);
                d.setMultAns(mult_choice_ans_temp[ans_temp[i]], 1);
            }
        }

        d.setAnsIdx(ans_temp); // store multiple choice answer indices sorted according to question
    }
    
    //MsgBox displaying saving file without title
    if (ui.titleEdit->text().isEmpty() && d.getNumQues()>0) {
        QMessageBox msgWarning;
        msgWarning.setText("WARNING!\nNo title entered. Exporting quiz with no name (.csv).");
        msgWarning.setIcon(QMessageBox::Warning);
        msgWarning.setWindowTitle("Caution");
        msgWarning.exec();
    }

    //MsgBox displaying cannot export blank quiz, quit App
    else if (ui.titleEdit->text().isEmpty() && d.getNumQues() == 0) {
        QMessageBox msgError;
        msgError.setText("DANGER!\nCannot export BLANK quiz.");
        msgError.setIcon(QMessageBox::Critical);
        msgError.setWindowTitle("Critical");
        msgError.exec();
        qApp->quit();
    }


    //d.printTypes(); // testing prints
    //d.printQues();

    d.fileWrite(d); // write quiz to .csv file

    QMessageBox msgBox;  // creat message box to pop-up
    msgBox.setWindowTitle("File Export");
    msgBox.setText(title + " Exported Successfully!");  // set message box title
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Close);
    msgBox.exec();
}


void QuizDesignerLatest::multChoiceAnswers() { // function for saving user-configured multiple choice answers
    MultChoiceDialog dialog(this); // instance of MultChoiceDialog
    if (dialog.exec()) {
        QString ans_a = dialog.aLineEdit->text(); // answer a for current multiple choice question
        QString ans_b = dialog.bLineEdit->text(); // answer b for current multiple choice question
        QString ans_c = dialog.cLineEdit->text(); // answer c for current multiple choice question
        QString ans_d = dialog.dLineEdit->text(); // answer d for current multiple choice question

        if (dialog.saveButton->isEnabled()) {  // when user clicks save
            vector<string> answers = { ans_a.toLocal8Bit().constData(), ans_b.toLocal8Bit().constData(), ans_c.toLocal8Bit().constData(), ans_d.toLocal8Bit().constData() };
            d.setMultAns(answers,1); // store user-configured answers into DataStore object
            ans_i++; // increment multiple choice answer counter
        }
    }
}

void QuizDesignerLatest::on_questButton_clicked() { // function for adding a question to the quiz
    AddQuestDialog dialog(this); // instance of AddQuestDialog

    QString title = ui.titleEdit->text();
    d.setTitle(title.toLocal8Bit().constData()); // grab user-configured title and store in DataStore object
    if (ui.titleEdit->text().isEmpty()) {
        ui.titleLabel_2->setStyleSheet("color: red;" "font: bold");
            ui.titleLabel_2->setText("<No Title>");
    }
    else {
            ui.titleLabel_2->setStyleSheet("font: bold");
            ui.titleLabel_2->setText("Title: " + title);
    }

    


    if (dialog.exec()) {
        // Radio button handling (i.e true/false, mult choice, fill blank)
        bool check_TF = dialog.trueFalseButton->isChecked(); // bool = 1 if button is checked off
        bool check_MC = dialog.multChoiceButton->isChecked(); // bool = 1 if button is checked off
        bool check_FB = dialog.fillBlankButton->isChecked(); // bool = 1 if button is checked off

        // ################### TRUE/FALSE ####################
        if (check_TF == 1)
        {
            QString selectt = dialog.trueFalseButton->text();  // grabs the label of the button for storage
            string selectt_s = selectt.toLocal8Bit().constData();
            d.setType(selectt_s); // stores the type of question to types vector
        }

        // ################### MULT CHOICE ####################
        else if (check_MC == 1)
        {
            QString selectm = dialog.multChoiceButton->text(); // grabs the label of the button for storage
            string selectm_s = selectm.toLocal8Bit().constData();
            d.setType(selectm_s);
            QuizDesignerLatest::multChoiceAnswers(); // store the multiple choice question answers
        }

        // ################### FILL BLANK ####################
        else if (check_FB == 1)
        {
            QString selectf = dialog.fillBlankButton->text(); // grabs the label of the button for storage
            string selectf_s = selectf.toLocal8Bit().constData();
            d.setType(selectf_s);
        }

        QString ques = dialog.quesLineEdit->text(); // grabs question entered into dialog box
        d.setQuestion(ques.toLocal8Bit().constData()); // store question as string into DataStore object

        bool en = dialog.saveButton->isEnabled(); // en = 1 when save button is clicked, 0 otherwise

        // only increment store total # of questions # when all of these conditions are met before clicking save
        if ((en == 1) && (!ques.isEmpty()) && ((check_TF) || (check_MC) || (check_FB))) {
            int totalQues = ui.spinBox->value(); // get user-configured total number of questions (1-15)
            if ((i < totalQues) && (i < MAXQUES)) {
                i++;
            }           
        }

        if (d.getMsgClicked()) { // if user clicked open in main()
            
            d.setNumQues(d.getNumQues()+1); // store current number of questions into DataStore object
        }
        else {
            d.setNumQues(i);
        }

        // Display added questions in GUI
        if (!ques.isEmpty()) {
            QListWidgetItem* item = new QListWidgetItem("Question: " + ques, ui.qlistWidget); // enter question number from counter here, i.e. "Question 1:"
            item->setData(Qt::UserRole, ques);
            ui.qlistWidget->setCurrentItem(item);
        }
        else { // otherwise, add empty item to list
            QListWidgetItem* item = new QListWidgetItem(" ", ui.qlistWidget); // enter question number from counter here, i.e. "Question 1:"
            item->setData(Qt::UserRole, ques);
            ui.qlistWidget->setCurrentItem(item);
        }
    }  
}


void QuizDesignerLatest::on_qlistWidget_currentItemChanged() { // displays either the currently selected question at the bottom of the dialog box, or <No question selected>
    QListWidgetItem* curItem = ui.qlistWidget->currentItem();

    if (curItem) {
        ui.label->setText(curItem->data(Qt::UserRole).toString());
    }
    else {
        ui.label->setText("<No question selected>");
    }
}


void QuizDesignerLatest::on_deleteButton_clicked() { // deletes the currently selected list item when user clicks Delete button
    //if (i >= 1) { // if at least one question exists, decrement question counter by one
    //    i--;
    //}

    QListWidgetItem* curItem = ui.qlistWidget->currentItem();
    
    vector<string> qtemp = d.getQues(); // temporarily grab stored questions
    vector<string> multqtemp;
    vector<int> ansidx = d.getAnsIdx(); // temporarily grab stored multiple choice answer indices
    int ans_size = d.getAnsIdx().size();
    // store all multiple choice ques
    for (int i = 0; i < ans_size; i++) {
        multqtemp.push_back(d.getMultQues(i));
    }

    if (curItem) {
        int row = ui.qlistWidget->row(curItem);
        ui.qlistWidget->takeItem(row);

        QString del = curItem->data(Qt::UserRole).toString(); // value user is going to delete
        string del_s = del.toLocal8Bit().constData();

        // search multiple choice vector and delete if found
        for (int r = 0; r < ans_size; r++) {
            if (multqtemp[r] == del_s) {
                d.removeMultAns(r);              
            }
        }
        
        // remove overall question and type
        for (int r = 0; r < qtemp.size(); r++) {
            if (qtemp[r] == del_s) {
                d.removeQues(r);
                d.removeType(r);               
            }
        }

        if (qtemp.size() > 0)
        {
            delete curItem; // delete currently selected item from GUI list  
        }
          

        if (ui.qlistWidget->count() > 0) {
            ui.qlistWidget->setCurrentRow(0);
        }
        else {
            QuizDesignerLatest::on_qlistWidget_currentItemChanged();
        }
    }
}


