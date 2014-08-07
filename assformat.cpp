#include "assformat.h"

AssFormat::AssFormat()
{

}

bool AssFormat::ReadFile(QString File)
{
	QFile AssFile;
	AssFile.setFileName(File);
	if(!AssFile.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		return false;
	}

	QTextStream TextStream(&AssFile);
	while (!TextStream.atEnd())
	{
		AssText << TextStream.readLine();
	}

	AssFile.close();
	return true;
}

bool AssFormat::WriteFile(QString File)
{
	QFile AssFile;
	AssFile.setFileName(File);
	if(!AssFile.open(QIODevice::ReadWrite | QIODevice::Text))
	{
		return false;
	}

	QTextStream TextStream(&AssFile);

	for(int i=0; i<AssText.size(); i++)
	{
		TextStream << AssText.at(i)<<endl;
	}

	AssFile.close();
	return true;
}

void AssFormat::NumerText()
{
	bool SectionEvents = false;
	int Virgule = 0;
	int NumStr = 1;

	for(int i=0;i<AssText.size();i++)
	{
		if(AssText.at(i).indexOf(QRegExp("^\\[")) > -1)
		{
			qDebug()<<AssText.at(i);
			SectionEvents = false;
		}

		//Ищем секцию Events
		if(AssText.at(i).indexOf(QRegExp("^\\[Events\\]")) > -1)
		{
			qDebug()<<AssText.at(i);
			SectionEvents = true;
		}

		if(SectionEvents)
		{
			//Находим количество запятых

			if(AssText.at(i).indexOf(QRegExp("^Format:")) > -1)
			{
				int temp = 0;
				for(Virgule=0;Virgule<20;Virgule++)
				{
					temp = AssText.at(i).indexOf(",",temp+1);
					//qDebug()<<temp;
					if( temp == -1)
					{
						break;
					}
				}
				qDebug()<<Virgule;
			}
			if(AssText.at(i).indexOf(QRegExp("^Dialogue:")) > -1)
			{
				//qDebug()<<AssText.at(i);
				int Offset = 0;
				for(int v=0;v<Virgule;v++)
				{
					Offset = AssText.at(i).indexOf(",",Offset+1);
					//qDebug()<<temp;
				}
				//qDebug()<<Offset;

				//qDebug()<<AssText.at(i).mid(0,Offset+1);

				QString TextNumStr = AssText.at(i).mid(0,Offset+1) + QString("%1").arg(NumStr);

				qDebug()<<TextNumStr;

				NumStr++;

				AssText.replace(i,TextNumStr);

			//qDebug()<<AssText.at(i).indexOf(QRegExp(","));
			}
		}
	}
}


