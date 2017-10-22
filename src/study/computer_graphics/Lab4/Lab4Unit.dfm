object Form1: TForm1
  Left = 428
  Top = 268
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #1055#1086#1083#1080#1075#1086#1085#1072#1083#1100#1085#1072#1103' '#1084#1086#1076#1077#1083#1100
  ClientHeight = 628
  ClientWidth = 407
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnClick = FormClick
  OnClose = FormClose
  OnCreate = FormCreate
  OnPaint = FormPaint
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 407
    Height = 81
    Align = alTop
    BorderStyle = bsSingle
    TabOrder = 0
    object Label1: TLabel
      Left = 160
      Top = 8
      Width = 91
      Height = 16
      Caption = #1057#1074#1077#1090#1086#1074#1086#1081' '#1083#1091#1095
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object TrackBar1: TTrackBar
      Left = 40
      Top = 32
      Width = 329
      Height = 33
      Max = 20
      Orientation = trHorizontal
      PageSize = 1
      Frequency = 1
      Position = 20
      SelEnd = 0
      SelStart = 0
      TabOrder = 0
      TabStop = False
      TickMarks = tmBottomRight
      TickStyle = tsAuto
      OnChange = TrackBar1Change
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 520
    Width = 407
    Height = 108
    Align = alBottom
    BorderStyle = bsSingle
    TabOrder = 1
    object Label2: TLabel
      Left = 6
      Top = 16
      Width = 106
      Height = 13
      Caption = #1055#1086#1074#1086#1088#1086#1090' '#1087#1086' '#1086#1089#1080' '#1061
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label3: TLabel
      Left = 6
      Top = 48
      Width = 106
      Height = 13
      Caption = #1055#1086#1074#1086#1088#1086#1090' '#1087#1086' '#1086#1089#1080' Y'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label4: TLabel
      Left = 6
      Top = 80
      Width = 106
      Height = 13
      Caption = #1055#1086#1074#1086#1088#1086#1090' '#1087#1086' '#1086#1089#1080' Z'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object TrackBar2: TTrackBar
      Left = 112
      Top = 8
      Width = 289
      Height = 33
      Max = 360
      Orientation = trHorizontal
      PageSize = 1
      Frequency = 1
      Position = 0
      SelEnd = 0
      SelStart = 0
      TabOrder = 0
      TickMarks = tmTopLeft
      TickStyle = tsNone
      OnChange = TrackBar2Change
    end
    object TrackBar3: TTrackBar
      Left = 112
      Top = 40
      Width = 289
      Height = 33
      Max = 360
      Orientation = trHorizontal
      PageSize = 1
      Frequency = 1
      Position = 0
      SelEnd = 0
      SelStart = 0
      TabOrder = 1
      TickMarks = tmTopLeft
      TickStyle = tsNone
      OnChange = TrackBar3Change
    end
    object TrackBar4: TTrackBar
      Left = 112
      Top = 72
      Width = 289
      Height = 33
      Max = 360
      Orientation = trHorizontal
      PageSize = 1
      Frequency = 1
      Position = 0
      SelEnd = 0
      SelStart = 0
      TabOrder = 2
      TickMarks = tmTopLeft
      TickStyle = tsNone
      OnChange = TrackBar4Change
    end
  end
end
