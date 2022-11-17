#include "stdafx.h"
#include "quizdesignerlatest.h"
#include "addquestdialog.h"
#include "datastore.h"

#include <iostream>

//using namespace std;

datastore d;

QuizDesignerLatest::QuizDesignerLatest(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
}

QuizDesignerLatest::~QuizDesignerLatest()
{}

int i = 0;
void QuizDesignerLatest::on_questButton_clicked() {
    AddQuestDialog dialog(this);
    i++;
    std::cout << "i = " << i << endl;
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
        }

        // ################### FILL BLANK ####################
        else if (check_FB == 1)
        {
            QString selectf = dialog.fillBlankButton->text(); // grabs the label of the button for storage
            string selectf_s = selectf.toLocal8Bit().constData();
            d.setType(selectf_s);
        }

        d.printTypes();
        d.printQues();

        QString ques = dialog.quesLineEdit->text();
        if (!ques.isEmpty()) {
            QListWidgetItem* item = new QListWidgetItem("Question: " + ques, ui.qlistWidget); // enter question number from counter here, i.e. "Question 1:"
            item->setData(Qt::UserRole, ques);
            ui.qlistWidget->setCurrentItem(item);
        }
    }
}

void QuizDesignerLatest::on_qlistWidget_currentItemChanged() {
    QListWidgetItem* curItem = ui.qlistWidget->currentItem();

    if (curItem) {
        ui.label->setText(curItem->data(Qt::UserRole).toString());
    }
    else {
        ui.label->setText("<No question selected>");
    }
}

void QuizDesignerLatest::on_deleteButton_clicked() {
    QListWidgetItem* curItem = ui.qlistWidget->currentItem();

    if (curItem) {
        int row = ui.qlistWidget->row(curItem);
        ui.qlistWidget->takeItem(row);
        delete curItem;

        if (ui.qlistWidget->count() > 0) {
            ui.qlistWidget->setCurrentRow(0);
        }
        else {
            on_qlistWidget_currentItemChanged();
        }

    }
}

