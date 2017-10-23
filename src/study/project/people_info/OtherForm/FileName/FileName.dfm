object FileNameForm: TFileNameForm
  Left = 243
  Top = 408
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #1042#1074#1086#1076' '#1080#1084#1077#1085#1080' '#1092#1072#1081#1083#1072
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
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 425
    Height = 49
    Caption = #1042#1074#1077#1076#1080#1090#1077' '#1080#1084#1103' '#1092#1072#1081#1083#1072' ('#1073#1077#1079' '#1088#1072#1089#1096#1080#1088#1077#1085#1080#1103')'
    TabOrder = 0
    object Edit1: TEdit
      Left = 8
      Top = 21
      Width = 409
      Height = 21
      TabOrder = 0
    end
  end
  object Ok: TBitBtn
    Left = 448
    Top = 16
    Width = 89
    Height = 33
    TabOrder = 1
    OnClick = OkClick
    Kind = bkOK
  end
  object Cancel: TBitBtn
    Left = 568
    Top = 16
    Width = 89
    Height = 33
    TabOrder = 2
    OnClick = CancelClick
    Kind = bkCancel
  end
end
