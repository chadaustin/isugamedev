#ifndef AINODE
#define AINODE

#include <queue>
#include <vector>


#include <iostream>

#include <AiQueue.h>
#include <InstinctManager.h>
#include <math.h>
#include <iostream>
#include <BehaviorMachine.h>
#include <Instinct.h>
#include <Action.h>
#include <AIManager.h>




/**
 * @AINode is a node in the AIsystems tree
 */
class AINode : public Subject
{
public:
	
   /** 
    * Constructor
    */
   AINode(std::string Name, int MaxChildren, int LevelInSystem){
      MyName = Name;
      MaxChild = MaxChildren;
      Level = LevelInSystem;

      /**
       * initialize instances of classes used by the AINode
       */
      aiqueue = new AiQueue;
      InstinctMan = new InstinctManager(aiqueue);
      MyAction = new Action(aiqueue);
   }

   /**
    * get the node's level in the system
    */
   int GetLevel() { return Level; }

   /** 
    * get the node's Maximum number of childern
    */
   int GetMaxChild(){ return MaxChild; }

   /**
    * return a pointer to the parent node
    */
   AINode* GetParent(){ return Parent; }

   /**
    * this method defines the process of how the node thinks?
    * first he cheks his instincts
    */
   void Update()
   {
      InstinctMan->InstinctsUpdate();
   }


public:
   /**
    * state information about our node in the AI system
    */
   int Level;
   int MaxChild;
   std::vector<AINode> Children;
   std::string MyName;
   AINode* Parent;

   /** 
    * @The five modules in a node: instinct, behaviorMachine, PriorityQueue, AImanager, action
    */
public:
   /**
    * This is the queue that the unit will follow 
    * @TODO: this needs to be changed to a priority queue
    */
   AiQueue* aiqueue;


   /**
    * flinch!
    * the instincts are what are checked every game cycle so should be 
    * as optimized as possible.  
    */
   InstinctManager* InstinctMan;
   
public:
   /**
    * it makes bees?
    * this is the state machine of behaviors that the node uses to control it's children 
    * @TODO: make it capable of outputing the states to it's children.
    */
   BehaviorMachine MyBMachine; 
   
   
   /**
    * Ben (my manager) is a prick!
    * This is the logic the state machine uses to make it's decision (this is where
    * the magic happens)
    */
   AIManager MyManager; 
   
   /**
    * Lights Camera ______!   
    * This is what tells the system which units need to be updated every cycle of the game
    */ 
   Action* MyAction; 

};

#endif
