object NewWayForm: TNewWayForm
  Left = 243
  Top = 498
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #1042#1074#1086#1076' '#1085#1086#1074#1086#1075#1086' '#1079#1085#1072#1095#1077#1085#1080#1103' '#1087#1091#1090#1080' '#1087#1086' '#1091#1084#1086#1083#1095#1072#1085#1080#1102
  ClientHeight = 63
  ClientWidth = 663
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
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 425
    Height = 49
    Caption = #1053#1086#1074#1099#1081' '#1087#1091#1090#1100
    TabOrder = 0
    object Edit1: TEdit
      Left = 8
      Top = 16
      Width = 409
      Height = 21
      TabOrder = 0
    end
  end
  object BitBtn1: TBitBtn
    Left = 448
    Top = 16
    Width = 89
    Height = 33
    TabOrder = 1
    OnClick = BitBtn1Click
    Kind = bkOK
  end
  object BitBtn2: TBitBtn
    Left = 568
    Top = 16
    Width = 89
    Height = 33
    TabOrder = 2
    OnClick = BitBtn2Click
    Kind = bkCancel
  end
end
