#include "insavodTcpServer.h"

insavodTcpServer::insavodTcpServer(QString _name, int _port, fenetreServ * _view) : insavodServer(_name, _view, _port), dataConnected(false), currentImage(1), currentFlux(1)
{
}

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
	QTextStream qout(stdout);
	QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());	
	if(client->canReadLine())
	{
		QStringList lines = QString(client->readLine()).split(QRegExp("[ \r\n][ \r\n]*"));
		for(int i=0;i<lines.size();i++)
		{
			qout << lines[i] << endl;
		}
		if(lines[0] == "GET")
		{
			bool isId;
			int id = lines[1].toInt(&isId);
			if(isId)
			{
				if(dataConnected)
				{
					// Envoi de l'image id
					if(id > 0)
					{
						currentImage = id;
					}
					if(fluxMap[currentFlux].files.size() >= currentImage)
					{
						QFile *currentImageDesc = fluxMap[currentFlux].files[currentImage-1];
						qout << "Image " << currentImage << " du flux " << currentFlux << endl;
						if(currentImageDesc->open(QIODevice::ReadOnly))
						{
							qout << "Envoi de l'image " << currentImageDesc->fileName() << endl;
							QDataStream os(dataConnection);
							os << currentImage << "\r\n" << currentImageDesc->size() << "\r\n" << currentImageDesc->readAll();
							currentImageDesc->close();
						}
					}
				}
				else
				{
					currentFlux = id;
				}
			}
		}
		else if(lines[0] == "LISTEN_PORT")
		{
			bool isPort;
			int port = lines[1].toInt(&isPort);
			if(isPort && !dataConnected)
			{
				dataConnection->connectToHost(client->peerAddress(), port);
				if(dataConnection->waitForConnected(1000))
				{
					qout << "Connected to " << client->peerAddress().toString() << ":" << port << endl;
					dataConnected = true;
				}
				else
				{
					qout << "Not connected" << endl;
				}
			}
		}
	}	
}

void insavodTcpServer::clientDisconnected()
{
	QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());		 
	int a=0;
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
