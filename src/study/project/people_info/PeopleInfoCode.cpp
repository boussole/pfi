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
/*/���������� ����������/*/
AnsiString FileWay;
AnsiString FileName;
Set <int, 65, 90> SetOfHighRegister;
//---------------------------------------------------------------------------
/*/��������� �������/*/
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
         if (MessageDlg("��� ������������ ����� �����������, ������ ������� ���?", mtInformation,
                        TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
            {
               FileNameForm->ShowModal();
               FileName = FileNameHelp;
               goto CheckFileName;
            }
         else
            {
               Application->MessageBoxA("�������������� ���� �� ����� ������!!!", "��������", MB_OK);
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
// (Height - ������) (Width - �����)
   if ((Screen->Width < 800) && (Screen->Height < 600))
      {
         Application->MessageBoxA("����������� ���������� ������: 800 � 600", "����������� ����� �������");
         return;
      }
   /*/�������������� ���� �����������/*/
   if (!FileExists("PeopleInfo.ini"))
      {
         if (!CreateDefaultFile())
            {
               PeopleInfoForm->Close();
               return;
            }
      }
   /*/�������������� ���� ����������/*/
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
/*/������� ����������� /*/
bool GetString(AnsiString Help)
   {
      AnsiString Fail = "���� "+ Help + " ���������� �������";
      bool Find = false;
      ifstream file;
      char Buffer[255];
      file.open(Help.c_str());
      if (file.fail())
         {
            Application->MessageBoxA(Fail.c_str(), "�������� �����", MB_OK);
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
/*/�������� ��������������� ����� �� ���������/*/
bool CreateDefaultFile()
   {
   ofstream file;
   file.open("PeopleInfo.ini");
   if (file.fail())
            {
               Application->MessageBoxA("���������� ������ �������������� ����!!!",
               "���������� ����� �������", MB_OK);
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
/*/������������� ������ � �����/*/
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
            /*/��������� ���� "="/*/
            i++;
            /*/��������� ������� ����� ����� "="/*/
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
/*/�������� ��������������� �����/*/
bool CreateInfoFile(THuman _Human)
   {
      bool Collision = false;
      FileNameHelp = "";
//      LowRegister();
      AfterCollision:
      /*/�������� ����� �� ���������/*/
      if (FileWay == "default")
         {
            if ( (!CreateDirectory("NoteBook", NULL)) && (!ERROR_ALREADY_EXISTS))
               {
                        Application->MessageBoxA("���������� ������� �����",
                                                 "�������� ����� �� ���������", MB_OK);
                        return (false);
               }
            else
               {
                  FileName = "NoteBook\\" + FileName;
               }
         }
      /*/�������� �������� �����/*/
      else
         {
            if ( (!CreateDirectory(FileWay.c_str(), NULL)) && (!ERROR_ALREADY_EXISTS))
               {
                  Application->MessageBoxA("���������� ������� �������� �����",
                                           "�������� �������� �����", MB_OK);
                  return (false);
               }
            else
               {
                  FileName = FileWay + "\\\\" + FileName;
               }
         }
                  /*/�������� �� �������� ����������� ������/*/
                  TryCollisions:
                  if (FileExists(FileName + ".txt"))
                     {
                        if (MessageDlg("���� � ����� ������ ��� ����������, ������ �������� ���?", mtInformation,
                        TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo)
                           {
                              Collision = true;
                              FileNameForm->ShowModal();
                              FileName = FileNameHelp;
                              ClearFileName:
                              if (OnlySpace())
                                 {
                                    if (MessageDlg("��� ������������ ����� �����������, ������ ������ ���?", mtInformation,
                                                   TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
                                          {
                                             FileNameForm->ShowModal();
                                             FileName = FileNameHelp;
                                             goto ClearFileName;
                                          }
                                    else
                                          {
                                             Application->MessageBoxA("�������������� ���� �� ����� ������!!!", "��������", MB_OK);
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
                  /*/�������� ��������������� �����/*/
                  ofstream file;
                  file.open( (FileName + ".txt").c_str());
                  if (file.fail())
                     {
                        Application->MessageBoxA("            ���������� ������� ����",
                                                 "�������� ��������������� �����", MB_OK);
                        file.close();
                        return(false);
                     }
                  else
                     {
                        file << "----------������ ������----------" << endl;
                        file << "�������: ";
                        file << "\t\t" << _Human.SurName.c_str() << endl;
                        file << "���: ";
                        file << "\t\t\t" << _Human.Name.c_str() << endl;
                        file << "��������: ";
                        file << "\t\t" << _Human.FathersName.c_str() << endl;
                        file << "�������� �������: ";
                        file << "\t" << _Human.Telephone.c_str() << endl;
                        file << "---------------------------------" << endl << endl;
                        file << "--------------�����--------------" << endl;
                        file << "������: ";
                        file << "\t\t" << _Human.Country.c_str() << endl;
                        file << "����, ����, �����: ";
                        file << "\t" << _Human.Territory.c_str() << endl;
                        file << "������: ";
                        file << "\t\t" << _Human.Index.c_str() << endl;
                        file << "�����: ";
                        file << "\t\t\t" << _Human.City.c_str() << endl;
                        file << "�����: ";
                        file << "\t\t\t" << _Human.Street.c_str() << endl;
                        file << "���: ";
                        file << "\t\t\t" << _Human.House.c_str() << endl;
                        file << "������: ";
                        file << "\t\t" << _Human.Corp.c_str() << endl;
                        file << "��������: ";
                        file << "\t\t" << _Human.Flat.c_str() << endl;
                        file << "---------------------------------" << endl << endl;
                        file << "------�������������� ������------" << endl;
                        file << "���� ��������: ";
                        file << "\t\t" << _Human.BirthDay.c_str() << endl;
                        file << "��������� �������: ";
                        file << "\t" << _Human.MobileTelephone.c_str() << endl;
                        file << "E - Mail: ";
                        file << "\t\t" << _Human.EMail.c_str() << endl;
                        file << "ICQ: ";
                        file << "\t\t\t" << _Human.ICQ.c_str() << endl;
                        file << "Nick: ";
                        file << "\t\t\t" << _Human.Nick.c_str() << endl;
                        file << "����� ������: ";
                        file << "\t\t" << _Human.WorkPlace.c_str() << endl;
                        file << "���������: ";
                        file << "\t\t" << _Human.Post.c_str() << endl;
                        file << "����� ������: ";
                        file << "\t\t" << _Human.WAddress.c_str() << endl;
                        file << "������� �������: ";
                        file << "\t" << _Human.WTelephone.c_str() << endl;
                        file << "����: ";
                        file << "\t\t\t" << _Human.Site.c_str() << endl;
                        file << "---------------------------------" << endl;
                        file.close();
                     }
      return(true);
   }
/*/-----------------------------------------------------------------------/*/
/*/���� ������ ����������� ������� ������/*/
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
/*/��������� ������ � ������ �������/*/
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
/*/�������� ����� �����, ����� � �� ���� ���� ����� - �� �������, ����� �������/*/
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
               Application->MessageBoxA("���������� ������ �������������� ����!!!",
               "��������� ���� �� ���������", MB_OK);
               file.close();
               return;
            }
         else
            {
               if (OnlySpaceWay())
                  {
                     if (MessageDlg("��� ������������ ���� �����������, ������ ������ ���?", mtInformation,
                                                   TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
                        {
                           goto Again;
                        }
                     else
                        {
                           Application->MessageBoxA("������ �������� ���������� � ���� ����������, ����� ����������� �������� �� ���������",
                                                   "��������� ���� �� ���������", MB_OK);

                           FileWay = "default";
                           return;
                        }
                  }
               file.flush();
               file << "save directory = ";
               file << NewWay.c_str();
               file << ";" << endl;
               file.close();
               Application->MessageBoxA("���������� ������������� ����������", "��������� ���� �� ���������", MB_OK);
               return;
            }
}
//---------------------------------------------------------------------------
/*/�������� ���� �� ����������/*/
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
               MessageDlg("�� ������� ������� ���� ��� ������", mtError, TMsgDlgButtons() << mbYes, 0);
               return;
            }
               file << "----------������ ������----------" << endl;
               file << "�������: ";
               file << "\t\t" << Human.SurName.c_str() << endl;
               file << "���: ";
               file << "\t\t\t" << Human.Name.c_str() << endl;
               file << "��������: ";
               file << "\t\t" << Human.FathersName.c_str() << endl;
               file << "�������� �������: ";
               file << "\t" << Human.Telephone.c_str() << endl;
               file << "---------------------------------" << endl << endl;
               file << "--------------�����--------------" << endl;
               file << "������: ";
               file << "\t\t" << Human.Country.c_str() << endl;
               file << "����, ����, �����: ";
               file << "\t" << Human.Territory.c_str() << endl;
               file << "������: ";
               file << "\t\t" << Human.Index.c_str() << endl;
               file << "�����: ";
               file << "\t\t\t" << Human.City.c_str() << endl;
               file << "�����: ";
               file << "\t\t\t" << Human.Street.c_str() << endl;
               file << "���: ";
               file << "\t\t\t" << Human.House.c_str() << endl;
               file << "������: ";
               file << "\t\t" << Human.Corp.c_str() << endl;
               file << "��������: ";
               file << "\t\t" << Human.Flat.c_str() << endl;
               file << "---------------------------------" << endl << endl;
               file << "------�������������� ������------" << endl;
               file << "���� ��������: ";
               file << "\t\t" << Human.BirthDay.c_str() << endl;
               file << "��������� �������: ";
               file << "\t" << Human.MobileTelephone.c_str() << endl;
               file << "E - Mail: ";
               file << "\t\t" << Human.EMail.c_str() << endl;
               file << "ICQ: ";
               file << "\t\t\t" << Human.ICQ.c_str() << endl;
               file << "Nick: ";
               file << "\t\t\t" << Human.Nick.c_str() << endl;
               file << "����� ������: ";
               file << "\t\t" << Human.WorkPlace.c_str() << endl;
               file << "���������: ";
               file << "\t\t" << Human.Post.c_str() << endl;
               file << "����� ������: ";
               file << "\t\t" << Human.WAddress.c_str() << endl;
               file << "������� �������: ";
               file << "\t" << Human.WTelephone.c_str() << endl;
               file << "---------------------------------" << endl;
         file.close();
      }
}
/*/----------------------------------------------------------------------/*/
void __fastcall TPeopleInfoForm::ScreenResClick(TObject *Sender)
{
   AnsiString HelpString= "������� ���������� ������: " + AnsiString(Screen->Width) + " X " + (Screen->Height);
   Application->MessageBoxA( HelpString.c_str(),
                             "����������", MB_OK);
   if ((Screen->Width < 1280) && (Screen->Height < 1024))
      {
         Application->MessageBoxA("��������������� ���������� ������: 1280 � 1024", "��������", MB_OK);
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

