#ifndef NODE_HPP
#define NODE_HPP

#include <functional>
#include <typeinfo>
#include <iostream>

enum struct nodetype: bool
{
   BRANCH,
   LEAF
};

/*---------------------------------------------------------------------------*/
/*                             base class                                    */
/*---------------------------------------------------------------------------*/

/** What's differences between class and struct in C++ Language?
 *  ============================================================
 *  1] default access authority varies.
 *  2] Class defaultly has private access if not specified.
 *  3] Struct defaultly has public access if not specified.
 */

struct node
{
      int weight; /* frequency info not value  */
      node *left;
      node *right;

	  /* pure virtual member function */
      virtual nodetype type() const = 0;

	  /* constructor and destructor */
      node(node *left_, node *right_, int weight_ = 0);
      virtual ~node() = 0;

   private:
	  /* copy constructor */
      node(const node *n);
	  /* operator overloading */
      node* operator=(const node *rhs);
};


/*---------------------------------------------------------------------------*/
/*                                derived class                              */
/*---------------------------------------------------------------------------*/

/*----- brance node ---------------------------------------------------------*/
struct branch: public node
{
      virtual nodetype type() const;

	  /* This actually is implementation, not just decalaration */
      branch(node *left_, node *right_): node(left_, right_) {}

};

/*----- leaf node -----------------------------------------------------------*/
struct leaf: public node
{
	  /* ? */
      char payload; /* value? */

      virtual nodetype type() const;

      leaf(char payload_, int weight_): node(nullptr, nullptr, weight_), payload(payload_) { }
};

/******************************************************************************
 *                              node_comp                                     *
 *****************************************************************************/

struct node_comp: public std::binary_function<node*, node*, bool>
{
      bool operator()(const node* N1, const node* N2);
};

#endif // NODE_HPP




