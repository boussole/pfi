object MainForm: TMainForm
  Left = 459
  Top = 342
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #1064#1072#1073#1083#1086#1085#1099' '#1092#1091#1085#1082#1094#1080#1081
  ClientHeight = 303
  ClientWidth = 358
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 113
    Height = 297
    Caption = #1048#1089#1093#1086#1076#1085#1099#1081' '#1084#1072#1089#1089#1080#1074
    TabOrder = 0
    object StringGrid1: TStringGrid
      Left = 8
      Top = 16
      Width = 97
      Height = 273
      ColCount = 1
      DefaultColWidth = 70
      DefaultRowHeight = 14
      FixedCols = 0
      RowCount = 2
      FixedRows = 0
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
      ScrollBars = ssVertical
      TabOrder = 0
    end
  end
  object Panel1: TPanel
    Left = 240
    Top = 5
    Width = 113
    Height = 292
    BorderStyle = bsSingle
    TabOrder = 1
    object BitBtn1: TBitBtn
      Left = 10
      Top = 152
      Width = 87
      Height = 33
      Caption = #1042#1099#1087#1086#1083#1085#1080#1090#1100
      TabOrder = 0
      OnClick = BitBtn1Click
      Kind = bkOK
    end
    object BitBtn2: TBitBtn
      Left = 10
      Top = 184
      Width = 87
      Height = 33
      Caption = #1043#1057#1063' '
      TabOrder = 1
      OnClick = BitBtn2Click
      Kind = bkIgnore
    end
    object BitBtn3: TBitBtn
      Left = 10
      Top = 216
      Width = 87
      Height = 33
      Caption = #1054#1095#1080#1089#1090#1080#1090#1100
      TabOrder = 2
      OnClick = BitBtn3Click
      Kind = bkRetry
    end
    object BitBtn4: TBitBtn
      Left = 10
      Top = 248
      Width = 87
      Height = 33
      Caption = #1042#1099#1093#1086#1076
      TabOrder = 3
      OnClick = BitBtn4Click
      Kind = bkClose
    end
    object LabeledEdit1: TLabeledEdit
      Left = 8
      Top = 24
      Width = 89
      Height = 21
      EditLabel.Width = 68
      EditLabel.Height = 13
      EditLabel.Caption = #1056#1072#1079#1084#1077#1088#1085#1086#1089#1090#1100
      LabelPosition = lpAbove
      LabelSpacing = 3
      ReadOnly = True
      TabOrder = 4
      Text = '2'
    end
    object Button1: TButton
      Left = 10
      Top = 48
      Width = 87
      Height = 25
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100
      TabOrder = 5
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 10
      Top = 72
      Width = 87
      Height = 25
      Caption = #1059#1076#1072#1083#1080#1090#1100
      TabOrder = 6
      OnClick = Button2Click
    end
    object RadioButton1: TRadioButton
      Left = 8
      Top = 98
      Width = 73
      Height = 17
      Caption = #1058#1080#1087' Int'
      Checked = True
      TabOrder = 7
      TabStop = True
    end
    object RadioButton2: TRadioButton
      Left = 8
      Top = 116
      Width = 73
      Height = 17
      Caption = #1058#1080#1087' Float'
      TabOrder = 8
    end
    object RadioButton3: TRadioButton
      Left = 8
      Top = 133
      Width = 73
      Height = 17
      Caption = #1058#1080#1087' Char'
      TabOrder = 9
    end
  end
  object GroupBox2: TGroupBox
    Left = 120
    Top = 0
    Width = 113
    Height = 297
    Caption = #1048#1090#1086#1075#1086#1074#1099#1081' '#1084#1072#1089#1089#1080#1074
    TabOrder = 2
    object StringGrid2: TStringGrid
      Left = 8
      Top = 16
      Width = 97
      Height = 273
      ColCount = 1
      DefaultColWidth = 70
      DefaultRowHeight = 14
      FixedCols = 0
      RowCount = 2
      FixedRows = 0
      ScrollBars = ssVertical
      TabOrder = 0
    end
  end
end
