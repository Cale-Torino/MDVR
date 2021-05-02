#ifndef INIREADER_H
#define INIREADER_H
class CIniReader
{
public:
    CIniReader(const char* szFileName);
    int ReadInteger(char* szSection, const char* szKey, int iDefaultValue);
    float ReadFloat(char* szSection, char* szKey, float fltDefaultValue);
    bool ReadBoolean(char* szSection, char* szKey, bool bolDefaultValue);
    char* ReadString(const char* szSection, const char* szKey, const char* szDefaultValue); // szDefault was orig const char*
private:
    char m_szFileName[255];
};
#endif//INIREADER_H
