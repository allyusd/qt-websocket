#include "websocketserver.h"

#include <QWebSocket>
#include <QWebSocketServer>
#include <QJsonObject>

WebSocketServer::WebSocketServer()
{
	this->m_webSocketServer = new QWebSocketServer("Web Server", QWebSocketServer::NonSecureMode, this);

	connect(this->m_webSocketServer, &QWebSocketServer::newConnection, [=]() {
		qDebug() << "new client socket";

		QWebSocket* socket = this->m_webSocketServer->nextPendingConnection();

		connect(socket, &QWebSocket::disconnected, [=]() {
			qDebug() << "client socket disconnected";

			socket->deleteLater();
		});

		connect(socket, &QWebSocket::textMessageReceived, [=](QString message) {
			qDebug() << "client textMessageReceived";

			qDebug() << "Read: " << message;
			qDebug() << "Send " << message;

			socket->sendTextMessage(message);
			socket->close();
		});

		connect(socket, &QWebSocket::binaryMessageReceived, [=](QByteArray message) {
			qDebug() << "client processBinaryMessage";

			qDebug() << "Read: " << message;
			qDebug() << "Send " << message;

			socket->sendBinaryMessage(message);
			socket->close();
		});
	});

	this->m_webSocketServer->listen(QHostAddress::Any, 8812);
	qDebug() << "Server listen: 8812";
}

WebSocketServer::~WebSocketServer()
{
}
