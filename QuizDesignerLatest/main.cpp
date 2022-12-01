#include "stdafx.h"
#include "quizdesignerlatest.h"
#include "datastore.h"
#include <QtWidgets/QApplication>

#include <iostream>

extern DataStore d;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QuizDesignerLatest w;  // instantiate object of main QWidget
    
    QMessageBox msgBox;  // creat message box to pop-up
    msgBox.setWindowTitle("Quiz Designer");  
    msgBox.setText("                     Quiz Designer");  // set message box title
    QAbstractButton* newButton = msgBox.addButton("New", QMessageBox::AcceptRole);  // create new button to create a new quiz
    QAbstractButton* openButton = msgBox.addButton("Open", QMessageBox::AcceptRole);  // create open button to open quiz for editing
    msgBox.setStandardButtons(QMessageBox::Cancel);  // create cancel button to exit the program
    int ret = msgBox.exec();

    if (msgBox.clickedButton() == newButton) { // if user clicks New, execute QuizDesignerLatest code (Main UI, dialogs...)
        d.setMsgClicked(0);
        w.show();
    }
    else if (msgBox.clickedButton() == openButton) { // if user clicks Open, open existing Quiz Designer .csv file for editing
        d.setMsgClicked(1);
        w.loadQuiz();
        w.show();
    }
    else if (ret == QMessageBox::Cancel) { // if user clicks Cancel, close the message box and end the program, returning 0
        msgBox.close();
        return 0;
    }

    
    return a.exec();
}
