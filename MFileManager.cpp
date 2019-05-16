//---------------------------------------------------------------------------

#include <vcl.h>

#pragma hdrstop

#include "MFileManager.h"


//---------------------------------------------------------------------------

#pragma package(smart_init)

#include <assert.h>

//---------------------------------------------------------------------------
void __fastcall DeleteLastSlash(AnsiString &sMsg)
{
    //sMsg = ExcludeTrailingBackslash(sMsg);

    if(sMsg.Length() == 0) return;

    while(sMsg.SubString(sMsg.Length(), 1) == "\\") {
        sMsg.Delete(sMsg.Length(), 1);
    }
}

int __fastcall DivideByIndicator(AnsiString sSrc, TStringList * sList, char cIndicator)
{
    int nDivideCnt; // Divide Count
    int nSrcLen;    // Source String Lenght
    int nTmpCnt;
    char temp[500];

    AnsiString sBuf;

    if(sList == NULL) return 0;
    else if(sSrc == "") return 0;

    memset(temp, '\0', sizeof(temp));

    nSrcLen = sSrc.Length();

    nTmpCnt = 0;
    nDivideCnt = 0;
    for(int i=0; i<nSrcLen; i++){
        if(sSrc.c_str()[i] == cIndicator){
            nTmpCnt = 0;
            sBuf = temp;
            sBuf = sBuf.Trim();
            sList->Add(sBuf);
            memset(temp, '\0', sizeof(temp));
            nDivideCnt++;
            sBuf = "";
        }
        else{
            temp[nTmpCnt] = sSrc.c_str()[i];
            nTmpCnt++;

            if((i+1) == nSrcLen) {
                sBuf = temp;
                sBuf = sBuf.Trim();
                sList->Add(sBuf);
                nDivideCnt++;
                sBuf = "";
                break;
            }
        }
    }

    return nDivideCnt;
}

//---------------------------------------------------------------------------
MFileManager::MFileManager()
{
    InitializeCriticalSection(&m_Sync);
    m_pSectionList  = new TStringList;
    m_pKeyList      = new TStringList;
}

MFileManager::MFileManager(AnsiString strFileName)
{
    InitializeCriticalSection(&m_Sync);

    char chPath[256];
    GetCurrentDirectory(256, chPath);

    m_strPath.printf("%s", chPath);

    m_strFileName = strFileName;
    m_strFile = m_strPath + "\\" + m_strFileName;

    m_pSectionList  = new TStringList;
    m_pKeyList      = new TStringList;
}

MFileManager::MFileManager(AnsiString strFileName, AnsiString strPath)
{
    InitializeCriticalSection(&m_Sync);

    if(strPath.SubString(strPath.Length(), 1) == "\\") {
        strPath.Delete(strPath.Length(), 1);
    }

    m_strPath       = strPath;
    m_strFileName   = strFileName;

    m_strFile       = m_strPath + "\\" + m_strFileName;

    m_pSectionList  = new TStringList;
    m_pKeyList      = new TStringList;

}

// 복사 생성자
__fastcall MFileManager::MFileManager(const MFileManager &from)
{
    InitializeCriticalSection(&m_Sync);

    m_strFileName       = from.m_strFileName;
    m_strPath           = from.m_strPath;
    m_strFile           = from.m_strFile;

    m_pSectionList      = new TStringList;
    m_pKeyList          = new TStringList;

}


void __fastcall MFileManager::Assign(MFileManager *pFrom)
{
    m_strFileName       = pFrom->m_strFileName;
    m_strPath           = pFrom->m_strPath;
    m_strFile           = pFrom->m_strFile;
}


MFileManager::~MFileManager()
{
    DeleteCriticalSection(&m_Sync);

    if(m_pSectionList) {
        m_pSectionList->Clear();
        delete m_pSectionList;
        m_pSectionList = NULL;
    }

    if(m_pKeyList) {
        m_pKeyList->Clear();
        delete m_pKeyList;
        m_pKeyList = NULL;
    }
}


void MFileManager::MFileManagerChangeData(AnsiString strFileName, AnsiString strPath)
{
    m_strPath = strPath;
    m_strFileName = strFileName;
    m_strFile = m_strPath + "\\" + m_strFileName;
}


void MFileManager::SetFilePath(AnsiString strPath)
{
//    if(strPath.SubString(strPath.Length(), 1) == "\\") {
//        strPath.Delete(strPath.Length(), 1);
//    }

    DeleteLastSlash(strPath);

    m_strPath = strPath;

    if(m_strFileName != "") {
        m_strFile = m_strPath + "\\" + m_strFileName;
    }
}

void MFileManager::SetFileName(AnsiString strFileName)
{
    m_strFileName = strFileName;
    m_strFile = m_strPath + "\\" + m_strFileName;
}

TStringList * MFileManager::GetSectionList()
{
    char lpszReturnBuffer[10240];
    ZeroMemory(lpszReturnBuffer, sizeof(lpszReturnBuffer));

    if(m_pSectionList) m_pSectionList->Clear();

    int nCount = 0;
    try {
        EnterCriticalSection(&m_Sync);
        nCount = GetPrivateProfileSectionNames(lpszReturnBuffer, sizeof(lpszReturnBuffer), m_strFile.c_str());
    }
    __finally {
        LeaveCriticalSection(&m_Sync);
    }

    //int nSectionCount = 0;
    int nDigitCount   = 0;
    char cSectionTemp[1000];
    ZeroMemory(cSectionTemp, sizeof(cSectionTemp));

    for(int i=0; i<nCount; i++) {
        if(lpszReturnBuffer[i] == '\0') {
            if(nDigitCount == 0) {
                break;
            }
            else {
                if(m_pSectionList) m_pSectionList->Add(cSectionTemp);
                //nSectionCount += 1;

                ZeroMemory(cSectionTemp, sizeof(cSectionTemp));
                nDigitCount = 0;
            }
        }
        else {
            cSectionTemp[nDigitCount] = lpszReturnBuffer[i];
            nDigitCount += 1;
        }
    }

    return m_pSectionList;

}

TStringList *  MFileManager::GetKeyList(AnsiString strSection)
{
    char lpszReturnBuffer[10240];
    ZeroMemory(lpszReturnBuffer, sizeof(lpszReturnBuffer));

    if(m_pKeyList) m_pKeyList->Clear();

    int nCount = 0;

    try {
        EnterCriticalSection(&m_Sync);
        nCount = GetPrivateProfileString(strSection.c_str(), NULL, "!@#$%", lpszReturnBuffer, sizeof(lpszReturnBuffer), m_strFile.c_str());
    }
    __finally {
        LeaveCriticalSection(&m_Sync);
    }

    if(strcmp(lpszReturnBuffer, "!@#$%") == 0)
    {
        return m_pKeyList;
    }

    //int nSectionCount = 0;
    int nDigitCount   = 0;
    char cSectionTemp[1000];
    ZeroMemory(cSectionTemp, sizeof(cSectionTemp));

    m_pKeyList->Clear();

    for(int i=0; i<nCount; i++) {
        if(lpszReturnBuffer[i] == '\0') {
            if(nDigitCount == 0) {
                break;
            }
            else {
                if(m_pKeyList) m_pKeyList->Add(cSectionTemp);
                //nSectionCount += 1;

                ZeroMemory(cSectionTemp, sizeof(cSectionTemp));
                nDigitCount = 0;
            }
        }
        else {
            cSectionTemp[nDigitCount] = lpszReturnBuffer[i];
            nDigitCount += 1;
        }
    }

    return m_pKeyList;

}


bool MFileManager::SetValue(AnsiString strSection, AnsiString strItem, unsigned short iValue)
{
    AnsiString strValue;
    int iResult;
    strValue.printf("%d", iValue);

    try {
        EnterCriticalSection(&m_Sync);
        iResult = WritePrivateProfileString(strSection.c_str(), strItem.c_str(), strValue.c_str(),m_strFile.c_str());
    }
    __finally {
        LeaveCriticalSection(&m_Sync);
    }

    if( !iResult ) return false;
    return true;
}

bool MFileManager::SetValue(AnsiString strSection, AnsiString strItem, int iValue)
{
    AnsiString strValue;
    int iResult;
    strValue.printf("%d", iValue);

    try {
        EnterCriticalSection(&m_Sync);
        iResult = WritePrivateProfileString(strSection.c_str(), strItem.c_str(), strValue.c_str(),m_strFile.c_str());
    }
    __finally {
        LeaveCriticalSection(&m_Sync);
    }

    if( !iResult ) return false;
    return true;
}

bool MFileManager::SetValue(AnsiString strSection, AnsiString strItem, UINT nValue)
{
    AnsiString strValue;
    int iResult;
    strValue.printf("%d", nValue);

    try {
        EnterCriticalSection(&m_Sync);
        iResult = WritePrivateProfileString(strSection.c_str(), strItem.c_str(), strValue.c_str(),m_strFile.c_str());
    }
    __finally {
        LeaveCriticalSection(&m_Sync);
    }

    if( !iResult ) return false;
    return true;
}

bool MFileManager::SetValue(AnsiString strSection, AnsiString strItem, long nValue)
{
    AnsiString strValue;
    int iResult;
    strValue.printf("%d", nValue);

    try {
        EnterCriticalSection(&m_Sync);
        iResult = WritePrivateProfileString(strSection.c_str(), strItem.c_str(), strValue.c_str(),m_strFile.c_str());
    }
    __finally {
        LeaveCriticalSection(&m_Sync);
    }

    if( !iResult ) return false;
    return true;
}

bool MFileManager::SetValue(AnsiString strSection, AnsiString strItem, unsigned long nValue)
{
    AnsiString strValue;
    int iResult;
    strValue.printf("%lu", nValue);

    try {
        EnterCriticalSection(&m_Sync);
        iResult = WritePrivateProfileString(strSection.c_str(), strItem.c_str(), strValue.c_str(),m_strFile.c_str());
    }
    __finally {
        LeaveCriticalSection(&m_Sync);
    }

    if( !iResult ) return false;
    return true;
}


bool MFileManager::SetValue(AnsiString strSection, AnsiString strItem, double dValue)
{
    AnsiString strValue;
    int iResult;
    strValue.printf("%lf", dValue);

    try {
        EnterCriticalSection(&m_Sync);
        iResult = WritePrivateProfileString(strSection.c_str(), strItem.c_str(), strValue.c_str(),m_strFile.c_str());
    }
    __finally {
        LeaveCriticalSection(&m_Sync);
    }
    if( !iResult ) return false;
    return true;
}

bool MFileManager::SetValue(AnsiString strSection, AnsiString strItem, AnsiString strValue)
{
    int iResult;

    try {
        EnterCriticalSection(&m_Sync);
        iResult = WritePrivateProfileString(strSection.c_str(), strItem.c_str(), strValue.c_str(),m_strFile.c_str());
    }
    __finally {
        LeaveCriticalSection(&m_Sync);
    }

    if( !iResult ) return false;
    return true;
}

bool MFileManager::SetValue(AnsiString strSection, AnsiString strItem, char* pchValue, UINT nSize)
{
    AnsiString strValue;
    int iResult;
    strValue.printf("%s", pchValue);

    try {
        EnterCriticalSection(&m_Sync);
        iResult = WritePrivateProfileString(strSection.c_str(), strItem.c_str(), strValue.c_str(),m_strFile.c_str());
    }
    __finally {
        LeaveCriticalSection(&m_Sync);
    }
    if( !iResult ) return false;
    return true;
}

bool MFileManager::SetValue(AnsiString strSection, AnsiString strItem, TColor cValue)
{
    AnsiString strValue;
    int nValue = cValue;
    int iResult;
    strValue.printf("%d", nValue);

    try {
        EnterCriticalSection(&m_Sync);
        iResult = WritePrivateProfileString(strSection.c_str(), strItem.c_str(), strValue.c_str(),m_strFile.c_str());
    }
    __finally {
        LeaveCriticalSection(&m_Sync);
    }

    if( !iResult ) return false;
    return true;
}


//------------------------------------------------------------------------------

bool MFileManager::GetValue(AnsiString strSection, AnsiString strItem, unsigned short * pnValue)
{
    int nValue = 0;
    try {
        EnterCriticalSection(&m_Sync);
        nValue = GetPrivateProfileInt(strSection.c_str(), strItem.c_str(), -999, m_strFile.c_str());
    }
    __finally {
        LeaveCriticalSection(&m_Sync);
    }

    if(nValue == -999) {
        return false;
    }

    *pnValue = (unsigned short)nValue;

    return true;
}

bool MFileManager::GetValue(AnsiString strSection, AnsiString strItem, int * pnValue)
{
    try {
        EnterCriticalSection(&m_Sync);
        *pnValue = GetPrivateProfileInt(strSection.c_str(), strItem.c_str(), -99, m_strFile.c_str());
    }
    __finally {
        LeaveCriticalSection(&m_Sync);
    }

    if(*pnValue == -99)
    {
        return false;
    }
    return true;
}

bool MFileManager::GetValue(AnsiString strSection, AnsiString strItem, UINT * pnValue)
{
    int nTemp;

    try {
        EnterCriticalSection(&m_Sync);
        nTemp = GetPrivateProfileInt(strSection.c_str(), strItem.c_str(), -99, m_strFile.c_str());
    }
    __finally {
        LeaveCriticalSection(&m_Sync);
    }

    if(nTemp == -99)
    {
        *pnValue = 0;
        return false;
    }
//	assert(nTemp >= 0);
    *pnValue = (UINT)nTemp;
    return true;
}

bool MFileManager::GetValue(AnsiString strSection, AnsiString strItem, long * pnValue)
{
    int nTemp;

    try {
        EnterCriticalSection(&m_Sync);
        nTemp = GetPrivateProfileInt(strSection.c_str(), strItem.c_str(), -99, m_strFile.c_str());
    }
    __finally {
        LeaveCriticalSection(&m_Sync);
    }

    if(nTemp == -99) {
        *pnValue = 0;
        return false;
    }
//	assert(nTemp >= 0);
    *pnValue = (long)nTemp;
    return true;
}

bool MFileManager::GetValue(AnsiString strSection, AnsiString strItem, unsigned long * pnValue)
{
    int nTemp;

    try {
        EnterCriticalSection(&m_Sync);
        nTemp = GetPrivateProfileInt(strSection.c_str(), strItem.c_str(), -99, m_strFile.c_str());
    }
    __finally {
        LeaveCriticalSection(&m_Sync);
    }

    if(nTemp == -99) {
        *pnValue = 0;
        return false;
    }
//	assert(nTemp >= 0);
    *pnValue = (unsigned long)nTemp;
    return true;
}


bool MFileManager::GetValue(AnsiString strSection, AnsiString strItem, double * pdValue)
{
    char chrData[256];
    memset(chrData, NULL, sizeof(chrData));

    try {
        EnterCriticalSection(&m_Sync);
        GetPrivateProfileString(strSection.c_str(), strItem.c_str(), "ERROR", chrData, 256, m_strFile.c_str());
    }
    __finally {
        LeaveCriticalSection(&m_Sync);
    }

    if(strcmp(chrData, "ERROR") == 0)
    {
        *pdValue = 0;
        return false;
    }

    *pdValue = atof(chrData);
    return true;
}

bool MFileManager::GetValue(AnsiString strSection, AnsiString strItem, AnsiString * pstrValue)
{
    char chrData[10000];
    memset(chrData, NULL, sizeof(chrData));

    try {
        EnterCriticalSection(&m_Sync);
        GetPrivateProfileString(strSection.c_str(), strItem.c_str(), "ERROR", chrData, 10000, m_strFile.c_str());
    }
    __finally {
        LeaveCriticalSection(&m_Sync);
    }


    if((strcmp(chrData, "ERROR") == 0) || (chrData[0] == '\0' ))
    {
        return false;
    }

    pstrValue->printf("%s", chrData);
    return true;
}

bool MFileManager::GetValue(AnsiString strSection, AnsiString strItem, char * pchValue, UINT nSize)
{
    char chrData[10000];
    memset(chrData, NULL, sizeof(chrData));

    try {
        EnterCriticalSection(&m_Sync);
        GetPrivateProfileString(strSection.c_str(), strItem.c_str(), "ERROR", chrData, 10000, m_strFile.c_str());
    }
    __finally {
        LeaveCriticalSection(&m_Sync);
    }

    if(strcmp(chrData, "ERROR") == 0) return false;

    if(strlen(chrData) > nSize) return false;

    strcpy(pchValue, chrData);
    return true;
}

bool MFileManager::GetValue(AnsiString strSection, AnsiString strItem, TColor * pcValue)
{
    int nColor = 0;

    try {
        EnterCriticalSection(&m_Sync);
        nColor = GetPrivateProfileInt(strSection.c_str(), strItem.c_str(), -99, m_strFile.c_str());
        *pcValue = (TColor)nColor;
    }
    __finally {
        LeaveCriticalSection(&m_Sync);
    }

    if(nColor == -99)
    {
        return false;
    }
    return true;
}


//------------------------------------------------------------------------------------------
bool      MFileManager::DeleteKey(AnsiString strSection, AnsiString strItem)
{
    int iResult;

    try {
        EnterCriticalSection(&m_Sync);
        WritePrivateProfileStruct(strSection.c_str(), strItem.c_str(), NULL, 0, m_strFile.c_str());
    }
    __finally {
        LeaveCriticalSection(&m_Sync);
    }

    if( !iResult ) return false;
    return true;
}

bool      MFileManager::DeleteSection(AnsiString strSection)
{
    int iResult;

    try {
        EnterCriticalSection(&m_Sync);
        WritePrivateProfileStruct(strSection.c_str(), NULL, NULL, 0, m_strFile.c_str());
    }
    __finally {
        LeaveCriticalSection(&m_Sync);
    }

    if( !iResult ) return false;
    return true;
}

//------------------------------------------------------------------------------------------

bool MFileManager::MakeBackUpFile()
{
    int nIndex;
    bool bRet = false;
    AnsiString strSrcFile, strDestFile;

    strSrcFile = m_strFile;
    nIndex = strSrcFile.AnsiPos(".ini");

    if(nIndex == -1 || nIndex == 0) return false;

    strDestFile = strSrcFile.SubString(1, nIndex-1) + ".bak";

    try {
        EnterCriticalSection(&m_Sync);
        bRet = CopyFile(strSrcFile.c_str(), strDestFile.c_str(), false);   // false이면 덮어쓰기 허용.
    }
    __finally {
        LeaveCriticalSection(&m_Sync);
    }

    return bRet;
}

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////

int    MFileManager::Set2xArrayValuePlus(AnsiString strSection, int iRow, int iCol, int iValue[300][300])
{
    AnsiString    strItem, strTmp, strResult;
    int ix, iy;

    for (iy = 0; iy < iRow; iy++)
    {
        strItem.printf("Line %d ", iy);
        strResult = "";
        for (ix = 0; ix < iCol; ix++)
        {
            strTmp.printf(" %d,", iValue[iy][ix]);
            strResult = strResult + strTmp;
        }
        if(SetValue(strSection, strItem, strResult) == false)
            return ERR_DATA_FAIL;
    }

    return ERR_DATA_SUCCESS;
}

int    MFileManager::Get2xArrayValuePlus(AnsiString strSection, int iRow, int iCol, int iValue[300][300])
{
    AnsiString    strItem, strTmp, strResult;
    int ix, iy;
    int iEnd;

    for (iy = 0; iy < iRow; iy++)
    {
        strItem.printf("Line %d ", iy);
        if(GetValue(strSection, strItem, &strResult) == false) {

            strResult = "";
            for (ix = 0; ix < iCol; ix++)
            {
                strTmp.printf(" %d,", iValue[iy][ix]);
                strResult = strResult + strTmp;
            }

            if(SetValue(strSection, strItem, strResult) == false) {
                return ERR_DATA_FAIL;
            }
        }

        strResult = strResult.Trim();

        //iEnd = 0;
        for (ix = 0; ix < iCol; ix++)
        {
            iEnd = strResult.AnsiPos(',');
            if (iEnd != -1)
            {
                strTmp = strResult.SubString(1, iEnd-1);
                iValue[iy][ix] = strTmp.ToInt();
                strResult.Delete(1, iEnd);
                strResult = strResult.Trim();
            }
            else {
                iValue[iy][ix] = 0;
            }
        }
    }
    return ERR_DATA_SUCCESS;
}




int    MFileManager::Set2xArrayValuePlus(AnsiString strSection, int iRow, int iCol, int *piValue)
{
    AnsiString    strItem, strTmp, strResult;
    int ix, iy;

    for (iy = 0; iy < iRow; iy++)
    {
        strItem.printf("Line %d ", iy);
        strResult = "";
        for (ix = 0; ix < iCol; ix++)
        {
            strTmp.printf(" %d,", *piValue);
            strResult = strResult + strTmp;
            piValue++;
        }
        if(SetValue(strSection, strItem, strResult) == false)
            return ERR_DATA_FAIL;
    }

    return ERR_DATA_SUCCESS;
}

int    MFileManager::Get2xArrayValuePlus(AnsiString strSection, int iRow, int iCol, int *piValue)
{
    AnsiString    strItem, strTmp, strResult;
    int ix, iy;
    int iEnd;

    for (iy = 0; iy < iRow; iy++)
    {
        strItem.printf("Line %d ", iy);

        if(GetValue(strSection, strItem, &strResult) == false) {
            int *pLineStartPtr = piValue;

            strResult = "";
            for (ix = 0; ix < iCol; ix++)
            {
                strTmp.printf(" %d,", *pLineStartPtr);
                strResult = strResult + strTmp;
                pLineStartPtr++;
            }

            if(SetValue(strSection, strItem, strResult) == false) {
                return ERR_DATA_FAIL;
            }
        }

        strResult = strResult.Trim();

        //iEnd = 0;
        for (ix = 0; ix < iCol; ix++)
        {
            iEnd = strResult.AnsiPos(',');
            if (iEnd != -1)
            {
                strTmp = strResult.SubString(1, iEnd-1);
                *piValue = strTmp.ToInt();
                strResult.Delete(1, iEnd);
                strResult = strResult.Trim();
            }
            else {
                *piValue = 0;
            }

            piValue++;
        }
    }
    return ERR_DATA_SUCCESS;
}




int    MFileManager::Set2xArrayValuePlus(AnsiString strSection, int iRow, int iCol, double dValue[300][300])
{
    AnsiString    strItem, strTmp, strResult;
    int ix, iy;

    for (iy = 0; iy < iRow; iy++)
    {
        strItem.printf("Line %d ", iy);
        strResult = "";
        for (ix = 0; ix < iCol; ix++)
        {
            strTmp.printf(" %8.2f,", dValue[iy][ix]);
            strResult = strResult + strTmp;
        }
        if(SetValue(strSection, strItem, strResult) == false)
            return ERR_DATA_FAIL;
    }
    return ERR_DATA_SUCCESS;
}

int    MFileManager::Get2xArrayValuePlus(AnsiString strSection, int iRow, int iCol, double dValue[300][300])
{
    AnsiString    strItem, strTmp, strResult;
    int ix, iy;
    int iEnd;
    for (iy = 0; iy < iRow; iy++)
    {
        strItem.printf("Line %d ", iy);
        if(GetValue(strSection, strItem, &strResult) == false) {

            strResult = "";
            for (ix = 0; ix < iCol; ix++)
            {
                strTmp.printf(" %8.2f,", dValue[iy][ix]);
                strResult = strResult + strTmp;
            }
            if(SetValue(strSection, strItem, strResult) == false)
                return ERR_DATA_FAIL;
        }

        strResult = strResult.Trim();
//        iEnd = 0;
        for (ix = 0; ix < iCol; ix++)
        {
            iEnd = strResult.AnsiPos(',');
            if (iEnd != -1)
            {
                strTmp = strResult.SubString(1, iEnd-1);
                dValue[iy][ix] = strTmp.ToDouble();
                strResult.Delete(1, iEnd);
                strResult = strResult.Trim();
            }
            else
                dValue[iy][ix] = 0.0;
        }
    }
    return ERR_DATA_SUCCESS;
}



int    MFileManager::Set2xArrayValuePlus(AnsiString strSection, int iRow, int iCol, double *pdValue)
{
    AnsiString    strItem, strTmp, strResult;
    int ix, iy;

    for (iy = 0; iy < iRow; iy++)
    {
        strItem.printf("Line %d ", iy);
        strResult = "";
        for (ix = 0; ix < iCol; ix++)
        {
            strTmp.printf(" %8.2f,", *pdValue);
            strResult = strResult + strTmp;
            pdValue++;
        }
        if(SetValue(strSection, strItem, strResult) == false)
            return ERR_DATA_FAIL;
    }
    return ERR_DATA_SUCCESS;
}

int    MFileManager::Get2xArrayValuePlus(AnsiString strSection, int iRow, int iCol, double *pdValue)
{
    AnsiString    strItem, strTmp, strResult;
    int ix, iy;
    int iEnd;
    for (iy = 0; iy < iRow; iy++)
    {
        strItem.printf("Line %d ", iy);
        if(GetValue(strSection, strItem, &strResult) == false) {
            double *pLineStartPtr = pdValue;
            strResult = "";
            for (ix = 0; ix < iCol; ix++)
            {
                strTmp.printf(" %8.2f,", *pLineStartPtr);
                strResult = strResult + strTmp;
                pLineStartPtr++;
            }
            if(SetValue(strSection, strItem, strResult) == false)
                return ERR_DATA_FAIL;
        }

        strResult = strResult.Trim();
//        iEnd = 0;
        for (ix = 0; ix < iCol; ix++)
        {
            iEnd = strResult.AnsiPos(',');
            if (iEnd != -1)
            {
                strTmp = strResult.SubString(1, iEnd-1);
                *pdValue = strTmp.ToDouble();
                strResult.Delete(1, iEnd);
                strResult = strResult.Trim();
            }
            else
                *pdValue = 0.0;

            pdValue++;
        }
    }
    return ERR_DATA_SUCCESS;
}





int    MFileManager::Set2xArrayValuePlus(AnsiString strSection, int iRow, int iCol, TColor cValue[300][300])
{
    AnsiString    strItem, strTmp, strResult;
    int ix, iy;
    int nColor;

    for (iy = 0; iy < iRow; iy++)
    {
        strItem.printf("Line %d ", iy);
        strResult = "";
        for (ix = 0; ix < iCol; ix++)
        {
            nColor = cValue[iy][ix];
            strTmp.printf(" %d,", nColor);
            strResult = strResult + strTmp;
        }
        if(SetValue(strSection, strItem, strResult) == false)
            return ERR_DATA_FAIL;
    }

    return ERR_DATA_SUCCESS;
}

int    MFileManager::Get2xArrayValuePlus(AnsiString strSection, int iRow, int iCol, TColor cValue[300][300])
{
    AnsiString    strItem, strTmp, strResult;
    int ix, iy;
    int iEnd;
    int nColor;

    for (iy = 0; iy < iRow; iy++)
    {
        strItem.printf("Line %d ", iy);
        if(GetValue(strSection, strItem, &strResult) == false) {

            strResult = "";
            for (ix = 0; ix < iCol; ix++)
            {
                nColor = cValue[iy][ix];
                strTmp.printf(" %d,", nColor);
                strResult = strResult + strTmp;
            }

            if(SetValue(strSection, strItem, strResult) == false) {
                return ERR_DATA_FAIL;
            }
        }

        strResult = strResult.Trim();

//        iEnd = 0;
        for (ix = 0; ix < iCol; ix++)
        {
            iEnd = strResult.AnsiPos(',');
            if (iEnd != -1)
            {
                strTmp = strResult.SubString(1, iEnd-1);
                nColor = strTmp.ToInt();
                cValue[iy][ix] = (TColor)nColor;
                strResult.Delete(1, iEnd);
                strResult = strResult.Trim();
            }
            else {
                cValue[iy][ix] = clBlack;
            }
        }
    }
    return ERR_DATA_SUCCESS;
}



int    MFileManager::Set2xArrayValuePlus(AnsiString strSection, int iRow, int iCol, TColor *pcValue)
{
    AnsiString    strItem, strTmp, strResult;
    int ix, iy;
    int nColor;

    for (iy = 0; iy < iRow; iy++)
    {
        strItem.printf("Line %d ", iy);
        strResult = "";
        for (ix = 0; ix < iCol; ix++)
        {
            nColor = *pcValue;
            strTmp.printf(" %d,", nColor);
            strResult = strResult + strTmp;
            pcValue++;
        }
        if(SetValue(strSection, strItem, strResult) == false)
            return ERR_DATA_FAIL;
    }

    return ERR_DATA_SUCCESS;
}

int    MFileManager::Get2xArrayValuePlus(AnsiString strSection, int iRow, int iCol, TColor *pcValue)
{
    AnsiString    strItem, strTmp, strResult;
    int ix, iy;
    int iEnd;
    int nColor;

    for (iy = 0; iy < iRow; iy++)
    {
        strItem.printf("Line %d ", iy);

        if(GetValue(strSection, strItem, &strResult) == false) {
            TColor *pLineStartPtr = pcValue;

            strResult = "";
            for (ix = 0; ix < iCol; ix++)
            {
                nColor = *pLineStartPtr;
                strTmp.printf(" %d,", nColor);
                strResult = strResult + strTmp;
                pLineStartPtr++;
            }

            if(SetValue(strSection, strItem, strResult) == false) {
                return ERR_DATA_FAIL;
            }
        }

        strResult = strResult.Trim();

//        iEnd = 0;
        for (ix = 0; ix < iCol; ix++)
        {
            iEnd = strResult.AnsiPos(',');
            if (iEnd != -1)
            {
                strTmp = strResult.SubString(1, iEnd-1);
                nColor = strTmp.ToInt();
                *pcValue = (TColor)nColor;
                strResult.Delete(1, iEnd);
                strResult = strResult.Trim();
            }
            else {
                *pcValue = clBlack;
            }

            pcValue++;
        }
    }
    return ERR_DATA_SUCCESS;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int    MFileManager::Set1xArrayValuePlus(AnsiString strSection, AnsiString strKey, int iXNum, double dValue[300])
{
    AnsiString    strTmp, strResult;
    int ix;

    strResult = "";
    for (ix = 0; ix < iXNum; ix++)
    {
        strTmp.printf("%0.3f,", dValue[ix]);
        strResult = strResult + strTmp;
    }
    if(SetValue(strSection, strKey, strResult) == false)
        return ERR_DATA_FAIL;

    return ERR_DATA_SUCCESS;
}

int    MFileManager::Get1xArrayValuePlus(AnsiString strSection, AnsiString strKey, int iXNum, double dValue[300])
{
    AnsiString    strTmp, strResult;
    int ix;
    int iEnd;

    if(GetValue(strSection, strKey, &strResult) == false) {
        strResult = "";
        for (ix = 0; ix < iXNum; ix++)
        {
            strTmp.printf("%0.3f,", dValue[ix]);
            strResult = strResult + strTmp;
        }

        if(SetValue(strSection, strKey, strResult) == false) {
            return ERR_DATA_FAIL;
        }
    }

    strResult = strResult.Trim();

#if 0
    iEnd = 0;
    for (ix = 0; ix < iXNum; ix++)
    {
        iEnd = strResult.AnsiPos(',');
        if (iEnd != -1)
        {
            strTmp = strResult.SubString(1, iEnd-1);
            strTmp = strTmp.Trim();
            dValue[ix] = strTmp.ToDouble();
            strResult.Delete(1, iEnd);
            strResult = strResult.Trim();
        }
        else
            dValue[ix] = 0;
    }
#else

    TStringList * sList = new TStringList;
    int nCount = DivideByIndicator(strResult, sList, ',');

    for(int i=0; i<iXNum; i++) {
        if(i < sList->Count) {
            strTmp = sList->Strings[i];
            dValue[i] = strTmp.ToDouble();
        }
    }

    // ini 파일에 배열 수보다 적은 데이터가 있다면 다시 저장시 나머지 부분을 생성시킨다.
    if(nCount < iXNum) {
        Set1xArrayValuePlus(strSection, strKey, iXNum, dValue);
    }

    delete sList;
#endif

    return ERR_DATA_SUCCESS;
}




int    MFileManager::Set1xArrayValuePlus(AnsiString strSection, AnsiString strKey, int iXNum, long Value[300])
{
    AnsiString    strTmp, strResult;
    int ix;

    strResult = "";
    for (ix = 0; ix < iXNum; ix++)
    {
        strTmp.printf("%0.3f,", Value[ix]);
        strResult = strResult + strTmp;
    }
    if(SetValue(strSection, strKey, strResult) == false)
        return ERR_DATA_FAIL;

    return ERR_DATA_SUCCESS;
}

int    MFileManager::Get1xArrayValuePlus(AnsiString strSection, AnsiString strKey, int iXNum, long Value[300])
{
    AnsiString    strTmp, strResult;
    int ix;
    int iEnd;

    if(GetValue(strSection, strKey, &strResult) == false) {
        strResult = "";
        for (ix = 0; ix < iXNum; ix++)
        {
            strTmp.printf("%0.3f,", Value[ix]);
            strResult = strResult + strTmp;
        }

        if(SetValue(strSection, strKey, strResult) == false) {
            return ERR_DATA_FAIL;
        }
    }

    strResult = strResult.Trim();

#if 0
    iEnd = 0;
    for (ix = 0; ix < iXNum; ix++)
    {
        iEnd = strResult.AnsiPos(',');
        if (iEnd != -1)
        {
            strTmp = strResult.SubString(1, iEnd-1);
            strTmp = strTmp.Trim();
            dValue[ix] = strTmp.ToDouble();
            strResult.Delete(1, iEnd);
            strResult = strResult.Trim();
        }
        else
            dValue[ix] = 0;
    }
#else

    TStringList * sList = new TStringList;
    int nCount = DivideByIndicator(strResult, sList, ',');

    for(int i=0; i<iXNum; i++) {
        if(i<sList->Count) {
            strTmp = sList->Strings[i];
            Value[i] = strTmp.ToDouble();
        }
    }

    // ini 파일에 배열 수보다 적은 데이터가 있다면 다시 저장시 나머지 부분을 생성시킨다.
    if(nCount < iXNum) {
        Set1xArrayValuePlus(strSection, strKey, iXNum, Value);
    }

    delete sList;
#endif

    return ERR_DATA_SUCCESS;
}




int    MFileManager::Set1xArrayValuePlus(AnsiString strSection, AnsiString strKey, int iXNum, unsigned long Value[300])
{
    AnsiString    strTmp, strResult;
    int ix;

    strResult = "";
    for (ix = 0; ix < iXNum; ix++)
    {
        strTmp.printf("%lu,", Value[ix]);
        strResult = strResult + strTmp;
    }
    if(SetValue(strSection, strKey, strResult) == false)
        return ERR_DATA_FAIL;

    return ERR_DATA_SUCCESS;
}

int    MFileManager::Get1xArrayValuePlus(AnsiString strSection, AnsiString strKey, int iXNum, unsigned long Value[300])
{
    AnsiString    strTmp, strResult;
    int ix;
    int iEnd;

    if(GetValue(strSection, strKey, &strResult) == false) {
        strResult = "";
        for (ix = 0; ix < iXNum; ix++)
        {
            strTmp.printf("%lu,", Value[ix]);
            strResult = strResult + strTmp;
        }

        if(SetValue(strSection, strKey, strResult) == false) {
            return ERR_DATA_FAIL;
        }
    }

    strResult = strResult.Trim();

#if 0
    iEnd = 0;
    for (ix = 0; ix < iXNum; ix++)
    {
        iEnd = strResult.AnsiPos(',');
        if (iEnd != -1)
        {
            strTmp = strResult.SubString(1, iEnd-1);
            strTmp = strTmp.Trim();
            dValue[ix] = strTmp.ToDouble();
            strResult.Delete(1, iEnd);
            strResult = strResult.Trim();
        }
        else
            dValue[ix] = 0;
    }
#else

    TStringList * sList = new TStringList;
    int nCount = DivideByIndicator(strResult, sList, ',');

    for(int i=0; i<iXNum; i++) {
        if(i<sList->Count) {
            strTmp = sList->Strings[i];
            Value[i] = strTmp.ToDouble();
        }
    }

    // ini 파일에 배열 수보다 적은 데이터가 있다면 다시 저장시 나머지 부분을 생성시킨다.
    if(nCount < iXNum) {
        Set1xArrayValuePlus(strSection, strKey, iXNum, Value);
    }

    delete sList;
#endif

    return ERR_DATA_SUCCESS;
}




int    MFileManager::Set1xArrayValuePlus(AnsiString strSection, AnsiString strKey, int iXNum, int iValue[300])
{
    AnsiString    strTmp, strResult;
    int ix;

    strResult = "";
    for (ix = 0; ix < iXNum; ix++)
    {
        strTmp.printf("%2d,", iValue[ix]);
        strResult = strResult + strTmp;
    }
    if(SetValue(strSection, strKey, strResult) == false)
        return ERR_DATA_FAIL;

    return ERR_DATA_SUCCESS;
}

int    MFileManager::Get1xArrayValuePlus(AnsiString strSection, AnsiString strKey, int iXNum, int iValue[300])
{
    AnsiString    strTmp, strResult;
    int ix;
    int iEnd;

    if(GetValue(strSection, strKey, &strResult) == false) {
        strResult = "";
        for (ix = 0; ix < iXNum; ix++)
        {
            strTmp.printf("%2d,", iValue[ix]);
            strResult = strResult + strTmp;
        }

        if(SetValue(strSection, strKey, strResult) == false) {
            return ERR_DATA_FAIL;
        }
    }

    strResult = strResult.Trim();

#if 0

    iEnd = 0;
    for (ix = 0; ix < iXNum; ix++)
    {
        iEnd = strResult.AnsiPos(',');
        if (iEnd != -1)
        {
            strTmp = strResult.SubString(1, iEnd-1);
            iValue[ix] = strTmp.ToInt();
            strResult.Delete(1, iEnd);
            strResult = strResult.Trim();
        }
        else
            iValue[ix] = 0;
    }

#else

    TStringList * sList = new TStringList;
    int nCount = DivideByIndicator(strResult, sList, ',');

    for(int i=0; i<iXNum; i++) {
        if(i<sList->Count) {
            strTmp = sList->Strings[i];
            iValue[i] = strTmp.ToIntDef(0);
        }
    }

    // ini 파일에 배열 수보다 적은 데이터가 있다면 다시 저장시 나머지 부분을 생성시킨다.
    if(nCount < iXNum) {
        Set1xArrayValuePlus(strSection, strKey, iXNum, iValue);
    }

    delete sList;
#endif

    return ERR_DATA_SUCCESS;
}



int    MFileManager::Set1xArrayValuePlus(AnsiString strSection, AnsiString strKey, int iXNum, unsigned int iValue[300])
{
    AnsiString    strTmp, strResult;
    int ix;

    strResult = "";
    for (ix = 0; ix < iXNum; ix++)
    {
        strTmp.printf("%2d,", iValue[ix]);
        strResult = strResult + strTmp;
    }
    if(SetValue(strSection, strKey, strResult) == false)
        return ERR_DATA_FAIL;

    return ERR_DATA_SUCCESS;
}

int    MFileManager::Get1xArrayValuePlus(AnsiString strSection, AnsiString strKey, int iXNum, unsigned int iValue[300])
{
    AnsiString    strTmp, strResult;
    int ix;
    int iEnd;

    if(GetValue(strSection, strKey, &strResult) == false) {
        strResult = "";
        for (ix = 0; ix < iXNum; ix++)
        {
            strTmp.printf("%2d,", iValue[ix]);
            strResult = strResult + strTmp;
        }

        if(SetValue(strSection, strKey, strResult) == false) {
            return ERR_DATA_FAIL;
        }
    }

    strResult = strResult.Trim();

#if 0

    iEnd = 0;
    for (ix = 0; ix < iXNum; ix++)
    {
        iEnd = strResult.AnsiPos(',');
        if (iEnd != -1)
        {
            strTmp = strResult.SubString(1, iEnd-1);
            iValue[ix] = strTmp.ToInt();
            strResult.Delete(1, iEnd);
            strResult = strResult.Trim();
        }
        else
            iValue[ix] = 0;
    }

#else

    TStringList * sList = new TStringList;
    int nCount = DivideByIndicator(strResult, sList, ',');

    for(int i=0; i<iXNum; i++) {
        if(i<sList->Count) {
            strTmp = sList->Strings[i];
            iValue[i] = strTmp.ToIntDef(0);
        }
    }

    // ini 파일에 배열 수보다 적은 데이터가 있다면 다시 저장시 나머지 부분을 생성시킨다.
    if(nCount < iXNum) {
        Set1xArrayValuePlus(strSection, strKey, iXNum, iValue);
    }

    delete sList;
#endif

    return ERR_DATA_SUCCESS;
}


int    MFileManager::Set1xArrayValuePlus(AnsiString strSection, AnsiString strKey, int iXNum, bool bValue[300])
{
    AnsiString    strTmp, strResult;
    int ix;

    strResult = "";
    for (ix = 0; ix < iXNum; ix++)
    {
        strTmp.printf("%d,", (int)bValue[ix]);
        strResult = strResult + strTmp;
    }
    if(SetValue(strSection, strKey, strResult) == false)
        return ERR_DATA_FAIL;

    return ERR_DATA_SUCCESS;
}

int    MFileManager::Get1xArrayValuePlus(AnsiString strSection, AnsiString strKey, int iXNum, bool bValue[300])
{
    AnsiString    strTmp, strResult;
    int ix;
    int iEnd;

    if(GetValue(strSection, strKey, &strResult) == false) {
        strResult = "";
        for (ix = 0; ix < iXNum; ix++)
        {
            strTmp.printf("%d,", (int)bValue[ix]);
            strResult = strResult + strTmp;
        }
        if(SetValue(strSection, strKey, strResult) == false)
            return ERR_DATA_FAIL;
    }

    strResult = strResult.Trim();

#if 0
    iEnd = 0;
    for (ix = 0; ix < iXNum; ix++)
    {
        iEnd = strResult.AnsiPos(',');
        if (iEnd != -1)
        {
            strTmp = strResult.SubString(1, iEnd-1);
            bValue[ix] = (bool) (strTmp.ToInt());
            strResult.Delete(1, iEnd);
            strResult = strResult.Trim();
        }
        else
            bValue[ix] = false;
    }
#else

    TStringList * sList = new TStringList;
    int nCount = DivideByIndicator(strResult, sList, ',');

    for(int i=0; i<iXNum; i++) {
        if(i<sList->Count) {
            strTmp = sList->Strings[i];
            bValue[i] = (bool) (strTmp.ToIntDef(0));
        }
    }

    // ini 파일에 배열 수보다 적은 데이터가 있다면 다시 저장시 나머지 부분을 생성시킨다.
    if(nCount < iXNum) {
        Set1xArrayValuePlus(strSection, strKey, iXNum, bValue);
    }

    delete sList;
#endif

    return ERR_DATA_SUCCESS;
}

int    MFileManager::Set1xArrayValuePlus(AnsiString strSection, AnsiString strKey, int iXNum, AnsiString strValue[300])
{
    AnsiString    strResult;
    int ix;

    strResult = "";
    for (ix = 0; ix < iXNum; ix++)
    {
        strResult = strResult + strValue[ix] + ",";
    }
    if(SetValue(strSection, strKey, strResult) == false)
        return ERR_DATA_FAIL;

    return ERR_DATA_SUCCESS;
}

int    MFileManager::Get1xArrayValuePlus(AnsiString strSection, AnsiString strKey, int iXNum, AnsiString strValue[300])
{
    AnsiString    strTmp, strResult;
    int ix;
    int iEnd;

    if(GetValue(strSection, strKey, &strResult) == false) {
        strResult = "";
        for (ix = 0; ix < iXNum; ix++)
        {
            strResult = strResult + strValue[ix] + ",";
        }
        if(SetValue(strSection, strKey, strResult) == false)
            return ERR_DATA_FAIL;
    }

    strResult = strResult.Trim();
#if 0
    iEnd = 0;
    for (ix = 0; ix < iXNum; ix++)
    {
        iEnd = strResult.AnsiPos(',');
        if (iEnd != -1)
        {
            strTmp = strResult.SubString(1, iEnd-1);
            strValue[ix] = strTmp;
            strResult.Delete(1, iEnd);
            strResult = strResult.Trim();
        }
        else
            strValue[ix] = "";
    }
#else

    TStringList * sList = new TStringList;
    int nCount = DivideByIndicator(strResult, sList, ',');

    for(int i=0; i<iXNum; i++) {
        if(i<sList->Count) {
            strTmp = sList->Strings[i];
            strValue[i] = strTmp;
        }
    }

    // ini 파일에 배열 수보다 적은 데이터가 있다면 다시 저장시 나머지 부분을 생성시킨다.
    if(nCount < iXNum) {
        Set1xArrayValuePlus(strSection, strKey, iXNum, strValue);
    }

    delete sList;
#endif

    return ERR_DATA_SUCCESS;
}




int    MFileManager::Set1xArrayValuePlus(AnsiString strSection, AnsiString strKey, int iXNum, TColor cValue[300])
{
    AnsiString    strTmp, strResult;
    int ix;
    int nColor;

    strResult = "";
    for (ix = 0; ix < iXNum; ix++)
    {
        nColor = cValue[ix];
        strTmp.printf("%2d,", nColor);
        strResult = strResult + strTmp;
    }
    if(SetValue(strSection, strKey, strResult) == false)
        return ERR_DATA_FAIL;

    return ERR_DATA_SUCCESS;
}

int    MFileManager::Get1xArrayValuePlus(AnsiString strSection, AnsiString strKey, int iXNum, TColor cValue[300])
{
    AnsiString    strTmp, strResult;
    int ix;
    int iEnd;
    int nColor;

    if(GetValue(strSection, strKey, &strResult) == false) {
        strResult = "";
        for (ix = 0; ix < iXNum; ix++)
        {
            nColor = cValue[ix];
            strTmp.printf("%2d,", nColor);
            strResult = strResult + strTmp;
        }

        if(SetValue(strSection, strKey, strResult) == false) {
            return ERR_DATA_FAIL;
        }
    }

    strResult = strResult.Trim();
#if 0
    iEnd = 0;
    for (ix = 0; ix < iXNum; ix++)
    {
        iEnd = strResult.AnsiPos(',');
        if (iEnd != -1)
        {
            strTmp = strResult.SubString(1, iEnd-1);
            nColor = strTmp.ToInt();
            cValue[ix] = (TColor)nColor;
            strResult.Delete(1, iEnd);
            strResult = strResult.Trim();
        }
        else
            cValue[ix] = clBlack;
    }
#else

    TStringList * sList = new TStringList;
    int nCount = DivideByIndicator(strResult, sList, ',');

    for(int i=0; i<iXNum; i++) {
        if(i<sList->Count) {
            strTmp = sList->Strings[i];
            nColor = strTmp.ToInt();
            cValue[i] = (TColor)nColor;
        }
    }

    // ini 파일에 배열 수보다 적은 데이터가 있다면 다시 저장시 나머지 부분을 생성시킨다.
    if(nCount < iXNum) {
        Set1xArrayValuePlus(strSection, strKey, iXNum, cValue);
    }

    delete sList;
#endif

    return ERR_DATA_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




int     MFileManager::SetValuePlus(AnsiString strSection, AnsiString strItem, bool bValue)
{
    m_strTmp = (bValue) ? "TRUE" : "false";
    SetValue(strSection, strItem, m_strTmp);
    return ERR_DATA_SUCCESS;
}

int     MFileManager::GetValuePlus(AnsiString strSection, AnsiString strItem, bool * pbValue, bool bDefaultValue)
{
    if(GetValue(strSection, strItem, &m_strTmp) == false)
    {
        m_strTmp = (bDefaultValue) ? "TRUE" : "false";
        SetValue(strSection, strItem, m_strTmp);
    }
    *pbValue = (m_strTmp == "TRUE") ? true : false;
    return ERR_DATA_SUCCESS;
}

int      MFileManager::SetValuePlus(AnsiString strSection, AnsiString strItem, unsigned short iValue)
{
    SetValue(strSection, strItem, iValue);
    return ERR_DATA_SUCCESS;
}

int      MFileManager::GetValuePlus(AnsiString strSection, AnsiString strItem, unsigned short * piValue, unsigned short iDefaultValue)
{
    if(GetValue(strSection, strItem, piValue) == false)
    {
        SetValue(strSection, strItem, iDefaultValue);
        *piValue = iDefaultValue;
    }
    return ERR_DATA_SUCCESS;
}

int      MFileManager::SetValuePlus(AnsiString strSection, AnsiString strItem, int iValue)
{
    SetValue(strSection, strItem, iValue);
    return ERR_DATA_SUCCESS;
}

int      MFileManager::GetValuePlus(AnsiString strSection, AnsiString strItem, int * piValue, int iDefaultValue)
{
    if(GetValue(strSection, strItem, piValue) == false)
    {
        SetValue(strSection, strItem, iDefaultValue);
        *piValue = iDefaultValue;
    }
    return ERR_DATA_SUCCESS;
}


int MFileManager::SetValuePlus(AnsiString strSection, AnsiString strItem, char *pValue)
{
    SetValue(strSection, strItem, pValue, strlen(pValue));
    return ERR_DATA_SUCCESS;

}

int MFileManager::GetValuePlus(AnsiString strSection, AnsiString strItem, char *pValue, char *pDefault)
{
    char szTemp[256];
    ZeroMemory(szTemp, sizeof(szTemp));

    if(GetValue(strSection, strItem, szTemp, 256) == false)
    {
        if(pDefault != NULL) {
            SetValue(strSection, strItem, pDefault, strlen(pDefault));
            strcpy(pValue, pDefault);
        }
    }
    else {
        strcpy(pValue, szTemp);
    }

    return ERR_DATA_SUCCESS;
}

int      MFileManager::SetValuePlus(AnsiString strSection, AnsiString strItem, UINT nValue)
{
    SetValue(strSection, strItem, nValue);
    return ERR_DATA_SUCCESS;
}

int      MFileManager::GetValuePlus(AnsiString strSection, AnsiString strItem, UINT * pnValue, UINT nDefaultValue)
{
    if(GetValue(strSection, strItem, pnValue) == false)
    {
        SetValue(strSection, strItem, nDefaultValue);
        *pnValue = nDefaultValue;
    }
    return ERR_DATA_SUCCESS;
}

int      MFileManager::SetValuePlus(AnsiString strSection, AnsiString strItem, long nValue)
{
    SetValue(strSection, strItem, nValue);
    return ERR_DATA_SUCCESS;
}

int      MFileManager::GetValuePlus(AnsiString strSection, AnsiString strItem, long * pnValue, long nDefaultValue)
{
    if(GetValue(strSection, strItem, pnValue) == false)
    {
        SetValue(strSection, strItem, nDefaultValue);
        *pnValue = nDefaultValue;
    }
    return ERR_DATA_SUCCESS;
}


int      MFileManager::SetValuePlus(AnsiString strSection, AnsiString strItem, unsigned long nValue)
{
    SetValue(strSection, strItem, nValue);
    return ERR_DATA_SUCCESS;
}

int      MFileManager::GetValuePlus(AnsiString strSection, AnsiString strItem, unsigned long * pnValue, unsigned long nDefaultValue)
{
    if(GetValue(strSection, strItem, pnValue) == false)
    {
        SetValue(strSection, strItem, nDefaultValue);
        *pnValue = nDefaultValue;
    }
    return ERR_DATA_SUCCESS;
}

int      MFileManager::SetValuePlus(AnsiString strSection, AnsiString strItem, double dValue)
{
    SetValue(strSection, strItem, dValue);
    return ERR_DATA_SUCCESS;
}

int      MFileManager::GetValuePlus(AnsiString strSection, AnsiString strItem, double * pdValue, double dDefaultValue)
{
    if(GetValue(strSection, strItem, pdValue) == false)
    {
        SetValue(strSection, strItem, dDefaultValue);
        *pdValue = dDefaultValue;
    }
    return ERR_DATA_SUCCESS;
}


int      MFileManager::SetValuePlus(AnsiString strSection, AnsiString strItem, AnsiString strValue)
{
    SetValue(strSection, strItem, strValue);
    return ERR_DATA_SUCCESS;
}

int      MFileManager::GetValuePlus(AnsiString strSection, AnsiString strItem, AnsiString * pstrValue, AnsiString strDefaultValue)
{
    if(GetValue(strSection, strItem, pstrValue) == false)
    {
        SetValue(strSection, strItem, strDefaultValue);
        *pstrValue = strDefaultValue;
    }
    return ERR_DATA_SUCCESS;
}



