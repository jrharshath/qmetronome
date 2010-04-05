#ifndef METRONOMECONF_H
#define METRONOMECONF_H

// to store the settings of the application

#include <QString>

class MetronomeConf
{
public:
    MetronomeConf(QString path);

    static bool isValidConfDir(QString path);

	QString getHighFile();
	QString getLowFile();
protected:
	QString highFile, lowFile;
};

#endif // METRONOMECONF_H
