
#include "stdafx.h"
#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <tchar.h>
#include <stdio.h>
#include "IniWriter.h"
#include "IniReader.h"
#include "SystemFunctions.h"
using namespace std;

//--------------------------------------------------------------------------------------------------//
//-----------------------------          TIME C.A Torino          ----------------------------------//
//--------------------------------------------------------------------------------------------------//
string SystemFunctions::currentDateTime() 
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "_%Y-%m-%d_%H", &tstruct);
    return buf;
}

string SystemFunctions::picfiletime()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
    return buf;
}
//--------------------------------------------------------------------------------------------------//
//-----------------------------GET PiCFILE DIRECTORY FROM INI FILE----------------------------------//
//--------------------------------------------------------------------------------------------------//

string SystemFunctions::picfiledir()
{

    char* inifile = convert_tochar_darray(inifilename());
    CIniReader iniReader(inifile);
    delete[] inifile;
    char *picfilepath_ch = iniReader.ReadString("LOCATION", "Picfiles", "");
    string picfilepath = string(picfilepath_ch);
    delete[] picfilepath_ch;

    return picfilepath + picfiletime()+"\\";

}

//--------------------------------------------------------------------------------------------------//
//------------------------------SET FILE AS COMPLETED IN INI FILE-----------------------------------//
//--------------------------------------------------------------------------------------------------//

void SystemFunctions::set_completed(const int answer, const string file)
{
    ofstream log;
    log.open("CMSv6_Picture_Extract_LOGS\\logs" + currentDateTime() + ".txt", ios::app);


    if (log.fail())
    {
        log << current_time() << "Failed to open log file. Aborting!" << endl;
        exit(1);
    }
    if ((answer == 1) || (answer == 0))
    {
        char* inifile = convert_tochar_darray(inifilename());
        char* section = convert_tochar_darray(file);
        CIniWriter iniWriter(inifile);
        delete[] inifile;
        iniWriter.WriteInteger(section, "Completed", answer);
        delete[] section;
    }
    else
    {
        log << current_time() << "Invalid input to completed function." << endl;
        exit(1);
    }
    log.close();
}

//--------------------------------------------------------------------------------------------------//
//----------------------GET THE INDEX FILE COUNTER OFFSET FROM INI FILE-----------------------------//
//--------------------------------------------------------------------------------------------------//

int SystemFunctions::get_counter(const string file)
{
    char* inifile = convert_tochar_darray(inifilename());
    CIniReader iniReader(inifile);
    delete[] inifile;
    char* section = convert_tochar_darray(file);
    int intVal = iniReader.ReadInteger(section, "Counter", 0);
    delete[] section;
    return intVal;
}

//--------------------------------------------------------------------------------------------------//
//---------------------------GET THE COMPLETED STATUS FROM INI FILE---------------------------------//
//--------------------------------------------------------------------------------------------------//

int SystemFunctions::get_completed(const string file)
{
    char* inifile = convert_tochar_darray(inifilename());
    CIniReader iniReader(inifile);
    delete[] inifile;
    char* section = convert_tochar_darray(file);
    int completed = iniReader.ReadInteger(section, "Completed", 0);
    delete[] section;
    return completed;
}

//--------------------------------------------------------------------------------------------------//
//-------------------------SET INDEX FILE COUNTER OFFSET IN INI FILE--------------------------------//
//--------------------------------------------------------------------------------------------------//

void SystemFunctions::set_counter(const int n, const string file)
{
    ofstream log;
    log.open("CMSv6_Picture_Extract_LOGS\\logs" + currentDateTime() + ".txt", ios::app);
    if (log.fail())
    {
        log << current_time() << "Failed to open log file. Aborting!" << endl;
        exit(1);
    }

    if (n >= 0)
    {
        char* inifile = convert_tochar_darray(inifilename());
        char* section = convert_tochar_darray(file);
        CIniWriter iniWriter(inifile);
        delete[] inifile;
        iniWriter.WriteInteger(section, "Counter", n);
        delete[] section;
    }
    else
    {
        log << current_time() << "Invalid input to counter function." << endl;
        exit(1);
    }
    log.close();
}

//--------------------------------------------------------------------------------------------------//
//--------------------------------GET CURDATE FOR USE IN LOGGING------------------------------------//
//--------------------------------------------------------------------------------------------------//

string SystemFunctions::current_time()
{
    ofstream log;
    log.open("CMSv6_Picture_Extract_LOGS\\logs" + currentDateTime() + ".txt", ios::app);
    if (log.fail())
    {
        log << current_time() << "Failed to open log file. Aborting!" << endl;
        exit(1);
    }

    time_t currentTime;
    struct tm *localTime;
    char Timestamp[25];
    time( &currentTime ); // Get the current time
	localTime = localtime(&currentTime);  // Convert the current time to the local time

    int dd   = localTime->tm_mday;
    int mm   = localTime->tm_mon + 1;
    int yyyy = localTime->tm_year + 1900;
    int HH   = localTime->tm_hour;
    int ii   = localTime->tm_min;
    int ss   = localTime->tm_sec;

    sprintf_s(Timestamp, "[%04d-%02d-%02d %02d:%02d:%02d] ", yyyy,mm,dd,HH,ii,ss);
    if (Timestamp != NULL)
        string str(Timestamp);
    else
    {
        cout << "Error converting Timestamp to a string. Aborting!" << endl;
        log << "Error converting Timestamp to a string. Aborting!" << endl;
        exit(1);
    }
    log.close();
    //string Timestamp = "[" + year + "-" + month + "-" + day + " " + hour + ":" + minute + ":" + second + "] ";
    return Timestamp;
}

//--------------------------------------------------------------------------------------------------//
//-------------------------------GET LAST FILENAME FROM INI FILE------------------------------------//
//--------------------------------------------------------------------------------------------------//

char* SystemFunctions::get_lastfile()
{
    char* inifile = convert_tochar_darray(inifilename());
    CIniReader iniReader(inifile);
    delete[] inifile;
    char* lastfile = iniReader.ReadString("Last File", "filename", "");
    return lastfile;
}

//--------------------------------------------------------------------------------------------------//
//---------------------------------SET THE NEW LAST FILE VALUE--------------------------------------//
//--------------------------------------------------------------------------------------------------//

void SystemFunctions::set_lastfile(const string file)
{
    ofstream log;
    log.open("CMSv6_Picture_Extract_LOGS\\logs" + currentDateTime() + ".txt", ios::app);
    if (log.fail())
    {
        log << current_time() << "Failed to open log file. Aborting!" << endl;
        exit(1);
    }
    char* filename = convert_tochar_darray(file);
    char* inifile = convert_tochar_darray(inifilename());
    CIniWriter iniWriter(inifile);
    delete[] inifile;
    iniWriter.WriteString("Last File", "filename", filename);
    delete[] filename;
    log.close();
}

//--------------------------------------------------------------------------------------------------//
//--------------------------------SET SNAPHOTS DIR FROM INI FILE------------------------------------//
//--------------------------------------------------------------------------------------------------//

string SystemFunctions::snaphotsdir()
{
    char* inifile = convert_tochar_darray(inifilename());
    CIniReader iniReader(inifile);
    delete[] inifile;
    char *snapshotpath_ch = iniReader.ReadString("LOCATION", "Snapshots", "");
    string snapshotpath = string(snapshotpath_ch);
    delete[] snapshotpath_ch;
    return snapshotpath;
}

//--------------------------------------------------------------------------------------------------//
//-----------------------------------CONVERT STRING TO CHAR*----------------------------------------//
//--------------------------------------------------------------------------------------------------//

char* SystemFunctions::convert_tochar_darray(const string filename)
{
    char* ch = new char[filename.length() + 1];
	strcpy(ch, filename.c_str());
    return ch;
}

// not working at the moment
bool SystemFunctions::isRunning(LPCSTR pName)
{
    HWND hwnd;
	hwnd = FindWindow(NULL, pName);
	if (hwnd != 0) {
        return true;
	} else {
		return false;
	}
}

/*bool IsProcessRunning(const wchar_t *processName)
{
    bool exists = false;
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (Process32First(snapshot, &entry))
        while (Process32Next(snapshot, &entry))
            if (!wcsicmp(entry.szExeFile, processName))
                exists = true;

    CloseHandle(snapshot);
    return exists;
}*/
//--------------------------------------------------------------------------------------------------//
//-------------------------------RETURN THE INI FILE FULL PATH--------------------------------------//
//--------------------------------------------------------------------------------------------------//

string SystemFunctions::inifilename()
{
    return basedir() + "\\CMSv6_Picture_Extract.ini";
}

//--------------------------------------------------------------------------------------------------//
//-----------------------------------------GET THE CWD----------------------------------------------//
//--------------------------------------------------------------------------------------------------//

string SystemFunctions::basedir()
{
    // Get the current directory and place it in the character variable szPath
    // Uses tchar.h and stdio.h
    TCHAR szPath[MAX_PATH] = _T("");
    GetCurrentDirectory(MAX_PATH, szPath);
    // Implicitly convert szPath to a string
    string base_dir = szPath;
    return base_dir;
}
