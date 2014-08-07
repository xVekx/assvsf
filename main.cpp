#include "assformat.h"
#include <stdio.h>

AssFormat AF;
//ffmpeg -i input.srt output.ass
int main(int argc, char *argv[])
{
	if(argc != 4)
	{
		qDebug()<<"Command format: assvsf fun in out";
		qDebug()<<"srt2ass";
		qDebug()<<"assnum";
		return -1;
	}

	QString InFile(argv[2]);
	QString OutFile(argv[3]);

	if(QString(argv[1]) ==  QString("assnum"))
	{
		qDebug()<<InFile<<"->"<<OutFile;
		if(!AF.ReadFile(InFile))
		{
			qDebug()<<"Not Open In File";
			return -1;
		}
		AF.NumerText();
		if(!AF.WriteFile(OutFile))
		{
			qDebug()<<"Not Save Out File";
			return -1;
		}
	}

	else if( QString(argv[1]) ==  QString("srt2ass"))
	{
		qDebug()<<InFile<<"->"<<OutFile;
		if(!AF.ReadSrtFile(InFile))
		{
			qDebug()<<"Not Open In File";
			return -1;
		}
		if(!AF.WriteFile(OutFile))
		{
			qDebug()<<"Not Save Out File";
			return -1;
		}
	}
}
