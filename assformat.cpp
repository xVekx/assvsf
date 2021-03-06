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
	AssFile.remove();
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
			SectionEvents = false;
		}
		//Ищем секцию Events
		if(AssText.at(i).indexOf(QRegExp("^\\[Events\\]")) > -1)
		{
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
					if( temp == -1)
					{
						break;
					}
				}
				qDebug()<<"Virgule"<<Virgule;
			}
			if(AssText.at(i).indexOf(QRegExp("^Dialogue:")) > -1)
			{
				int Offset = 0;
				for(int v=0;v<Virgule;v++)
				{
					Offset = AssText.at(i).indexOf(",",Offset+1);
				}
				QString TextNumStr = AssText.at(i).mid(0,Offset+1) + QString("%1").arg(NumStr);
				NumStr++;
				AssText.replace(i,TextNumStr);
			}
		}
	}
}

bool AssFormat::ReadSrtFile(QString File)
{
	QFile AssFile;
	AssFile.setFileName(File);
	if(!AssFile.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		return false;
	}
	QStringList SrtText;
	QTextStream TextStream(&AssFile);
	while (!TextStream.atEnd())
	{
		SrtText << TextStream.readLine();
	}
	AssFile.close();

	AssText<<QString("[Script Info]");
	AssText<<QString("; Script generated by ASSVSF");
	AssText<<QString("Title: Default ASSVSF file");
	AssText<<QString("ScriptType: v4.00+");
	AssText<<QString("WrapStyle: 0");
	AssText<<QString("ScaledBorderAndShadow: yes");
	AssText<<QString("Original Timing: xVekx");
	AssText<<QString("YCbCr Matrix: None\n");

	AssText<<QString("[V4+ Styles]");
	AssText<<QString("Format: Name, Fontname, Fontsize, PrimaryColour, SecondaryColour, OutlineColour, BackColour, Bold, Italic, Underline, StrikeOut, ScaleX, ScaleY, Spacing, Angle, BorderStyle, Outline, Shadow, Alignment, MarginL, MarginR, MarginV, Encoding");
	AssText<<QString("Style: Default,Arial,20,&H0002F8EA,&H000000FF,&H00000000,&H00000000,0,0,0,0,100,100,0,0,1,2,2,2,10,10,10,1\n");

	AssText<<QString("[Events]");
	AssText<<QString("Format: Layer, Start, End, Style, Name, MarginL, MarginR, MarginV, Effect, Text");

	bool StrDetect = false;
	QString AssStr;

	for(int i=0;i<SrtText.size();i++)
	{
		if(StrDetect)
		{
			int off=0;
			while(1)
			{
				if(i+off > SrtText.size() - 1)
				{
					break;
				}
				if(SrtText.at(i+off).indexOf(QRegExp("-->")) > -1)
				{
					break;
				}
				off++;
			}
			for(int a=0;a<off-1;a++)
			{
				if(SrtText.at(i+a).size() != 0)
				{
					AssStr += SrtText.at(i+a);
				}
				if(a < off-2 && SrtText.at(i+a+1).size() != 0)
				{
					AssStr += QString(" ");
				}
			}
			StrDetect = false;
			AssText << AssStr;
		}
		int OffsetStr = SrtText.at(i).indexOf(QRegExp("-->"));
		if(OffsetStr > -1 && !StrDetect)
		{
			StrDetect = true;
			int offb = 0;
			int offe = 0;
			offb = SrtText.at(i).indexOf(QRegExp("\\d\\d:\\d\\d:\\d\\d,\\d\\d\\d"));
			offe = SrtText.at(i).indexOf(QRegExp("\\s"));
			QTime BeginStr = QTime::fromString(SrtText.at(i).mid(offb,offe), "hh:mm:ss,zzz");
			offb = SrtText.at(i).indexOf(QRegExp("\\d\\d:\\d\\d:\\d\\d,\\d\\d\\d"),OffsetStr);
			offe = SrtText.at(i).indexOf(QRegExp("$"),OffsetStr);
			QTime EndStr = QTime::fromString(SrtText.at(i).mid(offb,offe), "hh:mm:ss,zzz");
			AssStr = QString("Dialogue: 0,");
			AssStr += BeginStr.toString("h:mm:ss.zzz,");
			AssStr += EndStr.toString("h:mm:ss.zzz,");
			AssStr += QString("Default,,0,0,0,,");
		}
	}
	return true;
}


