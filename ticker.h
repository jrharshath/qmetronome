#ifndef TICKER_H
#define TICKER_H

// The class that will make a tick sound.

#include <QObject>
#include <QString>
#include "metronomeconf.h"

#include <Phonon/MediaObject>
#include <Phonon/AudioOutput>

class Ticker : public QObject
{
	Q_OBJECT
public:
	enum TickType { HighTick, LowTick };

	Ticker(MetronomeConf *conf);

public slots:
	void tick(Ticker::TickType type);

protected:
	MetronomeConf *conf;
	Phonon::MediaObject *mediaObject;
	Phonon::AudioOutput *audioOutput;
	Phonon::Path path;
};

#endif // TICKER_H
