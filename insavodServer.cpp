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
	viewMessage(QString::fromUtf8("démarré sur le port ")+QString::number(port));
}

void insavodServer::stop()
{
	viewMessage(QString::fromUtf8("arrêté sur le port ")+QString::number(port));
}

void insavodServer::sendImage(QString imgName)
{
	viewMessage("Envoi de "+imgName);
}

void insavodServer::viewMessage(QString message)
{
	view->printMessage(QString("[")+name+QString("] ")+message);
}
