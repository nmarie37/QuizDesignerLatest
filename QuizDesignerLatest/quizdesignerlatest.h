#pragma once

#include <QtWidgets/QWidget>
#include "ui_quizdesignerlatest.h"

class QuizDesignerLatest : public QWidget // this class creates a Qt widget window that is the main UI for this project
{
    Q_OBJECT // pre-processor directive inherent to Qt

public:
    QuizDesignerLatest(QWidget *parent = nullptr); // customized constructor to work with Qt
    ~QuizDesignerLatest(); // destructor
    void loadQuiz(); //opens the Quiz Designer .csv file for editing

private:
    Ui::QuizDesignerLatestClass ui; // instance inherited from Qt namespace Ui

private slots: // slot naming convention: void on<object_name>_<signal_name>(<signal parameters>)
    void on_exportButton_clicked(); //Export quiz to csv file
    void on_questButton_clicked(); // Add Question button slot
    void multChoiceAnswers(); 
    void on_qlistWidget_currentItemChanged(); // List displayed of current quizzes slot
    void on_deleteButton_clicked(); // Delete Quiz slot
};
