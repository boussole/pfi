enum HEl{X, Y, Z, None};
/*/������ �������/*/
struct Row
   {
      Row();
      HEl Id;
      LDouble x;
      LDouble y;
      LDouble z;
      LDouble b;
   };
Row::Row()
   {
      Id = None;
   }

 