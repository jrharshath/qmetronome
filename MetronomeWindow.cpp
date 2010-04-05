#include "MetronomeWindow.h"
#include <QHBoxLayout>
#include <QApplication>
#include <QMessageBox>

MetronomeWindow::MetronomeWindow(MetronomeConf* conf)
{
	setupUi(this);

	this->statusBar()->showMessage("Stopped");

	timer = new QTimer(this);
	this->setTimerInterval();

	this->conf = conf;
	ticker = new Ticker( this->conf );

	this->tickIndex = 0;
	this->setAccents( this->accentsBox->value() );

	connect( this->timer, SIGNAL(timeout()), this, SLOT(doTick()) );
	connect( this->startStopTickingButton, SIGNAL(clicked()), this, SLOT(startStopTicking()) );
	connect( this->setBpmButton, SIGNAL(clicked()), this, SLOT(setBPM()) );
	connect( this->accentsBox, SIGNAL(valueChanged(int)), this, SLOT(setAccents(int)) );
	connect( this->quitAction, SIGNAL(triggered()), qApp, SLOT(quit()) );
	connect( this->aboutAction, SIGNAL(triggered()), this, SLOT(showAboutBox()) );

	connect( this->bpm60, SIGNAL(clicked()), this, SLOT(bpmPreset60()) );
	connect( this->bpm70, SIGNAL(clicked()), this, SLOT(bpmPreset70()) );
	connect( this->bpm80, SIGNAL(clicked()), this, SLOT(bpmPreset80()) );
	connect( this->bpm90, SIGNAL(clicked()), this, SLOT(bpmPreset90()) );
	connect( this->bpm100, SIGNAL(clicked()), this, SLOT(bpmPreset100()) );
	connect( this->bpm110, SIGNAL(clicked()), this, SLOT(bpmPreset110()) );
	connect( this->bpm120, SIGNAL(clicked()), this, SLOT(bpmPreset120()) );
}

int MetronomeWindow::getBPM() {
	return bpmBox->value();
}

void MetronomeWindow::setBPM() {
	if( this->timer->isActive() )
		this->statusBar()->showMessage("Ticking at "+QString::number(getBPM())+ " BPM");
	else
		this->statusBar()->showMessage("Ticking rate set to "+QString::number(getBPM())+ " BPM");

	this->setTimerInterval();
}

void MetronomeWindow::setAccents(int numAccents) {
	static int prevNum = 0;
	numAccents = this->accentsBox->value();
	QHBoxLayout *cont = this->accentContainer;

	if( prevNum==0 ) {
		prevNum = numAccents;
		for( int i=0; i<prevNum; i++ ) {
			QCheckBox* box = new QCheckBox( QString::number(i+1), this );
			cont->addWidget(box);
			this->accentChecks.append(box);
		}
	} else if( numAccents > prevNum ) {
		for( int i=prevNum; i<numAccents; i++ ) {
			QCheckBox* box = new QCheckBox( QString::number(i+1), this );
			cont->addWidget(box);
			this->accentChecks.append(box);
		}
		prevNum = numAccents;
	} else if( numAccents < prevNum ) {
		for( int i=prevNum; i>numAccents; i-- ) {
			QCheckBox* box = this->accentChecks.at(i-1);
			this->accentChecks.removeAt(i-1);
			cont->removeWidget(box);
			delete box;
		}
		prevNum = numAccents;
	}
}

void MetronomeWindow::startStopTicking() {
	this->setTimerInterval();

	if( this->timer->isActive() ) {
		this->timer->stop();
		this->statusBar()->showMessage("Stopped");
	} else {
		this->doTick();
		this->timer->start();
		this->statusBar()->showMessage("Ticking at "+QString::number(getBPM())+ " BPM");
	}
}

void MetronomeWindow::setTimerInterval() {
	float interval = 1000.0 * 60.0 / float(getBPM());
	this->timer->setInterval(interval);
}

void MetronomeWindow::doTick() {
	if( this->tickIndex >= this->accentChecks.size() ) this->tickIndex = 0;
	QCheckBox *box = this->accentChecks.at(this->tickIndex);
	if( box->isChecked() )
		this->ticker->tick(Ticker::HighTick);
	else
		this->ticker->tick(Ticker::LowTick);
	int size = this->accentChecks.size();
	for( int i=0; i<size; i++ ) {
		QCheckBox *temp = this->accentChecks.at(i);
		QFont font(temp->font());
		font.setBold(false);
		temp->setFont( font );
	}
	QFont font(box->font());
	font.setBold(true);
	box->setFont( font );

	this->tickIndex++;
}

void MetronomeWindow::showAboutBox() {
	QMessageBox::about(this, "About QMetronome", "A free metronome.\nharshath.jr@gmail.com");
}

void MetronomeWindow::bpmPreset60() {
	this->bpmBox->setValue(60);
	this->setBpmButton->click();
}
void MetronomeWindow::bpmPreset70() {
	this->bpmBox->setValue(70);
	this->setBpmButton->click();
}
void MetronomeWindow::bpmPreset80() {
	this->bpmBox->setValue(80);
	this->setBpmButton->click();
}
void MetronomeWindow::bpmPreset90() {
	this->bpmBox->setValue(90);
	this->setBpmButton->click();
}
void MetronomeWindow::bpmPreset100() {
	this->bpmBox->setValue(100);
	this->setBpmButton->click();
}
void MetronomeWindow::bpmPreset110() {
	this->bpmBox->setValue(110);
	this->setBpmButton->click();
}
void MetronomeWindow::bpmPreset120() {
	this->bpmBox->setValue(120);
	this->setBpmButton->click();
}
