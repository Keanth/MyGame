#include "stdafx.h"
#include "IOManager.h"
#include <fstream>
#include "Hero.h"

int IOManager::AppendToFileBegin(std::string fileName)
{
	std::ofstream log(fileName, std::ios::app);
	if (log.fail())
	{
		return 1;
	}

	SYSTEMTIME time;
	GetLocalTime(&time);

	log << "<Session>" << std::endl;
	log << "\t" << "<Start>" << std::endl;
	log << "\t\t" << "<Date>" << " " << time.wYear << " : " << time.wMonth << " : " << time.wDay << " " << "</Date>" << std::endl;
	log << "\t\t" << "<Time>" << " " << time.wHour << " : " << time.wMinute << " : " << time.wSecond << " " << "</Time>" << std::endl;
	log << "\t\t" << "<PlayerHealth>" << " " <<  Hero::m_health << " HP " << "</PlayerHealth>" << std::endl;
	log << "\t\t" << "<Info2>" << " ... " << "</Info2>" << std::endl;
	log << "\t" << "</Start>" << std::endl;
	
	return 0;
}

int IOManager::AppendToFileEnd(std::string fileName)
{
	std::ofstream log(fileName, std::ios::app);
	if (log.fail())
	{
		return 1;
	}

	SYSTEMTIME time;
	GetLocalTime(&time);

	log << "\t" << "<End>" << std::endl;
	log << "\t\t" << "<Date>" << " " << time.wYear << " : " << time.wMonth << " : " << time.wDay << " " << "</Date>" << std::endl;
	log << "\t\t" << "<Time>" << " " << time.wHour << " : " << time.wMinute << " : " << time.wSecond << " " << "</Time>" << std::endl;
	log << "\t\t" << "<PlayerHealth>" << " " << Hero::m_health << " HP " << "</PlayerHealth>" << std::endl;
	log << "\t\t" << "<Info2>" << " ... " << "</Info2>" << std::endl;
	log << "\t" << "</End>" << std::endl;
	log << "</Session>" << std::endl;

	return 0;
}

//************** TEMPLATE **************
////Name, first name – prog2 group	/**/
//<ClassName						/**/
//TABNameProp1 = ”valueProp1”		/**/
//TABNameProp2 = ”valueProp2”		/**/
//TABNameProp3 = ”valueProp3”		/**/
//	/ >								/**/
//************** TEMPLATE **************

//************** TEMPLATE **************
//<Session>							/**/
//TAB<Start>						/**/
//TABTAB<Date>yyyy:mm : dd< / Date>	/**/
//TABTAB<Time>hh : mm : ss< / Time>	/**/
//TABTAB<Info1>…< / Info1>			/**/
//TABTAB<Info2>…< / Info2>			/**/
//TABTAB…							/**/
//TAB< / Start>						/**/
//TAB<End>							/**/
//TABTAB<Date>yyyy:mm : dd< / Date>	/**/
//TABTAB<Time>hh : mm : ss< / Time>	/**/
//TABTAB<Info1>…< / Info1>			/**/
//TABTAB<Info2>…< / Info2>			/**/
//TABTAB…							/**/
//TAB< / End>						/**/
//< / Session>						/**/
//************** TEMPLATE **************