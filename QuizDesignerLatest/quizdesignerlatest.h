#pragma once

#include <QtWidgets/QWidget>
#include "ui_quizdesignerlatest.h"

class QuizDesignerLatest : public QWidget
{
    Q_OBJECT

public:
    QuizDesignerLatest(QWidget *parent = nullptr);
    ~QuizDesignerLatest();

private:
    Ui::QuizDesignerLatestClass ui;

private slots:
    void on_questButton_clicked();
    void on_qlistWidget_currentItemChanged();
    void on_deleteButton_clicked();  
};
