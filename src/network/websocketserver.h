#pragma once

#include <QObject>

class QWebSocketServer;

class WebSocketServer : public QObject
{
public:
	WebSocketServer();
	~WebSocketServer();

private:
	QWebSocketServer* m_webSocketServer;
};
