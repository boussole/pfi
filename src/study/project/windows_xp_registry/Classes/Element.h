#ifndef Element_h
#define Element_h
/*/-------------------------------------------/*/
enum Ttype{Binary, Dword, ExpandSz, MultiSz, Sz};
/*/-------------------------------------------/*/
   struct TElement
      {
         HKEY Root;         //�������� �����
         AnsiString Key;    //���� � �����
         AnsiString Data;   //������� ������
         Ttype Type;        //��� �������� ������
         AnsiString Value;  //��������
      };
/*/-------------------------------------------/*/
#endif
