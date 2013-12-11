#ifndef _FENETRE_SERV
#define _FENETRE_SERV

#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QListWidgetItem>

class fenetreServ : public QWidget
{
	Q_OBJECT

	public:
		fenetreServ();
		virtual ~fenetreServ();
		//void remplirListe();

	public slots: 
		void ajouterListe();

	private:
		QListWidget *liste;
		QPushButton *button;
		QLabel *label;
};

	
#endif
