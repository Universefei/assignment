#include "tree.hpp"

tree::tree(const std::map<char, int> histo) {
   /* auto is awesome, we needn't specify variable type */
   /* ++it is more efficient than it++ */
   for (auto it = histo.begin(); it != histo.end(); ++it) {
      leaves.push(new leaf(it->first, it->second));
   }
   create_tree();
}

tree::~tree() {
   delete root;
}


/******************************************************************************
 *                           build huffman tree                               *
 *****************************************************************************/

void 
tree::create_tree() {
   /* select the most minimum 2 node */
   node *right = leaves.top();   
   leaves.pop();

   node *left = leaves.top();    
   leaves.pop();

   /* merge them to a branch and add branch node to priority_queue */
   branch *parent = new branch(left, right);
   leaves.push(parent);

   /* check if over */
   if (leaves.size() < 2) {
      root = parent;
   }
   else {
	  /* recursive */
      create_tree();
   }
}


node* 
tree::rootnode() const {
   return root;
}
