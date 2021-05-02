#ifndef SYSTEMFUNCTIONS_H
#define SYSTEMFUNCTIONS_H
#include <string>
#include <windows.h>
using namespace std;

class SystemFunctions
{
public:
    string snaphotsdir();
    // Get current time for log file
    string current_time();
    string currentDateTime();
    string picfiletime();
    void set_completed(const int answer, const string file);
    int get_counter(const string file);
    int get_completed(const string file);
    void set_counter(const int n, const string file);
    char* get_lastfile();
    void set_lastfile(const string file);
    string picfiledir();
    bool isRunning(LPCSTR pName);
    //bool IsProcessRunning(const wchar_t *processName);
private:
    char* convert_tochar_darray(const string filename);
    string inifilename();
    string basedir();
};

#endif // SYSTEMFUNCTIONS_H
