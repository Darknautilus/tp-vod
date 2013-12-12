#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <iostream>

#include "fenetreServ.h"
#include "Server.h"

using namespace std;

int main(int argc, char *argv[])
{
	QApplication app(argc,argv);
	fenetreServ Serveur;

	Server *serv;
	try
	{
		serv = new Server(QString("catalogue.txt"));
	}
	catch(SERVER_ERRORS e)
	{
		cout << "Can't open catalog" << endl;
		return EXIT_FAILURE;
	}
	serv->listen(QHostAddress::Any, 8081);

  Serveur.show();

	return app.exec();
}
