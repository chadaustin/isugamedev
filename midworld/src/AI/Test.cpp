#include <iostream>
#include <vector>
#include "AISystem.h"
#include "Instinct.h"
#include "Behavior.h"
#include "Unit.h"
#include "Shoot.h"
#include "BoolBehavior.h"

int main(int argc, char* argv[])
{
   AISystem AI;
   std::string Unit1 = "Ben";
   std::string Unit2 = "Chad";
   std::string Unit3 = "Kevin";
   std::string Unit4 = "Jon";
   std::string Unit5 = "Andres";
   AINode Node1(Unit1, -1, 1);
   AINode Node2(Unit2, -1, 1);
   AINode Node3(Unit3, -1, 1);
   AINode Node4(Unit4, -1, 1);
   AINode Node5(Unit5, -1, 1);
  
   Behavior* First;
   Behavior* Second;
   
   Behavior* Third;
   Behavior* Fourth;

   

   BehaviorFactory B;
   Shoot S;
   
   First = CreateBehavior(S);
   Second = CreateBehavior(B);
   
   BoolBehavior Test;
   BoolBehavior Test2;
 //  Test2.SetFalse();
  
   Instinct* Shooting = new Instinct(Node2.InstinctMan, *First, Test);
   Instinct* Shooting2 = new Instinct(Node1.InstinctMan, *Second, Test2);
   
   AI.RegisterNode(Node1);
   AI.RegisterNode(Node2);
   AI.RegisterNode(Node3);
   AI.RegisterNode(Node4);
   AI.RegisterNode(Node5);



   

   AI.Update();
   AI.Update();
   AI.Update();
   


   std::cout<<"Done! Press any key to continue!"<<std::endl;
   std::cin.get();
 	return 0;
}