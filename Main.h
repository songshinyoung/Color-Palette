//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
#include "AZFlowShape.h"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Buttons.hpp>

#include "MFileManager.h"
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>
//---------------------------------------------------------------------------
class TfmMain : public TForm
{
__published:	// IDE-managed Components
    TStringGrid *StringGrid1;
    TPanel *Panel1;
    TAZFlowShape *AZFlowShape_Color;
    TPanel *Panel2;
    TPanel *Panel3;
    TPanel *Panel5;
    TLabel *Label_Pixel_Y;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label6;
    TLabel *Label7;
    TLabel *Label_Pixel_X;
    TTrackBar *TrackBar_Intensity;
    TEdit *Edit_Pixel_H;
    TEdit *Edit_Pixel_S;
    TEdit *Edit_Pixel_I;
    TEdit *Edit_Pixel_R;
    TEdit *Edit_Pixel_G;
    TEdit *Edit_Pixel_B;
    TEdit *Edit_CodeColor;
    TEdit *Edit_CodeColor2;
    TButton *Button_Copy_Code_1;
    TButton *Button_Copy_Code_2;
    TPanel *Panel4;
    TImage *Image1;
    TStringGrid *StringGrid_Cart;
    TPopupMenu *PopupMenu_Cart;
    TMenuItem *DeleteItem1;
    TPanel *Panel6;
    TPanel *Panel_SelectPixelColor;
    TPanel *Panel7;
    TRadioButton *RadioButton_Type_BG;
    TRadioButton *RadioButton_Type_Front;
    TPanel *Panel8;
    TPanel *Panel_Color;
    TEdit *Edit_Color;
    TLabel *Label_ColorType;
    TPanel *Panel9;
    TButton *Button_Copy;
    TLabel *Label1;
    TSpeedButton *Button_AddCart_1;
    TSpeedButton *Button_AddCart_2;
    TMenuItem *Copy1;
    TMenuItem *DeleteAll1;
    TMenuItem *N1;
    TImage *Image_Intensity;
    TMainMenu *MainMenu1;
    TMenuItem *File1;
    TMenuItem *Open1;
    TMenuItem *Save1;
    TMenuItem *Exit1;
    TOpenTextFileDialog *OpenTextFileDialog1;
    TSaveTextFileDialog *SaveTextFileDialog1;
    TMenuItem *SaveAs1;
    TStatusBar *StatusBar1;
    void __fastcall StringGrid1DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall AZFlowShape_ColorClick(TObject *Sender, int Row, int Col);
    void __fastcall StringGrid1Click(TObject *Sender);
    void __fastcall StringGrid1SelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
    void __fastcall Button_CopyClick(TObject *Sender);
    void __fastcall Image1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
    void __fastcall Image1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
    void __fastcall Image1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall TrackBar_IntensityChange(TObject *Sender);
    void __fastcall Edit_Pixel_HChange(TObject *Sender);
    void __fastcall Button_AddCart_1Click(TObject *Sender);
    void __fastcall StringGrid_CartDrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State);
    void __fastcall StringGrid_CartMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall DeleteItem1Click(TObject *Sender);
    void __fastcall StringGrid_CartClick(TObject *Sender);
    void __fastcall RadioButton_Type_BGClick(TObject *Sender);
    void __fastcall Copy1Click(TObject *Sender);
    void __fastcall Edit_ColorKeyPress(TObject *Sender, System::WideChar &Key);
    void __fastcall DeleteAll1Click(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall Open1Click(TObject *Sender);
    void __fastcall Save1Click(TObject *Sender);
    void __fastcall Exit1Click(TObject *Sender);
    void __fastcall SaveAs1Click(TObject *Sender);
    void __fastcall FormPaint(TObject *Sender);
    void __fastcall WndProc(TMessage &M);


private:	// User declarations
    int     nSelectColorIndex;

    TBitmap * m_pBitmapPixelMap;
    TBitmap * m_pIntensityPixelMap;

    bool    m_bMouseDown;
    int     m_nPixelMapX;
    int     m_nPixelMapY;
    int     m_nIntensity;

    int     m_nRGB_R;
    int     m_nRGB_G;
    int     m_nRGB_B;

    int     m_nCartIndex;

    int     m_nBGColor;
    int     m_nFontColor;

    void __fastcall DisplayUpdate();
    void __fastcall DisplayUpdatePixelMap(bool bFirst);

    void __fastcall SetPixelMapBySelectColor(TColor clSelectColor);

    void __fastcall SetColor_XYI(int nX, int nY, int nI);

    MFileManager * m_pFileManager;

    void __fastcall Load(MFileManager * pFileMng);
    void __fastcall Save(MFileManager * pFileMng);

public:		// User declarations
    __fastcall TfmMain(TComponent* Owner);
    TColor m_ColorIndex[200];
};
//---------------------------------------------------------------------------
extern PACKAGE TfmMain *fmMain;
//---------------------------------------------------------------------------
#endif
