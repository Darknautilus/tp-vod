#include <iostream>
#include <QTcpSocket>
#include <QString>
#include <QStringList>
#include <QTextStream>

#include "Server.h"

using namespace std;

Server::Server(QString pCatalog)
{
	if(!QFile::exists(pCatalog))
	{
		throw SERVER_ERRORS::CATALOG_NOT_FOUND;
	}
	else
	{
		catalog = new QFile(pCatalog);
	}
	QObject::connect(this, SIGNAL(newConnection()), this, SLOT(connectionFeedback()));
}

Server::~Server()
{
	qDeleteAll(clientConnections);
	delete catalog;
}

void Server::incomingConnection(int socketDesc)
{
	QTcpSocket *client = new QTcpSocket();
	client->setSocketDescriptor(socketDesc);
	QObject::connect(client, SIGNAL(readyRead()), this, SLOT(getClientRequest()));
	QObject::connect(client, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
	clientConnections.append(client);
}

void Server::getClientRequest()
{
	QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());	
	if(client->canReadLine())
	{
		QStringList lines = QString(client->readLine()).split(QRegExp("[ \r\n][ \r\n]*"));
		if(lines[0] == "GET" && QFile::exists(lines[1]))
		{
			cout << "Envoi de " << lines[1].toLocal8Bit().constData() << endl;
			QFile catalogue(lines[1].toLocal8Bit().constData());
			catalogue.open(QIODevice::ReadOnly);
			QTextStream os(client);
			QTextStream is(&catalogue);
			os.setAutoDetectUnicode(true);
			is.setAutoDetectUnicode(true);
			os << "HTTP/1.0 200 OK\r\nServer: TP_Serveur_3208\r\nConnection: Keep-Alive\r\nContent-Type: text/txt\r\nContent-Length: " << catalogue.size() << "\r\n\r\n";
			QString line;
			do
			{
				line = is.readLine();
				if(!line.isNull())
				{
					os << line.toLocal8Bit().constData() << endl;
				}
			}
			while(!line.isNull());
			catalogue.close();
		}
	}	
}

void Server::connectionFeedback()
{
	std::cout << "Nouvelle connexion !" << std::endl;
}


void Server::serverMessage()
{
	std::cout << "plop" << std::endl;
}

void Server::clientDisconnected()
{
	QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());		 
	if (!client)
		return;		 
	clientConnections.removeAll(client);
	client->deleteLater();
}
