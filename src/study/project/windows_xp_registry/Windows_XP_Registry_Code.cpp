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
REG_BINARY    - бинарный тип
REG_DWORD     - целый тип
REG_EXPAND_SZ - строковый тип
REG_MULTI_SZ  - массив строк
REG_SZ        - строка фиксированной длины
/*/
/*/-----------------------------------------------------------------------/*/
/*/Сохранение в реестре/*/
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
               MessageDlg("Ошибка в работе системного реестра!!!", mtError, TMsgDlgButtons() << mbOK, 0);
               RegKey.CloseKey();
               delete &RegKey;
               return;
            }
         if (Ok)
            {
               //Удаление элемента данных
               if (_Element.Value == "DeleteKey")
                  {
                     RegKey.DeleteKey(_Element.Data);
                  }
               else
               //Создание элемента данных
               if (_Element.Value == "CreateKey")
                  {
                     RegKey.CreateKey(_Element.Data);
                  }
               else
               {
               try
                  {
                     //Присовение заданного значения
                     switch (_Element.Type)
                        {
                           //Бинарный тип
                           case (Binary): {
                                             try
                                                {
                                                   RegKey.WriteBool(_Element.Data, StrToInt(_Element.Value));
                                                }
                                             catch (...)
                                                {
                                                   MessageDlg("Ошибка в заданном значении!!!", mtError, TMsgDlgButtons() << mbOK, 0);
                                                }
                                          }
                                             break;
                           //Целый тип
                           case (Dword) : {
                                             try
                                                {
                                                   RegKey.WriteInteger(_Element.Data, StrToInt(_Element.Value));
                                                }
                                             catch (...)
                                                {
                                                   MessageDlg("Ошибка в заданном значении!!!", mtError, TMsgDlgButtons() << mbOK, 0);
                                                }
                                          }
                                             break;
                           //Строковый тип
                           default      : {
                                             try
                                                {
                                                   RegKey.WriteString(_Element.Data, _Element.Value);
                                                }
                                             catch (...)
                                                {
                                                   MessageDlg("Ошибка в заданном значении!!!", mtError, TMsgDlgButtons() << mbOK, 0);
                                                }
                                          }
                                          break;
                        }
                  }
               catch (...)
                  {
                     MessageDlg("Ошибка в работе системного реестра!!!", mtError, TMsgDlgButtons() << mbOK, 0);
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
/*/Возврат значения из реестра/*/
void __fastcall TWindows_XP_Registry_Form :: RefreshValue(TElement &_Element)
   {
      bool Ok = false;
      TRegistry &RegKey = *new TRegistry();
      //-----------------------------------
         RegKey.RootKey = _Element.Root;
         //Ключ отсутствует
         if (!RegKey.KeyExists(_Element.Key))
            {
                     _Element.Key = "Miss";
                     RegKey.CloseKey();
                     delete &RegKey;
                     return;
            }
         //--------------------------------
         //Открытие ключа
         try
            {
               Ok = RegKey.OpenKey(_Element.Key, false);
            }
         catch (...)
            {
               MessageDlg("Ошибка в работе системного реестра!!!", mtError, TMsgDlgButtons() << mbOK, 0);
               RegKey.CloseKey();
               delete &RegKey;
               return;
            }
         if (Ok)
            {
               //Элемент данных отсутствует
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
                           //Возврат бинарного значения
                           case (Binary):
                                          {
                                             try
                                                {
                                                   _Element.Value = IntToStr(RegKey.ReadBool(_Element.Data));
                                                }
                                             catch (...)
                                                {
                                                   MessageDlg("Ошибка в типе данных значения ключа", mtError, TMsgDlgButtons() << mbOK, 0);
                                                }
                                          }
                                          break;
                           //Возврат целого значения
                           case (Dword) : {
                                             try
                                                {
                                                   _Element.Value = IntToStr(RegKey.ReadInteger(_Element.Data));
                                                }
                                             catch (...)
                                                {
                                                   MessageDlg("Ошибка в типе данных значения ключа", mtError, TMsgDlgButtons() << mbOK, 0);
                                                }
                                          }
                                          break;
                           //Возврат строки
                           default      : {
                                             try
                                                {
                                                   _Element.Value = RegKey.ReadString(_Element.Data);
                                                }
                                             catch (...)
                                                {
                                                   MessageDlg("Ошибка в типе данных значения ключа", mtError, TMsgDlgButtons() << mbOK, 0);
                                                }
                                          }
                                          break;
                        }
                  }
               catch (...)
                  {
                     Application->MessageBoxA("Ошибка в работе системного реестра", "Внимание", MB_OK);
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
   "Работа с памятью. \n\nВключение данного параметра приведет к тому, что ядро системы и драйвера не будут скидываться в файл подкачки (swap). Система и программы будут быстрее реагировать на действия пользователя. Параметр следует использовать только при большом объеме доступной памяти (>256 Мбайт).\n\nПуть: HKEY_LOCAL_MACHINE \\ System \\ CurrentControlSet \\ Control \\ Session Manager \\ Memory Management. \nПараметр: DisablePagingExecutive (REG_DWORD). \nЗначение: '0' - выключение (Disable), '1' - включение (Enable). \n\nВнимание: Если система не загрузилась, зайдите в защищенном режиме и измените назад этот параметр!!!";
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
   "Работа с памятью. \n\nВключение данного параметра (по умолчанию включено на сервере Windows.NET) приведет к тому, что операционная система будет использовать всю оперативную память для кеша системных файлов, за исключением 4 мегабайт зарезервированых для дискового кеша.\n\nПуть: HKEY_LOCAL_MACHINE \\ System \\ CurrentControlSet \\ Control \\ Session Manager \\ Memory Management. \nПараметр: LargeSystemCache (REG_DWORD). \nЗначение: '1' - включение опции (Enable), '0' - выключение, рекомендуется для серверов использующих приложения со своими собственными функциями кэширования памяти, например Microsoft SQL Server или IIS (Disable). \n\nВнимание: Если система не загрузилась, зайдите в защищенном режиме и измените назад этот параметр!!!";
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
         MessageDlg("Значение не корректно!!!", mtInformation, TMsgDlgButtons() << mbYes, 0);
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
   "Работа с памятью. \n\nIOPageLockLimit - сомнительная функция, если вы, конечно, не желаете организовать сервер из своей машины. Опция ускорит выполнение операций ввода/вывода при большом количестве передаваемых файлов или при подобных нагрузках. Не имеет ощутимого эффекта, если на вашем компьютере установлено менее 128 Мбайт памяти. Если памяти больше, то вы получите увеличение производительности при установке параметра в значение от 8 до 16 Мбайт.\n\nПуть: HKEY_LOCAL_MACHINE \\ System \\ CurrentControlSet \\ Control \\ Session Manager \\ Memory Management. \nПараметр: IOPageLockLimit (REG_DWORD). \nЗначение: По умолчанию выставляется 512 кбайт. Вам следует указать параметр в байтах, поэтому умножьте требуемое число мегабайт два раза на 1024. Протестируйте несколько настроек и выберите наилучшую.";
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
   "Работа с файлом подкачки. \n\nВключение данного ключа приводит к тому, что система при выходе заполняет пейджфайл (pagefile.sys) весь нулями, т.е. очищает. То же самое делается в апплете Local Security Policy в Administrative Tools, раздел Local Policies, Security Options, ключ Shutdown: Clear virtual memory pagefile when system shuts down.\n\nПуть: HKEY_LOCAL_MACHINE \\ SYSTEM \\ CurrentControlSet \\ Control \\ Session Manager \\ Memory Management.\nПараметр: ClearPageFileAtShutdown. \nЗначение: '1' - включить очистку (Enable), 0 - выключить очистку (Disable).\n\nВнимание: Включение данного параметра приводит к дополнительному ожиданию перед выключением компьютера.";
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
   "Работа с графической оболочкой. \n\nНазначение данного ключа - отключить сообщение о том что недостаточно свободного места на диске. \n\nПуть: HKEY_CURRENT_USER \\ Software \\ Microsoft \\ Windows \\ CurrentVersion \\ Policies \\ Explоrer. \nПараметр: NoLowDiskSpaceChecks (REG_DWORD). \nЗначение: '1' - отключение сообщения (Enable). '0' - включение сообщения (Disable).";
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
   "Работа с графической оболочкой. \n\nОтображать или скрывать папку Shared Documents (Мои документы) в 'Мой компьютер'. \n\nПуть:  HKEY_LOCAL_MACHINE \\ SOFTWARE \\ Microsoft \\ Windows \\ CurrentVersion \\ Explorer \\ MyComputer \\ NameSpace \\ DelegateFolders.\nДля скрытия папки (Hide Folder) необходимо удалить элемент данных, типа Reg_SZ - {59031a47-3f72-44a7-89c5-5595fe6b30ee}, или создать этот же элемент для отображения (Show Folder).";
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
   "Работа с графической оболочкой. \n\nИзменение данного параметра позволяет скрыть все значки с рабочего стола.\n\nПуть: HKEY_CURRENT_USER \\ Software \\ Microsoft \\ Windows \\ CurrentVersion \\ Policies \\ Explorer.\nПараметр: NoDesktop (REG_DWORD). \nЗначения 1 - скрыть (Enable), 0 - показывать (Disable).";
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
   "Работа с графической оболочкой. \n\nИзменение данного параметра приведет к тому, что Internet Explorer будет открываться в полноэкранном режиме.\n\nПуть: HKEY_CURRENT_USER \\ Console.\nПараметр: FullScreen (REG_DWORD). Значение: '1' - включить режим (Enable), '0' - выключить (Disable). \n\nА также.\nПуть: HKEY_CURRENT_USER \\ Software \\ Microsoft \\ Internet Explorer \\ Main. \nПараметр : FullScreen(REG_SZ). Значение: 'Yes' для включения (Enable) или 'No' для выключения (Disable)";
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
   "Работа с устройствами. \n\nДанный параметр отвечает за автозапуск компакт-дисков, который происходит тогда, когда вставляется новый диск. \n\nПуть: HKEY_LOCAL_MACHINE \\ SYSTEM \\ CurrentControlSet \\ Services \\ CDRom. \nПаpаметp: Autorun (REG_DWORD). \nЗначение: '1' - автоазпуск включен (Enable), '0' - выключен (Disable)";
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
   "Работа с устройствами. \n\nДанный параметр предназначен для того, чтобы машина с АТХ блоком выключалась сама. Перед этим следует проверить, чтобы Windows стоял с ядром ACPI. \n\nПуть: HKEY_LOCAL_MACHINE \\ SOFTWARE \\ Microsoft \\ Windows NT \\ CurrentVersion \\ Winlogon. \nПаpаметp: PowerdownAfterShutdown (REG_SZ). \nЗначение: '1' - отключать питание (Enable), '0' - не отключать (Disable). \n\nВнимание: Даже включение этого параметра не гарантирует правильное управление питанием!!!";
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
   "Работа с устройствами. \n\nДанный параметр включает режим Ultra DMA 66. Если вы имеете компьютер с Intel chipset, который поддерживает UDMA66, вы будете все еще находить, что режим UDMA66 заблокирован по умолчанию на компьютерах Windows 2000. \n\nПуть: HKEY_LOCAL_MACHINE \\ SYSTEM \\ CurrentControlSet \\ Control \\ Class \\ {4D36E96A-E325-11CE-BFC1-08002BE10318} \\ 0000. \nПараметр: EnableUDMA66 (REG_DWORD). \nЗначение: '1' - включить Ultra DMA 66 (Enable), '0' - выключить (Disable).";
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
   "Работа с сетью.\n\nДанный параметр позволяет скрыть компьютер в 'Сетевом окружении'. Необходимо помнить, что должно пройти некоторое время (около часа) прежде, чем ваш компьютер станет невидим в браузере. Но вы сможете на него зайти, если наберёте его имя вручную. \n\nПуть: HKEY_LOCAL_MACHINE \\ SYSTEM \\ CurrentControlSet \\ Services \\ lanmanserver \\ parameters. \nПараметр: Hidden (REG_DWORD). \nЗначение: '1' - скрыть компьютер (Enable), '0' - показывать (Disable).";
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
   "Работа с сетью. \n\nДанный параметр позволяет запретить / разрешить скрытые ресурсы С$, D$, ADMIN$ (для рабочей станции). Windows по умолчанию, при каждом запуске, открывает автоматически скрытые ресурсы. \n\nПуть: HKEY_LOCAL_MACHINE \\ SYSTEM \\ CurrentControlSet \\ Services \\ lanmanserver \\ parameters. \nПараметр: AutoShareWks (REG_DWORD). \nЗначение: '1' - разрешить автооткрытие (Enable), '0' - запретить (Disable). \n\nВнимание: После того, как вы запретили в реестре эти ресурсы (Disable), необходимо зашарить скрытые ресурсы каждого диска самостоятельно и они более не откроются после перезагрузки.";
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
   "Работа с сетью. \n\nДанный параметр позволяет запретить / разрешить скрытые ресурсы С$, D$, ADMIN$ (для cервера). Windows по умолчанию, при каждом запуске, открывает автоматически скрытые ресурсы. \n\nПуть: HKEY_LOCAL_MACHINE \\ SYSTEM \\ CurrentControlSet \\ Services \\ lanmanserver \\ parameters. \nПараметр: AutoShareServer (REG_DWORD). \nЗначение: '1' - разрешить (Enable), '0' - запретить (Disable).";
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
         MessageDlg("Значение не корректно!!!", mtInformation, TMsgDlgButtons() << mbYes, 0);
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
   "Ускорение работы Windows. \n\nЗначение этого ключа определяет время в миллисекундах, которое система выжидает, чтобы все процессы завершили выполнение. По умолчанию значение 20000, что означает 20 секунд, которые прибавляются к времени, затрачиваемому системой на выключение компьютера, если какая-то служба или программа не выгружается. Измените его на 5000, и всё пойдёт гораздо быстрее. Но не ставьте слишком мало, потому что в этом случае вы можете столкнуться с ситуацией, когда ХР будет убивать программы раньше, чем они будут успевать сохранить свои данные. Что тоже плохо. \n\nПуть: HKEY_LOCAL_MACHINE \\ SYSTEM \\ CurrentControlSet \\ Control. \nПараметр: WaitToKillServiceTimeout (REG_SZ). \nЗначение: в миллисекундах.";
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
         MessageDlg("Значение не корректно!!!", mtInformation, TMsgDlgButtons() << mbYes, 0);
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
   "Ускорение работы Windows. \n\nЗначение этого ключа определяет время задержки в миллисекундах, после которой появляются раскрывающиеся меню. Установите его в '0'.\n\nПуть: HKEY_CURRENT_USER \\ Control Panel \\ Desktop. \nПараметр: MenuShowDelay (REG_SZ). \nЗначение: в миллисекундах.";
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
   "Ускорение работы Windows. \n\nАнимации при сворачивании (минимизации) окон. \n\nПуть: HKEY_CURRENT_USER \\ Control Panel \\ Desktop \\ WindowMetrics. \nПараметр: MinAnimate (REG_SZ). \nЗначение: '0' - выключает анимацию (Disable), '1' - включает (Enable).";
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
   "Ускорение работы Windows. \n\nАвтоматический запуск дебагера (Debug). \n\nПуть: HKEY_LOCAL_MACHINE \\ SOFTWARE \\ Microsoft \\ Windows NT \\ CurrentVersion \\ AeDebug. \nПараметр: Auto (REG_SZ). \nЗначение: '1' - включение автозапуска (Enable), '0' - выключение автоматического запуска (Disable). \n\nВнимание: Это не только позволит быстрее закрывать подвиснувшие приложения, но и позволит ускорить запуск программ и освободить пару мегабайт оперативной памяти. \nВ случае отлюченного автозапуска (Disable): если возникнут какие-либо сбои в работе приложения, то система предложит либо закрыть приложение, либо передать его отладчику для отладки. Если выбрать второе, то запустится Dr.Watson (или другой дебагер), и создаст лог-файл. Если вы уверены, что такая возможность вам ни к чему, то можете удалить папку AeDebug из реестра.";
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
   "Ускорение работы Windows. \n\nАвтоматическая выгрузка неиспользуемых библиотек. Винды держат загруженными некоторые DLL, даже если приложение, которое их использовало, уже закрыто. Это делается для ускорения последующих обращений к этим библиотекам, но это замедляет работу системы в целом. Это относится ТОЛЬКО к 32-битным библиотекам! \n\nПуть: HKEY_LOCAL_MACHINE \\ SOFTWARE \\ Microsoft \\ Windows \\ CurrentVersion \\ Explorer.\nПараметр: AlwaysUnloadDll (REG_DWORD).\nЗначения: '1' - включить выгрузку библиотек (Enable), '0' - выключить (Disable). \n\nПоследствия: \nВо-первых, ранее закрытые приложения будут вновь грузиться так же долго, как и в первый раз. \nВо-вторых, 16-битные (старые) приложения могут выдавать сообщения об ошибках. Но ты же такими не пользуешься, верно?";
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
   "Ускорение работы Windows. \n\nКогда открывается директория, то NTFS обновляет метку последнего доступа к файлам. Если файлов много и на всех надо метку обновить, то это занимает довольно много времени. Однако эту функцию можно отключить. \n\nПуть: HKEY_LOCAL_MACHINE \\ SYSTEM \\ CurrentControlSet \\ Control \\ FileSystem. \nПараметр: NtfsDisableLastAccessUpdate (REG_DWORD). \nЗначение: '1' - oтключить обновление (Enable), '0' - включить обновление (Disable).";
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
   "Дополнительные возможности. \n\nДанный параметр позволяет полностью отключить SFC (System Files Protection). \n\nПуть: HKEY_LOCAL_MACHINE \\ SOFTWARE \\ Microsoft \\ Windows NT \\ CurrentVersion \\ Winlogon. \nПараметр: SFCDisable (REG_DWORD). \nЗначение: 'ffffff9d' - отключить SFC (Enable), '0' - включить (Disable). \n\nВнимание: следует помнить что сделав это, вы рискуете испытать на себе все последствия Dll-hell, начиная от снижения общей производительности системы и заканчивая самыми разнообразными проблемами и глюками, вызванных заменой системных библиотек на несовместимые версии от сторонних производителей.";
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
   "Дополнительные возможности. \n\nДанный параметр позволяет нажатием клавиш вручную создать аварийный дамп и посмотреть на 'синий экран смерти' (BSOD). Для этого нажмите правую клавишу <Ctrl> и, удерживая ее в этом состоянии, дважды нажмите клавишу <Scroll Lock>. \n\nПуть: HKEY_LOCAL_MACHINE \\ SYSTEM \\ CurrentControlSet \\ Services \\ i8042prt \\ Parameters. \nПараметр: CrashOnCtrlScroll (REG_DWORD). \nЗначение: '1' - включить функцию (Enable), '0' - выключить (Disable). \n\nПримечание: Если вы хотите увидеть синий экран, а не перезагрузку компьютера, не забудьте снять галку о немедленной перезагрузке в случае системных давмпов.";
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
   "Безопасность. \n\nWindows имеет заданное по умолчанию сберегающее экран приложение, называемое login.scr, который выполняется, даже если никакое сберегающее экран приложение не было выбрано. Это может представлять риск защиты, поскольку это может позволять локальному пользователю заменять login.scr другой программой и начинать(запускать) это с системными привилегиями. \n\nПуть: HKEY_USERS \\ .DEFAULT \\ Control Panel \\ Desktop. \nПараметр: ScreenSaveActive (REG_SZ). \nЗначение: '0' - заставка отключена (Disable), '1'  - заставка включена (Enabled).";
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
   "Безопасность. \n\nДанный параметр позволяет запретить показ имени предыдущего работавшего с системой пользователя. \n\nПуть: HKEY_LOCAL_MACHINE \\ SOFTWARE \\ Microsoft \\ Windows \\ CurrentVersion \\ policies \\ system.\nПараметр: DontDisplayLastUserName (REG_DWORD). \nЗначение: '1' - Не показывать (Enable), '0' - Показывать (Disable).";
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
   "Работа с графической оболочкой. \n\nДанный параметр позволяет очищать список недавно открывавшихся документов в меню 'Пуск' при выключении Windows. \n\nПуть: HKEY_CURRENT_USER \\ Software \\ Microsoft \\ Windows \\ CurrentVersion \\ Policies \\ Explorer. \nПараметр: ClearRecentDocsOnExit (REG_DWORD). \nЗначение: '1' - при выходе очистка списка (Enable), '0' - выход без очистки (Disable).";
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
   "Безопасность. \n\nNull-Session - это такая причудливая вещь, которая позволяет другому пользователю, даже не зная никаких логинов и паролей на вашу систему, получить всю инфу о зашареных (share - разделенных, доступных для общего пользования) директориях, об имеющихся на компе локальных пользователях, в общем, инфу много о чем. \n\nПуть: HKEY_LOCAL_MACHINE \\ SYSTEM \\ CurrentControlSet \\ Control \\ Lsa. \nПараметр: restrictanonymous (REG_DWORD). \nЗначение: '1' - закрыть 'дыру' (Enable), '0' - 'открыть' (Disable).";
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
   "Ускорение работы Windows. \n\nОтключение создания имен файлов в формате 8.3 (NTFS). Этот ключ останавливает работу части NTFS, отвечающей за создание совместимых с МС-ДОС имен файлов в формате 8.3. Отключение этого свойства может увеличить эффективность работы в разделах NTFS, с большим количеством файлов имеющих длинные имена. \n\nПуть: HKEY_LOCAL_MACHINE \\ SYSTEM \\ CurrentControlSet \\ Control \\ FileSystem. \nПараметр: NtfsDisable8dot3NameCreation (REG_DWORD). \nЗначение: '1' - Не создавать файлы формата 8.3 (Enable), '0' - Создавать (Disable). \n\nПредупреждение: Некоторые 16 разрядные инсталляционные программы могут иметь проблемы при включении этого параметра. Вы можете или заново включить создание 8.3 имен файлов в течение установки, или использовать имена каталогов не в формате LFN, то есть 'c:\\progra~1\\applic~1'.";
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
   "Ускорение работы Windows. \n\nДанный параметр позволяет зарезервировать необходимое пространство для MFT (аналог FAT-таблицы). \n\nПуть: HKEY_LOCAL_MACHINE \\ SYSTEM \\ CurrentControlSet \\ Control \\ FileSystem. \nПараметр: NtfsMftZoneReservation (REG_DWORD). \nЗначения: \nЕсли у вас на NTFS томе относительно немного файлов, которые обычно большие, установите это значение равное '1' (по умолчанию). Вы можете установить значение '2' или '3' для умеренного количества файлов. \n'4' (максимальное), если на томе будет находиться большое количество файлов. \n\nВнимание: Имейте в виду, что установка параметра больше чем 2, заставляют систему резервировать намного большую часть диска для MFT.";
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
   "Работа с графической оболочкой. \n\nДанный параметр позволяет скрыть / отобразить объект 'Корзина' (Recycle Bin) на рабочем столе. \n\nПуть: HKEY_LOCAL_MACHINE \\ SOFTWARE \\ Microsoft \\ Windows \\ CurrentVersion \\ Explorer \\ Desktop \\ NameSpace. \nПараметр: {645FF040-5081-101B-9F08-00AA002F954E} (REG_SZ). \nУдаление параметра приводит к скрытию корзины, создание к отображению. \n\nПримечание: перезагрузка не обязательна, достаточно обновить рабочий стол.";
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
   if (Element.Value == "") {Element.Value = "Корзина";}
   Edit4->Text = Element.Value;
}
//---------------------------------------------------------------------------
void __fastcall TWindows_XP_Registry_Form::RecycleBinRenameHelpClick(
      TObject *Sender)
{
   ParametrForm->RichEdit1->Lines->Text =
   "Работа с графической оболочкой. \n\nКому надоела надпись 'Корзина' или 'Recycle Bin' могут изменить её, написав свое. \n\nПуть: HKEY_CURRENT_USER \\ Software \\ Microsoft \\ Windows \\ CurrentVersion \\ Explorer \\ CLSID \\ {645FF040-5081-101B-9F08-00AA002F954E}. \nПараметр: 'По умолчанию' (REG_SZ). \nЗначение: название объекта 'Корзина'. \n\nПримечание: перезагрузка не обязательна, достаточно обновить рабочий стол.";
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
   "Работа с устройствами. \n\nДанный параметр предназначен для любителей разгона (Overclock). Если у вас видеокарта NVidia, то включив данный параметр, у вас в настройках видеокарты появится закладка 'Настройка тактовой частоты'. \n\nПуть: HKEY_LOCAL_MACHINE \\ Software \\ NVIDIA Corporation \\ Global \\ NVTweak. \nПараметр: CoolBits (REG_DWORD). \nЗначение: 3 - возможность разгона (Enable), 0 - разгон выключен (Disable).";
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
   "Ускорение работы Windows. \n\nЭта настройка позволяет ускорять запуск программ и системных файлов – обеспечивая их дополнительным кешированием. \n\nПуть: HKEY_LOCAL_MACHINE \\ SYSTEM \\ CurrentControlSet \\ Control \\ Session Manager \\ Memory Management \\ PrefetchParameters. \nПараметр: EnablePrefetcher (REG_DWORD). \nЗначение: \n0 – отключено (Рекомендуется для маломощных компьютеров); \n1 – рекомендуется для компьютеров с ОЗУ до 256МБ (Только программы). \n2 – Для тех у кого на борту от 512МБ и более (программы и системные быблиотеки); \n3 – Это уже рассчитано для супер-пупер мощных процов + минимум ОЗУ 512Мб, хотя при LargeSystemCache=1 прекрасно работает и на 256Мб ОЗУ. \nРекомендую EnablePrefetcher=3. \n\nВ природе вы можете встретить упоминание о EnablePrefetcher = 5 или волшебном ключе EnableSuperFetch = 1 – скажу из личного опыта толку от них нет. А в Windows XP SP2 EnablePrefetcher = 5 – может дать ошибку о повреждении реестра."
   "\nПараметры Prefetch можно также использовать для запуска отдельных программ, достаточно в свойствах ярлыка программы добавить ключик /Prefetch:1 – и заметим ускорение запуска этой программы, но, к сожалению, не со всеми программами это работает. На примере браузера FireFox в свойствах ярлыка: \n«C:\\Program Files\\Mozilla Firefox\\firefox.exe» меняем на... \n«C:\\Program Files\\Mozilla Firefox\\firefox.exe» /prefetch:1";
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
   "Работа с устройствами. \n\nДанный параметр убирает сигнал Beep. \n\nПуть: HKEY_CURRENT_USER \\ Control Panel \\ Sound. \nПараметр: Beep (REG_SZ). \nЗначение: 'yes' - сигнал включен (Enable), 'no' - сигнал выключен (Disable)";
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
   "Безопасность. \n\nВключает \\ отключает TaskManager (Диспетчер задач). \n\nПуть: HKEY_CURRENT_USER \\ Software \\ Microsoft \\ Windows \\ CurrentVersion \\ Policies \\ System. \nПараметр: DisableTaskMgr (REG_DWORD). \nЗначение: '1' - выключить диспетчер задач (Enable), '0' - включить диспетчер задач (Disable).";
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
   "Работа с графической оболочкой. \n\nДанный параметр позволяет вывезти номер версии Windows в правый нижний угол фона рабочего стола. \n\nПуть: HKEY_CURRENT_USER \\ Control Panel \\ Desktop. \nПараметр: PaintDesktopVersion (REG_DWORD). \nЗначение: '1' - вывод надписи (Enable), '0' - надпись не видна (Disable). \n\nПримечание: Требуется перезагрузка.";
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
   "Безопасность. \n\nУстраняется возможность атаки с применением троянских DLL, и, как следствие, получения прав администратора. \n\nПуть: HKEY_LOCAL_MACHINE \\ SYSTEM \\ CurrentControlSet \\ Control \\ Session Manager. \nПараметр: ProtectionMode (REG_DWORD). \nЗначение: '1' - включение защиты (Enable), '0' - отключение (Disable).";
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
   "Работа с графической оболочкой. \n\nДанный параметр позволяет заблокировать вызов контекстного меню. \n\nПуть: HKEY_CURRENT_USER \\ Software \\ Microsoft \\ Windows \\ CurrentVersion \\ Policies \\ Explorer. \nПараметр: NoViewContextMenu (REG_DWORD). \nЗначение: '1' - контекстное меню отключено (Enable), '0' - включено (Disable).";
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
   "Безопасность. \n\nВключает \ отключает возможность вызова редактора реестра (RegEdit.exe). \n\nПуть: HKEY_CURRENT_USER \\ Software \\ Microsoft \\ Windows \\ CurrentVersion \\ Policies \\ System. \nПараметр: DisableRegistryTools (DWORD). \nЗначение: '1' - запретить доступ к RegEdit.exe (Enable), '0' - разрешить доступ (Disable).";
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
   "Работа с устройствами. \n\nДанный параметр позволяет запускать клавишу 'Num Lock' при запуске Windows, в окне ввода пароля. \n\nПуть: HKEY_USERS \\ .DEFAULT \\ Control Panel \\ Keyboard. \nПараметр: InitialKeyboardIndicators (REG_SZ). \nЗначение: '2' - Num Lock запускается (Enable), '0' - Num Lock не включен (Disable). \n\nВнимание: Включение данного параметра приведет к тому, что Num Lock будет включаться у всех пользователей, работающих за данной машиной, даже если они заблокировали это включение в реестре в ветке: \nHKEY_CURRENT_USER \\ Control Panel \\ Keyboard, \nКлюч: InitialKeyboardIndicators.";
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
   "Работа с сетью.\n\nЕсли на вашем комьютере стоит более одной сетевой карты и они подключены к сетям, необходимо включить данный параметр. Данный параметр позволяет включить маршрутизацию Windows. \n\nПуть: HKEY_LOCAL_MACHINE \\ SYSTEM \\ CurrentControlSet \\ Services \\ Tcpip \\ Parameters. \nПараметр: IPEnableRouter (REG_DWORD). \nЗначение: '1' - включить маршрутизацию (Enable), '0' - выключить (Disable). \n\nПримечание: Необходимо помнить, что для работы маршрутизации Windows должна быть включена служба 'Routing and Remote access' (Маршрутизация и удаленный доступ).";
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
   "Работа с сетью.\n\nЕсли включить данный параметр, то перед началом соединения будет происходить проверка на мертвые маршрутизаторы по пути до сервера. Этот сильно тормозит протокол за счет лишних затрат на поиск.\n\nПуть: HKEY_LOCAL_MACHINE \\ SYSTEM \\ CurrentControlSet \\ Services \\ Tcpip \\ Parameters. \nПараметр: DeadGWDetectDefault (REG_DWORD). \nЗначение: '1' - проверка включена (Enable), '0' - проверка отключена (Disable).";
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
   "Работа с сетью.\n\nДанный параметр может позволить / запретить Windows изменять таблицу маршрутизации в ответ на ICMP редирект пакеты. \n\nПуть: HKEY_LOCAL_MACHINE \\ SYSTEM \\ CurrentControlSet \\ Services \\ Tcpip \\ Parameters. \nПараметр: EnableICMPRedirect (REG_DWORD). \nЗначение: '1' - разрешить изменение таблицы, '0' - запретить.";
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
   "Работа с сетью.\n\nДанный параметр запрещает / разрешает Windows вычислять MTU (иначе атакующий может сделать его очень маленьким и перегрузить стэк). \n\nПуть: HKEY_LOCAL_MACHINE \\ SYSTEM \\ CurrentControlSet \\ Services \\ Tcpip \\ Parameters. \nПараметр: EnablePMTUDiscovery (REG_DWORD). \nЗначение: '1' - разрешить вычисление таблицы, '0' - запретить.";
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
   "Работа с сетью.\n\nДанный параметр позволяет защитить машину от NetBIOS name-release атак. \n\nПуть: HKEY_LOCAL_MACHINE \\ SYSTEM \\ CurrentControlSet \\ Services \\ Tcpip \\ Parameters. \nПараметр: NoNameReleaseOnDemand (REG_DWORD). \nЗначение: '1' - включить защиту (Enable), '0' - отключить (Disable).";
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
   "Ускорение работы Windows. \n\nВключение данного параметра позволит Windows самому завершать подвисшие задачи без всякого предупреждения. Интервал через которое Windows завершит задачу определяется параметром WaitToKillAppTimeout, в той же ветке реестра. \n\nПуть: HKEY_CURRENT_USER \\ Control Panel \\ Desktop. \nПараметр: AutoEndTasks (REG_SZ). \nЗначение: 1 - разрешить автозавершение (Enable), 0 - запретить (Disable).";
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
         MessageDlg("Значение не корректно!!!", mtInformation, TMsgDlgButtons() << mbYes, 0);
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
   "Ускорение работы Windows. \n\nЗначением данного параметра является время в миллисекундах, по истечению которого Windows будет завершать повисшее приложение. \n\nПуть: HKEY_CURRENT_USER \\ Control Panel \\ Desktop. \nПараметр: WaitToKillAppTimeout (REG_SZ). \nЗначение: в миллисекундах. \n\nВнимание: Следует заметить, что, устанавливая слишком малые значения для WaitToKillAppTimeout, вы можете получить проблемы в виде не вовремя снятых программ и соответственно несохраненных данных.";
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
         MessageDlg("Значение не корректно!!!", mtInformation, TMsgDlgButtons() << mbYes, 0);
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
   "Ускорение работы Windows. \n\nЗначением данного параметра является время в миллисекундах, по истечению которого Windows будет считать задачу повисшей. \n\nПуть: HKEY_CURRENT_USER \\ Control Panel \\ Desktop. \nПараметр: HungAppTimeout (REG_SZ). \nЗначение: в миллисекундах. \n\nВнимание: Следует заметить, что, устанавливая слишком малые значения для HungAppTimeout, вы можете получить проблемы в виде не вовремя снятых программ и соответственно несохраненных данных.";
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
   "Работа с устройствами. \n\nДанный параметр позволяет запускать клавишу 'Num Lock' при запуске личных параметров для каждого пользователя данной машины. \n\nПуть: HKEY_CURRENT_USER \\ Control Panel \\ Keyboard. \nПараметр: InitialKeyboardIndicators (REG_SZ). \nЗначение: '2' - Num Lock запускается (Enable), '0' - Num Lock не включен (Disable). \n\nВнимание: Отключение запуска Num Lock возможно только при отключенном параметре InitialKeyboardIndicators в ветке HKEY_USERS (для всех пользователей).";
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
   "О программе \n===================\nПрограмма 'Windows XP Registry' предназначена для работы с реестром Windows XP. В ней собраны некоторые секреты системного реестра, позволяющие оптимизировать работу операционной системы."
   "\n===================\nОписание программы \n===================\nПрограмма 'Windows XP Registry' обладает очень простым интерфейсом. \nГлавное окно делится на закладки: \nAcceleration (ускорение) - предоставлены возможноcти по ускорению работы Windows XP; \nExplorer (графическая оболочка) - все, связанное с изменением пользовательского интерфейса; \nHardware (железо) - всё, связанное с оборудованием, установленном на компьютере; \nMemory (память) - оптимизация работы памяти и файла подкачки; \nNet (сеть) - всё, связанное с сетью и сетевой безопасностью; \nSecurity (безопасноть) - раздел для системных администраторов; \nOther (остальное) - все, что не относится ни к одному из вышеперечисленных."
   "\nКаждый раздел делится: на рамки с названием параметров, информационные меню (в виде перелючателей или полей), с возможными значениями этих параметров и кнопки. \nКнопка 'Save' - предназначена задавать значение параметру, которое указана в информационном меню данной рамки; \nКнопка 'Refresh' - устанавливает информационное меню в положение, равное текущему значению параметра; \nСправка - вызов справки осуществляется нажатием в любое место рамки, признаком является появление курсора со знаком вопроса. Справка включает в себя полное описание нужного параметра на русском языке. Внимательно читайте справку, чтобы понять какое информационное поле надо задать, чтобы добиться желаемого эффекта."
   "\n===================\nНеверные результаты \n===================\. \nАвтор не уверен в правильности работы всех параметров, включенных в данный проект, так как некоторые из них просто невозможно проверить и быть уверенным на все 100, так что лучше используйте, те о которых слышали :). \nОшибка кнопки 'Refresh' - ошибка, не ошибка, но недочет возможен, в случае, если параметр не создан, кнопка не будет реагировать на нажатие."
   "\n===================\nОт себя \n===================\. \nАвтор надеется, что данная программа облегчит жизнь многим людям, лишая их возможности бродить в дебрях реестра. Большая просьба сообщать обо всех недочетах и ошибках, замеченных в процессе использования программного продукта. \n\nЕсли кого заинтересовал данный проект, то если не лень... высылайте информацию о секретах реестра Windows XP (тех, которых нет в данной версии программы), мне на почту. Прошу заранее: 1) высылать информацию, будучи полностью уверенным в её достоверности. 2) высылать инфу в том виде, в котором она представлена в данном проекте. А именно: путь, параметр, тип, значение, описание. Очень надеюсь на вашу помощь. Если наберется ещё 20 - 30 параметров напишу вторую версию программы.";
   ParametrForm->Caption = "About program";
   ParametrForm->ShowModal();
}
//---------------------------------------------------------------------------

