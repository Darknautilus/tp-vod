#include "fenetreServ.h"

fenetreServ :: fenetreServ()
{
	this->resize(1000,500);
	button = new QPushButton ("Click to plop!", this);
	button->move(150,220);
	label = new QLabel("Bienvenue sur notre super Serveur de la mort qui tue", this);
	liste = new QListWidget(this);
	liste->move(0,20);

	QObject::connect(this->button, SIGNAL(clicked()), this, SLOT(ajouterListe()));
}

fenetreServ :: ~fenetreServ()
{
	
}


void fenetreServ :: ajouterListe() 
{
	new QListWidgetItem(tr("Nouvelle connexion"), liste);
}


