#ifndef _SERVER_H_
#define _SERVER_H_

#include <QTcpServer>
#include <QFile>
#include <QString>

enum SERVER_ERRORS
{
	CATALOG_NOT_FOUND
};

class Server : public QTcpServer
{
	Q_OBJECT

	public:
		Server(QString);
		~Server();
		
		void sendCatalog() const;
	
	private:
		QFile *catalog;
		QList<QTcpSocket *> clientConnections;

	protected:
		virtual void incomingConnection(int);

	public slots:
		void connectionFeedback();
		void serverMessage();
		void clientDisconnected();
		void getClientRequest();
};

#endif
