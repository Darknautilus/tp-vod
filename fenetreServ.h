#ifndef _FENETRE_SERV
#define _FENETRE_SERV

#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QListWidgetItem>

class insavodServer;

class fenetreServ : public QWidget
{
	Q_OBJECT

	public:
		fenetreServ();
		virtual ~fenetreServ();

		void printMessage(QString);
		QString getAppDirPath();

	private slots:
		void button_clicked();

	private:
		QListWidget *liste;
		QPushButton *button;
		QLabel *label;

		QList<insavodServer*> servers;
};

	
#endif
