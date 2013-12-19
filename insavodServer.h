#ifndef _INSAVODSERVER_H_
#define _INSAVODSERVER_H_

#include <QString>
#include <QHostAddress>
#include <QStringList>
#include <QFile>

class fenetreServ;

class insavodServer
{
	public:
		enum protocol
		{
			TCP_PULL,
			TCP_PUSH,
			UDP_PULL,
			UDP_PUSH,
			MCAST_PUSH,
			NULL_PROTOCOL
		};
		
		enum fluxParamCode
		{
			ID,
			NAME,
			PROTOCOL,
			IPS,
			PORT,
			TYPE,
			ADDRESS
		};
		
		struct fluxDesc
		{
			QString name;
			protocol protocolCode;
			float ips;
			int port;
			QString type;
			QString address;
			QList<QFile*> files;

			virtual ~fluxDesc()
			{
				files.clear();
			}
		};
		
		insavodServer(QString _name, fenetreServ *_view, int _port = 0);
		virtual ~insavodServer();

		virtual void start();
		virtual void stop();
		virtual void sendImage(QString);
		
		void viewMessage(QString);
		void parseCatalog();
	
		static const QMap<protocol, QString> strProtocols;
		static protocol protocolFromStr(QString);
	
	protected:
		QString name;
		int port;
		QHostAddress addr;
		QList<QAbstractSocket *> clientConnections;
		QMap<int,fluxDesc> fluxMap;
		QString APP_PATH;
	
	private:
		fenetreServ *view;
		static const QHash<fluxParamCode, QString> fluxParams;
		
};

typedef insavodServer::protocol insavodProtocol;
typedef insavodServer::fluxParamCode insavodFluxParam;

inline const QMap<insavodProtocol, QString> mkStrProtocols()
{
	QMap<insavodProtocol, QString> tmp;
	tmp[insavodProtocol::TCP_PULL] = QString("TCP_PULL");
	tmp[insavodProtocol::TCP_PUSH] = QString("TCP_PUSH");
	tmp[insavodProtocol::UDP_PULL] = QString("UDP_PULL");
	tmp[insavodProtocol::UDP_PUSH] = QString("UDP_PUSH");
	tmp[insavodProtocol::MCAST_PUSH] = QString("MCAST_PUSH");
	return tmp;
}

inline const QHash<insavodFluxParam, QString> createFluxHash()
{
	QHash<insavodFluxParam, QString> ret;
	ret[insavodFluxParam::ID] = QString("ID: ");
	ret[insavodFluxParam::NAME] = QString("Name: ");
	ret[insavodFluxParam::PROTOCOL] = QString("Protocol: ");
	ret[insavodFluxParam::IPS] = QString("IPS: ");
	ret[insavodFluxParam::PORT] = QString("Port: ");
	ret[insavodFluxParam::TYPE] = QString("Type: ");
	ret[insavodFluxParam::ADDRESS] = QString("Address: ");
	return ret;
}

#endif
