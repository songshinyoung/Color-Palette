object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Color Palette'
  ClientHeight = 581
  ClientWidth = 1067
  Color = clBtnFace
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnDestroy = FormDestroy
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 753
    Top = 0
    Height = 581
    Align = alRight
    Color = clSilver
    ParentColor = False
    ExplicitLeft = 811
    ExplicitTop = -8
    ExplicitHeight = 542
  end
  object StringGrid1: TStringGrid
    Left = 0
    Top = 0
    Width = 409
    Height = 581
    Align = alLeft
    ColCount = 3
    DefaultColWidth = 50
    RowCount = 201
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goEditing]
    TabOrder = 0
    OnClick = StringGrid1Click
    OnDrawCell = StringGrid1DrawCell
    OnSelectCell = StringGrid1SelectCell
    ColWidths = (
      50
      178
      154)
  end
  object Panel1: TPanel
    Left = 409
    Top = 0
    Width = 344
    Height = 581
    Align = alClient
    BevelOuter = bvNone
    BiDiMode = bdLeftToRight
    Caption = 'Panel1'
    ParentBiDiMode = False
    ParentBackground = False
    ShowCaption = False
    TabOrder = 1
    object AZFlowShape_Color: TAZFlowShape
      Left = 0
      Top = 0
      Width = 344
      Height = 444
      AZ_Col = 10
      AZ_Row = 20
      AZ_Space = 1
      AZ_Round = 0
      AZ_CellLineColorUse = False
      AZ_CellLineColor = clWhite
      AZ_OutLineColor = clWhite
      Title.Visible = False
      Title.Caption = 'Title'
      Title.Font.Charset = DEFAULT_CHARSET
      Title.Font.Color = clBlack
      Title.Font.Height = -13
      Title.Font.Name = 'Arial'
      Title.Font.Style = [fsBold]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Arail'
      Font.Style = []
      Align = alClient
      OnClick = AZFlowShape_ColorClick
      ExplicitLeft = 6
      ExplicitHeight = 405
    end
    object Panel2: TPanel
      Left = 0
      Top = 444
      Width = 344
      Height = 137
      Align = alBottom
      BevelOuter = bvNone
      Caption = 'Panel2'
      ShowCaption = False
      TabOrder = 0
      object Label1: TLabel
        Left = 48
        Top = 115
        Width = 83
        Height = 13
        Caption = 'Vcl.Graphics.hpp '
      end
      object Label_ColorType: TLabel
        Left = 48
        Top = 80
        Width = 55
        Height = 13
        Caption = 'Color Type '
      end
      object Panel_Color: TPanel
        Left = 48
        Top = 6
        Width = 185
        Height = 41
        BevelOuter = bvLowered
        Caption = 'Panel_Color'
        Color = 6172671
        ParentBackground = False
        ShowCaption = False
        TabOrder = 0
      end
      object Edit_Color: TEdit
        Tag = 1
        Left = 48
        Top = 53
        Width = 185
        Height = 21
        Color = clWhite
        TabOrder = 1
        Text = 'Edit_Color'
      end
      object Button_Copy: TButton
        Tag = 1
        Left = 239
        Top = 6
        Width = 98
        Height = 70
        Caption = 'Copy'
        TabOrder = 2
        OnClick = Button_CopyClick
      end
    end
  end
  object Panel3: TPanel
    Left = 756
    Top = 0
    Width = 311
    Height = 581
    Align = alRight
    BevelOuter = bvNone
    Caption = 'Panel3'
    ShowCaption = False
    TabOrder = 2
    object Label_Pixel_Y: TLabel
      Left = 72
      Top = 276
      Width = 34
      Height = 13
      Caption = 'Y : 000'
    end
    object Label2: TLabel
      Left = 120
      Top = 305
      Width = 25
      Height = 13
      AutoSize = False
      Caption = 'H'
    end
    object Label3: TLabel
      Left = 120
      Top = 331
      Width = 25
      Height = 13
      AutoSize = False
      Caption = 'S'
    end
    object Label4: TLabel
      Left = 120
      Top = 357
      Width = 25
      Height = 13
      AutoSize = False
      Caption = 'I'
    end
    object Label5: TLabel
      Left = 192
      Top = 305
      Width = 25
      Height = 13
      AutoSize = False
      Caption = 'R'
    end
    object Label6: TLabel
      Left = 192
      Top = 331
      Width = 25
      Height = 13
      AutoSize = False
      Caption = 'G'
    end
    object Label7: TLabel
      Left = 192
      Top = 357
      Width = 25
      Height = 13
      AutoSize = False
      Caption = 'B'
    end
    object Label_Pixel_X: TLabel
      Left = 24
      Top = 276
      Width = 34
      Height = 13
      Caption = 'X : 000'
    end
    object Panel_SelectPixelColor: TPanel
      Left = 24
      Top = 302
      Width = 81
      Height = 73
      BevelOuter = bvLowered
      BiDiMode = bdLeftToRight
      ParentBiDiMode = False
      ParentBackground = False
      TabOrder = 0
    end
    object TrackBar_Intensity: TTrackBar
      Left = 278
      Top = 30
      Width = 45
      Height = 240
      Max = 240
      Orientation = trVertical
      Position = 240
      TabOrder = 1
      OnChange = TrackBar_IntensityChange
    end
    object Edit_Pixel_H: TEdit
      Left = 135
      Top = 302
      Width = 40
      Height = 21
      TabOrder = 2
      Text = '0'
    end
    object Edit_Pixel_S: TEdit
      Left = 135
      Top = 328
      Width = 40
      Height = 21
      TabOrder = 3
      Text = '0'
    end
    object Edit_Pixel_I: TEdit
      Left = 135
      Top = 354
      Width = 40
      Height = 21
      TabOrder = 4
      Text = '0'
    end
    object Edit_Pixel_R: TEdit
      Left = 207
      Top = 302
      Width = 40
      Height = 21
      TabOrder = 5
      Text = '0'
    end
    object Edit_Pixel_G: TEdit
      Left = 207
      Top = 328
      Width = 40
      Height = 21
      TabOrder = 6
      Text = '0'
    end
    object Edit_Pixel_B: TEdit
      Left = 207
      Top = 354
      Width = 40
      Height = 21
      TabOrder = 7
      Text = '0'
    end
    object Edit_CodeColor: TEdit
      Tag = 2
      Left = 135
      Top = 389
      Width = 66
      Height = 21
      TabOrder = 8
      Text = '0'
    end
    object Edit_CodeColor2: TEdit
      Tag = 3
      Left = 135
      Top = 419
      Width = 66
      Height = 21
      TabOrder = 9
      Text = '0'
    end
    object Button_Copy_Code_1: TButton
      Tag = 2
      Left = 207
      Top = 388
      Width = 42
      Height = 24
      Caption = 'Copy'
      TabOrder = 10
      OnClick = Button_CopyClick
    end
    object Button_Copy_Code_2: TButton
      Tag = 3
      Left = 207
      Top = 418
      Width = 42
      Height = 24
      Caption = 'Copy'
      TabOrder = 11
      OnClick = Button_CopyClick
    end
    object Panel4: TPanel
      Left = 24
      Top = 32
      Width = 242
      Height = 242
      BevelOuter = bvLowered
      Caption = 'Panel4'
      ShowCaption = False
      TabOrder = 12
      object Image1: TImage
        Left = 1
        Top = 1
        Width = 240
        Height = 240
        Align = alClient
        OnMouseDown = Image1MouseDown
        OnMouseMove = Image1MouseMove
        OnMouseUp = Image1MouseUp
        ExplicitLeft = 11
        ExplicitTop = -13
      end
    end
    object Memo1: TMemo
      Left = 6
      Top = 448
      Width = 299
      Height = 124
      Lines.Strings = (
        'Memo1')
      ScrollBars = ssVertical
      TabOrder = 13
    end
  end
end
