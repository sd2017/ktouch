/***************************************************************************
 *   ktouchopenrequest.cpp                                                 *
 *   ---------------------                                                 *
 *   Copyright (C) 2004 by Andreas Nicolai                                 *
 *   ghorwin@users.sourceforge.net                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include "ktouchopenrequest.h"
#include "ktouchopenrequest.moc"

#include <qradiobutton.h>
#include <qlabel.h>
#include <q3buttongroup.h>

#include <kpushbutton.h>
#include <klineedit.h>
#include <kcombobox.h>
#include <kfiledialog.h>
#include <klocale.h>
#include <ksqueezedtextlabel.h>
#include <kmessagebox.h>
#include <klocale.h>


KTouchOpenRequest::KTouchOpenRequest(QWidget* parent, const char* name, bool modal, Qt::WFlags fl)
: QDialog(parent,name, modal,fl)
{
}

int KTouchOpenRequest::requestFileToOpen(KUrl& url, const QString& caption, const QString& title, 
      const QString& currentText, const QString& defaultText, const QString& openText,
      const QString& newText, KUrl current_url, QStringList defaultList, QString emptyListText)
{
    setWindowTitle(caption);
    openChoiceGroup->setTitle(title);
    currentRadioBtn->setText(currentText);
    presetRadioBtn->setText(defaultText);
    openFileRadioBtn->setText(openText);
    newRadioBtn->setText(newText);
    // Fill in current lecture URL or disable if not available
    if (current_url.isEmpty())  {
        currentLabel->setText("");
        currentRadioBtn->setEnabled(false);
        newRadioBtn->setChecked(true);
    }
    else {
        currentLabel->setText(current_url.url());
        currentRadioBtn->setEnabled(true);
        currentRadioBtn->setChecked(true);
    };
    // Fill preset combo with lecture files from the configuration object
    presetCombo->clear();
    if (defaultList.isEmpty()) {
        if (emptyListText.isEmpty())  presetCombo->addItem(i18n("<no default files available>"));
        else                          presetCombo->addItem(emptyListText);
        presetRadioBtn->setEnabled(false);
    }
    else {
        for (QStringList::Iterator it = defaultList.begin(); it != defaultList.end(); ++it )
            presetCombo->addItem(*it);
        presetRadioBtn->setEnabled(true);
    }
    presetCombo->setCurrentIndex(0);
    radioBtnChanged();
    
    // Finally executre the dialog
    int result = exec();
    url = m_url;
    return result;
}

void KTouchOpenRequest::okBtnClicked() {
    if (currentRadioBtn->isChecked())
        m_url = currentLabel->text();
    if (presetRadioBtn->isChecked())
        m_url = presetCombo->currentText();
    if (newRadioBtn->isChecked())
        m_url = QString();
    if (openFileRadioBtn->isChecked()) {
        if (openFileEdit->text().isEmpty()) {
            KMessageBox::error(this, i18n("Please select or enter a file name."));
            return;
        }
        KUrl tmp = openFileEdit->text();
        if (!tmp.isValid()) {
            KMessageBox::error(this, i18n("The URL seems to be malformed; please correct it."));
            return;
        }
        m_url = tmp;
    };            
    QDialog::accept();
}


void KTouchOpenRequest::radioBtnChanged() {
    if (currentRadioBtn->isChecked())   currentLabel->setEnabled(true);
    else                                currentLabel->setEnabled(false);
    if (presetRadioBtn->isChecked())    presetCombo->setEnabled(true);
    else                                presetCombo->setEnabled(false);
    if (openFileRadioBtn->isChecked()) {
        openFileEdit->setEnabled(true);
        browseBtn->setEnabled(true);
    }
    else {
        openFileEdit->setEnabled(false);
        browseBtn->setEnabled(false);
    }
}


void KTouchOpenRequest::browseBtnClicked() {
    KUrl tmp = KFileDialog::getOpenUrl(QString(), QString(), this, i18n("Select Training Lecture File") );
    if (!tmp.isEmpty())
        openFileEdit->setText(tmp.url());
}


