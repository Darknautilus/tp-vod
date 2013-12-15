#ifndef _SERVER_H_
#define _SERVER_H_

#include "insavodTcpServer.h"

class fenetreServ;

class httpServer : public insavodTcpServer
{
	Q_OBJECT

	public:
		httpServer(QString, int, fenetreServ *);
		virtual ~httpServer();

		void start();
		void stop();
		
	public slots:
		void getClientRequest();
};

#endif
