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
	dataConnection = new QTcpSocket();
	listen(addr,port);
}

void insavodTcpServer::stop()
{
	insavodServer::stop();
	delete dataConnection;
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
		QString req(client->readAll());
		QStringList lines = req.split(QRegExp("[ \r\n][\r\n]*"));
		if(lines[0] == "GET")
		{
			bool isId;
			int id = lines[1].toInt(&isId);
			if(isId)
			{
				if(!dataConnected)
				{
					currentFlux = id;
					QTextStream os(client);
					if(lines.size() >= 4 && lines[2] == "LISTEN_PORT")
					{
						bool isPort;
						int port = lines[3].toInt(&isPort);
						if(isPort && !dataConnected)
						{
							dataConnection->connectToHost(client->peerAddress(), port);
							if(dataConnection->waitForConnected(1000))
							{
								dataConnected = true;
							}
						}
					}
				}
				else
				{
					// Envoi de l'image id
					if(id > 0)
					{
						currentImage = id;
					}
					if(insavodServer::fluxMap[currentFlux].files.size() >= currentImage)
					{
						QFile *currentImageDesc = insavodServer::fluxMap[currentFlux].files[currentImage-1];
						if(currentImageDesc->open(QIODevice::ReadOnly))
						{
							QDataStream os(dataConnection);
							os << currentImage << "\r\n" << currentImageDesc->size() << "\r\n" << currentImageDesc->readAll();
							currentImageDesc->close();
						}
					}
				}
			}
		}
		else if(lines[0] == "END" && dataConnected)
		{
			dataConnected = false;
			dataConnection->disconnectFromHost();
		}
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
