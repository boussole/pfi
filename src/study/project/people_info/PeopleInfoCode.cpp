//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "PeopleInfoCode.h"
#include <fstream.h>
#include <Windows.h>
#include "OtherForm\\FileName\\FileName.cpp"
#include "OtherForm\\NewWay\\NewWay.cpp"
#include "OtherForm\\InfoError\\InfoError.cpp"
#include "OtherForm\\AboutProgram\\AboutProgram.cpp"
#include "OtherForm\\SplashForm\\SplashForm.cpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPeopleInfoForm *PeopleInfoForm;
//---------------------------------------------------------------------------
__fastcall TPeopleInfoForm::TPeopleInfoForm(TComponent* Owner)
   : TForm(Owner)
{
}
/*/-----------------------------------------------------------------------/*/
/*/Глобальная переменная/*/
AnsiString FileWay;
AnsiString FileName;
Set <int, 65, 90> SetOfHighRegister;
//---------------------------------------------------------------------------
/*/Прототипы функций/*/
bool GetString(AnsiString);
bool CreateDefaultFile();
bool Interpretator(AnsiString);
bool CreateInfoFile(THuman);
bool SearchInstruction(AnsiString);
void Modification();
void LowRegister();
bool OnlySpace();
bool OnlySpaceWay();
/*/-----------------------------------------------------------------------/*/
void __fastcall TPeopleInfoForm::SaveClick(TObject *Sender)
{
   THuman Human;
   Human.SurName = Edit2->Text;
   Human.Name = Edit1->Text;
   Human.FathersName = Edit3->Text;
   Human.Telephone = Edit12->Text;
   Human.Country = Edit4->Text;
   Human.City = Edit6->Text;
   Human.Territory = Edit7->Text;
   Human.Street = Edit5->Text;
   Human.Index = Edit8->Text;
   Human.House = Edit11->Text;
   Human.Corp = Edit9->Text;
   Human.Flat = Edit10->Text;
   Human.BirthDay = Edit13->Text;
   Human.MobileTelephone = Edit14->Text;
   Human.EMail = Edit15->Text;
   Human.ICQ = Edit16->Text;
   Human.Nick = Edit21->Text;
   Human.WorkPlace = Edit19->Text;
   Human.Post = Edit17->Text;
   Human.WAddress = Edit18->Text;
   Human.WTelephone = Edit20->Text;
   Human.Site = Edit22->Text;
   FileName = Human.SurName + " " + Human.Name;
   CheckFileName:
   if (OnlySpace())
      {
         if (MessageDlg("Имя создаваемого файла отсутствует, хотите создать его?", mtInformation,
                        TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
            {
               FileNameForm->ShowModal();
               FileName = FileNameHelp;
               goto CheckFileName;
            }
         else
            {
               Application->MessageBoxA("Информационный файл не будет создан!!!", "Внимание", MB_OK);
               return;
            }
      }
   if (!CreateInfoFile(Human))
      {
         InfoErrorForm->ShowModal();
      }
}
//---------------------------------------------------------------------------
void __fastcall TPeopleInfoForm::FormCreate(TObject *Sender)
{
   FileWay = "";
   FileName = "";
// (Height - ширина) (Width - длина)
   if ((Screen->Width < 800) && (Screen->Height < 600))
      {
         Application->MessageBoxA("Минимальное разрешение экрана: 800 Х 600", "Приложенние бужет закрыто");
         return;
      }
   /*/Информационный файл отсутствует/*/
   if (!FileExists("PeopleInfo.ini"))
      {
         if (!CreateDefaultFile())
            {
               PeopleInfoForm->Close();
               return;
            }
      }
   /*/Информационный файл существует/*/
   else
      {
         if (!GetString("PeopleInfo.ini"))
            {
               if (!CreateDefaultFile())
                  {
                     PeopleInfoForm->Close();
                     return;
                  }
            }
      }
   Modification();
   SetOfHighRegister << 65 << 66 << 67 << 68 << 69 << 70 << 71 << 72 << 73 << 74
                     << 75 << 76 << 77 << 78 << 79 << 80 << 81 << 82 << 83 << 84
                     << 85 << 86 << 87 << 88 << 89 << 90 ;
}
//---------------------------------------------------------------------------
/*/Функция определения /*/
bool GetString(AnsiString Help)
   {
      AnsiString Fail = "Файл "+ Help + " невозможно открыть";
      bool Find = false;
      ifstream file;
      char Buffer[255];
      file.open(Help.c_str());
      if (file.fail())
         {
            Application->MessageBoxA(Fail.c_str(), "Открытие файла", MB_OK);
            file.close();
            return (false);
         }
      else
         {
            while ((!file.eof()) &&  (!Find))
               {
                  file.getline(Buffer, sizeof (Buffer));
                  if (Interpretator(Buffer))
                     {
                        Find = true;
                        break;
                     }
               }
            file.close();
         }
      if (Find)
         {
            return (true);
         }
      else
         {
            return (false);
         }
   }
/*/------------------------------------------------------------------------/*/
/*/Создание информационного файла по умолчанию/*/
bool CreateDefaultFile()
   {
   ofstream file;
   file.open("PeopleInfo.ini");
   if (file.fail())
            {
               Application->MessageBoxA("Невозможно задать информационный файл!!!",
               "Приложение будет закрыто", MB_OK);
               file.close();
               return (false);
            }
         else
            {
               file.flush();
               file << "save directory = default;" << endl;
               file.close();
               FileWay = "default";
               return (true);
            }
   }
/*/------------------------------------------------------------------------/*/
/*/Интерпретация строки в файле/*/
bool Interpretator(AnsiString Help)
   {
      int i = 1;
      AnsiString Hlp;
      while ((i <= Help.Length()) && (Help[i] != '='))
         {
            if (Help[i] != ' ')
               {
                  Hlp = Hlp + Help[i];
               }
            i++;
         }
      if (Hlp == "savedirectory")
         {
            /*/пропустим знак "="/*/
            i++;
            /*/пропустим пробелы после знака "="/*/
            while ( (i <= Help.Length()) && (Help[i] == ' ') )
               {
                  i++;
               }
            while ((i <= Help.Length()) && (Help[i] != ';'))
               {
                  FileWay = FileWay + Help[i];
                  i++;
               }
            return (true);
         }
      else
         {
            return (false);
         }
   }
/*/------------------------------------------------------------------------/*/
/*/Создание информационного файла/*/
bool CreateInfoFile(THuman _Human)
   {
      bool Collision = false;
      FileNameHelp = "";
//      LowRegister();
      AfterCollision:
      /*/Создание папки по умолчанию/*/
      if (FileWay == "default")
         {
            if ( (!CreateDirectory("NoteBook", NULL)) && (!ERROR_ALREADY_EXISTS))
               {
                        Application->MessageBoxA("Невозможно создать папку",
                                                 "Создание папки по умолчанию", MB_OK);
                        return (false);
               }
            else
               {
                  FileName = "NoteBook\\" + FileName;
               }
         }
      /*/Создание заданной папки/*/
      else
         {
            if ( (!CreateDirectory(FileWay.c_str(), NULL)) && (!ERROR_ALREADY_EXISTS))
               {
                  Application->MessageBoxA("Невозможно создать заданную папку",
                                           "Создание заданной папки", MB_OK);
                  return (false);
               }
            else
               {
                  FileName = FileWay + "\\\\" + FileName;
               }
         }
                  /*/Проверка на коллизии одноименных файлов/*/
                  TryCollisions:
                  if (FileExists(FileName + ".txt"))
                     {
                        if (MessageDlg("Файл с таким именем уже существует, хотите заменить его?", mtInformation,
                        TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo)
                           {
                              Collision = true;
                              FileNameForm->ShowModal();
                              FileName = FileNameHelp;
                              ClearFileName:
                              if (OnlySpace())
                                 {
                                    if (MessageDlg("Имя создаваемого файла отсутствует, хотите задать его?", mtInformation,
                                                   TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
                                          {
                                             FileNameForm->ShowModal();
                                             FileName = FileNameHelp;
                                             goto ClearFileName;
                                          }
                                    else
                                          {
                                             Application->MessageBoxA("Информационный файл не будет создан!!!", "Внимание", MB_OK);
                                             return (false);
                                          }
                                 }
                              goto TryCollisions;
                        }
                     }
                  if (Collision)
                     {
                        Collision = false;
                        goto AfterCollision;
                     }
                  /*/Создание информационного файла/*/
                  ofstream file;
                  file.open( (FileName + ".txt").c_str());
                  if (file.fail())
                     {
                        Application->MessageBoxA("            Невозможно создать файл",
                                                 "Создание информационного файла", MB_OK);
                        file.close();
                        return(false);
                     }
                  else
                     {
                        file << "----------Личные данные----------" << endl;
                        file << "Фамилия: ";
                        file << "\t\t" << _Human.SurName.c_str() << endl;
                        file << "Имя: ";
                        file << "\t\t\t" << _Human.Name.c_str() << endl;
                        file << "Отчество: ";
                        file << "\t\t" << _Human.FathersName.c_str() << endl;
                        file << "Домашний телефон: ";
                        file << "\t" << _Human.Telephone.c_str() << endl;
                        file << "---------------------------------" << endl << endl;
                        file << "--------------Адрес--------------" << endl;
                        file << "Страна: ";
                        file << "\t\t" << _Human.Country.c_str() << endl;
                        file << "Край, село, район: ";
                        file << "\t" << _Human.Territory.c_str() << endl;
                        file << "Индекс: ";
                        file << "\t\t" << _Human.Index.c_str() << endl;
                        file << "Город: ";
                        file << "\t\t\t" << _Human.City.c_str() << endl;
                        file << "Улица: ";
                        file << "\t\t\t" << _Human.Street.c_str() << endl;
                        file << "Дом: ";
                        file << "\t\t\t" << _Human.House.c_str() << endl;
                        file << "Корпус: ";
                        file << "\t\t" << _Human.Corp.c_str() << endl;
                        file << "Квартира: ";
                        file << "\t\t" << _Human.Flat.c_str() << endl;
                        file << "---------------------------------" << endl << endl;
                        file << "------Дополнительные данные------" << endl;
                        file << "День рождения: ";
                        file << "\t\t" << _Human.BirthDay.c_str() << endl;
                        file << "Мобильный телефон: ";
                        file << "\t" << _Human.MobileTelephone.c_str() << endl;
                        file << "E - Mail: ";
                        file << "\t\t" << _Human.EMail.c_str() << endl;
                        file << "ICQ: ";
                        file << "\t\t\t" << _Human.ICQ.c_str() << endl;
                        file << "Nick: ";
                        file << "\t\t\t" << _Human.Nick.c_str() << endl;
                        file << "Место работы: ";
                        file << "\t\t" << _Human.WorkPlace.c_str() << endl;
                        file << "Должность: ";
                        file << "\t\t" << _Human.Post.c_str() << endl;
                        file << "Адрес работы: ";
                        file << "\t\t" << _Human.WAddress.c_str() << endl;
                        file << "Рабочий телефон: ";
                        file << "\t" << _Human.WTelephone.c_str() << endl;
                        file << "Сайт: ";
                        file << "\t\t\t" << _Human.Site.c_str() << endl;
                        file << "---------------------------------" << endl;
                        file.close();
                     }
      return(true);
   }
/*/-----------------------------------------------------------------------/*/
/*/Путь должен разделяться двойным слешем/*/
void Modification()
   {
      AnsiString Help;
      int i = 1;
      while (i <= FileWay.Length())
         {
            if (  (FileWay[i] == '\\')
                  &&
                  (
                     ( (i != FileWay.Length()) && (FileWay[i + 1] != '\\') )
                     &&
                     ( (i != 1) && (FileWay[i - 1] != '\\') )
                  )
               )
               {
                  Help = Help + '\\';
               }
            Help = Help + FileWay[i];
            i++;
         }
      FileWay = Help;
   }
/*/-----------------------------------------------------------------------/*/
/*/Переводим строку в нижний регистр/*/
void LowRegister()
   {
      for (int i = 1; i <= FileWay.Length(); i++)
         {
            if ( SetOfHighRegister.Contains(int(FileWay[i])) )
               {
                  FileWay[i] = char(int(FileWay[i]) + 32);
               }
         }
   }
/*/-----------------------------------------------------------------------/*/
/*/Проверка имени файла, чтобы в нём были хоть какие - то символы, кроме пробела/*/
bool OnlySpace()
   {
      for (int i = 1; i <= FileName.Length(); i++)
         {
            if ((FileName[i] != ' '))
               {
                  return (false);
               }
         }
      return (true);
   }
/*/-----------------------------------------------------------------------/*/
void __fastcall TPeopleInfoForm::SetNewWayClick(TObject *Sender)
{
   Again:
   NewWayForm->ShowModal();
   FileWay = NewWay;
   ofstream file;
   file.open("PeopleInfo.ini");
   if (file.fail())
            {
               Application->MessageBoxA("Невозможно задать информационный файл!!!",
               "Изменение пути по умолчанию", MB_OK);
               file.close();
               return;
            }
         else
            {
               if (OnlySpaceWay())
                  {
                     if (MessageDlg("Имя создаваемого пути отсутствует, хотите задать его?", mtInformation,
                                                   TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
                        {
                           goto Again;
                        }
                     else
                        {
                           Application->MessageBoxA("Данная операция невозможна в этом приложении, будет установлено значение по умолчанию",
                                                   "Изменение пути по умолчанию", MB_OK);

                           FileWay = "default";
                           return;
                        }
                  }
               file.flush();
               file << "save directory = ";
               file << NewWay.c_str();
               file << ";" << endl;
               file.close();
               Application->MessageBoxA("Желательно перезапустить приложение", "Изменение пути по умолчанию", MB_OK);
               return;
            }
}
//---------------------------------------------------------------------------
/*/Проверка пути на содержимое/*/
bool OnlySpaceWay()
   {
      for (int i = 1; i <= FileWay.Length(); i++)
         {
            if ((FileWay[i] != ' '))
               {
                  return (false);
               }
         }
      return (true);
   }
/*/-----------------------------------------------------------------------/*/

void __fastcall TPeopleInfoForm::SetDefaultWayClick(TObject *Sender)
{
   CreateDefaultFile();
}
//---------------------------------------------------------------------------

void __fastcall TPeopleInfoForm::ExitClick(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------

void __fastcall TPeopleInfoForm::ShowCurrentWayClick(TObject *Sender)
{
   MessageDlg(FileWay.c_str(), mtInformation, TMsgDlgButtons() << mbYes, 0);
}
//---------------------------------------------------------------------------
void __fastcall TPeopleInfoForm::About1Click(TObject *Sender)
{
   TAboutProgramForm *Form = new TAboutProgramForm(this);
   Form->ShowModal();
   delete Form;
   Form = NULL;
}
//---------------------------------------------------------------------------

void __fastcall TPeopleInfoForm::About2Click(TObject *Sender)
{
   TSplash *Form = new TSplash(this);
   Form->ShowModal();
   delete Form;
   Form = NULL;
}
//---------------------------------------------------------------------------

void __fastcall TPeopleInfoForm::BitBtn1Click(TObject *Sender)
{
   if (SaveDialog1->Execute())
      {
         THuman Human;
         Human.SurName = Edit2->Text;
         Human.Name = Edit1->Text;
         Human.FathersName = Edit3->Text;
         Human.Telephone = Edit12->Text;
         Human.Country = Edit4->Text;
         Human.City = Edit6->Text;
         Human.Territory = Edit7->Text;
         Human.Street = Edit5->Text;
         Human.Index = Edit8->Text;
         Human.House = Edit11->Text;
         Human.Corp = Edit9->Text;
         Human.Flat = Edit10->Text;
         Human.BirthDay = Edit13->Text;
         Human.MobileTelephone = Edit14->Text;
         Human.EMail = Edit15->Text;
         Human.ICQ = Edit16->Text;
         Human.Nick = Edit21->Text;
         Human.WorkPlace = Edit19->Text;
         Human.Post = Edit17->Text;
         Human.WAddress = Edit18->Text;
         Human.WTelephone = Edit20->Text;
         ofstream file;
         file.open((SaveDialog1->FileName).c_str());
         if (file.fail())
            {
               MessageDlg("Не удается открыть файл для записи", mtError, TMsgDlgButtons() << mbYes, 0);
               return;
            }
               file << "----------Личные данные----------" << endl;
               file << "Фамилия: ";
               file << "\t\t" << Human.SurName.c_str() << endl;
               file << "Имя: ";
               file << "\t\t\t" << Human.Name.c_str() << endl;
               file << "Отчество: ";
               file << "\t\t" << Human.FathersName.c_str() << endl;
               file << "Домашний телефон: ";
               file << "\t" << Human.Telephone.c_str() << endl;
               file << "---------------------------------" << endl << endl;
               file << "--------------Адрес--------------" << endl;
               file << "Страна: ";
               file << "\t\t" << Human.Country.c_str() << endl;
               file << "Край, село, район: ";
               file << "\t" << Human.Territory.c_str() << endl;
               file << "Индекс: ";
               file << "\t\t" << Human.Index.c_str() << endl;
               file << "Город: ";
               file << "\t\t\t" << Human.City.c_str() << endl;
               file << "Улица: ";
               file << "\t\t\t" << Human.Street.c_str() << endl;
               file << "Дом: ";
               file << "\t\t\t" << Human.House.c_str() << endl;
               file << "Корпус: ";
               file << "\t\t" << Human.Corp.c_str() << endl;
               file << "Квартира: ";
               file << "\t\t" << Human.Flat.c_str() << endl;
               file << "---------------------------------" << endl << endl;
               file << "------Дополнительные данные------" << endl;
               file << "День рождения: ";
               file << "\t\t" << Human.BirthDay.c_str() << endl;
               file << "Мобильный телефон: ";
               file << "\t" << Human.MobileTelephone.c_str() << endl;
               file << "E - Mail: ";
               file << "\t\t" << Human.EMail.c_str() << endl;
               file << "ICQ: ";
               file << "\t\t\t" << Human.ICQ.c_str() << endl;
               file << "Nick: ";
               file << "\t\t\t" << Human.Nick.c_str() << endl;
               file << "Место работы: ";
               file << "\t\t" << Human.WorkPlace.c_str() << endl;
               file << "Должность: ";
               file << "\t\t" << Human.Post.c_str() << endl;
               file << "Адрес работы: ";
               file << "\t\t" << Human.WAddress.c_str() << endl;
               file << "Рабочий телефон: ";
               file << "\t" << Human.WTelephone.c_str() << endl;
               file << "---------------------------------" << endl;
         file.close();
      }
}
/*/----------------------------------------------------------------------/*/
void __fastcall TPeopleInfoForm::ScreenResClick(TObject *Sender)
{
   AnsiString HelpString= "Текущее разрешение экрана: " + AnsiString(Screen->Width) + " X " + (Screen->Height);
   Application->MessageBoxA( HelpString.c_str(),
                             "Информация", MB_OK);
   if ((Screen->Width < 1280) && (Screen->Height < 1024))
      {
         Application->MessageBoxA("Рекомендованное разрешение экрана: 1280 Х 1024", "Внимание", MB_OK);
      }
}
//---------------------------------------------------------------------------

void __fastcall TPeopleInfoForm::ClearClick(TObject *Sender)
{
   Edit1->Clear(); Edit2->Clear(); Edit3->Clear(); Edit4->Clear(); Edit5->Clear();
   Edit6->Clear(); Edit7->Clear(); Edit8->Clear(); Edit9->Clear(); Edit10->Clear();
   Edit11->Clear(); Edit12->Clear(); Edit13->Clear(); Edit14->Clear();Edit15->Clear();
   Edit16->Clear(); Edit17->Clear(); Edit18->Clear(); Edit19->Clear(); Edit20->Clear(); Edit21->Clear();
   Edit22->Clear();
}
//---------------------------------------------------------------------------

