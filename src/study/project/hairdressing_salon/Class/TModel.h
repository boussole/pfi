#ifndef TModel_H
#define TModel_H
//--------------
#include "Math.hpp"
//---------------------------------------------------------
enum TStatus{Free, Borrow, Rest};
//---------------------------------------------------------
//Sit channel Type
struct TChannelSit
{
   TChannelSit() {Status = Free; Timer = 0;}
   TStatus Status;
   size_t Timer;
};
//---------------------------------------------------------
//Sit waiting type
struct TWaitSit
{
   TWaitSit() {Status = Free; Timer = 0; Number = 0;}
   TStatus Status;
   size_t Number;
   size_t Timer;
};
//---------------------------------------------------------
struct THotHours
{
   THotHours() {Do = false; Begin = 0; Duration = 0;}
   bool Do;
   size_t Begin;
   size_t Duration;
};
//---------------------------------------------------------
struct TRest
{
   TRest() {Do = false; Begin = 0; Duration = 0;}
   bool Do;
   size_t Begin;
   size_t Duration;
};
//---------------------------------------------------------
class TModel
{
   public:
      TModel(TPictureBuffer *, TValueBuffer *, TValueBuffer *, TValueBuffer *, TArrayChannel<TChannel> *, TArrayChannel<TSit> *MBuffer, TArrayChannel<TLeave> *, size_t, size_t, size_t, THotHours, TRest *, size_t, TArrayChannel<TSit> *, TArrayChannel<TSit> *);
      ~TModel();
      bool Modelling();
      size_t NotTopHour(size_t);
      size_t TopHour(size_t);
      size_t Factorial(size_t);
      double Round(double);
      void CheckTimeOut();
      bool GetFreeChannel();
      bool GetFreeSit();
      bool GetRequest();
      void ServiceBegin();
      size_t GetTime(size_t);
      bool FiftyFifty(size_t);
      bool StayOrNot(size_t);
   private:
      size_t WorkTime, IndexCol, NCount, MCount, NBusyCount, MBusyCount, Number, NumberFreeChannel, NumberMinimalRequest, NumberFreeSit, Interval;
      TPictureBuffer *PictureBuffer;
      TValueBuffer *RBuffer, *LBuffer, *SBuffer;
      TArrayChannel<TChannel> *NBuffer;
      TArrayChannel<TSit> *MBuffer;
      TArrayChannel<TLeave> *Reject;
      TArrayChannel<TSit> *LeaveSys;
      TArrayChannel<TSit> *Fifteen;
      THotHours HotHours;
      bool Error, Hot, OnRest;
      //Channel Array
      TChannelSit *Channel;
      //Waiting Sit Array
      TWaitSit *Sit;
      //Rest of the channel
      TRest *RestChannel;
      TChannel StartService;
      TSit Waiting;
      TLeave LeaveSystem;
};
//---------------------------------------------------------
//Constructor
TModel :: TModel(TPictureBuffer *_P, TValueBuffer *_R, TValueBuffer *_L, TValueBuffer *_S, TArrayChannel<TChannel> *_N,
                 TArrayChannel<TSit> *_M, TArrayChannel<TLeave> *_Reject, size_t _NCount, size_t _MCount, size_t _WorkTime,
                 THotHours _HotHours, TRest *_RestChannel, size_t _Interval, TArrayChannel<TSit> *_LeaveSystem, TArrayChannel<TSit> *_Fifteen)
{
   PictureBuffer = _P;
   RBuffer = _R;
   LBuffer = _L;
   SBuffer = _S;
   NBuffer = _N;
   MBuffer = _M;
   NCount = _NCount;
   MCount = _MCount;
   Reject = _Reject;
   IndexCol = 1;
   WorkTime = _WorkTime;
   Error = false;
   NBusyCount = 0;
   MBusyCount = 0;
   HotHours = _HotHours;
   Hot = false;
   Number = 1;
   RestChannel = _RestChannel;
   OnRest = false;
   NumberFreeChannel = 0;
   NumberMinimalRequest = 0;
   NumberFreeSit = 0;
   Interval = _Interval;
   LeaveSys = _LeaveSystem;
   Fifteen = _Fifteen;
   //-------------------
   //Dynamic variables
   Channel = NULL;
   Channel = new TChannelSit[NCount];
   Sit = NULL;
   if (MCount != 0)
   {
      Sit = new TWaitSit[MCount];
   }
}
//---------------------------------------------------------
//Destructor
TModel :: ~TModel()
{
   if (Channel != NULL) {delete []Channel; Channel = NULL;}
   if (Sit != NULL) {delete []Sit; Sit = NULL;}
}
//---------------------------------------------------------
//Modelling of the Hairdressing Salon
bool TModel :: Modelling()
{
   //-----------
   //Create Left Table
   for (size_t j = 0; j < (4 + NCount + MCount); j++)
      {
         if (PictureBuffer->Add())
            {
               PictureBuffer->SetKind(j, Table);
               PictureBuffer->SetType(j, Table_Menu);
            }
         else
            {
               Error = true;
               break;
            }
      }
   if (Error) {return Error;}
   //-----------
   //Modelling other time
   while (IndexCol <= WorkTime)
      {
         //-----------------
         //Create the objects
         for (size_t j = 0; j < (4 + NCount + MCount); j++)
            if (!PictureBuffer->Add())
            {
               Error = true;
               break;
            }
         //---------
         //Create N - menu
         PictureBuffer->SetKind((IndexCol * (4 + NCount + MCount)), Table);
         PictureBuffer->SetType((IndexCol * (4 + NCount + MCount)), Table_N);
         //---------
         //Create r - menu
         PictureBuffer->SetKind(((IndexCol * (4 + NCount + MCount)) + 1), Table);
         PictureBuffer->SetType(((IndexCol * (4 + NCount + MCount)) + 1), Table_R);
         RBuffer->Add(rand() % 100);
         //---------
         //Create l - menu
         PictureBuffer->SetKind(((IndexCol * (4 + NCount + MCount)) + 2), Table);
         PictureBuffer->SetType(((IndexCol * (4 + NCount + MCount)) + 2), Table_l);
         //---------
         //Calculate Hot Hours
         if ((HotHours.Do) && (HotHours.Begin  + 1 == IndexCol))
            {
               Hot = true;
            }
         if (IndexCol - HotHours.Begin  > HotHours.Duration)
            {
               Hot = false;
            }
         //---------
         if (Hot)
            {LBuffer->Add(TopHour((*RBuffer)[IndexCol - 1]));}
         else
            {LBuffer->Add(NotTopHour((*RBuffer)[IndexCol - 1]));}
         //---------
         //Check channel's status. if channel is free, then check timeout time
         //---------
         for (size_t j = 0; j < NCount; j++)
            {
               //Decrement of the working time
               if (Channel[j].Status != Free)
                  {
                     Channel[j].Timer -= 1;
                  }
               //Free the channel ...
               if (Channel[j].Timer == 0)
                  {
                     PictureBuffer->SetKind(((IndexCol * (4 + NCount + MCount)) + 3 + j), Graphic);
                     PictureBuffer->SetType(((IndexCol * (4 + NCount + MCount)) + 3 + j), Graphic_n);
                     //-------------
                     switch (Channel[j].Status)
                        {
                           case (Free):   PictureBuffer->SetStatus(((IndexCol * (4 + NCount + MCount)) + 3 + j), Empty);
                                          break;
                           //----------
                           case (Rest):   PictureBuffer->SetStatus(((IndexCol * (4 + NCount + MCount)) + 3 + j), Empty);
                                          NBusyCount--;
                                          OnRest = false;
                                          Channel[j].Status = Free;
                                          break;
                           //----------
                           case (Borrow): PictureBuffer->SetStatus(((IndexCol * (4 + NCount + MCount)) + 3 + j), Finish);
                                          NBusyCount--;
                                          Channel[j].Status = Free;
                                          break;
                        };
                  }
               else
                  {
               //or continue the service
                     PictureBuffer->SetKind(((IndexCol * (4 + NCount + MCount)) + 3 + j), Graphic);
                     switch (Channel[j].Status)
                        {
                           case (Borrow): {
                                             PictureBuffer->SetType(((IndexCol * (4 + NCount + MCount)) + 3 + j), Graphic_n);
                                             PictureBuffer->SetStatus(((IndexCol * (4 + NCount + MCount)) + 3 + j), Continue);
                                             break;
                                          }
                           //--------
                           case (Rest):   {
                                             PictureBuffer->SetType(((IndexCol * (4 + NCount + MCount)) + 3 + j), TimeOut);
                                             break;
                                          }
                        };
                  }
            }
         //Check the Timout, if other channels is working
         CheckTimeOut();
         //---------
         //Service of the waiting transacts
         //---------
         //Search Free Channels
         while ((GetRequest()) && (GetFreeChannel()))
            {
               PictureBuffer->SetStatus(((IndexCol * (4 + NCount + MCount)) + 3 + NumberFreeChannel), Start);

               StartService.Step = IndexCol;
               StartService.Number = Sit[NumberMinimalRequest].Number;
               StartService.RandomValue = rand() % 100;
               StartService.Time = GetTime(StartService.RandomValue) / Interval;
               NBuffer[NumberFreeChannel].Add(StartService);

               Channel[NumberFreeChannel].Status = Borrow;
               Channel[NumberFreeChannel].Timer = StartService.Time;

               Sit[NumberMinimalRequest].Status = Free;
               Sit[NumberMinimalRequest].Number = 0;
               Sit[NumberMinimalRequest].Timer = 0;

               PictureBuffer->SetKind(((IndexCol * (4 + NCount + MCount)) + 3 + NCount + NumberMinimalRequest), Graphic);
               PictureBuffer->SetType(((IndexCol * (4 + NCount + MCount)) + 3 + NCount + NumberMinimalRequest), Graphic_m);
               PictureBuffer->SetStatus(((IndexCol * (4 + NCount + MCount)) + 3 + NCount + NumberMinimalRequest), Finish);

               NBusyCount++;
               MBusyCount--;
            }
         //---------
         for (size_t j = 0; j < MCount; j++)
            {
               //Decrement the timer
               if (Sit[j].Status != Free)
                  {
                     Sit[j].Timer -= 1;
                  }
               //Free or Continue the sit ...
               if (Sit[j].Timer == 0)
                  {
                     PictureBuffer->SetKind(((IndexCol * (4 + NCount + MCount)) + 3 + NCount + j), Graphic);
                     PictureBuffer->SetType(((IndexCol * (4 + NCount + MCount)) + 3 + NCount + j), Graphic_m);
                     //-------------
                     switch (Sit[j].Status)
                        {
                           case (Free):   PictureBuffer->SetStatus( ((IndexCol * (4 + NCount + MCount)) + 3 + NCount + j), (PictureBuffer->GetStatus( ((IndexCol * (4 + NCount + MCount)) + 3 + NCount + j)) | Empty)  );
                                          break;
                           //----------
                           // > 15
                           case (Borrow):
                                          Waiting.RandomValue = rand() % 100;
                                          Waiting.Step = IndexCol;
                                          Waiting.Number = Sit[j].Number;
                                          if (!FiftyFifty(Waiting.RandomValue))
                                             {
                                                PictureBuffer->SetStatus(((IndexCol * (4 + NCount + MCount)) + 3 + NCount + j), Finish);
                                                PictureBuffer->SetLeave(((IndexCol * (4 + NCount + MCount)) + 3 + NCount + j), Desire);
                                                Fifteen[j].Add(Waiting);
                                                MBusyCount--;
                                                Sit[j].Status = Free;
                                                Sit[j].Number = 0;
                                                Sit[j].Timer = 0;
                                             }
                                          else
                                             {
                                                PictureBuffer->SetStatus(((IndexCol * (4 + NCount + MCount)) + 3 + NCount + j), Start);
                                                Sit[j].Timer = 3;
                                                MBuffer[j].Add(Waiting);
                                             }
                                          break;
                        };
                  }
               else
                  {
                  //or continue the Waiting
                     PictureBuffer->SetKind(((IndexCol * (4 + NCount + MCount)) + 3 + NCount + j), Graphic);
                     PictureBuffer->SetType(((IndexCol * (4 + NCount + MCount)) + 3 + NCount + j), Graphic_m);
                     PictureBuffer->SetStatus(((IndexCol * (4 + NCount + MCount)) + 3 + NCount + j), Continue);
                  }
            }
         //---------
         //Service of the come transacts
         //---------
         for (size_t i = 0; i < (*LBuffer)[IndexCol - 1]; i++)
            {
               //Go to the Service
               if (GetFreeChannel())
                  {
                     PictureBuffer->SetStatus(((IndexCol * (4 + NCount + MCount)) + 3 + NumberFreeChannel), Start);

                     StartService.Step = IndexCol;
                     StartService.Number = Number;
                     StartService.RandomValue = rand() % 100;
                     StartService.Time = GetTime(StartService.RandomValue) / Interval;
                     NBuffer[NumberFreeChannel].Add(StartService);

                     Channel[NumberFreeChannel].Status = Borrow;
                     Channel[NumberFreeChannel].Timer = StartService.Time;
                     NBusyCount++;
                  }
               //Go to wait
               else
                  {
                     if (GetFreeSit())
                        {
                           Waiting.Step = IndexCol;
                           Waiting.Number = Number;
                           Waiting.RandomValue = rand() % 100;
                           if (StayOrNot(Waiting.RandomValue))
                              {
                                 PictureBuffer->SetStatus(((IndexCol * (4 + NCount + MCount)) + 3 + NCount + NumberFreeSit), Start);
                                 MBuffer[NumberFreeSit].Add(Waiting);
                                 Sit[NumberFreeSit].Number = Number;
                                 Sit[NumberFreeSit].Status = Borrow;
                                 Sit[NumberFreeSit].Timer = 3;
                                 MBusyCount++;
                              }
                           else
                              {
                                 PictureBuffer->SetLeave(((IndexCol * (4 + NCount + MCount)) + 3 + NCount + NumberFreeSit), Desire);
                                 LeaveSys[MBusyCount].Add(Waiting);
                              }
                        }
                     //Leave the System
                     else
                        {
                           PictureBuffer->SetLeave(((IndexCol * (4 + NCount + MCount)) + 2 + NCount + MCount), (PictureBuffer->GetLeave((IndexCol * (4 + NCount + MCount)) + 2 + NCount + MCount)) | Rejection);
                           LeaveSystem.Step = IndexCol;
                           LeaveSystem.Number = Number;
                           (*Reject).Add(LeaveSystem);
                        }
                  }
               Number++;
            }
         //---------
         //Calc S - Status of the system
         //---------
         PictureBuffer->SetKind(((IndexCol * (4 + NCount + MCount)) + 3 + NCount + MCount), Table);
         PictureBuffer->SetType(((IndexCol * (4 + NCount + MCount)) + 3 + NCount + MCount), Table_S);
         if ((OnRest) && (MBusyCount > 0))
            SBuffer->Add(NBusyCount + MBusyCount + NCount + MCount);
         else
            SBuffer->Add(NBusyCount + MBusyCount);
         //---------
         IndexCol++;
      }
   //After close the salon
   if (Error) {return Error;}
   while (NBusyCount != 0)
      {
         //-----------------
         //Create the objects
         for (size_t j = 0; j < (4 + NCount + MCount); j++)
            if (!PictureBuffer->Add())
            {
               Error = true;
               break;
            }
         if (MBusyCount > 0)
         {
         for (size_t j = 0; j < MCount; j++)
            {
               if (Sit[j].Status != Free)
                  {
                     PictureBuffer->SetKind(((IndexCol * (4 + NCount + MCount)) + 3 + NCount + j), Graphic);
                     PictureBuffer->SetType(((IndexCol * (4 + NCount + MCount)) + 3 + NCount + j), Graphic_m);
                     PictureBuffer->SetStatus(((IndexCol * (4 + NCount + MCount)) + 3 + NCount + j), Finish);
                     PictureBuffer->SetLeave(((IndexCol * (4 + NCount + MCount)) + 3 + NCount + j), Desire);
                     MBusyCount--;
                     Sit[j].Status = Free;
                     Sit[j].Number = 0;
                     Sit[j].Timer = 0;
                  }
            }
         }
         //---------
         //Create N - menu
         PictureBuffer->SetKind((IndexCol * (4 + NCount + MCount)), Table);
         PictureBuffer->SetType((IndexCol * (4 + NCount + MCount)), Table_N);
         //---------
         //Create r - menu
         PictureBuffer->SetKind(((IndexCol * (4 + NCount + MCount)) + 1), Table);
         PictureBuffer->SetType(((IndexCol * (4 + NCount + MCount)) + 1), Table_R);
         RBuffer->Add(0);
         //---------
         //Create l - menu
         PictureBuffer->SetKind(((IndexCol * (4 + NCount + MCount)) + 2), Table);
         PictureBuffer->SetType(((IndexCol * (4 + NCount + MCount)) + 2), Table_l);
         LBuffer->Add(0);
         //----------------
         //Work the channel
         for (size_t j = 0; j < NCount; j++)
            {
            //Decrement of the working time
               if (Channel[j].Status != Free)
                  {
                     Channel[j].Timer -= 1;
                  }
               //Free the channel ...
               if (Channel[j].Timer == 0)
                  {
                     PictureBuffer->SetKind(((IndexCol * (4 + NCount + MCount)) + 3 + j), Graphic);
                     PictureBuffer->SetType(((IndexCol * (4 + NCount + MCount)) + 3 + j), Graphic_n);
                     //-------------
                     switch (Channel[j].Status)
                        {
                           case (Free):   PictureBuffer->SetStatus(((IndexCol * (4 + NCount + MCount)) + 3 + j), Empty);
                                          break;
                           //----------
                           case (Rest):   PictureBuffer->SetStatus(((IndexCol * (4 + NCount + MCount)) + 3 + j), Empty);
                                          NBusyCount--;
                                          OnRest = false;
                                          Channel[j].Status = Free;
                                          break;
                           //----------
                           case (Borrow): PictureBuffer->SetStatus(((IndexCol * (4 + NCount + MCount)) + 3 + j), Finish);
                                          NBusyCount--;
                                          Channel[j].Status = Free;
                                          break;
                        };
                  }
               else
                  {
               //or continue the service
                     PictureBuffer->SetKind(((IndexCol * (4 + NCount + MCount)) + 3 + j), Graphic);
                     switch (Channel[j].Status)
                        {
                           case (Borrow): {
                                             PictureBuffer->SetType(((IndexCol * (4 + NCount + MCount)) + 3 + j), Graphic_n);
                                             PictureBuffer->SetStatus(((IndexCol * (4 + NCount + MCount)) + 3 + j), Continue);
                                             break;
                                          }
                           //--------
                           case (Rest):   {
                                             PictureBuffer->SetType(((IndexCol * (4 + NCount + MCount)) + 3 + j), TimeOut);
                                             break;
                                          }
                        };
                  }
            }
         //----------------
         //Create m
         for (size_t j = 0; j < MCount; j++)
            {
                 PictureBuffer->SetKind(((IndexCol * (4 + NCount + MCount)) + 3 + NCount + j), Graphic);
                 PictureBuffer->SetType(((IndexCol * (4 + NCount + MCount)) + 3 + NCount + j), Graphic_m);
                 PictureBuffer->SetStatus(((IndexCol * (4 + NCount + MCount)) + 3 + NCount + j), Empty);
            }
         //----------------
         //Create S
         PictureBuffer->SetKind(((IndexCol * (4 + NCount + MCount)) + 3 + NCount + MCount), Table);
         PictureBuffer->SetType(((IndexCol * (4 + NCount + MCount)) + 3 + NCount + MCount), Table_S);
         SBuffer->Add(NBusyCount + MBusyCount);
         IndexCol++;
      }
   if (Error) {return Error;}
   //-----------
   return Error;
}
//---------------------------------------------------------
//Count of the came transacts in not top hours
size_t TModel :: NotTopHour(size_t Value)
{
   //e ^ 0.5 ~= 0.6
   double LowLimit = 0, HighLimit = 0;
   for (size_t l = 0; l < 4; l++)
      {
         HighLimit = Round(LowLimit + (((Power(0.5, l)) / Factorial(l))) * 0.6 * 100);
         if ( (Value >= LowLimit) && (Value < HighLimit) )
            {
               return l;
            }
         else
            {
               LowLimit = HighLimit;
            }
      }
   return 3;
}
//---------------------------------------------------------
//Count of the came transacts in top hours
size_t TModel :: TopHour(size_t Value)
{
   //e ^ 1 ~= 0.37
   double LowLimit = 0, HighLimit = 0;
   for (size_t l = 0; l < 5; l++)
      {
         HighLimit = (LowLimit + (((Power(1, l)) / Factorial(l))) *  0.36764705 * 100);
         if ( (Value >= Round(LowLimit)) && (Value < Round(HighLimit)) )
            {
               return l;
            }
         else
            {
               LowLimit = HighLimit;
            }
      }
   return 4;
}
//---------------------------------------------------------
//Factorial
size_t TModel :: Factorial(size_t Value)
{
   size_t Help = 1;
   if (Value == 0) {return 1;}
   for (size_t i = 1; i <= Value; i++)
      {
         Help *= i;
      }
   return Help;
}
//---------------------------------------------------------
//Round
double TModel :: Round(double Value)
{
   size_t HelpInt = Value;
   double HelpDouble =  (Value / (double)HelpInt);
   if (HelpDouble > 1)
      {return (HelpInt + 1);}
   else
      {return Value;}
}
//---------------------------------------------------------
void TModel :: CheckTimeOut()
{
   size_t NumberChannel;
   bool found = false;
   if (!OnRest)
      {
         for (size_t j = 0; j < NCount; j++)
            {
               if ((RestChannel[j].Do) && (!found) && (RestChannel[j].Begin <= IndexCol - 1) && (Channel[j].Status == Free))
                  {
                     NumberChannel = j;
                     found = true;
                  }
               if (
                     (found)
                     &&
                     (RestChannel[j].Do)
                     &&
                     (Channel[j].Status == Free)
                     &&
                     (RestChannel[j].Begin < RestChannel[NumberChannel].Begin))
                  {
                     NumberChannel = j;
                  }
            }
               if (found)
                  {
                     RestChannel[NumberChannel].Do = false;
                     Channel[NumberChannel].Status = Rest;
                     Channel[NumberChannel].Timer = RestChannel[NumberChannel].Duration;
                     OnRest = true;
                     NBusyCount++;
                     PictureBuffer->SetKind(((IndexCol * (4 + NCount + MCount)) + 3 + NumberChannel), Graphic);
                     PictureBuffer->SetType(((IndexCol * (4 + NCount + MCount)) + 3 + NumberChannel), TimeOut);
                     found = false;
                  }
      }
}
//---------------------------------------------------------
//Return Number of the free channel
bool TModel :: GetFreeChannel()
{
   bool found = false;
   for (size_t i = 0 ; i < NCount; i++)
      {
         if (Channel[i].Status == Free)
            {
               NumberFreeChannel = i;
               found = true;
               break;
            }
      }
   return found;
}
//---------------------------------------------------------
//Return Number of the Free Sit
bool TModel :: GetFreeSit()
{
   bool found = false;
   for (size_t i = 0 ; i < MCount; i++)
      {
         if (Sit[i].Status == Free)
            {
               NumberFreeSit = i;
               found = true;
               break;
            }
      }
   return found;
}
//---------------------------------------------------------
//Return Number of the waiting Sit, Who will be go to the service
bool TModel :: GetRequest()
{
   bool found = false;
   //Search first Request
   for (size_t i = 0; i < MCount; i++)
      {
         if (Sit[i].Status == Borrow)
            {
               NumberMinimalRequest = i;
               found = true;
               break;
            }
      }
   //Search minimal Request
   if (found)
      {
         for (size_t i = NumberMinimalRequest; i < MCount; i++)
            {
               if ((Sit[i].Status == Borrow) && (Sit[i].Number < Sit[NumberMinimalRequest].Number))
                  {
                     NumberMinimalRequest = i;
                  }
            }
      }
   return found;
}
//---------------------------------------------------------
//Return Time of the Service
size_t TModel :: GetTime(size_t Value)
{
   if ((Value >= 0) && (Value <= 6))
      {return 10;}
   if ((Value >= 7) && (Value <= 30))
      {return 15;}
   if ((Value >= 31) && (Value <= 68))
      {return 20;}
   if ((Value >= 69) && (Value <= 92))
      {return 25;}
   if ((Value >= 93) && (Value <= 98))
      {return 30;}
   if (Value == 99)
      {return 35;}
}
//---------------------------------------------------------
//>15
bool TModel :: FiftyFifty(size_t Value)
{
   if ((0 <= Value) && (Value <= 49)) {return false;}
   else {return true;}
}
//---------------------------------------------------------
bool TModel :: StayOrNot(size_t Value)
{
   //R1 =
   if (MBusyCount == 0)
      {
         if ((Value >= 0) && (Value <= 9))
            {return false;}
         else
            {return true;}
      }
   //R2 = > 1 free sit
   if ((MBusyCount >= 1) && (MBusyCount < MCount - 1))
      {
         if ((Value >= 0) && (Value <= 29))
            {return false;}
         else
            {return true;}
      }
   //R3 = last free sit
   if (MBusyCount == MCount - 1)
      {
         return (FiftyFifty(Value));
      }
}
//---------------------------------------------------------
#endif
