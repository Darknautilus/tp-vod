#include "insavodServer.h"
#include "fenetreServ.h"

insavodServer::insavodServer(QString _name, fenetreServ *_view, int _port) : name(_name), port(_port), addr(QHostAddress::Any), view(_view)
{
}

insavodServer::~insavodServer()
{
	qDeleteAll(clientConnections);
}

void insavodServer::start()
{
	viewMessage(QString::fromUtf8("démarré sur le port ")+QString::number(port));
}

void insavodServer::stop()
{
	viewMessage(QString::fromUtf8("arrêté sur le port ")+QString::number(port));
}

void insavodServer::sendImage(QString imgName)
{
	viewMessage("Envoi de "+imgName);
}

void insavodServer::viewMessage(QString message)
{
	view->printMessage(QString("[")+name+QString("] ")+message);
}

QString insavodServer::parseCatalog()
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
