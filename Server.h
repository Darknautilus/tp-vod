#ifndef _SERVER_H_
#define _SERVER_H_

#include <QTcpServer>

class Server : public QTcpServer
{
	Q_OBJECT

	public:
		Server();
		~Server();

	public slots:
		void clientWelcomeMessage();
		void connectionFeedback();
		void serverMessage();
	//	void remplirListe(QListWidget *list);	
};

#endif
