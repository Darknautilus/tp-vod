#ifndef _INSAVODSERVER_H_
#define _INSAVODSERVER_H_

#include <QString>
#include <QHostAddress>

#include "fenetreServ.h"

class insavodServer
{
	public:
		insavodServer(QString _name, fenetreServ *_view, int _port = 0);
		virtual ~insavodServer();

		virtual void start();
		virtual void stop();
		virtual void sendImage(QString);
		
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
