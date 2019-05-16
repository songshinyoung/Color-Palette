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
 * MFileManager Class�� ���Ϸ� ���� Ư�� Item�� ��� ���ų� �ݴ�� Ư�� Item�� ���� ������ �ϴ� Class �̴�.
 */
class MFileManager
{
protected:
    AnsiString          m_strFileName;
    AnsiString          m_strPath;
    AnsiString          m_strFile;
    CRITICAL_SECTION    m_Sync;     // ��ũ�� �ʿ��� ������ �̰ɷ� ���ƾ��Ѵ�. Ư�� AnsiString ������ �ٸ� ������� ���� ������ �� ��� �̰ɷ� ����ȭ �Ѵ�.

    TStringList *       m_pSectionList;
    TStringList *       m_pKeyList;

public:

    /**
     * ������
     */
    MFileManager();

    /**
     * ������ strFileName : �аų� �����ϴ� File �̸�
     */
    MFileManager(AnsiString strFileName);

    /**
     * ������ strFileName : �аų� �����ϴ� File �̸�
     *             strPath : File�� ��θ�
     */
    MFileManager(AnsiString strFileName, AnsiString strPath);

    /**
     * ���� ������
     */
    __fastcall MFileManager(const MFileManager &from);


    void __fastcall Assign(MFileManager *pFrom) ;



    void MFileManagerChangeData(AnsiString strFileName, AnsiString strPath);


    /**
     * �Ҹ���
     */
    virtual ~MFileManager();

	/** File Path�� �ٽ� ���� �ϴ� �Լ� */
    void SetFilePath(AnsiString strPath);

	/** File Path�� �ٽ� ���� �ϴ� �Լ� */
    void SetFileName(AnsiString strFileName);

    TStringList *  GetSectionList();
    TStringList *  GetKeyList(AnsiString strSection);

    AnsiString __fastcall GetFileName()         {return m_strFileName; };
    AnsiString __fastcall GetPath()             {return m_strPath; };
    AnsiString __fastcall GetFileFullPathName() {return m_strFile; };
	/**
     * Backup File�� ����� �Լ�
     */
    bool MakeBackUpFile();

private:
//    bool __fastcall GetIniFile(TIniFile * pFile, bool & bLocalIniCreate);
    AnsiString    m_strTmp;


protected:
    //int SetValue(AnsiString strSection, AnsiString strItem, int nValue, TIniFile * pFile = NULL);

    /**
     * File�� ���ڷ� ���� Section�� Item�� �������� ���� �Լ�
     */
    bool SetValue(AnsiString strSection, AnsiString strItem, unsigned short nValue);


    /**
     * File�� ���ڷ� ���� Section�� Item�� �������� ���� �Լ�
     */
    bool SetValue(AnsiString strSection, AnsiString strItem, int nValue);

	/**
     * File�� ���ڷ� ���� Section�� Item�� �������� ���� �Լ�
     */
    bool SetValue(AnsiString strSection, AnsiString strItem, UINT nValue);

	/**
     * File�� ���ڷ� ���� Section�� Item�� �������� ���� �Լ�
     */
    bool SetValue(AnsiString strSection, AnsiString strItem, long nValue);

	/**
     * File�� ���ڷ� ���� Section�� Item�� �������� ���� �Լ�
     */
    bool SetValue(AnsiString strSection, AnsiString strItem, unsigned long nValue);

    /**
     * File�� ���ڷ� ���� Section�� Item�� �Ǽ����� ���� �Լ�
     */
    bool SetValue(AnsiString strSection, AnsiString strItem, double dValue);

    /**
     * File�� ���ڷ� ���� Section�� Item�� ���ڰ��� ���� �Լ�
     */
    bool SetValue(AnsiString strSection, AnsiString strItem, AnsiString strValue);
	 /**
     * File�� ���ڷ� ���� Section�� Item�� ���ڰ��� ���� �Լ�
     */
    bool SetValue(AnsiString strSection, AnsiString strItem, char* pchValue, UINT nSize);

    /**
     * File�� ���ڷ� ���� Section�� Item�� TColor���� ���� �Լ�
     */
    bool SetValue(AnsiString strSection, AnsiString strItem, TColor cValue);


    /**
     * File���� ���ڷ� ���� Section�� Item�� ���� �о� ���� �Լ�
     */
    bool GetValue(AnsiString strSection, AnsiString strItem, unsigned short * pnValue);

    /**
     * File���� ���ڷ� ���� Section�� Item�� ���� �о� ���� �Լ�
     */
    bool GetValue(AnsiString strSection, AnsiString strItem, int * pnValue);

	/**
     * File���� ���ڷ� ���� Section�� Item�� ���� �о� ���� �Լ�
     */
    bool GetValue(AnsiString strSection, AnsiString strItem, UINT * pnValue);

	/**
     * File���� ���ڷ� ���� Section�� Item�� ���� �о� ���� �Լ�
     */
    bool GetValue(AnsiString strSection, AnsiString strItem, long * pnValue);

	/**
     * File���� ���ڷ� ���� Section�� Item�� ���� �о� ���� �Լ�
     */
    bool GetValue(AnsiString strSection, AnsiString strItem, unsigned long * pnValue);

    /**
     * File���� ���ڷ� ���� Section�� Item�� ���� �о� ���� �Լ�
     */
    bool GetValue(AnsiString strSection, AnsiString strItem, double * pdValue);

    /**
     * File���� ���ڷ� ���� Section�� Item�� ���� �о� ���� �Լ�
     */
    bool GetValue(AnsiString strSection, AnsiString strItem, AnsiString * pstrValue);

	/**
     * File���� ���ڷ� ���� Section�� Item�� ���� �о� ���� �Լ�
     */
    bool GetValue(AnsiString strSection, AnsiString strItem, char * pchValue, UINT nSize);

    /**
     * File���� ���ڷ� ���� Section�� Item�� ���� �о� ���� �Լ�
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

