#ifndef _WEBSOCKET_H
#define _WEBSOCKET_H

#include <QtNetwork>
#include <QUrl>

class WebSocket: public QObject
{
    Q_OBJECT

public:
    WebSocket(QTcpSocket *sock, QUrl viewer, int buftime);
    ~WebSocket();

    /* Socket-like interfaces */
    qint64 write(const char *buf, qint64 maxSize);
    qint64 read(char *data, qint64 maxSize);
    qint64 bytesAvailable() const;
    bool flush();

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

    enum {
        OpContinuation = 0x0,
        OpTextFrame,
        OpBinaryFrame,
        OpClose = 0x8,
        OpPing,
        OpPong
    };

    void sendResponse(int code, QString response);
    void sendHeader(QString header, QString value);
    void sendError(int code, QString message);
    qint64 sendFrame(QByteArray buf);
    void endHeaders();
    WState processHeader();
    WState sendHandshake();
    WState decodeFrame();
    void encodeFrame();
    void abort(QString message);
    void sendPong();
    void sendClose();

};

#endif
