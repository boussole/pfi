object MainForm: TMainForm
  Left = 465
  Top = 424
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #1050#1086#1085#1090#1077#1081#1085#1077#1088#1085#1099#1081' '#1082#1083#1072#1089#1089
  ClientHeight = 143
  ClientWidth = 444
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
    Width = 217
    Height = 41
    Caption = #1057#1086#1079#1076#1072#1085#1080#1077' '#1084#1085#1086#1078#1077#1089#1090#1074#1072' '#1080#1079' n - '#1101#1083#1077#1084#1077#1085#1090#1086#1074
    TabOrder = 0
    object Edit1: TEdit
      Left = 8
      Top = 16
      Width = 121
      Height = 21
      TabOrder = 0
    end
    object BitBtn1: TBitBtn
      Left = 136
      Top = 14
      Width = 75
      Height = 24
      Caption = 'Create'
      TabOrder = 1
      OnClick = BitBtn1Click
      Kind = bkYes
    end
  end
  object GroupBox2: TGroupBox
    Left = 224
    Top = 0
    Width = 217
    Height = 41
    Caption = #1055#1088#1086#1074#1077#1088#1080#1090#1100' '#1087#1088#1080#1085#1072#1076#1078#1077#1078#1085#1086#1089#1090#1100' '#1084#1085#1086#1078#1077#1089#1090#1074#1091
    TabOrder = 1
    object Edit2: TEdit
      Left = 8
      Top = 16
      Width = 121
      Height = 21
      TabOrder = 0
    end
    object BitBtn2: TBitBtn
      Left = 136
      Top = 14
      Width = 75
      Height = 24
      Caption = 'Check'
      TabOrder = 1
      OnClick = BitBtn2Click
      Kind = bkHelp
    end
  end
  object GroupBox3: TGroupBox
    Left = 0
    Top = 48
    Width = 217
    Height = 41
    Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1074' '#1084#1085#1086#1078#1077#1089#1090#1074#1086
    TabOrder = 2
    object Edit3: TEdit
      Left = 8
      Top = 16
      Width = 121
      Height = 21
      TabOrder = 0
    end
    object BitBtn3: TBitBtn
      Left = 136
      Top = 14
      Width = 75
      Height = 24
      Caption = '+'
      TabOrder = 1
      OnClick = BitBtn3Click
    end
  end
  object GroupBox4: TGroupBox
    Left = 224
    Top = 48
    Width = 217
    Height = 41
    Caption = #1059#1076#1072#1083#1080#1090#1100' '#1080#1079' '#1084#1085#1086#1078#1077#1089#1090#1074#1086
    TabOrder = 3
    object Edit4: TEdit
      Left = 8
      Top = 16
      Width = 121
      Height = 21
      TabOrder = 0
    end
    object BitBtn4: TBitBtn
      Left = 136
      Top = 14
      Width = 75
      Height = 24
      Caption = '-'
      TabOrder = 1
      OnClick = BitBtn4Click
    end
  end
  object GroupBox5: TGroupBox
    Left = 0
    Top = 96
    Width = 441
    Height = 41
    Caption = #1056#1072#1089#1087#1077#1095#1072#1090#1082#1072' '#1084#1085#1086#1078#1077#1089#1090#1074#1072
    TabOrder = 4
    object Edit5: TEdit
      Left = 8
      Top = 16
      Width = 345
      Height = 21
      TabOrder = 0
    end
    object BitBtn5: TBitBtn
      Left = 360
      Top = 14
      Width = 75
      Height = 24
      Caption = 'Print'
      TabOrder = 1
      OnClick = BitBtn5Click
    end
  end
end
