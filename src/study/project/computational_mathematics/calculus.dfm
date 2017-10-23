object Form1: TForm1
  Left = 452
  Top = 210
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #1042#1099#1095#1080#1089#1083#1080#1090#1077#1083#1100#1085#1072#1103' '#1084#1072#1090#1077#1084#1072#1090#1080#1082#1072
  ClientHeight = 396
  ClientWidth = 644
  Color = clInactiveCaptionText
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
    Left = 8
    Top = 0
    Width = 631
    Height = 393
    ActivePage = TabSheet1
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clSilver
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabIndex = 0
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = #1050#1072#1083#1100#1082#1091#1083#1103#1090#1086#1088
      object Label1: TLabel
        Left = 192
        Top = 16
        Width = 212
        Height = 37
        Caption = #1050#1072#1083#1100#1082#1091#1083#1103#1090#1086#1088
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -32
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold, fsItalic]
        ParentFont = False
      end
      object GroupBox1: TGroupBox
        Left = 8
        Top = 64
        Width = 609
        Height = 41
        Caption = #1042#1099#1088#1072#1078#1077#1085#1080#1077
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        object Edit1: TEdit
          Left = 8
          Top = 16
          Width = 593
          Height = 21
          TabOrder = 0
          OnChange = Edit1Change
          OnKeyPress = Edit1KeyPress
        end
      end
      object BitBtn1: TBitBtn
        Left = 272
        Top = 224
        Width = 345
        Height = 33
        Caption = '&'#1042#1099#1095#1080#1089#1083#1080#1090#1100
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold, fsUnderline]
        ParentFont = False
        TabOrder = 6
        OnClick = BitBtn1Click
        Kind = bkYes
      end
      object GroupBox2: TGroupBox
        Left = 8
        Top = 120
        Width = 249
        Height = 41
        Caption = #1047#1085#1072#1095#1077#1085#1080#1077' '#1087#1077#1088#1077#1084#1077#1085#1085#1086#1081' '#1061
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        object Edit2: TEdit
          Left = 8
          Top = 16
          Width = 233
          Height = 21
          TabOrder = 0
          OnChange = Edit1Change
          OnKeyPress = Edit2KeyPress
        end
      end
      object GroupBox3: TGroupBox
        Left = 8
        Top = 168
        Width = 249
        Height = 41
        Caption = #1047#1085#1072#1095#1077#1085#1080#1077' '#1087#1077#1088#1077#1084#1077#1085#1085#1086#1081' Y'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 2
        object Edit3: TEdit
          Left = 8
          Top = 16
          Width = 233
          Height = 21
          TabOrder = 0
          OnChange = Edit1Change
          OnKeyPress = Edit2KeyPress
        end
      end
      object GroupBox4: TGroupBox
        Left = 8
        Top = 216
        Width = 249
        Height = 41
        Caption = #1047#1085#1072#1095#1077#1085#1080#1077' '#1087#1077#1088#1077#1084#1077#1085#1085#1086#1081' Z'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 3
        object Edit4: TEdit
          Left = 8
          Top = 16
          Width = 233
          Height = 21
          TabOrder = 0
          OnChange = Edit1Change
          OnKeyPress = Edit2KeyPress
        end
      end
      object GroupBox5: TGroupBox
        Left = 8
        Top = 304
        Width = 249
        Height = 41
        Caption = #1054#1090#1074#1077#1090
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 5
        object Edit5: TEdit
          Left = 8
          Top = 16
          Width = 233
          Height = 21
          TabStop = False
          ReadOnly = True
          TabOrder = 0
          OnKeyPress = Edit5KeyPress
        end
      end
      object BitBtn2: TBitBtn
        Left = 272
        Top = 310
        Width = 345
        Height = 35
        Caption = '&'#1042#1099#1093#1086#1076
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold, fsUnderline]
        ParentFont = False
        TabOrder = 7
        OnClick = BitBtn2Click
        Kind = bkClose
      end
      object GroupBox6: TGroupBox
        Left = 272
        Top = 120
        Width = 345
        Height = 97
        TabOrder = 4
        object RadioButton1: TRadioButton
          Left = 24
          Top = 16
          Width = 113
          Height = 17
          Caption = #1043#1088#1072#1076#1091#1089#1099
          Checked = True
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 0
          TabStop = True
        end
        object RadioButton2: TRadioButton
          Left = 24
          Top = 40
          Width = 113
          Height = 17
          Caption = #1056#1072#1076#1080#1072#1085#1099
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 1
        end
        object RadioButton3: TRadioButton
          Left = 24
          Top = 64
          Width = 113
          Height = 17
          Caption = #1043#1088#1072#1076#1099
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 2
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = #1053#1077#1083#1080#1085#1077#1081#1085#1099#1077' '#1091#1088#1072#1074#1085#1077#1085#1080#1103
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ImageIndex = 1
      ParentFont = False
      object PageControl2: TPageControl
        Left = 8
        Top = 8
        Width = 609
        Height = 345
        ActivePage = TabSheet3
        TabIndex = 0
        TabOrder = 0
        object TabSheet3: TTabSheet
          Caption = #1052#1077#1090#1086#1076' '#1073#1080#1089#1089#1077#1082#1094#1080#1080
          object GroupBox7: TGroupBox
            Left = 8
            Top = 8
            Width = 585
            Height = 121
            Caption = #1058#1072#1073#1083#1080#1094#1072' '#1087#1088#1080#1073#1083#1080#1078#1077#1085#1080#1081
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
            TabOrder = 0
            object StringGrid1: TStringGrid
              Left = 8
              Top = 16
              Width = 569
              Height = 97
              TabStop = False
              ColCount = 6
              DefaultColWidth = 90
              DefaultRowHeight = 14
              FixedCols = 0
              RowCount = 2
              ScrollBars = ssVertical
              TabOrder = 0
            end
          end
          object BitBtn3: TBitBtn
            Left = 257
            Top = 289
            Width = 152
            Height = 27
            Caption = #1055#1086#1080#1089#1082
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold, fsUnderline]
            ParentFont = False
            TabOrder = 7
            OnClick = BitBtn3Click
            Kind = bkOK
          end
          object GroupBox8: TGroupBox
            Left = 8
            Top = 240
            Width = 137
            Height = 75
            Caption = #1048#1085#1090#1077#1088#1074#1072#1083' '#1087#1086#1080#1089#1082#1072
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
            TabOrder = 2
            object Label2: TLabel
              Left = 8
              Top = 12
              Width = 31
              Height = 24
              Caption = 'a = '
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -19
              Font.Name = 'MS Sans Serif'
              Font.Style = []
              ParentFont = False
            end
            object Label3: TLabel
              Left = 8
              Top = 40
              Width = 32
              Height = 24
              Caption = 'b = '
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -19
              Font.Name = 'MS Sans Serif'
              Font.Style = []
              ParentFont = False
            end
            object Edit6: TEdit
              Left = 40
              Top = 16
              Width = 81
              Height = 21
              TabOrder = 0
              OnKeyPress = Edit2KeyPress
            end
            object Edit7: TEdit
              Left = 40
              Top = 40
              Width = 81
              Height = 21
              TabOrder = 1
              OnKeyPress = Edit2KeyPress
            end
          end
          object BitBtn4: TBitBtn
            Left = 440
            Top = 289
            Width = 152
            Height = 27
            Caption = '&'#1042#1099#1093#1086#1076
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold, fsUnderline]
            ParentFont = False
            TabOrder = 8
            OnClick = BitBtn2Click
            Kind = bkClose
          end
          object GroupBox9: TGroupBox
            Left = 256
            Top = 250
            Width = 337
            Height = 37
            Caption = #1054#1090#1074#1077#1090
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
            TabOrder = 6
            object Label8: TLabel
              Left = 10
              Top = 15
              Width = 21
              Height = 16
              Caption = 'X = '
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = []
              ParentFont = False
            end
            object Edit11: TEdit
              Left = 30
              Top = 12
              Width = 303
              Height = 21
              TabStop = False
              TabOrder = 0
              OnKeyPress = Edit9KeyPress
            end
          end
          object GroupBox10: TGroupBox
            Left = 8
            Top = 184
            Width = 137
            Height = 41
            Caption = #1056#1072#1073#1086#1095#1072#1103' '#1092#1086#1088#1084#1091#1083#1072
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
            TabOrder = 5
            object Label4: TLabel
              Left = 8
              Top = 16
              Width = 97
              Height = 20
              Caption = #1089' = (a+b) / 2'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -16
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
          end
          object GroupBox11: TGroupBox
            Left = 160
            Top = 184
            Width = 81
            Height = 131
            TabOrder = 3
            object RadioButton4: TRadioButton
              Left = 8
              Top = 16
              Width = 65
              Height = 17
              Caption = #1043#1088#1072#1076#1091#1089#1099
              Checked = True
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -11
              Font.Name = 'MS Sans Serif'
              Font.Style = []
              ParentFont = False
              TabOrder = 0
              TabStop = True
            end
            object RadioButton5: TRadioButton
              Left = 8
              Top = 60
              Width = 65
              Height = 17
              Caption = #1056#1072#1076#1080#1072#1085#1099
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -11
              Font.Name = 'MS Sans Serif'
              Font.Style = []
              ParentFont = False
              TabOrder = 1
            end
            object RadioButton6: TRadioButton
              Left = 8
              Top = 104
              Width = 57
              Height = 17
              Caption = #1043#1088#1072#1076#1099
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -11
              Font.Name = 'MS Sans Serif'
              Font.Style = []
              ParentFont = False
              TabOrder = 2
            end
          end
          object GroupBox12: TGroupBox
            Left = 256
            Top = 184
            Width = 337
            Height = 65
            Caption = #1058#1086#1095#1085#1086#1089#1090#1100
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
            TabOrder = 4
            object Label5: TLabel
              Left = 8
              Top = 18
              Width = 35
              Height = 13
              Caption = 'eps   = '
            end
            object Label6: TLabel
              Left = 8
              Top = 42
              Width = 31
              Height = 13
              Caption = 'eps '#39' ='
            end
            object Edit8: TEdit
              Left = 48
              Top = 16
              Width = 281
              Height = 21
              TabOrder = 0
              OnKeyPress = Edit2KeyPress
            end
            object Edit9: TEdit
              Left = 48
              Top = 40
              Width = 281
              Height = 21
              ReadOnly = True
              TabOrder = 1
              OnKeyPress = Edit9KeyPress
            end
          end
          object GroupBox13: TGroupBox
            Left = 8
            Top = 136
            Width = 585
            Height = 41
            Caption = #1060#1091#1085#1082#1094#1080#1103' '
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
            TabOrder = 1
            object Label7: TLabel
              Left = 8
              Top = 16
              Width = 48
              Height = 20
              Caption = 'f (x) ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -16
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsItalic]
              ParentFont = False
            end
            object Edit10: TEdit
              Left = 56
              Top = 16
              Width = 521
              Height = 21
              TabOrder = 0
              OnKeyPress = Edit10KeyPress
            end
          end
        end
        object TabSheet4: TTabSheet
          Caption = #1052#1077#1090#1086#1076' '#1093#1086#1088#1076
          ImageIndex = 1
          object GroupBox14: TGroupBox
            Left = 8
            Top = 8
            Width = 585
            Height = 113
            Caption = #1058#1072#1073#1083#1080#1094#1072' '#1087#1088#1080#1073#1083#1080#1078#1077#1085#1080#1081
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
            TabOrder = 2
            object StringGrid2: TStringGrid
              Left = 8
              Top = 16
              Width = 569
              Height = 89
              TabStop = False
              ColCount = 6
              DefaultColWidth = 90
              DefaultRowHeight = 14
              FixedCols = 0
              RowCount = 2
              ScrollBars = ssVertical
              TabOrder = 0
            end
          end
          object GroupBox15: TGroupBox
            Left = 8
            Top = 128
            Width = 585
            Height = 41
            Caption = #1060#1091#1085#1082#1094#1080#1103
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
            TabOrder = 0
            object Label9: TLabel
              Left = 8
              Top = 16
              Width = 48
              Height = 20
              Caption = 'f (x) ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -16
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsItalic]
              ParentFont = False
            end
            object Edit12: TEdit
              Left = 56
              Top = 16
              Width = 521
              Height = 21
              TabOrder = 0
              OnKeyPress = Edit10KeyPress
            end
          end
          object GroupBox16: TGroupBox
            Left = 264
            Top = 176
            Width = 329
            Height = 65
            Caption = #1058#1086#1095#1085#1086#1089#1090#1100
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
            TabOrder = 4
            object Label10: TLabel
              Left = 8
              Top = 20
              Width = 29
              Height = 13
              Caption = 'eps = '
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -11
              Font.Name = 'MS Sans Serif'
              Font.Style = []
              ParentFont = False
            end
            object Label11: TLabel
              Left = 8
              Top = 45
              Width = 31
              Height = 13
              Caption = 'eps '#39' ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -11
              Font.Name = 'MS Sans Serif'
              Font.Style = []
              ParentFont = False
            end
            object Edit13: TEdit
              Left = 48
              Top = 16
              Width = 273
              Height = 21
              TabOrder = 0
              OnKeyPress = Edit2KeyPress
            end
            object Edit14: TEdit
              Left = 48
              Top = 40
              Width = 273
              Height = 21
              ReadOnly = True
              TabOrder = 1
              OnKeyPress = Edit9KeyPress
            end
          end
          object GroupBox17: TGroupBox
            Left = 176
            Top = 176
            Width = 81
            Height = 139
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
            TabOrder = 3
            object RadioButton7: TRadioButton
              Left = 8
              Top = 16
              Width = 65
              Height = 17
              Caption = #1043#1088#1072#1076#1091#1089#1099
              Checked = True
              TabOrder = 0
              TabStop = True
            end
            object RadioButton8: TRadioButton
              Left = 8
              Top = 64
              Width = 65
              Height = 17
              Caption = #1056#1072#1076#1080#1072#1085#1099
              TabOrder = 1
            end
            object RadioButton9: TRadioButton
              Left = 8
              Top = 112
              Width = 57
              Height = 17
              Caption = #1043#1088#1072#1076#1099
              TabOrder = 2
            end
          end
          object GroupBox18: TGroupBox
            Left = 264
            Top = 248
            Width = 329
            Height = 43
            Caption = #1054#1090#1074#1077#1090
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
            TabOrder = 5
            object Label12: TLabel
              Left = 8
              Top = 16
              Width = 21
              Height = 16
              Caption = 'X = '
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = []
              ParentFont = False
            end
            object Edit15: TEdit
              Left = 32
              Top = 13
              Width = 289
              Height = 21
              TabStop = False
              ReadOnly = True
              TabOrder = 0
              OnKeyPress = Edit9KeyPress
            end
          end
          object GroupBox19: TGroupBox
            Left = 8
            Top = 176
            Width = 161
            Height = 57
            Caption = #1056#1072#1073#1086#1095#1072#1103' '#1092#1086#1088#1084#1091#1083#1072
            TabOrder = 6
            object Label13: TLabel
              Left = 72
              Top = 18
              Width = 19
              Height = 13
              Caption = 'b-a'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -11
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Label14: TLabel
              Left = 8
              Top = 29
              Width = 19
              Height = 13
              Caption = 'c ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -11
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Label15: TLabel
              Left = 48
              Top = 24
              Width = 6
              Height = 24
              Caption = '('
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -21
              Font.Name = 'MS Sans Serif'
              Font.Style = []
              ParentFont = False
            end
            object Label16: TLabel
              Left = 112
              Top = 24
              Width = 6
              Height = 24
              Caption = ')'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -21
              Font.Name = 'MS Sans Serif'
              Font.Style = []
              ParentFont = False
            end
            object Label17: TLabel
              Left = 31
              Top = 29
              Width = 16
              Height = 13
              Caption = 'a -'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -11
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Label18: TLabel
              Left = 57
              Top = 41
              Width = 51
              Height = 13
              Caption = 'f(b) - f(a)'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -11
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Label19: TLabel
              Left = 123
              Top = 31
              Width = 29
              Height = 13
              Caption = '* f(a)'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -11
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Label20: TLabel
              Left = 57
              Top = 29
              Width = 49
              Height = 13
              Caption = '------------'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -11
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
          end
          object GroupBox20: TGroupBox
            Left = 8
            Top = 240
            Width = 161
            Height = 75
            Caption = #1048#1085#1090#1077#1088#1074#1072#1083' '#1087#1086#1080#1089#1082#1072
            TabOrder = 1
            object Label21: TLabel
              Left = 8
              Top = 10
              Width = 26
              Height = 24
              Caption = 'a ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -19
              Font.Name = 'MS Sans Serif'
              Font.Style = []
              ParentFont = False
            end
            object Label22: TLabel
              Left = 8
              Top = 41
              Width = 27
              Height = 24
              Caption = 'b ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -19
              Font.Name = 'MS Sans Serif'
              Font.Style = []
              ParentFont = False
            end
            object Edit16: TEdit
              Left = 43
              Top = 14
              Width = 110
              Height = 21
              TabOrder = 0
              OnKeyPress = Edit2KeyPress
            end
            object Edit17: TEdit
              Left = 43
              Top = 44
              Width = 111
              Height = 21
              TabOrder = 1
              OnKeyPress = Edit2KeyPress
            end
          end
          object BitBtn5: TBitBtn
            Left = 265
            Top = 294
            Width = 152
            Height = 23
            Caption = #1055#1086#1080#1089#1082
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold, fsUnderline]
            ParentFont = False
            TabOrder = 7
            OnClick = BitBtn5Click
            Kind = bkOK
          end
          object BitBtn6: TBitBtn
            Left = 440
            Top = 294
            Width = 152
            Height = 23
            Caption = #1042#1099#1093#1086#1076
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold, fsUnderline]
            ParentFont = False
            TabOrder = 8
            OnClick = BitBtn2Click
            Kind = bkClose
          end
        end
        object TabSheet9: TTabSheet
          Caption = #1052#1077#1090#1086#1076' '#1082#1072#1089#1072#1090#1077#1083#1100#1085#1099#1093' ('#1053#1100#1102#1090#1086#1085#1072' - '#1056#1072#1092#1089#1086#1085#1072')'
          ImageIndex = 2
          object GroupBox21: TGroupBox
            Left = 8
            Top = 8
            Width = 585
            Height = 113
            Caption = #1058#1072#1073#1083#1080#1094#1072' '#1087#1088#1080#1073#1083#1080#1078#1077#1085#1080#1081
            TabOrder = 0
            object StringGrid3: TStringGrid
              Left = 8
              Top = 16
              Width = 569
              Height = 89
              TabStop = False
              ColCount = 4
              DefaultColWidth = 135
              DefaultRowHeight = 14
              FixedCols = 0
              RowCount = 2
              ScrollBars = ssVertical
              TabOrder = 0
            end
          end
          object GroupBox22: TGroupBox
            Left = 8
            Top = 128
            Width = 585
            Height = 38
            Caption = #1060#1091#1085#1082#1094#1080#1103
            TabOrder = 1
            object Label23: TLabel
              Left = 6
              Top = 14
              Width = 48
              Height = 20
              Caption = 'f (x) ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -16
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsItalic]
              ParentFont = False
            end
            object Edit18: TEdit
              Left = 59
              Top = 11
              Width = 518
              Height = 21
              TabOrder = 0
              OnKeyPress = Edit10KeyPress
            end
          end
          object GroupBox23: TGroupBox
            Left = 8
            Top = 168
            Width = 585
            Height = 41
            Caption = #1055#1077#1088#1074#1072#1103' '#1087#1088#1086#1080#1079#1074#1086#1076#1085#1072#1103' '#1092#1091#1085#1082#1094#1080#1080
            TabOrder = 2
            object Label24: TLabel
              Left = 5
              Top = 16
              Width = 55
              Height = 20
              Caption = 'f '#39' (x) ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -16
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsItalic]
              ParentFont = False
            end
            object Edit19: TEdit
              Left = 58
              Top = 15
              Width = 520
              Height = 21
              TabOrder = 0
              OnKeyPress = Edit10KeyPress
            end
          end
          object GroupBox24: TGroupBox
            Left = 8
            Top = 211
            Width = 153
            Height = 62
            Caption = #1056#1072#1073#1086#1095#1072#1103' '#1092#1086#1088#1084#1091#1083#1072
            TabOrder = 3
            object Label25: TLabel
              Left = 8
              Top = 26
              Width = 34
              Height = 24
              Caption = 'X ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -19
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Label26: TLabel
              Left = 84
              Top = 30
              Width = 56
              Height = 16
              Caption = '-----------'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Label27: TLabel
              Left = 105
              Top = 17
              Width = 11
              Height = 16
              Caption = 'Y'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Label28: TLabel
              Left = 105
              Top = 40
              Width = 19
              Height = 16
              Caption = 'Y '#39
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Label29: TLabel
              Left = 48
              Top = 26
              Width = 29
              Height = 24
              Caption = 'X -'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -19
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
          end
          object GroupBox25: TGroupBox
            Left = 168
            Top = 211
            Width = 121
            Height = 62
            Caption = #1053#1072#1095#1072#1083#1100#1085#1086#1077' '#1079#1085#1072#1095#1077#1085#1080#1077
            TabOrder = 4
            object Label32: TLabel
              Left = 8
              Top = 24
              Width = 24
              Height = 20
              Caption = #1061' ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -16
              Font.Name = 'MS Sans Serif'
              Font.Style = []
              ParentFont = False
            end
            object Edit22: TEdit
              Left = 32
              Top = 24
              Width = 78
              Height = 21
              TabOrder = 0
              OnKeyPress = Edit2KeyPress
            end
          end
          object GroupBox26: TGroupBox
            Left = 296
            Top = 211
            Width = 193
            Height = 62
            Caption = #1058#1086#1095#1085#1086#1089#1090#1100
            TabOrder = 5
            object Label30: TLabel
              Left = 9
              Top = 13
              Width = 39
              Height = 20
              Caption = 'eps ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -16
              Font.Name = 'MS Sans Serif'
              Font.Style = []
              ParentFont = False
            end
            object Label31: TLabel
              Left = 10
              Top = 36
              Width = 42
              Height = 20
              Caption = 'eps '#39'='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -16
              Font.Name = 'MS Sans Serif'
              Font.Style = []
              ParentFont = False
            end
            object Edit20: TEdit
              Left = 64
              Top = 15
              Width = 121
              Height = 21
              TabOrder = 0
              OnKeyPress = Edit2KeyPress
            end
            object Edit21: TEdit
              Left = 64
              Top = 39
              Width = 121
              Height = 21
              ReadOnly = True
              TabOrder = 1
              OnKeyPress = Edit9KeyPress
            end
          end
          object GroupBox27: TGroupBox
            Left = 496
            Top = 211
            Width = 97
            Height = 104
            TabOrder = 6
            object RadioButton10: TRadioButton
              Left = 8
              Top = 16
              Width = 73
              Height = 17
              Caption = #1043#1088#1072#1076#1091#1089#1099
              Checked = True
              TabOrder = 0
              TabStop = True
            end
            object RadioButton11: TRadioButton
              Left = 8
              Top = 48
              Width = 81
              Height = 17
              Caption = #1056#1072#1076#1080#1072#1085#1099
              TabOrder = 1
            end
            object RadioButton12: TRadioButton
              Left = 8
              Top = 80
              Width = 81
              Height = 17
              Caption = #1043#1088#1072#1076#1099
              TabOrder = 2
            end
          end
          object GroupBox28: TGroupBox
            Left = 8
            Top = 275
            Width = 281
            Height = 40
            Caption = #1054#1090#1074#1077#1090
            TabOrder = 7
            object Label34: TLabel
              Left = 8
              Top = 16
              Width = 20
              Height = 20
              Caption = 'x ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -16
              Font.Name = 'MS Sans Serif'
              Font.Style = []
              ParentFont = False
            end
            object Edit24: TEdit
              Left = 32
              Top = 16
              Width = 241
              Height = 21
              TabStop = False
              TabOrder = 0
              OnKeyPress = Edit9KeyPress
            end
          end
          object BitBtn7: TBitBtn
            Left = 296
            Top = 280
            Width = 89
            Height = 33
            Caption = #1055#1086#1080#1089#1082
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold, fsUnderline]
            ParentFont = False
            TabOrder = 8
            OnClick = BitBtn7Click
            Kind = bkOK
          end
          object BitBtn8: TBitBtn
            Left = 399
            Top = 280
            Width = 89
            Height = 33
            Caption = #1042#1099#1093#1086#1076
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold, fsUnderline]
            ParentFont = False
            TabOrder = 9
            OnClick = BitBtn2Click
            Kind = bkClose
          end
        end
      end
    end
    object TabSheet5: TTabSheet
      Caption = #1054#1076#1085#1086#1084#1077#1088#1085#1072#1103' '#1086#1087#1090#1080#1084#1080#1079#1072#1094#1080#1103
      ImageIndex = 2
      object PageControl3: TPageControl
        Left = 8
        Top = 8
        Width = 609
        Height = 353
        ActivePage = TabSheet10
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabIndex = 0
        TabOrder = 0
        object TabSheet10: TTabSheet
          Caption = #1052#1077#1090#1086#1076' '#1073#1080#1089#1089#1077#1082#1094#1080#1080
          object GroupBox29: TGroupBox
            Left = 0
            Top = 8
            Width = 601
            Height = 105
            Caption = #1058#1072#1073#1083#1080#1094#1072' '#1087#1088#1080#1073#1083#1080#1078#1077#1085#1080#1081
            TabOrder = 6
            object StringGrid4: TStringGrid
              Left = 8
              Top = 16
              Width = 585
              Height = 81
              TabStop = False
              ColCount = 6
              DefaultColWidth = 92
              DefaultRowHeight = 14
              FixedCols = 0
              RowCount = 2
              ScrollBars = ssVertical
              TabOrder = 0
            end
          end
          object GroupBox30: TGroupBox
            Left = 8
            Top = 120
            Width = 585
            Height = 41
            Caption = #1055#1077#1088#1074#1072#1103' '#1087#1088#1086#1080#1079#1074#1086#1076#1085#1072#1103' '#1092#1091#1085#1082#1094#1080#1080
            TabOrder = 0
            object Label33: TLabel
              Left = 8
              Top = 21
              Width = 34
              Height = 13
              Caption = 'F '#39' (x) ='
            end
            object Edit23: TEdit
              Left = 48
              Top = 16
              Width = 529
              Height = 21
              TabOrder = 0
              OnKeyPress = Edit10KeyPress
            end
          end
          object GroupBox31: TGroupBox
            Left = 8
            Top = 168
            Width = 129
            Height = 41
            Caption = #1056#1072#1073#1086#1095#1072#1103' '#1092#1086#1088#1084#1091#1083#1072
            TabOrder = 7
            object Label35: TLabel
              Left = 8
              Top = 16
              Width = 107
              Height = 20
              Caption = #1089' = (a + b) / 2'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -16
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
          end
          object GroupBox32: TGroupBox
            Left = 248
            Top = 168
            Width = 345
            Height = 65
            Caption = #1058#1086#1095#1085#1086#1089#1090#1100
            TabOrder = 3
            object Label38: TLabel
              Left = 8
              Top = 16
              Width = 39
              Height = 16
              Caption = 'eps ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Label39: TLabel
              Left = 8
              Top = 40
              Width = 47
              Height = 16
              Caption = 'eps '#39' ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Edit27: TEdit
              Left = 72
              Top = 8
              Width = 265
              Height = 21
              TabOrder = 0
              OnKeyPress = Edit2KeyPress
            end
            object Edit28: TEdit
              Left = 72
              Top = 32
              Width = 265
              Height = 21
              ReadOnly = True
              TabOrder = 1
              OnKeyPress = Edit9KeyPress
            end
          end
          object GroupBox33: TGroupBox
            Left = 0
            Top = 216
            Width = 137
            Height = 97
            Caption = #1048#1085#1090#1077#1088#1074#1072#1083' '#1087#1086#1080#1089#1082#1072
            TabOrder = 1
            object Label36: TLabel
              Left = 8
              Top = 16
              Width = 26
              Height = 20
              Caption = 'a ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -16
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Label37: TLabel
              Left = 8
              Top = 64
              Width = 26
              Height = 20
              Caption = 'b ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -16
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Edit25: TEdit
              Left = 40
              Top = 16
              Width = 89
              Height = 21
              TabOrder = 0
              OnKeyPress = Edit2KeyPress
            end
            object Edit26: TEdit
              Left = 40
              Top = 64
              Width = 89
              Height = 21
              TabOrder = 1
              OnKeyPress = Edit2KeyPress
            end
          end
          object GroupBox34: TGroupBox
            Left = 144
            Top = 168
            Width = 97
            Height = 145
            TabOrder = 2
            object RadioButton13: TRadioButton
              Left = 8
              Top = 16
              Width = 81
              Height = 17
              Caption = #1043#1088#1072#1076#1091#1089#1099
              Checked = True
              TabOrder = 0
              TabStop = True
            end
            object RadioButton14: TRadioButton
              Left = 8
              Top = 69
              Width = 81
              Height = 17
              Caption = #1056#1072#1076#1080#1072#1085#1099
              TabOrder = 1
            end
            object RadioButton15: TRadioButton
              Left = 8
              Top = 120
              Width = 81
              Height = 17
              Caption = #1043#1088#1072#1076#1099
              TabOrder = 2
            end
          end
          object GroupBox35: TGroupBox
            Left = 248
            Top = 240
            Width = 345
            Height = 41
            Caption = #1054#1090#1074#1077#1090
            TabOrder = 8
            object Label40: TLabel
              Left = 8
              Top = 16
              Width = 28
              Height = 20
              Caption = #1061' ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -16
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Edit29: TEdit
              Left = 48
              Top = 16
              Width = 289
              Height = 21
              TabStop = False
              ReadOnly = True
              TabOrder = 0
              OnKeyPress = Edit9KeyPress
            end
          end
          object BitBtn9: TBitBtn
            Left = 248
            Top = 288
            Width = 165
            Height = 25
            Caption = #1055#1086#1080#1089#1082
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold, fsUnderline]
            ParentFont = False
            TabOrder = 4
            OnClick = BitBtn9Click
            Kind = bkYes
          end
          object BitBtn10: TBitBtn
            Left = 428
            Top = 288
            Width = 165
            Height = 25
            Caption = #1042#1099#1093#1086#1076
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold, fsUnderline]
            ParentFont = False
            TabOrder = 5
            OnClick = BitBtn2Click
            Kind = bkClose
          end
        end
        object TabSheet11: TTabSheet
          Caption = #1052#1077#1090#1086#1076' '#1079#1086#1083#1086#1090#1086#1075#1086' '#1089#1077#1095#1077#1085#1080#1103
          ImageIndex = 1
          object GroupBox36: TGroupBox
            Left = 0
            Top = 0
            Width = 601
            Height = 113
            Caption = #1058#1072#1073#1083#1080#1094#1072' '#1087#1088#1080#1073#1083#1080#1078#1077#1085#1080#1081
            TabOrder = 6
            object StringGrid5: TStringGrid
              Left = 8
              Top = 16
              Width = 585
              Height = 89
              TabStop = False
              ColCount = 11
              DefaultColWidth = 100
              DefaultRowHeight = 14
              FixedCols = 0
              RowCount = 2
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -5
              Font.Name = 'MS Sans Serif'
              Font.Style = []
              ParentFont = False
              TabOrder = 0
            end
          end
          object GroupBox37: TGroupBox
            Left = 0
            Top = 120
            Width = 185
            Height = 73
            Caption = #1048#1085#1090#1077#1088#1074#1072#1083' '#1087#1086#1080#1089#1082#1072
            TabOrder = 1
            object Label41: TLabel
              Left = 16
              Top = 16
              Width = 31
              Height = 20
              Caption = 'a = '
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -16
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Label42: TLabel
              Left = 16
              Top = 48
              Width = 26
              Height = 20
              Caption = 'b ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -16
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Edit30: TEdit
              Left = 56
              Top = 16
              Width = 121
              Height = 21
              TabOrder = 0
              OnKeyPress = Edit2KeyPress
            end
            object Edit31: TEdit
              Left = 56
              Top = 48
              Width = 121
              Height = 21
              TabOrder = 1
              OnKeyPress = Edit2KeyPress
            end
          end
          object GroupBox38: TGroupBox
            Left = 192
            Top = 120
            Width = 209
            Height = 73
            Caption = #1058#1086#1095#1085#1086#1089#1090#1100
            TabOrder = 2
            object Label43: TLabel
              Left = 8
              Top = 16
              Width = 45
              Height = 20
              Caption = 'eps ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -16
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Label44: TLabel
              Left = 8
              Top = 48
              Width = 54
              Height = 20
              Caption = 'eps '#39' ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -16
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Edit32: TEdit
              Left = 72
              Top = 16
              Width = 129
              Height = 21
              TabOrder = 0
              OnKeyPress = Edit2KeyPress
            end
            object Edit33: TEdit
              Left = 72
              Top = 48
              Width = 129
              Height = 21
              ReadOnly = True
              TabOrder = 1
              OnKeyPress = Edit9KeyPress
            end
          end
          object GroupBox39: TGroupBox
            Left = 0
            Top = 232
            Width = 601
            Height = 41
            Caption = #1054#1090#1074#1077#1090
            TabOrder = 7
            object Label45: TLabel
              Left = 8
              Top = 16
              Width = 28
              Height = 20
              Caption = #1061' ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -16
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Edit34: TEdit
              Left = 56
              Top = 16
              Width = 537
              Height = 21
              TabStop = False
              ReadOnly = True
              TabOrder = 0
              OnKeyPress = Edit9KeyPress
            end
          end
          object BitBtn11: TBitBtn
            Left = 8
            Top = 280
            Width = 185
            Height = 33
            Caption = #1055#1086#1080#1089#1082
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold, fsUnderline]
            ParentFont = False
            TabOrder = 4
            OnClick = BitBtn11Click
            Kind = bkOK
          end
          object BitBtn12: TBitBtn
            Left = 408
            Top = 280
            Width = 185
            Height = 33
            Caption = #1042#1099#1093#1086#1076
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold, fsUnderline]
            ParentFont = False
            TabOrder = 5
            OnClick = BitBtn2Click
            Kind = bkClose
          end
          object GroupBox40: TGroupBox
            Left = 408
            Top = 120
            Width = 193
            Height = 73
            TabOrder = 3
            object RadioButton16: TRadioButton
              Left = 8
              Top = 16
              Width = 113
              Height = 17
              Caption = #1043#1088#1072#1076#1091#1089#1099
              Checked = True
              TabOrder = 0
              TabStop = True
            end
            object RadioButton17: TRadioButton
              Left = 96
              Top = 16
              Width = 81
              Height = 17
              Caption = #1056#1072#1076#1080#1072#1085#1099
              TabOrder = 1
            end
            object RadioButton18: TRadioButton
              Left = 8
              Top = 48
              Width = 113
              Height = 17
              Caption = #1043#1088#1072#1076#1099
              TabOrder = 2
            end
          end
          object GroupBox41: TGroupBox
            Left = 0
            Top = 200
            Width = 601
            Height = 33
            Caption = #1060#1091#1085#1082#1094#1080#1103
            TabOrder = 0
            object Label46: TLabel
              Left = 8
              Top = 13
              Width = 37
              Height = 16
              Caption = 'f (x) ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsItalic]
              ParentFont = False
            end
            object Edit35: TEdit
              Left = 56
              Top = 8
              Width = 537
              Height = 21
              TabOrder = 0
              OnKeyPress = Edit10KeyPress
            end
          end
        end
        object TabSheet12: TTabSheet
          Caption = #1052#1077#1090#1086#1076' '#1053#1100#1102#1090#1086#1085#1072' - '#1056#1072#1092#1089#1086#1085#1072
          ImageIndex = 2
          object GroupBox42: TGroupBox
            Left = 8
            Top = 8
            Width = 585
            Height = 113
            Caption = #1058#1072#1073#1083#1080#1094#1072' '#1087#1088#1080#1073#1083#1080#1078#1077#1085#1080#1081
            TabOrder = 8
            object StringGrid6: TStringGrid
              Left = 8
              Top = 16
              Width = 569
              Height = 89
              TabStop = False
              DefaultColWidth = 107
              DefaultRowHeight = 14
              FixedCols = 0
              RowCount = 2
              ScrollBars = ssVertical
              TabOrder = 0
            end
          end
          object GroupBox44: TGroupBox
            Left = 8
            Top = 280
            Width = 489
            Height = 41
            Caption = #1042#1090#1086#1088#1072#1103' '#1087#1088#1086#1080#1079#1074#1086#1076#1085#1072#1103' '#1092#1091#1085#1082#1094#1080#1080
            TabOrder = 2
            object Label51: TLabel
              Left = 8
              Top = 16
              Width = 55
              Height = 16
              Caption = 'F '#39#39' (x) ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Edit38: TEdit
              Left = 64
              Top = 13
              Width = 417
              Height = 21
              TabOrder = 0
              OnKeyPress = Edit10KeyPress
            end
          end
          object GroupBox45: TGroupBox
            Left = 8
            Top = 240
            Width = 489
            Height = 41
            Caption = #1055#1077#1088#1074#1072#1103' '#1087#1088#1086#1080#1079#1074#1086#1076#1085#1072#1103' '#1092#1091#1085#1082#1094#1080#1080
            TabOrder = 1
            object Label50: TLabel
              Left = 8
              Top = 16
              Width = 51
              Height = 16
              Caption = 'F '#39' (x) ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Edit37: TEdit
              Left = 64
              Top = 14
              Width = 417
              Height = 21
              TabOrder = 0
              OnKeyPress = Edit10KeyPress
            end
          end
          object GroupBox46: TGroupBox
            Left = 8
            Top = 200
            Width = 489
            Height = 33
            Caption = #1060#1091#1085#1082#1094#1080#1103
            TabOrder = 0
            object Label49: TLabel
              Left = 8
              Top = 14
              Width = 37
              Height = 16
              Caption = 'f (x) ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsItalic]
              ParentFont = False
            end
            object Edit36: TEdit
              Left = 64
              Top = 8
              Width = 417
              Height = 21
              TabOrder = 0
              OnKeyPress = Edit10KeyPress
            end
          end
          object GroupBox47: TGroupBox
            Left = 8
            Top = 128
            Width = 185
            Height = 73
            Caption = #1058#1086#1095#1085#1086#1089#1090#1100
            TabOrder = 3
            object Label47: TLabel
              Left = 8
              Top = 16
              Width = 39
              Height = 16
              Caption = 'eps ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Label48: TLabel
              Left = 8
              Top = 48
              Width = 47
              Height = 16
              Caption = 'eps '#39' ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Edit39: TEdit
              Left = 64
              Top = 16
              Width = 113
              Height = 21
              TabOrder = 0
              OnKeyPress = Edit2KeyPress
            end
            object Edit40: TEdit
              Left = 64
              Top = 48
              Width = 113
              Height = 21
              ReadOnly = True
              TabOrder = 1
              OnKeyPress = Edit9KeyPress
            end
          end
          object GroupBox43: TGroupBox
            Left = 296
            Top = 128
            Width = 297
            Height = 41
            Caption = #1054#1090#1074#1077#1090
            TabOrder = 9
            object Label52: TLabel
              Left = 8
              Top = 21
              Width = 20
              Height = 13
              Caption = #1061' ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -11
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Edit41: TEdit
              Left = 32
              Top = 16
              Width = 257
              Height = 21
              TabStop = False
              ReadOnly = True
              TabOrder = 0
              OnKeyPress = Edit9KeyPress
            end
          end
          object GroupBox48: TGroupBox
            Left = 200
            Top = 128
            Width = 89
            Height = 41
            Caption = 'Xo'
            TabOrder = 4
            object Edit42: TEdit
              Left = 8
              Top = 16
              Width = 73
              Height = 21
              TabOrder = 0
              OnKeyPress = Edit2KeyPress
            end
          end
          object BitBtn13: TBitBtn
            Left = 200
            Top = 176
            Width = 185
            Height = 25
            Caption = #1055#1086#1080#1089#1082
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold, fsUnderline]
            ParentFont = False
            TabOrder = 6
            OnClick = BitBtn13Click
            Kind = bkOK
          end
          object BitBtn14: TBitBtn
            Left = 408
            Top = 176
            Width = 185
            Height = 25
            Caption = #1042#1099#1093#1086#1076
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold, fsUnderline]
            ParentFont = False
            TabOrder = 7
            OnClick = BitBtn2Click
            Kind = bkClose
          end
          object GroupBox49: TGroupBox
            Left = 504
            Top = 208
            Width = 89
            Height = 113
            TabOrder = 5
            object RadioButton19: TRadioButton
              Left = 8
              Top = 8
              Width = 73
              Height = 17
              Caption = #1043#1088#1072#1076#1091#1089#1099
              Checked = True
              TabOrder = 0
              TabStop = True
            end
            object RadioButton20: TRadioButton
              Left = 8
              Top = 48
              Width = 73
              Height = 17
              Caption = #1056#1072#1076#1080#1072#1085#1099
              TabOrder = 1
            end
            object RadioButton21: TRadioButton
              Left = 8
              Top = 88
              Width = 57
              Height = 17
              Caption = #1043#1088#1072#1076#1099
              TabOrder = 2
            end
          end
        end
      end
    end
    object TabSheet7: TTabSheet
      Caption = #1063#1080#1089#1083#1077#1085#1085#1086#1077' '#1080#1085#1090#1077#1075#1088#1080#1088#1086#1074#1072#1085#1080#1077
      ImageIndex = 4
      object PageControl5: TPageControl
        Left = 8
        Top = 8
        Width = 609
        Height = 353
        ActivePage = TabSheet16
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabIndex = 0
        TabOrder = 0
        object TabSheet16: TTabSheet
          Caption = #1052#1077#1090#1086#1076' '#1087#1088#1103#1084#1086#1091#1075#1086#1083#1100#1085#1080#1082#1086#1074
          object GroupBox68: TGroupBox
            Left = 8
            Top = 8
            Width = 585
            Height = 41
            Caption = #1060#1091#1085#1082#1094#1080#1103
            TabOrder = 0
            object Label91: TLabel
              Left = 2
              Top = 18
              Width = 53
              Height = 16
              Caption = 'f ( x ) ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold, fsItalic]
              ParentFont = False
            end
            object Edit61: TEdit
              Left = 56
              Top = 16
              Width = 521
              Height = 21
              TabOrder = 0
              OnKeyPress = Edit10KeyPress
            end
          end
          object GroupBox69: TGroupBox
            Left = 8
            Top = 56
            Width = 233
            Height = 73
            Caption = #1048#1085#1090#1077#1088#1074#1072#1083
            TabOrder = 1
            object Label92: TLabel
              Left = 8
              Top = 21
              Width = 22
              Height = 16
              Caption = 'a ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Label93: TLabel
              Left = 8
              Top = 44
              Width = 22
              Height = 16
              Caption = 'b ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Edit62: TEdit
              Left = 32
              Top = 16
              Width = 193
              Height = 21
              TabOrder = 0
              OnKeyPress = Edit2KeyPress
            end
            object Edit63: TEdit
              Left = 32
              Top = 40
              Width = 193
              Height = 21
              TabOrder = 1
              OnKeyPress = Edit2KeyPress
            end
          end
          object GroupBox70: TGroupBox
            Left = 8
            Top = 136
            Width = 233
            Height = 49
            Caption = #1064#1072#1075
            TabOrder = 2
            object Label94: TLabel
              Left = 8
              Top = 20
              Width = 21
              Height = 16
              Caption = 'h ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Edit64: TEdit
              Left = 32
              Top = 16
              Width = 193
              Height = 21
              TabOrder = 0
              OnKeyPress = Edit2KeyPress
            end
          end
          object GroupBox71: TGroupBox
            Left = 256
            Top = 56
            Width = 89
            Height = 129
            TabOrder = 3
            object RadioButton31: TRadioButton
              Left = 8
              Top = 16
              Width = 73
              Height = 17
              Caption = #1043#1088#1072#1076#1091#1089#1099
              Enabled = False
              TabOrder = 0
            end
            object RadioButton32: TRadioButton
              Left = 8
              Top = 56
              Width = 65
              Height = 17
              Caption = #1056#1072#1076#1080#1072#1085#1099
              Checked = True
              TabOrder = 1
              TabStop = True
            end
            object RadioButton33: TRadioButton
              Left = 8
              Top = 96
              Width = 57
              Height = 17
              Caption = #1043#1088#1072#1076#1099
              Enabled = False
              TabOrder = 2
            end
          end
          object GroupBox72: TGroupBox
            Left = 7
            Top = 192
            Width = 589
            Height = 129
            Caption = #1056#1077#1079#1091#1083#1100#1090#1072#1090' '#1074#1099#1095#1080#1089#1083#1077#1085#1080#1081
            TabOrder = 5
            object BitBtn21: TBitBtn
              Left = 416
              Top = 64
              Width = 155
              Height = 25
              Caption = #1042#1099#1095#1080#1089#1083#1080#1090#1100
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold, fsUnderline]
              ParentFont = False
              TabOrder = 0
              OnClick = BitBtn21Click
              Kind = bkYes
            end
            object BitBtn22: TBitBtn
              Left = 416
              Top = 96
              Width = 155
              Height = 25
              Caption = #1042#1099#1093#1086#1076
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold, fsUnderline]
              ParentFont = False
              TabOrder = 1
              Kind = bkClose
            end
            object GroupBox74: TGroupBox
              Left = 8
              Top = 16
              Width = 569
              Height = 41
              Caption = #1047#1085#1072#1095#1077#1085#1080#1077' '#1080#1085#1090#1077#1075#1088#1072#1083#1072
              TabOrder = 2
              object Edit65: TEdit
                Left = 8
                Top = 16
                Width = 553
                Height = 21
                TabStop = False
                ReadOnly = True
                TabOrder = 0
                OnKeyPress = Edit5KeyPress
              end
            end
            object GroupBox75: TGroupBox
              Left = 8
              Top = 80
              Width = 401
              Height = 41
              Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1088#1072#1079#1073#1080#1077#1085#1080#1081
              TabOrder = 3
              object Edit66: TEdit
                Left = 8
                Top = 16
                Width = 385
                Height = 21
                TabStop = False
                ReadOnly = True
                TabOrder = 0
                OnKeyPress = Edit5KeyPress
              end
            end
          end
          object GroupBox73: TGroupBox
            Left = 360
            Top = 56
            Width = 233
            Height = 129
            Caption = #1052#1077#1090#1086#1076#1099
            TabOrder = 4
            object RadioButton34: TRadioButton
              Left = 8
              Top = 16
              Width = 169
              Height = 17
              Caption = #1051#1077#1074#1099#1093'  '#1087#1088#1103#1084#1086#1091#1075#1086#1083#1100#1085#1080#1082#1086#1074
              Checked = True
              TabOrder = 0
              TabStop = True
            end
            object RadioButton35: TRadioButton
              Left = 8
              Top = 56
              Width = 185
              Height = 17
              Caption = #1062#1077#1085#1090#1088#1072#1083#1100#1085#1099#1093' '#1087#1088#1103#1084#1086#1091#1075#1086#1083#1100#1085#1080#1082#1086#1074
              TabOrder = 1
            end
            object RadioButton36: TRadioButton
              Left = 8
              Top = 96
              Width = 169
              Height = 17
              Caption = #1055#1088#1072#1074#1099#1093' '#1087#1088#1103#1084#1086#1091#1075#1086#1083#1100#1085#1080#1082#1086#1074
              TabOrder = 2
            end
          end
        end
        object TabSheet17: TTabSheet
          Caption = #1052#1077#1090#1086#1076' '#1090#1088#1072#1087#1077#1094#1080#1080
          ImageIndex = 1
          object GroupBox76: TGroupBox
            Left = 8
            Top = 8
            Width = 585
            Height = 41
            Caption = #1060#1091#1085#1082#1094#1080#1103
            TabOrder = 0
            object Label95: TLabel
              Left = 8
              Top = 18
              Width = 53
              Height = 16
              Caption = 'f ( x ) ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold, fsItalic]
              ParentFont = False
            end
            object Edit67: TEdit
              Left = 64
              Top = 16
              Width = 513
              Height = 21
              TabOrder = 0
              OnKeyPress = Edit10KeyPress
            end
          end
          object GroupBox77: TGroupBox
            Left = 8
            Top = 56
            Width = 185
            Height = 73
            Caption = #1048#1085#1090#1077#1088#1074#1072#1083
            TabOrder = 1
            object Label96: TLabel
              Left = 5
              Top = 21
              Width = 22
              Height = 16
              Caption = 'a ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Label97: TLabel
              Left = 5
              Top = 46
              Width = 22
              Height = 16
              Caption = 'b ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Edit68: TEdit
              Left = 32
              Top = 16
              Width = 145
              Height = 21
              TabOrder = 0
              OnKeyPress = Edit2KeyPress
            end
            object Edit69: TEdit
              Left = 32
              Top = 42
              Width = 145
              Height = 21
              TabOrder = 1
              OnKeyPress = Edit2KeyPress
            end
          end
          object GroupBox78: TGroupBox
            Left = 200
            Top = 56
            Width = 105
            Height = 129
            TabOrder = 3
            object RadioButton37: TRadioButton
              Left = 8
              Top = 16
              Width = 73
              Height = 17
              Caption = #1043#1088#1072#1076#1091#1089#1099
              Enabled = False
              TabOrder = 0
            end
            object RadioButton38: TRadioButton
              Left = 8
              Top = 60
              Width = 73
              Height = 17
              Caption = #1056#1072#1076#1080#1072#1085#1099
              Checked = True
              TabOrder = 1
              TabStop = True
            end
            object RadioButton39: TRadioButton
              Left = 8
              Top = 104
              Width = 65
              Height = 17
              Caption = #1043#1088#1072#1076#1099
              Enabled = False
              TabOrder = 2
            end
          end
          object GroupBox79: TGroupBox
            Left = 8
            Top = 192
            Width = 585
            Height = 129
            Caption = #1056#1077#1079#1091#1083#1100#1090#1072#1090' '#1074#1099#1095#1080#1089#1083#1077#1085#1080#1081
            TabOrder = 4
            object GroupBox80: TGroupBox
              Left = 8
              Top = 16
              Width = 569
              Height = 41
              Caption = #1047#1085#1072#1095#1077#1085#1080#1077' '#1080#1085#1090#1077#1075#1088#1072#1083#1072
              TabOrder = 3
              object Edit70: TEdit
                Left = 8
                Top = 16
                Width = 553
                Height = 21
                TabStop = False
                ReadOnly = True
                TabOrder = 0
                OnKeyPress = Edit5KeyPress
              end
            end
            object GroupBox81: TGroupBox
              Left = 8
              Top = 80
              Width = 393
              Height = 41
              Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1088#1072#1079#1073#1080#1077#1085#1080#1081
              TabOrder = 2
              object Edit71: TEdit
                Left = 8
                Top = 16
                Width = 377
                Height = 21
                TabStop = False
                ReadOnly = True
                TabOrder = 0
                OnKeyPress = Edit5KeyPress
              end
            end
            object BitBtn23: TBitBtn
              Left = 413
              Top = 64
              Width = 155
              Height = 25
              Caption = #1042#1099#1095#1080#1089#1083#1080#1090#1100
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold, fsUnderline]
              ParentFont = False
              TabOrder = 0
              OnClick = BitBtn23Click
              Kind = bkYes
            end
            object BitBtn24: TBitBtn
              Left = 413
              Top = 96
              Width = 155
              Height = 25
              Caption = #1042#1099#1093#1086#1076
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold, fsUnderline]
              ParentFont = False
              TabOrder = 1
              Kind = bkClose
            end
          end
          object GroupBox82: TGroupBox
            Left = 8
            Top = 136
            Width = 185
            Height = 49
            Caption = #1064#1072#1075
            TabOrder = 2
            object Label98: TLabel
              Left = 8
              Top = 21
              Width = 21
              Height = 16
              Caption = 'h ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Edit72: TEdit
              Left = 32
              Top = 16
              Width = 145
              Height = 21
              TabOrder = 0
              OnKeyPress = Edit2KeyPress
            end
          end
          object GroupBox83: TGroupBox
            Left = 320
            Top = 56
            Width = 273
            Height = 129
            Caption = #1056#1072#1073#1086#1095#1072#1103' '#1092#1086#1088#1084#1091#1083#1072
            TabOrder = 5
            object Image1: TImage
              Left = 16
              Top = 16
              Width = 241
              Height = 105
              Picture.Data = {
                07544269746D61704A680000424D4A680000000000003604000028000000F100
                0000690000000100080000000000146400000000000000000000000100000000
                000000000000000080000080000000808000800000008000800080800000C0C0
                C000C0DCC000F0CAA6000020400000206000002080000020A0000020C0000020
                E00000400000004020000040400000406000004080000040A0000040C0000040
                E00000600000006020000060400000606000006080000060A0000060C0000060
                E00000800000008020000080400000806000008080000080A0000080C0000080
                E00000A0000000A0200000A0400000A0600000A0800000A0A00000A0C00000A0
                E00000C0000000C0200000C0400000C0600000C0800000C0A00000C0C00000C0
                E00000E0000000E0200000E0400000E0600000E0800000E0A00000E0C00000E0
                E00040000000400020004000400040006000400080004000A0004000C0004000
                E00040200000402020004020400040206000402080004020A0004020C0004020
                E00040400000404020004040400040406000404080004040A0004040C0004040
                E00040600000406020004060400040606000406080004060A0004060C0004060
                E00040800000408020004080400040806000408080004080A0004080C0004080
                E00040A0000040A0200040A0400040A0600040A0800040A0A00040A0C00040A0
                E00040C0000040C0200040C0400040C0600040C0800040C0A00040C0C00040C0
                E00040E0000040E0200040E0400040E0600040E0800040E0A00040E0C00040E0
                E00080000000800020008000400080006000800080008000A0008000C0008000
                E00080200000802020008020400080206000802080008020A0008020C0008020
                E00080400000804020008040400080406000804080008040A0008040C0008040
                E00080600000806020008060400080606000806080008060A0008060C0008060
                E00080800000808020008080400080806000808080008080A0008080C0008080
                E00080A0000080A0200080A0400080A0600080A0800080A0A00080A0C00080A0
                E00080C0000080C0200080C0400080C0600080C0800080C0A00080C0C00080C0
                E00080E0000080E0200080E0400080E0600080E0800080E0A00080E0C00080E0
                E000C0000000C0002000C0004000C0006000C0008000C000A000C000C000C000
                E000C0200000C0202000C0204000C0206000C0208000C020A000C020C000C020
                E000C0400000C0402000C0404000C0406000C0408000C040A000C040C000C040
                E000C0600000C0602000C0604000C0606000C0608000C060A000C060C000C060
                E000C0800000C0802000C0804000C0806000C0808000C080A000C080C000C080
                E000C0A00000C0A02000C0A04000C0A06000C0A08000C0A0A000C0A0C000C0A0
                E000C0C00000C0C02000C0C04000C0C06000C0C08000C0C0A000F0FBFF00A4A0
                A000808080000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
                FF00070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070700000007070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070700000007070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070000000707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070000000707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070000000707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707000000070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707000000070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070700
                0000070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070700000007070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070700000007070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070000000707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070000000707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070000000707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707000000070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707000000070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707000007075200A40707070707070707070707070707070700000707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070700
                0000070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070700000707004907070707
                0707070707070707070707070700000707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070700000007070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                070707070707070707070000A45B00A407070707070707070707070707070707
                0700000707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070700000007070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070000
                0000490707070707000000000000070707070707070000070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070000000707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                070707070707070707070707070707070707000000009B070707070707070707
                0707070707070707070000070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070000000707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070000A40000A40707070700000000000007070707074907000007
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070000000707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707000007A40000
                A407070707070707070707070707070049000007070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707000000070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707000007070707070707070707070707070707
                070707A449000007070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707000000070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707000007070707070707070707070707070707070707070752000707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070700
                0000070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070700000007070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070000000000000000000707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070700000007070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707075200000000000000000707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070700000000
                0000000000000000000000000000000000000000000000070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070000000707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070000009B07070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070700000000000000000000000000000000
                0000000000000000000000070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070000000707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707079B000000A4070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070700000000000000000000000000000000000000000000000000000007
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070000000707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0752000000A40707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070000000000000000
                0000000000000000000000000000000000000007070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707000000070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070700000000A40707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070000000000000707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707000000070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                07070707070707070707A4000000490707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0700000000000007070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070700
                0000070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                07070707070707070707070707070707070707070707070707070707070707A4
                0000009B07070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070700000000000007070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070700000007070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                07070707070707070707070707070707070707075B0000490707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707000000000000070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070700000007070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070000000707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0000000000000707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070000000707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707490000070707000000
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070000000000000707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070000000707070707070707000000000000
                0000000000000000070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                07070707070707070707075200005B079B000052070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070700000000000007070707070707070707070707070707
                0707070707070707070707070707070707A40000490707070707070707070707
                0707070707070707070707070707070707070707490000A40707070707070707
                0707070000000707070707070707000000000000000000000000000007070707
                0707070707070707070707070707070707070707070707070707070707070707
                07070707070707070707070707070707070707070707070707070707070707A4
                00000000000000A4070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070700
                0000000000070707070707070707070707070707070707070707070707070707
                07070707070000009B0707070707070707070707070707070707070707070707
                07070707070707079B0000000707070707070707070707000000070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707A40000
                5207070707070707070707070707070707070707075200000052A40707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707000000000000070707070707
                0707070707070707070707070707070707070707070707079B00000007070707
                0707070707070707070707070707070707070707070707070707070707000000
                9B07070707070707070707000000070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707490000A40707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070000000000000707070707070707070707070707070707
                0707070707070707070707074900005207070707070707070707070707070707
                0707070707070707070707070707070707520000490707070707070707070700
                0000070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                070707079B000000070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070000
                00000000070707070707070707070707070707070707070707070707070707A4
                000000A407070707070707070707070707070707070707070707000007070000
                0707070707A4000000A407070707070707070700000007070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707074900005B07070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070700000000000007070707070707
                0707070707070707070707070707070707070752000000070707070707070707
                0707070707070707070707070707000007000007070707070707000000520707
                0707070707070700000007070707070707070707070707000000000707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707A4000000F707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707000000000000070707070707070707070707070707000000
                000707070707070000004907070707A400000000A407070707070707A4000000
                00A4000000000707070707070707490000000707070707070707070000000707
                0707070707070707070707000000000707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070752
                0000000707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707000000
                0000000707070707070707070707070707000000000707070707A40000005207
                0707070752000000000707070707070700000000520700000007070707070707
                070752000000A407070707070707070000000707070707070707070707070700
                0000000707070707070707070707070707070707070707070707070707070707
                0707070000000007070707070000000007070700000052070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070000000000000707070707070707
                07070707070000000007070707079B0000009B070707070707000000009B0707
                0707079B0000000007070000000007070707070707079B0000009B0707070707
                0707070000000707070707070707070707070700000000070707070707070707
                0707070707070707070707070707070707070707070707000000000707070707
                000000000707A40000009B070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070000000007070707070707070707070707070707
                0707070707070700000000000007070707070707070707070700000000070707
                070752000000A40707070707079B000000000707070707000000009B07070000
                07000007070707070707A4000000520707070707070707000000070707070707
                0707070707070700000000070707070707070707070707070707070707070707
                07070707070707070707070000000007070707070000000007075B000000F707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0000000007070707070707070707070707070707070707070707070700000000
                0000070707070707070707070700000000070707070749000000A40707070707
                0707490000005B0707075B00000049070707000007070000070707070707A400
                0000490707070707070707000000070707070707070707070707070000000007
                0707070707070707070700000000000000000000000000000007070707070700
                000000070707070700000000070752000000F707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707000000000707070707070707
                0707070707070707070707070707070707000000000000070707070707070707
                07000000000707070707000000000707070707070707A4000000000707070000
                0000A40707070000070707070707070707070700000000070707070707070700
                0000070707070707070707070707070000000007070707070707070707070000
                0000000000000000000000000007070707070700000000070707070700000000
                0707000000000707070000000000000000000000000000000000000000000000
                0000000000000000000000000000000000000000000000000000070707070707
                0707070707070707000000000707070707070707070707070707070707070707
                0707070707070000000000000707070707070707070000000007070707070000
                0000070707070707070707520000005207520000005207070707000007070707
                0707070707070700000000070707070707070700000007070707070707070707
                0707070000000007070707070707070707070000000000000000000000000000
                0007070707070700000000070707070700000000070700000000070707000000
                0000000000000000000000000000000000000000000000000000000000000000
                0000000000000000000000000000070707070707070707070707070700000000
                0707070707070707070707070707070707070707070707070707070000000000
                0007070707070707070000000007070707070000000007070707070707070707
                00000000A4000000000707070707000007070707070707070707070000000007
                0707070707070700000007070707070707070707070707000000000707070707
                0707070707070000000000000000000000000000000707070707070000000007
                0707070700000000070700000000070707000000000000000000000000000000
                0000000000000000000000000000000000000000000000000000000000000000
                0000070707070707070707000000000000000000000000000007070707070707
                0707070707070707070707070707070700000000000007070707070707000000
                00070707070700000000070707070707070707079B000000000000005B070707
                0707070707070707070707070707070000000007070707070707070000000707
                0707070707070707070707000000000707070707070707070707070707070707
                0707070707070707070707070707070000000007070707070000000007070000
                0000070707000000000000000000000000000000000000000000000000000000
                0000000000000000000000000000000000000000000007070707070707070700
                0000000000000000000000000007070707070707070707070707070707070707
                0707070700000000000007070707070707000000000707070707000000000707
                0707070707070707074900000000000007070707070707070707070707070707
                0707070000000007070707070707070000000707070707070707070707070700
                0000000707070707070707070707070707070707070707070707070707070707
                0707070000000007070707070000000007070000000007070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070700000000000000000000000000
                0007070707070707070707070707070707070707070707070000000000000707
                070707070700000000070707070749000000A407070707070707070707A40000
                000000A4070707070707070707070707070707070707A4000000490707070707
                0707070000000707070707070707070707070700000000070707070707070707
                070707070707070707070707070707070707070707070700000000F707070707
                00000000070752000000F7070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070700000000000000000000000000000707070707070707070707
                0707070707070707070707070000000000000707070707070700000000070707
                070752000000A407070707070707070707070000000000070707070707070707
                07070707070707070707A4000000520707070707070707000000070707070707
                0707070707070700000000070707070707070707070700000000000000000000
                0000000000070707070707000000009B070707F700000000070752000000F707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0000000007070707070707070707070707070707070707070707070707070700
                000000000007070707070707070000000007070707075B0000009B0707070707
                07070707079B00000000005B0707070707070707070707070707070707079B00
                00005B0707070707070707000000070707070707070707070707070000000007
                0707070707070707070700000000000000000000000000000007070707070700
                00000000A4070752000000490707A40000009B07070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707000000000707070707070707
                0707070707070707070707070707070707070000000000000707070707070700
                00000000000000000707A4000000520707070707070707070700000000000000
                07070707070707070707070707070707070752000000A4070707070707070700
                0000070707070707070707070707070000000007070707070707070707070000
                000000000000000000000000000707070707070000000000000000000000009B
                0707070000005207070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707000000000707070707070707070707070707070707070707
                0707070707000000000000070707070707070700000000000000000007070700
                0000490707070707070707075200000000000000520707070707070707070707
                0707070707074900000007070707070707070700000007070707070707070707
                0707070000000007070707070707070707070000000000000000000000000000
                0007070707070700000000520000000000004907070707490000000707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070700000000
                0707070707070707070707070707070707070707070707070000000000000707
                07070707070707000000000000000000070707520000000707070707070707A4
                000000000700000000A407070707070707070707070707070707000000520707
                0707070707070700000007070707070707070707070707000000000707070707
                0707070707070707070707070707070707070707070707070707070000000007
                A4520000499B0707070707A4000000A407070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070700000000070707070707070707070707
                0707070707070707070707000000000000070707070707070707070707000000
                00070707070707A40000009B07070707070707490000005B075B000000490707
                070707070707070707070707079B000000A40707070707070707070000000707
                0707070707070707070707000000000707070707070707070707070707070707
                0707070707070707070707070707070000000007070707070707070707070707
                0000005207070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707000007075200A40707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070000
                000000000707070707070707070707070700000000A407070707070700000052
                0707070707079B00000000070707000000009B07070707070707070707070707
                0752000000070707070707070707070000000707070707070707070707070700
                0000000707070707070707070707070707070707070707070707070707070707
                07070700000000070707070707070707070707079B0000000707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707000007070049070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707000000000000070707070707070707
                070707070700000000000000520707079B000000070707070707000000009B07
                07079B0000000007070707070707070707070707070000009B07070707070707
                0707070000000707070707070707070707070700000000070707070707070707
                0707070707070707070707070707070707070707070707000000000707070707
                070707070707070707490000A407070707070707070707070752000052070707
                070707070707070707070707070707070707070707070000A45B00A407070707
                0707070707070707070707070707070707070707070707070707070707070707
                070707070000000000000707070707070707070707070707079B000000000000
                49070707070000009B0707070752000000000707070707000000005207070707
                07070707070707079B0000000707070707070707070707000000070707070707
                0707070707070700000000070707070707070707070707070707070707070707
                0707070707070707070707000000000707070707070707070707070707A40000
                49070707070707070707070752009B9B00520707070707070707070707070707
                0707070707070707070700000000490707070707070707070707070707070707
                0707070707070707070707070707070707070707070707000000000000070707
                0707070707070707070707070707A452000000495207070707A4000049070707
                A400000000A40707070707A400000000A40707070707070707070707490000A4
                0707070707070707070707000000070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070700
                0000000707070707070707070707070707070707070707070707000007070707
                4900F7F700000707070707070707070707070707070707070700000707070000
                00009B0707070707070707070707070707070707070707070707070707070707
                0707070707070707070700000000000007070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070700
                0000070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                07070707070707070707070707070000070707070000F7F70000070707070707
                0707070707070707070707070700000707070000A40000A40707070707070707
                0707070707070707070707070707070707070707070707070707070707000000
                0000000707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070700000007070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                07070000070707070000F7F70000070707070700000707070707070707070707
                070000070707000007A40000A407070707070707070707070707070707070707
                0707070707070707070707070707070700000000000007070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070700000007070707070707070000000000000000000000000000
                0707070707070707070707070707070707070707070707070707070707070707
                070707070707070707070707070707070707070707070000070707070000F7F7
                0000070707070700000707070707070707070707070000070707000007070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070000000000000707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070000000707
                0707070707070000000000000000000000000000070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                070707070707070707070000070707070000F7F7000007070707070000070707
                0707070707070707070000070707000007070707070707070707070707070707
                0707070707070707070707070707070707070707070700000000000007070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070000000707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707A40000
                A407070752009B9B0052070700000000000000000707070707070707A40000A4
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070000000000000707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070000000707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707000000000707070752000052070707
                0000000000000000070707070707070700000000070707070707070707070707
                0707070707070707070707070707070707070707070707070707070700000000
                0000070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707000000070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070752005B5B005207070707070707070707070707000007070707070707
                07070752005B5B00520707070707070707070707070707070707070707070707
                0707070707070707070707070707070000000000000707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707000000070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707A4000007070000A407
                07070707070707070707070000070707070707070707A4000007070000A40707
                0707070707070707070707070707070707070707070707070707070707070707
                0707000000000000070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070700
                0000070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                07070707070707070707070000A40707A4000007070707070707070707070700
                000707070707070707070000A40707A400000707070707070707070707070707
                0707070707070707070707070707070707070707070000000000000707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070700000007070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707075B00
                520707070752005B0707070707070707070707070707070707070707075B0052
                0707070752005B07070707070707070707070707070707070707070707070707
                0707070707070707000000000000000000000000000000000000000000000000
                0000000707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070700000007070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707A400000707070707070000A4070707
                07070707070707070707070707070707A400000707070707070000A407070707
                0707070707070707070707070707070707070707070707070707070700000000
                0000000000000000000000000000000000000000000000070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070000000707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070700000000000000000000000000000000
                0000000000000000000000070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070000000707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070700000000000000000000000000000000000000000000000000000007
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070000000707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707000000070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070000070700000707070707070707070707070707
                0707070700000707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707000000070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0000070700000707070707070707070707070707070707070000070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070700
                0000070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707000007070000070707070000
                0000000000070707070707070000070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070700000007070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707000007070000070707070707070707070707070707070707
                0000070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070700000007070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070700000707
                0000070707070707070707070707070707070707000007070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070000000707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070700005BA4000007070707070707070707
                0707070707074907000007070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070000000707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070700009B49009B07070707070707070707070707070707004900000707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070000000707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707A44900000707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707000000070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070752000707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707000000070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070700
                0000070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070700000007070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070700000007070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070000000707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070000000707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070000000707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707000000070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707000000070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070700
                0000070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070700000007070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070700000007070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070000000707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070000000707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070000000707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707000000070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707000000070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070700
                0000070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                07070707070707070707070707070707070707000000}
            end
          end
        end
        object TabSheet18: TTabSheet
          Caption = #1052#1077#1090#1086#1076' '#1057#1080#1084#1087#1089#1086#1085#1072' ('#1087#1072#1088#1072#1073#1086#1083')'
          ImageIndex = 2
          object GroupBox84: TGroupBox
            Left = 8
            Top = 8
            Width = 585
            Height = 41
            Caption = #1060#1091#1085#1082#1094#1080#1103
            TabOrder = 0
            object Label99: TLabel
              Left = 8
              Top = 18
              Width = 53
              Height = 16
              Caption = 'f ( x ) ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold, fsItalic]
              ParentFont = False
            end
            object Edit73: TEdit
              Left = 64
              Top = 16
              Width = 513
              Height = 21
              TabOrder = 0
              OnKeyPress = Edit10KeyPress
            end
          end
          object GroupBox85: TGroupBox
            Left = 8
            Top = 56
            Width = 185
            Height = 81
            Caption = #1048#1085#1090#1077#1088#1074#1072#1083
            TabOrder = 1
            object Label100: TLabel
              Left = 8
              Top = 21
              Width = 22
              Height = 16
              Caption = 'a ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Label101: TLabel
              Left = 8
              Top = 53
              Width = 22
              Height = 16
              Caption = 'b ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Edit74: TEdit
              Left = 40
              Top = 16
              Width = 137
              Height = 21
              TabOrder = 0
              OnKeyPress = Edit2KeyPress
            end
            object Edit75: TEdit
              Left = 40
              Top = 48
              Width = 137
              Height = 21
              TabOrder = 1
              OnKeyPress = Edit2KeyPress
            end
          end
          object GroupBox86: TGroupBox
            Left = 8
            Top = 192
            Width = 585
            Height = 129
            Caption = #1056#1077#1079#1091#1083#1100#1090#1072#1090#1099' '#1074#1099#1095#1080#1089#1083#1077#1085#1080#1081
            TabOrder = 4
            object BitBtn25: TBitBtn
              Left = 416
              Top = 64
              Width = 155
              Height = 25
              Caption = #1042#1099#1095#1080#1089#1083#1080#1090#1100
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold, fsUnderline]
              ParentFont = False
              TabOrder = 0
              OnClick = BitBtn25Click
              Kind = bkYes
            end
            object BitBtn26: TBitBtn
              Left = 416
              Top = 96
              Width = 155
              Height = 25
              Caption = #1042#1099#1093#1086#1076
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold, fsUnderline]
              ParentFont = False
              TabOrder = 1
              Kind = bkClose
            end
            object GroupBox87: TGroupBox
              Left = 8
              Top = 16
              Width = 569
              Height = 41
              Caption = #1047#1085#1072#1095#1077#1085#1080#1077' '#1080#1085#1090#1077#1075#1088#1072#1083#1072
              TabOrder = 2
              object Edit76: TEdit
                Left = 8
                Top = 16
                Width = 553
                Height = 21
                TabStop = False
                ReadOnly = True
                TabOrder = 0
                OnKeyPress = Edit5KeyPress
              end
            end
            object GroupBox88: TGroupBox
              Left = 8
              Top = 80
              Width = 401
              Height = 41
              Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1088#1072#1079#1073#1080#1077#1085#1080#1081
              TabOrder = 3
              object Edit77: TEdit
                Left = 8
                Top = 16
                Width = 385
                Height = 21
                TabStop = False
                ReadOnly = True
                TabOrder = 0
                OnKeyPress = Edit5KeyPress
              end
            end
          end
          object GroupBox89: TGroupBox
            Left = 208
            Top = 56
            Width = 97
            Height = 129
            TabOrder = 3
            object RadioButton40: TRadioButton
              Left = 8
              Top = 16
              Width = 73
              Height = 17
              Caption = #1043#1088#1072#1076#1091#1089#1099
              Enabled = False
              TabOrder = 0
            end
            object RadioButton41: TRadioButton
              Left = 8
              Top = 56
              Width = 73
              Height = 17
              Caption = #1056#1072#1076#1080#1072#1085#1099
              Checked = True
              TabOrder = 1
              TabStop = True
            end
            object RadioButton42: TRadioButton
              Left = 8
              Top = 96
              Width = 73
              Height = 17
              Caption = #1043#1088#1072#1076#1099
              Enabled = False
              TabOrder = 2
            end
          end
          object GroupBox90: TGroupBox
            Left = 8
            Top = 136
            Width = 185
            Height = 49
            Caption = #1064#1072#1075
            TabOrder = 2
            object Label102: TLabel
              Left = 8
              Top = 19
              Width = 21
              Height = 16
              Caption = 'h ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Edit78: TEdit
              Left = 40
              Top = 16
              Width = 137
              Height = 21
              TabOrder = 0
              OnKeyPress = Edit2KeyPress
            end
          end
          object GroupBox92: TGroupBox
            Left = 312
            Top = 56
            Width = 281
            Height = 129
            Caption = #1056#1072#1073#1086#1095#1072#1103' '#1092#1086#1088#1084#1091#1083#1072
            TabOrder = 5
            object Image2: TImage
              Left = 8
              Top = 16
              Width = 265
              Height = 105
              Picture.Data = {
                07544269746D617022720000424D227200000000000036040000280000000901
                0000690000000100080000000000EC6D00000000000000000000000100000000
                000000000000000080000080000000808000800000008000800080800000C0C0
                C000C0DCC000F0CAA6000020400000206000002080000020A0000020C0000020
                E00000400000004020000040400000406000004080000040A0000040C0000040
                E00000600000006020000060400000606000006080000060A0000060C0000060
                E00000800000008020000080400000806000008080000080A0000080C0000080
                E00000A0000000A0200000A0400000A0600000A0800000A0A00000A0C00000A0
                E00000C0000000C0200000C0400000C0600000C0800000C0A00000C0C00000C0
                E00000E0000000E0200000E0400000E0600000E0800000E0A00000E0C00000E0
                E00040000000400020004000400040006000400080004000A0004000C0004000
                E00040200000402020004020400040206000402080004020A0004020C0004020
                E00040400000404020004040400040406000404080004040A0004040C0004040
                E00040600000406020004060400040606000406080004060A0004060C0004060
                E00040800000408020004080400040806000408080004080A0004080C0004080
                E00040A0000040A0200040A0400040A0600040A0800040A0A00040A0C00040A0
                E00040C0000040C0200040C0400040C0600040C0800040C0A00040C0C00040C0
                E00040E0000040E0200040E0400040E0600040E0800040E0A00040E0C00040E0
                E00080000000800020008000400080006000800080008000A0008000C0008000
                E00080200000802020008020400080206000802080008020A0008020C0008020
                E00080400000804020008040400080406000804080008040A0008040C0008040
                E00080600000806020008060400080606000806080008060A0008060C0008060
                E00080800000808020008080400080806000808080008080A0008080C0008080
                E00080A0000080A0200080A0400080A0600080A0800080A0A00080A0C00080A0
                E00080C0000080C0200080C0400080C0600080C0800080C0A00080C0C00080C0
                E00080E0000080E0200080E0400080E0600080E0800080E0A00080E0C00080E0
                E000C0000000C0002000C0004000C0006000C0008000C000A000C000C000C000
                E000C0200000C0202000C0204000C0206000C0208000C020A000C020C000C020
                E000C0400000C0402000C0404000C0406000C0408000C040A000C040C000C040
                E000C0600000C0602000C0604000C0606000C0608000C060A000C060C000C060
                E000C0800000C0802000C0804000C0806000C0808000C080A000C080C000C080
                E000C0A00000C0A02000C0A04000C0A06000C0A08000C0A0A000C0A0C000C0A0
                E000C0C00000C0C02000C0C04000C0C06000C0C08000C0C0A000F0FBFF00A4A0
                A000808080000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
                FF00070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707000000070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707000000070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070000000707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070000000707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070000000707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070700000007070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070700000007070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070700
                0000070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707000000070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707000000070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070000000707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070000000707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070000000707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070700000007070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070700000007070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070700
                0000070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707000000070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707000000070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070000000707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070000000707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070000000707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070700000007070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070700000007070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070700
                0000070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070000000707070707
                0707070707070707070707070707070707000707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707000000070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070700000707070707070707070707070707070707070707070000000007
                0707070707070707070707070707070707070707070707070707070707070707
                0700000007070007070007070707000000070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707000000070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070007000007070707490707070707070707070707070707
                0707000007070749F70007070707070707070707070707070707070707070707
                0707070707070707070000070700000707070007490007070707000007070700
                0707070707070700070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070000000707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707000707070700070707070007
                0707070707070707070707070707070700070707490007070707070707070707
                0707070707070707070707070707070707070707070707000707490707070007
                5200070000070749070707070007070707070707000707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070000000707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0007070707000707000700070707070707070707070707070707070700070707
                0000070707070707070707070707070707070707070707070707070707070707
                070707000707A400070700490700070707070707000707070007070707070707
                0007070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070000000707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070700000000000007070707
                0707070707070707070707000707070707000707070007070707070707070707
                0707070707070707000707070700070707070707070707070707070707000707
                070007070700070707070707070707000700F700070700490700070707070007
                0007070707000707070707070700070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070700000007070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707000707070707
                0707070007070707070707070707070707070707070707000707070707000707
                0707070707070707070007070707070707070707000707070707070707070707
                0007070707070707070707070707070707070707070707070707070007070007
                0707000707000707070707000707070707000707070707070700070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070700000007070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070007070707070707070700070707070707070707070707070707
                0707070007070707000700070707070707070707070007070707070707070700
                0700070707070707070707070007070707070707070707070707070707070707
                0707070707070007000707070707070707070707070707070707070707000707
                0707070707000707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070700
                0000070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070007070707070707070707000707
                0707070707070707070707070707070007070707000700070707070707070707
                0700070707070707070707000700070707070707070707070007070707070707
                0707070707070707070707070707070707070007000707070707070707070707
                0707070707070707070007070707070707000707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707000000070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070000000000
                0000070707070707070700070707070707070707070707070707070007070707
                0007000707070707070700000000000000070707070707000700070707070707
                0700000000000000070707070707070707070707070707070707070707070007
                0007070707070707070707070707070707070707070007070707070707000707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707000000070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070700070707070707070707070707000707070707070707
                0707070707070700070707000707070007070707070707070700070707070707
                0707000707070007070707070707070700070707070707070707070707070707
                0707070707070707070007070700070707070707070707070707070707070707
                0700070707070707070007070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070000000707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070700070707070707070707
                0707070007070707070700070007070707070700070707000707070007070707
                0707070707000707070707070707000707070007070707070707070700070707
                0707070707070707070707070707070707070707070007070700070707070707
                0707070707070707070707070700070707070707070007070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070000000707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707000707070707070707070707070007070707070707000707070707070707
                0007070707070707070707070707070707000707070707070707070707070707
                0707070707070707000707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070007070707070707
                0007070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070000000707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070700070707070007070707
                0700000000000707070707070007070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070700070707070707070007070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070700000007070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070000000007070707070707070007070707070707070700070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070007070707070707000707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070700000007070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070700
                0000070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707000000070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707000000070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070000000707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070000000707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070000000707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070700000007070707070707070707070707070707070707070707
                0707070707070707070707070707070707000000000707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070700000007070707070707070707
                0707070707070707070707070707070707070707070707070707070700070707
                0700070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070700
                0000070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070700070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707000000070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070700070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707000000070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707000707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070000000707070000000000000000000000000000070707070707070707
                0707070707070707070707070707000000070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070000000707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707000707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070000000707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070007070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070700000007070707070707070707070707070707070707070707
                0707070707070707070707070707070700070707070007070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070700000007070707070707070707
                0707070707070707070707070707070707070707070707070707070707000000
                0007070707070707070707070707070707070707070707070707070707070007
                0707070707070007000007070707000007070707070707070707070707070700
                0007070700000007000707000700070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070007000007070707
                0007070707070707070707070707070707000007070707000707070707070707
                0707070707070707070707070707070707070707070707070000070707070000
                0007070007070007070707070700070007070707070707070707070707070700
                0000070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070007070707070707000707070700070700F7F700070707
                0707070707070707070707070700070700000707000700490707000707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070007070707000707070007070707070707070707070707070707070700
                0707000700070707070707070707070707070707070707070707070707070707
                0707070707070007070700000707070007490007070707070700070700070707
                0707070707070707070707000000070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070007070707070707000707
                070700070700F7F7000707070707070707070707070707070700070707490707
                0007005207070700070707070707070707070707070707070707070707070707
                0707070707070707070707070707070007070707000707070007070707070707
                0707070707070707070707000707070700070707070707070707070707070707
                0707070707070707070707070707070707070007070707490707070007520007
                0000000707000707000707070707070707070707070707000000070707070707
                0707070700070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                000707070707070700070707070700070700F7F7000707070707070707070707
                070707070700070707A400070000070007070700070707070707070707070707
                0707070707070707070007070707070707070707070707070707000707070707
                0007070700070707070707070707070707070707070707000707070000070707
                0707070707070707070707070007070700070707000707070707070707070007
                070707A400070700490700070707070707000707070007070707070707070707
                0707070000000707070707070707070700070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070007070707070707000707070707000707070000
                070707070707000707070707070707070700070700F700070000070007070700
                0707070707070707070007070707070707070707070007070707070707070707
                0707070707070007070707070007075200070707070707070007070707070707
                07070700070749F7000707070707070007070707070707070707070707070707
                070707070707070707070007070700F700070700490700070707070700000707
                0700070707070707000707070707070000000707070707070707070700070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070007070707070707
                0007070707000700070707070707070707070007070707070707070700070007
                0700070700070700070707000707070707070707070007070707070707000000
                0000000707070707070707070707070707070007070707000700070700070707
                0707070700070707070707070707000700070700070707070707070007070707
                0707070707070707070707070707070707070707070007000707070007070700
                0707000707070707070007070700070707070707000707070707070000000707
                0707070707070707000707070707000000000000000707070707000000000000
                0000000000000000000000000000000000000000000707070707070707070707
                0707070700070707070707070007070707000700070707070707070707070007
                0707070707070707000700070707070707070707070707000707070707070707
                0700070707070707070700F7F700070707070707070707070707070707070007
                0707070007000707070707070707070700070707070707070707000700070707
                0707070707070700070707070707070707070707070707070707070707070707
                0700070007070707070707070707070707070707070707070700070707070707
                0007070707070700000007070707070707070707000707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070700070707070707070007070707000700
                0707070707070700000000000000070707070707000700070707070707070707
                0707070007070707070700000000000000070707070700F7F700070707070707
                0707070707070707070700070707070007000707070707070700000000000000
                0707070707070007000707070707070700000000000000070707070707070707
                0707070707070707070707070700070007070707070707070707070707070707
                0707070707000707070000000000000007070700000007070707070707070707
                0007070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070700070707
                0707070700070707000707070007070707070707070700070707070707070700
                0707070007070707070707070707070007070707070707070700070707070707
                07070700F7000707070707070707070707070707070700070707000707070007
                0707070707070707000707070707070707000707070007070707070707070700
                0707070707070707070707070707070707070707070707070007070700070707
                0707070707070707070707070707070707000707070707070007070707070700
                0000070707070707070707070007070707070000000000000007070707070707
                0707070707070707070707070707070707070707070707070707070707070700
                0700070707070707000707070707070700070707000707070007070707070707
                0707000707070707070707000707070007070707070707070707070007070707
                07070707070007070707070707070700F7000707070707070700070007070707
                0707000707070007070700070707070707070707000707070707070707000707
                0700070707070707070707000707070707070707070707070707070707070707
                0707070700070707000707070707070707070707070707070707070707000707
                0707070700070707070707000000070707070707070707070007070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070007070707070707070007070707070707000707
                0707070707070707070707070707000707070707070707070707070707070707
                0707070707070007070707070707070707000707070707070707070700000707
                0707070707070007070707070707070007070707070707070707070707070707
                0007070707070707070707070707070707070707070707000707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707000707070707070700070707070707000000070707070707
                0707070700070707070707070707070707070707070707070707070707070707
                0700070707000707070707070707070707070707070700000000000707070707
                0700070707070707070007070707070707070707070707070707070707070707
                0707070707070707070707070707070707070007070707070707070707070707
                0707070707070707000007070707070700000000000707070707070007070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707000707070707070707070707
                0707070000000707070707070707070700070707070707070707070707070707
                0707070707070707070707070700070707000707070707070707070707070707
                0707070700070707070707070707000707070707070700070707070707070707
                0707070707070707070707070707070707070707070707070707070707000707
                0707070707070707070707070707070707070707070007070707070707070007
                0707070707070707000707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070700
                0707070707070707070707070707070000000707070707070707070707070707
                0707070707070707070707070707070707070707070707070700070707000707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070000000707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707000707070007070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070700000007070707070707070707070707070707070707070707
                0707070707070707070707070707070707000707070007070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070700000007070707070707070707
                0707070707070707070707070707070707070707070707070707070707000007
                0700070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070700
                0000070707070707070707070707070707070707070707070707070707070707
                0707070707070707070007000007070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707000000070707000000000000000000000000000007
                0707070707070707070707070707070707070707070007070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707000000070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0700070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070000000707070707070707070707070707070707070707070707070707
                0707070707070707070707070700070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070000000707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070000000707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070700000007070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070700000007070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070700
                0000070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707000000070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707000000070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070000000707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070000000707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070000000707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070700000007070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070700000007070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070700
                0000070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707000000070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707000000070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070000000707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070000000707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070000000707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070700000007070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070700000007070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070700
                0000070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707000000070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707000000070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070000000707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070000000707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070000000707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070700000007070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070700000007070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070700
                0000070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707070707070707070707070707070707070707070707
                0707070707070707070707000000}
            end
          end
        end
      end
    end
    object TabSheet8: TTabSheet
      Caption = #1047#1072#1076#1072#1095#1072' '#1050#1086#1096#1080
      ImageIndex = 5
      object PageControl4: TPageControl
        Left = 8
        Top = 8
        Width = 609
        Height = 353
        ActivePage = TabSheet13
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabIndex = 0
        TabOrder = 0
        object TabSheet13: TTabSheet
          Caption = #1052#1077#1090#1086#1076' '#1069#1081#1083#1077#1088#1072
          object GroupBox50: TGroupBox
            Left = 8
            Top = 8
            Width = 585
            Height = 105
            Caption = #1058#1072#1073#1083#1080#1094#1072' '#1074#1099#1095#1080#1089#1083#1077#1085#1080#1081
            TabOrder = 6
            object StringGrid7: TStringGrid
              Left = 8
              Top = 16
              Width = 569
              Height = 81
              TabStop = False
              ColCount = 3
              DefaultColWidth = 180
              DefaultRowHeight = 14
              FixedCols = 0
              RowCount = 2
              ScrollBars = ssVertical
              TabOrder = 0
            end
          end
          object GroupBox51: TGroupBox
            Left = 8
            Top = 120
            Width = 185
            Height = 41
            Caption = #1064#1072#1075
            TabOrder = 1
            object Label53: TLabel
              Left = 8
              Top = 19
              Width = 25
              Height = 16
              Caption = 'h = '
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Edit43: TEdit
              Left = 32
              Top = 16
              Width = 145
              Height = 21
              TabOrder = 0
              OnKeyPress = Edit2KeyPress
            end
          end
          object GroupBox52: TGroupBox
            Left = 8
            Top = 168
            Width = 185
            Height = 73
            Caption = #1048#1085#1090#1077#1088#1074#1072#1083
            TabOrder = 2
            object Label54: TLabel
              Left = 8
              Top = 19
              Width = 19
              Height = 13
              Caption = 'a ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -11
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Label55: TLabel
              Left = 8
              Top = 44
              Width = 23
              Height = 13
              Caption = 'b = '
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -11
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Edit44: TEdit
              Left = 32
              Top = 16
              Width = 145
              Height = 21
              TabOrder = 0
              OnChange = Edit44Change
              OnKeyPress = Edit2KeyPress
            end
            object Edit45: TEdit
              Left = 32
              Top = 40
              Width = 145
              Height = 21
              TabOrder = 1
              OnKeyPress = Edit2KeyPress
            end
          end
          object GroupBox53: TGroupBox
            Left = 8
            Top = 248
            Width = 585
            Height = 73
            Caption = #1053#1072#1095#1072#1083#1100#1085#1099#1077' '#1091#1089#1083#1086#1074#1080#1103
            TabOrder = 0
            object Label56: TLabel
              Left = 7
              Top = 19
              Width = 58
              Height = 16
              Caption = 'y '#39' ( x ) ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Label57: TLabel
              Left = 8
              Top = 48
              Width = 18
              Height = 16
              Caption = 'y ('
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Label59: TLabel
              Left = 104
              Top = 48
              Width = 18
              Height = 16
              Caption = ') ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Edit46: TEdit
              Left = 72
              Top = 16
              Width = 505
              Height = 21
              TabOrder = 0
              OnKeyPress = Edit46KeyPress
            end
            object Edit47: TEdit
              Left = 32
              Top = 48
              Width = 65
              Height = 21
              TabStop = False
              TabOrder = 2
              OnChange = Edit47Change
              OnKeyPress = Edit2KeyPress
            end
            object Edit48: TEdit
              Left = 128
              Top = 48
              Width = 449
              Height = 21
              TabOrder = 1
              OnKeyPress = Edit2KeyPress
            end
          end
          object GroupBox54: TGroupBox
            Left = 200
            Top = 120
            Width = 89
            Height = 121
            TabOrder = 3
            object RadioButton22: TRadioButton
              Left = 8
              Top = 16
              Width = 65
              Height = 17
              Caption = #1043#1088#1072#1076#1091#1089#1099
              Checked = True
              TabOrder = 0
              TabStop = True
            end
            object RadioButton23: TRadioButton
              Left = 8
              Top = 57
              Width = 65
              Height = 17
              Caption = #1056#1072#1076#1080#1072#1085#1099
              TabOrder = 1
            end
            object RadioButton24: TRadioButton
              Left = 8
              Top = 96
              Width = 65
              Height = 17
              Caption = #1043#1088#1072#1076#1099
              TabOrder = 2
            end
          end
          object GroupBox55: TGroupBox
            Left = 296
            Top = 120
            Width = 209
            Height = 121
            Caption = #1056#1072#1073#1086#1095#1080#1077' '#1092#1086#1088#1084#1091#1083#1099
            TabOrder = 7
            object Label58: TLabel
              Left = 16
              Top = 24
              Width = 156
              Height = 20
              Caption = 'X (k+1) = X (k) + h'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -16
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold, fsItalic, fsUnderline]
              ParentFont = False
            end
            object Label60: TLabel
              Left = 16
              Top = 88
              Width = 189
              Height = 20
              Caption = 'Y (k+1) = Y (k) + Y'#39' * h'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -16
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold, fsItalic, fsUnderline]
              ParentFont = False
            end
          end
          object BitBtn15: TBitBtn
            Left = 512
            Top = 128
            Width = 81
            Height = 25
            Caption = #1054#1090#1074#1077#1090
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold, fsUnderline]
            ParentFont = False
            TabOrder = 4
            OnClick = BitBtn15Click
            Kind = bkYes
          end
          object BitBtn16: TBitBtn
            Left = 512
            Top = 216
            Width = 81
            Height = 25
            Caption = #1042#1099#1093#1086#1076
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold, fsUnderline]
            ParentFont = False
            TabOrder = 5
            OnClick = BitBtn2Click
            Kind = bkClose
          end
        end
        object TabSheet14: TTabSheet
          Caption = #1048#1089#1087#1088#1072#1074#1083#1077#1085#1085#1099#1081' '#1084#1077#1090#1086#1076' '#1069#1081#1083#1077#1088#1072
          ImageIndex = 1
          object GroupBox56: TGroupBox
            Left = 8
            Top = 8
            Width = 593
            Height = 113
            Caption = #1058#1072#1073#1083#1080#1094#1072' '#1087#1088#1080#1073#1083#1080#1078#1077#1085#1080#1081
            TabOrder = 6
            object StringGrid8: TStringGrid
              Left = 8
              Top = 16
              Width = 577
              Height = 89
              TabStop = False
              ColCount = 6
              DefaultColWidth = 90
              DefaultRowHeight = 14
              FixedCols = 0
              RowCount = 2
              ScrollBars = ssVertical
              TabOrder = 0
            end
          end
          object GroupBox57: TGroupBox
            Left = 8
            Top = 128
            Width = 185
            Height = 41
            Caption = #1064#1072#1075
            TabOrder = 1
            object Label61: TLabel
              Left = 8
              Top = 21
              Width = 21
              Height = 16
              Caption = 'h ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Edit49: TEdit
              Left = 32
              Top = 16
              Width = 145
              Height = 21
              TabOrder = 0
              OnKeyPress = Edit2KeyPress
            end
          end
          object GroupBox58: TGroupBox
            Left = 8
            Top = 176
            Width = 185
            Height = 73
            Caption = #1048#1085#1090#1077#1088#1074#1072#1083
            TabOrder = 2
            object Label62: TLabel
              Left = 8
              Top = 20
              Width = 22
              Height = 16
              Caption = 'a ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Label63: TLabel
              Left = 8
              Top = 53
              Width = 22
              Height = 16
              Caption = 'b ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Edit50: TEdit
              Left = 32
              Top = 16
              Width = 145
              Height = 21
              TabOrder = 0
              OnChange = Edit50Change
              OnKeyPress = Edit2KeyPress
            end
            object Edit51: TEdit
              Left = 32
              Top = 48
              Width = 145
              Height = 21
              TabOrder = 1
              OnKeyPress = Edit2KeyPress
            end
          end
          object GroupBox59: TGroupBox
            Left = 200
            Top = 128
            Width = 89
            Height = 121
            TabOrder = 3
            object RadioButton25: TRadioButton
              Left = 8
              Top = 16
              Width = 73
              Height = 17
              Caption = #1043#1088#1072#1076#1091#1089#1099
              Checked = True
              TabOrder = 0
              TabStop = True
            end
            object RadioButton26: TRadioButton
              Left = 8
              Top = 56
              Width = 73
              Height = 17
              Caption = #1056#1072#1076#1080#1072#1085#1099
              TabOrder = 1
            end
            object RadioButton27: TRadioButton
              Left = 8
              Top = 96
              Width = 73
              Height = 17
              Caption = #1043#1088#1072#1076#1099
              TabOrder = 2
            end
          end
          object GroupBox60: TGroupBox
            Left = 8
            Top = 256
            Width = 593
            Height = 65
            Caption = #1053#1072#1095#1072#1083#1100#1085#1099#1077' '#1091#1089#1083#1086#1074#1080#1103
            TabOrder = 0
            object Label64: TLabel
              Left = 8
              Top = 18
              Width = 54
              Height = 16
              Caption = 'y'#39' ( x ) ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Label65: TLabel
              Left = 9
              Top = 40
              Width = 18
              Height = 16
              Caption = 'y ('
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Label66: TLabel
              Left = 112
              Top = 40
              Width = 18
              Height = 16
              Caption = ') ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Edit52: TEdit
              Left = 64
              Top = 16
              Width = 521
              Height = 21
              TabOrder = 0
              OnKeyPress = Edit46KeyPress
            end
            object Edit53: TEdit
              Left = 32
              Top = 40
              Width = 73
              Height = 21
              TabStop = False
              TabOrder = 2
              OnChange = Edit53Change
              OnKeyPress = Edit2KeyPress
            end
            object Edit54: TEdit
              Left = 136
              Top = 40
              Width = 449
              Height = 21
              TabOrder = 1
              OnKeyPress = Edit2KeyPress
            end
          end
          object BitBtn17: TBitBtn
            Left = 520
            Top = 136
            Width = 80
            Height = 25
            Caption = #1054#1090#1074#1077#1090
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold, fsUnderline]
            ParentFont = False
            TabOrder = 4
            OnClick = BitBtn17Click
            Kind = bkYes
          end
          object BitBtn18: TBitBtn
            Left = 520
            Top = 224
            Width = 79
            Height = 25
            Caption = #1042#1099#1093#1086#1076
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold, fsUnderline]
            ParentFont = False
            TabOrder = 5
            OnClick = BitBtn2Click
            Kind = bkClose
          end
          object GroupBox61: TGroupBox
            Left = 296
            Top = 128
            Width = 217
            Height = 121
            Caption = #1056#1072#1073#1086#1095#1080#1077' '#1092#1086#1088#1084#1091#1083#1099
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
            TabOrder = 7
            object Label67: TLabel
              Left = 3
              Top = 16
              Width = 156
              Height = 20
              Caption = 'X (k+1) = X (k) + h'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -16
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold, fsItalic, fsUnderline]
              ParentFont = False
            end
            object Label68: TLabel
              Left = 2
              Top = 37
              Width = 141
              Height = 20
              Caption = '~X = X + ( h / 2 )'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -16
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold, fsItalic, fsUnderline]
              ParentFont = False
            end
            object Label69: TLabel
              Left = 2
              Top = 56
              Width = 174
              Height = 20
              Caption = '~Y = Y + Y'#39' * ( h / 2 )'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -16
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold, fsItalic, fsUnderline]
              ParentFont = False
            end
            object Label70: TLabel
              Left = 4
              Top = 97
              Width = 199
              Height = 20
              Caption = 'Y (k+1) = Y (k) + ~Y'#39' * h'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -16
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold, fsItalic, fsUnderline]
              ParentFont = False
            end
            object Label71: TLabel
              Left = 2
              Top = 76
              Width = 126
              Height = 20
              Caption = '~Y = f (~x; ~y )'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -16
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold, fsItalic, fsUnderline]
              ParentFont = False
            end
          end
        end
        object TabSheet15: TTabSheet
          Caption = #1052#1077#1090#1086#1076' '#1056#1091#1085#1075#1077' - '#1050#1091#1090#1090#1072' IV '#1087#1086#1088#1103#1076#1082#1072
          ImageIndex = 2
          object GroupBox62: TGroupBox
            Left = 8
            Top = 8
            Width = 585
            Height = 105
            Caption = #1058#1072#1073#1083#1080#1094#1072' '#1074#1099#1095#1080#1089#1083#1077#1085#1080#1081
            TabOrder = 6
            object StringGrid9: TStringGrid
              Left = 8
              Top = 16
              Width = 569
              Height = 81
              TabStop = False
              ColCount = 13
              DefaultColWidth = 100
              DefaultRowHeight = 14
              FixedCols = 0
              RowCount = 2
              TabOrder = 0
            end
          end
          object GroupBox63: TGroupBox
            Left = 8
            Top = 120
            Width = 185
            Height = 41
            Caption = #1064#1072#1075
            TabOrder = 1
            object Label72: TLabel
              Left = 8
              Top = 20
              Width = 21
              Height = 16
              Caption = 'h ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Edit55: TEdit
              Left = 32
              Top = 16
              Width = 145
              Height = 21
              TabOrder = 0
              OnKeyPress = Edit2KeyPress
            end
          end
          object GroupBox64: TGroupBox
            Left = 8
            Top = 168
            Width = 185
            Height = 81
            Caption = #1048#1085#1090#1077#1088#1074#1072#1083
            TabOrder = 2
            object Label73: TLabel
              Left = 8
              Top = 19
              Width = 22
              Height = 16
              Caption = 'a ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Label74: TLabel
              Left = 8
              Top = 51
              Width = 22
              Height = 16
              Caption = 'b ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Edit56: TEdit
              Left = 32
              Top = 16
              Width = 145
              Height = 21
              TabOrder = 0
              OnChange = Edit56Change
              OnKeyPress = Edit2KeyPress
            end
            object Edit57: TEdit
              Left = 32
              Top = 48
              Width = 145
              Height = 21
              TabOrder = 1
              OnKeyPress = Edit2KeyPress
            end
          end
          object GroupBox65: TGroupBox
            Left = 8
            Top = 248
            Width = 585
            Height = 73
            Caption = #1053#1072#1095#1072#1083#1100#1085#1099#1077' '#1091#1089#1083#1086#1074#1080#1103
            TabOrder = 0
            object Label75: TLabel
              Left = 4
              Top = 20
              Width = 58
              Height = 16
              Caption = 'y '#39' ( x ) ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Label76: TLabel
              Left = 4
              Top = 50
              Width = 18
              Height = 16
              Caption = 'y ('
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Label77: TLabel
              Left = 112
              Top = 51
              Width = 18
              Height = 16
              Caption = ') ='
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsBold]
              ParentFont = False
            end
            object Edit58: TEdit
              Left = 64
              Top = 16
              Width = 513
              Height = 21
              TabOrder = 0
              OnKeyPress = Edit46KeyPress
            end
            object Edit59: TEdit
              Left = 26
              Top = 48
              Width = 81
              Height = 21
              TabStop = False
              TabOrder = 2
              OnChange = Edit59Change
              OnKeyPress = Edit2KeyPress
            end
            object Edit60: TEdit
              Left = 136
              Top = 48
              Width = 440
              Height = 21
              TabOrder = 1
              OnKeyPress = Edit2KeyPress
            end
          end
          object GroupBox66: TGroupBox
            Left = 200
            Top = 120
            Width = 97
            Height = 129
            TabOrder = 3
            object RadioButton28: TRadioButton
              Left = 8
              Top = 16
              Width = 65
              Height = 17
              Caption = #1043#1088#1072#1076#1091#1089#1099
              Checked = True
              TabOrder = 0
              TabStop = True
            end
            object RadioButton29: TRadioButton
              Left = 8
              Top = 56
              Width = 65
              Height = 17
              Caption = #1056#1072#1076#1080#1072#1085#1099
              TabOrder = 1
            end
            object RadioButton30: TRadioButton
              Left = 8
              Top = 96
              Width = 73
              Height = 17
              Caption = #1043#1088#1072#1076#1099
              TabOrder = 2
            end
          end
          object BitBtn19: TBitBtn
            Left = 512
            Top = 128
            Width = 80
            Height = 25
            Caption = #1054#1090#1074#1077#1090
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold, fsUnderline]
            ParentFont = False
            TabOrder = 4
            OnClick = BitBtn19Click
            Kind = bkYes
          end
          object BitBtn20: TBitBtn
            Left = 511
            Top = 216
            Width = 80
            Height = 25
            Caption = #1042#1099#1093#1086#1076
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold, fsUnderline]
            ParentFont = False
            TabOrder = 5
            Kind = bkClose
          end
          object GroupBox67: TGroupBox
            Left = 304
            Top = 120
            Width = 201
            Height = 129
            Caption = #1056#1072#1073#1086#1095#1080#1077' '#1092#1086#1088#1084#1091#1083#1099
            TabOrder = 7
            object Label78: TLabel
              Left = 8
              Top = 16
              Width = 86
              Height = 13
              Caption = 'X (k+1) = X (k) + h'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -11
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsUnderline]
              ParentFont = False
            end
            object Label79: TLabel
              Left = 8
              Top = 32
              Width = 77
              Height = 13
              Caption = '~X = X (k) + h/2'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -11
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsUnderline]
              ParentFont = False
            end
            object Label80: TLabel
              Left = 8
              Top = 48
              Width = 39
              Height = 13
              Caption = '^X = ~X'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -11
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsUnderline]
              ParentFont = False
            end
            object Label81: TLabel
              Left = 8
              Top = 64
              Width = 47
              Height = 13
              Caption = '<X = X +h'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -11
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsUnderline]
              ParentFont = False
            end
            object Label82: TLabel
              Left = 8
              Top = 80
              Width = 50
              Height = 13
              Caption = 'T1 = f(x; y)'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -11
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsUnderline]
              ParentFont = False
            end
            object Label83: TLabel
              Left = 8
              Top = 96
              Width = 64
              Height = 13
              Caption = 'T2 = f(~x; ~y)'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -11
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsUnderline]
              ParentFont = False
            end
            object Label84: TLabel
              Left = 104
              Top = 32
              Width = 94
              Height = 13
              Caption = '~Y = Y (k) + T1*h/2'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -11
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsUnderline]
              ParentFont = False
            end
            object Label85: TLabel
              Left = 104
              Top = 48
              Width = 93
              Height = 13
              Caption = '^Y = Y (k) + T2*h/2'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -11
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsUnderline]
              ParentFont = False
            end
            object Label86: TLabel
              Left = 104
              Top = 64
              Width = 82
              Height = 13
              Caption = '<Y = Y (k) + T3*h'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -11
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsUnderline]
              ParentFont = False
            end
            object Label87: TLabel
              Left = 104
              Top = 16
              Width = 94
              Height = 13
              Caption = 'Y(k+1) = Y (k) + T*h'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -11
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsUnderline]
              ParentFont = False
            end
            object Label88: TLabel
              Left = 104
              Top = 80
              Width = 59
              Height = 13
              Caption = 'T3 =f(^x; ^y)'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -11
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsUnderline]
              ParentFont = False
            end
            object Label89: TLabel
              Left = 104
              Top = 96
              Width = 62
              Height = 13
              Caption = 'T4 = f(<x; <y)'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -11
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsUnderline]
              ParentFont = False
            end
            object Label90: TLabel
              Left = 8
              Top = 112
              Width = 163
              Height = 13
              Caption = 'T = ( T1 + 2*T2 + 2*T3 + T4) * 1/6'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -11
              Font.Name = 'MS Sans Serif'
              Font.Style = [fsUnderline]
              ParentFont = False
            end
          end
        end
      end
    end
  end
  object MainMenu1: TMainMenu
    Left = 616
    object Help1: TMenuItem
      Caption = 'Help'
      object Information1: TMenuItem
        Caption = 'Information...'
        OnClick = Information1Click
      end
      object About1: TMenuItem
        Caption = 'About...'
        OnClick = About1Click
      end
    end
  end
end
