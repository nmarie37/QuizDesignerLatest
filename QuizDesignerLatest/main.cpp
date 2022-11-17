#include "stdafx.h"
#include "quizdesignerlatest.h"
#include "datastore.h"
#include <QtWidgets/QApplication>

#include <iostream>

extern datastore d;

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

    if (msgBox.clickedButton() == newButton) {
        w.show();
    }
    else if (msgBox.clickedButton() == openButton) {

    }
    else if (ret == QMessageBox::Cancel) {
        msgBox.close();
        return 0;
    }

    

    return a.exec();
}
