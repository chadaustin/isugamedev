#ifndef MW_NAV_NODE_TREE_H
#define MW_NAV_NODE_TREE_H

#include <iostream>
#include <gmtl/Generate.h>
#include <vector>
#include <string>


namespace mw
{


   /**
    * structure to make it easier to deal with Nodes.
    */
   struct Node
   {
      std::string name;
      gmtl::Vec3f loc;
      std::vector<Node*> links;
   };

   /**
    * class to handle the navigation capabilities of the driods
    */
   class NavNodeTree
   {
   public:   
      /**
       * adds a node to the tree
       * returns true if successfully added node
       */
      bool addNode(Node* newNode);
      
      /** 
       * adds a link between two nodes
       * returns true if sucessful
       */
      bool addLink(std::string node1, std::string node2);
      
      /** 
       * removes a node 
       * the specified node must not have any links currently 
       * active.  returns false if there are still links alive.
       */
      bool removeNode(std::string name);
      
      /**
       * returns a reference to a vector containing references to all the 
       * nodes that node has a link to.
       */
      std::vector<Node*>* allLinks(std::string node);
      
   private:
      std::vector<Node*> Tree;
   };

      
} // namespace mw     

#endif
