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
