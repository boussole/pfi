object fMain: TfMain
  Left = 434
  Top = 380
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #1056#1077#1077#1089#1090#1088' - '#1086#1090#1095#1077#1090' '#1087#1086' '#1088#1072#1089#1093#1086#1076#1091' '#1101#1083#1077#1082#1090#1088#1086#1101#1085#1077#1088#1075#1080#1080
  ClientHeight = 347
  ClientWidth = 754
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
  object Panel1: TPanel
    Left = 0
    Top = 304
    Width = 753
    Height = 41
    BorderStyle = bsSingle
    TabOrder = 0
    object BitBtn3: TBitBtn
      Left = 152
      Top = 4
      Width = 153
      Height = 25
      Caption = #1055#1088#1077#1076#1074'. '#1087#1088#1086#1089#1084#1086#1090#1088
      ModalResult = 5
      TabOrder = 0
      OnClick = BitBtn3Click
      Glyph.Data = {
        DE010000424DDE01000000000000760000002800000024000000120000000100
        0400000000006801000000000000000000001000000000000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00344446333334
        44433333FFFF333333FFFF33000033AAA43333332A4333338833F33333883F33
        00003332A46333332A4333333383F33333383F3300003332A2433336A6633333
        33833F333383F33300003333AA463362A433333333383F333833F33300003333
        6AA4462A46333333333833FF833F33330000333332AA22246333333333338333
        33F3333300003333336AAA22646333333333383333F8FF33000033444466AA43
        6A43333338FFF8833F383F330000336AA246A2436A43333338833F833F383F33
        000033336A24AA442A433333333833F33FF83F330000333333A2AA2AA4333333
        333383333333F3330000333333322AAA4333333333333833333F333300003333
        333322A4333333333333338333F333330000333333344A433333333333333338
        3F333333000033333336A24333333333333333833F333333000033333336AA43
        33333333333333833F3333330000333333336663333333333333333888333333
        0000}
      NumGlyphs = 2
    end
    object BitBtn2: TBitBtn
      Left = 592
      Top = 4
      Width = 145
      Height = 25
      Caption = #1042#1099#1093#1086#1076
      TabOrder = 1
      OnClick = BitBtn2Click
      Kind = bkCancel
    end
    object BitBtn1: TBitBtn
      Left = 8
      Top = 4
      Width = 145
      Height = 25
      Caption = #1055#1086#1076#1089#1095#1077#1090
      TabOrder = 2
      OnClick = BitBtn1Click
      Kind = bkOK
    end
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 8
    Width = 753
    Height = 289
    ActivePage = TabSheet1
    TabIndex = 0
    TabOrder = 1
    object TabSheet1: TTabSheet
      Caption = #1054#1090#1095#1077#1090
      object GroupBox1: TGroupBox
        Left = 0
        Top = 4
        Width = 737
        Height = 257
        TabOrder = 0
        object StringGrid1: TStringGrid
          Left = 8
          Top = 16
          Width = 721
          Height = 233
          DefaultColWidth = 142
          DefaultRowHeight = 14
          FixedCols = 0
          RowCount = 15
          Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
          ScrollBars = ssNone
          TabOrder = 0
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080
      ImageIndex = 1
      object GroupBox11: TGroupBox
        Left = 608
        Top = 8
        Width = 129
        Height = 41
        Caption = #1058#1086#1095#1085#1086#1089#1090#1100
        TabOrder = 0
        object Edit8: TEdit
          Left = 8
          Top = 16
          Width = 97
          Height = 21
          ReadOnly = True
          TabOrder = 0
          Text = '2'
        end
        object UpDown3: TUpDown
          Left = 105
          Top = 16
          Width = 15
          Height = 21
          Associate = Edit8
          Min = 1
          Position = 2
          TabOrder = 1
          Wrap = False
        end
      end
      object GroupBox10: TGroupBox
        Left = 472
        Top = 8
        Width = 129
        Height = 41
        Caption = #1055#1088#1086#1094#1077#1085#1090' '#1078#1080#1083#1100#1094#1086#1074
        TabOrder = 1
        object Edit7: TEdit
          Left = 8
          Top = 16
          Width = 113
          Height = 21
          TabOrder = 0
          Text = '94'
        end
      end
      object GroupBox12: TGroupBox
        Left = 0
        Top = 0
        Width = 465
        Height = 257
        TabOrder = 2
        object GroupBox4: TGroupBox
          Left = 8
          Top = 56
          Width = 145
          Height = 193
          Caption = #1043#1072#1088#1072#1078#1080
          TabOrder = 0
          object StringGrid2: TStringGrid
            Left = 8
            Top = 16
            Width = 129
            Height = 169
            ColCount = 1
            DefaultColWidth = 125
            DefaultRowHeight = 14
            FixedCols = 0
            RowCount = 1
            FixedRows = 0
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
            ScrollBars = ssVertical
            TabOrder = 0
            RowHeights = (
              14)
          end
        end
        object GroupBox7: TGroupBox
          Left = 160
          Top = 56
          Width = 145
          Height = 193
          Caption = #1040#1088#1077#1085#1076#1072#1090#1086#1088#1099
          TabOrder = 1
          object StringGrid3: TStringGrid
            Left = 8
            Top = 16
            Width = 129
            Height = 169
            ColCount = 1
            DefaultColWidth = 125
            DefaultRowHeight = 14
            FixedCols = 0
            RowCount = 1
            FixedRows = 0
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
            ScrollBars = ssVertical
            TabOrder = 0
            RowHeights = (
              14)
          end
        end
        object GroupBox5: TGroupBox
          Left = 8
          Top = 16
          Width = 145
          Height = 41
          Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1075#1072#1088#1072#1078#1077#1081
          TabOrder = 2
          object Edit3: TEdit
            Left = 8
            Top = 16
            Width = 121
            Height = 21
            ReadOnly = True
            TabOrder = 0
            Text = '1'
          end
          object UpDown1: TUpDown
            Left = 129
            Top = 16
            Width = 15
            Height = 21
            Associate = Edit3
            Min = 1
            Position = 1
            TabOrder = 1
            Wrap = False
            OnClick = UpDown1Click
          end
        end
        object GroupBox6: TGroupBox
          Left = 160
          Top = 16
          Width = 145
          Height = 41
          Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1072#1088#1077#1085#1076#1072#1090#1086#1088#1086#1074
          TabOrder = 3
          object Edit4: TEdit
            Left = 8
            Top = 16
            Width = 121
            Height = 21
            ReadOnly = True
            TabOrder = 0
            Text = '1'
          end
          object UpDown2: TUpDown
            Left = 129
            Top = 16
            Width = 15
            Height = 21
            Associate = Edit4
            Min = 1
            Position = 1
            TabOrder = 1
            Wrap = False
            OnClick = UpDown2Click
          end
        end
        object GroupBox9: TGroupBox
          Left = 312
          Top = 16
          Width = 145
          Height = 41
          Caption = #1040#1088#1077#1085#1076#1072#1090#1086#1088
          TabOrder = 4
          object Edit6: TEdit
            Left = 8
            Top = 16
            Width = 129
            Height = 21
            TabOrder = 0
          end
        end
        object GroupBox8: TGroupBox
          Left = 312
          Top = 56
          Width = 145
          Height = 41
          Caption = #1055#1086#1076#1089#1074#1077#1090#1082#1072
          TabOrder = 5
          object Edit5: TEdit
            Left = 8
            Top = 16
            Width = 129
            Height = 21
            TabOrder = 0
          end
        end
        object GroupBox3: TGroupBox
          Left = 312
          Top = 160
          Width = 145
          Height = 41
          Caption = #1060#1072#1082#1090
          TabOrder = 6
          object Edit2: TEdit
            Left = 8
            Top = 16
            Width = 129
            Height = 21
            TabOrder = 0
          end
        end
        object GroupBox2: TGroupBox
          Left = 312
          Top = 208
          Width = 145
          Height = 41
          Caption = #1044#1086#1075#1086#1074#1086#1088#1085#1072#1103' '#1074#1077#1083#1080#1095#1080#1085#1072
          TabOrder = 7
          object Edit1: TEdit
            Left = 8
            Top = 16
            Width = 129
            Height = 21
            TabOrder = 0
          end
        end
      end
      object GroupBox13: TGroupBox
        Left = 472
        Top = 160
        Width = 265
        Height = 97
        Caption = #1047#1072#1075#1086#1083#1086#1074#1086#1082
        TabOrder = 3
        object CheckBox1: TCheckBox
          Left = 8
          Top = 24
          Width = 97
          Height = 17
          Caption = #1052#1077#1089#1103#1094
          Color = clBtnFace
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentColor = False
          ParentFont = False
          TabOrder = 0
          OnClick = CheckBox1Click
        end
        object CheckBox2: TCheckBox
          Left = 144
          Top = 24
          Width = 97
          Height = 17
          Caption = #1043#1086#1076
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 1
          OnClick = CheckBox2Click
        end
        object LabeledEdit1: TLabeledEdit
          Left = 8
          Top = 72
          Width = 113
          Height = 21
          Color = clInactiveCaptionText
          EditLabel.Width = 33
          EditLabel.Height = 13
          EditLabel.Caption = #1052#1077#1089#1103#1094
          LabelPosition = lpAbove
          LabelSpacing = 3
          ReadOnly = True
          TabOrder = 2
        end
        object LabeledEdit2: TLabeledEdit
          Left = 144
          Top = 72
          Width = 113
          Height = 21
          Color = clInactiveCaptionText
          EditLabel.Width = 18
          EditLabel.Height = 13
          EditLabel.Caption = #1043#1086#1076
          LabelPosition = lpAbove
          LabelSpacing = 3
          ReadOnly = True
          TabOrder = 3
          Text = '200'
        end
      end
    end
  end
  object MainMenu1: TMainMenu
    Left = 720
    object N1: TMenuItem
      Caption = '&'#1054#1090#1095#1077#1090
      object N2: TMenuItem
        Caption = #1055#1086#1076#1089#1095#1077#1090
        OnClick = BitBtn1Click
      end
      object N3: TMenuItem
        Caption = #1055#1088#1077#1076#1074#1072#1088#1080#1090#1077#1083#1100#1085#1099#1081' '#1087#1088#1086#1089#1084#1086#1090#1088
        OnClick = BitBtn3Click
      end
      object N4: TMenuItem
        Caption = '-'
      end
      object N5: TMenuItem
        Caption = #1042#1099#1093#1086#1076
        OnClick = BitBtn2Click
      end
    end
    object N6: TMenuItem
      Caption = '&'#1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077
      object N7: TMenuItem
        Caption = #1054#1090' '#1072#1074#1090#1086#1088#1072
        OnClick = N7Click
      end
    end
  end
end
