#ifndef _INSAVODUDPSERVER_H_
#define _INSAVODUDPSERVER_H_

#include <QUdpSocket>
#include <QTextStream>
#include <QObject>

#include "insavodServer.h"

class insavodUdpServer : public QObject, public insavodServer
{
	public:
		insavodUdpServer(QString, int, fenetreServ *);
		virtual ~insavodUdpServer();

		virtual void start();
		virtual void stop();
		void sendImage(QString);

	//protected:
		//virtual void incomingConnection(int);
	
	public slots:
		void clientDisconnected();
		void getClientRequest();

	private:
		QUdpSocket *socketUdpServer;
		QUdpSocket *dataConnection;
};

#endif
