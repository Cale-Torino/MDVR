#include "stdafx.h"
#include "IniWriter.h"
#include <iostream>
#include <stdio.h>
#include <Windows.h>
CIniWriter::CIniWriter(const char* szFileName)
{
    memset(m_szFileName, 0x00, 255);
    memcpy(m_szFileName, szFileName, strlen(szFileName));
}
void CIniWriter::WriteInteger(char* szSection, const char* szKey, int iValue)
{
    char szValue[255];
	sprintf_s(szValue, "%d", iValue);
    WritePrivateProfileString(szSection,  szKey, szValue, m_szFileName);
}
void CIniWriter::WriteFloat(char* szSection, char* szKey, float fltValue)
{
    char szValue[255];
    sprintf_s(szValue, "%f", fltValue);
    WritePrivateProfileString(szSection,  szKey, szValue, m_szFileName);
}
void CIniWriter::WriteBoolean(char* szSection, char* szKey, bool bolValue)
{
    char szValue[255];
    sprintf_s(szValue, "%s", bolValue ? "True" : "False");
    WritePrivateProfileString(szSection,  szKey, szValue, m_szFileName);
}
void CIniWriter::WriteString(const char* szSection, const char* szKey, char* szValue)
{
    WritePrivateProfileString(szSection,  szKey, szValue, m_szFileName);
}
