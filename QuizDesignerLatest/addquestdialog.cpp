#include "stdafx.h"
#include "addquestdialog.h"

AddQuestDialog::AddQuestDialog(QWidget *parent) // this class creates a Qt Dialog, which sends information back to the main UI and updates accordingly
	: QDialog(parent)
{
	setupUi(this); // create instances of Qt widgets
}

AddQuestDialog::~AddQuestDialog()
{}
