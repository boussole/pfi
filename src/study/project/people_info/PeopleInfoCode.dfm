object PeopleInfoForm: TPeopleInfoForm
  Left = 278
  Top = 287
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'PeopleInfoForm'
  ClientHeight = 325
  ClientWidth = 723
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 0
    Top = 42
    Width = 721
    Height = 281
    ActivePage = TabSheet1
    TabIndex = 0
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = #1054#1073#1097#1072#1103' '#1080#1085#1092#1086#1088#1084#1072#1094#1080#1103
      object GroupBox1: TGroupBox
        Left = 360
        Top = -1
        Width = 345
        Height = 41
        Caption = #1048#1084#1103' (Name)'
        TabOrder = 1
        object Edit1: TEdit
          Left = 8
          Top = 16
          Width = 329
          Height = 21
          TabOrder = 0
        end
      end
      object GroupBox2: TGroupBox
        Left = 8
        Top = -1
        Width = 345
        Height = 41
        Caption = #1060#1072#1084#1080#1083#1080#1103' (Surname)'
        TabOrder = 0
        object Edit2: TEdit
          Left = 8
          Top = 16
          Width = 329
          Height = 21
          TabOrder = 0
        end
      end
      object GroupBox3: TGroupBox
        Left = 8
        Top = 41
        Width = 345
        Height = 41
        Caption = #1054#1090#1095#1077#1089#1090#1074#1086' (Fathers name)'
        TabOrder = 2
        object Edit3: TEdit
          Left = 8
          Top = 16
          Width = 329
          Height = 21
          TabOrder = 0
        end
      end
      object GroupBox4: TGroupBox
        Left = 8
        Top = 88
        Width = 697
        Height = 157
        Caption = #1040#1076#1088#1077#1089' (Address)'
        TabOrder = 4
        object GroupBox5: TGroupBox
          Left = 8
          Top = 19
          Width = 340
          Height = 41
          Caption = #1057#1090#1088#1072#1085#1072' (Country)'
          TabOrder = 0
          object Edit4: TEdit
            Left = 8
            Top = 16
            Width = 321
            Height = 21
            TabOrder = 0
          end
        end
        object GroupBox6: TGroupBox
          Left = 352
          Top = 19
          Width = 340
          Height = 41
          Caption = #1043#1086#1088#1086#1076' (City)'
          TabOrder = 1
          object Edit6: TEdit
            Left = 8
            Top = 16
            Width = 329
            Height = 21
            TabOrder = 0
          end
        end
        object GroupBox7: TGroupBox
          Left = 352
          Top = 67
          Width = 340
          Height = 41
          Caption = #1059#1083#1080#1094#1072' (Street)'
          TabOrder = 3
          object Edit5: TEdit
            Left = 8
            Top = 16
            Width = 329
            Height = 21
            TabOrder = 0
          end
        end
        object GroupBox8: TGroupBox
          Left = 9
          Top = 67
          Width = 340
          Height = 41
          Caption = #1050#1088#1072#1081', '#1089#1077#1083#1086', '#1088#1072#1081#1086#1085' (Territory)'
          TabOrder = 2
          object Edit7: TEdit
            Left = 8
            Top = 16
            Width = 321
            Height = 21
            TabOrder = 0
          end
        end
        object GroupBox9: TGroupBox
          Left = 8
          Top = 110
          Width = 165
          Height = 41
          Caption = #1048#1085#1076#1077#1082#1089' (Index)'
          TabOrder = 4
          object Edit8: TEdit
            Left = 8
            Top = 16
            Width = 151
            Height = 21
            TabOrder = 0
          end
        end
        object GroupBox10: TGroupBox
          Left = 353
          Top = 110
          Width = 167
          Height = 41
          Caption = #1050#1086#1088#1087#1091#1089' (Corps)'
          TabOrder = 6
          object Edit9: TEdit
            Left = 8
            Top = 16
            Width = 153
            Height = 21
            TabOrder = 0
          end
        end
        object GroupBox11: TGroupBox
          Left = 525
          Top = 110
          Width = 167
          Height = 41
          Caption = #1050#1074#1072#1088#1090#1080#1088#1072' (Flat)'
          TabOrder = 7
          object Edit10: TEdit
            Left = 8
            Top = 16
            Width = 153
            Height = 21
            TabOrder = 0
          end
        end
        object GroupBox12: TGroupBox
          Left = 179
          Top = 110
          Width = 169
          Height = 41
          Caption = #1044#1086#1084' (House)'
          TabOrder = 5
          object Edit11: TEdit
            Left = 8
            Top = 16
            Width = 153
            Height = 21
            TabOrder = 0
          end
        end
      end
      object GroupBox13: TGroupBox
        Left = 360
        Top = 41
        Width = 345
        Height = 41
        Caption = #1044#1086#1084#1072#1096#1085#1080#1081' '#1090#1077#1083#1077#1092#1086#1085' (Home telephone)'
        TabOrder = 3
        object Edit12: TEdit
          Left = 8
          Top = 16
          Width = 329
          Height = 21
          TabOrder = 0
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = #1044#1086#1087#1086#1083#1085#1080#1090#1077#1083#1100#1085#1072#1103' '#1080#1085#1092#1086#1088#1084#1072#1094#1080#1103
      ImageIndex = 1
      object GroupBox14: TGroupBox
        Left = 8
        Top = 8
        Width = 329
        Height = 41
        Caption = #1044#1077#1085#1100' '#1088#1086#1078#1076#1077#1085#1080#1103' (BirthDay)'
        TabOrder = 0
        object Edit13: TEdit
          Left = 8
          Top = 16
          Width = 313
          Height = 21
          TabOrder = 0
        end
      end
      object GroupBox15: TGroupBox
        Left = 8
        Top = 64
        Width = 329
        Height = 41
        Caption = #1052#1086#1073#1080#1083#1100#1085#1099#1081' '#1090#1077#1083#1077#1092#1086#1085' (Mobile telephone)'
        TabOrder = 1
        object Edit14: TEdit
          Left = 8
          Top = 16
          Width = 313
          Height = 21
          TabOrder = 0
        end
      end
      object GroupBox16: TGroupBox
        Left = 8
        Top = 112
        Width = 329
        Height = 41
        Caption = #1040#1076#1088#1077#1089' '#1101#1083#1077#1082#1090#1088#1086#1085#1085#1086#1081' '#1087#1086#1095#1090#1099' (E - Mail)'
        TabOrder = 2
        object Edit15: TEdit
          Left = 8
          Top = 16
          Width = 313
          Height = 21
          TabOrder = 0
        end
      end
      object GroupBox17: TGroupBox
        Left = 8
        Top = 160
        Width = 329
        Height = 49
        Caption = #1053#1086#1084#1077#1088' ICQ'
        TabOrder = 3
        object Edit16: TEdit
          Left = 8
          Top = 16
          Width = 313
          Height = 21
          TabOrder = 0
        end
      end
      object GroupBox20: TGroupBox
        Left = 352
        Top = 8
        Width = 353
        Height = 201
        TabOrder = 5
        object GroupBox19: TGroupBox
          Left = 8
          Top = 104
          Width = 337
          Height = 41
          Caption = #1040#1076#1088#1077#1089' '#1088#1072#1073#1086#1090#1099' (Work'#39's address)'
          TabOrder = 2
          object Edit18: TEdit
            Left = 8
            Top = 16
            Width = 321
            Height = 21
            TabOrder = 0
          end
        end
        object GroupBox18: TGroupBox
          Left = 8
          Top = 56
          Width = 337
          Height = 41
          Caption = #1044#1086#1083#1078#1085#1086#1089#1090#1100' (Post)'
          TabOrder = 1
          object Edit17: TEdit
            Left = 8
            Top = 16
            Width = 321
            Height = 21
            TabOrder = 0
          end
        end
        object GroupBox21: TGroupBox
          Left = 8
          Top = 8
          Width = 337
          Height = 41
          Caption = #1052#1077#1089#1090#1086' '#1088#1072#1073#1086#1090#1099' (Work place)'
          TabOrder = 0
          object Edit19: TEdit
            Left = 8
            Top = 16
            Width = 321
            Height = 21
            TabOrder = 0
          end
        end
        object GroupBox22: TGroupBox
          Left = 8
          Top = 152
          Width = 337
          Height = 41
          Caption = #1056#1072#1073#1086#1095#1080#1081' '#1090#1077#1083#1077#1092#1086#1085' (Work'#39's telephone)'
          TabOrder = 3
          object Edit20: TEdit
            Left = 8
            Top = 16
            Width = 321
            Height = 21
            TabOrder = 0
          end
        end
      end
      object GroupBox23: TGroupBox
        Left = 8
        Top = 211
        Width = 329
        Height = 42
        Caption = #1053#1080#1082#1080' (Nick'#39's)'
        TabOrder = 4
        object Edit21: TEdit
          Left = 8
          Top = 16
          Width = 313
          Height = 21
          TabOrder = 0
        end
      end
      object GroupBox24: TGroupBox
        Left = 352
        Top = 211
        Width = 353
        Height = 41
        Caption = #1057#1072#1081#1090' (Site) '
        TabOrder = 6
        object Edit22: TEdit
          Left = 16
          Top = 16
          Width = 321
          Height = 21
          TabOrder = 0
        end
      end
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 721
    Height = 41
    TabOrder = 1
    object Save: TBitBtn
      Left = 9
      Top = 8
      Width = 72
      Height = 25
      Caption = 'Save'
      TabOrder = 0
      OnClick = SaveClick
    end
    object SetNewWay: TBitBtn
      Left = 265
      Top = 8
      Width = 88
      Height = 25
      Caption = 'Set New Way'
      TabOrder = 3
      OnClick = SetNewWayClick
    end
    object SetDefaultWay: TBitBtn
      Left = 168
      Top = 8
      Width = 97
      Height = 25
      Caption = 'Set Default Way'
      TabOrder = 2
      OnClick = SetDefaultWayClick
    end
    object Exit: TBitBtn
      Left = 624
      Top = 8
      Width = 86
      Height = 25
      Caption = 'Exit'
      TabOrder = 7
      OnClick = ExitClick
    end
    object ShowCurrentWay: TBitBtn
      Left = 353
      Top = 8
      Width = 98
      Height = 25
      Caption = 'Show Current Way'
      TabOrder = 4
      OnClick = ShowCurrentWayClick
    end
    object BitBtn1: TBitBtn
      Left = 81
      Top = 8
      Width = 88
      Height = 25
      Caption = 'Save As...'
      TabOrder = 1
      OnClick = BitBtn1Click
    end
    object ScreenRes: TBitBtn
      Left = 450
      Top = 8
      Width = 103
      Height = 25
      Caption = 'Screen Resolution'
      TabOrder = 5
      OnClick = ScreenResClick
    end
    object Clear: TBitBtn
      Left = 552
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Clear'
      TabOrder = 6
      OnClick = ClearClick
    end
  end
  object MainMenu1: TMainMenu
    Left = 688
    Top = 32
    object ControlPanel1: TMenuItem
      Caption = 'Control Panel'
      object Save1: TMenuItem
        Caption = 'Save'
        OnClick = SaveClick
      end
      object SaveAs: TMenuItem
        Caption = 'Save As...'
        OnClick = BitBtn1Click
      end
      object SetNewWay1: TMenuItem
        Caption = 'Set New Way'
        OnClick = SetNewWayClick
      end
      object SetdefaultWay1: TMenuItem
        Caption = 'Set Default Way'
        OnClick = SetDefaultWayClick
      end
      object ShowCurrentWay1: TMenuItem
        Caption = 'Show Current Way'
        OnClick = ShowCurrentWayClick
      end
      object ScrRes: TMenuItem
        Caption = 'Screen Resolution'
        OnClick = ScreenResClick
      end
      object Clr: TMenuItem
        Caption = 'Clear'
        OnClick = ClearClick
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object Exit1: TMenuItem
        Caption = 'Exit'
        OnClick = ExitClick
      end
    end
    object Help1: TMenuItem
      Caption = 'Help'
      object About1: TMenuItem
        Caption = 'About PeopleInfo...'
        OnClick = About1Click
      end
      object About2: TMenuItem
        Caption = 'About...'
        OnClick = About2Click
      end
    end
  end
  object SaveDialog1: TSaveDialog
    Filter = #1058#1077#1082#1089#1090#1086#1074#1099#1081' (*.txt), (*.dat)|*.txt, *dat'
    Left = 656
    Top = 32
  end
end
