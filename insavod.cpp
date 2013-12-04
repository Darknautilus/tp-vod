#include <QApplication>
#include <QPushButton>
#include <iostream>

#include "Server.h"

int main(int argc, char *argv[])
{
	QApplication app(argc,argv);

	QPushButton button("Click to plop!");

	Server serv;
	serv.listen(QHostAddress::Any, 8081);

	QObject::connect(&button, SIGNAL(clicked()), &serv, SLOT(serverMessage()));
	button.show();

	return app.exec();
}
