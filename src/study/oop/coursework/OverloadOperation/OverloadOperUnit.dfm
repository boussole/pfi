object MainForm: TMainForm
  Left = 389
  Top = 333
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #1055#1077#1088#1077#1075#1088#1091#1079#1082#1072' '#1086#1087#1077#1088#1072#1094#1080#1081
  ClientHeight = 366
  ClientWidth = 571
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
  object Set1: TGroupBox
    Left = 0
    Top = 0
    Width = 281
    Height = 257
    Caption = #1052#1085#1086#1078#1077#1089#1090#1074#1086' 1'
    TabOrder = 0
    object GroupBox1: TGroupBox
      Left = 8
      Top = 16
      Width = 265
      Height = 41
      Caption = #1057#1086#1079#1076#1072#1085#1080#1077' '#1084#1085#1086#1078#1077#1089#1090#1074#1072' '#1080#1079' n - '#1101#1083#1077#1084#1077#1085#1090#1086#1074
      TabOrder = 0
      object Edit1: TEdit
        Left = 8
        Top = 16
        Width = 169
        Height = 21
        TabOrder = 0
      end
      object BitBtn1: TBitBtn
        Left = 182
        Top = 15
        Width = 75
        Height = 23
        Caption = #1057#1086#1079#1076#1072#1090#1100
        TabOrder = 1
        OnClick = BitBtn1Click
        Kind = bkYes
      end
    end
    object GroupBox2: TGroupBox
      Left = 8
      Top = 64
      Width = 265
      Height = 41
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1101#1083#1077#1084#1077#1085#1090' '#1074' '#1084#1085#1086#1078#1077#1089#1090#1074#1086
      TabOrder = 1
      object Edit2: TEdit
        Left = 8
        Top = 16
        Width = 169
        Height = 21
        TabOrder = 0
      end
      object BitBtn2: TBitBtn
        Left = 182
        Top = 15
        Width = 75
        Height = 23
        Caption = #1044#1086#1073#1072#1074#1080#1090#1100
        TabOrder = 1
        OnClick = BitBtn2Click
      end
    end
    object GroupBox3: TGroupBox
      Left = 8
      Top = 160
      Width = 265
      Height = 41
      Caption = #1055#1088#1086#1074#1077#1088#1080#1090#1100' '#1085#1072' '#1087#1088#1080#1085#1072#1076#1083#1077#1078#1085#1086#1089#1090#1100' '#1084#1085#1086#1078#1077#1089#1090#1074#1091
      TabOrder = 2
      object Edit3: TEdit
        Left = 8
        Top = 16
        Width = 169
        Height = 21
        TabOrder = 0
      end
      object BitBtn3: TBitBtn
        Left = 182
        Top = 15
        Width = 75
        Height = 23
        Caption = #1058#1077#1089#1090
        TabOrder = 1
        OnClick = BitBtn3Click
        Kind = bkHelp
      end
    end
    object GroupBox4: TGroupBox
      Left = 8
      Top = 112
      Width = 265
      Height = 41
      Caption = #1059#1076#1072#1083#1080#1090#1100' '#1101#1083#1077#1084#1077#1085#1090' '#1080#1079' '#1084#1085#1086#1078#1077#1089#1090#1074#1072
      TabOrder = 3
      object Edit4: TEdit
        Left = 8
        Top = 16
        Width = 169
        Height = 21
        TabOrder = 0
      end
      object BitBtn4: TBitBtn
        Left = 182
        Top = 15
        Width = 75
        Height = 23
        Caption = #1059#1076#1072#1083#1080#1090#1100
        TabOrder = 1
        OnClick = BitBtn4Click
      end
    end
    object GroupBox5: TGroupBox
      Left = 8
      Top = 208
      Width = 265
      Height = 41
      Caption = #1056#1072#1089#1087#1077#1095#1072#1090#1082#1072' '#1084#1085#1086#1078#1077#1089#1090#1074#1072
      TabOrder = 4
      object Edit5: TEdit
        Left = 8
        Top = 16
        Width = 169
        Height = 21
        ReadOnly = True
        TabOrder = 0
      end
      object BitBtn5: TBitBtn
        Left = 182
        Top = 15
        Width = 75
        Height = 23
        Caption = #1055#1077#1095#1072#1090#1100
        TabOrder = 1
        OnClick = BitBtn5Click
      end
    end
  end
  object Set3: TGroupBox
    Left = 0
    Top = 264
    Width = 569
    Height = 97
    Caption = #1052#1085#1086#1078#1077#1089#1090#1074#1086' 3'
    TabOrder = 1
    object GroupBox12: TGroupBox
      Left = 8
      Top = 16
      Width = 177
      Height = 73
      Caption = #1055#1088#1080#1089#1074#1086#1077#1085#1080#1077
      TabOrder = 0
      object Edit11: TEdit
        Left = 8
        Top = 16
        Width = 161
        Height = 21
        ReadOnly = True
        TabOrder = 0
      end
      object Button1: TButton
        Left = 8
        Top = 40
        Width = 75
        Height = 25
        Caption = #1052#1085#1086#1078#1077#1089#1090#1074#1086' 1'
        TabOrder = 1
        OnClick = Button1Click
      end
      object Button2: TButton
        Left = 96
        Top = 40
        Width = 75
        Height = 25
        Caption = #1052#1085#1086#1078#1077#1089#1090#1074#1086' 2'
        TabOrder = 2
        OnClick = Button2Click
      end
    end
    object GroupBox13: TGroupBox
      Left = 192
      Top = 16
      Width = 185
      Height = 73
      Caption = #1054#1073#1098#1077#1076#1080#1085#1077#1085#1080#1077
      TabOrder = 1
      object Edit12: TEdit
        Left = 8
        Top = 16
        Width = 169
        Height = 21
        ReadOnly = True
        TabOrder = 0
      end
      object Button3: TButton
        Left = 8
        Top = 40
        Width = 169
        Height = 25
        Caption = #1054#1073#1098#1077#1076#1080#1085#1080#1090#1100' '#1084#1085#1086#1078#1077#1089#1090#1074#1072
        TabOrder = 1
        OnClick = Button3Click
      end
    end
    object GroupBox14: TGroupBox
      Left = 384
      Top = 16
      Width = 177
      Height = 73
      Caption = #1055#1077#1088#1077#1089#1077#1095#1077#1085#1080#1077
      TabOrder = 2
      object Edit13: TEdit
        Left = 8
        Top = 16
        Width = 161
        Height = 21
        ReadOnly = True
        TabOrder = 0
      end
      object Button4: TButton
        Left = 8
        Top = 40
        Width = 161
        Height = 25
        Caption = #1057#1086#1079#1076#1072#1090#1100' '#1087#1077#1088#1077#1089#1077#1095#1077#1085#1080#1077
        TabOrder = 1
        OnClick = Button4Click
      end
    end
  end
  object GroupBox6: TGroupBox
    Left = 288
    Top = 0
    Width = 281
    Height = 257
    Caption = #1052#1085#1086#1078#1077#1089#1090#1074#1086' 2'
    TabOrder = 2
    object GroupBox7: TGroupBox
      Left = 8
      Top = 16
      Width = 265
      Height = 41
      Caption = #1057#1086#1079#1076#1072#1085#1080#1077' '#1084#1085#1086#1078#1077#1089#1090#1074#1072' '#1080#1079' n - '#1101#1083#1077#1084#1077#1085#1090#1086#1074
      TabOrder = 0
      object Edit6: TEdit
        Left = 8
        Top = 16
        Width = 169
        Height = 21
        TabOrder = 0
      end
      object BitBtn6: TBitBtn
        Left = 182
        Top = 15
        Width = 75
        Height = 23
        Caption = #1057#1086#1079#1076#1072#1090#1100
        TabOrder = 1
        OnClick = BitBtn6Click
        Kind = bkYes
      end
    end
    object GroupBox8: TGroupBox
      Left = 8
      Top = 64
      Width = 265
      Height = 41
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1101#1083#1077#1084#1077#1085#1090' '#1074' '#1084#1085#1086#1078#1077#1089#1090#1074#1086
      TabOrder = 1
      object Edit7: TEdit
        Left = 8
        Top = 16
        Width = 169
        Height = 21
        TabOrder = 0
      end
      object BitBtn7: TBitBtn
        Left = 182
        Top = 15
        Width = 75
        Height = 23
        Caption = #1044#1086#1073#1072#1074#1080#1090#1100
        TabOrder = 1
        OnClick = BitBtn7Click
      end
    end
    object GroupBox9: TGroupBox
      Left = 8
      Top = 160
      Width = 265
      Height = 41
      Caption = #1055#1088#1086#1074#1077#1088#1080#1090#1100' '#1085#1072' '#1087#1088#1080#1085#1072#1076#1083#1077#1078#1085#1086#1089#1090#1100' '#1084#1085#1086#1078#1077#1089#1090#1074#1091
      TabOrder = 2
      object Edit8: TEdit
        Left = 8
        Top = 16
        Width = 169
        Height = 21
        TabOrder = 0
      end
      object BitBtn8: TBitBtn
        Left = 182
        Top = 15
        Width = 75
        Height = 23
        Caption = #1058#1077#1089#1090
        TabOrder = 1
        OnClick = BitBtn8Click
        Kind = bkHelp
      end
    end
    object GroupBox10: TGroupBox
      Left = 8
      Top = 112
      Width = 265
      Height = 41
      Caption = #1059#1076#1072#1083#1080#1090#1100' '#1101#1083#1077#1084#1077#1085#1090' '#1080#1079' '#1084#1085#1086#1078#1077#1089#1090#1074#1072
      TabOrder = 3
      object Edit9: TEdit
        Left = 8
        Top = 16
        Width = 169
        Height = 21
        TabOrder = 0
      end
      object BitBtn9: TBitBtn
        Left = 182
        Top = 15
        Width = 75
        Height = 23
        Caption = #1059#1076#1072#1083#1080#1090#1100
        TabOrder = 1
        OnClick = BitBtn9Click
      end
    end
    object GroupBox11: TGroupBox
      Left = 8
      Top = 208
      Width = 265
      Height = 41
      Caption = #1056#1072#1089#1087#1077#1095#1072#1090#1082#1072' '#1084#1085#1086#1078#1077#1089#1090#1074#1072
      TabOrder = 4
      object Edit10: TEdit
        Left = 8
        Top = 16
        Width = 169
        Height = 21
        ReadOnly = True
        TabOrder = 0
      end
      object BitBtn10: TBitBtn
        Left = 182
        Top = 15
        Width = 75
        Height = 23
        Caption = #1055#1077#1095#1072#1090#1100
        TabOrder = 1
        OnClick = BitBtn10Click
      end
    end
  end
end
