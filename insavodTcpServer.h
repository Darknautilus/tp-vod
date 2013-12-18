#ifndef _INSAVODTCPSERVER_H_
#define _INSAVODTCPSERVER_H_

#include <QTcpServer>
#include <QTcpSocket>

#include "insavodServer.h"

class insavodTcpServer : public QTcpServer, public insavodServer
{
	Q_OBJECT

	public:
		insavodTcpServer(QString, int, fenetreServ *);
		virtual ~insavodTcpServer();

		virtual void start();
		virtual void stop();
		void sendImage(QString);

	protected:
		virtual void incomingConnection(int);

	private:
		bool dataConnected;
		QTcpSocket *dataConnection;
		int currentImage;
		int currentFlux;
	
	public slots:
		void clientDisconnected();
		void getClientRequest();
};

#endif
