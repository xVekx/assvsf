#ifndef ASSFORMAT_H
#define ASSFORMAT_H

#include <QFile>
#include <QDebug>
#include <QStringList>
#include <QTextStream>
#include <QTime>

class AssFormat
{
public:
	AssFormat();
	bool ReadFile(QString File);
	bool WriteFile(QString File);
	void NumerText();
	QStringList AssText;
	bool ReadSrtFile(QString File);
	QTime TimeSRT(QString str, int offset);
};

#endif // ASSFORMAT_H
