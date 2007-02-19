/***************************************************************************
 *   ktouchlectureeditor.h                                                 *
 *   ---------------------                                                 *
 *   Copyright (C) 2000 by Håvard Frøiland, 2003 by Andreas Nicolai        *
 *   ghorwin@users.sourceforge.net                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef KTOUCHLECTUREEDITORDIALOG_H
#define KTOUCHLECTUREEDITORDIALOG_H

#include <QFont>
#include <QDialog>

#include <kurl.h>

#include "ui_ktouchlectureeditordialog.h"
#include "ktouchlecture.h"

/// This is the KTouch lecture editor dialog.
///
/// The lecture edit dialog works like a standalone edit tool for editing lectures.
/// Upon opening of the dialog the 'open lecture' dialog box is shown where
/// the user can either select a local training lecture or load a lecture file.
/// Then the user can edit the lecture and save it (if desired under a different
/// file name).
/// The use of the editor is simple, just include ktouchlectureeditor.h and do
/// @code
///  KTouchLectureEditor dlg;
///  bool ok = dlg.startEditor(current_lecture);
///  // current_lecture should be the URL pointing to the current/default 
///  // lecture or an empty URL
/// @endcode
/// @see startEditor() for details on the return value.
class KTouchLectureEditorDialog : public QDialog, public Ui_KTouchLectureEditorDialog {
    Q_OBJECT
  public:
    /// Constructor
    KTouchLectureEditorDialog(QWidget *parent = 0);
    /// Destructor
    ~KTouchLectureEditorDialog() {};
    /// Shows and executes the dialog (argument is the url to the default or 
    /// current lecture file).
    /// @return Returns 'true' if the dialog was properly executed (thus reloading 
    ///         of the lecture in KTouch is necessary) or 'false' if user canceled
    ///         the "Open request" dialog.
    bool startEditor(const KUrl& url);

  private slots:
    /// Called when the Font button was clicked.
    void fontBtnClicked();
    /// Called when the Open button was clicked.
    void openBtnClicked();
    /// Called when the Save button was clicked.
    void saveBtnClicked();
    /// Called when the Save As button was clicked.
    void saveAsBtnClicked();
    /// Called when the editor is closed.
    void closeQuery() { if (saveModified()) accept(); };
    /// Called when the editor is rejected (x clicked).
    void reject()     { closeQuery(); };
    /// Will be called whenever some changes are made.
    void setModified() { setModified(true); }
    /// Will be called whenever another level has been selected.
    void newSelection(int row);
    /// Will be called whenever the new chars description is changed.
    void newCharsChanged(const QString& text);
    /// Will be called when the "New Level" button has been clicked.
    void newLevel();
    /// Will be called when the "Delete Level" button has been clicked.
    void deleteLevel();
    /// Will be called when the "Move Level Up" button has been clicked.
    void moveUp();
    /// Will be called when the "Move Level Down" button has been clicked.
    void moveDown();

  private:
    /// Transfers data from the lecture object to the dialog.
    void transfer_to_dialog();
    /// Transfers data from the dialog to the lecture object.
    void transfer_from_dialog();
    /// Fills the level user interface with data from the current level (stored in m_level).
    void showCurrentLevel();
    /// Copies the content of the user interface into the vector with the level data.
    void storeCurrentLevel();
    /// Creates a default level and appends it to the already existing levels.
    void createNewLevel();
    /// Setups and opens the 'Open request dialog'. The url 'url' is used in the
    /// open request dialog for the 'current' url selection. When the open request 
    /// dialog is closed the function attempts to load the lecture or if that failes
    /// creates a new lecture. 
    /// @return The function returns the return code from the open request dialog, so 
    ///         that one can react on a "cancel" choice.
    int openLectureFile(const KUrl& url);
    /// Changes the state of the lecture file (flag==true means modified).
    void setModified(bool flag);
    /// If the lecture is modified the user is prompted to save it or throw away the changes. 
    /// If the user accepts the dialog the file is saved. 
    /// @return The function returns 'false' if the user aborted the save request, otherwise true.
    bool saveModified();

    KTouchLecture	m_lecture;         ///< The currently used lecture.
    int             m_level;           ///< The current level number, corresponds to the row.
    bool            m_modified;        ///< Flag indicating whether the lecture has been modified.
    KUrl            m_currentURL;      ///< URL of the current lecture.
};

#endif // KTOUCHLECTUREEDITORDIALOG_H