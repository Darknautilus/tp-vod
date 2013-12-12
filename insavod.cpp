#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <iostream>

#include "fenetreServ.h"
#include "httpServer.h"

using namespace std;

int main(int argc, char *argv[])
{
	QApplication app(argc,argv);
	fenetreServ Serveur;

  Serveur.show();

	return app.exec();
}
