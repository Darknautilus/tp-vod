#ifndef _SERVER_H_
#define _SERVER_H_

#include <QTcpServer>
#include <QFile>
#include <QString>

#include "insavodServer.h"

class fenetreServ;

class httpServer : public QTcpServer, public insavodServer
{
	Q_OBJECT

	public:
		httpServer(QString, int, fenetreServ *);
		~httpServer();

		void start();
		void stop();
		
	protected:
		virtual void incomingConnection(int);

	public slots:
		void clientDisconnected();
		void getClientRequest();
};

#endif
