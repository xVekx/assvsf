#include "assformat.h"
#include <stdio.h>

AssFormat AF;
//ffmpeg -i input.srt output.ass
int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		qDebug()<<"Command format: assvsf in.ass out.ass";
		return -1;
	}
	QString InFile(argv[1]);
	QString OutFile(argv[2]);
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
	return 0;
}
