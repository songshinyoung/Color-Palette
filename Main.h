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
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TStringGrid *StringGrid1;
    TPanel *Panel1;
    TAZFlowShape *AZFlowShape_Color;
    TPanel *Panel2;
    TPanel *Panel_Color;
    TEdit *Edit_Color;
    TButton *Button_Copy;
    TLabel *Label1;
    TLabel *Label_ColorType;
    TPanel *Panel3;
    TLabel *Label_Pixel_Y;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label6;
    TLabel *Label7;
    TPanel *Panel_SelectPixelColor;
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
    TLabel *Label_Pixel_X;
    TSplitter *Splitter1;
    TPanel *Panel4;
    TImage *Image1;
    TMemo *Memo1;
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



private:	// User declarations
    int nSelectColorIndex;

    TBitmap * m_pBitmapPixelMap;

    bool    m_bMouseDown;
    int     m_nPixelMapX;
    int     m_nPixelMapY;
    int     m_nIntensity;

    void __fastcall DisplayUpdate();
    void __fastcall DisplayUpdatePixelMap(bool bFirst);

    void __fastcall SetPixelMapBySelectColor(TColor clSelectColor);

public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
    TColor m_ColorIndex[200];
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
