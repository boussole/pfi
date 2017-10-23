object MainForm: TMainForm
  Left = 349
  Top = 415
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #1059#1087#1086#1088#1103#1076#1086#1095#1080#1074#1072#1085#1080#1077' '#1084#1072#1089#1089#1080#1074#1072' '#1089' '#1087#1077#1088#1077#1075#1088#1091#1079#1082#1086#1081' '#1092#1091#1085#1082#1094#1080#1081
  ClientHeight = 275
  ClientWidth = 701
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
  object Source: TGroupBox
    Left = 0
    Top = 0
    Width = 297
    Height = 273
    Caption = #1048#1089#1093#1086#1076#1085#1072#1103' '#1084#1072#1090#1088#1080#1094#1072
    TabOrder = 0
    object StringGrid1: TStringGrid
      Left = 8
      Top = 16
      Width = 281
      Height = 249
      ColCount = 2
      DefaultRowHeight = 14
      FixedCols = 0
      RowCount = 2
      FixedRows = 0
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
      TabOrder = 0
    end
  end
  object Final: TGroupBox
    Left = 304
    Top = 0
    Width = 297
    Height = 273
    Caption = #1048#1079#1084#1077#1085#1077#1085#1085#1072#1103' '#1084#1072#1090#1088#1080#1094#1072
    TabOrder = 1
    object StringGrid2: TStringGrid
      Left = 8
      Top = 16
      Width = 281
      Height = 249
      ColCount = 2
      DefaultRowHeight = 14
      FixedCols = 0
      RowCount = 2
      FixedRows = 0
      TabOrder = 0
    end
  end
  object BitBtn1: TBitBtn
    Left = 608
    Top = 176
    Width = 89
    Height = 25
    Caption = #1042#1099#1087#1086#1083#1085#1080#1090#1100
    TabOrder = 2
    OnClick = BitBtn1Click
    Kind = bkYes
  end
  object BitBtn2: TBitBtn
    Left = 608
    Top = 200
    Width = 89
    Height = 25
    Caption = #1043#1057#1063' '
    TabOrder = 3
    OnClick = BitBtn2Click
    Kind = bkIgnore
  end
  object BitBtn3: TBitBtn
    Left = 608
    Top = 224
    Width = 89
    Height = 25
    Caption = #1054#1095#1080#1089#1090#1080#1090#1100
    TabOrder = 4
    OnClick = BitBtn3Click
    Kind = bkRetry
  end
  object BitBtn4: TBitBtn
    Left = 608
    Top = 248
    Width = 89
    Height = 25
    Caption = #1042#1099#1093#1086#1076
    TabOrder = 5
    OnClick = BitBtn4Click
    Kind = bkCancel
  end
  object LabeledEdit1: TLabeledEdit
    Left = 608
    Top = 16
    Width = 89
    Height = 21
    EditLabel.Width = 39
    EditLabel.Height = 13
    EditLabel.Caption = #1057#1090#1088#1086#1082#1080':'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 6
    Text = '2'
  end
  object LabeledEdit2: TLabeledEdit
    Left = 608
    Top = 88
    Width = 89
    Height = 21
    EditLabel.Width = 47
    EditLabel.Height = 13
    EditLabel.Caption = #1057#1090#1086#1083#1073#1094#1099':'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 7
    Text = '2'
  end
  object Button1: TButton
    Left = 608
    Top = 40
    Width = 45
    Height = 25
    Caption = '+'
    TabOrder = 8
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 652
    Top = 40
    Width = 45
    Height = 25
    Caption = '-'
    TabOrder = 9
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 608
    Top = 112
    Width = 45
    Height = 25
    Caption = '+'
    TabOrder = 10
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 652
    Top = 112
    Width = 45
    Height = 25
    Caption = '-'
    TabOrder = 11
    OnClick = Button4Click
  end
  object RadioButton1: TRadioButton
    Left = 608
    Top = 143
    Width = 89
    Height = 17
    Caption = #1062#1077#1083#1099#1077
    Checked = True
    TabOrder = 12
    TabStop = True
  end
  object RadioButton2: TRadioButton
    Left = 608
    Top = 159
    Width = 89
    Height = 17
    Caption = #1042#1077#1097#1077#1089#1090#1074'.'
    TabOrder = 13
  end
end
