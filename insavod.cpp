#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <iostream>

#include "fenetreServ.h"
#include "Server.h"

int main(int argc, char *argv[])
{
	QApplication app(argc,argv);
	fenetreServ Serveur;

	Server serv;
	serv.listen(QHostAddress::Any, 8081);

  Serveur.show();


	return app.exec();
}
