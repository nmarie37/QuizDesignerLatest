#pragma once

#include <QDialog>
#include "ui_multchoicedialog.h"

class MultChoiceDialog : public QDialog, public Ui::MultChoiceDialogClass
{
	Q_OBJECT

public:
	MultChoiceDialog(QWidget *parent = nullptr);
	~MultChoiceDialog();

private:
	 
};
