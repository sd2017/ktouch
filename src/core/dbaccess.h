/*
 * Copyright 2012  Sebastian Gottfried <sebastiangottfried@web.de>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DBACCESS_H
#define DBACCESS_H

#include <QObject>

class QSqlDatabase;
class QSqlError;

class DbAccess : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString errorMessage READ errorMessage NOTIFY errorMessageChanged)
public:
    explicit DbAccess(QObject* parent = 0);
    QString errorMessage() const;

signals:
    void errorMessageChanged();

protected:
    QSqlDatabase database();
    void raiseError(const QSqlError& error);
private:
    bool checkDbSchema();
    bool migrateFrom1_0To1_1();
    QString m_errorMessage;
};

#endif // DBACCESS_H
