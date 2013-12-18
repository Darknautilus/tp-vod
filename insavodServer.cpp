#include "insavodServer.h"
#include "fenetreServ.h"

const QMap<insavodProtocol, QString> insavodServer::strProtocols = mkStrProtocols();
const QHash<insavodFluxParam, QString> insavodServer::fluxParams = createFluxHash();

insavodServer::insavodServer(QString _name, fenetreServ *_view, int _port) : name(_name), port(_port), addr(QHostAddress::Any), APP_PATH(_view->getAppDirPath()), view(_view)
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

insavodProtocol insavodServer::protocolFromStr(QString str)
{
	QMapIterator<insavodProtocol,QString> i(strProtocols);
	while(i.hasNext())
	{
		i.next();
		if(str == i.value())
		{
			return i.key();
		}
	}
	return insavodProtocol::NULL_PROTOCOL;
}

void insavodServer::parseCatalog()
{
	QString line;

	QFile catalog(APP_PATH+"/catalog.tmp");
	catalog.open(QIODevice::WriteOnly | QIODevice::Text);
	QTextStream cos(&catalog);

	if(QFile::exists(APP_PATH+"/startup.txt"))
	{
		QStringList sflux;
		QFile startup(APP_PATH+"/startup.txt");
		startup.open(QIODevice::ReadOnly | QIODevice::Text);
		viewMessage("Reading startup.txt");
		QTextStream sstartup(&startup);
		line = sstartup.readLine();
		int i=1;
		while(!line.isNull())
		{
			// Analyse startup.txt
			if(i <= 2)
			{
				cos << line << "\r\n";
			}
			else
			{
				sflux << line;
			}
			line = sstartup.readLine();
			i++;
		}
		for(i=0;i<sflux.size();i++)
		{
			//fluxInfo fi;
			int fluxId = -1;
			fluxDesc flux_desc;
			bool idSet = false;
			bool nameSet = false;
			bool protocolSet = false;
			bool ipsSet = false;
			bool portSet = false;
			bool typeSet = false;
			bool addressSet = false;
			
			QFile flux(APP_PATH+"/"+sflux[i]);
			flux.open(QIODevice::ReadOnly | QIODevice::Text);
			viewMessage("Reading "+sflux[i]);
			QTextStream sflux(&flux);
			
			line = sflux.readLine();
			while(!line.isNull())
			{
				// Analyse du flux
				if(!idSet && line.contains(fluxParams[insavodFluxParam::ID], Qt::CaseInsensitive))
				{
					fluxId = line.remove(fluxParams[insavodFluxParam::ID], Qt::CaseInsensitive).toInt();
					idSet = true;
				}
				else if(!nameSet && line.contains(fluxParams[insavodFluxParam::NAME], Qt::CaseInsensitive))
				{
					flux_desc.name = line.remove(fluxParams[insavodFluxParam::NAME], Qt::CaseInsensitive);
					nameSet = true;
				}
				else if(!protocolSet && line.contains(fluxParams[insavodFluxParam::PROTOCOL], Qt::CaseInsensitive))
				{
					flux_desc.protocolCode = protocolFromStr(line.remove(fluxParams[insavodFluxParam::PROTOCOL], Qt::CaseInsensitive));
					protocolSet = true;
				}
				else if(!ipsSet && line.contains(fluxParams[insavodFluxParam::IPS], Qt::CaseInsensitive))
				{
					flux_desc.ips = line.remove(fluxParams[insavodFluxParam::IPS], Qt::CaseInsensitive).toFloat();
					ipsSet = true;
				}
				else if(!portSet && line.contains(fluxParams[insavodFluxParam::PORT], Qt::CaseInsensitive))
				{
					flux_desc.port = line.remove(fluxParams[insavodFluxParam::PORT], Qt::CaseInsensitive).toInt();
					portSet = true;
				}
				else if(!typeSet && line.contains(fluxParams[insavodFluxParam::TYPE], Qt::CaseInsensitive))
				{
					flux_desc.type = line.remove(fluxParams[insavodFluxParam::TYPE], Qt::CaseInsensitive);
					typeSet = true;
				}
				else if(!addressSet && line.contains(fluxParams[insavodFluxParam::ADDRESS], Qt::CaseInsensitive))
				{
					flux_desc.address = line.remove(fluxParams[insavodFluxParam::ADDRESS], Qt::CaseInsensitive);
					addressSet = true;
				}
				else
				{
					if(QFile::exists(APP_PATH+line))
					{
						flux_desc.files.append(new QFile(APP_PATH+line));
					}
					else
					{
						viewMessage("Erreur dans le flux : image non trouvée");
					}
				}
				line = sflux.readLine();
			}
			if(addressSet && typeSet && portSet && ipsSet && protocolSet && nameSet && idSet)
			{
				fluxMap.insert(fluxId,flux_desc);
			}
			flux.close();
		}
		startup.close();

		for(QMap<int,fluxDesc>::const_iterator it = fluxMap.constBegin(); it != fluxMap.constEnd(); ++it)
		{
			cos << "Object ID=" << it.key() << " name=" << it.value().name << " type=" << it.value().type << " address=" << it.value().address << " port=" << it.value().port << " protocol=" << strProtocols[it.value().protocolCode] << " ips=" << it.value().ips << " \r\n";
		}
	}
	else
	{
		viewMessage("startup.txt file couldn't be found");
		stop();
	}
	cos << "\r\n";
	catalog.close();
}
