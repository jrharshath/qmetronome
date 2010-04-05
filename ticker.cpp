#include "ticker.h"
#include <QTextStream>

Ticker::Ticker(MetronomeConf *conf) : conf(conf) {
	this->mediaObject = new Phonon::MediaObject(this);
	this->audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
	this->path = Phonon::createPath(mediaObject, audioOutput);
}

void Ticker::tick(Ticker::TickType type) {
	static int i=0; i++;

	if( type==Ticker::HighTick )
		mediaObject->setCurrentSource( Phonon::MediaSource(this->conf->getHighFile()) );
	else
		mediaObject->setCurrentSource( Phonon::MediaSource(this->conf->getLowFile()) );
	mediaObject->play();
}
