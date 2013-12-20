#ifndef _FENETRE_SERV
#define _FENETRE_SERV

#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>
#include <QVBoxLayout>

class insavodServer;

class fenetreServ : public QWidget
{
	Q_OBJECT

	public:
		fenetreServ();
		virtual ~fenetreServ();

		void printMessage(QString);
		QString getAppDirPath();

	private:
		QListWidget *liste;
		QLabel *label;

		QList<insavodServer*> servers;
};

	
#endif
