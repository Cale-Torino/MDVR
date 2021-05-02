#include "stdafx.h"
#include "IniReader.h"
#include <iostream>
#include <stdio.h>
#include <Windows.h>

CIniReader::CIniReader(const char* szFileName)
{
    memset(m_szFileName, 0x00, 255);
    memcpy(m_szFileName, szFileName, strlen(szFileName));
}
int CIniReader::ReadInteger(char* szSection, const char* szKey, int iDefaultValue)
{
    int iResult = GetPrivateProfileInt(szSection,  szKey, iDefaultValue, m_szFileName);
    return iResult;
}
float CIniReader::ReadFloat(char* szSection, char* szKey, float fltDefaultValue)
{
    char szResult[255];
    char szDefault[255];
    float fltResult;
    sprintf_s(szDefault, "%f",fltDefaultValue);
    GetPrivateProfileString(szSection,  szKey, szDefault, szResult, 255, m_szFileName);
    fltResult =  atof(szResult);
    return fltResult;
}
bool CIniReader::ReadBoolean(char* szSection, char* szKey, bool bolDefaultValue)
{
    char szResult[255];
    char szDefault[255];
    bool bolResult;
    sprintf_s(szDefault, "%s", bolDefaultValue? "True" : "False");
    GetPrivateProfileString(szSection, szKey, szDefault, szResult, 255, m_szFileName);
    bolResult =  (strcmp(szResult, "True") == 0 ||
        strcmp(szResult, "true") == 0) ? true : false;
    return bolResult;
}
char* CIniReader::ReadString(const char* szSection, const char* szKey, const char* szDefaultValue)
{
    char* szResult = new char[255];
    memset(szResult, 0x00, 255);
    GetPrivateProfileString(szSection,  szKey,
		szDefaultValue, szResult, 255, m_szFileName);
    return szResult;
}
