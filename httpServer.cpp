#include "httpServer.h"
#include "fenetreServ.h"

httpServer::httpServer(QString _name, int _port, fenetreServ *_view) : insavodTcpServer(_name, _port, _view)
{
}

httpServer::~httpServer()
{
	stop();
}

void httpServer::start()
{
	insavodTcpServer::start();
	parseCatalog();
}

void httpServer::stop()
{
	insavodTcpServer::stop();
	QFile::remove(QCoreApplication::applicationDirPath()+"/catalog.tmp");
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
