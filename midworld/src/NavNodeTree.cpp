#include "NavNodeTree.h"


namespace mw
{
   
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
