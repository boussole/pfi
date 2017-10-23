#ifndef Element_h
#define Element_h
/*/-------------------------------------------/*/
enum Ttype{Binary, Dword, ExpandSz, MultiSz, Sz};
/*/-------------------------------------------/*/
   struct TElement
      {
         HKEY Root;         //название корня
         AnsiString Key;    //путь к ключу
         AnsiString Data;   //элемент данных
         Ttype Type;        //тип элемента данных
         AnsiString Value;  //значение
      };
/*/-------------------------------------------/*/
#endif
