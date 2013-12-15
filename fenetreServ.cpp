#include "fenetreServ.h"
#include "httpServer.h"

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

