#ifndef MW_DROID_H
#define MW_DROID_H

#include <gmtl/Generate.h>

#include "Enemy.h"
#include "NavNodeTree.h"


namespace mw
{
   class Droid: public Enemy
   {
   public:
      Droid(GameState* gameState);
      ~Droid();

      void update(float dt);

      void shoot();

      float getTimeDelta();
      
      Weapon* getGun();
      
      void walkRandom();
      void rotate();
      
      void setFuckedFlag(bool b){ fuckedFlag = b; }
      bool getFuckedFlag(){ return fuckedFlag; }
      
      void setGoalNode(Node* node){goalNode = node; }
      Node* getGoalNode(){ return goalNode; }
      Node* getFakeNode(){return fakeNode;}
      void setFakeNode(gmtl::Vec3f pos){fakeNode->loc = pos; }
      Node* getCurrentNode(){ return currentNode; }
      void setCurrentNode(Node* node){ currentNode = node; }
      NavNodeTree* getTree(){ return mTree; }
      void setTree(NavNodeTree* t){mTree = t;}
      void setWasFuckedFlag(bool b){ wasFuckedFlag = b; }
      bool getWasFuckedFlag(){ return wasFuckedFlag; }
      void setFirstTimeFlag(bool b){ firstTimeFlag = b; }
      bool getFirstTimeFlag(){ return firstTimeFlag; }
      
   private:
      float timeDelta;
      Weapon* gun;
      // this flag is set when we are not doing what we are not traversing a 
      // path between two nodes.  Or more accurately it gets set when we start 
      // chasing the player.  
      bool fuckedFlag;

      // flag to help us with finding our way back to a node after we finish
      // chasing a player
      bool wasFuckedFlag;

      
      // flag for testing whether or not we should reset the velocity of the
      // droid to zero
      bool firstTimeFlag;
      
      // we keep a reference to 2 nodes the node we are comming from and the
      // node that we are going to
      Node* goalNode;
      Node* currentNode;
      
      // we also need to know about the navNodeTree
      NavNodeTree* mTree;

      //HACK: if we ever deviate from a path between 2 nodes then we no longer
      //can just interpelate between those 2 nodes, we are required to keep a
      //location in memory of a new "fake" node at our current location, so that
      //as soon as we want to return to a node we can then interpelate between
      //this fake node and our goal node.  Therefore we are required to keep the
      //following node (Arg, this sucks)
      Node* fakeNode;
   };
}

#endif
