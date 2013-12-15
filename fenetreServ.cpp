#include "fenetreServ.h"
#include "httpServer.h"

fenetreServ::fenetreServ()
{
	this->resize(1000,500);
	button = new QPushButton ("Click to plop!", this);
	button->move(150,220);
	label = new QLabel("Bienvenue sur notre super Serveur de la mort qui tue", this);
	liste = new QListWidget(this);
	liste->move(0,20);
	
	servers.append(new httpServer(QString("HTTP-Server"), 8081, this));
	servers.append(new insavodTcpServer(QString("TCP-Server"), 8082, this));
	for(int i=0; i<servers.size(); i++)
	{
		servers[i]->start();
	}
	
	QObject::connect(this->button, SIGNAL(clicked()), this, SLOT(button_clicked()));
}

fenetreServ::~fenetreServ()
{
	servers.clear();
}

void fenetreServ::printMessage(QString message)
{
	new QListWidgetItem(message, liste);
}

void fenetreServ::button_clicked()
{
	printMessage(QString("plop"));
}

