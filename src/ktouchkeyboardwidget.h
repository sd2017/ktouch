/***************************************************************************
 *   ktouchkeyboardwidget.h                                                *
 *   ----------------------                                                *
 *   Copyright (C) 2000 by Håvard Frøiland, 2006 by Andreas Nicolai        *
 *   haavard@users.sourceforge.net                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef KTOUCHKEYBOARDWIDGET_H
#define KTOUCHKEYBOARDWIDGET_H

#include <QGraphicsView>
#include <QResizeEvent>
#include <QPaintEvent>
#include <QList>
#include <QVector>
#include <QMap>
#include <QSet>

class KUrl;
class KTouchKeyboard;

/** This is the keyboard widget at the bottom of the training screen.
 *  In addition to the painting functions this class has the member
 *  functions loadKeyboard() and saveKeyboard() which can read and write
 *  a keyboard layout from/into a file. \n
 *  The keyboard is drawn in the paintEvent() member function. The
 *  resizing, that means the recalculation of m_shift is
 *  done in the resizeEvent() member function. \n
 *  The state of keyboard and keys does not change while it is
 *  repainted or resized. Only when a new character has been typed
 *  and the newKey() slot is called the state changes (and thus the
 *  activated keys and finger key animations etc.)
 */
class KTouchKeyboardWidget : public QGraphicsView {
    Q_OBJECT
  public:
    /// Constructor
    explicit KTouchKeyboardWidget(QWidget *parent);
	/// Destructor (frees allocated data).
    ~KTouchKeyboardWidget();
    /// Reads a keyboard layout from the given URL.
    /// The function returns 'true' when the reading was successful or 'false' if not. In this
    /// case the optional parameter errorMsg contains the error message.
    bool loadKeyboard(QWidget * window, const KUrl& url, QString& errorMsg);
    /// Applies preferences to the keyboard layout and the keys.
    /// This means that the layout is basically recreated and if the layout type/language
    /// changed it will be reloaded.
    void applyPreferences(QWidget * window, bool silent);
	/// This sets the string with currently known characters and sets the keys that do not
	/// contain a character of this list to inactive.
	void setKnownChars(const QSet<QChar>& knownChars);

  public slots:
    /// This function displays the next key (or key combination) the user has to press.
    void newKey(const QChar& nextChar);
	void resizeKeyboard();

  protected:

    /// Resizes the keyboard.
    void resizeEvent(QResizeEvent *);
    void reset();

  private:
    /// Does what the name says (create a default keyboard which is a number keypad).
    /// This function is needed in case there no keyboard file could be found.
    void createDefaultKeyboard();

	KTouchKeyboard*				m_keyboard;			///< Data defining a keyboard.

    QString						m_currentLayout;    ///< The name of the currently used layout.
    QChar						m_nextKey;          ///< The next to be pressed character.
	QSet<QChar>					m_knownChars;		///< String with already known characters in this lecture and level.

    QGraphicsScene*				m_scene;			///< The graphics scene 
};

#endif  // KTOUCHKEYBOARDWIDGET_H
