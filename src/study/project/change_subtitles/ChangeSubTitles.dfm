object ChangeSubTitlesForm: TChangeSubTitlesForm
  Left = 270
  Top = 352
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'ChangeSubTitlesForm'
  ClientHeight = 251
  ClientWidth = 730
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
  object Change: TGroupBox
    Left = 0
    Top = 48
    Width = 729
    Height = 201
    Caption = #1057#1091#1073#1090#1080#1090#1088#1099
    TabOrder = 0
    object Operation: TGroupBox
      Left = 528
      Top = 24
      Width = 193
      Height = 105
      Caption = #1044#1077#1081#1089#1090#1074#1080#1103' '#1085#1072#1076' '#1092#1072#1081#1083#1086#1084' '#1089#1091#1073#1090#1080#1090#1088#1086#1074
      TabOrder = 0
      object Sum: TRadioButton
        Left = 8
        Top = 72
        Width = 97
        Height = 17
        Caption = #1059#1074#1077#1083#1080#1095#1077#1085#1080#1077
        TabOrder = 0
      end
      object Minus: TRadioButton
        Left = 8
        Top = 32
        Width = 89
        Height = 17
        Caption = #1059#1084#1077#1085#1100#1096#1077#1085#1080#1077
        Checked = True
        TabOrder = 1
        TabStop = True
      end
    end
    object FileSubTitles: TGroupBox
      Left = 8
      Top = 24
      Width = 513
      Height = 49
      Caption = #1054#1073#1088#1072#1073#1072#1090#1099#1074#1072#1077#1084#1099#1081' '#1092#1072#1081#1083' '#1089#1091#1073#1090#1080#1090#1088#1086#1074
      TabOrder = 1
      object Edit1: TEdit
        Left = 8
        Top = 16
        Width = 409
        Height = 21
        TabOrder = 0
      end
      object BitBtn1: TBitBtn
        Left = 432
        Top = 16
        Width = 75
        Height = 25
        Caption = #1054#1090#1082#1088#1099#1090#1100
        TabOrder = 1
        OnClick = BitBtn1Click
      end
    end
    object SaveChangeSubTitles: TGroupBox
      Left = 8
      Top = 80
      Width = 513
      Height = 49
      Caption = #1057#1086#1093#1088#1072#1085#1103#1077#1084#1099#1081' '#1092#1072#1081#1083' '#1089#1091#1073#1090#1080#1090#1088#1086#1074
      TabOrder = 2
      object Edit2: TEdit
        Left = 8
        Top = 16
        Width = 409
        Height = 21
        TabOrder = 0
      end
      object BitBtn2: TBitBtn
        Left = 432
        Top = 16
        Width = 75
        Height = 25
        Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
        TabOrder = 1
        OnClick = BitBtn2Click
      end
    end
    object ChangeTime: TGroupBox
      Left = 8
      Top = 136
      Width = 513
      Height = 57
      Caption = #1055#1088#1080#1088#1072#1097#1077#1085#1080#1077' '#1074#1088#1077#1084#1077#1085#1080
      TabOrder = 3
      object StringGrid1: TStringGrid
        Left = 6
        Top = 16
        Width = 499
        Height = 38
        ColCount = 4
        DefaultColWidth = 123
        DefaultRowHeight = 15
        FixedCols = 0
        RowCount = 2
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
        ScrollBars = ssNone
        TabOrder = 0
        OnKeyPress = StringGrid1KeyPress
      end
    end
    object Run: TBitBtn
      Left = 528
      Top = 144
      Width = 89
      Height = 49
      Caption = 'Change'
      TabOrder = 4
      OnClick = RunClick
      Kind = bkOK
    end
    object Exit: TBitBtn
      Left = 632
      Top = 144
      Width = 89
      Height = 49
      Caption = 'Exit'
      TabOrder = 5
      OnClick = ExitClick
      Kind = bkClose
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 729
    Height = 41
    TabOrder = 1
  end
  object OpenDialog1: TOpenDialog
    Filter = 
      'SubTitles (*.srt, *.txt, *.sub, *.ssa)|*.srt; *.txt; *.sub; *.ss' +
      'a'
    Left = 664
    Top = 8
  end
  object SaveDialog1: TSaveDialog
    Filter = 
      'SubTitles (*.srt, *.txt, *.sub, *.ssa)|*.srt; *.txt; *.sub; *.ss' +
      'a'
    Left = 696
    Top = 8
  end
  object MainMenu1: TMainMenu
    Left = 632
    Top = 8
    object ControlPanel1: TMenuItem
      Caption = 'Control Panel'
      object ChangeSubTitles1: TMenuItem
        Caption = 'Change SubTitles'
        OnClick = RunClick
      end
      object CloseProgram1: TMenuItem
        Caption = 'Close Program'
        OnClick = ExitClick
      end
    end
    object AboutProgram1: TMenuItem
      Caption = 'Help'
      object AboutProgram2: TMenuItem
        Caption = 'About Program...'
        OnClick = AboutProgram2Click
      end
      object About1: TMenuItem
        Caption = 'About...'
        OnClick = About1Click
      end
    end
  end
end
