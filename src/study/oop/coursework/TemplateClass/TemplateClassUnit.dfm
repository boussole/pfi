object ManForm: TManForm
  Left = 278
  Top = 237
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #1064#1072#1073#1083#1086#1085#1099' '#1082#1083#1072#1089#1089#1086#1074
  ClientHeight = 325
  ClientWidth = 773
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
    Width = 345
    Height = 209
    Caption = #1052#1085#1086#1078#1077#1089#1090#1074#1086' 1'
    TabOrder = 0
    object GroupBox5: TGroupBox
      Left = 8
      Top = 16
      Width = 329
      Height = 41
      Caption = #1057#1086#1079#1076#1072#1085#1080#1077' '#1084#1085#1086#1078#1077#1089#1090#1074#1086' '#1080#1079' n - '#1101#1083#1077#1084#1077#1085#1090#1086#1074
      TabOrder = 0
      object Edit1: TEdit
        Left = 8
        Top = 15
        Width = 233
        Height = 21
        TabOrder = 0
      end
      object BitBtn1: TBitBtn
        Left = 248
        Top = 12
        Width = 75
        Height = 25
        Caption = #1057#1086#1079#1076#1072#1090#1100
        TabOrder = 1
        OnClick = BitBtn1Click
        Kind = bkOK
      end
    end
    object GroupBox6: TGroupBox
      Left = 8
      Top = 64
      Width = 329
      Height = 41
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1101#1083#1077#1084#1077#1085#1090' '#1074' '#1084#1085#1086#1078#1077#1089#1090#1074#1086
      TabOrder = 1
      object Edit2: TEdit
        Left = 8
        Top = 15
        Width = 233
        Height = 21
        TabOrder = 0
      end
      object BitBtn2: TBitBtn
        Left = 248
        Top = 12
        Width = 75
        Height = 25
        Caption = #1044#1086#1073#1072#1074#1080#1090#1100
        TabOrder = 1
        OnClick = BitBtn2Click
      end
    end
    object GroupBox7: TGroupBox
      Left = 8
      Top = 112
      Width = 329
      Height = 41
      Caption = #1059#1076#1072#1083#1080#1090#1100' '#1101#1083#1077#1084#1077#1085#1090' '#1080#1079' '#1084#1085#1086#1078#1077#1089#1090#1074#1072
      TabOrder = 2
      object Edit3: TEdit
        Left = 8
        Top = 15
        Width = 233
        Height = 21
        TabOrder = 0
      end
      object BitBtn3: TBitBtn
        Left = 248
        Top = 12
        Width = 75
        Height = 25
        Caption = #1059#1076#1072#1083#1080#1090#1100
        TabOrder = 1
        OnClick = BitBtn3Click
      end
    end
    object GroupBox8: TGroupBox
      Left = 8
      Top = 160
      Width = 329
      Height = 41
      Caption = #1056#1072#1089#1087#1077#1095#1072#1090#1082#1072' '#1084#1085#1086#1078#1077#1089#1090#1074#1072
      TabOrder = 3
      object Edit4: TEdit
        Left = 8
        Top = 15
        Width = 233
        Height = 21
        ReadOnly = True
        TabOrder = 0
      end
      object BitBtn4: TBitBtn
        Left = 248
        Top = 12
        Width = 75
        Height = 25
        Caption = #1055#1077#1095#1072#1090#1100
        TabOrder = 1
        OnClick = BitBtn4Click
      end
    end
  end
  object GroupBox3: TGroupBox
    Left = 0
    Top = 216
    Width = 769
    Height = 105
    Caption = #1052#1085#1086#1078#1077#1089#1090#1074#1086' 3'
    TabOrder = 1
    object GroupBox13: TGroupBox
      Left = 8
      Top = 16
      Width = 249
      Height = 81
      Caption = #1055#1088#1080#1089#1074#1086#1077#1085#1080#1077
      TabOrder = 0
      object Edit9: TEdit
        Left = 8
        Top = 16
        Width = 233
        Height = 21
        ReadOnly = True
        TabOrder = 0
      end
      object BitBtn9: TBitBtn
        Left = 8
        Top = 48
        Width = 113
        Height = 25
        Caption = #1052#1085#1086#1078#1077#1089#1090#1074#1086' 1'
        TabOrder = 1
        OnClick = BitBtn9Click
      end
      object BitBtn10: TBitBtn
        Left = 128
        Top = 48
        Width = 113
        Height = 25
        Caption = #1052#1085#1086#1078#1077#1089#1090#1074#1086' 2'
        TabOrder = 2
        OnClick = BitBtn10Click
      end
    end
    object GroupBox14: TGroupBox
      Left = 264
      Top = 16
      Width = 249
      Height = 81
      Caption = #1054#1073#1098#1077#1076#1080#1085#1077#1085#1080#1077
      TabOrder = 1
      object Edit10: TEdit
        Left = 8
        Top = 16
        Width = 233
        Height = 21
        ReadOnly = True
        TabOrder = 0
      end
      object BitBtn11: TBitBtn
        Left = 8
        Top = 48
        Width = 233
        Height = 25
        Caption = #1054#1073#1098#1077#1076#1080#1085#1077#1085#1080#1077' '#1084#1085#1086#1078#1077#1089#1090#1074
        TabOrder = 1
        OnClick = BitBtn11Click
      end
    end
    object GroupBox15: TGroupBox
      Left = 520
      Top = 16
      Width = 241
      Height = 81
      Caption = #1055#1077#1088#1077#1089#1077#1095#1077#1085#1080#1077
      TabOrder = 2
      object Edit11: TEdit
        Left = 8
        Top = 16
        Width = 225
        Height = 21
        ReadOnly = True
        TabOrder = 0
      end
      object BitBtn12: TBitBtn
        Left = 8
        Top = 48
        Width = 225
        Height = 25
        Caption = #1055#1077#1088#1077#1089#1077#1095#1077#1085#1080#1077' '#1084#1085#1086#1078#1077#1089#1090#1074
        TabOrder = 1
        OnClick = BitBtn12Click
      end
    end
  end
  object GroupBox4: TGroupBox
    Left = 352
    Top = 0
    Width = 65
    Height = 153
    Caption = #1058#1080#1087
    TabOrder = 2
    object RadioButton1: TRadioButton
      Left = 4
      Top = 16
      Width = 57
      Height = 17
      Caption = 'Int'
      Checked = True
      TabOrder = 0
      TabStop = True
    end
    object RadioButton2: TRadioButton
      Left = 4
      Top = 72
      Width = 57
      Height = 17
      Caption = 'Short'
      TabOrder = 1
    end
    object RadioButton3: TRadioButton
      Left = 4
      Top = 128
      Width = 57
      Height = 17
      Caption = 'Char'
      TabOrder = 2
    end
  end
  object GroupBox2: TGroupBox
    Left = 424
    Top = 0
    Width = 345
    Height = 209
    Caption = #1052#1085#1086#1078#1077#1089#1090#1074#1086' 2'
    TabOrder = 3
    object GroupBox9: TGroupBox
      Left = 8
      Top = 16
      Width = 329
      Height = 41
      Caption = #1057#1086#1079#1076#1072#1085#1080#1077' '#1084#1085#1086#1078#1077#1089#1090#1074#1072' '#1080#1079' n - '#1101#1083#1077#1084#1077#1085#1090#1086#1074
      TabOrder = 0
      object Edit5: TEdit
        Left = 8
        Top = 15
        Width = 233
        Height = 21
        TabOrder = 0
      end
      object BitBtn5: TBitBtn
        Left = 248
        Top = 12
        Width = 75
        Height = 25
        Caption = #1057#1086#1079#1076#1072#1090#1100
        TabOrder = 1
        OnClick = BitBtn5Click
        Kind = bkYes
      end
    end
    object GroupBox10: TGroupBox
      Left = 8
      Top = 64
      Width = 329
      Height = 41
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1101#1083#1077#1084#1077#1085#1090' '#1074' '#1084#1085#1086#1078#1077#1089#1090#1074#1086
      TabOrder = 1
      object Edit6: TEdit
        Left = 8
        Top = 15
        Width = 233
        Height = 21
        TabOrder = 0
      end
      object BitBtn6: TBitBtn
        Left = 248
        Top = 12
        Width = 75
        Height = 25
        Caption = #1044#1086#1073#1072#1074#1080#1090#1100
        TabOrder = 1
        OnClick = BitBtn6Click
      end
    end
    object GroupBox11: TGroupBox
      Left = 8
      Top = 112
      Width = 329
      Height = 41
      Caption = #1059#1076#1072#1083#1080#1090#1100' '#1101#1083#1077#1084#1077#1085#1090' '#1080#1079' '#1084#1085#1086#1078#1077#1089#1090#1074#1072
      TabOrder = 2
      object Edit7: TEdit
        Left = 8
        Top = 15
        Width = 233
        Height = 21
        TabOrder = 0
      end
      object BitBtn7: TBitBtn
        Left = 248
        Top = 12
        Width = 75
        Height = 25
        Caption = #1059#1076#1072#1083#1080#1090#1100
        TabOrder = 1
        OnClick = BitBtn7Click
      end
    end
    object GroupBox12: TGroupBox
      Left = 8
      Top = 160
      Width = 329
      Height = 41
      Caption = #1056#1072#1089#1087#1077#1095#1072#1090#1082#1072' '#1084#1085#1086#1078#1077#1089#1090#1074#1072
      TabOrder = 3
      object Edit8: TEdit
        Left = 8
        Top = 15
        Width = 233
        Height = 21
        ReadOnly = True
        TabOrder = 0
      end
      object BitBtn8: TBitBtn
        Left = 248
        Top = 12
        Width = 75
        Height = 25
        Caption = #1055#1077#1095#1072#1090#1100
        TabOrder = 1
        OnClick = BitBtn8Click
      end
    end
  end
  object BitBtn13: TBitBtn
    Left = 352
    Top = 160
    Width = 65
    Height = 49
    Caption = #1054#1095#1080#1089#1090#1082#1072
    TabOrder = 4
    OnClick = BitBtn13Click
  end
end
