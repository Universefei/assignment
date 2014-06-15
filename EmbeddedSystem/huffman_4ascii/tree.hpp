#ifndef TREE_HPP
#define TREE_HPP

#include <queue>
#include <map>

#include "node.hpp"

class tree
{
   public:
	  /* constructor */
      tree(const std::map<char, int> histo);
	  /* destructor */
      ~tree();
      node* rootnode() const;

   private:
      node *root;

	  /* sort alogrithm is determined via function class node_comp */
	  /* node_comp is compare node's weight */
	  /* before building tree, nodes real data are stored in priority_queue */

	  /* after create tree, priority is invalid, we just use root pointer
	   * to manipulate each node
	   */

	  /* std::priority_queue template parameters:
	   * ========================================
	   * 1] the type of elements
	   * 2] optional. the container that the priority queue uses internally for
	   *    its elements
	   * 3] the sorting criterion
	   */
      std::priority_queue<node*, std::vector<node*>, node_comp> leaves;
      void create_tree();

	  /* copy constructor */
      tree(const tree &t);
      tree& operator=(const tree &rhs);
};

#endif // TREE_HPP
