//---------------------------------------------------------------------------
/*
    Vcl.Graphics.hpp �� ���ǵ� Named Color�� Ȯ���ϴ� �ڵ�.

    ���� : http://docwiki.embarcadero.com/RADStudio/Tokyo/en/Colors_in_the_VCL
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#include <Clipbrd.hpp>

#pragma hdrstop

#include "Main.h"
#include "rgb_hsi.h"

#define MAKE_RGB(R,G,B) ((B)<<16 | (G)<<8 | (R))

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AZFlowShape"
#pragma resource "*.dfm"
TfmMain *fmMain;
//---------------------------------------------------------------------------

__fastcall TfmMain::TfmMain(TComponent* Owner)
    : TForm(Owner)
{
    m_pFileManager = new MFileManager("Config.ini");

    m_nCartIndex = 0;
    nSelectColorIndex = 0;

    m_bMouseDown = false;
    m_nPixelMapX = 0;
    m_nPixelMapY = 240;
    m_nIntensity = 240;


    //----------------------------------
    // Color Map �׸���.
   m_pBitmapPixelMap = new TBitmap();
   m_pBitmapPixelMap->Width  = 240;
   m_pBitmapPixelMap->Height = 240;

    double dH=0, dS=0, dI=0;
    double dR=0, dG=0, dB=0;

    for(int H=0; H<240; H++) {
        for(int S=0; S<240; S++) {
            dH = (double)H/240.0;            // ����
            dS = (double)(240-S) / 240.0;    // ä��
            dI = 1; //(double)(240-S/3) / 240.0;  // ��

            HSI_to_RGB(dH, dS, dI, dR, dG, dB);
            m_pBitmapPixelMap->Canvas->Pixels[H][S] = TColor(((int)dB) << 16  | ((int)dG) << 8 | ((int)dR));
        }
    }

    m_pIntensityPixelMap = new TBitmap();
    m_pIntensityPixelMap->Width  = 10;
    m_pIntensityPixelMap->Height = 240;
    //----------------------------------

    //Image_Intensity->ControlStyle = Image_Intensity->ControlStyle << csOpaque;


    HSI_to_RGB(0, 0, 1, dR, dG, dB);
    m_nRGB_R = dR;
    m_nRGB_G = dG;
    m_nRGB_B = dB;

    m_nBGColor   = (m_nRGB_B << 16 | m_nRGB_G << 8 | m_nRGB_R);
    m_nFontColor = 0x0;

    ZeroMemory(m_ColorIndex, sizeof(m_ColorIndex));

    for(unsigned int i=0; i<ARRAYSIZE(m_ColorIndex); i++) m_ColorIndex[i] = clBlack;

    m_ColorIndex[0]  = clBlack;
    m_ColorIndex[1]  = clMaroon;
    m_ColorIndex[2]  = clGreen;
    m_ColorIndex[3]  = clOlive;
    m_ColorIndex[4]  = clNavy;
    m_ColorIndex[5]  = clPurple;
    m_ColorIndex[6]  = clTeal;
    m_ColorIndex[7]  = clGray;
    m_ColorIndex[8]  = clSilver;
    m_ColorIndex[9]  = clRed;
    m_ColorIndex[10] = clLime;
    m_ColorIndex[11] = clYellow;
    m_ColorIndex[12] = clBlue;
    m_ColorIndex[13] = clFuchsia;
    m_ColorIndex[14] = clAqua;
    m_ColorIndex[15] = clLtGray;
    m_ColorIndex[16] = clDkGray;
    m_ColorIndex[17] = clWhite;
    m_ColorIndex[18] = clMoneyGreen;
    m_ColorIndex[19] = clSkyBlue;
    m_ColorIndex[20] = clCream;
    m_ColorIndex[21] = clMedGray;
    m_ColorIndex[22] = clNone;
    m_ColorIndex[23] = clDefault;

    m_ColorIndex[24]  = clScrollBar;
    m_ColorIndex[25]  = clBackground;
    m_ColorIndex[26]  = clActiveCaption;
    m_ColorIndex[27]  = clInactiveCaption;
    m_ColorIndex[28]  = clMenu;
    m_ColorIndex[29]  = clWindow;
    m_ColorIndex[30]  = clWindowFrame;
    m_ColorIndex[31]  = clMenuText;
    m_ColorIndex[32]  = clWindowText;
    m_ColorIndex[33]  = clCaptionText;
    m_ColorIndex[34] = clActiveBorder;
    m_ColorIndex[35] = clInactiveBorder;
    m_ColorIndex[36] = clAppWorkSpace;
    m_ColorIndex[37] = clHighlight;
    m_ColorIndex[38] = clHighlightText;
    m_ColorIndex[39] = clBtnFace;
    m_ColorIndex[40] = clBtnShadow;
    m_ColorIndex[41] = clGrayText;
    m_ColorIndex[42] = clBtnText;
    m_ColorIndex[43] = clInactiveCaptionText;
    m_ColorIndex[44] = clBtnHighlight;
    m_ColorIndex[45] = cl3DDkShadow;
    m_ColorIndex[46] = cl3DLight;
    m_ColorIndex[47] = clInfoText;
    m_ColorIndex[48] = clInfoBk;
    m_ColorIndex[49] = clHotLight;
    m_ColorIndex[50] = clGradientActiveCaption;
    m_ColorIndex[51] = clGradientInactiveCaption;
    m_ColorIndex[52] = clMenuHighlight;
    m_ColorIndex[53] = clMenuBar;

    m_ColorIndex[54] = clWebSnow;
    m_ColorIndex[55] = clWebFloralWhite;
    m_ColorIndex[56] = clWebLavenderBlush;
    m_ColorIndex[57] = clWebOldLace;
    m_ColorIndex[58] = clWebIvory;
    m_ColorIndex[59] = clWebCornSilk;
    m_ColorIndex[60] = clWebBeige;
    m_ColorIndex[61] = clWebAntiqueWhite;
    m_ColorIndex[62] = clWebWheat;
    m_ColorIndex[63] = clWebAliceBlue;
    m_ColorIndex[64] = clWebGhostWhite;
    m_ColorIndex[65] = clWebLavender;
    m_ColorIndex[66] = clWebSeashell;
    m_ColorIndex[67] = clWebLightYellow;
    m_ColorIndex[68] = clWebPapayaWhip;
    m_ColorIndex[69] = clWebNavajoWhite;
    m_ColorIndex[70] = clWebMoccasin;
    m_ColorIndex[71] = clWebBurlywood;
    m_ColorIndex[72] = clWebAzure;
    m_ColorIndex[73] = clWebMintcream;
    m_ColorIndex[74] = clWebHoneydew;
    m_ColorIndex[75] = clWebLinen;
    m_ColorIndex[76] = clWebLemonChiffon;
    m_ColorIndex[77] = clWebBlanchedAlmond;
    m_ColorIndex[78] = clWebBisque;
    m_ColorIndex[79] = clWebPeachPuff;
    m_ColorIndex[80] = clWebTan;
    m_ColorIndex[81] = clWebYellow;
    m_ColorIndex[82] = clWebDarkOrange;
    m_ColorIndex[83] = clWebRed;
    m_ColorIndex[84] = clWebDarkRed;
    m_ColorIndex[85] = clWebMaroon;
    m_ColorIndex[86] = clWebIndianRed;
    m_ColorIndex[87] = clWebSalmon;
    m_ColorIndex[88] = clWebCoral;
    m_ColorIndex[89] = clWebGold;
    m_ColorIndex[90] = clWebTomato;
    m_ColorIndex[91] = clWebCrimson;
    m_ColorIndex[92] = clWebBrown;
    m_ColorIndex[93] = clWebChocolate;
    m_ColorIndex[94] = clWebSandyBrown;
    m_ColorIndex[95] = clWebLightSalmon;
    m_ColorIndex[96] = clWebLightCoral;
    m_ColorIndex[97] = clWebOrange;
    m_ColorIndex[98] = clWebOrangeRed;
    m_ColorIndex[99] = clWebFirebrick;
    m_ColorIndex[100] = clWebSaddleBrown;
    m_ColorIndex[101] = clWebSienna;
    m_ColorIndex[102] = clWebPeru;
    m_ColorIndex[103] = clWebDarkSalmon;
    m_ColorIndex[104] = clWebRosyBrown;
    m_ColorIndex[105] = clWebPaleGoldenrod;
    m_ColorIndex[106] = clWebLightGoldenrodYellow;
    m_ColorIndex[107] = clWebOlive;
    m_ColorIndex[108] = clWebForestGreen;
    m_ColorIndex[109] = clWebGreenYellow;
    m_ColorIndex[110] = clWebChartreuse;
    m_ColorIndex[111] = clWebLightGreen;
    m_ColorIndex[112] = clWebAquamarine;
    m_ColorIndex[113] = clWebSeaGreen;
    m_ColorIndex[114] = clWebGoldenRod;
    m_ColorIndex[115] = clWebKhaki;
    m_ColorIndex[116] = clWebOliveDrab;
    m_ColorIndex[117] = clWebGreen;
    m_ColorIndex[118] = clWebYellowGreen;
    m_ColorIndex[119] = clWebLawnGreen;
    m_ColorIndex[120] = clWebPaleGreen;
    m_ColorIndex[121] = clWebMediumAquamarine;
    m_ColorIndex[122] = clWebMediumSeaGreen;
    m_ColorIndex[123] = clWebDarkGoldenRod;
    m_ColorIndex[124] = clWebDarkKhaki;
    m_ColorIndex[125] = clWebDarkOliveGreen;
    m_ColorIndex[126] = clWebDarkgreen;
    m_ColorIndex[127] = clWebLimeGreen;
    m_ColorIndex[128] = clWebLime;
    m_ColorIndex[129] = clWebSpringGreen;
    m_ColorIndex[130] = clWebMediumSpringGreen;
    m_ColorIndex[131] = clWebDarkSeaGreen;
    m_ColorIndex[132] = clWebLightSeaGreen;
    m_ColorIndex[133] = clWebPaleTurquoise;
    m_ColorIndex[134] = clWebLightCyan;
    m_ColorIndex[135] = clWebLightBlue;
    m_ColorIndex[136] = clWebLightSkyBlue;
    m_ColorIndex[137] = clWebCornFlowerBlue;
    m_ColorIndex[138] = clWebDarkBlue;
    m_ColorIndex[139] = clWebIndigo;
    m_ColorIndex[140] = clWebMediumTurquoise;
    m_ColorIndex[141] = clWebTurquoise;
    m_ColorIndex[142] = clWebCyan;
    m_ColorIndex[143] = clWebAqua;
    m_ColorIndex[144] = clWebPowderBlue;
    m_ColorIndex[145] = clWebSkyBlue;
    m_ColorIndex[146] = clWebRoyalBlue;
    m_ColorIndex[147] = clWebMediumBlue;
    m_ColorIndex[148] = clWebMidnightBlue;
    m_ColorIndex[149] = clWebDarkTurquoise;
    m_ColorIndex[150] = clWebCadetBlue;
    m_ColorIndex[151] = clWebDarkCyan;
    m_ColorIndex[152] = clWebTeal;
    m_ColorIndex[153] = clWebDeepskyBlue;
    m_ColorIndex[154] = clWebDodgerBlue;
    m_ColorIndex[155] = clWebBlue;
    m_ColorIndex[156] = clWebNavy;
    m_ColorIndex[157] = clWebDarkViolet;
    m_ColorIndex[158] = clWebDarkOrchid;
    m_ColorIndex[159] = clWebMagenta;
    m_ColorIndex[160] = clWebFuchsia;
    m_ColorIndex[161] = clWebDarkMagenta;
    m_ColorIndex[162] = clWebMediumVioletRed;
    m_ColorIndex[163] = clWebPaleVioletRed;
    m_ColorIndex[164] = clWebBlueViolet;
    m_ColorIndex[165] = clWebMediumOrchid;
    m_ColorIndex[166] = clWebMediumPurple;
    m_ColorIndex[167] = clWebPurple;
    m_ColorIndex[168] = clWebDeepPink;
    m_ColorIndex[169] = clWebLightPink;
    m_ColorIndex[170] = clWebViolet;
    m_ColorIndex[171] = clWebOrchid;
    m_ColorIndex[172] = clWebPlum;
    m_ColorIndex[173] = clWebThistle;
    m_ColorIndex[174] = clWebHotPink;
    m_ColorIndex[175] = clWebPink;
    m_ColorIndex[176] = clWebLightSteelBlue;
    m_ColorIndex[177] = clWebMediumSlateBlue;
    m_ColorIndex[178] = clWebLightSlateGray;
    m_ColorIndex[179] = clWebWhite;
    m_ColorIndex[180] = clWebLightgrey;
    m_ColorIndex[181] = clWebGray;
    m_ColorIndex[182] = clWebSteelBlue;
    m_ColorIndex[183] = clWebSlateBlue;
    m_ColorIndex[184] = clWebSlateGray;
    m_ColorIndex[185] = clWebWhiteSmoke;
    m_ColorIndex[186] = clWebSilver;
    m_ColorIndex[187] = clWebDimGray;
    m_ColorIndex[188] = clWebMistyRose;
    m_ColorIndex[189] = clWebDarkSlateBlue;
    m_ColorIndex[190] = clWebDarkSlategray;
    m_ColorIndex[191] = clWebGainsboro;
    m_ColorIndex[192] = clWebDarkGray;
    m_ColorIndex[193] = clWebBlack;

}
//---------------------------------------------------------------------------

void __fastcall TfmMain::FormDestroy(TObject *Sender)
{
    if(m_pBitmapPixelMap)   delete m_pBitmapPixelMap;
    if(m_pIntensityPixelMap)delete m_pIntensityPixelMap;
    if(m_pFileManager)      delete m_pFileManager;
}


//---------------------------------------------------------------------------
void __fastcall TfmMain::FormShow(TObject *Sender)
{
    StringGrid1->Cells[1][1] = "test";

    for(int i=1; i<StringGrid1->RowCount; i++) StringGrid1->Cells[0][i] = i;

    StringGrid1->Cells[0][0] = "No.";
    StringGrid1->Cells[1][0] = "Color Name";
    StringGrid1->Cells[2][0] = "Color";

    StringGrid1->Cells[1][1]  = "clBlack";
    StringGrid1->Cells[1][2]  = "clMaroon";
    StringGrid1->Cells[1][3]  = "clGreen";
    StringGrid1->Cells[1][4]  = "clOlive";
    StringGrid1->Cells[1][5]  = "clNavy";
    StringGrid1->Cells[1][6]  = "clPurple";
    StringGrid1->Cells[1][7]  = "clTeal";
    StringGrid1->Cells[1][8]  = "clGray";
    StringGrid1->Cells[1][9]  = "clSilver";
    StringGrid1->Cells[1][10] = "clRed";
    StringGrid1->Cells[1][11] = "clLime";
    StringGrid1->Cells[1][12] = "clYellow";
    StringGrid1->Cells[1][13] = "clBlue";
    StringGrid1->Cells[1][14] = "clFuchsia";
    StringGrid1->Cells[1][15] = "clAqua";
    StringGrid1->Cells[1][16] = "clLtGray";
    StringGrid1->Cells[1][17] = "clDkGray";
    StringGrid1->Cells[1][18] = "clWhite";
    StringGrid1->Cells[1][19] = "clMoneyGreen";
    StringGrid1->Cells[1][20] = "clSkyBlue";
    StringGrid1->Cells[1][21] = "clCream";
    StringGrid1->Cells[1][22] = "clMedGray";
    StringGrid1->Cells[1][23] = "clNone";
    StringGrid1->Cells[1][24] = "clDefault";
    StringGrid1->Cells[1][25] = "clScrollBar";
    StringGrid1->Cells[1][26] = "clBackground";
    StringGrid1->Cells[1][27] = "clActiveCaption";
    StringGrid1->Cells[1][28] = "clInactiveCaption";
    StringGrid1->Cells[1][29] = "clMenu";
    StringGrid1->Cells[1][30] = "clWindow";
    StringGrid1->Cells[1][31] = "clWindowFrame";
    StringGrid1->Cells[1][32] = "clMenuText";
    StringGrid1->Cells[1][33] = "clWindowText";
    StringGrid1->Cells[1][34] = "clCaptionText";
    StringGrid1->Cells[1][35] = "clActiveBorder";
    StringGrid1->Cells[1][36] = "clInactiveBorder";
    StringGrid1->Cells[1][37] = "clAppWorkSpace";
    StringGrid1->Cells[1][38] = "clHighlight";
    StringGrid1->Cells[1][39] = "clHighlightText";
    StringGrid1->Cells[1][40] = "clBtnFace";
    StringGrid1->Cells[1][41] = "clBtnShadow";
    StringGrid1->Cells[1][42] = "clGrayText";
    StringGrid1->Cells[1][43] = "clBtnText";
    StringGrid1->Cells[1][44] = "clInactiveCaptionText";
    StringGrid1->Cells[1][45] = "clBtnHighlight";
    StringGrid1->Cells[1][46] = "cl3DDkShadow";
    StringGrid1->Cells[1][47] = "cl3DLight";
    StringGrid1->Cells[1][48] = "clInfoText";
    StringGrid1->Cells[1][49] = "clInfoBk";
    StringGrid1->Cells[1][50] = "clHotLight";
    StringGrid1->Cells[1][51] = "clGradientActiveCaption";
    StringGrid1->Cells[1][52] = "clGradientInactiveCaption";
    StringGrid1->Cells[1][53] = "clMenuHighlight";
    StringGrid1->Cells[1][54] = "clMenuBar";

    StringGrid1->Cells[1][55] = "clWebSnow";
    StringGrid1->Cells[1][56] = "clWebFloralWhite";
    StringGrid1->Cells[1][57] = "clWebLavenderBlush";
    StringGrid1->Cells[1][58] = "clWebOldLace";
    StringGrid1->Cells[1][59] = "clWebIvory";
    StringGrid1->Cells[1][60] = "clWebCornSilk";
    StringGrid1->Cells[1][61] = "clWebBeige";
    StringGrid1->Cells[1][62] = "clWebAntiqueWhite";
    StringGrid1->Cells[1][63] = "clWebWheat";
    StringGrid1->Cells[1][64] = "clWebAliceBlue";
    StringGrid1->Cells[1][65] = "clWebGhostWhite";
    StringGrid1->Cells[1][66] = "clWebLavender";
    StringGrid1->Cells[1][67] = "clWebSeashell";
    StringGrid1->Cells[1][68] = "clWebLightYellow";
    StringGrid1->Cells[1][69] = "clWebPapayaWhip";
    StringGrid1->Cells[1][70] = "clWebNavajoWhite";
    StringGrid1->Cells[1][71] = "clWebMoccasin";
    StringGrid1->Cells[1][72] = "clWebBurlywood";
    StringGrid1->Cells[1][73] = "clWebAzure";
    StringGrid1->Cells[1][74] = "clWebMintcream";
    StringGrid1->Cells[1][75] = "clWebHoneydew";
    StringGrid1->Cells[1][76] = "clWebLinen";
    StringGrid1->Cells[1][77] = "clWebLemonChiffon";
    StringGrid1->Cells[1][78] = "clWebBlanchedAlmond";
    StringGrid1->Cells[1][79] = "clWebBisque";
    StringGrid1->Cells[1][80] = "clWebPeachPuff";
    StringGrid1->Cells[1][81] = "clWebTan";
    StringGrid1->Cells[1][82] = "clWebYellow";
    StringGrid1->Cells[1][83] = "clWebDarkOrange";
    StringGrid1->Cells[1][84] = "clWebRed";
    StringGrid1->Cells[1][85] = "clWebDarkRed";
    StringGrid1->Cells[1][86] = "clWebMaroon";
    StringGrid1->Cells[1][87] = "clWebIndianRed";
    StringGrid1->Cells[1][88] = "clWebSalmon";
    StringGrid1->Cells[1][89] = "clWebCoral";
    StringGrid1->Cells[1][90] = "clWebGold";
    StringGrid1->Cells[1][91] = "clWebTomato";
    StringGrid1->Cells[1][92] = "clWebCrimson";
    StringGrid1->Cells[1][93] = "clWebBrown";
    StringGrid1->Cells[1][94] = "clWebChocolate";
    StringGrid1->Cells[1][95] = "clWebSandyBrown";
    StringGrid1->Cells[1][96] = "clWebLightSalmon";
    StringGrid1->Cells[1][97] = "clWebLightCoral";
    StringGrid1->Cells[1][98] = "clWebOrange";
    StringGrid1->Cells[1][99] = "clWebOrangeRed";
    StringGrid1->Cells[1][100] = "clWebFirebrick";
    StringGrid1->Cells[1][101] = "clWebSaddleBrown";
    StringGrid1->Cells[1][102] = "clWebSienna";
    StringGrid1->Cells[1][103] = "clWebPeru";
    StringGrid1->Cells[1][104] = "clWebDarkSalmon";
    StringGrid1->Cells[1][105] = "clWebRosyBrown";
    StringGrid1->Cells[1][106] = "clWebPaleGoldenrod";
    StringGrid1->Cells[1][107] = "clWebLightGoldenrodYellow";
    StringGrid1->Cells[1][108] = "clWebOlive";
    StringGrid1->Cells[1][109] = "clWebForestGreen";
    StringGrid1->Cells[1][110] = "clWebGreenYellow";
    StringGrid1->Cells[1][111] = "clWebChartreuse";
    StringGrid1->Cells[1][112] = "clWebLightGreen";
    StringGrid1->Cells[1][113] = "clWebAquamarine";
    StringGrid1->Cells[1][114] = "clWebSeaGreen";
    StringGrid1->Cells[1][115] = "clWebGoldenRod";
    StringGrid1->Cells[1][116] = "clWebKhaki";
    StringGrid1->Cells[1][117] = "clWebOliveDrab";
    StringGrid1->Cells[1][118] = "clWebGreen";
    StringGrid1->Cells[1][119] = "clWebYellowGreen";
    StringGrid1->Cells[1][120] = "clWebLawnGreen";
    StringGrid1->Cells[1][121] = "clWebPaleGreen";
    StringGrid1->Cells[1][122] = "clWebMediumAquamarine";
    StringGrid1->Cells[1][123] = "clWebMediumSeaGreen";
    StringGrid1->Cells[1][124] = "clWebDarkGoldenRod";
    StringGrid1->Cells[1][125] = "clWebDarkKhaki";
    StringGrid1->Cells[1][126] = "clWebDarkOliveGreen";
    StringGrid1->Cells[1][127] = "clWebDarkgreen";
    StringGrid1->Cells[1][128] = "clWebLimeGreen";
    StringGrid1->Cells[1][129] = "clWebLime";
    StringGrid1->Cells[1][130] = "clWebSpringGreen";
    StringGrid1->Cells[1][131] = "clWebMediumSpringGreen";
    StringGrid1->Cells[1][132] = "clWebDarkSeaGreen";
    StringGrid1->Cells[1][133] = "clWebLightSeaGreen";
    StringGrid1->Cells[1][134] = "clWebPaleTurquoise";
    StringGrid1->Cells[1][135] = "clWebLightCyan";
    StringGrid1->Cells[1][136] = "clWebLightBlue";
    StringGrid1->Cells[1][137] = "clWebLightSkyBlue";
    StringGrid1->Cells[1][138] = "clWebCornFlowerBlue";
    StringGrid1->Cells[1][139] = "clWebDarkBlue";
    StringGrid1->Cells[1][140] = "clWebIndigo";
    StringGrid1->Cells[1][141] = "clWebMediumTurquoise";
    StringGrid1->Cells[1][142] = "clWebTurquoise";
    StringGrid1->Cells[1][143] = "clWebCyan";
    StringGrid1->Cells[1][144] = "clWebAqua";
    StringGrid1->Cells[1][145] = "clWebPowderBlue";
    StringGrid1->Cells[1][146] = "clWebSkyBlue";
    StringGrid1->Cells[1][147] = "clWebRoyalBlue";
    StringGrid1->Cells[1][148] = "clWebMediumBlue";
    StringGrid1->Cells[1][149] = "clWebMidnightBlue";
    StringGrid1->Cells[1][150] = "clWebDarkTurquoise";
    StringGrid1->Cells[1][151] = "clWebCadetBlue";
    StringGrid1->Cells[1][152] = "clWebDarkCyan";
    StringGrid1->Cells[1][153] = "clWebTeal";
    StringGrid1->Cells[1][154] = "clWebDeepskyBlue";
    StringGrid1->Cells[1][155] = "clWebDodgerBlue";
    StringGrid1->Cells[1][156] = "clWebBlue";
    StringGrid1->Cells[1][157] = "clWebNavy";
    StringGrid1->Cells[1][158] = "clWebDarkViolet";
    StringGrid1->Cells[1][159] = "clWebDarkOrchid";
    StringGrid1->Cells[1][160] = "clWebMagenta";
    StringGrid1->Cells[1][161] = "clWebFuchsia";
    StringGrid1->Cells[1][162] = "clWebDarkMagenta";
    StringGrid1->Cells[1][163] = "clWebMediumVioletRed";
    StringGrid1->Cells[1][164] = "clWebPaleVioletRed";
    StringGrid1->Cells[1][165] = "clWebBlueViolet";
    StringGrid1->Cells[1][166] = "clWebMediumOrchid";
    StringGrid1->Cells[1][167] = "clWebMediumPurple";
    StringGrid1->Cells[1][168] = "clWebPurple";
    StringGrid1->Cells[1][169] = "clWebDeepPink";
    StringGrid1->Cells[1][170] = "clWebLightPink";
    StringGrid1->Cells[1][171] = "clWebViolet";
    StringGrid1->Cells[1][172] = "clWebOrchid";
    StringGrid1->Cells[1][173] = "clWebPlum";
    StringGrid1->Cells[1][174] = "clWebThistle";
    StringGrid1->Cells[1][175] = "clWebHotPink";
    StringGrid1->Cells[1][176] = "clWebPink";
    StringGrid1->Cells[1][177] = "clWebLightSteelBlue";
    StringGrid1->Cells[1][178] = "clWebMediumSlateBlue";
    StringGrid1->Cells[1][179] = "clWebLightSlateGray";
    StringGrid1->Cells[1][180] = "clWebWhite";
    StringGrid1->Cells[1][181] = "clWebLightgrey";
    StringGrid1->Cells[1][182] = "clWebGray";
    StringGrid1->Cells[1][183] = "clWebSteelBlue";
    StringGrid1->Cells[1][184] = "clWebSlateBlue";
    StringGrid1->Cells[1][185] = "clWebSlateGray";
    StringGrid1->Cells[1][186] = "clWebWhiteSmoke";
    StringGrid1->Cells[1][187] = "clWebSilver";
    StringGrid1->Cells[1][188] = "clWebDimGray";
    StringGrid1->Cells[1][189] = "clWebMistyRose";
    StringGrid1->Cells[1][190] = "clWebDarkSlateBlue";
    StringGrid1->Cells[1][191] = "clWebDarkSlategray";
    StringGrid1->Cells[1][192] = "clWebGainsboro";
    StringGrid1->Cells[1][193] = "clWebDarkGray";
    StringGrid1->Cells[1][194] = "clWebBlack";
    StringGrid1->Cells[1][195] = "clWebBlack";
    StringGrid1->Cells[1][196] = "clWebBlack";
    StringGrid1->Cells[1][197] = "clWebBlack";
    StringGrid1->Cells[1][198] = "clWebBlack";
    StringGrid1->Cells[1][199] = "clWebBlack";
    StringGrid1->Cells[1][200] = "clWebBlack";

    for(int y=0; y<AZFlowShape_Color->AZ_Row; y++) {
        for(int x=0; x<AZFlowShape_Color->AZ_Col; x++) {
            int nIdx = y*AZFlowShape_Color->AZ_Col + x;
            //if(nIdx<194) {
                AZFlowShape_Color->Cells[y][x]->BGColor = m_ColorIndex[nIdx];
            //}
            //else {
            //    AZFlowShape_Color->Cells[y][x]->BGColor = clBlack;
            //}
        }
    }

    Image1->Picture->Bitmap->Width  = 240;
    Image1->Picture->Bitmap->Height = 240;

    Image_Intensity->Picture->Bitmap->Width  = 10;
    Image_Intensity->Picture->Bitmap->Height = 240;

    StringGrid_Cart->Cells[0][0] = "No.";
    StringGrid_Cart->Cells[1][0] = "Memo";
    StringGrid_Cart->Cells[2][0] = "Color Name";
    StringGrid_Cart->Cells[3][0] = "Color Value";

    for(int row=1; row<StringGrid_Cart->RowCount; row++) {
        StringGrid_Cart->Cells[0][row] = row;
    }

    DisplayUpdatePixelMap(true);
    DisplayUpdate();
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::StringGrid1DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State)
{
    Rect.Left -= 4;
// �� �׸���
    // ���� ���� ��ư �������
    if(State.Contains(gdFixed)) {
        StringGrid1->Canvas->Brush->Color = clBtnFace;
        StringGrid1->Canvas->Font->Color = clWindowText;
        StringGrid1->Canvas->FillRect(Rect);
        Frame3D(StringGrid1->Canvas, Rect, clBtnHighlight, clBtnShadow, 1);
    }
//    // ���õ� ���� ���̶���Ʈ ��
//    else if (State.Contains(gdSelected))
//    {
//        StringGrid1->Canvas->Brush->Color = clHighlight;
//        StringGrid1->Canvas->Font->Color = clHighlightText;
//        StringGrid1->Canvas->FillRect(Rect);
//    }
    // ������ ���� �⺻ ������
    else
    {
        if(ACol == 2)                       StringGrid1->Canvas->Brush->Color = m_ColorIndex[ARow-1];
        else if(State.Contains(gdSelected)) StringGrid1->Canvas->Brush->Color = clMenuHighlight;
        else if(ARow <= 24)                 StringGrid1->Canvas->Brush->Color = StringGrid1->Color;
        else if(ARow <= 54)                 StringGrid1->Canvas->Brush->Color = clWebBeige;
        else                                StringGrid1->Canvas->Brush->Color = StringGrid1->Color;

        StringGrid1->Canvas->Font->Color = StringGrid1->Font->Color;
        StringGrid1->Canvas->FillRect(Rect);
    }

// �� ����(�ؽ�Ʈ) ���
    StringGrid1->Canvas->TextRect(Rect, Rect.Left+2, Rect.Top + 3, StringGrid1->Cells[ACol][ARow]);

}
//----------------------------------------------------------------------
void __fastcall TfmMain::AZFlowShape_ColorClick(TObject *Sender, int Row, int Col)
{
    int nIdx = Row * AZFlowShape_Color->AZ_Col + Col;

    nSelectColorIndex = nIdx;
    nSelectColorIndex = nSelectColorIndex < 0 ? 0 : nSelectColorIndex;
    nSelectColorIndex = nSelectColorIndex >= 200 ? 199 : nSelectColorIndex;

    StringGrid1->Row = nSelectColorIndex + 1;

    SetPixelMapBySelectColor(m_ColorIndex[nSelectColorIndex]);

    StringGrid1->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfmMain::StringGrid1Click(TObject *Sender)
{
    nSelectColorIndex = StringGrid1->Selection.Top - 1;

    nSelectColorIndex = nSelectColorIndex < 0 ? 0 : nSelectColorIndex;
    nSelectColorIndex = nSelectColorIndex >= 200 ? 199 : nSelectColorIndex;

    SetPixelMapBySelectColor(m_ColorIndex[nSelectColorIndex]);

    DisplayUpdate();
}
//---------------------------------------------------------------------------

void __fastcall TfmMain::Edit_ColorKeyPress(TObject *Sender, System::WideChar &Key)
{
    if(Key == VK_RETURN) {
        String sColor = Edit_Color->Text.Trim();

        for(int i=1; i<StringGrid1->RowCount; i++) {
            if(StringGrid1->Cells[1][i] == sColor) {
                nSelectColorIndex = i - 1;
                SetPixelMapBySelectColor(m_ColorIndex[nSelectColorIndex]);
                StringGrid1->Row = i;
            }
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TfmMain::DisplayUpdate()
{
    for(int y=0; y<AZFlowShape_Color->AZ_Row; y++) {
        for(int x=0; x<AZFlowShape_Color->AZ_Col; x++) {
            int nIdx = y*AZFlowShape_Color->AZ_Col + x;
            if(nSelectColorIndex == nIdx) {
                AZFlowShape_Color->Cells[y][x]->LineColor = clBlack;
            }
            else {
                AZFlowShape_Color->Cells[y][x]->LineColor = clWhite;
            }
        }
    }

    if(nSelectColorIndex >= 0 && nSelectColorIndex < 200) {
        Panel_Color->Color = m_ColorIndex[nSelectColorIndex];
        Edit_Color->Text = StringGrid1->Cells[1][nSelectColorIndex+1];
    }
    else {
        Panel_Color->Color = clBlack;
        Edit_Color->Text = "clBlack";
    }

    TNotifyEvent OnClickEventTemp = StringGrid1->OnClick;
    StringGrid1->OnClick = NULL;
    StringGrid1->Row = nSelectColorIndex + 1;
    StringGrid1->OnClick = OnClickEventTemp;

    if(nSelectColorIndex < 24) {
        Label_ColorType->Caption = "Normal Colors";
    }
    else if(nSelectColorIndex < 54) {
        Label_ColorType->Caption = "System Colors";
    }
    else {
        Label_ColorType->Caption = "Web Colors";
    }

    if(m_pFileManager) {
        StatusBar1->Panels->Items[1]->Text = m_pFileManager->GetFileFullPathName();
    }

}
//---------------------------------------------------------------------------
void __fastcall TfmMain::DisplayUpdatePixelMap(bool bFirst)
{
    double dH=0, dS=0, dI=0;
    double dR=0, dG=0, dB=0;

    if(bFirst) {
        Image1->Picture->Bitmap->Assign(m_pBitmapPixelMap);
    }

    // �� Trackbar �׸���
    //m_pIntensityPixelMap->Canvas->Brush->Style = bsSolid;
    for(int i=0; i<24; i++) {
        HSI_to_RGB((double)m_nPixelMapX/240.0, (double)(240-m_nPixelMapY)/240.0, (double)(i*10)/240.0, dR, dG, dB);
        m_pIntensityPixelMap->Canvas->Pen->Color   = TColor(((int)dB) << 16  | ((int)dG) << 8 | ((int)dR));
        m_pIntensityPixelMap->Canvas->Brush->Color = m_pIntensityPixelMap->Canvas->Pen->Color;
        m_pIntensityPixelMap->Canvas->FillRect(Rect(0, i*10, m_pIntensityPixelMap->Width, i*10 + 10));
        //Image_Intensity->Canvas->MoveTo(0, i);
        //Image_Intensity->Canvas->LineTo(Image_Intensity->Width, i);
    }

    //m_pIntensityPixelMap->Canvas->Pen->Color   = clGray;
    //m_pIntensityPixelMap->Canvas->Brush->Style = bsClear;
    //m_pIntensityPixelMap->Canvas->Rectangle(0,0,m_pIntensityPixelMap->Width, m_pIntensityPixelMap->Height);
    Image_Intensity->Picture->Bitmap->Assign(m_pIntensityPixelMap);


    // Ŀ�� �׸���
    TCanvas * pCanvas = Image1->Picture->Bitmap->Canvas;

    if(m_bMouseDown == false) {

        pCanvas->Pen->Width = 1;
        pCanvas->Pen->Color = TColor((255-m_nRGB_B) << 16  | (255-m_nRGB_G) << 8 | (255-m_nRGB_R));
        pCanvas->MoveTo(m_nPixelMapX-2, m_nPixelMapY);
        pCanvas->LineTo(m_nPixelMapX-5, m_nPixelMapY);
        pCanvas->MoveTo(m_nPixelMapX+2,   m_nPixelMapY);
        pCanvas->LineTo(m_nPixelMapX+5, m_nPixelMapY);
        pCanvas->MoveTo(m_nPixelMapX,   m_nPixelMapY-2);
        pCanvas->LineTo(m_nPixelMapX,   m_nPixelMapY-5);
        pCanvas->MoveTo(m_nPixelMapX,   m_nPixelMapY+2);
        pCanvas->LineTo(m_nPixelMapX,   m_nPixelMapY+5);


        System::Classes::TNotifyEvent pOnChange = TrackBar_Intensity->OnChange;
        TrackBar_Intensity->OnChange = NULL;
        TrackBar_Intensity->Position = m_nIntensity;
        TrackBar_Intensity->OnChange = pOnChange;

    }

    Label_Pixel_X->Caption = "X : " + IntToStr(m_nPixelMapX);
    Label_Pixel_Y->Caption = "Y : " + IntToStr(m_nPixelMapY);

    // ���� ���õ� ���󿡼� ���� �߰��Ͽ� ���� ǥ��
    dH = (double)m_nPixelMapX / 240.0;          // ����
    dS = (double)(240-m_nPixelMapY) / 240.0;    // ä��
    dI = (double)(m_nIntensity) / 240.0;        // ��

    //HSI_to_RGB(dH, dS, dI, dR, dG, dB);
    //Panel_SelectPixelColor->Color = TColor(((int)dB) << 16  | ((int)dG) << 8 | ((int)dR));
//    if(RadioButton_Type_BG->Checked) {
//        Panel_SelectPixelColor->Color = TColor((m_nRGB_B) << 16  | (m_nRGB_G) << 8 | (m_nRGB_R));
//    }
//    else {
//        Panel_SelectPixelColor->Font->Color = TColor((m_nRGB_B) << 16  | (m_nRGB_G) << 8 | (m_nRGB_R));
//    }

    Panel_SelectPixelColor->Color       = (TColor)m_nBGColor;
    Panel_SelectPixelColor->Font->Color = (TColor)m_nFontColor;


    Edit_Pixel_H->OnChange   = NULL;
    Edit_Pixel_S->OnChange   = NULL;
    Edit_Pixel_I->OnChange   = NULL;
    Edit_Pixel_R->OnChange   = NULL;
    Edit_Pixel_G->OnChange   = NULL;
    Edit_Pixel_B->OnChange   = NULL;
    Edit_CodeColor->OnChange = NULL;
    Edit_CodeColor2->OnChange =NULL;

    Edit_Pixel_H->Text = m_nPixelMapX;
    Edit_Pixel_S->Text = 240-m_nPixelMapY;
    Edit_Pixel_I->Text = m_nIntensity;

    Edit_Pixel_R->Text = m_nRGB_R;
    Edit_Pixel_G->Text = m_nRGB_G;
    Edit_Pixel_B->Text = m_nRGB_B;

    Edit_Pixel_R->Color = (TColor)MAKE_RGB(m_nRGB_R, 0, 0);
    Edit_Pixel_G->Color = (TColor)MAKE_RGB(0, m_nRGB_G, 0);
    Edit_Pixel_B->Color = (TColor)MAKE_RGB(0, 0, m_nRGB_B);



    AnsiString sMsg;

    if(Edit_CodeColor->Focused() != true) {
        sMsg.printf("0x%02X%02X%02X", (int)m_nRGB_B, (int)m_nRGB_G, (int)m_nRGB_R);
        Edit_CodeColor->Text = sMsg;
    }

    sMsg.printf("$00%02X%02X%02X", (int)m_nRGB_B, (int)m_nRGB_G, (int)m_nRGB_R);
    Edit_CodeColor2->Text = sMsg;

    Edit_Pixel_H->OnChange   = Edit_Pixel_HChange;
    Edit_Pixel_S->OnChange   = Edit_Pixel_HChange;
    Edit_Pixel_I->OnChange   = Edit_Pixel_HChange;
    Edit_Pixel_R->OnChange   = Edit_Pixel_HChange;
    Edit_Pixel_G->OnChange   = Edit_Pixel_HChange;
    Edit_Pixel_B->OnChange   = Edit_Pixel_HChange;
    Edit_CodeColor->OnChange = Edit_Pixel_HChange;
    Edit_CodeColor2->OnChange =Edit_Pixel_HChange;


}
//---------------------------------------------------------------------------
void __fastcall TfmMain::StringGrid1SelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TfmMain::Button_CopyClick(TObject *Sender)
{
    TButton * pBtn = dynamic_cast<TButton *>(Sender);

    if(pBtn == NULL) return;

    switch(pBtn->Tag) {
        case 1:
            Edit_Color->SelectAll();
            Edit_Color->CopyToClipboard();
            break;

        case 2:
            Edit_CodeColor->SelectAll();
            Edit_CodeColor->CopyToClipboard();
            break;

        case 3:
            Edit_CodeColor2->SelectAll();
            Edit_CodeColor2->CopyToClipboard();
            break;
    }

}
//---------------------------------------------------------------------------


void __fastcall TfmMain::Image1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
    if(Button != mbLeft) return;

    m_bMouseDown = true;

    SetColor_XYI(X, Y, m_nIntensity);

    DisplayUpdatePixelMap(true);

    StringGrid1->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfmMain::Image1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
    if(m_bMouseDown) {
        m_bMouseDown = false;
        DisplayUpdatePixelMap(false);
    }

}
//---------------------------------------------------------------------------

void __fastcall TfmMain::Image1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
    if(m_bMouseDown) {
        SetColor_XYI(X, Y, m_nIntensity);

        DisplayUpdatePixelMap(false);
    }

}
//---------------------------------------------------------------------------


void __fastcall TfmMain::TrackBar_IntensityChange(TObject *Sender)
{
    m_nIntensity = TrackBar_Intensity->Position;

    SetColor_XYI(m_nPixelMapX, m_nPixelMapY, m_nIntensity);

    DisplayUpdatePixelMap(false);
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::SetColor_XYI(int nX, int nY, int nI)
{
    m_nPixelMapX = nX;
    m_nPixelMapY = nY;
    m_nIntensity = nI;

    m_nPixelMapX = m_nPixelMapX < 0   ? 0   : m_nPixelMapX;
    m_nPixelMapX = m_nPixelMapX > 240 ? 240 : m_nPixelMapX;
    m_nPixelMapY = m_nPixelMapY < 0   ? 0   : m_nPixelMapY;
    m_nPixelMapY = m_nPixelMapY > 240 ? 240 : m_nPixelMapY;
    m_nIntensity = m_nIntensity < 0   ? 0   : m_nIntensity;
    m_nIntensity = m_nIntensity > 240 ? 240 : m_nIntensity;

    double dR=0, dG=0, dB=0;
    HSI_to_RGB((double)m_nPixelMapX/240.0, (double)(240-m_nPixelMapY)/240.0, (double)m_nIntensity/240.0, dR, dG, dB);
    m_nRGB_R = dR;
    m_nRGB_G = dG;
    m_nRGB_B = dB;

    if(RadioButton_Type_BG->Checked) {
        m_nBGColor   = (m_nRGB_B << 16 | m_nRGB_G << 8 | m_nRGB_R);
    }
    else {
        m_nFontColor = (m_nRGB_B << 16 | m_nRGB_G << 8 | m_nRGB_R);
    }
}
//---------------------------------------------------------------------------

void __fastcall TfmMain::SetPixelMapBySelectColor(TColor clSelectColor)
{
    int RGB = ColorToRGB(clSelectColor);

    double dR = GetRValue(RGB);
    double dG = GetGValue(RGB);
    double dB = GetBValue(RGB);

    m_nRGB_R = dR;
    m_nRGB_G = dG;
    m_nRGB_B = dB;

    double dH=0, dS=0, dI=0;
    RGB_to_HSI(dR, dG, dB, dH, dS, dI);

    m_nPixelMapX = dH * 240;
    m_nPixelMapY = 240 - dS * 240;
    m_nIntensity = dI * 240;

    if(RadioButton_Type_BG->Checked) {
        m_nBGColor   = RGB;
    }
    else {
        m_nFontColor = RGB;
    }

    DisplayUpdatePixelMap(true);
}

//---------------------------------------------------------------------------
void __fastcall TfmMain::Edit_Pixel_HChange(TObject *Sender)
{
    TEdit * pEdit = dynamic_cast<TEdit *>(Sender);
    if(pEdit == NULL || fmMain->Showing == false) return;

    int nIdx = pEdit->Tag;

    int nH=0, nS=0, nI=0, nR=0, nG=0, nB=0, nHexColor = 0;
    double dR=0, dG=0, dB=0;

    AnsiString sText =  pEdit->Text;
    sText = sText.Trim();

    switch(nIdx) {
        case 1: // H
        case 2: // S
        case 3: // I
            nH = Edit_Pixel_H->Text.ToIntDef(0);
            nS = Edit_Pixel_S->Text.ToIntDef(0);
            nI = Edit_Pixel_I->Text.ToIntDef(0);

            SetColor_XYI(nH, nS, nI);

            DisplayUpdatePixelMap(true);
            break;

        case 4: // R
        case 5: // G
        case 6: // B
            nR = Edit_Pixel_R->Text.ToIntDef(0);
            nG = Edit_Pixel_G->Text.ToIntDef(0);
            nB = Edit_Pixel_B->Text.ToIntDef(0);

            nR = nR < 0   ? 0   : nR;
            nR = nR > 255 ? 255 : nR;
            nG = nG < 0   ? 0   : nG;
            nG = nG > 255 ? 255 : nG;
            nB = nB < 0   ? 0   : nB;
            nB = nB > 255 ? 255 : nB;

            SetPixelMapBySelectColor((TColor)((nB << 16) | (nG <<8) | nR));
            break;

        case 7: // Hex Color Code
            nHexColor = Edit_CodeColor->Text.ToIntDef(0);
            SetPixelMapBySelectColor((TColor)nHexColor);
            break;

        case 8: // Delphi Color Code
            break;

    }

}
//---------------------------------------------------------------------------

void __fastcall TfmMain::Button_AddCart_1Click(TObject *Sender)
{
    TSpeedButton * pBtn = dynamic_cast<TSpeedButton *>(Sender);
    if(pBtn == NULL) return;

    int nIdx = pBtn->Tag;
    int RGB = 0;

    switch(nIdx) {
        case 1: // Named Color
            m_nCartIndex += 1;
            if(m_nCartIndex >= StringGrid_Cart->RowCount) StringGrid_Cart->RowCount += 1;
            StringGrid_Cart->Cells[3][m_nCartIndex] = "0x" + IntToHex(m_ColorIndex[nSelectColorIndex], 8);
            StringGrid_Cart->Cells[2][m_nCartIndex] = StringGrid1->Cells[1][nSelectColorIndex+1];
            StringGrid_Cart->Cells[1][m_nCartIndex] = "";
            StringGrid_Cart->Cells[0][m_nCartIndex] = m_nCartIndex;
            break;

        case 2: // Pixel Palette
            m_nCartIndex += 1;
            if(m_nCartIndex >= StringGrid_Cart->RowCount) StringGrid_Cart->RowCount += 1;
            RGB = m_nRGB_B << 16 | m_nRGB_G << 8 | m_nRGB_R;
            StringGrid_Cart->Cells[3][m_nCartIndex] = "0x" + IntToHex(RGB, 8);
            StringGrid_Cart->Cells[2][m_nCartIndex] = "";
            StringGrid_Cart->Cells[1][m_nCartIndex] = "";
            StringGrid_Cart->Cells[0][m_nCartIndex] = m_nCartIndex;
            break;
    }

}
//---------------------------------------------------------------------------

void __fastcall TfmMain::StringGrid_CartDrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State)
{
    TCanvas * pCanvas = StringGrid_Cart->Canvas;

    Rect.Left -= 4;

    if(State.Contains(gdFixed) || (ARow == 0) || (ACol == 0)) {
        pCanvas->Brush->Color = clBtnFace;
        pCanvas->Font->Color = clWindowText;
        pCanvas->FillRect(Rect);
        Frame3D(pCanvas, Rect, clBtnHighlight, clBtnShadow, 1);
        pCanvas->TextRect(Rect, Rect.Left+2, Rect.Top + 3, StringGrid_Cart->Cells[ACol][ARow]);
    }
    else if(ACol==3){
        AnsiString sColor = StringGrid_Cart->Cells[ACol][ARow];
        int nColor = sColor.ToIntDef(0x00FFFFFF);

        // �� ������ ��Ʈ ������ ���Ѵ�.
        double dR = GetRValue(nColor);
        double dG = GetGValue(nColor);
        double dB = GetBValue(nColor);
        double dH=0, dS=0, dI=0;
        RGB_to_HSI(dR, dG, dB, dH, dS, dI);
        pCanvas->Font->Color = (dI * 240) > 140 ? clBlack : clWhite;

        pCanvas->Brush->Color = (TColor)nColor;
        pCanvas->FillRect(Rect);
        pCanvas->TextRect(Rect, Rect.Left+4, Rect.Top+4, sColor);

    }

    pCanvas->Brush->Color = clWhite;
    pCanvas->Font->Color  = clBlack;
}
//---------------------------------------------------------------------------



void __fastcall TfmMain::StringGrid_CartMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
//    if(Button == mbRight) {
//
//        SelectRow(RowByPoint(X, Y));
//        PopupMenu_Cart->Popup(X + StringGrid_Cart->Left + Panel3->Left + this->Left,
//                              Y+StringGrid_Cart->Top + this->Top);
//    }

}
//---------------------------------------------------------------------------

void __fastcall TfmMain::DeleteItem1Click(TObject *Sender)
{
    int nIdx = StringGrid_Cart->Selection.Top;

    for(int row=nIdx+1; row< StringGrid_Cart->RowCount; row++) {
        for(int col=0; col<StringGrid_Cart->ColCount; col++) {
            StringGrid_Cart->Cells[col][row-1] = StringGrid_Cart->Cells[col][row];
        }
    }

    for(int col=0; col<StringGrid_Cart->ColCount; col++) {
        StringGrid_Cart->Cells[col][StringGrid_Cart->RowCount-1] = "";
    }

    if(StringGrid_Cart->RowCount > 2) {
        StringGrid_Cart->RowCount -= 1;
    }

    m_nCartIndex -= 1;
    m_nCartIndex = m_nCartIndex < 0 ? 0 : m_nCartIndex;

    for(int row=1; row<StringGrid_Cart->RowCount; row++) {
        StringGrid_Cart->Cells[0][row] = row;
    }

}
//---------------------------------------------------------------------------
void __fastcall TfmMain::DeleteAll1Click(TObject *Sender)
{
    StringGrid_Cart->RowCount = 2;
    for(int col=0; col<StringGrid_Cart->ColCount; col++) {
        StringGrid_Cart->Cells[col][1] = "";
    }

    m_nCartIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfmMain::Copy1Click(TObject *Sender)
{
    int row = StringGrid_Cart->Selection.Top;
    int col = StringGrid_Cart->Selection.Left;

    TClipboard * pCB = Clipboard();
    pCB->Open();
    pCB->SetTextBuf(StringGrid_Cart->Cells[col][row].w_str());
    pCB->Close();
}
//---------------------------------------------------------------------------



void __fastcall TfmMain::StringGrid_CartClick(TObject *Sender)
{
//    int row = StringGrid_Cart->Selection.Top;
//    int col = StringGrid_Cart->Selection.Left;
//
//    TClipboard * pCB = Clipboard();
//    pCB->Open();
//    pCB->SetTextBuf(StringGrid_Cart->Cells[col][row].w_str());
//    pCB->Close();

}
//---------------------------------------------------------------------------



void __fastcall TfmMain::RadioButton_Type_BGClick(TObject *Sender)
{
    TRadioButton * pBtn = dynamic_cast<TRadioButton *>(Sender);
    if(pBtn == NULL) return;

    if(pBtn->Tag == 0) {
        // Back Ground
        SetPixelMapBySelectColor(Panel_SelectPixelColor->Color);
    }
    else {
        // Font
        SetPixelMapBySelectColor(Panel_SelectPixelColor->Font->Color);
    }

}
//---------------------------------------------------------------------------
void __fastcall TfmMain::Load(MFileManager * pFileMng)
{
    if(pFileMng == NULL) return;

    AnsiString sKey;

    pFileMng->GetValuePlus("LAST WORK INFO", "m_nPixelMapX", &m_nPixelMapX, m_nPixelMapX);
    pFileMng->GetValuePlus("LAST WORK INFO", "m_nPixelMapY", &m_nPixelMapY, m_nPixelMapY);
    pFileMng->GetValuePlus("LAST WORK INFO", "m_nIntensity", &m_nIntensity, m_nIntensity);

    pFileMng->GetValuePlus("LAST WORK INFO", "m_nRGB_R", &m_nRGB_R, m_nRGB_R);
    pFileMng->GetValuePlus("LAST WORK INFO", "m_nRGB_G", &m_nRGB_G, m_nRGB_G);
    pFileMng->GetValuePlus("LAST WORK INFO", "m_nRGB_B", &m_nRGB_B, m_nRGB_B);

    pFileMng->GetValuePlus("LAST WORK INFO", "m_nBGColor",   &m_nBGColor,   m_nBGColor);
    pFileMng->GetValuePlus("LAST WORK INFO", "m_nFontColor", &m_nFontColor, m_nFontColor);

    pFileMng->GetValuePlus("LAST WORK INFO", "m_nCartIndex", &m_nCartIndex, m_nCartIndex);
    pFileMng->GetValuePlus("LAST WORK INFO", "nSelectColorIndex", &nSelectColorIndex, nSelectColorIndex);

    StringGrid_Cart->RowCount = m_nCartIndex + 1;
    for(int i=0; i<m_nCartIndex; i++) {
        sKey.printf("Cart_%03d", i);
        AnsiString sTemp[3];
        pFileMng->Get1xArrayValuePlus("COLOR CART", sKey, 3, sTemp);

        StringGrid_Cart->Cells[0][i+1] = i+1;
        StringGrid_Cart->Cells[1][i+1] = sTemp[0];
        StringGrid_Cart->Cells[2][i+1] = sTemp[1];
        StringGrid_Cart->Cells[3][i+1] = sTemp[2];
    }

}

//---------------------------------------------------------------------------
void __fastcall TfmMain::Save(MFileManager * pFileMng)
{
    if(pFileMng == NULL) return;

    AnsiString sKey;

    pFileMng->SetValuePlus("LAST WORK INFO", "m_nPixelMapX",m_nPixelMapX);
    pFileMng->SetValuePlus("LAST WORK INFO", "m_nPixelMapY",m_nPixelMapY);
    pFileMng->SetValuePlus("LAST WORK INFO", "m_nIntensity",m_nIntensity);

    pFileMng->SetValuePlus("LAST WORK INFO", "m_nRGB_R", m_nRGB_R);
    pFileMng->SetValuePlus("LAST WORK INFO", "m_nRGB_G", m_nRGB_G);
    pFileMng->SetValuePlus("LAST WORK INFO", "m_nRGB_B", m_nRGB_B);

    pFileMng->SetValuePlus("LAST WORK INFO", "m_nBGColor",   m_nBGColor);
    pFileMng->SetValuePlus("LAST WORK INFO", "m_nFontColor", m_nFontColor);

    pFileMng->SetValuePlus("LAST WORK INFO", "m_nCartIndex", m_nCartIndex);
    pFileMng->SetValuePlus("LAST WORK INFO", "nSelectColorIndex", nSelectColorIndex);


    AnsiString sTemp[3];
    for(int i=0; i<m_nCartIndex; i++) {
        sKey.printf("Cart_%03d", i);
        sTemp[0] = StringGrid_Cart->Cells[1][i+1];
        sTemp[1] = StringGrid_Cart->Cells[2][i+1];
        sTemp[2] = StringGrid_Cart->Cells[3][i+1];

        pFileMng->Set1xArrayValuePlus("COLOR CART", sKey, 3, sTemp);
    }
}

//---------------------------------------------------------------------------
void __fastcall TfmMain::FormCreate(TObject *Sender)
{
    Load(m_pFileManager);
}
//---------------------------------------------------------------------------

void __fastcall TfmMain::FormClose(TObject *Sender, TCloseAction &Action)
{
    Save(m_pFileManager);
}
//---------------------------------------------------------------------------

void __fastcall TfmMain::Open1Click(TObject *Sender)
{
    AnsiString sPath = ExtractFilePath(Application->ExeName);
    OpenTextFileDialog1->InitialDir = sPath;
    OpenTextFileDialog1->Filter = "Config files (*.ini)|*.ini|All File (*.*)";

    if(OpenTextFileDialog1->Execute()) {
        AnsiString sFullName = OpenTextFileDialog1->FileName;
        AnsiString sPath     = ExtractFilePath(sFullName);
        AnsiString sFile     = ExtractFileName(sFullName);

        if(FileExists(sFullName)) {
            if(m_pFileManager) delete m_pFileManager;
            m_pFileManager = new MFileManager(sFile, sPath);

            Load(m_pFileManager);

            DisplayUpdatePixelMap(true);
            DisplayUpdate();
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TfmMain::Save1Click(TObject *Sender)
{
    Save(m_pFileManager);
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::SaveAs1Click(TObject *Sender)
{
    AnsiString sPath = m_pFileManager->GetPath();
    SaveTextFileDialog1->InitialDir = sPath;
    SaveTextFileDialog1->Filter = "Config files (*.ini)|*.ini|All File (*.*)";

    if(SaveTextFileDialog1->Execute()) {
        AnsiString sFullName = SaveTextFileDialog1->FileName;
        AnsiString sPath     = ExtractFilePath(sFullName);
        AnsiString sFile     = ExtractFileName(sFullName);

        if(m_pFileManager) delete m_pFileManager;
        m_pFileManager = new MFileManager(sFile, sPath);

        Save(m_pFileManager);

        DisplayUpdate();
    }
}
//---------------------------------------------------------------------------

void __fastcall TfmMain::Exit1Click(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------


void __fastcall TfmMain::FormPaint(TObject *Sender)
{
    static int count = 0;
    count += 1;
    Caption += count;
}
//---------------------------------------------------------------------------

void __fastcall TfmMain::WndProc(TMessage &M)
{
    switch (M.Msg)
    {
        case WM_CREATE:
            TForm::WndProc(M);
            break;

        case WM_PAINT:
            TForm::WndProc(M);
            break;

        case WM_ERASEBKGND:
            TForm::WndProc(M);
            break;

        default:
            TForm::WndProc(M);
            break;
    }
}

