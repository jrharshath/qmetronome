#ifndef METRONOMEWINDOW_H
#define METRONOMEWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QList>
#include <QCheckBox>

#include "ui_MetronomeWindow.h"
#include "metronomeconf.h"
#include "ticker.h"

class MetronomeWindow : public QMainWindow, public Ui::MetronomeWindow
{
    Q_OBJECT
public:
    MetronomeWindow(MetronomeConf* conf);

    int getBPM();
    int getNumAccents();

protected slots:
    void setBPM();
	void setAccents(int numAccents);

	void startStopTicking();
	void doTick();

	// todo: find a better way to do this
	void bpmPreset60();
	void bpmPreset70();
	void bpmPreset80();
	void bpmPreset90();
	void bpmPreset100();
	void bpmPreset110();
	void bpmPreset120();

	void showAboutBox();

protected:
	void setTimerInterval();

	QTimer *timer;
    MetronomeConf* conf;
	Ticker *ticker;

	QList<QCheckBox*> accentChecks;
	int tickIndex;
};

#endif // METRONOMEWINDOW_H
