#include "node.hpp"

/**FQA
 * ===
 * 1] Why not implement node's copy constructor?
 * 
 */



/*---------------------------------------------------------------------------*/
/*                               Constructor                                 */
/*---------------------------------------------------------------------------*/

/**NB:this prototype is not the same if count : clause
 * ===================================================
 * This constructor's prototype :
 * node(node *left_, node *right_, int weight_)
 */

/* the after-colon clause means:
 * initialize member left with left_,which is appear in params list
 * initialize member right with right_, which is also in params list
 */
node::node(node *left_, node *right_, int weight_): left(left_), right(right_)
{
   if (weight_ == 0)
      weight = left->weight + right->weight;
   else
      weight = weight_;
}

/*---------------------------------------------------------------------------*/
/*                               Destructor                                  */
/*---------------------------------------------------------------------------*/

node::~node()
{
   delete left;
   delete right;
}

/*---------------------------------------------------------------------------*/
/*                           Operator overloading                            */
/*---------------------------------------------------------------------------*/

/**Two ways to operator overloading
* ================================
* 1] operator overloading as member function.
* 2] as friend function. this means one more param than former one.
*/
 
bool node_comp::operator()(const node* N1, const node* N2) {
   return N1->weight > N2->weight;
}

/*---------------------------------------------------------------------------*/
/*                              operations                                   */
/*---------------------------------------------------------------------------*/

/*----- branch::type() ------------------------------------------------------*/
nodetype branch::type() const
{
   /* NB:how to reference a enum's instance */
   return nodetype::BRANCH;
}

/*----- leaf::type() --------------------------------------------------------*/
nodetype leaf::type() const
{
   return nodetype::LEAF;
}

