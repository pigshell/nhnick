/*
  Copyright (C) 2015 Coriolis Technologies Pvt Ltd, info@coriolis.co.in
  Author: Ganesh Varadarajan

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
  
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.
  
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef _WEBSOCKET_H
#define _WEBSOCKET_H

#include <QtNetwork>
#include <QUrl>

class WebSocket: public QObject
{
    Q_OBJECT

public:
    WebSocket(QObject *p, QTcpSocket *sock, QUrl viewer, int buftime);
    ~WebSocket();

    /* Socket-like interfaces */
    qint64 write(const char *buf, qint64 maxSize);
    qint64 read(char *data, qint64 maxSize);
    qint64 bytesAvailable() const;
    bool flush();
    void close();

Q_SIGNALS:
    void setupComplete();
    void readyRead();
    void disconnected();

private slots:
    void readClient();
    void discardClient();
    void flushOutbuf();

private:
    QTcpSocket *socket;
    enum WState {Unconnected, Request, Header, Response, FrameStart,
        Frame};
    WState state;
    QHash<QString, QString> headers;
    QString subprotocol;
    QByteArray request;
    QByteArray frame;
    QByteArray inbuf;
    QByteArray outbuf;
    QUrl viewer;
    QString origin;
    qint64 wantbytes;
    int buftime;
    QTimer *timer;

    enum {
        OpContinuation = 0x0,
        OpTextFrame,
        OpBinaryFrame,
        OpClose = 0x8,
        OpPing,
        OpPong
    };

    void sendResponse(int code, const QString& response);
    void sendHeader(const QString& header, const QString& value);
    void sendError(int code, const QString& message);
    qint64 sendFrame(const QByteArray& buf);
    void endHeaders();
    WState processHeader();
    WState sendHandshake();
    WState decodeFrame();
    void encodeFrame();
    void abort(const QString& message);
    void sendPong(const QByteArray& framedata);
    void sendClose(const QByteArray& framedata, quint16 code = 1000);

};

#endif
