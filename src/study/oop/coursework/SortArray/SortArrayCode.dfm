object MainForm: TMainForm
  Left = 537
  Top = 320
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #1057#1086#1088#1090#1080#1088#1086#1074#1082#1072
  ClientHeight = 332
  ClientWidth = 189
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
    Width = 89
    Height = 225
    Caption = 'Source'
    TabOrder = 0
    object StringGrid1: TStringGrid
      Left = 8
      Top = 16
      Width = 73
      Height = 201
      ColCount = 1
      DefaultColWidth = 50
      DefaultRowHeight = 14
      FixedCols = 0
      RowCount = 2
      FixedRows = 0
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
      ScrollBars = ssVertical
      TabOrder = 0
    end
  end
  object SortOut: TGroupBox
    Left = 96
    Top = 0
    Width = 89
    Height = 225
    Caption = 'Sort Out'
    TabOrder = 1
    object StringGrid2: TStringGrid
      Left = 8
      Top = 16
      Width = 73
      Height = 201
      ColCount = 1
      DefaultColWidth = 50
      DefaultRowHeight = 14
      FixedCols = 0
      RowCount = 2
      FixedRows = 0
      ScrollBars = ssVertical
      TabOrder = 0
    end
  end
  object BitBtn1: TBitBtn
    Left = 96
    Top = 232
    Width = 89
    Height = 25
    Caption = #1057#1086#1088#1090#1080#1088#1086#1074#1072#1090#1100
    TabOrder = 2
    OnClick = BitBtn1Click
    Kind = bkYes
  end
  object BitBtn2: TBitBtn
    Left = 96
    Top = 256
    Width = 89
    Height = 25
    Caption = #1043#1057#1063
    TabOrder = 3
    OnClick = BitBtn2Click
    Kind = bkIgnore
  end
  object ClearStringGrid: TBitBtn
    Left = 96
    Top = 280
    Width = 89
    Height = 25
    Caption = #1054#1095#1080#1089#1090#1080#1090#1100
    TabOrder = 4
    OnClick = ClearStringGridClick
    Kind = bkRetry
  end
  object LabeledEdit1: TLabeledEdit
    Left = 8
    Top = 257
    Width = 81
    Height = 21
    EditLabel.Width = 68
    EditLabel.Height = 13
    EditLabel.Caption = #1056#1072#1079#1084#1077#1088#1085#1086#1089#1090#1100
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 5
    Text = '2'
  end
  object Exit: TBitBtn
    Left = 96
    Top = 304
    Width = 89
    Height = 25
    Caption = #1042#1099#1093#1086#1076
    TabOrder = 6
    OnClick = ExitClick
    Kind = bkCancel
  end
  object AddTable: TButton
    Left = 8
    Top = 280
    Width = 81
    Height = 25
    Caption = #1044#1086#1073#1072#1074#1080#1090#1100
    TabOrder = 7
    OnClick = AddTableClick
  end
  object DeleteTable: TButton
    Left = 8
    Top = 304
    Width = 81
    Height = 25
    Caption = #1059#1076#1072#1083#1080#1090#1100
    TabOrder = 8
    OnClick = DeleteTableClick
  end
end
