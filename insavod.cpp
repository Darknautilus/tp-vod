#include "fenetreServ.h"

int main(int argc, char *argv[])
{
	QApplication app(argc,argv);
	fenetreServ Serveur;

  Serveur.show();

	return app.exec();
}
