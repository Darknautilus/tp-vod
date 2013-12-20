#include "fenetreServ.h"
#include "httpServer.h"
#include "insavodUdpServer.h"

fenetreServ::fenetreServ()
{
	this->resize(800,400);
	button = new QPushButton ("Click to plop!", this);
	button->move(400,320);
	label = new QLabel("Bienvenue sur notre super Serveur de la mort qui tue", this);
	label->move(400,0);
	liste = new QListWidget(this);
	liste->move(0,20);
	liste->resize(800,300);
	
	//Démarrage des différents serveurs
	servers.append(new httpServer(QString("HTTP-Server"), 8081, this));
	servers.append(new insavodTcpServer(QString("TCP-Server"), 8082, this));
	servers.append(new insavodUdpServer(QString("UDP-Server"), 8083, this));
	for(int i=0; i<servers.size(); i++)
	{
		servers[i]->start();
	}

	// click to plop !
	QObject::connect(this->button, SIGNAL(clicked()), this, SLOT(button_clicked()));
}

fenetreServ::~fenetreServ()
{
	servers.clear();
}

QString fenetreServ::getAppDirPath()
{
	return QCoreApplication::applicationDirPath(); 
}

void fenetreServ::printMessage(QString message)
{
	new QListWidgetItem(message, liste);
}

void fenetreServ::button_clicked()
{
	printMessage(QString("plop"));
}

