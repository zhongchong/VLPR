#include "vlpr.h"
#include <QtGui/QApplication>
#include<QTextCodec>
#include <QSplashScreen>
#include <QElapsedTimer>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	//启动动画
	QPixmap pixmap("./Resources/splash.png");
	QSplashScreen *splash = new QSplashScreen(pixmap);
	splash->show();
	QElapsedTimer t;
	t.start();
	while(t.elapsed()<1000)
	{
		QCoreApplication::processEvents();
	}

	//中文处理
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
	QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
	QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());

	a.setWindowIcon(QIcon("./Resources/qt.ico"));

	VLPR w;
	w.show();
	splash->finish(&w);
	delete splash;
	return a.exec();
}
