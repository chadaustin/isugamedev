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
   class Node
   {
   public:
      Node()
      {
         loc[0]=loc[1]=loc[2]=0.0f;
         name = "unknown";
      }
      Node(std::string n)
      {
         Node();
         name = n;
      }
      gmtl::Vec3f getLoc(){ 
         std::cout << "in getLoc" << std::endl;
         std::cout << name << std::endl;
         std::cout << loc[0] << std::endl;
         return loc; }
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
       * constructor
       */
      NavNodeTree()
      {
         Tree.clear();
      }

      /** 
       * a method that allows us to query the tree for the closest node 
       * to a given point
       */
      Node* findNearestNavNode(gmtl::Vec3f pos);
      
      /**
       * adds a node to the tree
       * returns true if successfully added node
       *
       * This is inline because VC7 is pissing me off and won't
       * link if it's not inline.  :(
       */
      void addNode(Node* newNode)
      {
         std::cout << "pushing newNode onto Tree" << std::endl;
         Tree.push_back(newNode);
         std::cout << "Tree.begin()->name = "<< Tree[0]->getLoc()[0] << std::endl;
         for(unsigned int i=0;i<newNode->links.size();i++)
         {
            newNode->links[i]->links.push_back(newNode);
         }
         std::cout << "Tree.size(): " << Tree.size() << std::endl;
      }

      /** 
       * adds a link between two nodes
       * returns true if sucessful
       */
      bool addLink(const std::string& node1, const std::string& node2);
      
      /** 
       * removes a node 
       * the specified node must not have any links currently 
       * active.  returns false if there are still links alive.
       */
      bool removeNode(const std::string& name);
      
      /**
       * returns a reference to a vector containing references to all the 
       * nodes that node has a link to.
       */
      std::vector<Node*>& allLinks(const std::string& node);
      
      std::vector<Node*>& getTree(){ return Tree; }
   private:
      std::vector<Node*> Tree;
   };

      
} // namespace mw     

#endif
