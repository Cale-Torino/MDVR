#ifndef INDEXFILESTRUCTURE_H
#define INDEXFILESTRUCTURE_H
#include <string>
#include <windows.h>
using namespace std;

class StoreFileIndex
{
public:
    void create_jpgfile(string& filename);
    int get_fileoffset();
    int get_filelen();
private:
    // Some chars must be converted to int
    char szDevIDNO[32];		    // device number
    char cFileType;			    // file type  0: normal 1: alarm
    char cChannle;			    // channel number start from 0
    char cEncode;				// coded format (not used)
    char cReserve;			    // Alternate field
    SYSTEMTIME FileTime;        // File time
    int nFileOffst;			    // File migration
    int nFileLen;			    // File length
    char cEndFlag[4];		    // End Flag
};
const char INDEX_END_FLAG[] = "@@@@";   // End flag

#endif // INDEXFILESTRUCTURE_H



