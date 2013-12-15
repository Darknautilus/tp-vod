#ifndef _SERVER_H_
#define _SERVER_H_

#include <QFile>

#include "insavodTcpServer.h"

class fenetreServ;

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

inline QHash<int,QString> createFluxHash()
{
	QHash<int,QString> ret;
	ret[1] = "ID: ";
	ret[2] = "Name: ";
	ret[3] = "Type: ";
	ret[4] = "Address: ";
	ret[5] = "Port: ";
	ret[6] = "Protocol: ";
	ret[7] = "IPS: ";
	return ret;
}

const QHash<int,QString> fluxParams = createFluxHash();

class httpServer : public insavodTcpServer
{
	Q_OBJECT

	public:
		httpServer(QString, int, fenetreServ *);
		virtual ~httpServer();

		void start();
		void stop();
		
		QString parseCatalog();

	public slots:
		void getClientRequest();
};

#endif
