/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the plugins of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/


#include "qvncscreen.h"
#include "qvnccursor.h"
#include "qvncserver.h"
#include <QtCore/QRegularExpression>
#include <QtGui/QPainter>
#include <QDebug>

QT_BEGIN_NAMESPACE

QVNCScreen::QVNCScreen(const QStringList &args)
    : mArgs(args)
{
}

QVNCScreen::~QVNCScreen()
{
}

static inline int defaultWidth() { return 1024; }
static inline int defaultHeight() { return 768; }
static inline int defaultDisplay() { return 0; }

static void usage()
{
    qWarning() << "VNC Platform Integration options:";
    qWarning() << "    size=<Width>x<Height> - set the display width and height";
    qWarning() << "         defaults to" << defaultWidth() << "x" << defaultHeight();
    qWarning() << "    display=<ID> - set the VNC display port to ID + 5900";
    qWarning() << "         defaults to" << defaultDisplay();
}

bool QVNCScreen::initialize()
{
    QRegularExpression sizeRx(QLatin1String("size=(\\d+)x(\\d+)"));
    QRegularExpression displayRx(QLatin1String("display=(\\d+)"));
    QRect userGeometry;
    bool showUsage = false;
    int display = defaultDisplay();

    foreach (const QString &arg, mArgs) {
        QRegularExpressionMatch match;
        if (arg.contains(sizeRx, &match)) {
            userGeometry.setSize(QSize(match.captured(1).toInt(), match.captured(2).toInt()));
            userGeometry.setTopLeft(QPoint(0, 0));
        } else if (arg.contains(displayRx, &match)) {
            display = match.captured(1).toInt();
        } else {
            qWarning() << "Unknown VNC options:" << arg;
            showUsage = true;
        }
    }

    if (showUsage) {
        usage();
    }

    if (!userGeometry.isValid()) {
        userGeometry.setSize(QSize(defaultWidth(), defaultHeight()));
        userGeometry.setTopLeft(QPoint(0, 0));
    }

    mGeometry = userGeometry;
    mDepth = 32;
    mFormat = QImage::Format_RGB32;
    mPhysicalSize = userGeometry.size() * 254 / 720;

    QFbScreen::initializeCompositor();
    d_ptr = new QVNCScreenPrivate(this);
    QVNCCursor *c = new QVNCCursor(d_ptr->vncServer, this);
    mCursor = c;
    d_ptr->vncServer->setCursor(c);

    return true;
}


QRegion QVNCScreen::doRedraw()
{
    QRegion touched = QFbScreen::doRedraw();

    if (touched.isEmpty())
        return touched;

    QVector<QRect> rects = touched.rects();
    for (int i = 0; i < rects.size(); i++)
        d_ptr->setDirty(rects[i]);
    return touched;
}

QVNCDirtyMap *QVNCScreen::dirtyMap()
{
    return d_ptr->dirty;
}

QT_END_NAMESPACE
