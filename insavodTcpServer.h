#ifndef _INSAVODTCPSERVER_H_
#define _INSAVODTCPSERVER_H_

#include <QTcpServer>
#include <QString>

#include "insavodServer.h"

class insavodTcpServer : public QTcpServer, public insavodServer
{
	public:
		insavodTcpServer(QString, int, fenetreServ *);
		~insavodTcpServer();
};

#endif
