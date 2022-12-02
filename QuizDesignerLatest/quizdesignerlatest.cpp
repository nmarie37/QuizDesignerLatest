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

#define MAXQUES 15

DataStore d;

QuizDesignerLatest::QuizDesignerLatest(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this); // create instances of Qt widgets
}

QuizDesignerLatest::~QuizDesignerLatest()
{}

static int i = 0; // counter to keep track of number of generated questions; static to retain value outsode of function scope
static int ans_i = 0;

void QuizDesignerLatest::loadQuiz() {
    cout << "message clicked in load quiz: " << d.getMsgClicked() << endl;
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    QString filename = dialog.getOpenFileName(this, "Select a File");
    string filename_s = filename.toLocal8Bit().constData();
    //ui.titleEdit->setText(filename);

    QFile file(filename);
    ifstream f;
    f.open(filename_s, ios::in);
    if (f.is_open()) {
        std::cout << "File is open and ready \n";
    }
    else {
        std::cout << "File not found! \n";
        return;
    }
        

    if (!file.exists()) {
        qCritical() << "File not found";
    }
    
    if (!file.open(QIODevice::ReadOnly)) {
        qCritical() << file.errorString();
    }

    
    d.fileRead(d, f);

    f.close();

    //ui.titleEdit->setText(QString::fromStdString(d.getTitle()));

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

void QuizDesignerLatest::on_exportButton_clicked() {
    //d.fileWrite(d, d.getTypes(), d.getQues());
    QString title = ui.titleEdit->text();
    d.setTitle(title.toLocal8Bit().constData());
    cout << "export button clicked! d.getTitle(): " << d.getTitle() << endl;
    d.fileWrite(d);

}

void QuizDesignerLatest::multChoiceAnswers() {
    MultChoiceDialog dialog(this);
    if (dialog.exec()) {
        QString ans_a = dialog.aLineEdit->text();
        QString ans_b = dialog.bLineEdit->text();
        QString ans_c = dialog.cLineEdit->text();
        QString ans_d = dialog.dLineEdit->text();
        if (dialog.saveButton->isEnabled()) {  
            cout << "Save button was enabled!" << endl;
            vector<string> answers = { ans_a.toLocal8Bit().constData(), ans_b.toLocal8Bit().constData(), ans_c.toLocal8Bit().constData(), ans_d.toLocal8Bit().constData() };
            d.setMultAns(answers,1);
            ans_i++;
        }
    }
}

void QuizDesignerLatest::on_questButton_clicked() {
    cout << "message clicked in new quiz: " << d.getMsgClicked() << endl;
    AddQuestDialog dialog(this); // instance of AddQuestDialog

    QString title = ui.titleEdit->text();
    d.setTitle(title.toLocal8Bit().constData());
    cout << "title: " << d.getTitle() << endl;

    std::cout << "i = " << d.getNumQues() << endl;
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
            cout << "tf type string:" << selectt_s << "end" << endl;
        }

        // ################### MULT CHOICE ####################
        else if (check_MC == 1)
        {
            QString selectm = dialog.multChoiceButton->text(); // grabs the label of the button for storage
            string selectm_s = selectm.toLocal8Bit().constData();
            d.setType(selectm_s);
            cout << "MC type string:" << selectm_s << "end" << endl;
            QuizDesignerLatest::multChoiceAnswers();
        }

        // ################### FILL BLANK ####################
        else if (check_FB == 1)
        {
            QString selectf = dialog.fillBlankButton->text(); // grabs the label of the button for storage
            string selectf_s = selectf.toLocal8Bit().constData();
            d.setType(selectf_s);
            cout << "FB type string:" << selectf_s << "end" << endl;
        }

        QString ques = dialog.quesLineEdit->text(); // grabs question entered into dialog box
        d.setQuestion(ques.toLocal8Bit().constData());

        bool en = dialog.saveButton->isEnabled(); // en = 1 when save button is clicked, 0 otherwise
        // only increment store total # of questions # when all of these conditions are met before clicking save
        if ((en == 1) && (!ques.isEmpty()) && ((check_TF) || (check_MC) || (check_FB))) {
            cout << "en = " << en << endl;
            int totalQues = ui.spinBox->value(); // get user-configured total number of questions (1-15)
            if ((i < totalQues) && (i < MAXQUES)) {
                i++;
            }           
        }
        d.setNumQues(i); // store current number of questions into DataStore object

        vector<string> getTypes_temp;
        vector<string> getQues_temp;
        getTypes_temp = d.getTypes();
        getQues_temp = d.getQues();


        vector<int> ans_temp;
        // keep track of answers based on index; use these indices later when sorting to identify answers properly
        for (int i = 0; i < ans_i; i++) {
            ans_temp.push_back(i); // should create vector that holds 0...number of mult choice ques - 1
        }
        d.setAnsIdx(ans_temp);

        for (int i = 0; i < d.getAnsIdx().size(); i++) {
            cout << "getAnsIdx: " << endl;
            cout << d.getAnsIdx()[i] << endl;
        }

        vector<string> mult_choice_ques; // vector to store only multiple choice questions BEFORE sorting

        // store only multiple choice questions
        for (int i = 0; i < getTypes_temp.size(); i++) {
            if (getTypes_temp[i] == "Multiple Choice (Single Answer)") {
                mult_choice_ques.push_back(getQues_temp[i]);
            }
            else {
                continue;
            }
        }

        // sort questions based on question type
        d.pairSort(getTypes_temp, getQues_temp);

        for (int i = 0; i < getTypes_temp.size(); i++) {
            cout << "t1 sorted: " << getTypes_temp[i] << endl;
        }

        for (int i = 0; i < getQues_temp.size(); i++) {
            cout << "t2 sorted: " << getQues_temp[i] << endl;
        }

        d.setQuestions(getQues_temp);
        d.setTypes(getTypes_temp);

        

        vector<vector<string>> mult_choice_ans_temp = d.getMultAns();
        vector<vector<string>> mult_choice_sorted;
        vector<int> ans_idx_temp = d.getAnsIdx();

        for (int i = 0; i < ans_idx_temp.size(); i++) {
            cout << "ans_idx_temp before sort: " << endl;
            cout << ans_idx_temp[i] << endl;
        }
        // sort multiple choice answers based on multiple choice questions order
        d.pairSortInt(mult_choice_ques, ans_idx_temp);

        for (int i = 0; i < ans_idx_temp.size(); i++) {
            cout << "ans_idx_temp after sort: " << endl;
            cout << ans_idx_temp[i] << endl;
        }

        cout << "size of mult_choice_ques: " << mult_choice_ques.size() << endl;
        cout << "size of ans_idx_temp (should match above): " << ans_idx_temp.size() << endl;

        vector<string> blank;
        d.setMultAns(blank, 0); // clears setMultAns
        for (int i = 0; i < ans_idx_temp.size(); i++) {
            d.setMultAns(mult_choice_ans_temp[ans_idx_temp[i]],1);
        }
        

        d.printTypes();
        d.printQues();

       // if (d.getMsgClicked() == 0) {
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
       // }
        //else if (d.getMsgClicked() == 1)
        //{
        //    for (int i = 0; i < d.getQues().size(); i++) {
        //        if (!QString::fromStdString(d.getQues()[i]).isEmpty()) {
        //            QListWidgetItem* item = new QListWidgetItem("Question: " + QString::fromStdString(d.getQues()[i]), ui.qlistWidget); // enter question number from counter here, i.e. "Question 1:"
        //            item->setData(Qt::UserRole, QString::fromStdString(d.getQues()[i]));
        //            ui.qlistWidget->setCurrentItem(item);
        //        }
        //        else { // otherwise, add empty item to list
        //            QListWidgetItem* item = new QListWidgetItem(" ", ui.qlistWidget); // enter question number from counter here, i.e. "Question 1:"
        //            item->setData(Qt::UserRole, QString::fromStdString(d.getQues()[i]));
        //            ui.qlistWidget->setCurrentItem(item);
        //        }
        //    }
        //}

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
    if (i >= 1) { // if at least one question exists, decrement question counter by one
        i--;
    }

    QListWidgetItem* curItem = ui.qlistWidget->currentItem();

    if (curItem) {
        int row = ui.qlistWidget->row(curItem);
        ui.qlistWidget->takeItem(row);

        QString del = curItem->data(Qt::UserRole).toString(); // value user is going to delete
        string del_s = del.toLocal8Bit().constData();
        cout << "del_s = " << del_s;
        vector<string> qtemp = d.getQues();

        for (static int r = 0; r < qtemp.size(); r++) {
            if (qtemp[r] == del_s) {
                cout << "Found ques to remove from vector!" << endl;
                d.removeQues(r);
            }
        }

        delete curItem;    

        if (ui.qlistWidget->count() > 0) {
            ui.qlistWidget->setCurrentRow(0);
        }
        else {
            on_qlistWidget_currentItemChanged();
        }

    }
}


