#ifndef AISYSTEM
#define AISYSTEM


#include <list>
#include <vector>

#include "Observer.h"
#include "AINode.h"
#include "InstinctManager.h"

namespace mw
{

class AISystem
{
public:
   /**
    * Constructor
    */
   AISystem(){};


   /** 
    * returns the total number of nodes in the system
    */
   int NumOfNodes(){ return NodeList.size(); }

   /** 
    * returns the number of nodes at level
    * @TODO: until we implement this with a tree, this method will return 0
    */
   int NumOfNodes(int Level){ return 0; }
   
   /**
    * registers a node with teh system
    * @TODO - at the very least figure this out so we are more efficient: 
    * we need an n-array tree instead of a vector, but once we have one
    * we will need to modify this to look at the parent node and then add it as a 
    * child of that parent (if there is room ... error checking etc -- definentially
    * a prototype - in the mean time we are just going to push it into our tree.
    */
   void RegisterNode(AINode Node){ NodeList.push_back(Node); }

   
   /**
    * The update function is what gets called every game cycle - so this
    * should get called from in your games update function. 
    * It works by iterating through all the nodes that are in the system checking
    * all their instincts, updating their behavior managers, updating the AIqueue
    * and performing the current action.  
    */
   void Update(){ 
      // put an iterator here and update all instincts in nodeList   

        std::vector<AINode>* Nodes = &NodeList;
        for(std::vector<AINode>::iterator itr = Nodes->begin(); itr != Nodes->end(); itr++)
      {
         (*itr).Update();
      }


   }

   std::vector<AINode>* GetNodeList()
   {
      return &NodeList;
   }


private:

   /**
    * @TODO - maybe: change this so we use an n-arry tree not a list
    */
   std::vector<AINode> NodeList;
  
};

}

#endif

