#include "NavNodeTree.h"


namespace mw
{
   
   NavNodeTree::NavNodeTree()
   {
   
   }
   

   bool NavNodeTree::addNode(Node* newNode)
   {
      Tree.push_back(newNode);
      for(int i=0;i<newNode->links.size();i++)
      {
         newNode->links[i]->links.push_back(newNode);
      }
      return true;
   }


   bool NavNodeTree::addLink(std::string node1, std::string node2)
   {
      Node* n1, *n2;
      for(int i=0;i<Tree.size();i++)
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
      }else
      {
         
         n1->links.push_back(n2);
         n2->links.push_back(n1);
         return true;
      }
   }


   std::vector<Node*>* NavNodeTree::allLinks(std::string node)
   {
      Node* n;
   //   std::vector<Node*>* nodes = new std::vector<Node*>;
      for(int i=0;i<Tree.size();i++)
      {
         if(Tree[i]->name == node)
         {
            n = Tree[i];
            i=Tree.size();
         }
         
      }
      return &n->links;
   }


}
