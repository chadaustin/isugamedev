#include "NavNodeTree.h"



namespace mw
{
   
   Node* NavNodeTree::findNearestNavNode(gmtl::Vec3f pos)
   {
      float nearestDist=10000000;
      
      float testDist;
      Node* nearestNode=NULL;
      for(int i=0;i<Tree.size();i++)
      {
         if((testDist = (Tree[i]->loc[0]-pos[0])*(Tree[i]->loc[0]-pos[0])+
         (Tree[i]->loc[2]-pos[2])*(Tree[i]->loc[2]-pos[2]))<=nearestDist)
         {
            nearestDist = testDist;
            nearestNode = Tree[i];
         }
      }
      return nearestNode;
   }
   

   bool NavNodeTree::addLink(const std::string& node1, const std::string& node2)
   {
      Node* n1 = 0;
      Node* n2 = 0;;
      for(unsigned int i=0;i<Tree.size();i++)
      {
         if(Tree[i]->name == node1)
         {
            n1 = Tree[i];
         }
         else if(Tree[i]->name == node2)
         {
            n2 = Tree[i];
         }
      }
      if(n1==NULL || n2==NULL)
      {
         return false;
      }
      else
      {
         n1->links.push_back(n2);
         n2->links.push_back(n1);
         return true;
      }
   }


   std::vector<Node*>& NavNodeTree::allLinks(const std::string& node)
   {
      Node* n = 0;
      for(unsigned int i=0;i<Tree.size();i++)
      {
         if(Tree[i]->name == node)
         {
            n = Tree[i];
            break;
         }
      }
      if (n)
      {
         return n->links;
      }
      else
      {
         static std::vector<Node*> empty;
         return empty;
      }
   }
}
