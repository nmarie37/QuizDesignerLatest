#include "stdafx.h"
#include "quizdesignerlatest.h"
#include "addquestdialog.h"
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

void QuizDesignerLatest::loadQuiz() {
    QString filename = QFileDialog::getOpenFileName(this, "Select a File");
    ui.titleEdit->setText(filename);

    QFile file(filename);
    if (!file.exists()) {
        qCritical() << "File not found";
    }

    if (!file.open(QIODevice::ReadOnly)) {
        qCritical() << file.errorString();
    }

    QTextStream stream(&file);

    int i = 0;
    while (!stream.atEnd()) {
        QString line = stream.readLine();
        ui.qlistWidget->addItem(line);
        i++;
    }

    file.close();
}

void QuizDesignerLatest::on_exportButton_clicked() {
    QString quizName = ui.titleEdit->text();

    QFile file(quizName + ".csv");
    if (!file.open(QIODevice::WriteOnly)) {
        qCritical() << file.errorString();
    }

    for (int i = 0; i < d.getNumQues(); i++) {
        QTextStream stream(&file);
        stream << ui.qlistWidget->item(i)->text() << Qt::endl;
    }

    file.flush();
    file.close();
}

void QuizDesignerLatest::on_questButton_clicked() {
    AddQuestDialog dialog(this); // instance of AddQuestDialog

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

        QString ques = dialog.quesLineEdit->text(); // grabs question entered into dialog box

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

        d.printTypes();
        d.printQues();

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
    if (i >= 1) { // if at least one question exists, decrement question counter by one
        i--;
    }

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

