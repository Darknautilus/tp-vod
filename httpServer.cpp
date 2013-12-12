#include <iostream>
#include <QTcpSocket>
#include <QString>
#include <QStringList>
#include <QTextStream>

#include "httpServer.h"
#include "fenetreServ.h"

using namespace std;

httpServer::httpServer(QString _name, int _port, fenetreServ *_view) : insavodServer(_name, _view, _port)
{
}

httpServer::~httpServer()
{
}

void httpServer::start()
{
	insavodServer::start();
	listen(addr,port);
}

void httpServer::stop()
{
	insavodServer::stop();
	close();
}

void httpServer::incomingConnection(int socketDesc)
{
	QTcpSocket *client = new QTcpSocket();
	client->setSocketDescriptor(socketDesc);
	QObject::connect(client, SIGNAL(readyRead()), this, SLOT(getClientRequest()));
	QObject::connect(client, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
	viewMessage(QString("nouvelle connexion !"));
	clientConnections.append(client);
}

void httpServer::getClientRequest()
{
	QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());	
	if(client->canReadLine())
	{
		QStringList lines = QString(client->readLine()).split(QRegExp("[ \r\n][ \r\n]*"));
		if(lines[0] == "GET" && QFile::exists(lines[1]))
		{
			viewMessage(QString("Envoi de ")+lines[1]);
			QFile catalogue(lines[1].toLocal8Bit().constData());
			catalogue.open(QIODevice::ReadOnly);
			QTextStream os(client);
			QTextStream is(&catalogue);
			os.setAutoDetectUnicode(true);
			is.setAutoDetectUnicode(true);
			os << "HTTP/1.0 200 OK\r\nhttpServer: TP_Serveur_3208\r\nConnection: Keep-Alive\r\nContent-Type: text/txt\r\nContent-Length: " << catalogue.size() << "\r\n\r\n";
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

void httpServer::clientDisconnected()
{
	QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());		 
	if (!client)
		return;		 
	clientConnections.removeAll(client);
	client->deleteLater();
	viewMessage(QString::fromUtf8("connexion terminée"));
}
