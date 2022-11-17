#pragma once

#include <QDialog>
#include "ui_addquestdialog.h"

class AddQuestDialog : public QDialog, public Ui::AddQuestDialogClass
{
	Q_OBJECT

public:
	AddQuestDialog(QWidget *parent = nullptr);
	~AddQuestDialog();

private:
	 
};
