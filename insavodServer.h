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
			MCAST_PUSH
		};
		
		struct fluxDesc
		{
			QString name;
			protocol protocolCode;
			float ips;
			QList<QFile> files;
		};
		
		insavodServer(QString _name, fenetreServ *_view, int _port = 0);
		virtual ~insavodServer();

		virtual void start();
		virtual void stop();
		virtual void sendImage(QString);
		
		void viewMessage(QString);
		void parseCatalog();
	
		static const std::map<protocol,const char *> strProtocols;
	
	protected:
		QString name;
		int port;
		QHostAddress addr;
		QList<QAbstractSocket *> clientConnections;
		QMap<int,fluxDesc> flux;
		QString APP_PATH;
	
	private:
		struct fluxInfo
		{
			QString id;
			QString name;
			QString protocol;
			QString address;
			QString port;
			QString type;
			QString ips;
			QStringList files;
		};
		
		fenetreServ *view;
		static const QHash<int,QString> fluxParams;
		
};

#endif
