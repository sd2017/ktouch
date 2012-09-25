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

#include "graphplugin.h"

#include <qdeclarative.h>
#include <QAbstractTableModel>

#include "linegraphcore.h"
#include "dimension.h"
#include "linegraphbackgroundpainter.h"
#include "linegraphpainter.h"
#include "linegraphpoint.h"

void GraphPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QLatin1String("org.kde.ktouch.graph"));

    qmlRegisterType<LineGraphCore>(uri, 0, 1, "GraphCoreItem");
    qmlRegisterType<Dimension>(uri, 0, 1, "Dimension");
    qmlRegisterType<LineGraphBackgroundPainter>(uri, 0, 1, "LineGraphBackgroundPainter");
    qmlRegisterType<LineGraphPainter>(uri, 0, 1, "LineGraphPainter");
    qmlRegisterType<LineGraphPoint>(uri, 0, 1, "LineGraphPoint");

    qmlRegisterUncreatableType<QAbstractTableModel>(uri, 0, 1, "QAbstractTableModel", "abstract class");
}

Q_EXPORT_PLUGIN2(graphplugin, GraphPlugin)
