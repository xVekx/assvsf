#ifndef ASSFORMAT_H
#define ASSFORMAT_H

#include <QFile>
#include <QDebug>
#include <QStringList>
#include <QTextStream>

class AssFormat
{
public:
	AssFormat();
	bool ReadFile(QString File);
	bool WriteFile(QString File);
	void NumerText();
	QStringList AssText;
};

#endif // ASSFORMAT_H
