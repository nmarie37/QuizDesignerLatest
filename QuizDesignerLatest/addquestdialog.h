#pragma once

#include <QDialog>
#include "ui_addquestdialog.h"

class AddQuestDialog : public QDialog, public Ui::AddQuestDialogClass // this class creates a Qt Dialog, which sends information back to the main UI and updates accordingly
{
	Q_OBJECT // pre-processor directive inherent to Qt

public:
	AddQuestDialog(QWidget *parent = nullptr); // customized constructor to work with Qt
	~AddQuestDialog(); // destructor

private:
	 
};
