object Windows_XP_Registry_Form: TWindows_XP_Registry_Form
  Left = 343
  Top = 292
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #1054#1087#1090#1080#1084#1080#1079#1072#1094#1080#1103' Windows XP'
  ClientHeight = 414
  ClientWidth = 536
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
  object Control_Panel_Pages: TPageControl
    Left = 3
    Top = 16
    Width = 529
    Height = 393
    ActivePage = Acceleration
    TabIndex = 0
    TabOrder = 0
    object Acceleration: TTabSheet
      Caption = 'Acceleration'
      ImageIndex = 2
      object AccelerationPages: TPageControl
        Left = 0
        Top = 8
        Width = 521
        Height = 353
        ActivePage = AccelerationP1
        TabIndex = 0
        TabOrder = 0
        object AccelerationP1: TTabSheet
          Caption = 'Page 1'
          object MenuShowDelayHelp: TGroupBox
            Left = 264
            Top = 168
            Width = 249
            Height = 73
            Cursor = crHelp
            Caption = 'MenuShowDelay'
            TabOrder = 0
            OnClick = MenuShowDelayHelpClick
            object Panel7: TPanel
              Left = 8
              Top = 16
              Width = 161
              Height = 49
              BorderStyle = bsSingle
              TabOrder = 0
              object GroupBox9: TGroupBox
                Left = 8
                Top = 0
                Width = 145
                Height = 41
                Caption = 'Time (ms)'
                TabOrder = 0
                object Edit2: TEdit
                  Left = 8
                  Top = 16
                  Width = 129
                  Height = 21
                  TabOrder = 0
                end
              end
            end
            object MenuShowDelaySave: TBitBtn
              Left = 176
              Top = 16
              Width = 65
              Height = 25
              Caption = 'Save'
              TabOrder = 1
              OnClick = MenuShowDelaySaveClick
              Kind = bkOK
            end
            object MenuShowDelayRefresh: TBitBtn
              Left = 176
              Top = 40
              Width = 65
              Height = 25
              Caption = 'Refresh'
              TabOrder = 2
              OnClick = MenuShowDelayRefreshClick
              Kind = bkRetry
            end
          end
          object AutoDebugerHelp: TGroupBox
            Left = 264
            Top = 8
            Width = 249
            Height = 73
            Cursor = crHelp
            Caption = 'Auto Debuger - Dr. Watson'
            TabOrder = 1
            OnClick = AutoDebugerHelpClick
            object Panel2: TPanel
              Left = 8
              Top = 16
              Width = 161
              Height = 49
              BorderStyle = bsSingle
              TabOrder = 0
              object RadioButton3: TRadioButton
                Left = 8
                Top = 24
                Width = 137
                Height = 17
                Caption = 'Disable'
                TabOrder = 0
              end
              object RadioButton4: TRadioButton
                Left = 8
                Top = 8
                Width = 129
                Height = 17
                Caption = 'Enable'
                Checked = True
                TabOrder = 1
                TabStop = True
              end
            end
            object AutoDebugerSave: TBitBtn
              Left = 176
              Top = 16
              Width = 65
              Height = 25
              Caption = 'Save'
              TabOrder = 1
              OnClick = AutoDebugerSaveClick
              Kind = bkOK
            end
            object AutoDebugerRefresh: TBitBtn
              Left = 176
              Top = 40
              Width = 65
              Height = 25
              Caption = 'Refresh'
              TabOrder = 2
              OnClick = AutoDebugerRefreshClick
              Kind = bkRetry
            end
          end
          object AlwaysUnloadDllHelp: TGroupBox
            Left = 0
            Top = 8
            Width = 249
            Height = 73
            Cursor = crHelp
            Caption = 'AlwaysUnloadDll'
            TabOrder = 2
            OnClick = AlwaysUnloadDllHelpClick
            object Panel28: TPanel
              Left = 8
              Top = 16
              Width = 161
              Height = 49
              BorderStyle = bsSingle
              TabOrder = 0
              object RadioButton51: TRadioButton
                Left = 8
                Top = 8
                Width = 113
                Height = 17
                Caption = 'Enable'
                Checked = True
                TabOrder = 0
                TabStop = True
              end
              object RadioButton52: TRadioButton
                Left = 8
                Top = 24
                Width = 113
                Height = 17
                Caption = 'Disable'
                TabOrder = 1
              end
            end
            object AlwaysUnloadDllSave: TBitBtn
              Left = 176
              Top = 16
              Width = 65
              Height = 25
              Caption = 'Save'
              TabOrder = 1
              OnClick = AlwaysUnloadDllSaveClick
              Kind = bkOK
            end
            object AlwaysUnloadDllRefresh: TBitBtn
              Left = 176
              Top = 40
              Width = 65
              Height = 25
              Caption = 'Refresh'
              TabOrder = 2
              OnClick = AlwaysUnloadDllRefreshClick
              Kind = bkRetry
            end
          end
          object NtfsDisableLastAccessUpdateHelp: TGroupBox
            Left = 264
            Top = 248
            Width = 249
            Height = 73
            Cursor = crHelp
            Caption = 'NtfsDisableLastAccessUpdate'
            TabOrder = 3
            OnClick = GroupBox5Click
            object Panel6: TPanel
              Left = 8
              Top = 16
              Width = 161
              Height = 49
              BorderStyle = bsSingle
              TabOrder = 0
              object RadioButton9: TRadioButton
                Left = 8
                Top = 8
                Width = 137
                Height = 17
                Caption = 'Enable'
                Checked = True
                TabOrder = 0
                TabStop = True
              end
              object RadioButton10: TRadioButton
                Left = 8
                Top = 24
                Width = 137
                Height = 17
                Caption = 'Disable'
                TabOrder = 1
              end
            end
            object NtfsDisableLastAccessUpdateSave: TBitBtn
              Left = 176
              Top = 16
              Width = 65
              Height = 25
              Caption = 'Save'
              TabOrder = 1
              OnClick = NtfsDisableLastAccessUpdateSaveClick
              Kind = bkOK
            end
            object NtfsDisableLastAccessUpdateRefresh: TBitBtn
              Left = 176
              Top = 40
              Width = 65
              Height = 25
              Caption = 'Refresh'
              TabOrder = 2
              OnClick = NtfsDisableLastAccessUpdateRefreshClick
              Kind = bkRetry
            end
          end
          object AutoEndTasksHelp: TGroupBox
            Left = 0
            Top = 88
            Width = 249
            Height = 73
            Cursor = crHelp
            Caption = 'AutoEndTasks'
            TabOrder = 4
            OnClick = AutoEndTasksHelpClick
            object Panel46: TPanel
              Left = 8
              Top = 16
              Width = 161
              Height = 49
              BorderStyle = bsSingle
              TabOrder = 0
              object RadioButton87: TRadioButton
                Left = 8
                Top = 8
                Width = 113
                Height = 17
                Caption = 'Enable'
                Checked = True
                TabOrder = 0
                TabStop = True
              end
              object RadioButton88: TRadioButton
                Left = 8
                Top = 24
                Width = 113
                Height = 17
                Caption = 'Disable'
                TabOrder = 1
              end
            end
            object AutoEndTasksSave: TBitBtn
              Left = 176
              Top = 16
              Width = 65
              Height = 25
              Caption = 'Save'
              TabOrder = 1
              OnClick = AutoEndTasksSaveClick
              Kind = bkOK
            end
            object AutoEndTasksRedresh: TBitBtn
              Left = 176
              Top = 40
              Width = 65
              Height = 25
              Caption = 'Refresh'
              TabOrder = 2
              OnClick = AutoEndTasksRedreshClick
              Kind = bkRetry
            end
          end
          object EnablePrefetcherHelp: TGroupBox
            Left = 264
            Top = 88
            Width = 249
            Height = 73
            Cursor = crHelp
            Caption = 'EnablePrefetcher'
            TabOrder = 5
            OnClick = EnablePrefetcherHelpClick
            object Panel33: TPanel
              Left = 8
              Top = 16
              Width = 161
              Height = 49
              BorderStyle = bsSingle
              TabOrder = 0
              object RadioButton59: TRadioButton
                Left = 8
                Top = 8
                Width = 25
                Height = 17
                Caption = '0'
                Checked = True
                TabOrder = 0
                TabStop = True
              end
              object RadioButton60: TRadioButton
                Left = 8
                Top = 24
                Width = 25
                Height = 17
                Caption = '1'
                TabOrder = 1
              end
              object RadioButton61: TRadioButton
                Left = 112
                Top = 8
                Width = 33
                Height = 17
                Caption = '2'
                TabOrder = 2
              end
              object RadioButton62: TRadioButton
                Left = 112
                Top = 24
                Width = 33
                Height = 17
                Caption = '3'
                TabOrder = 3
              end
            end
            object EnablePrefetcherSave: TBitBtn
              Left = 176
              Top = 16
              Width = 65
              Height = 25
              Caption = 'Save'
              TabOrder = 1
              OnClick = EnablePrefetcherSaveClick
              Kind = bkOK
            end
            object EnablePrefetcherRefresh: TBitBtn
              Left = 176
              Top = 40
              Width = 65
              Height = 25
              Caption = 'Refresh'
              TabOrder = 2
              OnClick = EnablePrefetcherRefreshClick
              Kind = bkRetry
            end
          end
          object HungAppTimeoutHelp: TGroupBox
            Left = 0
            Top = 168
            Width = 249
            Height = 73
            Cursor = crHelp
            Caption = 'HungAppTimeout'
            TabOrder = 6
            OnClick = HungAppTimeoutHelpClick
            object Panel48: TPanel
              Left = 8
              Top = 16
              Width = 161
              Height = 49
              BorderStyle = bsSingle
              TabOrder = 0
              object GroupBox6: TGroupBox
                Left = 8
                Top = 0
                Width = 145
                Height = 41
                Caption = 'Time (ms)'
                TabOrder = 0
                object Edit6: TEdit
                  Left = 8
                  Top = 16
                  Width = 129
                  Height = 21
                  TabOrder = 0
                end
              end
            end
            object HungAppTimeoutSave: TBitBtn
              Left = 176
              Top = 16
              Width = 65
              Height = 25
              Caption = 'Save'
              TabOrder = 1
              OnClick = HungAppTimeoutSaveClick
              Kind = bkOK
            end
            object HungAppTimeoutRefresh: TBitBtn
              Left = 176
              Top = 40
              Width = 65
              Height = 25
              Caption = 'Refresh'
              TabOrder = 2
              OnClick = HungAppTimeoutRefreshClick
              Kind = bkRetry
            end
          end
          object MinAnimateHelp: TGroupBox
            Left = 0
            Top = 248
            Width = 249
            Height = 73
            Cursor = crHelp
            Caption = 'MinAnimate'
            TabOrder = 7
            OnClick = MinAnimateHelpClick
            object Panel8: TPanel
              Left = 8
              Top = 16
              Width = 161
              Height = 49
              BorderStyle = bsSingle
              TabOrder = 0
              object RadioButton11: TRadioButton
                Left = 8
                Top = 8
                Width = 81
                Height = 17
                Caption = 'Enable'
                Checked = True
                TabOrder = 0
                TabStop = True
              end
              object RadioButton12: TRadioButton
                Left = 8
                Top = 24
                Width = 81
                Height = 17
                Caption = 'Disable'
                TabOrder = 1
              end
            end
            object MinAnimateSave: TBitBtn
              Left = 177
              Top = 16
              Width = 65
              Height = 25
              Caption = 'Save'
              TabOrder = 1
              OnClick = MinAnimateSaveClick
              Kind = bkOK
            end
            object MinAnimateRefresh: TBitBtn
              Left = 177
              Top = 40
              Width = 65
              Height = 25
              Caption = 'Refresh'
              TabOrder = 2
              OnClick = MinAnimateRefreshClick
              Kind = bkRetry
            end
          end
        end
        object AccelerationP2: TTabSheet
          Caption = 'Page 2'
          ImageIndex = 1
          object WaitToKillAppTimeoutHelp: TGroupBox
            Left = 0
            Top = 88
            Width = 249
            Height = 73
            Cursor = crHelp
            Caption = 'WaitToKillAppTimeout'
            TabOrder = 0
            OnClick = WaitToKillAppTimeoutHelpClick
            object Panel47: TPanel
              Left = 8
              Top = 16
              Width = 161
              Height = 49
              BorderStyle = bsSingle
              TabOrder = 0
              object GroupBox4: TGroupBox
                Left = 8
                Top = 0
                Width = 145
                Height = 41
                Caption = 'Time (ms)'
                TabOrder = 0
                object Edit5: TEdit
                  Left = 8
                  Top = 16
                  Width = 129
                  Height = 21
                  TabOrder = 0
                end
              end
            end
            object WaitToKillAppTimeoutSave: TBitBtn
              Left = 176
              Top = 16
              Width = 65
              Height = 25
              Caption = 'Save'
              TabOrder = 1
              OnClick = WaitToKillAppTimeoutSaveClick
              Kind = bkOK
            end
            object WaitToKillAppTimeoutRefresh: TBitBtn
              Left = 176
              Top = 40
              Width = 65
              Height = 25
              Caption = 'Refresh'
              TabOrder = 2
              OnClick = WaitToKillAppTimeoutRefreshClick
              Kind = bkRetry
            end
          end
          object WaitToKillServiceTimeOutHelp: TGroupBox
            Left = 264
            Top = 88
            Width = 249
            Height = 73
            Cursor = crHelp
            Caption = 'WaitToKillServiceTimeOut'
            TabOrder = 1
            OnClick = WaitToKillServiceTimeOutHelpClick
            object Panel3: TPanel
              Left = 8
              Top = 16
              Width = 161
              Height = 49
              BorderStyle = bsSingle
              TabOrder = 0
              object GroupBox3: TGroupBox
                Left = 8
                Top = 0
                Width = 145
                Height = 41
                Caption = 'Time (ms)'
                TabOrder = 0
                object Edit1: TEdit
                  Left = 8
                  Top = 16
                  Width = 129
                  Height = 21
                  TabOrder = 0
                end
              end
            end
            object BitBtn5: TBitBtn
              Left = 176
              Top = 16
              Width = 65
              Height = 25
              Caption = 'Save'
              TabOrder = 1
              OnClick = BitBtn5Click
              Kind = bkYes
            end
            object BitBtn6: TBitBtn
              Left = 176
              Top = 40
              Width = 65
              Height = 25
              Caption = 'Refresh'
              TabOrder = 2
              OnClick = BitBtn6Click
              Kind = bkRetry
            end
          end
          object NtfsMftZoneReservationHelp: TGroupBox
            Left = 264
            Top = 8
            Width = 249
            Height = 73
            Cursor = crHelp
            Caption = 'NtfsMftZoneReservation'
            TabOrder = 2
            OnClick = NtfsMftZoneReservationHelpClick
            object Panel18: TPanel
              Left = 8
              Top = 16
              Width = 161
              Height = 49
              BorderStyle = bsSingle
              TabOrder = 0
              object RadioButton29: TRadioButton
                Left = 8
                Top = 8
                Width = 25
                Height = 17
                Caption = '1'
                Checked = True
                TabOrder = 0
                TabStop = True
              end
              object RadioButton30: TRadioButton
                Left = 8
                Top = 24
                Width = 25
                Height = 17
                Caption = '2'
                TabOrder = 1
              end
              object RadioButton31: TRadioButton
                Left = 112
                Top = 8
                Width = 33
                Height = 17
                Caption = '3'
                TabOrder = 2
              end
              object RadioButton32: TRadioButton
                Left = 112
                Top = 24
                Width = 33
                Height = 17
                Caption = '4'
                TabOrder = 3
              end
            end
            object NtfsMftZoneReservationSave: TBitBtn
              Left = 176
              Top = 16
              Width = 65
              Height = 25
              Caption = 'Save'
              TabOrder = 1
              OnClick = NtfsMftZoneReservationSaveClick
              Kind = bkOK
            end
            object NtfsMftZoneReservationRefresh: TBitBtn
              Left = 176
              Top = 40
              Width = 65
              Height = 25
              Caption = 'Refresh'
              TabOrder = 2
              OnClick = NtfsMftZoneReservationRefreshClick
              Kind = bkRetry
            end
          end
          object NtfsDisable8dot3NameCreationHelp: TGroupBox
            Left = 0
            Top = 8
            Width = 249
            Height = 73
            Cursor = crHelp
            Caption = 'NtfsDisable8dot3NameCreation'
            TabOrder = 3
            OnClick = NtfsDisable8dot3NameCreationHelpClick
            object Panel20: TPanel
              Left = 8
              Top = 16
              Width = 161
              Height = 49
              BorderStyle = bsSingle
              TabOrder = 0
              object RadioButton35: TRadioButton
                Left = 8
                Top = 8
                Width = 129
                Height = 17
                Caption = 'Enable'
                Checked = True
                TabOrder = 0
                TabStop = True
              end
              object RadioButton36: TRadioButton
                Left = 8
                Top = 24
                Width = 137
                Height = 17
                Caption = 'Disable'
                TabOrder = 1
              end
            end
            object NtfsDisable8dot3NameCreationSave: TBitBtn
              Left = 176
              Top = 16
              Width = 65
              Height = 25
              Caption = 'Save'
              TabOrder = 1
              OnClick = NtfsDisable8dot3NameCreationSaveClick
              Kind = bkOK
            end
            object NtfsDisable8dot3NameCreationRefresh: TBitBtn
              Left = 176
              Top = 40
              Width = 65
              Height = 25
              Caption = 'Refresh'
              TabOrder = 2
              OnClick = NtfsDisable8dot3NameCreationRefreshClick
              Kind = bkRetry
            end
          end
          object GroupBox2: TGroupBox
            Left = 0
            Top = 168
            Width = 249
            Height = 73
            Cursor = crHelp
            TabOrder = 4
            object Panel45: TPanel
              Left = 8
              Top = 16
              Width = 161
              Height = 49
              BorderStyle = bsSingle
              TabOrder = 0
              object RadioButton85: TRadioButton
                Left = 8
                Top = 8
                Width = 113
                Height = 17
                Caption = 'Enable'
                Checked = True
                TabOrder = 0
                TabStop = True
              end
              object RadioButton86: TRadioButton
                Left = 8
                Top = 24
                Width = 113
                Height = 17
                Caption = 'Disable'
                TabOrder = 1
              end
            end
            object BitBtn1: TBitBtn
              Left = 176
              Top = 16
              Width = 65
              Height = 25
              Caption = 'Save'
              TabOrder = 1
              Kind = bkOK
            end
            object BitBtn2: TBitBtn
              Left = 176
              Top = 40
              Width = 65
              Height = 25
              Caption = 'Refresh'
              TabOrder = 2
              Kind = bkRetry
            end
          end
        end
      end
    end
    object Explorer: TTabSheet
      Caption = 'Explorer'
      ImageIndex = 1
      object ExplorerPages: TPageControl
        Left = 0
        Top = 8
        Width = 521
        Height = 353
        ActivePage = ExplorerPage1
        TabIndex = 0
        TabOrder = 0
        object ExplorerPage1: TTabSheet
          Caption = 'Page 1'
          object SharedDocumentsHelp: TGroupBox
            Left = 264
            Top = 8
            Width = 249
            Height = 73
            Cursor = crHelp
            Caption = 'Hide / Show '#39'Shared Documents'#39
            TabOrder = 0
            OnClick = SharedDocumentsHelpClick
            object Panel5: TPanel
              Left = 8
              Top = 16
              Width = 161
              Height = 49
              BorderStyle = bsSingle
              TabOrder = 0
              object RadioButton7: TRadioButton
                Left = 8
                Top = 8
                Width = 113
                Height = 17
                Caption = 'Hide Folder'
                Checked = True
                TabOrder = 0
                TabStop = True
              end
              object RadioButton8: TRadioButton
                Left = 8
                Top = 24
                Width = 113
                Height = 17
                Caption = 'Show Folder'
                TabOrder = 1
              end
            end
            object SharedDocumentsSave: TBitBtn
              Left = 176
              Top = 16
              Width = 65
              Height = 25
              Caption = 'Save'
              TabOrder = 1
              OnClick = SharedDocumentsSaveClick
              Kind = bkOK
            end
            object SharedDocumentsRefresh: TBitBtn
              Left = 176
              Top = 40
              Width = 65
              Height = 25
              Caption = 'Refresh'
              TabOrder = 2
              OnClick = SharedDocumentsRefreshClick
              Kind = bkRetry
            end
          end
          object NoLowDiskSpaceChecksHelp: TGroupBox
            Left = 0
            Top = 8
            Width = 249
            Height = 73
            Cursor = crHelp
            Caption = 'NoLowDiskSpaceChecks'
            TabOrder = 1
            OnClick = NoLowDiskSpaceChecksHelpClick
            object Panel4: TPanel
              Left = 8
              Top = 16
              Width = 161
              Height = 49
              BorderStyle = bsSingle
              TabOrder = 0
              object RadioButton5: TRadioButton
                Left = 8
                Top = 8
                Width = 137
                Height = 17
                Caption = 'Enable'
                Checked = True
                TabOrder = 0
                TabStop = True
              end
              object RadioButton6: TRadioButton
                Left = 8
                Top = 24
                Width = 137
                Height = 17
                Caption = 'Disable'
                TabOrder = 1
              end
            end
            object NoLowDiskSpaceChecksSave: TBitBtn
              Left = 176
              Top = 16
              Width = 65
              Height = 25
              Caption = 'Save'
              TabOrder = 1
              OnClick = NoLowDiskSpaceChecksSaveClick
              Kind = bkOK
            end
            object NoLowDiskSpaceChecksRefresh: TBitBtn
              Left = 176
              Top = 40
              Width = 65
              Height = 25
              Caption = 'Refresh'
              TabOrder = 2
              OnClick = NoLowDiskSpaceChecksRefreshClick
              Kind = bkRetry
            end
          end
          object FullScreenHelp: TGroupBox
            Left = 264
            Top = 88
            Width = 249
            Height = 73
            Cursor = crHelp
            Caption = 'FullScreen'
            TabOrder = 2
            OnClick = FullScreenHelpClick
            object Panel19: TPanel
              Left = 8
              Top = 16
              Width = 161
              Height = 49
              BorderStyle = bsSingle
              TabOrder = 0
              object RadioButton33: TRadioButton
                Left = 8
                Top = 8
                Width = 129
                Height = 17
                Caption = 'Enable'
                Checked = True
                TabOrder = 0
                TabStop = True
              end
              object RadioButton34: TRadioButton
                Left = 8
                Top = 24
                Width = 137
                Height = 17
                Caption = 'Disable'
                TabOrder = 1
              end
            end
            object FullScreenSave: TBitBtn
              Left = 176
              Top = 16
              Width = 65
              Height = 25
              Caption = 'Save'
              TabOrder = 1
              OnClick = FullScreenSaveClick
              Kind = bkOK
            end
            object FullScreenRefresh: TBitBtn
              Left = 176
              Top = 40
              Width = 65
              Height = 25
              Caption = 'Refresh'
              TabOrder = 2
              OnClick = FullScreenRefreshClick
              Kind = bkRetry
            end
          end
          object NoDesktopHelp: TGroupBox
            Left = 0
            Top = 88
            Width = 249
            Height = 73
            Cursor = crHelp
            Caption = 'NoDesktop'
            TabOrder = 3
            OnClick = NoDesktopHelpClick
            object Panel30: TPanel
              Left = 8
              Top = 16
              Width = 161
              Height = 49
              BorderStyle = bsSingle
              TabOrder = 0
              object RadioButton55: TRadioButton
                Left = 8
                Top = 8
                Width = 113
                Height = 17
                Caption = 'Enable'
                Checked = True
                TabOrder = 0
                TabStop = True
              end
              object RadioButton56: TRadioButton
                Left = 8
                Top = 24
                Width = 113
                Height = 17
                Caption = 'Disable'
                TabOrder = 1
              end
            end
            object NoDesktopSave: TBitBtn
              Left = 176
              Top = 16
              Width = 65
              Height = 25
              Caption = 'Save'
              TabOrder = 1
              OnClick = NoDesktopSaveClick
              Kind = bkOK
            end
            object NoDesktopRefresh: TBitBtn
              Left = 176
              Top = 40
              Width = 65
              Height = 25
              Caption = 'Refresh'
              TabOrder = 2
              OnClick = NoDesktopRefreshClick
              Kind = bkRetry
            end
          end
          object ClearRecentDocsOnExitHelp: TGroupBox
            Left = 0
            Top = 248
            Width = 249
            Height = 73
            Cursor = crHelp
            Caption = 'ClearRecentDocsOnExit'
            TabOrder = 4
            OnClick = GroupBox18Click
            object Panel15: TPanel
              Left = 8
              Top = 16
              Width = 161
              Height = 49
              BorderStyle = bsSingle
              TabOrder = 0
              object RadioButton23: TRadioButton
                Left = 8
                Top = 8
                Width = 129
                Height = 17
                Caption = 'Enable'
                Checked = True
                TabOrder = 0
                TabStop = True
              end
              object RadioButton24: TRadioButton
                Left = 8
                Top = 24
                Width = 137
                Height = 17
                Caption = 'Disable'
                TabOrder = 1
              end
            end
            object ClearRecentDocsOnExitSave: TBitBtn
              Left = 176
              Top = 16
              Width = 65
              Height = 25
              Caption = 'Save'
              TabOrder = 1
              OnClick = ClearRecentDocsOnExitSaveClick
              Kind = bkOK
            end
            object ClearRecentDocsOnExitRefresh: TBitBtn
              Left = 176
              Top = 40
              Width = 65
              Height = 25
              Caption = 'Refresh'
              TabOrder = 2
              OnClick = ClearRecentDocsOnExitRefreshClick
              Kind = bkRetry
            end
          end
          object RecycleBinHelp: TGroupBox
            Left = 0
            Top = 168
            Width = 249
            Height = 73
            Cursor = crHelp
            Caption = 'Recycle Bin Hide / Show'
            TabOrder = 5
            OnClick = RecycleBinHelpClick
            object Panel31: TPanel
              Left = 8
              Top = 16
              Width = 161
              Height = 49
              BorderStyle = bsSingle
              TabOrder = 0
              object RadioButton57: TRadioButton
                Left = 8
                Top = 8
                Width = 113
                Height = 17
                Caption = 'Hide Recycle Bin'
                Checked = True
                TabOrder = 0
                TabStop = True
              end
              object RadioButton58: TRadioButton
                Left = 8
                Top = 24
                Width = 113
                Height = 17
                Caption = 'Show Recycle Bin'
                TabOrder = 1
              end
            end
            object RecycleBinSave: TBitBtn
              Left = 176
              Top = 16
              Width = 65
              Height = 25
              Caption = 'Save'
              TabOrder = 1
              OnClick = RecycleBinSaveClick
              Kind = bkOK
            end
            object RecycleBinRefresh: TBitBtn
              Left = 176
              Top = 40
              Width = 65
              Height = 25
              Caption = 'Refresh'
              TabOrder = 2
              OnClick = RecycleBinRefreshClick
              Kind = bkRetry
            end
          end
          object RecycleBinRenameHelp: TGroupBox
            Left = 264
            Top = 168
            Width = 249
            Height = 73
            Cursor = crHelp
            Caption = 'Recycle Bin Rename'
            TabOrder = 6
            OnClick = RecycleBinRenameHelpClick
            object Panel29: TPanel
              Left = 8
              Top = 16
              Width = 161
              Height = 49
              BorderStyle = bsSingle
              TabOrder = 0
              object GroupBox1: TGroupBox
                Left = 8
                Top = 0
                Width = 145
                Height = 41
                Caption = 'Name'
                TabOrder = 0
                object Edit4: TEdit
                  Left = 8
                  Top = 16
                  Width = 129
                  Height = 21
                  TabOrder = 0
                end
              end
            end
            object RecycleBinRenameSave: TBitBtn
              Left = 176
              Top = 16
              Width = 65
              Height = 25
              Caption = 'Save'
              TabOrder = 1
              OnClick = RecycleBinRenameSaveClick
              Kind = bkOK
            end
            object RecycleBinRenameRefresh: TBitBtn
              Left = 176
              Top = 40
              Width = 65
              Height = 25
              Caption = 'Refresh'
              TabOrder = 2
              OnClick = RecycleBinRenameRefreshClick
              Kind = bkRetry
            end
          end
          object PaintDesktopVersionHelp: TGroupBox
            Left = 264
            Top = 248
            Width = 249
            Height = 73
            Cursor = crHelp
            Caption = 'PaintDesktopVersion'
            TabOrder = 7
            OnClick = PaintDesktopVersionHelpClick
            object Panel36: TPanel
              Left = 8
              Top = 16
              Width = 161
              Height = 49
              BorderStyle = bsSingle
              TabOrder = 0
              object RadioButton67: TRadioButton
                Left = 8
                Top = 8
                Width = 113
                Height = 17
                Caption = 'Enable'
                Checked = True
                TabOrder = 0
                TabStop = True
              end
              object RadioButton68: TRadioButton
                Left = 8
                Top = 24
                Width = 113
                Height = 17
                Caption = 'Disable'
                TabOrder = 1
              end
            end
            object PaintDesktopVersionSave: TBitBtn
              Left = 176
              Top = 16
              Width = 65
              Height = 25
              Caption = 'Save'
              TabOrder = 1
              OnClick = PaintDesktopVersionSaveClick
              Kind = bkOK
            end
            object PaintDesktopVersionRefresh: TBitBtn
              Left = 176
              Top = 40
              Width = 65
              Height = 25
              Caption = 'Refresh'
              TabOrder = 2
              OnClick = PaintDesktopVersionRefreshClick
              Kind = bkRetry
            end
          end
        end
        object ExplorerPage2: TTabSheet
          Caption = 'Page 2'
          ImageIndex = 1
          object NoViewContextMenuHelp: TGroupBox
            Left = 0
            Top = 8
            Width = 249
            Height = 73
            Cursor = crHelp
            Caption = 'NoViewContextMenu'
            TabOrder = 0
            OnClick = NoViewContextMenuHelpClick
            object Panel38: TPanel
              Left = 8
              Top = 16
              Width = 161
              Height = 49
              BorderStyle = bsSingle
              TabOrder = 0
              object RadioButton71: TRadioButton
                Left = 8
                Top = 8
                Width = 113
                Height = 17
                Caption = 'Enable'
                Checked = True
                TabOrder = 0
                TabStop = True
              end
              object RadioButton72: TRadioButton
                Left = 8
                Top = 24
                Width = 113
                Height = 17
                Caption = 'Disable'
                TabOrder = 1
              end
            end
            object NoViewContextMenuSave: TBitBtn
              Left = 176
              Top = 16
              Width = 65
              Height = 25
              Caption = 'Save'
              TabOrder = 1
              OnClick = NoViewContextMenuSaveClick
              Kind = bkOK
            end
            object NoViewContextMenuRefresh: TBitBtn
              Left = 176
              Top = 40
              Width = 65
              Height = 25
              Caption = 'Refresh'
              TabOrder = 2
              OnClick = NoViewContextMenuRefreshClick
              Kind = bkRetry
            end
          end
        end
      end
    end
    object Hardware: TTabSheet
      Caption = 'Hardware'
      ImageIndex = 5
      object EnableUDMA66Help: TGroupBox
        Left = 264
        Top = 88
        Width = 249
        Height = 73
        Cursor = crHelp
        Caption = 'EnableUDMA66'
        TabOrder = 0
        OnClick = EnableUDMA66HelpClick
        object Panel21: TPanel
          Left = 8
          Top = 16
          Width = 161
          Height = 49
          BorderStyle = bsSingle
          TabOrder = 0
          object RadioButton37: TRadioButton
            Left = 8
            Top = 8
            Width = 113
            Height = 17
            Caption = 'Enable'
            Checked = True
            TabOrder = 0
            TabStop = True
          end
          object RadioButton38: TRadioButton
            Left = 8
            Top = 24
            Width = 113
            Height = 17
            Caption = 'Disable'
            TabOrder = 1
          end
        end
        object EnableUDMA66Save: TBitBtn
          Left = 176
          Top = 16
          Width = 65
          Height = 25
          Caption = 'Save'
          TabOrder = 1
          OnClick = EnableUDMA66SaveClick
          Kind = bkOK
        end
        object EnableUDMA66Refresh: TBitBtn
          Left = 176
          Top = 40
          Width = 65
          Height = 25
          Caption = 'Refresh'
          TabOrder = 2
          OnClick = EnableUDMA66RefreshClick
          Kind = bkRetry
        end
      end
      object PowerdownAfterShutdownHelp: TGroupBox
        Left = 8
        Top = 248
        Width = 249
        Height = 73
        Cursor = crHelp
        Caption = 'PowerdownAfterShutdown'
        TabOrder = 1
        OnClick = PowerdownAfterShutdownHelpClick
        object Panel22: TPanel
          Left = 8
          Top = 16
          Width = 161
          Height = 49
          BorderStyle = bsSingle
          TabOrder = 0
          object RadioButton39: TRadioButton
            Left = 8
            Top = 8
            Width = 129
            Height = 17
            Caption = 'Enable'
            Checked = True
            TabOrder = 0
            TabStop = True
          end
          object RadioButton40: TRadioButton
            Left = 8
            Top = 24
            Width = 137
            Height = 17
            Caption = 'Disable'
            TabOrder = 1
          end
        end
        object PowerdownAfterShutdownSave: TBitBtn
          Left = 176
          Top = 16
          Width = 65
          Height = 25
          Caption = 'Save'
          TabOrder = 1
          OnClick = PowerdownAfterShutdownSaveClick
          Kind = bkOK
        end
        object PowerdownAfterShutdownRefresh: TBitBtn
          Left = 176
          Top = 40
          Width = 65
          Height = 25
          Caption = 'Refresh'
          TabOrder = 2
          OnClick = PowerdownAfterShutdownRefreshClick
          Kind = bkRetry
        end
      end
      object AutoRunHelp: TGroupBox
        Left = 8
        Top = 8
        Width = 249
        Height = 73
        Cursor = crHelp
        Caption = 'AutoRun'
        TabOrder = 2
        OnClick = AutoRunHelpClick
        object Panel1: TPanel
          Left = 8
          Top = 16
          Width = 161
          Height = 49
          BorderStyle = bsSingle
          TabOrder = 0
          object RadioButton1: TRadioButton
            Left = 8
            Top = 8
            Width = 81
            Height = 17
            Caption = 'Enable'
            Checked = True
            TabOrder = 0
            TabStop = True
          end
          object RadioButton2: TRadioButton
            Left = 8
            Top = 24
            Width = 129
            Height = 17
            Caption = 'Disable'
            TabOrder = 1
          end
        end
        object AutoRunSave: TBitBtn
          Left = 176
          Top = 16
          Width = 65
          Height = 25
          Caption = 'Save'
          TabOrder = 1
          OnClick = AutoRunSaveClick
          Kind = bkOK
        end
        object AutoRunRefresh: TBitBtn
          Left = 176
          Top = 40
          Width = 65
          Height = 25
          Caption = 'Refresh'
          TabOrder = 2
          OnClick = AutoRunRefreshClick
          Kind = bkRetry
        end
      end
      object CoolBitsHelp: TGroupBox
        Left = 8
        Top = 88
        Width = 249
        Height = 73
        Cursor = crHelp
        Caption = 'CoolBits'
        TabOrder = 3
        OnClick = CoolBitsHelpClick
        object Panel32: TPanel
          Left = 8
          Top = 16
          Width = 161
          Height = 49
          BorderStyle = bsSingle
          TabOrder = 0
          object RadioButton53: TRadioButton
            Left = 8
            Top = 8
            Width = 113
            Height = 17
            Caption = 'Enable'
            Checked = True
            TabOrder = 0
            TabStop = True
          end
          object RadioButton54: TRadioButton
            Left = 8
            Top = 24
            Width = 113
            Height = 17
            Caption = 'Disable'
            TabOrder = 1
          end
        end
        object CoolBitsSave: TBitBtn
          Left = 176
          Top = 16
          Width = 65
          Height = 25
          Caption = 'Save'
          TabOrder = 1
          OnClick = CoolBitsSaveClick
          Kind = bkOK
        end
        object CoolBitsRefresh: TBitBtn
          Left = 176
          Top = 40
          Width = 65
          Height = 25
          Caption = 'Refresh'
          TabOrder = 2
          OnClick = CoolBitsRefreshClick
          Kind = bkRetry
        end
      end
      object BeepHelp: TGroupBox
        Left = 264
        Top = 8
        Width = 249
        Height = 73
        Cursor = crHelp
        Caption = 'Beep'
        TabOrder = 4
        OnClick = BeepHelpClick
        object Panel34: TPanel
          Left = 8
          Top = 16
          Width = 161
          Height = 49
          BorderStyle = bsSingle
          TabOrder = 0
          object RadioButton63: TRadioButton
            Left = 8
            Top = 8
            Width = 113
            Height = 17
            Caption = 'Enable'
            Checked = True
            TabOrder = 0
            TabStop = True
          end
          object RadioButton64: TRadioButton
            Left = 8
            Top = 24
            Width = 113
            Height = 17
            Caption = 'Disable'
            TabOrder = 1
          end
        end
        object BeepSave: TBitBtn
          Left = 176
          Top = 16
          Width = 65
          Height = 25
          Caption = 'Save'
          TabOrder = 1
          OnClick = BeepSaveClick
          Kind = bkOK
        end
        object BeepRefresh: TBitBtn
          Left = 176
          Top = 40
          Width = 65
          Height = 25
          Caption = 'Refresh'
          TabOrder = 2
          OnClick = BeepRefreshClick
          Kind = bkRetry
        end
      end
      object InitialKeyboardIndicatorsHelp: TGroupBox
        Left = 8
        Top = 168
        Width = 249
        Height = 73
        Cursor = crHelp
        Caption = 'InitialKeyboardIndicators'
        TabOrder = 5
        OnClick = InitialKeyboardIndicatorsHelpClick
        object Panel40: TPanel
          Left = 8
          Top = 16
          Width = 161
          Height = 49
          BorderStyle = bsSingle
          TabOrder = 0
          object RadioButton75: TRadioButton
            Left = 8
            Top = 8
            Width = 113
            Height = 17
            Caption = 'Enable'
            Checked = True
            TabOrder = 0
            TabStop = True
          end
          object RadioButton76: TRadioButton
            Left = 8
            Top = 24
            Width = 113
            Height = 17
            Caption = 'Disable'
            TabOrder = 1
          end
        end
        object InitialKeyboardIndicatorsSave: TBitBtn
          Left = 176
          Top = 16
          Width = 65
          Height = 25
          Caption = 'Save'
          TabOrder = 1
          OnClick = InitialKeyboardIndicatorsSaveClick
          Kind = bkOK
        end
        object InitialKeyboardIndicatorsRefresh: TBitBtn
          Left = 176
          Top = 40
          Width = 65
          Height = 25
          Caption = 'Refresh'
          TabOrder = 2
          OnClick = InitialKeyboardIndicatorsRefreshClick
          Kind = bkRetry
        end
      end
      object InitialKeyboardIndicatorsUserHelp: TGroupBox
        Left = 264
        Top = 168
        Width = 249
        Height = 73
        Cursor = crHelp
        Caption = 'InitialKeyboardIndicators (User)'
        TabOrder = 6
        OnClick = InitialKeyboardIndicatorsUserHelpClick
        object Panel49: TPanel
          Left = 8
          Top = 16
          Width = 161
          Height = 49
          BorderStyle = bsSingle
          TabOrder = 0
          object RadioButton89: TRadioButton
            Left = 8
            Top = 8
            Width = 113
            Height = 17
            Caption = 'Enable'
            Checked = True
            TabOrder = 0
            TabStop = True
          end
          object RadioButton90: TRadioButton
            Left = 8
            Top = 24
            Width = 113
            Height = 17
            Caption = 'Disable'
            TabOrder = 1
          end
        end
        object InitialKeyboardIndicatorsUserSave: TBitBtn
          Left = 176
          Top = 16
          Width = 65
          Height = 25
          Caption = 'Save'
          TabOrder = 1
          OnClick = InitialKeyboardIndicatorsUserSaveClick
          Kind = bkOK
        end
        object InitialKeyboardIndicatorsUserRefresh: TBitBtn
          Left = 176
          Top = 40
          Width = 65
          Height = 25
          Caption = 'Refresh'
          TabOrder = 2
          OnClick = InitialKeyboardIndicatorsUserRefreshClick
          Kind = bkRetry
        end
      end
    end
    object Memory: TTabSheet
      Caption = 'Memory'
      object DisablePagingExecutiveHelp: TGroupBox
        Left = 264
        Top = 8
        Width = 249
        Height = 73
        Cursor = crHelp
        Caption = 'DisablePagingExecutive'
        TabOrder = 0
        OnClick = DisablePagingExecutiveHelpClick
        object Panel9: TPanel
          Left = 8
          Top = 16
          Width = 161
          Height = 49
          BorderStyle = bsSingle
          TabOrder = 0
          object RadioButton13: TRadioButton
            Left = 8
            Top = 8
            Width = 81
            Height = 17
            Caption = 'Enable'
            Checked = True
            TabOrder = 0
            TabStop = True
          end
          object RadioButton14: TRadioButton
            Left = 8
            Top = 24
            Width = 81
            Height = 17
            Caption = 'Disable'
            TabOrder = 1
          end
        end
        object DisablePagingExecutiveSave: TBitBtn
          Left = 176
          Top = 16
          Width = 65
          Height = 25
          Caption = 'Save'
          TabOrder = 1
          OnClick = DisablePagingExecutiveSaveClick
          Kind = bkOK
        end
        object DisablePagingExecutiveRefresh: TBitBtn
          Left = 176
          Top = 40
          Width = 65
          Height = 25
          Caption = 'Refresh'
          TabOrder = 2
          OnClick = DisablePagingExecutiveRefreshClick
          Kind = bkRetry
        end
      end
      object LargeSystemCacheHelp: TGroupBox
        Left = 264
        Top = 88
        Width = 249
        Height = 73
        Cursor = crHelp
        Caption = 'LargeSystemCache'
        TabOrder = 1
        OnClick = LargeSystemCacheHelpClick
        object Panel10: TPanel
          Left = 8
          Top = 16
          Width = 161
          Height = 49
          BorderStyle = bsSingle
          TabOrder = 0
          object RadioButton15: TRadioButton
            Left = 8
            Top = 8
            Width = 73
            Height = 17
            Caption = 'Enable'
            Checked = True
            TabOrder = 0
            TabStop = True
          end
          object RadioButton16: TRadioButton
            Left = 8
            Top = 24
            Width = 81
            Height = 17
            Caption = 'Disable'
            TabOrder = 1
          end
        end
        object LargeSystemCacheSave: TBitBtn
          Left = 176
          Top = 16
          Width = 65
          Height = 25
          Caption = 'Save'
          TabOrder = 1
          OnClick = LargeSystemCacheSaveClick
          Kind = bkOK
        end
        object LargeSystemCacheRefresh: TBitBtn
          Left = 176
          Top = 40
          Width = 65
          Height = 25
          Caption = 'Refresh'
          TabOrder = 2
          OnClick = LargeSystemCacheRefreshClick
          Kind = bkRetry
        end
      end
      object IOPageLockLimitHelp: TGroupBox
        Left = 8
        Top = 88
        Width = 249
        Height = 73
        Cursor = crHelp
        Caption = 'IOPageLockLimit'
        TabOrder = 2
        OnClick = IOPageLockLimitHelpClick
        object Panel11: TPanel
          Left = 8
          Top = 16
          Width = 161
          Height = 49
          BorderStyle = bsSingle
          TabOrder = 0
          object GroupBox14: TGroupBox
            Left = 8
            Top = 0
            Width = 145
            Height = 41
            Caption = 'Value (Bytes)'
            TabOrder = 0
            object Edit3: TEdit
              Left = 8
              Top = 16
              Width = 129
              Height = 21
              TabOrder = 0
            end
          end
        end
        object IOPageLockLimitSave: TBitBtn
          Left = 176
          Top = 16
          Width = 65
          Height = 25
          Caption = 'Save'
          TabOrder = 1
          OnClick = IOPageLockLimitSaveClick
          Kind = bkOK
        end
        object IOPageLockLimitRefresh: TBitBtn
          Left = 176
          Top = 40
          Width = 65
          Height = 25
          Caption = 'Refresh'
          TabOrder = 2
          OnClick = IOPageLockLimitRefreshClick
          Kind = bkRetry
        end
      end
      object ClearPageFileAtShutdownHelp: TGroupBox
        Left = 8
        Top = 8
        Width = 249
        Height = 73
        Cursor = crHelp
        Caption = 'ClearPageFileAtShutdown'
        TabOrder = 3
        OnClick = ClearPageFileAtShutdownHelpClick
        object Panel12: TPanel
          Left = 8
          Top = 16
          Width = 161
          Height = 49
          BorderStyle = bsSingle
          TabOrder = 0
          object RadioButton17: TRadioButton
            Left = 8
            Top = 8
            Width = 73
            Height = 17
            Caption = 'Enable'
            Checked = True
            TabOrder = 0
            TabStop = True
          end
          object RadioButton18: TRadioButton
            Left = 8
            Top = 24
            Width = 73
            Height = 17
            Caption = 'Disable'
            TabOrder = 1
          end
        end
        object ClearPageFileAtShutdownSave: TBitBtn
          Left = 176
          Top = 16
          Width = 65
          Height = 25
          Caption = 'Save'
          TabOrder = 1
          OnClick = ClearPageFileAtShutdownSaveClick
          Kind = bkOK
        end
        object ClearPageFileAtShutdownRefresh: TBitBtn
          Left = 176
          Top = 40
          Width = 65
          Height = 25
          Caption = 'Refresh'
          TabOrder = 2
          OnClick = ClearPageFileAtShutdownRefreshClick
          Kind = bkRetry
        end
      end
    end
    object Net: TTabSheet
      Caption = 'Net'
      ImageIndex = 6
      object NetPages: TPageControl
        Left = 0
        Top = 8
        Width = 521
        Height = 353
        ActivePage = NetPage1
        TabIndex = 0
        TabOrder = 0
        object NetPage1: TTabSheet
          Caption = 'Page 1'
          object DeadGWDetectDefaultHelp: TGroupBox
            Left = 0
            Top = 88
            Width = 249
            Height = 73
            Cursor = crHelp
            Caption = 'DeadGWDetectDefault'
            TabOrder = 0
            OnClick = DeadGWDetectDefaultHelpClick
            object Panel27: TPanel
              Left = 8
              Top = 16
              Width = 161
              Height = 49
              BorderStyle = bsSingle
              TabOrder = 0
              object RadioButton49: TRadioButton
                Left = 8
                Top = 8
                Width = 113
                Height = 17
                Caption = 'Enable'
                Checked = True
                TabOrder = 0
                TabStop = True
              end
              object RadioButton50: TRadioButton
                Left = 8
                Top = 24
                Width = 113
                Height = 17
                Caption = 'Disable'
                TabOrder = 1
              end
            end
            object DeadGWDetectDefaultSave: TBitBtn
              Left = 176
              Top = 16
              Width = 65
              Height = 25
              Caption = 'Save'
              TabOrder = 1
              OnClick = DeadGWDetectDefaultSaveClick
              Kind = bkOK
            end
            object DeadGWDetectDefaultRefresh: TBitBtn
              Left = 176
              Top = 40
              Width = 65
              Height = 25
              Caption = 'Refresh'
              TabOrder = 2
              OnClick = DeadGWDetectDefaultRefreshClick
              Kind = bkRetry
            end
          end
          object AutoShareServerHelp: TGroupBox
            Left = 0
            Top = 8
            Width = 249
            Height = 73
            Cursor = crHelp
            Caption = 'AutoShareServer'
            TabOrder = 1
            OnClick = AutoShareServerHelpClick
            object Panel26: TPanel
              Left = 8
              Top = 16
              Width = 161
              Height = 49
              BorderStyle = bsSingle
              TabOrder = 0
              object RadioButton47: TRadioButton
                Left = 8
                Top = 8
                Width = 113
                Height = 17
                Caption = 'Enable'
                Checked = True
                TabOrder = 0
                TabStop = True
              end
              object RadioButton48: TRadioButton
                Left = 8
                Top = 24
                Width = 113
                Height = 17
                Caption = 'Disable'
                TabOrder = 1
              end
            end
            object AutoShareServerSave: TBitBtn
              Left = 176
              Top = 16
              Width = 65
              Height = 25
              Caption = 'Save'
              TabOrder = 1
              OnClick = AutoShareServerSaveClick
              Kind = bkOK
            end
            object AutoShareServerRefresh: TBitBtn
              Left = 176
              Top = 40
              Width = 65
              Height = 25
              Caption = 'Refresh'
              TabOrder = 2
              OnClick = AutoShareServerRefreshClick
              Kind = bkRetry
            end
          end
          object AutoShareWksHelp: TGroupBox
            Left = 264
            Top = 8
            Width = 249
            Height = 73
            Cursor = crHelp
            Caption = 'AutoShareWks'
            TabOrder = 2
            OnClick = AutoShareWksHelpClick
            object Panel25: TPanel
              Left = 8
              Top = 16
              Width = 161
              Height = 49
              BorderStyle = bsSingle
              TabOrder = 0
              object RadioButton45: TRadioButton
                Left = 8
                Top = 8
                Width = 113
                Height = 17
                Caption = 'Enable'
                Checked = True
                TabOrder = 0
                TabStop = True
              end
              object RadioButton46: TRadioButton
                Left = 8
                Top = 24
                Width = 113
                Height = 17
                Caption = 'Disable'
                TabOrder = 1
              end
            end
            object AutoShareWksSave: TBitBtn
              Left = 176
              Top = 16
              Width = 65
              Height = 25
              Caption = 'Save'
              TabOrder = 1
              OnClick = AutoShareWksSaveClick
              Kind = bkOK
            end
            object AutoShareWksRefresh: TBitBtn
              Left = 176
              Top = 40
              Width = 65
              Height = 25
              Caption = 'Refresh'
              TabOrder = 2
              OnClick = AutoShareWksRefreshClick
              Kind = bkRetry
            end
          end
          object HiddenHelp: TGroupBox
            Left = 264
            Top = 168
            Width = 249
            Height = 73
            Cursor = crHelp
            Caption = 'Hidden'
            TabOrder = 3
            OnClick = HiddenHelpClick
            object Panel24: TPanel
              Left = 8
              Top = 16
              Width = 161
              Height = 49
              BorderStyle = bsSingle
              TabOrder = 0
              object RadioButton43: TRadioButton
                Left = 8
                Top = 8
                Width = 113
                Height = 17
                Caption = 'Enable'
                Checked = True
                TabOrder = 0
                TabStop = True
              end
              object RadioButton44: TRadioButton
                Left = 8
                Top = 24
                Width = 113
                Height = 17
                Caption = 'Disable'
                TabOrder = 1
              end
            end
            object SaveHidden: TBitBtn
              Left = 176
              Top = 16
              Width = 65
              Height = 25
              Caption = 'Save'
              TabOrder = 1
              OnClick = SaveHiddenClick
              Kind = bkOK
            end
            object RefreshHidden: TBitBtn
              Left = 176
              Top = 40
              Width = 65
              Height = 25
              Caption = 'Refresh'
              TabOrder = 2
              OnClick = RefreshHiddenClick
              Kind = bkRetry
            end
          end
          object IPEnableRouterHelp: TGroupBox
            Left = 0
            Top = 248
            Width = 249
            Height = 73
            Cursor = crHelp
            Caption = 'IPEnableRouter'
            TabOrder = 4
            OnClick = IPEnableRouterHelpClick
            object Panel41: TPanel
              Left = 8
              Top = 16
              Width = 161
              Height = 49
              BorderStyle = bsSingle
              TabOrder = 0
              object RadioButton77: TRadioButton
                Left = 8
                Top = 8
                Width = 113
                Height = 17
                Caption = 'Enable'
                Checked = True
                TabOrder = 0
                TabStop = True
              end
              object RadioButton78: TRadioButton
                Left = 8
                Top = 24
                Width = 113
                Height = 17
                Caption = 'Disable'
                TabOrder = 1
              end
            end
            object IPEnableRouterSave: TBitBtn
              Left = 176
              Top = 16
              Width = 65
              Height = 25
              Caption = 'Save'
              TabOrder = 1
              OnClick = IPEnableRouterSaveClick
              Kind = bkOK
            end
            object IPEnableRouterRefresh: TBitBtn
              Left = 176
              Top = 40
              Width = 65
              Height = 25
              Caption = 'Refresh'
              TabOrder = 2
              OnClick = IPEnableRouterRefreshClick
              Kind = bkRetry
            end
          end
          object EnableICMPRedirectHelp: TGroupBox
            Left = 264
            Top = 88
            Width = 249
            Height = 73
            Cursor = crHelp
            Caption = 'EnableICMPRedirect'
            TabOrder = 5
            OnClick = EnableICMPRedirectHelpClick
            object Panel42: TPanel
              Left = 8
              Top = 16
              Width = 161
              Height = 49
              BorderStyle = bsSingle
              TabOrder = 0
              object RadioButton79: TRadioButton
                Left = 8
                Top = 8
                Width = 113
                Height = 17
                Caption = 'Enable'
                Checked = True
                TabOrder = 0
                TabStop = True
              end
              object RadioButton80: TRadioButton
                Left = 8
                Top = 24
                Width = 113
                Height = 17
                Caption = 'Disable'
                TabOrder = 1
              end
            end
            object EnableICMPRedirectSave: TBitBtn
              Left = 176
              Top = 16
              Width = 65
              Height = 25
              Caption = 'Save'
              TabOrder = 1
              OnClick = EnableICMPRedirectSaveClick
              Kind = bkOK
            end
            object EnableICMPRedirectRefresh: TBitBtn
              Left = 176
              Top = 40
              Width = 65
              Height = 25
              Caption = 'Refresh'
              TabOrder = 2
              OnClick = EnableICMPRedirectRefreshClick
              Kind = bkRetry
            end
          end
          object EnablePMTUDiscoveryHelp: TGroupBox
            Left = 0
            Top = 168
            Width = 249
            Height = 73
            Cursor = crHelp
            Caption = 'EnablePMTUDiscovery'
            TabOrder = 6
            OnClick = EnablePMTUDiscoveryHelpClick
            object Panel43: TPanel
              Left = 8
              Top = 16
              Width = 161
              Height = 49
              BorderStyle = bsSingle
              TabOrder = 0
              object RadioButton81: TRadioButton
                Left = 8
                Top = 8
                Width = 113
                Height = 17
                Caption = 'Enable'
                Checked = True
                TabOrder = 0
                TabStop = True
              end
              object RadioButton82: TRadioButton
                Left = 8
                Top = 24
                Width = 113
                Height = 17
                Caption = 'Disable'
                TabOrder = 1
              end
            end
            object EnablePMTUDiscoverySave: TBitBtn
              Left = 176
              Top = 16
              Width = 65
              Height = 25
              Caption = 'Save'
              TabOrder = 1
              OnClick = EnablePMTUDiscoverySaveClick
              Kind = bkOK
            end
            object EnablePMTUDiscoveryRefresh: TBitBtn
              Left = 176
              Top = 40
              Width = 65
              Height = 25
              Caption = 'Refresh'
              TabOrder = 2
              OnClick = EnablePMTUDiscoveryRefreshClick
              Kind = bkRetry
            end
          end
          object NoNameReleaseOnDemandHelp: TGroupBox
            Left = 264
            Top = 248
            Width = 249
            Height = 73
            Cursor = crHelp
            Caption = 'NoNameReleaseOnDemand'
            TabOrder = 7
            OnClick = NoNameReleaseOnDemandHelpClick
            object Panel44: TPanel
              Left = 8
              Top = 16
              Width = 161
              Height = 49
              BorderStyle = bsSingle
              TabOrder = 0
              object RadioButton83: TRadioButton
                Left = 8
                Top = 8
                Width = 113
                Height = 17
                Caption = 'Enable'
                Checked = True
                TabOrder = 0
                TabStop = True
              end
              object RadioButton84: TRadioButton
                Left = 8
                Top = 24
                Width = 113
                Height = 17
                Caption = 'Disable'
                TabOrder = 1
              end
            end
            object NoNameReleaseOnDemandSave: TBitBtn
              Left = 176
              Top = 16
              Width = 65
              Height = 25
              Caption = 'Save'
              TabOrder = 1
              OnClick = NoNameReleaseOnDemandSaveClick
              Kind = bkOK
            end
            object NoNameReleaseOnDemandRefresh: TBitBtn
              Left = 176
              Top = 40
              Width = 65
              Height = 25
              Caption = 'Refresh'
              TabOrder = 2
              OnClick = NoNameReleaseOnDemandRefreshClick
              Kind = bkRetry
            end
          end
        end
      end
    end
    object Security: TTabSheet
      Caption = 'Security'
      ImageIndex = 4
      object ScreenSaveActiveHelp: TGroupBox
        Left = 264
        Top = 168
        Width = 249
        Height = 73
        Cursor = crHelp
        Caption = 'ScreenSaveActive'
        TabOrder = 0
        OnClick = ScreenSaveActiveHelpClick
        object Panel13: TPanel
          Left = 8
          Top = 16
          Width = 161
          Height = 49
          BorderStyle = bsSingle
          TabOrder = 0
          object RadioButton19: TRadioButton
            Left = 8
            Top = 24
            Width = 65
            Height = 17
            Caption = 'Disable'
            TabOrder = 0
          end
          object RadioButton20: TRadioButton
            Left = 8
            Top = 8
            Width = 73
            Height = 17
            Caption = 'Enable'
            Checked = True
            TabOrder = 1
            TabStop = True
          end
        end
        object ScreenSaveActiveSave: TBitBtn
          Left = 176
          Top = 16
          Width = 65
          Height = 25
          Caption = 'Save'
          TabOrder = 1
          OnClick = ScreenSaveActiveSaveClick
          Kind = bkOK
        end
        object ScreenSaveActiveRefresh: TBitBtn
          Left = 176
          Top = 40
          Width = 65
          Height = 25
          Caption = 'Refresh'
          TabOrder = 2
          OnClick = ScreenSaveActiveRefreshClick
          Kind = bkRetry
        end
      end
      object DontDisplayLastUserNameHelp: TGroupBox
        Left = 8
        Top = 88
        Width = 249
        Height = 73
        Cursor = crHelp
        Caption = 'DontDisplayLastUserName'
        TabOrder = 1
        OnClick = DontDisplayLastUserNameHelpClick
        object Panel14: TPanel
          Left = 8
          Top = 16
          Width = 161
          Height = 49
          BorderStyle = bsSingle
          TabOrder = 0
          object RadioButton21: TRadioButton
            Left = 8
            Top = 8
            Width = 137
            Height = 17
            Caption = 'Enable'
            Checked = True
            TabOrder = 0
            TabStop = True
          end
          object RadioButton22: TRadioButton
            Left = 8
            Top = 24
            Width = 129
            Height = 17
            Caption = 'Disable'
            TabOrder = 1
          end
        end
        object DontDisplayLastUserNameSave: TBitBtn
          Left = 176
          Top = 16
          Width = 65
          Height = 25
          Caption = 'Save'
          TabOrder = 1
          OnClick = DontDisplayLastUserNameSaveClick
          Kind = bkOK
        end
        object DontDisplayLastUserNameRefresh: TBitBtn
          Left = 176
          Top = 40
          Width = 65
          Height = 25
          Caption = 'Refresh'
          TabOrder = 2
          OnClick = DontDisplayLastUserNameRefreshClick
          Kind = bkRetry
        end
      end
      object restrictanonymousHelp: TGroupBox
        Left = 8
        Top = 168
        Width = 249
        Height = 73
        Cursor = crHelp
        Caption = 'restrictanonymous'
        TabOrder = 2
        OnClick = restrictanonymousHelpClick
        object Panel16: TPanel
          Left = 8
          Top = 16
          Width = 161
          Height = 49
          BorderStyle = bsSingle
          TabOrder = 0
          object RadioButton25: TRadioButton
            Left = 8
            Top = 8
            Width = 129
            Height = 17
            Caption = 'Enable'
            Checked = True
            TabOrder = 0
            TabStop = True
          end
          object RadioButton26: TRadioButton
            Left = 8
            Top = 24
            Width = 137
            Height = 17
            Caption = 'Disable'
            TabOrder = 1
          end
        end
        object restrictanonymousSave: TBitBtn
          Left = 176
          Top = 16
          Width = 65
          Height = 25
          Caption = 'Save'
          TabOrder = 1
          OnClick = restrictanonymousSaveClick
          Kind = bkOK
        end
        object restrictanonymousRefresh: TBitBtn
          Left = 176
          Top = 40
          Width = 65
          Height = 25
          Caption = 'Refresh'
          TabOrder = 2
          OnClick = restrictanonymousRefreshClick
          Kind = bkRetry
        end
      end
      object DisableTaskMgrHelp: TGroupBox
        Left = 8
        Top = 8
        Width = 249
        Height = 73
        Cursor = crHelp
        Caption = 'DisableTaskMgr'
        TabOrder = 3
        OnClick = DisableTaskMgrHelpClick
        object Panel35: TPanel
          Left = 8
          Top = 16
          Width = 161
          Height = 49
          BorderStyle = bsSingle
          TabOrder = 0
          object RadioButton65: TRadioButton
            Left = 8
            Top = 8
            Width = 113
            Height = 17
            Caption = 'Enable'
            Checked = True
            TabOrder = 0
            TabStop = True
          end
          object RadioButton66: TRadioButton
            Left = 8
            Top = 24
            Width = 113
            Height = 17
            Caption = 'Disable'
            TabOrder = 1
          end
        end
        object DisableTaskMgrSave: TBitBtn
          Left = 176
          Top = 16
          Width = 65
          Height = 25
          Caption = 'Save'
          TabOrder = 1
          OnClick = DisableTaskMgrSaveClick
          Kind = bkOK
        end
        object DisableTaskMgrRefresh: TBitBtn
          Left = 176
          Top = 40
          Width = 65
          Height = 25
          Caption = 'Refresh'
          TabOrder = 2
          OnClick = DisableTaskMgrRefreshClick
          Kind = bkRetry
        end
      end
      object ProtectionModeHelp: TGroupBox
        Left = 264
        Top = 88
        Width = 249
        Height = 73
        Cursor = crHelp
        Caption = 'Protection Mode'
        TabOrder = 4
        OnClick = ProtectionModeHelpClick
        object Panel37: TPanel
          Left = 8
          Top = 16
          Width = 161
          Height = 49
          BorderStyle = bsSingle
          TabOrder = 0
          object RadioButton69: TRadioButton
            Left = 8
            Top = 8
            Width = 113
            Height = 17
            Caption = 'Enable'
            Checked = True
            TabOrder = 0
            TabStop = True
          end
          object RadioButton70: TRadioButton
            Left = 8
            Top = 24
            Width = 113
            Height = 17
            Caption = 'Disable'
            TabOrder = 1
          end
        end
        object ProtectionModeSave: TBitBtn
          Left = 176
          Top = 16
          Width = 65
          Height = 25
          Caption = 'Save'
          TabOrder = 1
          OnClick = ProtectionModeSaveClick
          Kind = bkOK
        end
        object ProtectionModeRefresh: TBitBtn
          Left = 176
          Top = 40
          Width = 65
          Height = 25
          Caption = 'Refresh'
          TabOrder = 2
          OnClick = ProtectionModeRefreshClick
          Kind = bkRetry
        end
      end
      object DisableRegistryToolsHelp: TGroupBox
        Left = 264
        Top = 8
        Width = 249
        Height = 73
        Cursor = crHelp
        Caption = 'DisableRegistryTools'
        TabOrder = 5
        OnClick = DisableRegistryToolsHelpClick
        object Panel39: TPanel
          Left = 8
          Top = 16
          Width = 161
          Height = 49
          BorderStyle = bsSingle
          TabOrder = 0
          object RadioButton73: TRadioButton
            Left = 8
            Top = 8
            Width = 113
            Height = 17
            Caption = 'Enable'
            Checked = True
            TabOrder = 0
            TabStop = True
          end
          object RadioButton74: TRadioButton
            Left = 8
            Top = 24
            Width = 113
            Height = 17
            Caption = 'Disable'
            TabOrder = 1
          end
        end
        object DisableRegistryToolsSave: TBitBtn
          Left = 176
          Top = 16
          Width = 65
          Height = 25
          Caption = 'Save'
          TabOrder = 1
          OnClick = DisableRegistryToolsSaveClick
          Kind = bkOK
        end
        object DisableRegistryToolsRefresh: TBitBtn
          Left = 176
          Top = 40
          Width = 65
          Height = 25
          Caption = 'Refresh'
          TabOrder = 2
          OnClick = DisableRegistryToolsRefreshClick
          Kind = bkRetry
        end
      end
    end
    object Other: TTabSheet
      Caption = 'Other'
      ImageIndex = 7
      object SFCDisableHelp: TGroupBox
        Left = 264
        Top = 8
        Width = 249
        Height = 73
        Cursor = crHelp
        Caption = 'SfcDisable'
        TabOrder = 0
        OnClick = SFCDisableHelpClick
        object Panel23: TPanel
          Left = 8
          Top = 16
          Width = 161
          Height = 49
          BorderStyle = bsSingle
          TabOrder = 0
          object RadioButton41: TRadioButton
            Left = 8
            Top = 8
            Width = 113
            Height = 17
            Caption = 'Enable'
            Checked = True
            TabOrder = 0
            TabStop = True
          end
          object RadioButton42: TRadioButton
            Left = 8
            Top = 24
            Width = 113
            Height = 17
            Caption = 'Disable'
            TabOrder = 1
          end
        end
        object SFCDisableSave: TBitBtn
          Left = 176
          Top = 16
          Width = 65
          Height = 25
          Caption = 'Save'
          TabOrder = 1
          OnClick = BitBtn45Click
          Kind = bkOK
        end
        object SFCDisableRefresh: TBitBtn
          Left = 176
          Top = 40
          Width = 65
          Height = 25
          Caption = 'Refresh'
          TabOrder = 2
          OnClick = SFCDisableRefreshClick
          Kind = bkRetry
        end
      end
      object CrashOnCtrlScrollHelp: TGroupBox
        Left = 8
        Top = 8
        Width = 249
        Height = 73
        Cursor = crHelp
        Caption = 'CrashOnCtrlScroll'
        TabOrder = 1
        OnClick = CrashOnCtrlScrollHelpClick
        object Panel17: TPanel
          Left = 8
          Top = 16
          Width = 161
          Height = 49
          BorderStyle = bsSingle
          TabOrder = 0
          object RadioButton27: TRadioButton
            Left = 8
            Top = 8
            Width = 145
            Height = 17
            Caption = 'Enable'
            Checked = True
            TabOrder = 0
            TabStop = True
          end
          object RadioButton28: TRadioButton
            Left = 8
            Top = 24
            Width = 137
            Height = 17
            Caption = 'Disable'
            TabOrder = 1
          end
        end
        object CrashOnCtrlScrollSave: TBitBtn
          Left = 176
          Top = 16
          Width = 65
          Height = 25
          Caption = 'Save'
          TabOrder = 1
          OnClick = CrashOnCtrlScrollSaveClick
          Kind = bkOK
        end
        object CrashOnCtrlScrollRefresh: TBitBtn
          Left = 176
          Top = 40
          Width = 65
          Height = 25
          Caption = 'Refresh'
          TabOrder = 2
          OnClick = CrashOnCtrlScrollRefreshClick
          Kind = bkRetry
        end
      end
    end
  end
  object MainMenu1: TMainMenu
    Left = 504
    object Help1: TMenuItem
      Caption = 'Help'
      object Aboutprogram1: TMenuItem
        Caption = 'About program...'
        OnClick = Aboutprogram1Click
      end
      object About1: TMenuItem
        Caption = 'About...'
        OnClick = About1Click
      end
    end
  end
end
