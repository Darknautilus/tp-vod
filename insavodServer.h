#ifndef _INSAVODSERVER_H_
#define _INSAVODSERVER_H_

#include <QString>
#include <QHostAddress>

#include "fenetreServ.h"

class insavodServer
{
	enum protocol
	{
		TCP_PULL,
		TCP_PUSH,
		UDP_PULL,
		UDP_PUSH,
		MCAST_PUSH
	};

	public:
		insavodServer(QString _name, fenetreServ *_view, int _port = 0);
		virtual ~insavodServer();

		virtual void start();
		virtual void stop();

		void viewMessage(QString);

	protected:
		QString name;
		int port;
		QHostAddress addr;
		QList<QAbstractSocket *> clientConnections;
	
	private:
		fenetreServ *view;

};

#endif
