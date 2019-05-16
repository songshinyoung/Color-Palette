//---------------------------------------------------------------------------

#ifndef MFileManagerH
#define MFileManagerH
//---------------------------------------------------------------------------
#include <Classes.hpp>

//#include "GlobalValue.h"

#define ERR_DATA_SUCCESS                0
#define ERR_DATA_LIMIT_OVER             1
#define ERR_DATA_READ                   2
#define ERR_DATA_WRITE                  3
#define ERR_DATA_FAIL                   4

/**
 * MFileManager Class는 파일로 부터 특정 Item을 얻어 오거나 반대로 특정 Item에 쓰는 역할을 하는 Class 이다.
 */
class MFileManager
{
protected:
    AnsiString          m_strFileName;
    AnsiString          m_strPath;
    AnsiString          m_strFile;
    CRITICAL_SECTION    m_Sync;     // 싱크가 필요한 변수는 이걸로 막아야한다. 특히 AnsiString 변수는 다른 쓰래드와 같이 엑세스 할 경우 이걸로 동기화 한다.

    TStringList *       m_pSectionList;
    TStringList *       m_pKeyList;

public:

    /**
     * 생성자
     */
    MFileManager();

    /**
     * 생성자 strFileName : 읽거나 쓰야하는 File 이름
     */
    MFileManager(AnsiString strFileName);

    /**
     * 생성자 strFileName : 읽거나 쓰야하는 File 이름
     *             strPath : File의 경로명
     */
    MFileManager(AnsiString strFileName, AnsiString strPath);

    /**
     * 복사 생성자
     */
    __fastcall MFileManager(const MFileManager &from);


    void __fastcall Assign(MFileManager *pFrom) ;



    void MFileManagerChangeData(AnsiString strFileName, AnsiString strPath);


    /**
     * 소멸자
     */
    virtual ~MFileManager();

	/** File Path를 다시 설정 하는 함수 */
    void SetFilePath(AnsiString strPath);

	/** File Path를 다시 설정 하는 함수 */
    void SetFileName(AnsiString strFileName);

    TStringList *  GetSectionList();
    TStringList *  GetKeyList(AnsiString strSection);

    AnsiString __fastcall GetFileName()         {return m_strFileName; };
    AnsiString __fastcall GetPath()             {return m_strPath; };
    AnsiString __fastcall GetFileFullPathName() {return m_strFile; };
	/**
     * Backup File을 만드는 함수
     */
    bool MakeBackUpFile();

private:
//    bool __fastcall GetIniFile(TIniFile * pFile, bool & bLocalIniCreate);
    AnsiString    m_strTmp;


protected:
    //int SetValue(AnsiString strSection, AnsiString strItem, int nValue, TIniFile * pFile = NULL);

    /**
     * File에 인자로 받은 Section과 Item에 정수값을 쓰는 함수
     */
    bool SetValue(AnsiString strSection, AnsiString strItem, unsigned short nValue);


    /**
     * File에 인자로 받은 Section과 Item에 정수값을 쓰는 함수
     */
    bool SetValue(AnsiString strSection, AnsiString strItem, int nValue);

	/**
     * File에 인자로 받은 Section과 Item에 정수값을 쓰는 함수
     */
    bool SetValue(AnsiString strSection, AnsiString strItem, UINT nValue);

	/**
     * File에 인자로 받은 Section과 Item에 정수값을 쓰는 함수
     */
    bool SetValue(AnsiString strSection, AnsiString strItem, long nValue);

	/**
     * File에 인자로 받은 Section과 Item에 정수값을 쓰는 함수
     */
    bool SetValue(AnsiString strSection, AnsiString strItem, unsigned long nValue);

    /**
     * File에 인자로 받은 Section과 Item에 실수값을 쓰는 함수
     */
    bool SetValue(AnsiString strSection, AnsiString strItem, double dValue);

    /**
     * File에 인자로 받은 Section과 Item에 문자값을 쓰는 함수
     */
    bool SetValue(AnsiString strSection, AnsiString strItem, AnsiString strValue);
	 /**
     * File에 인자로 받은 Section과 Item에 문자값을 쓰는 함수
     */
    bool SetValue(AnsiString strSection, AnsiString strItem, char* pchValue, UINT nSize);

    /**
     * File에 인자로 받은 Section과 Item에 TColor값을 쓰는 함수
     */
    bool SetValue(AnsiString strSection, AnsiString strItem, TColor cValue);


    /**
     * File에서 인자로 받은 Section과 Item의 값을 읽어 오는 함수
     */
    bool GetValue(AnsiString strSection, AnsiString strItem, unsigned short * pnValue);

    /**
     * File에서 인자로 받은 Section과 Item의 값을 읽어 오는 함수
     */
    bool GetValue(AnsiString strSection, AnsiString strItem, int * pnValue);

	/**
     * File에서 인자로 받은 Section과 Item의 값을 읽어 오는 함수
     */
    bool GetValue(AnsiString strSection, AnsiString strItem, UINT * pnValue);

	/**
     * File에서 인자로 받은 Section과 Item의 값을 읽어 오는 함수
     */
    bool GetValue(AnsiString strSection, AnsiString strItem, long * pnValue);

	/**
     * File에서 인자로 받은 Section과 Item의 값을 읽어 오는 함수
     */
    bool GetValue(AnsiString strSection, AnsiString strItem, unsigned long * pnValue);

    /**
     * File에서 인자로 받은 Section과 Item의 값을 읽어 오는 함수
     */
    bool GetValue(AnsiString strSection, AnsiString strItem, double * pdValue);

    /**
     * File에서 인자로 받은 Section과 Item의 값을 읽어 오는 함수
     */
    bool GetValue(AnsiString strSection, AnsiString strItem, AnsiString * pstrValue);

	/**
     * File에서 인자로 받은 Section과 Item의 값을 읽어 오는 함수
     */
    bool GetValue(AnsiString strSection, AnsiString strItem, char * pchValue, UINT nSize);

    /**
     * File에서 인자로 받은 Section과 Item의 값을 읽어 오는 함수
     */
    bool GetValue(AnsiString strSection, AnsiString strItem, TColor * pcValue);


public:
    int SetValuePlus(AnsiString strSection, AnsiString strItem, bool bValue);
    int GetValuePlus(AnsiString strSection, AnsiString strItem, bool * pbValue, bool iDefaultValue = false);

    int SetValuePlus(AnsiString strSection, AnsiString strItem, unsigned short iValue);
    int GetValuePlus(AnsiString strSection, AnsiString strItem, unsigned short * piValue, unsigned short iDefaultValue = 0);

    int SetValuePlus(AnsiString strSection, AnsiString strItem, int iValue);
    int GetValuePlus(AnsiString strSection, AnsiString strItem, int * piValue, int iDefaultValue = 0);

    int SetValuePlus(AnsiString strSection, AnsiString strItem, UINT nValue);
    int GetValuePlus(AnsiString strSection, AnsiString strItem, UINT * pnValue, UINT nDefaultValue = 0);

    int SetValuePlus(AnsiString strSection, AnsiString strItem, long nValue);
    int GetValuePlus(AnsiString strSection, AnsiString strItem, long * pnValue, long nDefaultValue = 0);

    int SetValuePlus(AnsiString strSection, AnsiString strItem, unsigned long nValue);
    int GetValuePlus(AnsiString strSection, AnsiString strItem, unsigned long * pnValue, unsigned long nDefaultValue = 0);

    int SetValuePlus(AnsiString strSection, AnsiString strItem, double dValue);
    int GetValuePlus(AnsiString strSection, AnsiString strItem, double * pdValue, double dDefaultValue = 0.0);

    int SetValuePlus(AnsiString strSection, AnsiString strItem, char *pValue);
    int GetValuePlus(AnsiString strSection, AnsiString strItem, char *pValue, char *pDefault = NULL);
    //int  SetValuePlus(const AnsiString strSection, AnsiString strItem, double dValue);
    //int  GetValuePlus(const AnsiString strSection, AnsiString strItem, double * pdValue, double dDefaultValue = 0.0);

    int SetValuePlus(AnsiString strSection, AnsiString strItem, TColor iValue);
    int GetValuePlus(AnsiString strSection, AnsiString strItem, TColor * piValue, TColor iDefaultValue = clBlack);

    int    SetValuePlus(AnsiString strSection, AnsiString strItem, AnsiString strValue);
    int    GetValuePlus(AnsiString strSection, AnsiString strItem, AnsiString * pstrValue, AnsiString strDefaultValue = "");

    int    Set2xArrayValuePlus(AnsiString strSection, int iRow, int ICol, int iValue[300][300]);
    int    Get2xArrayValuePlus(AnsiString strSection, int iRow, int ICol, int iValue[300][300]);

    int    Set2xArrayValuePlus(AnsiString strSection, int iRow, int ICol, int *piValue);
    int    Get2xArrayValuePlus(AnsiString strSection, int iRow, int ICol, int *piValue);


    int    Set2xArrayValuePlus(AnsiString strSection, int iRow, int ICol, double dValue[300][300]);
    int    Get2xArrayValuePlus(AnsiString strSection, int iRow, int ICol, double dValue[300][300]);

    int    Set2xArrayValuePlus(AnsiString strSection, int iRow, int ICol, double *pdValue);
    int    Get2xArrayValuePlus(AnsiString strSection, int iRow, int ICol, double *pdValue);


    int    Set2xArrayValuePlus(AnsiString strSection, int iRow, int ICol, TColor iValue[300][300]);
    int    Get2xArrayValuePlus(AnsiString strSection, int iRow, int ICol, TColor iValue[300][300]);

    int    Set2xArrayValuePlus(AnsiString strSection, int iRow, int ICol, TColor *piValue);
    int    Get2xArrayValuePlus(AnsiString strSection, int iRow, int ICol, TColor *piValue);


	// wmh
    int    Set1xArrayValuePlus(AnsiString strSection, AnsiString strKey, int iXNum, double dValue[300]);
    int    Get1xArrayValuePlus(AnsiString strSection, AnsiString strKey, int iXNum, double dValue[300]);

    int    Set1xArrayValuePlus(AnsiString strSection, AnsiString strKey, int iXNum, long iValue[300]);
    int    Get1xArrayValuePlus(AnsiString strSection, AnsiString strKey, int iXNum, long iValue[300]);

    int    Set1xArrayValuePlus(AnsiString strSection, AnsiString strKey, int iXNum, unsigned long iValue[300]);
    int    Get1xArrayValuePlus(AnsiString strSection, AnsiString strKey, int iXNum, unsigned long iValue[300]);

    int    Set1xArrayValuePlus(AnsiString strSection, AnsiString strKey, int iXNum, int iValue[300]);
    int    Get1xArrayValuePlus(AnsiString strSection, AnsiString strKey, int iXNum, int iValue[300]);

    int    Set1xArrayValuePlus(AnsiString strSection, AnsiString strKey, int iXNum, unsigned int iValue[300]);
    int    Get1xArrayValuePlus(AnsiString strSection, AnsiString strKey, int iXNum, unsigned int iValue[300]);

    int    Set1xArrayValuePlus(AnsiString strSection, AnsiString strKey, int iXNum, bool bValue[300]);
    int    Get1xArrayValuePlus(AnsiString strSection, AnsiString strKey, int iXNum, bool bValue[300]);

    int    Set1xArrayValuePlus(AnsiString strSection, AnsiString strKey, int iXNum, AnsiString strValue[300]);
    int    Get1xArrayValuePlus(AnsiString strSection, AnsiString strKey, int iXNum, AnsiString strValue[300]);

    int    Set1xArrayValuePlus(AnsiString strSection, AnsiString strKey, int iXNum, TColor iValue[300]);
    int    Get1xArrayValuePlus(AnsiString strSection, AnsiString strKey, int iXNum, TColor iValue[300]);



    bool      DeleteKey(AnsiString strSection, AnsiString strItem);
    bool      DeleteSection(AnsiString strSection);

};

#endif

