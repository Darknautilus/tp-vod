#include <iostream>
#include <QTcpSocket>


#include "Server.h"


Server::Server()
{
	QObject::connect(this, SIGNAL(newConnection()), this, SLOT(connectionFeedback()));
	QObject::connect(this, SIGNAL(newConnection()), this, SLOT(clientWelcomeMessage()));
}

Server::~Server()
{
}

void Server::connectionFeedback()
{
	std::cout << "Nouvelle connexion !" << std::endl;
}

void Server::serverMessage()
{
	std::cout << "plop" << std::endl;
}

void Server::clientWelcomeMessage()
{
	QTcpSocket *client = nextPendingConnection();
	client->write("Bienvenue !\n");
}
