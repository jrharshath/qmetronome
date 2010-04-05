#include "metronomeconf.h"
#include <QDir>

MetronomeConf::MetronomeConf(QString path) {
    if( MetronomeConf::isValidConfDir(path) ) {
		this->highFile = path + "/high.mp3";
		this->lowFile = path + "/low.mp3";
	}
}

QString MetronomeConf::getHighFile() {
	return this->highFile;
}

QString MetronomeConf::getLowFile() {
	return this->lowFile;
}

bool MetronomeConf::isValidConfDir(QString path) {
    QDir dir(path);
	QFile high( path + "/high.mp3");
	QFile low( path + "/low.mp3");
	if( dir.exists() && high.exists() && low.exists() )
		return true;

    return false;
}
