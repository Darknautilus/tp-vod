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
/*	//Attend indéfiniment que de nouvelles informations soient disponibles
	while (socketUdpServer->waitForReadyRead(-1))
	{
		//Vérifie s'il y a des informations en attente d'être lues
		while (socketUdpServer->hasPendingDatagrams())
		{*/
	connect(socketUdpServer, SIGNAL(readyRead()), this, SLOT (getClientRequest()));

	QByteArray datagram;
	datagram.resize(socketUdpServer->pendingDatagramSize());
		
	QHostAddress adresseClient;
	quint16 portClient;

	socketUdpServer->readDatagram(datagram.data(), datagram.size(), &adresseClient, &portClient);
	viewMessage("Informations recues du client"+adresseClient.toString());

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

/*void insavodUdpServer::incomingConnection(int socketDesc)
{
	client->setSocketDescriptor(socketDesc);
	QObject::connect(client, SIGNAL(readyRead()), this, SLOT(getClientRequest()));
}
*/

/*void insavodUdpServer::incomingConnection(int sock)
{
 	QUdpSocket *client = new QUdpSocket();
	client->setSocketDescriptor(sock);
	QObject::connect(client,SIGNAL(readyRead()), this, SLOT(getClientRequest()));
	QObject::connect(client, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
	clientConnections.append(client);
	dataConnection = new QUdpSocket();
}
*/

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
