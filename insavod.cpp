#include <QApplication>
#include <QPushButton>
#include <iostream>

#include "Server.h"

using namespace std;

int main(int argc, char *argv[])
{
	QApplication app(argc,argv);

	QPushButton button("Click to plop!");

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

	QObject::connect(&button, SIGNAL(clicked()), serv, SLOT(serverMessage()));
	button.show();

	return app.exec();
}
