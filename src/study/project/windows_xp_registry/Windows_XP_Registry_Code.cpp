//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Windows_XP_Registry_Code.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TWindows_XP_Registry_Form *Windows_XP_Registry_Form;
//---------------------------------------------------------------------------
__fastcall TWindows_XP_Registry_Form::TWindows_XP_Registry_Form(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
/*/
REG_BINARY    - �������� ���
REG_DWORD     - ����� ���
REG_EXPAND_SZ - ��������� ���
REG_MULTI_SZ  - ������ �����
REG_SZ        - ������ ������������� �����
/*/
/*/-----------------------------------------------------------------------/*/
/*/���������� � �������/*/
void __fastcall TWindows_XP_Registry_Form :: SaveValue(TElement _Element)
   {
      bool Ok = false;
      TRegistry &RegKey = *new TRegistry();
      //-----------------------------------
         RegKey.RootKey = _Element.Root;
         RegKey.Access = KEY_ALL_ACCESS;
         try
            {
               Ok = RegKey.OpenKey(_Element.Key, false);
            }
         catch (...)
            {
               MessageDlg("������ � ������ ���������� �������!!!", mtError, TMsgDlgButtons() << mbOK, 0);
               RegKey.CloseKey();
               delete &RegKey;
               return;
            }
         if (Ok)
            {
               //�������� �������� ������
               if (_Element.Value == "DeleteKey")
                  {
                     RegKey.DeleteKey(_Element.Data);
                  }
               else
               //�������� �������� ������
               if (_Element.Value == "CreateKey")
                  {
                     RegKey.CreateKey(_Element.Data);
                  }
               else
               {
               try
                  {
                     //���������� ��������� ��������
                     switch (_Element.Type)
                        {
                           //�������� ���
                           case (Binary): {
                                             try
                                                {
                                                   RegKey.WriteBool(_Element.Data, StrToInt(_Element.Value));
                                                }
                                             catch (...)
                                                {
                                                   MessageDlg("������ � �������� ��������!!!", mtError, TMsgDlgButtons() << mbOK, 0);
                                                }
                                          }
                                             break;
                           //����� ���
                           case (Dword) : {
                                             try
                                                {
                                                   RegKey.WriteInteger(_Element.Data, StrToInt(_Element.Value));
                                                }
                                             catch (...)
                                                {
                                                   MessageDlg("������ � �������� ��������!!!", mtError, TMsgDlgButtons() << mbOK, 0);
                                                }
                                          }
                                             break;
                           //��������� ���
                           default      : {
                                             try
                                                {
                                                   RegKey.WriteString(_Element.Data, _Element.Value);
                                                }
                                             catch (...)
                                                {
                                                   MessageDlg("������ � �������� ��������!!!", mtError, TMsgDlgButtons() << mbOK, 0);
                                                }
                                          }
                                          break;
                        }
                  }
               catch (...)
                  {
                     MessageDlg("������ � ������ ���������� �������!!!", mtError, TMsgDlgButtons() << mbOK, 0);
                     RegKey.CloseKey();
                     delete &RegKey;
                     return;
                  }
               }
               }
      //-------------
      RegKey.CloseKey();
      delete &RegKey;
   }
/*/----------------------------------------------------------------------/*/
/*/������� �������� �� �������/*/
void __fastcall TWindows_XP_Registry_Form :: RefreshValue(TElement &_Element)
   {
      bool Ok = false;
      TRegistry &RegKey = *new TRegistry();
      //-----------------------------------
         RegKey.RootKey = _Element.Root;
         //���� �����������
         if (!RegKey.KeyExists(_Element.Key))
            {
                     _Element.Key = "Miss";
                     RegKey.CloseKey();
                     delete &RegKey;
                     return;
            }
         //--------------------------------
         //�������� �����
         try
            {
               Ok = RegKey.OpenKey(_Element.Key, false);
            }
         catch (...)
            {
               MessageDlg("������ � ������ ���������� �������!!!", mtError, TMsgDlgButtons() << mbOK, 0);
               RegKey.CloseKey();
               delete &RegKey;
               return;
            }
         if (Ok)
            {
               //������� ������ �����������
               if (!RegKey.ValueExists(_Element.Data))
                  {
                     _Element.Data = "Miss";
                     RegKey.CloseKey();
                     delete &RegKey;
                     return;
                  }
               try
                  {
                     switch (_Element.Type)
                        {
                           //������� ��������� ��������
                           case (Binary):
                                          {
                                             try
                                                {
                                                   _Element.Value = IntToStr(RegKey.ReadBool(_Element.Data));
                                                }
                                             catch (...)
                                                {
                                                   MessageDlg("������ � ���� ������ �������� �����", mtError, TMsgDlgButtons() << mbOK, 0);
                                                }
                                          }
                                          break;
                           //������� ������ ��������
                           case (Dword) : {
                                             try
                                                {
                                                   _Element.Value = IntToStr(RegKey.ReadInteger(_Element.Data));
                                                }
                                             catch (...)
                                                {
                                                   MessageDlg("������ � ���� ������ �������� �����", mtError, TMsgDlgButtons() << mbOK, 0);
                                                }
                                          }
                                          break;
                           //������� ������
                           default      : {
                                             try
                                                {
                                                   _Element.Value = RegKey.ReadString(_Element.Data);
                                                }
                                             catch (...)
                                                {
                                                   MessageDlg("������ � ���� ������ �������� �����", mtError, TMsgDlgButtons() << mbOK, 0);
                                                }
                                          }
                                          break;
                        }
                  }
               catch (...)
                  {
                     Application->MessageBoxA("������ � ������ ���������� �������", "��������", MB_OK);
                     RegKey.CloseKey();
                     delete &RegKey;
                     return;
                  }
            }
      delete &RegKey;
   }
//---------------------------------------------------------------------------
//DisablePagingExecutive
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::DisablePagingExecutiveSaveClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Memory Management";
   Element.Data = "DisablePagingExecutive";
   Element.Type = Dword;
   if (RadioButton13->Checked) {Element.Value = "1";}
   if (RadioButton14->Checked) {Element.Value = "0";}
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::DisablePagingExecutiveRefreshClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Memory Management";
   Element.Data = "DisablePagingExecutive";
   Element.Type = Dword;
   RefreshValue(Element);
   if (Element.Value == "1") {RadioButton13->Checked = true;}
   if ((Element.Value == "0") || (Element.Data == "Miss")) {RadioButton14->Checked = true;}
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::DisablePagingExecutiveHelpClick(TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "������ � �������. \n\n��������� ������� ��������� �������� � ����, ��� ���� ������� � �������� �� ����� ����������� � ���� �������� (swap). ������� � ��������� ����� ������� ����������� �� �������� ������������. �������� ������� ������������ ������ ��� ������� ������ ��������� ������ (>256 �����).\n\n����: HKEY_LOCAL_MACHINE \\ System \\ CurrentControlSet \\ Control \\ Session Manager \\ Memory Management. \n��������: DisablePagingExecutive (REG_DWORD). \n��������: '0' - ���������� (Disable), '1' - ��������� (Enable). \n\n��������: ���� ������� �� �����������, ������� � ���������� ������ � �������� ����� ���� ��������!!!";
   ParametrForm->Caption = "DisablePagingExecutive";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//LargeSystemCache
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::LargeSystemCacheSaveClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Memory Management";
   Element.Data = "LargeSystemCache";
   Element.Type = Dword;
   if (RadioButton15->Checked) {Element.Value = "1";}
   if (RadioButton16->Checked) {Element.Value = "0";}
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::LargeSystemCacheRefreshClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Memory Management";
   Element.Data = "LargeSystemCache";
   Element.Type = Dword;
   RefreshValue(Element);
   if (Element.Value == "1") {RadioButton15->Checked = true;}
   if ((Element.Value == "0") || (Element.Value == "Miss")) {RadioButton16->Checked = true;}
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::LargeSystemCacheHelpClick(TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "������ � �������. \n\n��������� ������� ��������� (�� ��������� �������� �� ������� Windows.NET) �������� � ����, ��� ������������ ������� ����� ������������ ��� ����������� ������ ��� ���� ��������� ������, �� ����������� 4 �������� ���������������� ��� ��������� ����.\n\n����: HKEY_LOCAL_MACHINE \\ System \\ CurrentControlSet \\ Control \\ Session Manager \\ Memory Management. \n��������: LargeSystemCache (REG_DWORD). \n��������: '1' - ��������� ����� (Enable), '0' - ����������, ������������� ��� �������� ������������ ���������� �� ������ ������������ ��������� ����������� ������, �������� Microsoft SQL Server ��� IIS (Disable). \n\n��������: ���� ������� �� �����������, ������� � ���������� ������ � �������� ����� ���� ��������!!!";
   ParametrForm->Caption = "LargeSystemCache";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//IOPageLockLimit
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::IOPageLockLimitSaveClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Memory Management";
   Element.Data = "IOPageLockLimit";
   Element.Type = Dword;
   if (Edit3->Text == "") {Edit3->Text = "0";}
   try
      {
         StrToInt(Edit3->Text);
      }
   catch (EConvertError &)
      {
         MessageDlg("�������� �� ���������!!!", mtInformation, TMsgDlgButtons() << mbYes, 0);
         return;
      }
   Element.Value = Edit3->Text;
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::IOPageLockLimitRefreshClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Memory Management";
   Element.Data = "IOPageLockLimit";
   Element.Type = Dword;
   RefreshValue(Element);
   Edit3->Text = Element.Value;
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::IOPageLockLimitHelpClick(TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "������ � �������. \n\nIOPageLockLimit - ������������ �������, ���� ��, �������, �� ������� ������������ ������ �� ����� ������. ����� ������� ���������� �������� �����/������ ��� ������� ���������� ������������ ������ ��� ��� �������� ���������. �� ����� ��������� �������, ���� �� ����� ���������� ����������� ����� 128 ����� ������. ���� ������ ������, �� �� �������� ���������� ������������������ ��� ��������� ��������� � �������� �� 8 �� 16 �����.\n\n����: HKEY_LOCAL_MACHINE \\ System \\ CurrentControlSet \\ Control \\ Session Manager \\ Memory Management. \n��������: IOPageLockLimit (REG_DWORD). \n��������: �� ��������� ������������ 512 �����. ��� ������� ������� �������� � ������, ������� �������� ��������� ����� �������� ��� ���� �� 1024. ������������� ��������� �������� � �������� ���������.";
   ParametrForm->Caption = "IOPageLockLimit";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//ClearPageFileAtShutdown
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::ClearPageFileAtShutdownSaveClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Memory Management";
   Element.Data = "ClearPageFileAtShutdown";
   Element.Type = Dword;
   if (RadioButton17->Checked) {Element.Value = "1";}
   if (RadioButton18->Checked) {Element.Value = "0";}
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::ClearPageFileAtShutdownRefreshClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Memory Management";
   Element.Data = "ClearPageFileAtShutdown";
   Element.Type = Dword;
   RefreshValue(Element);
   if (Element.Value == "1") {RadioButton17->Checked = true;}
   if ((Element.Value == "0") || (Element.Value == "Miss")) {RadioButton18->Checked = true;}
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::ClearPageFileAtShutdownHelpClick(TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "������ � ������ ��������. \n\n��������� ������� ����� �������� � ����, ��� ������� ��� ������ ��������� ��������� (pagefile.sys) ���� ������, �.�. �������. �� �� ����� �������� � ������� Local Security Policy � Administrative Tools, ������ Local Policies, Security Options, ���� Shutdown: Clear virtual memory pagefile when system shuts down.\n\n����: HKEY_LOCAL_MACHINE \\ SYSTEM \\ CurrentControlSet \\ Control \\ Session Manager \\ Memory Management.\n��������: ClearPageFileAtShutdown. \n��������: '1' - �������� ������� (Enable), 0 - ��������� ������� (Disable).\n\n��������: ��������� ������� ��������� �������� � ��������������� �������� ����� ����������� ����������.";
   ParametrForm->Caption = "ClearPageFileAtShutdown";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//NoLowDiskSpaceChecks
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::NoLowDiskSpaceChecksSaveClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_CURRENT_USER;
   Element.Key =  "\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer";
   Element.Data = "NoLowDiskSpaceChecks";
   Element.Type = Dword;
   if (RadioButton5->Checked) {Element.Value = "1";}
   if (RadioButton6->Checked) {Element.Value = "0";}
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::NoLowDiskSpaceChecksRefreshClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_CURRENT_USER;
   Element.Key =  "\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer";
   Element.Data = "NoLowDiskSpaceChecks";
   Element.Type = Dword;
   RefreshValue(Element);
   if (Element.Value == "1") {RadioButton5->Checked = true;}
   if ((Element.Value == "0") || (Element.Data == "Miss")) {RadioButton6->Checked = true;}
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::NoLowDiskSpaceChecksHelpClick(
      TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "������ � ����������� ���������. \n\n���������� ������� ����� - ��������� ��������� � ��� ��� ������������ ���������� ����� �� �����. \n\n����: HKEY_CURRENT_USER \\ Software \\ Microsoft \\ Windows \\ CurrentVersion \\ Policies \\ Expl�rer. \n��������: NoLowDiskSpaceChecks (REG_DWORD). \n��������: '1' - ���������� ��������� (Enable). '0' - ��������� ��������� (Disable).";
   ParametrForm->Caption = "NoLowDiskSpaceChecks";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//Show or Hide Shared Documents folder
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::SharedDocumentsSaveClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\MyComputer\\NameSpace\\DelegateFolders";
   Element.Data = "{59031a47-3f72-44a7-89c5-5595fe6b30ee}";
   Element.Type = Sz;
   if (RadioButton7->Checked) {Element.Value = "DeleteKey";}
   if (RadioButton8->Checked) {Element.Value = "CreateKey";}
   SaveValue(Element);
}
//---------------------------------------------------------------------------
/*/Shared Documents - Refresh/*/
void __fastcall TWindows_XP_Registry_Form::SharedDocumentsRefreshClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\MyComputer\\NameSpace\\DelegateFolders\\{59031a47-3f72-44a7-89c5-5595fe6b30ee}";
   Element.Data = " ";
   Element.Type = Sz;
   RefreshValue(Element);
   if (Element.Key == "Miss") {RadioButton7->Checked = true;}
   if (Element.Key != "Miss") {RadioButton8->Checked = true;}
}
//---------------------------------------------------------------------------
//Shared Documents - Help
void __fastcall TWindows_XP_Registry_Form::SharedDocumentsHelpClick(TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "������ � ����������� ���������. \n\n���������� ��� �������� ����� Shared Documents (��� ���������) � '��� ���������'. \n\n����:  HKEY_LOCAL_MACHINE \\ SOFTWARE \\ Microsoft \\ Windows \\ CurrentVersion \\ Explorer \\ MyComputer \\ NameSpace \\ DelegateFolders.\n��� ������� ����� (Hide Folder) ���������� ������� ������� ������, ���� Reg_SZ - {59031a47-3f72-44a7-89c5-5595fe6b30ee}, ��� ������� ���� �� ������� ��� ����������� (Show Folder).";
   ParametrForm->Caption = "Show or Hide Shared Documents folder";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//NoDesktop
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::NoDesktopSaveClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_CURRENT_USER;
   Element.Key =  "\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer";
   Element.Data = "NoDesktop";
   Element.Type = Dword;
   if (RadioButton55->Checked) {Element.Value = "1";}
   if (RadioButton56->Checked) {Element.Value = "0";}
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::NoDesktopRefreshClick(
      TObject *Sender)
{
TElement Element;
   Element.Root = HKEY_CURRENT_USER;
   Element.Key =  "\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer";
   Element.Data = "NoDesktop";
   Element.Type = Dword;
   RefreshValue(Element);
   if (Element.Value == "1") {RadioButton55->Checked = true;}
   if ((Element.Value == "0") || (Element.Data == "Miss")) {RadioButton56->Checked = true;}
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::NoDesktopHelpClick(TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "������ � ����������� ���������. \n\n��������� ������� ��������� ��������� ������ ��� ������ � �������� �����.\n\n����: HKEY_CURRENT_USER \\ Software \\ Microsoft \\ Windows \\ CurrentVersion \\ Policies \\ Explorer.\n��������: NoDesktop (REG_DWORD). \n�������� 1 - ������ (Enable), 0 - ���������� (Disable).";
   ParametrForm->Caption = "NoDesktop";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//FullScreen
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::FullScreenSaveClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_CURRENT_USER;
   Element.Key =  "\\Console";
   Element.Data = "FullScreen";
   Element.Type = Dword;
   if (RadioButton33->Checked) {Element.Value = "1";}
   if (RadioButton34->Checked) {Element.Value = "0";}
   SaveValue(Element);

   Element.Key =  "\\Software\\Microsoft\\Internet Explorer\\Main";
   Element.Data = "FullScreen";
   Element.Type = Sz;
   if (RadioButton33->Checked) {Element.Value = "yes";}
   if (RadioButton34->Checked) {Element.Value = "no";}
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::FullScreenRefreshClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_CURRENT_USER;
   Element.Key =  "\\Console";
   Element.Data = "FullScreen";
   Element.Type = Dword;
   RefreshValue(Element);
   if (Element.Value == "0") {RadioButton34->Checked = true; return;}

   Element.Key =  "\\Software\\Microsoft\\Internet Explorer\\Main";
   Element.Data = "FullScreen";
   Element.Type = Sz;
   RefreshValue(Element);
   if (Element.Value == "yes") {RadioButton33->Checked = true;}
   if (Element.Value == "no") {RadioButton34->Checked = true;}
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::FullScreenHelpClick(TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "������ � ����������� ���������. \n\n��������� ������� ��������� �������� � ����, ��� Internet Explorer ����� ����������� � ������������� ������.\n\n����: HKEY_CURRENT_USER \\ Console.\n��������: FullScreen (REG_DWORD). ��������: '1' - �������� ����� (Enable), '0' - ��������� (Disable). \n\n� �����.\n����: HKEY_CURRENT_USER \\ Software \\ Microsoft \\ Internet Explorer \\ Main. \n�������� : FullScreen(REG_SZ). ��������: 'Yes' ��� ��������� (Enable) ��� 'No' ��� ���������� (Disable)";
   ParametrForm->Caption = "FullScreen";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//AutoRun
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::AutoRunSaveClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SYSTEM\\CurrentControlSet\\Services\\Cdrom";
   Element.Data = "AutoRun";
   Element.Type = Dword;
   if (RadioButton1->Checked) {Element.Value = "1";}
   if (RadioButton2->Checked) {Element.Value = "0";}
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::AutoRunRefreshClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SYSTEM\\CurrentControlSet\\Services\\Cdrom";
   Element.Data = "AutoRun";
   Element.Type = Dword;
   RefreshValue(Element);
   if ((Element.Value == "0") || (Element.Value == "Miss")) {RadioButton2->Checked = true;}
   if (Element.Value == "1") {RadioButton1->Checked = true;}
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::AutoRunHelpClick(TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "������ � ������������. \n\n������ �������� �������� �� ���������� �������-������, ������� ���������� �����, ����� ����������� ����� ����. \n\n����: HKEY_LOCAL_MACHINE \\ SYSTEM \\ CurrentControlSet \\ Services \\ CDRom. \n��p����p: Autorun (REG_DWORD). \n��������: '1' - ���������� ������� (Enable), '0' - �������� (Disable)";
   ParametrForm->Caption = "AutoRun";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//PowerdownAfterShutdown
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::PowerdownAfterShutdownSaveClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon";
   Element.Data = "PowerdownAfterShutdown";
   Element.Type = Sz;
   if (RadioButton39->Checked) {Element.Value = "1";}
   if (RadioButton40->Checked) {Element.Value = "0";}
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::PowerdownAfterShutdownRefreshClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon";
   Element.Data = "PowerdownAfterShutdown";
   Element.Type = Sz;
   RefreshValue(Element);
   if (Element.Value == "1") {RadioButton39->Checked = true;}
   if (Element.Value == "0") {RadioButton40->Checked = true;}
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::PowerdownAfterShutdownHelpClick(
      TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "������ � ������������. \n\n������ �������� ������������ ��� ����, ����� ������ � ��� ������ ����������� ����. ����� ���� ������� ���������, ����� Windows ����� � ����� ACPI. \n\n����: HKEY_LOCAL_MACHINE \\ SOFTWARE \\ Microsoft \\ Windows NT \\ CurrentVersion \\ Winlogon. \n��p����p: PowerdownAfterShutdown (REG_SZ). \n��������: '1' - ��������� ������� (Enable), '0' - �� ��������� (Disable). \n\n��������: ���� ��������� ����� ��������� �� ����������� ���������� ���������� ��������!!!";
   ParametrForm->Caption = "PowerdownAfterShutdown";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//EnableUDMA66
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::EnableUDMA66SaveClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SYSTEM\\CurrentControlSet\\Control\\Class\\{4D36E96A-E325-11CE-BFC1-08002BE10318}\\0000";
   Element.Data = "EnableUDMA66";
   Element.Type = Dword;
   if (RadioButton37->Checked) {Element.Value = "1";}
   if (RadioButton38->Checked) {Element.Value = "0";}
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::EnableUDMA66RefreshClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SYSTEM\\CurrentControlSet\\Control\\Class\\{4D36E96A-E325-11CE-BFC1-08002BE10318}\\0000";
   Element.Data = "EnableUDMA66";
   Element.Type = Dword;
   RefreshValue(Element);
   if (Element.Value == "1") {RadioButton37->Checked = true;}
   if ((Element.Value == "0") || Element.Data == "Miss") {RadioButton38->Checked = true;}
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::EnableUDMA66HelpClick(
      TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "������ � ������������. \n\n������ �������� �������� ����� Ultra DMA 66. ���� �� ������ ��������� � Intel chipset, ������� ������������ UDMA66, �� ������ ��� ��� ��������, ��� ����� UDMA66 ������������ �� ��������� �� ����������� Windows 2000. \n\n����: HKEY_LOCAL_MACHINE \\ SYSTEM \\ CurrentControlSet \\ Control \\ Class \\ {4D36E96A-E325-11CE-BFC1-08002BE10318} \\ 0000. \n��������: EnableUDMA66 (REG_DWORD). \n��������: '1' - �������� Ultra DMA 66 (Enable), '0' - ��������� (Disable).";
   ParametrForm->Caption = "EnableUDMA66";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//Hidden
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::SaveHiddenClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SYSTEM\\CurrentControlSet\\Services\\lanmanserver\\parameters";
   Element.Data = "Hidden";
   Element.Type = Dword;
   if (RadioButton43->Checked) {Element.Value = "1";}
   if (RadioButton44->Checked) {Element.Value = "0";}
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::RefreshHiddenClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SYSTEM\\CurrentControlSet\\Services\\lanmanserver\\parameters";
   Element.Data = "Hidden";
   Element.Type = Dword;
   RefreshValue(Element);
   if (Element.Value == "1") {RadioButton43->Checked = true;}
   if ((Element.Data == "Miss") || (Element.Value == "0")) {RadioButton44->Checked = true;}
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::HiddenHelpClick(TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "������ � �����.\n\n������ �������� ��������� ������ ��������� � '������� ���������'. ���������� �������, ��� ������ ������ ��������� ����� (����� ����) ������, ��� ��� ��������� ������ ������� � ��������. �� �� ������� �� ���� �����, ���� ������� ��� ��� �������. \n\n����: HKEY_LOCAL_MACHINE \\ SYSTEM \\ CurrentControlSet \\ Services \\ lanmanserver \\ parameters. \n��������: Hidden (REG_DWORD). \n��������: '1' - ������ ��������� (Enable), '0' - ���������� (Disable).";
   ParametrForm->Caption = "Hidden";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//AutoShareWks
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::AutoShareWksSaveClick(
      TObject *Sender)
{
  TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SYSTEM\\CurrentControlSet\\Services\\lanmanserver\\parameters";
   Element.Data = "AutoShareWks";
   Element.Type = Dword;
   if (RadioButton45->Checked) {Element.Value = "1";}
   if (RadioButton46->Checked) {Element.Value = "0";}
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::AutoShareWksRefreshClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SYSTEM\\CurrentControlSet\\Services\\lanmanserver\\parameters";
   Element.Data = "AutoShareWks";
   Element.Type = Dword;
   RefreshValue(Element);
   if ((Element.Value == "1") || (Element.Data == "Miss")) {RadioButton45->Checked = true;}
   if (Element.Value == "0") {RadioButton46->Checked = true;}
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::AutoShareWksHelpClick(
      TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "������ � �����. \n\n������ �������� ��������� ��������� / ��������� ������� ������� �$, D$, ADMIN$ (��� ������� �������). Windows �� ���������, ��� ������ �������, ��������� ������������� ������� �������. \n\n����: HKEY_LOCAL_MACHINE \\ SYSTEM \\ CurrentControlSet \\ Services \\ lanmanserver \\ parameters. \n��������: AutoShareWks (REG_DWORD). \n��������: '1' - ��������� ������������ (Enable), '0' - ��������� (Disable). \n\n��������: ����� ����, ��� �� ��������� � ������� ��� ������� (Disable), ���������� �������� ������� ������� ������� ����� �������������� � ��� ����� �� ��������� ����� ������������.";
   ParametrForm->Caption = "AutoShareWks";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//AutoShareServer
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::AutoShareServerSaveClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SYSTEM\\CurrentControlSet\\Services\\lanmanserver\\parameters";
   Element.Data = "AutoShareServer";
   Element.Type = Dword;
   if (RadioButton47->Checked) {Element.Value = "1";}
   if (RadioButton48->Checked) {Element.Value = "0";}
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::AutoShareServerRefreshClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SYSTEM\\CurrentControlSet\\Services\\lanmanserver\\parameters";
   Element.Data = "AutoShareServer";
   Element.Type = Dword;
   RefreshValue(Element);
   if ((Element.Value == "1") || (Element.Data == "Miss")) {RadioButton47->Checked = true;}
   if (Element.Value == "0") {RadioButton48->Checked = true;}
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::AutoShareServerHelpClick(
      TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "������ � �����. \n\n������ �������� ��������� ��������� / ��������� ������� ������� �$, D$, ADMIN$ (��� c������). Windows �� ���������, ��� ������ �������, ��������� ������������� ������� �������. \n\n����: HKEY_LOCAL_MACHINE \\ SYSTEM \\ CurrentControlSet \\ Services \\ lanmanserver \\ parameters. \n��������: AutoShareServer (REG_DWORD). \n��������: '1' - ��������� (Enable), '0' - ��������� (Disable).";
   ParametrForm->Caption = "AutoShareServer";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//WaitToKillServiceTimeout
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::BitBtn5Click(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SYSTEM\\CurrentControlSet\\Control";
   Element.Data = "WaitToKillServiceTimeout";
   Element.Type = Sz;
   if (Edit1->Text == "") {Edit1->Text = "0";}
   try
      {
         StrToInt(Edit1->Text);
      }
   catch (EConvertError &)
      {
         MessageDlg("�������� �� ���������!!!", mtInformation, TMsgDlgButtons() << mbYes, 0);
         return;
      }
   Element.Value = Edit1->Text;
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::BitBtn6Click(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SYSTEM\\CurrentControlSet\\Control";
   Element.Data = "WaitToKillServiceTimeout";
   Element.Type = Sz;
   RefreshValue(Element);
   Edit1->Text = Element.Value;
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::WaitToKillServiceTimeOutHelpClick(
      TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "��������� ������ Windows. \n\n�������� ����� ����� ���������� ����� � �������������, ������� ������� ��������, ����� ��� �������� ��������� ����������. �� ��������� �������� 20000, ��� �������� 20 ������, ������� ������������ � �������, �������������� �������� �� ���������� ����������, ���� �����-�� ������ ��� ��������� �� �����������. �������� ��� �� 5000, � �� ����� ������� �������. �� �� ������� ������� ����, ������ ��� � ���� ������ �� ������ ����������� � ���������, ����� �� ����� ������� ��������� ������, ��� ��� ����� �������� ��������� ���� ������. ��� ���� �����. \n\n����: HKEY_LOCAL_MACHINE \\ SYSTEM \\ CurrentControlSet \\ Control. \n��������: WaitToKillServiceTimeout (REG_SZ). \n��������: � �������������.";
   ParametrForm->Caption = "WaitToKillServiceTimeout";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//MenuShowDelay
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::MenuShowDelaySaveClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_CURRENT_USER;
   Element.Key =  "\\Control Panel\\Desktop";
   Element.Data = "MenuShowDelay";
   Element.Type = Sz;
   if (Edit2->Text == "") {Edit2->Text = "0";}
   try
      {
         StrToInt(Edit2->Text);
      }
   catch (EConvertError &)
      {
         MessageDlg("�������� �� ���������!!!", mtInformation, TMsgDlgButtons() << mbYes, 0);
         return;
      }
   Element.Value = Edit2->Text;
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::MenuShowDelayRefreshClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_CURRENT_USER;
   Element.Key =  "\\Control Panel\\Desktop";
   Element.Data = "MenuShowDelay";
   Element.Type = Sz;
   RefreshValue(Element);
   Edit2->Text = Element.Value;
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::MenuShowDelayHelpClick(
      TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "��������� ������ Windows. \n\n�������� ����� ����� ���������� ����� �������� � �������������, ����� ������� ���������� �������������� ����. ���������� ��� � '0'.\n\n����: HKEY_CURRENT_USER \\ Control Panel \\ Desktop. \n��������: MenuShowDelay (REG_SZ). \n��������: � �������������.";
   ParametrForm->Caption = "MenuShowDelay";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//MinAnimate
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::MinAnimateSaveClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_CURRENT_USER;
   Element.Key =  "\\Control Panel\\Desktop\\WindowMetrics";
   Element.Data = "MinAnimate";
   Element.Type = Sz;
   if (RadioButton11->Checked) {Element.Value = "1";}
   if (RadioButton12->Checked) {Element.Value = "0";}
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::MinAnimateRefreshClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_CURRENT_USER;
   Element.Key =  "\\Control Panel\\Desktop\\WindowMetrics";
   Element.Data = "MinAnimate";
   Element.Type = Sz;
   RefreshValue(Element);
   if ((Element.Value == "1") || (Element.Data == "Miss")) {RadioButton11->Checked = true;}
   if (Element.Value == "0") {RadioButton12->Checked = true;}
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::MinAnimateHelpClick(
      TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "��������� ������ Windows. \n\n�������� ��� ������������ (�����������) ����. \n\n����: HKEY_CURRENT_USER \\ Control Panel \\ Desktop \\ WindowMetrics. \n��������: MinAnimate (REG_SZ). \n��������: '0' - ��������� �������� (Disable), '1' - �������� (Enable).";
   ParametrForm->Caption = "MinAnimate";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//Dr. Watson Auto Debuger
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::AutoDebugerSaveClick(TObject *Sender)
{
   TElement Element;
  Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\AeDebug";
   Element.Data = "Auto";
   Element.Type = Sz;
   if (RadioButton3->Checked) {Element.Value = "0";}
   if (RadioButton4->Checked) {Element.Value = "1";}
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::AutoDebugerRefreshClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\AeDebug";
   Element.Data = "Auto";
   Element.Type = Sz;
   RefreshValue(Element);
   if ((Element.Value == "0") || (Element.Value == "Miss")) {RadioButton3->Checked = true;}
   if (Element.Value == "1") {RadioButton4->Checked = true;}
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::AutoDebugerHelpClick(TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "��������� ������ Windows. \n\n�������������� ������ �������� (Debug). \n\n����: HKEY_LOCAL_MACHINE \\ SOFTWARE \\ Microsoft \\ Windows NT \\ CurrentVersion \\ AeDebug. \n��������: Auto (REG_SZ). \n��������: '1' - ��������� ����������� (Enable), '0' - ���������� ��������������� ������� (Disable). \n\n��������: ��� �� ������ �������� ������� ��������� ������������ ����������, �� � �������� �������� ������ �������� � ���������� ���� �������� ����������� ������. \n� ������ ����������� ����������� (Disable): ���� ��������� �����-���� ���� � ������ ����������, �� ������� ��������� ���� ������� ����������, ���� �������� ��� ��������� ��� �������. ���� ������� ������, �� ���������� Dr.Watson (��� ������ �������), � ������� ���-����. ���� �� �������, ��� ����� ����������� ��� �� � ����, �� ������ ������� ����� AeDebug �� �������.";
   ParametrForm->Caption = "Dr. Watson Auto Debuger";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//AlwaysUnloadDll
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::AlwaysUnloadDllSaveClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer";
   Element.Data = "AlwaysUnloadDll";
   Element.Type = Dword;
   if (RadioButton51->Checked) {Element.Value = "1";}
   if (RadioButton52->Checked) {Element.Value = "0";}
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::AlwaysUnloadDllRefreshClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer";
   Element.Data = "AlwaysUnloadDll";
   Element.Type = Dword;
   RefreshValue(Element);
   if (Element.Value == "1") {RadioButton51->Checked = true;}
   if ((Element.Value == "0") || (Element.Data == "Miss")) {RadioButton52->Checked = true;}
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::AlwaysUnloadDllHelpClick(
      TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "��������� ������ Windows. \n\n�������������� �������� �������������� ���������. ����� ������ ������������ ��������� DLL, ���� ���� ����������, ������� �� ������������, ��� �������. ��� �������� ��� ��������� ����������� ��������� � ���� �����������, �� ��� ��������� ������ ������� � �����. ��� ��������� ������ � 32-������ �����������! \n\n����: HKEY_LOCAL_MACHINE \\ SOFTWARE \\ Microsoft \\ Windows \\ CurrentVersion \\ Explorer.\n��������: AlwaysUnloadDll (REG_DWORD).\n��������: '1' - �������� �������� ��������� (Enable), '0' - ��������� (Disable). \n\n�����������: \n��-������, ����� �������� ���������� ����� ����� ��������� ��� �� �����, ��� � � ������ ���. \n��-������, 16-������ (������) ���������� ����� �������� ��������� �� �������. �� �� �� ������ �� �����������, �����?";
   ParametrForm->Caption = "AlwaysUnloadDll";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//NtfsDisableLastAccessUpdate
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::NtfsDisableLastAccessUpdateSaveClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SYSTEM\\CurrentControlSet\\Control\\FileSystem";
   Element.Data = "NtfsDisableLastAccessUpdate";
   Element.Type = Dword;
   if (RadioButton9->Checked) {Element.Value = "1";}
   if (RadioButton10->Checked) {Element.Value = "0";}
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::NtfsDisableLastAccessUpdateRefreshClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SYSTEM\\CurrentControlSet\\Control\\FileSystem";
   Element.Data = "NtfsDisableLastAccessUpdate";
   Element.Type = Dword;
   RefreshValue(Element);
   if (Element.Value == "1") {RadioButton9->Checked = true;}
   if ((Element.Value == "0") || (Element.Data == "Miss")) {RadioButton10->Checked = true;}
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::GroupBox5Click(TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "��������� ������ Windows. \n\n����� ����������� ����������, �� NTFS ��������� ����� ���������� ������� � ������. ���� ������ ����� � �� ���� ���� ����� ��������, �� ��� �������� �������� ����� �������. ������ ��� ������� ����� ���������. \n\n����: HKEY_LOCAL_MACHINE \\ SYSTEM \\ CurrentControlSet \\ Control \\ FileSystem. \n��������: NtfsDisableLastAccessUpdate (REG_DWORD). \n��������: '1' - o�������� ���������� (Enable), '0' - �������� ���������� (Disable).";
   ParametrForm->Caption = "NtfsDisableLastAccessUpdate";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//SFCDisable
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::BitBtn45Click(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon";
   Element.Data = "SFCDisable";
   Element.Type = Dword;
   if (RadioButton41->Checked) {Element.Value = IntToStr(0xffffff9d);}
   if (RadioButton42->Checked) {Element.Value = "0";}
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::SFCDisableRefreshClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon";
   Element.Data = "SFCDisable";
   Element.Type = Dword;
   RefreshValue(Element);
   if (Element.Value == "-99") {RadioButton41->Checked = true;}
   if ((Element.Value == "0") || (Element.Value == "Miss")) {RadioButton42->Checked = true;}
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::SFCDisableHelpClick(
      TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "�������������� �����������. \n\n������ �������� ��������� ��������� ��������� SFC (System Files Protection). \n\n����: HKEY_LOCAL_MACHINE \\ SOFTWARE \\ Microsoft \\ Windows NT \\ CurrentVersion \\ Winlogon. \n��������: SFCDisable (REG_DWORD). \n��������: 'ffffff9d' - ��������� SFC (Enable), '0' - �������� (Disable). \n\n��������: ������� ������� ��� ������ ���, �� �������� �������� �� ���� ��� ����������� Dll-hell, ������� �� �������� ����� ������������������ ������� � ���������� ������ �������������� ���������� � �������, ��������� ������� ��������� ��������� �� ������������� ������ �� ��������� ��������������.";
   ParametrForm->Caption = "SFCDisable";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//CrashOnCtrlScroll
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::CrashOnCtrlScrollSaveClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SYSTEM\\CurrentControlSet\\Services\\i8042prt\\Parameters";
   Element.Data = "CrashOnCtrlScroll";
   Element.Type = Dword;
   if (RadioButton27->Checked) {Element.Value = "1";}
   if (RadioButton28->Checked) {Element.Value = "0";}
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::CrashOnCtrlScrollRefreshClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SYSTEM\\CurrentControlSet\\Services\\i8042prt\\Parameters";
   Element.Data = "CrashOnCtrlScroll";
   Element.Type = Dword;
   RefreshValue(Element);
   if (Element.Value == "1") {RadioButton27->Checked = true;}
   if ((Element.Value == "0") || (Element.Data == "Miss")) {RadioButton28->Checked = true;}
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::CrashOnCtrlScrollHelpClick(
      TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "�������������� �����������. \n\n������ �������� ��������� �������� ������ ������� ������� ��������� ���� � ���������� �� '����� ����� ������' (BSOD). ��� ����� ������� ������ ������� <Ctrl> �, ��������� �� � ���� ���������, ������ ������� ������� <Scroll Lock>. \n\n����: HKEY_LOCAL_MACHINE \\ SYSTEM \\ CurrentControlSet \\ Services \\ i8042prt \\ Parameters. \n��������: CrashOnCtrlScroll (REG_DWORD). \n��������: '1' - �������� ������� (Enable), '0' - ��������� (Disable). \n\n����������: ���� �� ������ ������� ����� �����, � �� ������������ ����������, �� �������� ����� ����� � ����������� ������������ � ������ ��������� �������.";
   ParametrForm->Caption = "CrashOnCtrlScroll";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//ScreenSaveActive
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::ScreenSaveActiveSaveClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_USERS;
   Element.Key =  "\\.DEFAULT\\Control Panel\\Desktop";
   Element.Data = "ScreenSaveActive";
   Element.Type = Sz;
   if (RadioButton19->Checked) {Element.Value = "0";}
   if (RadioButton20->Checked) {Element.Value = "1";}
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::ScreenSaveActiveRefreshClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_USERS;
   Element.Key =  "\\.DEFAULT\\Control Panel\\Desktop";
   Element.Data = "ScreenSaveActive";
   Element.Type = Sz;
   RefreshValue(Element);
   if ((Element.Value == "0") || (Element.Value == "Miss")) {RadioButton19->Checked = true;}
   if (Element.Value == "1") {RadioButton20->Checked = true;}
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::ScreenSaveActiveHelpClick(
      TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "������������. \n\nWindows ����� �������� �� ��������� ����������� ����� ����������, ���������� login.scr, ������� �����������, ���� ���� ������� ����������� ����� ���������� �� ���� �������. ��� ����� ������������ ���� ������, ��������� ��� ����� ��������� ���������� ������������ �������� login.scr ������ ���������� � ��������(���������) ��� � ���������� ������������. \n\n����: HKEY_USERS \\ .DEFAULT \\ Control Panel \\ Desktop. \n��������: ScreenSaveActive (REG_SZ). \n��������: '0' - �������� ��������� (Disable), '1'  - �������� �������� (Enabled).";
   ParametrForm->Caption = "ScreenSaveActive";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//DontDisplayLastUserName
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::DontDisplayLastUserNameSaveClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\policies\\system";
   Element.Data = "DontDisplayLastUserName";
   Element.Type = Dword;
   if (RadioButton21->Checked) {Element.Value = "1";}
   if (RadioButton22->Checked) {Element.Value = "0";}
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::DontDisplayLastUserNameRefreshClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\policies\\system";
   Element.Data = "DontDisplayLastUserName";
   Element.Type = Dword;
   RefreshValue(Element);
   if (Element.Value == "1") {RadioButton21->Checked = true;}
   if ((Element.Value == "0") || (Element.Data == "Miss")) {RadioButton22->Checked = true;}
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::DontDisplayLastUserNameHelpClick(
      TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "������������. \n\n������ �������� ��������� ��������� ����� ����� ����������� ����������� � �������� ������������. \n\n����: HKEY_LOCAL_MACHINE \\ SOFTWARE \\ Microsoft \\ Windows \\ CurrentVersion \\ policies \\ system.\n��������: DontDisplayLastUserName (REG_DWORD). \n��������: '1' - �� ���������� (Enable), '0' - ���������� (Disable).";
   ParametrForm->Caption = "DontDisplayLastUserName";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//ClearRecentDocsOnExit
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::ClearRecentDocsOnExitSaveClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_CURRENT_USER;
   Element.Key =  "\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer";
   Element.Data = "ClearRecentDocsOnExit";
   Element.Type = Dword;
   if (RadioButton24->Checked) {Element.Value = "0";}
   if (RadioButton23->Checked) {Element.Value = "1";}
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::ClearRecentDocsOnExitRefreshClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_CURRENT_USER;
   Element.Key =  "\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer";
   Element.Data = "ClearRecentDocsOnExit";
   Element.Type = Dword;
   RefreshValue(Element);
   if (Element.Value == "1") {RadioButton23->Checked = true;}
   if ((Element.Value == "0") || (Element.Data == "Miss")) {RadioButton24->Checked = true;}
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::GroupBox18Click(TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "������ � ����������� ���������. \n\n������ �������� ��������� ������� ������ ������� ������������� ���������� � ���� '����' ��� ���������� Windows. \n\n����: HKEY_CURRENT_USER \\ Software \\ Microsoft \\ Windows \\ CurrentVersion \\ Policies \\ Explorer. \n��������: ClearRecentDocsOnExit (REG_DWORD). \n��������: '1' - ��� ������ ������� ������ (Enable), '0' - ����� ��� ������� (Disable).";
   ParametrForm->Caption = "ClearRecentDocsOnExit";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//restrictanonymous
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::restrictanonymousSaveClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SYSTEM\\CurrentControlSet\\Control\\Lsa";
   Element.Data = "restrictanonymous";
   Element.Type = Dword;
   if (RadioButton25->Checked) {Element.Value = "1";}
   if (RadioButton26->Checked) {Element.Value = "0";}
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::restrictanonymousRefreshClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SYSTEM\\CurrentControlSet\\Control\\Lsa";
   Element.Data = "restrictanonymous";
   Element.Type = Dword;
   RefreshValue(Element);
   if (Element.Value == "1") {RadioButton25->Checked = true;}
   if ((Element.Value == "0") || (Element.Value == "Miss")) {RadioButton26->Checked = true;}
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::restrictanonymousHelpClick(TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "������������. \n\nNull-Session - ��� ����� ����������� ����, ������� ��������� ������� ������������, ���� �� ���� ������� ������� � ������� �� ���� �������, �������� ��� ���� � ��������� (share - �����������, ��������� ��� ������ �����������) �����������, �� ��������� �� ����� ��������� �������������, � �����, ���� ����� � ���. \n\n����: HKEY_LOCAL_MACHINE \\ SYSTEM \\ CurrentControlSet \\ Control \\ Lsa. \n��������: restrictanonymous (REG_DWORD). \n��������: '1' - ������� '����' (Enable), '0' - '�������' (Disable).";
   ParametrForm->Caption = "restrictanonymous";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//NtfsDisable8dot3NameCreation
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::NtfsDisable8dot3NameCreationSaveClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SYSTEM\\CurrentControlSet\\Control\\FileSystem";
   Element.Data = "NtfsDisable8dot3NameCreation";
   Element.Type = Dword;
   if (RadioButton35->Checked) {Element.Value = "1";}
   if (RadioButton36->Checked) {Element.Value = "0";}
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::NtfsDisable8dot3NameCreationRefreshClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SYSTEM\\CurrentControlSet\\Control\\FileSystem";
   Element.Data = "NtfsDisable8dot3NameCreation";
   Element.Type = Dword;
   RefreshValue(Element);
   if (Element.Value == "1") {RadioButton35->Checked = true;}
   if ((Element.Value == "0") || (Element.Value == "Miss")) {RadioButton36->Checked = true;}
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::NtfsDisable8dot3NameCreationHelpClick(TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "��������� ������ Windows. \n\n���������� �������� ���� ������ � ������� 8.3 (NTFS). ���� ���� ������������� ������ ����� NTFS, ���������� �� �������� ����������� � ��-��� ���� ������ � ������� 8.3. ���������� ����� �������� ����� ��������� ������������� ������ � �������� NTFS, � ������� ����������� ������ ������� ������� �����. \n\n����: HKEY_LOCAL_MACHINE \\ SYSTEM \\ CurrentControlSet \\ Control \\ FileSystem. \n��������: NtfsDisable8dot3NameCreation (REG_DWORD). \n��������: '1' - �� ��������� ����� ������� 8.3 (Enable), '0' - ��������� (Disable). \n\n��������������: ��������� 16 ��������� ��������������� ��������� ����� ����� �������� ��� ��������� ����� ���������. �� ������ ��� ������ �������� �������� 8.3 ���� ������ � ������� ���������, ��� ������������ ����� ��������� �� � ������� LFN, �� ���� 'c:\\progra~1\\applic~1'.";
   ParametrForm->Caption = "NtfsDisable8dot3NameCreation";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//NtfsMftZoneReservation
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::NtfsMftZoneReservationSaveClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SYSTEM\\CurrentControlSet\\Control\\FileSystem";
   Element.Data = "NtfsMftZoneReservation";
   Element.Type = Dword;
   if (RadioButton29->Checked) {Element.Value = "1";}
   if (RadioButton30->Checked) {Element.Value = "2";}
   if (RadioButton31->Checked) {Element.Value = "3";}
   if (RadioButton32->Checked) {Element.Value = "4";}
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::NtfsMftZoneReservationRefreshClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SYSTEM\\CurrentControlSet\\Control\\FileSystem";
   Element.Data = "NtfsMftZoneReservation";
   Element.Type = Dword;
   RefreshValue(Element);
   if ((Element.Value == "1") || (Element.Data == "Miss")) {RadioButton29->Checked = true;}
   if (Element.Value == "2") {RadioButton30->Checked = true;}
   if (Element.Value == "3") {RadioButton31->Checked = true;}
   if (Element.Value == "4") {RadioButton32->Checked = true;}
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::NtfsMftZoneReservationHelpClick(
      TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "��������� ������ Windows. \n\n������ �������� ��������� ��������������� ����������� ������������ ��� MFT (������ FAT-�������). \n\n����: HKEY_LOCAL_MACHINE \\ SYSTEM \\ CurrentControlSet \\ Control \\ FileSystem. \n��������: NtfsMftZoneReservation (REG_DWORD). \n��������: \n���� � ��� �� NTFS ���� ������������ ������� ������, ������� ������ �������, ���������� ��� �������� ������ '1' (�� ���������). �� ������ ���������� �������� '2' ��� '3' ��� ���������� ���������� ������. \n'4' (������������), ���� �� ���� ����� ���������� ������� ���������� ������. \n\n��������: ������ � ����, ��� ��������� ��������� ������ ��� 2, ���������� ������� ������������� ������� ������� ����� ����� ��� MFT.";
   ParametrForm->Caption = "NtfsMftZoneReservation";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//Recycle Bin
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::RecycleBinSaveClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Desktop\\NameSpace";
   Element.Data = "{645FF040-5081-101B-9F08-00AA002F954E}";
   Element.Type = Sz;
   if (RadioButton57->Checked) {Element.Value = "DeleteKey";}
   if (RadioButton58->Checked) {Element.Value = "CreateKey";}
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::RecycleBinRefreshClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Desktop\\NameSpace\\{645FF040-5081-101B-9F08-00AA002F954E}";
   Element.Data = "Recycle Bin";
   Element.Type = Sz;
   RefreshValue(Element);
   if (Element.Key == "Miss") {RadioButton57->Checked = true;}
   if (Element.Key != "Miss") {RadioButton58->Checked = true;}
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::RecycleBinHelpClick(TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "������ � ����������� ���������. \n\n������ �������� ��������� ������ / ���������� ������ '�������' (Recycle Bin) �� ������� �����. \n\n����: HKEY_LOCAL_MACHINE \\ SOFTWARE \\ Microsoft \\ Windows \\ CurrentVersion \\ Explorer \\ Desktop \\ NameSpace. \n��������: {645FF040-5081-101B-9F08-00AA002F954E} (REG_SZ). \n�������� ��������� �������� � ������� �������, �������� � �����������. \n\n����������: ������������ �� �����������, ���������� �������� ������� ����.";
   ParametrForm->Caption = "Recycle Bin Hide / Show";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//RecycleBinRename
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::RecycleBinRenameSaveClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_CURRENT_USER;
   Element.Key =  "\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\CLSID\\{645FF040-5081-101B-9F08-00AA002F954E}";
   Element.Data = "";
   Element.Type = Sz;
   Element.Value = Edit4->Text;
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::RecycleBinRenameRefreshClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_CURRENT_USER;
   Element.Key =  "\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\CLSID\\{645FF040-5081-101B-9F08-00AA002F954E}";
   Element.Data = "";
   Element.Type = Sz;
   RefreshValue(Element);
   if (Element.Value == "") {Element.Value = "�������";}
   Edit4->Text = Element.Value;
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::RecycleBinRenameHelpClick(
      TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "������ � ����������� ���������. \n\n���� ������� ������� '�������' ��� 'Recycle Bin' ����� �������� �, ������� ����. \n\n����: HKEY_CURRENT_USER \\ Software \\ Microsoft \\ Windows \\ CurrentVersion \\ Explorer \\ CLSID \\ {645FF040-5081-101B-9F08-00AA002F954E}. \n��������: '�� ���������' (REG_SZ). \n��������: �������� ������� '�������'. \n\n����������: ������������ �� �����������, ���������� �������� ������� ����.";
   ParametrForm->Caption = "Recycle Bin Rename";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//CoolBits
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::CoolBitsSaveClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\Software\\NVIDIA Corporation\\Global\\NVTweak";
   Element.Data = "CoolBits";
   Element.Type = Dword;
   if (RadioButton53->Checked) {Element.Value = "3";}
   if (RadioButton54->Checked) {Element.Value = "0";}
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::CoolBitsRefreshClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\Software\\NVIDIA Corporation\\Global\\NVTweak";
   Element.Data = "CoolBits";
   Element.Type = Dword;
   RefreshValue(Element);
   if (Element.Value == "3") {RadioButton53->Checked = true;}
   if ((Element.Value == "0") || (Element.Data == "Miss")) {RadioButton54->Checked = true;}
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::CoolBitsHelpClick(
      TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "������ � ������������. \n\n������ �������� ������������ ��� ��������� ������� (Overclock). ���� � ��� ���������� NVidia, �� ������� ������ ��������, � ��� � ���������� ���������� �������� �������� '��������� �������� �������'. \n\n����: HKEY_LOCAL_MACHINE \\ Software \\ NVIDIA Corporation \\ Global \\ NVTweak. \n��������: CoolBits (REG_DWORD). \n��������: 3 - ����������� ������� (Enable), 0 - ������ �������� (Disable).";
   ParametrForm->Caption = "CoolBits";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//EnablePrefetcher
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::EnablePrefetcherSaveClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Memory Management\\PrefetchParameters";
   Element.Data = "EnablePrefetcher";
   Element.Type = Dword;
   if (RadioButton59->Checked) {Element.Value = "0";}
   if (RadioButton60->Checked) {Element.Value = "1";}
   if (RadioButton61->Checked) {Element.Value = "2";}
   if (RadioButton62->Checked) {Element.Value = "3";}
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::EnablePrefetcherRefreshClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Memory Management\\PrefetchParameters";
   Element.Data = "EnablePrefetcher";
   Element.Type = Dword;
   RefreshValue(Element);
   if (Element.Data == "Miss") {RadioButton59->Checked = false; RadioButton60->Checked = false; RadioButton61->Checked = false; RadioButton62->Checked = false;}
   if (Element.Value == "0") {RadioButton59->Checked = true;}
   if (Element.Value == "1") {RadioButton60->Checked = true;}
   if (Element.Value == "2") {RadioButton61->Checked = true;}
   if (Element.Value == "3") {RadioButton62->Checked = true;}
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::EnablePrefetcherHelpClick(
      TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "��������� ������ Windows. \n\n��� ��������� ��������� �������� ������ �������� � ��������� ������ � ����������� �� �������������� ������������. \n\n����: HKEY_LOCAL_MACHINE \\ SYSTEM \\ CurrentControlSet \\ Control \\ Session Manager \\ Memory Management \\ PrefetchParameters. \n��������: EnablePrefetcher (REG_DWORD). \n��������: \n0 � ��������� (������������� ��� ���������� �����������); \n1 � ������������� ��� ����������� � ��� �� 256�� (������ ���������). \n2 � ��� ��� � ���� �� ����� �� 512�� � ����� (��������� � ��������� ����������); \n3 � ��� ��� ���������� ��� �����-����� ������ ������ + ������� ��� 512��, ���� ��� LargeSystemCache=1 ��������� �������� � �� 256�� ���. \n���������� EnablePrefetcher=3. \n\n� ������� �� ������ ��������� ���������� � EnablePrefetcher = 5 ��� ��������� ����� EnableSuperFetch = 1 � ����� �� ������� ����� ����� �� ��� ���. � � Windows XP SP2 EnablePrefetcher = 5 � ����� ���� ������ � ����������� �������."
   "\n��������� Prefetch ����� ����� ������������ ��� ������� ��������� ��������, ���������� � ��������� ������ ��������� �������� ������ /Prefetch:1 � � ������� ��������� ������� ���� ���������, ��, � ���������, �� �� ����� ����������� ��� ��������. �� ������� �������� FireFox � ��������� ������: \n�C:\\Program Files\\Mozilla Firefox\\firefox.exe� ������ ��... \n�C:\\Program Files\\Mozilla Firefox\\firefox.exe� /prefetch:1";
   ParametrForm->Caption = "EnablePrefetcher";
   ParametrForm->ShowModal();
}
//--------------------------------------------------------------------------
//Beep
//--------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::BeepSaveClick(TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_CURRENT_USER;
   Element.Key =  "\\Control Panel\\Sound";
   Element.Data = "Beep";
   Element.Type = Sz;
   if (RadioButton63->Checked) {Element.Value = "yes";}
   if (RadioButton64->Checked) {Element.Value = "no";}
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::BeepRefreshClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_CURRENT_USER;
   Element.Key =  "\\Control Panel\\Sound";
   Element.Data = "Beep";
   Element.Type = Sz;
   RefreshValue(Element);
   if ((Element.Value == "yes") || (Element.Value == "Miss")) {RadioButton63->Checked = true;}
   if (Element.Value == "no") {RadioButton64->Checked = true;}
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::BeepHelpClick(TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "������ � ������������. \n\n������ �������� ������� ������ Beep. \n\n����: HKEY_CURRENT_USER \\ Control Panel \\ Sound. \n��������: Beep (REG_SZ). \n��������: 'yes' - ������ ������� (Enable), 'no' - ������ �������� (Disable)";
   ParametrForm->Caption = "Beep";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//DisableTaskMgr
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::DisableTaskMgrSaveClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_CURRENT_USER;
   Element.Key =  "\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies";
   Element.Data = "System";
   Element.Type = Dword;
   if (RadioButton65->Checked)
      {
         Element.Value = "CreateKey";
         SaveValue(Element);
      }
   Element.Key =  "\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System";
   Element.Data = "DisableTaskMgr";
   if (RadioButton65->Checked) {Element.Value = "1";}
   if (RadioButton66->Checked) {Element.Value = "0";}
   SaveValue(Element);
}
//---------------------------------------------------------------------------

void __fastcall TWindows_XP_Registry_Form::DisableTaskMgrRefreshClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_CURRENT_USER;
   Element.Key =  "\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System";
   Element.Data = "DisableTaskMgr";
   Element.Type = Dword;
   RefreshValue(Element);
   if (Element.Value == "1") {RadioButton65->Checked = true;}
   if ((Element.Value == "0") || (Element.Data == "Miss") || (Element.Key == "Miss")) {RadioButton66->Checked = true;}
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::DisableTaskMgrHelpClick(
      TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "������������. \n\n�������� \\ ��������� TaskManager (��������� �����). \n\n����: HKEY_CURRENT_USER \\ Software \\ Microsoft \\ Windows \\ CurrentVersion \\ Policies \\ System. \n��������: DisableTaskMgr (REG_DWORD). \n��������: '1' - ��������� ��������� ����� (Enable), '0' - �������� ��������� ����� (Disable).";
   ParametrForm->Caption = "DisableTaskMgr";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//PaintDesktopVersion
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::PaintDesktopVersionSaveClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_CURRENT_USER;
   Element.Key =  "\\Control Panel\\Desktop";
   Element.Data = "PaintDesktopVersion";
   Element.Type = Dword;
   if (RadioButton67->Checked) {Element.Value = "1";}
   if (RadioButton68->Checked) {Element.Value = "0";}
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::PaintDesktopVersionRefreshClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_CURRENT_USER;
   Element.Key =  "\\Control Panel\\Desktop";
   Element.Data = "PaintDesktopVersion";
   Element.Type = Dword;
   RefreshValue(Element);
   if (Element.Value == "1") {RadioButton67->Checked = true;}
   if ((Element.Value == "0") || (Element.Data == "Miss")) {RadioButton68->Checked = true;}
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::PaintDesktopVersionHelpClick(
      TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "������ � ����������� ���������. \n\n������ �������� ��������� ������� ����� ������ Windows � ������ ������ ���� ���� �������� �����. \n\n����: HKEY_CURRENT_USER \\ Control Panel \\ Desktop. \n��������: PaintDesktopVersion (REG_DWORD). \n��������: '1' - ����� ������� (Enable), '0' - ������� �� ����� (Disable). \n\n����������: ��������� ������������.";
   ParametrForm->Caption = "PaintDesktopVersion";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//Protection Mode
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::ProtectionModeSaveClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SYSTEM\\CurrentControlSet\\Control\\Session Manager";
   Element.Data = "ProtectionMode";
   Element.Type = Dword;
   if (RadioButton69->Checked) {Element.Value = "1";}
   if (RadioButton70->Checked) {Element.Value = "0";}
   SaveValue(Element);
}
//---------------------------------------------------------------------------

void __fastcall TWindows_XP_Registry_Form::ProtectionModeRefreshClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SYSTEM\\CurrentControlSet\\Control\\Session Manager";
   Element.Data = "ProtectionMode";
   Element.Type = Dword;
   RefreshValue(Element);
   if (Element.Value == "1") {RadioButton69->Checked = true;}
   if (Element.Value == "0") {RadioButton70->Checked = true;}
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::ProtectionModeHelpClick(
      TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "������������. \n\n����������� ����������� ����� � ����������� ��������� DLL, �, ��� ���������, ��������� ���� ��������������. \n\n����: HKEY_LOCAL_MACHINE \\ SYSTEM \\ CurrentControlSet \\ Control \\ Session Manager. \n��������: ProtectionMode (REG_DWORD). \n��������: '1' - ��������� ������ (Enable), '0' - ���������� (Disable).";
   ParametrForm->Caption = "ProtectionMode";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//NoViewContextMenu
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::NoViewContextMenuSaveClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_CURRENT_USER;
   Element.Key =  "\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer";
   Element.Data = "NoViewContextMenu";
   Element.Type = Dword;
   if (RadioButton71->Checked) {Element.Value = "1";}
   if (RadioButton72->Checked) {Element.Value = "0";}
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::NoViewContextMenuRefreshClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_CURRENT_USER;
   Element.Key =  "\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer";
   Element.Data = "NoViewContextMenu";
   Element.Type = Dword;
   RefreshValue(Element);
   if (Element.Value == "1") {RadioButton71->Checked = true;}
   if ((Element.Value == "0") || (Element.Value == "Miss")) {RadioButton72->Checked = true;}
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::NoViewContextMenuHelpClick(
      TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "������ � ����������� ���������. \n\n������ �������� ��������� ������������� ����� ������������ ����. \n\n����: HKEY_CURRENT_USER \\ Software \\ Microsoft \\ Windows \\ CurrentVersion \\ Policies \\ Explorer. \n��������: NoViewContextMenu (REG_DWORD). \n��������: '1' - ����������� ���� ��������� (Enable), '0' - �������� (Disable).";
   ParametrForm->Caption = "NoViewContextMenu";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//DisableRegistryTools
//---------------------------------------------------------------------------

void __fastcall TWindows_XP_Registry_Form::DisableRegistryToolsSaveClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_CURRENT_USER;
   Element.Key =  "\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies";
   Element.Data = "System";
   Element.Type = Dword;
   if (RadioButton73->Checked)
      {
         Element.Value = "CreateKey";
         SaveValue(Element);
      }
   Element.Key =  "\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System";
   Element.Data = "DisableRegistryTools";
   if (RadioButton73->Checked) {Element.Value = "1";}
   if (RadioButton74->Checked) {Element.Value = "0";}
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::DisableRegistryToolsRefreshClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_CURRENT_USER;
   Element.Key =  "\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System";
   Element.Data = "DisableRegistryTools";
   Element.Type = Dword;
   RefreshValue(Element);
   if (Element.Value == "1") {RadioButton73->Checked = true;}
   if ((Element.Value == "0") || (Element.Data == "Miss") || (Element.Key == "Miss")) {RadioButton74->Checked = true;}
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::DisableRegistryToolsHelpClick(
      TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "������������. \n\n�������� \ ��������� ����������� ������ ��������� ������� (RegEdit.exe). \n\n����: HKEY_CURRENT_USER \\ Software \\ Microsoft \\ Windows \\ CurrentVersion \\ Policies \\ System. \n��������: DisableRegistryTools (DWORD). \n��������: '1' - ��������� ������ � RegEdit.exe (Enable), '0' - ��������� ������ (Disable).";
   ParametrForm->Caption = "DisableRegistryTools";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//InitialKeyboardIndicators
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::InitialKeyboardIndicatorsSaveClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_USERS;
   Element.Key =  "\\.DEFAULT\\Control Panel\\Keyboard";
   Element.Data = "InitialKeyboardIndicators";
   Element.Type = Sz;
   if (RadioButton75->Checked) {Element.Value = "2";}
   if (RadioButton76->Checked) {Element.Value = "0";}
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::InitialKeyboardIndicatorsRefreshClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_USERS;
   Element.Key =  "\\.DEFAULT\\Control Panel\\Keyboard";
   Element.Data = "InitialKeyboardIndicators";
   Element.Type = Sz;
   RefreshValue(Element);
   if (Element.Value == "2") {RadioButton75->Checked = true;}
   if (Element.Value == "0") {RadioButton76->Checked = true;}
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::InitialKeyboardIndicatorsHelpClick(
      TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "������ � ������������. \n\n������ �������� ��������� ��������� ������� 'Num Lock' ��� ������� Windows, � ���� ����� ������. \n\n����: HKEY_USERS \\ .DEFAULT \\ Control Panel \\ Keyboard. \n��������: InitialKeyboardIndicators (REG_SZ). \n��������: '2' - Num Lock ����������� (Enable), '0' - Num Lock �� ������� (Disable). \n\n��������: ��������� ������� ��������� �������� � ����, ��� Num Lock ����� ���������� � ���� �������������, ���������� �� ������ �������, ���� ���� ��� ������������� ��� ��������� � ������� � �����: \nHKEY_CURRENT_USER \\ Control Panel \\ Keyboard, \n����: InitialKeyboardIndicators.";
   ParametrForm->Caption = "InitialKeyboardIndicators";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//IPEnableRouter
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::IPEnableRouterSaveClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters";
   Element.Data = "IPEnableRouter";
   Element.Type = Dword;
   if (RadioButton77->Checked) {Element.Value = "1";}
   if (RadioButton78->Checked) {Element.Value = "0";}
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::IPEnableRouterRefreshClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters";
   Element.Data = "IPEnableRouter";
   Element.Type = Dword;
   RefreshValue(Element);
   if (Element.Value == "1") {RadioButton77->Checked = true;}
   if ((Element.Data == "Miss") || (Element.Value == "0")) {RadioButton78->Checked = true;}
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::IPEnableRouterHelpClick(
      TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "������ � �����.\n\n���� �� ����� ��������� ����� ����� ����� ������� ����� � ��� ���������� � �����, ���������� �������� ������ ��������. ������ �������� ��������� �������� ������������� Windows. \n\n����: HKEY_LOCAL_MACHINE \\ SYSTEM \\ CurrentControlSet \\ Services \\ Tcpip \\ Parameters. \n��������: IPEnableRouter (REG_DWORD). \n��������: '1' - �������� ������������� (Enable), '0' - ��������� (Disable). \n\n����������: ���������� �������, ��� ��� ������ ������������� Windows ������ ���� �������� ������ 'Routing and Remote access' (������������� � ��������� ������).";
   ParametrForm->Caption = "IPEnableRouter";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//DeadGWDetectDefault
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::DeadGWDetectDefaultSaveClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters";
   Element.Data = "DeadGWDetectDefault";
   Element.Type = Dword;
   if (RadioButton49->Checked) {Element.Value = "1";}
   if (RadioButton50->Checked) {Element.Value = "0";}
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::DeadGWDetectDefaultRefreshClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters";
   Element.Data = "DeadGWDetectDefault";
   Element.Type = Dword;
   RefreshValue(Element);
   if ((Element.Value == "1") || (Element.Value == "Miss")) {RadioButton49->Checked = true;}
   if (Element.Value == "0") {RadioButton50->Checked = true;}
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::DeadGWDetectDefaultHelpClick(
      TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "������ � �����.\n\n���� �������� ������ ��������, �� ����� ������� ���������� ����� ����������� �������� �� ������� �������������� �� ���� �� �������. ���� ������ �������� �������� �� ���� ������ ������ �� �����.\n\n����: HKEY_LOCAL_MACHINE \\ SYSTEM \\ CurrentControlSet \\ Services \\ Tcpip \\ Parameters. \n��������: DeadGWDetectDefault (REG_DWORD). \n��������: '1' - �������� �������� (Enable), '0' - �������� ��������� (Disable).";
   ParametrForm->Caption = "DeadGWDetectDefault";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//EnableICMPRedirect
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::EnableICMPRedirectSaveClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters";
   Element.Data = "EnableICMPRedirect";
   Element.Type = Dword;
   if (RadioButton79->Checked) {Element.Value = "1";}
   if (RadioButton80->Checked) {Element.Value = "0";}
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::EnableICMPRedirectRefreshClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters";
   Element.Data = "EnableICMPRedirect";
   Element.Type = Dword;
   RefreshValue(Element);
   if (Element.Value == "1") {RadioButton79->Checked = true;}
   if (Element.Value == "0") {RadioButton80->Checked = true;}
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::EnableICMPRedirectHelpClick(
      TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "������ � �����.\n\n������ �������� ����� ��������� / ��������� Windows �������� ������� ������������� � ����� �� ICMP �������� ������. \n\n����: HKEY_LOCAL_MACHINE \\ SYSTEM \\ CurrentControlSet \\ Services \\ Tcpip \\ Parameters. \n��������: EnableICMPRedirect (REG_DWORD). \n��������: '1' - ��������� ��������� �������, '0' - ���������.";
   ParametrForm->Caption = "EnableICMPRedirect";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//EnablePMTUDiscovery
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::EnablePMTUDiscoverySaveClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters";
   Element.Data = "EnablePMTUDiscovery";
   Element.Type = Dword;
   if (RadioButton81->Checked) {Element.Value = "1";}
   if (RadioButton82->Checked) {Element.Value = "0";}
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::EnablePMTUDiscoveryRefreshClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters";
   Element.Data = "EnablePMTUDiscovery";
   Element.Type = Dword;
   RefreshValue(Element);
   if ((Element.Value == "1") || (Element.Data == "Miss")) {RadioButton81->Checked = true;}
   if (Element.Value == "0") {RadioButton82->Checked = true;}
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::EnablePMTUDiscoveryHelpClick(
      TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "������ � �����.\n\n������ �������� ��������� / ��������� Windows ��������� MTU (����� ��������� ����� ������� ��� ����� ��������� � ����������� ����). \n\n����: HKEY_LOCAL_MACHINE \\ SYSTEM \\ CurrentControlSet \\ Services \\ Tcpip \\ Parameters. \n��������: EnablePMTUDiscovery (REG_DWORD). \n��������: '1' - ��������� ���������� �������, '0' - ���������.";
   ParametrForm->Caption = "EnablePMTUDiscovery";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//NoNameReleaseOnDemand
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::NoNameReleaseOnDemandSaveClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters";
   Element.Data = "NoNameReleaseOnDemand";
   Element.Type = Dword;
   if (RadioButton83->Checked) {Element.Value = "1";}
   if (RadioButton84->Checked) {Element.Value = "0";}
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::NoNameReleaseOnDemandRefreshClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_LOCAL_MACHINE;
   Element.Key =  "\\SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters";
   Element.Data = "NoNameReleaseOnDemand";
   Element.Type = Dword;
   RefreshValue(Element);
   if ((Element.Value == "0") || (Element.Data == "Miss")) {RadioButton84->Checked = true;}
   if (Element.Value == "1") {RadioButton83->Checked = true;}
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::NoNameReleaseOnDemandHelpClick(
      TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "������ � �����.\n\n������ �������� ��������� �������� ������ �� NetBIOS name-release ����. \n\n����: HKEY_LOCAL_MACHINE \\ SYSTEM \\ CurrentControlSet \\ Services \\ Tcpip \\ Parameters. \n��������: NoNameReleaseOnDemand (REG_DWORD). \n��������: '1' - �������� ������ (Enable), '0' - ��������� (Disable).";
   ParametrForm->Caption = "NoNameReleaseOnDemand";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//AutoEndTasks
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::AutoEndTasksSaveClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_CURRENT_USER;
   Element.Key =  "\\Control Panel\\Desktop";
   Element.Data = "AutoEndTasks";
   Element.Type = Sz;
   if (RadioButton87->Checked) {Element.Value = "1";}
   if (RadioButton88->Checked) {Element.Value = "0";}
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::AutoEndTasksRedreshClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_CURRENT_USER;
   Element.Key =  "\\Control Panel\\Desktop";
   Element.Data = "AutoEndTasks";
   Element.Type = Sz;
   RefreshValue(Element);
   if (Element.Value == "1") {RadioButton87->Checked = true;}
   if (Element.Value == "0") {RadioButton88->Checked = true;}
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::AutoEndTasksHelpClick(
      TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "��������� ������ Windows. \n\n��������� ������� ��������� �������� Windows ������ ��������� ��������� ������ ��� ������� ��������������. �������� ����� ������� Windows �������� ������ ������������ ���������� WaitToKillAppTimeout, � ��� �� ����� �������. \n\n����: HKEY_CURRENT_USER \\ Control Panel \\ Desktop. \n��������: AutoEndTasks (REG_SZ). \n��������: 1 - ��������� �������������� (Enable), 0 - ��������� (Disable).";
   ParametrForm->Caption = "AutoEndTasks";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//WaitToKillAppTimeout
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::WaitToKillAppTimeoutSaveClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_CURRENT_USER;
   Element.Key =  "\\Control Panel\\Desktop";
   Element.Data = "WaitToKillAppTimeout";
   Element.Type = Sz;
   if (Edit5->Text == "") {Edit5->Text = "0";}
   try
      {
         StrToInt(Edit5->Text);
      }
   catch (EConvertError &)
      {
         MessageDlg("�������� �� ���������!!!", mtInformation, TMsgDlgButtons() << mbYes, 0);
         return;
      }
   Element.Value = Edit5->Text;
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::WaitToKillAppTimeoutRefreshClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_CURRENT_USER;
   Element.Key =  "\\Control Panel\\Desktop";
   Element.Data = "WaitToKillAppTimeout";
   Element.Type = Sz;
   RefreshValue(Element);
   Edit5->Text = Element.Value;
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::WaitToKillAppTimeoutHelpClick(
      TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "��������� ������ Windows. \n\n��������� ������� ��������� �������� ����� � �������������, �� ��������� �������� Windows ����� ��������� �������� ����������. \n\n����: HKEY_CURRENT_USER \\ Control Panel \\ Desktop. \n��������: WaitToKillAppTimeout (REG_SZ). \n��������: � �������������. \n\n��������: ������� ��������, ���, ������������ ������� ����� �������� ��� WaitToKillAppTimeout, �� ������ �������� �������� � ���� �� ������� ������ �������� � �������������� ������������� ������.";
   ParametrForm->Caption = "WaitToKillAppTimeout";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//HungAppTimeout
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::HungAppTimeoutSaveClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_CURRENT_USER;
   Element.Key =  "\\Control Panel\\Desktop";
   Element.Data = "HungAppTimeout";
   Element.Type = Sz;
   if (Edit6->Text == "") {Edit6->Text = "0";}
   try
      {
         StrToInt(Edit6->Text);
      }
   catch (EConvertError &)
      {
         MessageDlg("�������� �� ���������!!!", mtInformation, TMsgDlgButtons() << mbYes, 0);
         return;
      }
   Element.Value = Edit6->Text;
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::HungAppTimeoutRefreshClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_CURRENT_USER;
   Element.Key =  "\\Control Panel\\Desktop";
   Element.Data = "HungAppTimeout";
   Element.Type = Sz;
   RefreshValue(Element);
   Edit6->Text = Element.Value;
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::HungAppTimeoutHelpClick(
      TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "��������� ������ Windows. \n\n��������� ������� ��������� �������� ����� � �������������, �� ��������� �������� Windows ����� ������� ������ ��������. \n\n����: HKEY_CURRENT_USER \\ Control Panel \\ Desktop. \n��������: HungAppTimeout (REG_SZ). \n��������: � �������������. \n\n��������: ������� ��������, ���, ������������ ������� ����� �������� ��� HungAppTimeout, �� ������ �������� �������� � ���� �� ������� ������ �������� � �������������� ������������� ������.";
   ParametrForm->Caption = "HungAppTimeout";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
//InitialKeyboardIndicators (User)
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::InitialKeyboardIndicatorsUserSaveClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_CURRENT_USER;
   Element.Key =  "\\Control Panel\\Keyboard";
   Element.Data = "InitialKeyboardIndicators";
   Element.Type = Sz;
   if (RadioButton89->Checked) {Element.Value = "2";}
   if (RadioButton90->Checked) {Element.Value = "0";}
   SaveValue(Element);
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::InitialKeyboardIndicatorsUserRefreshClick(
      TObject *Sender)
{
   TElement Element;
   Element.Root = HKEY_CURRENT_USER;
   Element.Key =  "\\Control Panel\\Keyboard";
   Element.Data = "InitialKeyboardIndicators";
   Element.Type = Sz;
   RefreshValue(Element);
   if (Element.Value == "2") {RadioButton89->Checked = true;}
   if (Element.Value == "0") {RadioButton90->Checked = true;}
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::InitialKeyboardIndicatorsUserHelpClick(
      TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "������ � ������������. \n\n������ �������� ��������� ��������� ������� 'Num Lock' ��� ������� ������ ���������� ��� ������� ������������ ������ ������. \n\n����: HKEY_CURRENT_USER \\ Control Panel \\ Keyboard. \n��������: InitialKeyboardIndicators (REG_SZ). \n��������: '2' - Num Lock ����������� (Enable), '0' - Num Lock �� ������� (Disable). \n\n��������: ���������� ������� Num Lock �������� ������ ��� ����������� ��������� InitialKeyboardIndicators � ����� HKEY_USERS (��� ���� �������������).";
   ParametrForm->Caption = "InitialKeyboardIndicators (User)";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::FormCreate(TObject *Sender)
{
   Splash = NULL;  
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::About1Click(TObject *Sender)
{
   Splash = new TSplash(NULL);
   Splash->ShowModal();
   delete Splash;
   Splash = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::Aboutprogram1Click(
      TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "� ��������� \n===================\n��������� 'Windows XP Registry' ������������� ��� ������ � �������� Windows XP. � ��� ������� ��������� ������� ���������� �������, ����������� �������������� ������ ������������ �������."
   "\n===================\n�������� ��������� \n===================\n��������� 'Windows XP Registry' �������� ����� ������� �����������. \n������� ���� ������� �� ��������: \nAcceleration (���������) - ������������� ��������c�� �� ��������� ������ Windows XP; \nExplorer (����������� ��������) - ���, ��������� � ���������� ����������������� ����������; \nHardware (������) - ��, ��������� � �������������, ������������� �� ����������; \nMemory (������) - ����������� ������ ������ � ����� ��������; \nNet (����) - ��, ��������� � ����� � ������� �������������; \nSecurity (�����������) - ������ ��� ��������� ���������������; \nOther (���������) - ���, ��� �� ��������� �� � ������ �� �����������������."
   "\n������ ������ �������: �� ����� � ��������� ����������, �������������� ���� (� ���� ������������� ��� �����), � ���������� ���������� ���� ���������� � ������. \n������ 'Save' - ������������� �������� �������� ���������, ������� ������� � �������������� ���� ������ �����; \n������ 'Refresh' - ������������� �������������� ���� � ���������, ������ �������� �������� ���������; \n������� - ����� ������� �������������� �������� � ����� ����� �����, ��������� �������� ��������� ������� �� ������ �������. ������� �������� � ���� ������ �������� ������� ��������� �� ������� �����. ����������� ������� �������, ����� ������ ����� �������������� ���� ���� ������, ����� �������� ��������� �������."
   "\n===================\n�������� ���������� \n===================\. \n����� �� ������ � ������������ ������ ���� ����������, ���������� � ������ ������, ��� ��� ��������� �� ��� ������ ���������� ��������� � ���� ��������� �� ��� 100, ��� ��� ����� �����������, �� � ������� ������� :). \n������ ������ 'Refresh' - ������, �� ������, �� ������� ��������, � ������, ���� �������� �� ������, ������ �� ����� ����������� �� �������."
   "\n===================\n�� ���� \n===================\. \n����� ��������, ��� ������ ��������� �������� ����� ������ �����, ����� �� ����������� ������� � ������ �������. ������� ������� �������� ��� ���� ��������� � �������, ���������� � �������� ������������� ������������ ��������. \n\n���� ���� ������������� ������ ������, �� ���� �� ����... ��������� ���������� � �������� ������� Windows XP (���, ������� ��� � ������ ������ ���������), ��� �� �����. ����� �������: 1) �������� ����������, ������ ��������� ��������� � � �������������. 2) �������� ���� � ��� ����, � ������� ��� ������������ � ������ �������. � ������: ����, ��������, ���, ��������, ��������. ����� ������� �� ���� ������. ���� ��������� ��� 20 - 30 ���������� ������ ������ ������ ���������.";
   ParametrForm->Caption = "About program";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------

