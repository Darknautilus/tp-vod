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
	
	httpserv = new httpServer(QString("HTTP-Server"), 8081, this);
	httpserv->start();
	
	QObject::connect(this->button, SIGNAL(clicked()), this, SLOT(button_clicked()));
}

fenetreServ::~fenetreServ()
{
	delete httpserv;
}

void fenetreServ::printMessage(QString message)
{
	new QListWidgetItem(message, liste);
}

void fenetreServ::button_clicked()
{
	printMessage(QString("plop"));
}

void fenetreServ::newConnection() 
{
	new QListWidgetItem(tr("Nouvelle connexion"), liste);
}


