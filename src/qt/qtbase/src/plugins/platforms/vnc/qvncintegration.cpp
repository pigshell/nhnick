/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the plugins of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qvncintegration.h"
#include "qvncscreen.h"

#if defined(Q_OS_MAC)
# include <QtPlatformSupport/private/qcoretextfontdatabase_p.h>
#else
# include <QtPlatformSupport/private/qgenericunixfontdatabase_p.h>
#endif

#include <QtPlatformSupport/private/qgenericunixeventdispatcher_p.h>

#include <QtPlatformSupport/private/qfbbackingstore_p.h>
#include <QtPlatformSupport/private/qfbwindow_p.h>
#include <QtPlatformSupport/private/qfbcursor_p.h>
//#include <private/qinputdevicemanager_p_p.h>

#include <QtGui/private/qguiapplication_p.h>
#include <qpa/qplatforminputcontextfactory_p.h>
#include <QDebug>

QT_BEGIN_NAMESPACE

QPlatformFontDatabase *getPlatformDatabase()
{
    QPlatformFontDatabase *db;
#if defined(Q_OS_MAC)
    db = new QCoreTextFontDatabase();
#else
    db = new QGenericUnixFontDatabase();
#endif
    return db;
}

QVNCIntegration::QVNCIntegration(const QStringList &paramList)
    : m_fontDb(getPlatformDatabase())
{
    m_primaryScreen = new QVNCScreen(paramList);
}

QVNCIntegration::~QVNCIntegration()
{
    delete m_primaryScreen;
}

void QVNCIntegration::initialize()
{
    if (m_primaryScreen->initialize())
        screenAdded(m_primaryScreen);
    else
        qWarning("vnc: Failed to initialize screen");

    m_inputContext = QPlatformInputContextFactory::create();
    m_nativeInterface.reset(new QPlatformNativeInterface);
    //QInputDeviceManagerPrivate::get(QGuiApplicationPrivate::inputDeviceManager())->setDeviceCount(QInputDeviceManager::DeviceTypePointer, 1);
}

bool QVNCIntegration::hasCapability(QPlatformIntegration::Capability cap) const
{
    switch (cap) {
    case ThreadedPixmaps: return true;
    case WindowManagement: return false;
    default: return QPlatformIntegration::hasCapability(cap);
    }
}

QPlatformBackingStore *QVNCIntegration::createPlatformBackingStore(QWindow *window) const
{
    return new QFbBackingStore(window);
}

QPlatformWindow* QVNCIntegration::createPlatformWindow(QWindow* window) const
{
    return new QFbWindow(window);
}

QAbstractEventDispatcher *QVNCIntegration::createEventDispatcher() const
{
    return createUnixEventDispatcher();
}

QList<QPlatformScreen *> QVNCIntegration::screens() const
{
    QList<QPlatformScreen *> list;
    list.append(m_primaryScreen);
    return list;
}

QPlatformFontDatabase *QVNCIntegration::fontDatabase() const
{
    return m_fontDb.data();
}

QPlatformNativeInterface *QVNCIntegration::nativeInterface() const
{
    return m_nativeInterface.data();
}

QT_END_NAMESPACE
