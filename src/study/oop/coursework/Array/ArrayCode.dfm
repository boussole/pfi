object MainForm: TMainForm
  Left = 346
  Top = 373
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #1056#1072#1073#1086#1090#1072' '#1089' '#1084#1072#1089#1089#1080#1074#1072#1084#1080
  ClientHeight = 301
  ClientWidth = 622
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 0
    Top = 8
    Width = 305
    Height = 161
    Caption = #1048#1089#1093#1086#1076#1085#1072#1103' '#1084#1072#1090#1088#1080#1094#1072
    TabOrder = 0
    object SourceArray: TStringGrid
      Left = 8
      Top = 16
      Width = 289
      Height = 137
      ColCount = 2
      DefaultRowHeight = 14
      FixedCols = 0
      RowCount = 2
      FixedRows = 0
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
      TabOrder = 0
    end
  end
  object GroupBox2: TGroupBox
    Left = 312
    Top = 8
    Width = 305
    Height = 161
    Caption = #1059#1087#1086#1088#1103#1076#1086#1095#1077#1085#1085#1072#1103' '#1084#1072#1090#1088#1080#1094#1072
    TabOrder = 1
    object FinalArray: TStringGrid
      Left = 8
      Top = 16
      Width = 289
      Height = 137
      ColCount = 2
      DefaultRowHeight = 14
      FixedCols = 0
      RowCount = 2
      FixedRows = 0
      TabOrder = 0
    end
  end
  object ControlPanel: TGroupBox
    Left = 0
    Top = 176
    Width = 617
    Height = 121
    Caption = #1055#1072#1085#1077#1083#1100' '#1091#1087#1088#1072#1074#1083#1077#1085#1080#1103
    TabOrder = 2
    object SizeOfMatrix: TGroupBox
      Left = 8
      Top = 16
      Width = 145
      Height = 97
      Caption = #1056#1072#1079#1084#1077#1088#1085#1086#1089#1090#1100' '#1084#1072#1090#1088#1080#1094#1099
      TabOrder = 0
      object LabeledEdit1: TLabeledEdit
        Left = 8
        Top = 32
        Width = 121
        Height = 21
        Color = clSilver
        EditLabel.Width = 91
        EditLabel.Height = 13
        EditLabel.Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1089#1090#1088#1086#1082
        LabelPosition = lpAbove
        LabelSpacing = 3
        ReadOnly = True
        TabOrder = 0
        Text = '2'
        OnKeyUp = LabeledEdit1KeyUp
      end
      object LabeledEdit2: TLabeledEdit
        Left = 8
        Top = 72
        Width = 121
        Height = 21
        Color = clSilver
        EditLabel.Width = 109
        EditLabel.Height = 13
        EditLabel.Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1089#1090#1086#1083#1073#1094#1086#1074
        LabelPosition = lpAbove
        LabelSpacing = 3
        ReadOnly = True
        TabOrder = 1
        Text = '2'
        OnKeyUp = LabeledEdit2KeyUp
      end
    end
    object ButtonDo: TBitBtn
      Left = 312
      Top = 16
      Width = 289
      Height = 33
      Caption = #1042#1099#1087#1086#1083#1085#1080#1090#1100
      TabOrder = 1
      OnClick = ButtonDoClick
      Kind = bkOK
    end
    object ButtonExit: TBitBtn
      Left = 312
      Top = 81
      Width = 289
      Height = 33
      Caption = #1042#1099#1093#1086#1076
      TabOrder = 2
      OnClick = ButtonExitClick
      Kind = bkAbort
    end
    object Action: TGroupBox
      Left = 160
      Top = 16
      Width = 145
      Height = 97
      Caption = #1056#1077#1078#1080#1084' '#1088#1072#1073#1086#1090#1099
      TabOrder = 3
      object RadioButton1: TRadioButton
        Left = 16
        Top = 24
        Width = 113
        Height = 17
        Caption = #1043#1057#1063
        Checked = True
        TabOrder = 0
        TabStop = True
        OnClick = RadioButton1Click
      end
      object RadioButton2: TRadioButton
        Left = 16
        Top = 64
        Width = 113
        Height = 17
        Caption = #1042#1088#1091#1095#1085#1091#1102
        TabOrder = 1
        OnClick = RadioButton2Click
      end
    end
    object BitBtn1: TBitBtn
      Left = 312
      Top = 48
      Width = 289
      Height = 33
      Caption = #1054#1095#1080#1089#1090#1080#1090#1100' '#1087#1086#1083#1103
      TabOrder = 4
      OnClick = BitBtn1Click
      Kind = bkRetry
    end
  end
end
