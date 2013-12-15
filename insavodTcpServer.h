#ifndef _INSAVODTCPSERVER_H_
#define _INSAVODTCPSERVER_H_

#include <QTcpServer>

#include "insavodServer.h"

class insavodTcpServer : public QTcpServer, public insavodServer
{
	public:
		insavodTcpServer(QString, int, fenetreServ *);
		virtual ~insavodTcpServer();

		void start();
		void stop();
		void sendImage(QString);

	protected:
		virtual void incomingConnection(int);
	
	public slots:
		void clientDisconnected();
		void getClientRequest();
};

#endif
