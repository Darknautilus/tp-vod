#include "fenetreServ.h"
#include "httpServer.h"
#include "insavodUdpServer.h"

fenetreServ::fenetreServ()
{
	this->resize(800,400);
	label = new QLabel("<font color=\"#0000A0\">Bienvenue sur le serveur du binome B3208</font>", this);
	//label->move(400,0);
	liste = new QListWidget(this);
	//liste->move(0,20);
	liste->resize(800,300);
	
	//Création du layout et arrangement des widgets
	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(label);
	layout->addWidget(liste);

	//Affectation du Layout à la fenêtre
	this->setLayout(layout);
	
	this->setStyleSheet("Background-color:skyblue");
liste->setStyleSheet("Background-color:lightblue");
	
	//Démarrage des différents serveurs
	servers.append(new httpServer(QString("HTTP-Server"), 8081, this));
	servers.append(new insavodTcpServer(QString("TCP-Server"), 8082, this));
	servers.append(new insavodUdpServer(QString("UDP-Server"), 8083, this));
	for(int i=0; i<servers.size(); i++)
	{
		servers[i]->start();
	}
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
