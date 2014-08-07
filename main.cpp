#include "assformat.h"
#include <stdio.h>

AssFormat AF;

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		qDebug()<<"Command format: assvsf in.ass out.ass";
	}

	QString InFile(argv[1]);
	QString OutFile(argv[2]);

	qDebug()<<InFile<<"->"<<OutFile;

	if(!AF.ReadFile(InFile))
	{
		qDebug()<<"Not Open In File";
		return 0;
	}

	AF.NumerText();

	AF.WriteFile(OutFile);

	return 0;
}
