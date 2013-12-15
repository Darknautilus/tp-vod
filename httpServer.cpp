#include <iostream>
#include <QTcpSocket>
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
	stop();
}

void httpServer::start()
{
	insavodServer::start();
	listen(addr,port);
	parseCatalog();
}

void httpServer::stop()
{
	QFile::remove(QCoreApplication::applicationDirPath()+"/catalog.tmp");
	insavodServer::stop();
	close();
}

QString httpServer::parseCatalog()
{
	QString APP_PATH = QCoreApplication::applicationDirPath();
	QString line;
	QString scatalog;
	QTextStream os(&scatalog);

	QFile catalog(APP_PATH+"/catalog.tmp");
	catalog.open(QIODevice::WriteOnly | QIODevice::Text);
	QTextStream cos(&catalog);

	if(QFile::exists(APP_PATH+"/startup.txt"))
	{
		QStringList sflux;
		QFile startup(APP_PATH+"/startup.txt");
		startup.open(QIODevice::ReadOnly | QIODevice::Text);
		QTextStream sstartup(&startup);
		line = sstartup.readLine();
		int i=1;
		while(!line.isNull())
		{
			// Analyse startup.txt
			if(i <= 2)
			{
				cos << line << "\r\n";
				os << line << endl;
			}
			else
			{
				sflux << line;
			}
			line = sstartup.readLine();
			i++;
		}
		QList<fluxInfo> flux;
		for(i=0;i<sflux.size();i++)
		{
			QFile flux(APP_PATH+"/"+sflux[i]);
			flux.open(QIODevice::ReadOnly | QIODevice::Text);
			QTextStream sflux(&flux);
			fluxInfo fi;
			line = sflux.readLine();
			int j=1;
			while(!line.isNull())
			{
				// Analyse du flux
				switch(j)
				{
					case 1:
						fi.id = line.remove(fluxParams[j]);
						break;
					case 2:
						fi.name = line.remove(fluxParams[j]);
						break;
					case 3:
						fi.type = line.remove(fluxParams[j]);
						break;
					case 4:
						fi.address = line.remove(fluxParams[j]);
						break;
					case 5:
						fi.port = line.remove(fluxParams[j]);
						break;
					case 6:
						fi.protocol = line.remove(fluxParams[j]);
						break;
					case 7:
						fi.ips = line.remove(fluxParams[j]);
						break;
					default:
						fi.files << line;
						break;	
				}
				line = sflux.readLine();
				j++;
			}
			QString object("Object ID="+fi.id+" name="+fi.name+" type="+fi.type+" address="+fi.address+" port="+fi.port+" protocol="+fi.protocol+" ips="+fi.ips+" ");
			cos << object << "\r\n";
			os << object << endl;
			flux.close();
		}
		startup.close();
	}
	cos << "\r\n";
	os << endl;
	catalog.close();
	return scatalog;
}

void httpServer::incomingConnection(int socketDesc)
{
	QTcpSocket *client = new QTcpSocket();
	client->setSocketDescriptor(socketDesc);
	QObject::connect(client, SIGNAL(readyRead()), this, SLOT(getClientRequest()));
	QObject::connect(client, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
	clientConnections.append(client);
}

void httpServer::getClientRequest()
{
	QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());	
	if(client->canReadLine())
	{
		QStringList lines = QString(client->readLine()).split(QRegExp("[ \r\n][ \r\n]*"));
		if(lines[0] == "GET")
		{
			viewMessage(QString::fromUtf8("Envoi du catalogue à ")+client->peerAddress().toString()+":"+QString::number(client->peerPort()));
			QFile catalogue(QCoreApplication::applicationDirPath()+"/catalog.tmp");
			catalogue.open(QIODevice::ReadOnly | QIODevice::Text);
			QTextStream os(client);
			QTextStream is(&catalogue);
			os << "HTTP/1.1 200 OK\r\nServer: TP_Serveur_3208\r\nConnection: Keep-Alive\r\nContent-Type: text/txt\r\nContent-Length: " << catalogue.size() << "\r\n\r\n";
			QString line = is.readLine();
			while(!line.isNull())
			{
				os << line.toLocal8Bit().constData() << "\r\n";
				line = is.readLine();
			}
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
}
