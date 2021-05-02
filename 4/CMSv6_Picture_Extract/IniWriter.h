#ifndef INIWRITER_H
#define INIWRITER_H
class CIniWriter
{
public:
    CIniWriter(const char* szFileName);
    void WriteInteger(char* szSection, const char* szKey, int iValue);
    void WriteFloat(char* szSection, char* szKey, float fltValue);
    void WriteBoolean(char* szSection, char* szKey, bool bolValue);
    void WriteString(const char* szSection, const char* szKey, char* szValue);
private:
    char m_szFileName[255];
};
#endif //INIWRITER_H
