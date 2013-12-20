#include <iostream>
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

	socketUdpServer = new QUdpSocket();
	socketUdpServer->bind(8083, QUdpSocket::ShareAddress);
	connect(socketUdpServer, SIGNAL(readyRead()), this, SLOT (getClientRequest()));

	QByteArray datagram;
	datagram.resize(socketUdpServer->pendingDatagramSize());
		
	QHostAddress adresseClient;
	quint16 portClient;

	socketUdpServer->readDatagram(datagram.data(), datagram.size(), &adresseClient, &portClient);
}

void insavodUdpServer::stop()
{
	insavodServer::stop();
	socketUdpServer->close();
	delete socketUdpServer;
}

void insavodUdpServer::sendImage(QString imgName)
{
	insavodServer::sendImage(imgName);
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
	{
	}
	else 
	{	
	clientConnections.removeAll(client);
	client->deleteLater();
	}
	delete dataConnection;
}
