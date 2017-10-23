object MainForm: TMainForm
  Left = 351
  Top = 354
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #1044#1080#1085#1072#1084#1080#1095#1077#1089#1082#1080#1077' '#1089#1090#1088#1091#1082#1090#1091#1088#1099' '#1076#1072#1085#1085#1099#1093
  ClientHeight = 330
  ClientWidth = 603
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 297
    Height = 201
    Caption = #1048#1089#1093#1086#1076#1085#1099#1081' '#1089#1087#1080#1089#1086#1082
    TabOrder = 0
    object StringGrid1: TStringGrid
      Left = 8
      Top = 16
      Width = 281
      Height = 177
      ColCount = 3
      DefaultRowHeight = 14
      FixedCols = 0
      RowCount = 2
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
      ScrollBars = ssVertical
      TabOrder = 0
      ColWidths = (
        56
        158
        42)
    end
  end
  object GroupBox2: TGroupBox
    Left = 304
    Top = 0
    Width = 297
    Height = 201
    Caption = #1054#1073#1088#1072#1073#1086#1090#1072#1085#1085#1099#1081' '#1089#1087#1080#1089#1086#1082
    TabOrder = 1
    object StringGrid2: TStringGrid
      Left = 8
      Top = 16
      Width = 281
      Height = 177
      ColCount = 3
      DefaultRowHeight = 14
      FixedCols = 0
      RowCount = 2
      ScrollBars = ssVertical
      TabOrder = 0
      ColWidths = (
        56
        158
        42)
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 208
    Width = 601
    Height = 121
    BevelInner = bvLowered
    BevelOuter = bvNone
    TabOrder = 2
    object LabeledEdit1: TLabeledEdit
      Left = 8
      Top = 19
      Width = 121
      Height = 21
      EditLabel.Width = 110
      EditLabel.Height = 13
      EditLabel.Caption = #1056#1072#1079#1084#1077#1088#1085#1086#1089#1090#1100'  '#1089#1087#1080#1089#1082#1072
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 0
      Text = '1'
    end
    object Create: TBitBtn
      Left = 8
      Top = 69
      Width = 121
      Height = 25
      Caption = #1057#1086#1079#1076#1072#1090#1100' '#1089#1087#1080#1089#1086#1082
      TabOrder = 1
      OnClick = CreateClick
      Kind = bkYes
    end
    object BitBtn2: TBitBtn
      Left = 69
      Top = 45
      Width = 60
      Height = 25
      Caption = '-'
      TabOrder = 2
      OnClick = BitBtn2Click
    end
    object BitBtn3: TBitBtn
      Left = 8
      Top = 45
      Width = 60
      Height = 25
      Caption = '+'
      TabOrder = 3
      OnClick = BitBtn3Click
    end
    object BitBtn4: TBitBtn
      Left = 453
      Top = 45
      Width = 141
      Height = 25
      Caption = #1059#1076#1072#1083#1080#1090#1100' '#1080#1079' '#1074#1077#1088#1096#1080#1085#1099
      TabOrder = 4
      OnClick = BitBtn4Click
    end
    object BitBtn5: TBitBtn
      Left = 312
      Top = 45
      Width = 141
      Height = 25
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1074' '#1074#1077#1088#1096#1080#1085#1091
      TabOrder = 5
      OnClick = BitBtn5Click
    end
    object BitBtn1: TBitBtn
      Left = 312
      Top = 69
      Width = 141
      Height = 49
      Caption = #1059#1076#1072#1083#1080#1090#1100' '#1089#1087#1080#1089#1086#1082
      TabOrder = 6
      OnClick = BitBtn1Click
      Kind = bkAbort
    end
    object Exit: TBitBtn
      Left = 453
      Top = 69
      Width = 141
      Height = 49
      Caption = #1042#1099#1093#1086#1076
      TabOrder = 7
      OnClick = ExitClick
      Kind = bkNo
    end
    object StringGrid3: TStringGrid
      Left = 312
      Top = 7
      Width = 281
      Height = 34
      ColCount = 3
      DefaultRowHeight = 14
      FixedCols = 0
      RowCount = 2
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
      ScrollBars = ssVertical
      TabOrder = 8
      ColWidths = (
        74
        154
        42)
    end
    object BitBtn6: TBitBtn
      Left = 136
      Top = 21
      Width = 153
      Height = 25
      Caption = #1042#1099#1074#1086#1076' '#1089#1087#1080#1089#1082#1072
      TabOrder = 9
      OnClick = BitBtn6Click
    end
    object BitBtn7: TBitBtn
      Left = 136
      Top = 45
      Width = 153
      Height = 25
      Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1101#1083#1077#1084#1077#1085#1090#1086#1074
      TabOrder = 10
      OnClick = BitBtn7Click
    end
    object BitBtn8: TBitBtn
      Left = 136
      Top = 69
      Width = 153
      Height = 25
      Caption = #1069#1083#1077#1084#1077#1085#1090' '#1080#1079' '#1074#1077#1088#1096#1080#1085#1099
      TabOrder = 11
      OnClick = BitBtn8Click
    end
    object BitBtn9: TBitBtn
      Left = 136
      Top = 93
      Width = 153
      Height = 25
      Caption = #1054#1095#1080#1089#1090#1082#1072' '#1087#1086#1083#1077#1081
      TabOrder = 12
      OnClick = BitBtn9Click
    end
    object RadioButton1: TRadioButton
      Left = 8
      Top = 102
      Width = 65
      Height = 13
      Caption = #1054#1095#1077#1088#1077#1076#1100
      Checked = True
      TabOrder = 13
      TabStop = True
    end
    object RadioButton2: TRadioButton
      Left = 80
      Top = 101
      Width = 49
      Height = 17
      Caption = #1057#1090#1077#1082
      TabOrder = 14
    end
  end
end
