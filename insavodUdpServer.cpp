#include <iostream>
#include <QUdpSocket>
#include <QStringList>

#include "insavodUdpServer.h"

insavodUdpServer::insavodUdpServer(QString _name, int _port, fenetreServ * _view) : insavodServer(_name, _view, _port)
{}

insavodUdpServer::~insavodUdpServer()
{
	stop();
}

void insavodUdpServer::start()
{
	insavodServer::start();
	listen(addr,port);
}

void insavodUdpServer::stop()
{
	insavodServer::stop();
	close();
}

void insavodUdpServer::sendImage(QString imgName)
{
	insavodServer::sendImage(imgName);
}

void insavodUdpServer::incomingConnection(int socketDesc)
{
	QUdpSocket *client = new QUdpSocket();
	client->setSocketDescriptor(socketDesc);
	QObject::connect(client, SIGNAL(readyRead()), this, SLOT(getClientRequest()));
	QObject::connect(client, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
	clientConnections.append(client);
}

void insavodUdpServer::getClientRequest()
{
	QUdpSocket *client = qobject_cast<QUdpSocket *>(sender());	
	if(client->canReadLine())
	{
		QStringList lines = QString(client->readLine()).split(QRegExp("[ \r\n][ \r\n]*"));
	}	
}

void insavodUdpServer::clientDisconnected()
{
	QUdpSocket *client = qobject_cast<QUdpSocket *>(sender());		 
	if (!client)
		return;		 
	clientConnections.removeAll(client);
	client->deleteLater();
}
