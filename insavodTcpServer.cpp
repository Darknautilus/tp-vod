#include "insavodTcpServer.h"

insavodTcpServer::insavodTcpServer(QString _name, int _port, fenetreServ * _view) : insavodServer(_name, _view, _port)
{}

insavodTcpServer::~insavodTcpServer()
{
	stop();
}

void insavodTcpServer::start()
{
	insavodServer::start();
	listen(addr,port);
}

void insavodTcpServer::stop()
{
	insavodServer::stop();
	close();
}

void insavodTcpServer::sendImage(QString imgName)
{
	insavodServer::sendImage(imgName);
}

void insavodTcpServer::incomingConnection(int socketDesc)
{
	QTcpSocket *client = new QTcpSocket();
	client->setSocketDescriptor(socketDesc);
	QObject::connect(client, SIGNAL(readyRead()), this, SLOT(getClientRequest()));
	QObject::connect(client, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
	clientConnections.append(client);
}

void insavodTcpServer::getClientRequest()
{
	QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());	
	if(client->canReadLine())
	{
		QStringList lines = QString(client->readLine()).split(QRegExp("[ \r\n][ \r\n]*"));
	}	
}

void insavodTcpServer::clientDisconnected()
{
	QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());		 
	if (!client)
		return;		 
	clientConnections.removeAll(client);
	client->deleteLater();
}
