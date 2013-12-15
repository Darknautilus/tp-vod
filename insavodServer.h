#ifndef _INSAVODSERVER_H_
#define _INSAVODSERVER_H_

#include <QString>
#include <QHostAddress>
#include <QStringList>
#include <QFile>

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


class insavodServer
{
	public:
		insavodServer(QString _name, fenetreServ *_view, int _port = 0);
		virtual ~insavodServer();

		virtual void start();
		virtual void stop();
		virtual void sendImage(QString);
		
		void viewMessage(QString);
		QString parseCatalog();
	
	protected:
		QString name;
		int port;
		QHostAddress addr;
		QList<QAbstractSocket *> clientConnections;
	
	private:
		fenetreServ *view;

};

#endif
