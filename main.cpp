#include <QApplication>
#include <QDir>
#include <QTextStream>

#include "MetronomeWindow.h"
#include "metronomeconf.h"

QString appPath;
QString dataPath;

QTextStream err(stderr);

int main(int argc, char **argv)
{
    QApplication app(argc,argv);
	app.setApplicationName("QMetronome");
	QString path1 = QDir::homePath()+"/.qmetronome";
	QString path2 = app.applicationDirPath()+"/conf";

    MetronomeConf* conf = 0;

    if( MetronomeConf::isValidConfDir(path1) ) {
        conf = new MetronomeConf(path1);
    } else if( MetronomeConf::isValidConfDir(path2) ) {
		conf = new MetronomeConf(path2);
    } else {
        err << "Application data does not exist! Exiting..";
        return -1;
    }

    MetronomeWindow *w = new MetronomeWindow(conf);
    w->show();
    return app.exec();
}
