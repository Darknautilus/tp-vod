#include "insavodServer.h"

insavodServer::insavodServer(QString _name, fenetreServ *_view, int _port) : name(_name), port(_port), addr(QHostAddress::Any), view(_view)
{
}

insavodServer::~insavodServer()
{
	qDeleteAll(clientConnections);
}

void insavodServer::start()
{
	QString buffer;
	QTextStream out(&buffer, QIODevice::ReadWrite);
	out << name << " démarré sur le port " << port;
	view->printMessage(buffer);
}

void insavodServer::stop()
{
	QString buffer;
	QTextStream out(&buffer, QIODevice::ReadWrite);
	out.setAutoDetectUnicode(true);
	out << name << " arrêté sur le port " << port;
	view->printMessage(buffer);
}

