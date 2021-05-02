#include "stdafx.h"
#include <string>
#include <sstream>
#include <windows.h>
#include <stdio.h>
#include "IndexFileStructure.h"
#include "ExtractFile.h"
#include "SystemFunctions.h"
using namespace std;

void StoreFileIndex::create_jpgfile(string& filename)
{
    // place SystemTime variables into local variables
    int yyyy, mm, dd, hh, ii, ss;
    yyyy = FileTime.wYear;
    mm   = FileTime.wMonth;
    dd   = FileTime.wDay;
    hh   = FileTime.wHour;
    ii   = FileTime.wMinute;
    ss   = FileTime.wSecond;
    char jpg_date[18], dir_date[11], year[5], month[3], day[3];
    SystemFunctions Sys;

    sprintf_s(jpg_date, "%04d%02d%02d_%02d%02d%02d", yyyy, mm, dd, hh, ii, ss);
    sprintf_s(dir_date, "%04d-%02d-%02d", yyyy, mm, dd);
    sprintf_s(year, "%04d", yyyy);
    sprintf_s(month, "%02d", mm);
    sprintf_s(day, "%02d", dd);

    // Implicitly convert the char variables to strings
    string dev_id_str = szDevIDNO;
    int channel_int = cChannle;
    ostringstream channel_ss;
    channel_ss << channel_int + 1;

    string channel_str = channel_ss.str();

    // create necessary folders
    // CreateDirectory only works for a single
    // directory unfortunately
    string newfolder1 = Sys.snaphotsdir();
    CreateDirectory(newfolder1.c_str(), NULL);
    string newfolder2 = newfolder1 + dev_id_str + "\\";
    CreateDirectory(newfolder2.c_str(), NULL);
    //string newfolder3 = newfolder2 + year + "\\";
    //CreateDirectory(newfolder3.c_str(), NULL);
    //string newfolder4 = newfolder3 + month + "\\";
    //CreateDirectory(newfolder4.c_str(), NULL);
    //string newfolder5 = newfolder4 + day + "\\";
    //CreateDirectory(newfolder5.c_str(), NULL);
    //string newfolder6 = newfolder5 + "CH" + channel_str + "\\";
    //CreateDirectory(newfolder6.c_str(), NULL);

    // Maybe make string a cstring?
    filename = newfolder2 + dev_id_str + "_" + jpg_date + "_N" + channel_str + "0.jpg";
}

int StoreFileIndex::get_fileoffset()
{
    return nFileOffst;
}

int StoreFileIndex::get_filelen()
{
    return nFileLen;
}
