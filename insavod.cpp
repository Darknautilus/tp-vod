#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
	QApplication app(argc,argv);
	
	QPushButton button("Hello World <3");
	button.show();

	return app.exec();
}
