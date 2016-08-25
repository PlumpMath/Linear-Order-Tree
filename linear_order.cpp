/* 
---------------------------------------------------------------------------------------------------------
Solution to the 1st Project of Advanced Data Structures I9600
City College of New York, CUNY 

AUTHOR : ANKAN KUMAR GIRI

Email : agiri000@citymail.cuny.edu / ankangiri@gmail.com
---------------------------------------------------------------------------------------------------------

INSTRUCTIONS:
=============

compiles with command line "g++ -std=c++11 linear_order_tree.cpp -o lot.out"
run using "./lot.out 
------------------------------------------------------------------------------------------------------------
*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdint>
using namespace std;
class ReverseTree
{
    public:
        long key;
        int height;
        ReverseTree *left;
        ReverseTree *right;
        ReverseTree *parent;
};
class OrderTree
{
    public:
        long key;
        int height;
        OrderTree *left;
        OrderTree *right;
        ReverseTree *rvstree;
};
class Stack
{
    public:
        OrderTree *tree_t;
        Stack *next;
};
class ReverseStack
{
    public:
        ReverseTree *tree_t;
        ReverseStack *next;
}; 
Stack *create_stack()
{
    Stack *stack = new Stack();
    stack->next = NULL;
    return stack;
}
void push(OrderTree *&tree, Stack *&stack)
{
    Stack *tmp_stack = new Stack();
    tmp_stack->tree_t = tree;
    tmp_stack->next = stack->next;
    stack->next = tmp_stack;
}
bool stack_empty(Stack *&stack)
{
    if (stack->next == NULL)
    {
        return true;
    }
    return false;
}
OrderTree *pop(Stack *&stack)
{
    Stack *tmp_stack = stack->next;
    OrderTree *tree = tmp_stack->tree_t;
    stack->next = tmp_stack->next;
    delete tmp_stack;
    return tree;
}
void remove_stack(Stack *&stack)
{
    Stack *temp_stack;
    do
    {
        temp_stack = stack->next;
        delete stack;
        stack = temp_stack;
    } while (temp_stack != NULL);
}
ReverseStack *create_reversestack()
{
    ReverseStack *stack = new ReverseStack();
    stack->next = NULL;
    return stack;
}
void push(ReverseTree *&tree, ReverseStack *&stack)
{
    ReverseStack *tmp_stack = new ReverseStack();
    tmp_stack->tree_t = tree;
    tmp_stack->next = stack->next;
    stack->next = tmp_stack;
}
bool stack_empty(ReverseStack *&stack)
{
    if (stack->next == NULL)
    {
        return true;
    }
    return false;
}
ReverseTree *pop(ReverseStack *&stack)
{
    ReverseStack *tmp_stack = stack->next;
    ReverseTree *tree = tmp_stack->tree_t;
    stack->next = tmp_stack->next;
    delete tmp_stack;
    return tree;
}
void reverse_push(ReverseStack *&stack1, ReverseStack *&stack2)
{
    while(!stack_empty(stack1))
    {
        ReverseTree *tree = pop(stack1);
        push(tree, stack2);
    }
}
void remove_stack(ReverseStack *&stack)
{
    ReverseStack *temp_stack;
    do
    {
        temp_stack = stack->next;
        delete stack;
        stack = temp_stack;
    } while (temp_stack != NULL);
}
ReverseTree *get_root(ReverseTree *&rt)
{
    if(rt->parent==NULL)
    {
        return rt;
    }
    ReverseTree *rt_tmp = rt;
    while(rt_tmp->parent!=NULL)
    {
        rt_tmp = rt_tmp->parent;
    }
    return rt_tmp;
}
void left_rotation_ordertree(OrderTree *&n)
{
    OrderTree *tmp_node;
    long tmp_key;
    tmp_node = n->left;
    tmp_key  = n->key;
    n->left  = n->right;
    n->key   = n->right->key;
    n->right = n->left->right;
    n->left->right = n->left->left;
    n->left->left  = tmp_node;
    n->left->key   = tmp_key;
}
void right_rotation_ordertree(OrderTree *&n)
{
    OrderTree *tmp_node;
    long tmp_key;
    tmp_node = n->right;
    tmp_key  = n->key;
    n->right = n->left;
    n->key   = n->left->key;
    n->left  = n->right->left;
    n->right->left = n->right->right;
    n->right->right  = tmp_node;
    n->right->key   = tmp_key;
}
void left_rotation_reversetree(ReverseTree *&n)
{
    ReverseTree *tmp_node;
    tmp_node = n->left;
    n->left  = n->right;
    n->right = n->left->right;
    n->right->parent = n;
    n->left->right = n->left->left;
    n->left->left  = tmp_node;
    n->left->left->parent = n->left;
}
void right_rotation_reversetree(ReverseTree *&n)
{
    ReverseTree *tmp_node;
    tmp_node = n->right;
    n->right = n->left;
    n->left  = n->right->left;
    n->left->parent = n;
    n->right->left = n->right->right;
    n->right->right  = tmp_node;
    n->right->right->parent = n->right;
}
int a_leftof_b(ReverseTree *&a, ReverseTree *&b)
{
    ReverseTree *a_tmp = a;
    ReverseTree *b_tmp = b;
    while(a_tmp->parent!=b_tmp->parent)
    {
        if(a_tmp->parent->height==b_tmp->parent->height)
        {
            a_tmp=a_tmp->parent;
            b_tmp=b_tmp->parent;
        }
        else if(a_tmp->parent->height<b_tmp->parent->height)
        {
            a_tmp=a_tmp->parent;
        }
        else if(a_tmp->parent->height>b_tmp->parent->height)
        {
            b_tmp=b_tmp->parent;
        }
    }
    if(a_tmp->parent->left==a_tmp && b_tmp->parent->right==b_tmp)
    {
        return 1;
    }
    return 0;
}
int a_rightof_b(ReverseTree *&a, ReverseTree *&b)
{
    ReverseTree *a_tmp = a;
    ReverseTree *b_tmp = b;
    while(a_tmp->parent!=b_tmp->parent)
    {
        if(a_tmp->parent->height==b_tmp->parent->height)
        {
            a_tmp=a_tmp->parent;
            b_tmp=b_tmp->parent;
        }
        else if(a_tmp->parent->height<b_tmp->parent->height)
        {
            a_tmp=a_tmp->parent;
        }
        else if(a_tmp->parent->height>b_tmp->parent->height)
        {
            b_tmp=b_tmp->parent;
        }
    }
    if(a_tmp->parent->right==a_tmp && b_tmp->parent->left==b_tmp)
    {
        return 1;
    }
    return 0;
}
OrderTree *create_order()
{
    OrderTree *ot = new OrderTree();
    ot->left=NULL;
    ot->right=NULL;
    ot->height=0;
    ot->rvstree=NULL;
}
void insert_into_emptytree(OrderTree *&tree, long a)
{
    if( tree->left == NULL ) // Tree is empty
    {
        tree->left = (OrderTree *)(intptr_t) a;
        tree->key  = a;
        tree->height = 0;
        tree->right  = NULL;
        ReverseTree *reverse = new ReverseTree();
        reverse->height=0;
        reverse->parent = NULL;
        reverse->left = NULL;
        reverse->right = NULL;
        reverse->key = a;
        tree->rvstree = reverse;
   }
}
void insert_top(OrderTree *&tree, long a)
{
    if( tree->left == NULL ) // Tree is empty
    {
        insert_into_emptytree(tree,a);
    }
    else if( tree->right == NULL ) // Tree has one node
    {
        OrderTree *old_leaf, *new_leaf;
        old_leaf = new OrderTree();
        old_leaf->left = tree->left;
        old_leaf->key = tree->key;
        old_leaf->right  = NULL;
        old_leaf->height = 0;
        old_leaf->rvstree = tree->rvstree;
        new_leaf = new OrderTree();
        new_leaf->left = (OrderTree *)(intptr_t) a;
        new_leaf->key = a;
        new_leaf->right  = NULL;
        new_leaf->height = 0;
        if( tree->key < a)
        {
            tree->left  = old_leaf;
            tree->right = new_leaf;
            tree->key = a;
        }
        else
        {
            tree->left  = new_leaf;
            tree->right = old_leaf;
        }
        tree->height = 1;
        tree->rvstree=NULL;
        ReverseTree *rtreerc = new ReverseTree();
        rtreerc->left=NULL;
        rtreerc->right=NULL;
        rtreerc->key=a;
        rtreerc->height=0;
        ReverseTree *rtreep = new ReverseTree();
        rtreep->parent=NULL;
        rtreep->left = old_leaf->rvstree;
        rtreep->right = rtreerc;
        rtreep->height = 1;
        rtreerc->parent = rtreep;
        rtreep->left->parent = rtreep;
        rtreep->right->parent = rtreep;
        new_leaf->rvstree = rtreerc;
    }
    else
    {
        Stack *stk = create_stack();
        OrderTree *tmp_node = tree;
        while( tmp_node->right != NULL )
        {
            push(tmp_node,stk);
            if( a < tmp_node->key )
               tmp_node = tmp_node->left;
            else
               tmp_node = tmp_node->right;
        }
        OrderTree *old_leaf = new OrderTree();
        old_leaf->left = tmp_node->left;
        old_leaf->key = tmp_node->key;
        old_leaf->right  = NULL;
        old_leaf->height = 0;
        old_leaf->rvstree = tmp_node->rvstree;
        OrderTree *new_leaf  = new OrderTree();
        new_leaf->left = (OrderTree *)(intptr_t) a;
        new_leaf->key = a;
        new_leaf->right  = NULL;
        new_leaf->height = 0;
        if( tmp_node->key < a )
        {
            tmp_node->left  = old_leaf;
            tmp_node->right = new_leaf;
            tmp_node->key = a;
        }
        else
        {
            tmp_node->left  = new_leaf;
            tmp_node->right = old_leaf;
        }
        tmp_node->height = 1;
        tmp_node->rvstree = NULL;
        ReverseTree *root_t = get_root(old_leaf->rvstree);
        ReverseStack *rvs_stk = create_reversestack();
        while(root_t->right != NULL)
        {
            push(root_t,rvs_stk);
            root_t=root_t->right;
        }
        ReverseTree *rtreep = new ReverseTree();
        rtreep->height = 1;
        rtreep->parent = root_t->parent;
        if(root_t->parent->left==root_t)
            rtreep->parent->left = rtreep;
        else
            rtreep->parent->right = rtreep;
        root_t->parent = rtreep;
        rtreep->left = root_t;
        ReverseTree *rtreerc = new ReverseTree();
        rtreerc->left = NULL;
        rtreerc->key = a;
        rtreerc->right  = NULL;
        rtreerc->height = 0;
        rtreerc->parent = rtreep;
        rtreep->right = rtreerc;
        new_leaf->rvstree = rtreerc;
        int finished = 0;
        while( !stack_empty(stk) > 0 && !finished )
        {
            int tmp_height, old_height;
            tmp_node = pop(stk);
            old_height= tmp_node->height;
            if( tmp_node->left->height - tmp_node->right->height == 2 )
            {
                if( tmp_node->left->left->height - tmp_node->right->height == 1 )
                {
                    right_rotation_ordertree( tmp_node );
                    tmp_node->right->height = tmp_node->right->left->height + 1;
                    tmp_node->height = tmp_node->right->height + 1;
                }
                else
                {
                    left_rotation_ordertree( tmp_node->left );
                    right_rotation_ordertree( tmp_node );
                    tmp_height = tmp_node->left->left->height;
                    tmp_node->left->height  = tmp_height + 1;
                    tmp_node->right->height = tmp_height + 1;
                    tmp_node->height = tmp_height + 2;
                }
            }
            else if ( tmp_node->left->height - tmp_node->right->height == -2 )
            {
                if( tmp_node->right->right->height - tmp_node->left->height == 1 )
                {
                    left_rotation_ordertree( tmp_node );
                    tmp_node->left->height = tmp_node->left->right->height + 1;
                    tmp_node->height = tmp_node->left->height + 1;
                }
                else
                {
                    right_rotation_ordertree( tmp_node->right );
                    left_rotation_ordertree( tmp_node );
                    tmp_height = tmp_node->right->right->height;
                    tmp_node->left->height  = tmp_height + 1;
                    tmp_node->right->height = tmp_height + 1;
                    tmp_node->height = tmp_height + 2;
                }
            }
            else /* update height even if there was no rotation */
            {
                if( tmp_node->left->height > tmp_node->right->height )
                    tmp_node->height = tmp_node->left->height + 1;
                else
                    tmp_node->height = tmp_node->right->height + 1;
            }
            if( tmp_node->height == old_height )
                finished = 1;
        }
        remove_stack(stk);
        finished = 0;
        while( !stack_empty(rvs_stk) > 0 && !finished )
        {
            int tmp_height, old_height;
            root_t = pop(rvs_stk);
            old_height= root_t->height;
            if( root_t->left->height - root_t->right->height == 2 )
            {
                if( root_t->left->left->height - root_t->right->height == 1 )
                {
                    right_rotation_reversetree( root_t );
                    root_t->right->height = root_t->right->left->height + 1;
                    root_t->height = root_t->right->height + 1;
                }
                else
                {
                    left_rotation_reversetree( root_t->left );
                    right_rotation_reversetree( root_t );
                    tmp_height = root_t->left->left->height;
                    root_t->left->height  = tmp_height + 1;
                    root_t->right->height = tmp_height + 1;
                    root_t->height = tmp_height + 2;
                }
            }
            else if ( root_t->left->height - root_t->right->height == -2 )
            {
                if( root_t->right->right->height - root_t->left->height == 1 )
                {
                    left_rotation_reversetree( root_t );
                    root_t->left->height = root_t->left->right->height + 1;
                    root_t->height = root_t->left->height + 1;
                }
                else
                {
                    right_rotation_reversetree( root_t->right );
                    left_rotation_reversetree( root_t );
                    tmp_height = root_t->right->right->height;
                    root_t->left->height  = tmp_height + 1;
                    root_t->right->height = tmp_height + 1;
                    root_t->height = tmp_height + 2;
                }
            }
            else /* update height even if there was no rotation */
            {
                if( root_t->left->height > root_t->right->height )
                    root_t->height = root_t->left->height + 1;
                else
                    root_t->height = root_t->right->height + 1;
            }
            if( root_t->height == old_height )
                finished = 1;
        }
        remove_stack(rvs_stk);
    }
}
void insert_before(OrderTree *&tree, long a, long b)
{
    if( tree->left == NULL ) // Tree is empty
    {
        insert_into_emptytree(tree,a);
    }
    else if( tree->right == NULL ) // Tree has one node
    {
        OrderTree *old_leaf, *new_leaf;
        old_leaf = new OrderTree();
        old_leaf->left = tree->left;
        old_leaf->key = tree->key;
        if(old_leaf->key!=b)
        {
            return;
        }
        old_leaf->right  = NULL;
        old_leaf->height = 0;
        old_leaf->rvstree = tree->rvstree;
        new_leaf = new OrderTree();
        new_leaf->left = (OrderTree *) (intptr_t)a;
        new_leaf->key = a;
        new_leaf->right  = NULL;
        new_leaf->height = 0;
        if( tree->key < a)
        {
            tree->left  = old_leaf;
            tree->right = new_leaf;
            tree->key = a;
        }
        else
        {
            tree->left  = new_leaf;
            tree->right = old_leaf;
        }
        tree->height = 1;
        tree->rvstree=NULL;
        ReverseTree *rtreelc = new ReverseTree();
        rtreelc->left=NULL;
        rtreelc->right=NULL;
        rtreelc->key=a;
        rtreelc->height=0;
        ReverseTree *rtreep = new ReverseTree();
        rtreep->parent=NULL;
        rtreep->left = rtreelc;
        rtreep->right = old_leaf->rvstree;
        rtreep->height = 1;
        rtreelc->parent = rtreep;
        rtreep->left->parent = rtreep;
        rtreep->right->parent = rtreep;
        new_leaf->rvstree = rtreelc;
    }
    else
    {
        OrderTree *tmp_node = tree;
        ReverseTree *reverse_b;
        while( tmp_node->right != NULL )
        {
            if( b < tmp_node->key )
               tmp_node = tmp_node->left;
            else
               tmp_node = tmp_node->right;
        }
        if(tmp_node->key!=b)
        {
            return;
        }
        reverse_b = tmp_node->rvstree;
        Stack *stk = create_stack();
        tmp_node = tree;
        while( tmp_node->right != NULL )
        {
            push(tmp_node,stk);
            if( a < tmp_node->key )
               tmp_node = tmp_node->left;
            else
               tmp_node = tmp_node->right;
        }
        OrderTree *old_leaf = new OrderTree();
        old_leaf->left = tmp_node->left;
        old_leaf->key = tmp_node->key;
        old_leaf->right  = NULL;
        old_leaf->height = 0;
        old_leaf->rvstree = tmp_node->rvstree;
        OrderTree *new_leaf  = new OrderTree();
        new_leaf->left = (OrderTree *) (intptr_t)a;
        new_leaf->key = a;
        new_leaf->right  = NULL;
        new_leaf->height = 0;
        if( tmp_node->key < a )
        {
            tmp_node->left  = old_leaf;
            tmp_node->right = new_leaf;
            tmp_node->key = a;
        }
        else
        {
            tmp_node->left  = new_leaf;
            tmp_node->right = old_leaf;
        }
        tmp_node->height = 1;
        tmp_node->rvstree = NULL;
        ReverseStack *rvs_stk1 = create_reversestack();
        ReverseStack *rvs_stk2 = create_reversestack();
        ReverseTree *root_t = reverse_b;
        while(root_t->parent != NULL)
        {
            push(root_t->parent,rvs_stk1);
            root_t=root_t->parent;
        }
        reverse_push(rvs_stk1,rvs_stk2);
        ReverseTree *rtreep = new ReverseTree();
        rtreep->height = 1;
        rtreep->parent = reverse_b->parent;
        if(reverse_b->parent->left==reverse_b)
            rtreep->parent->left = rtreep;
        else
            rtreep->parent->right = rtreep;
        reverse_b->parent = rtreep;
        rtreep->right = reverse_b;
        ReverseTree *rtreelc = new ReverseTree();
        rtreelc->left = NULL;
        rtreelc->key = a;
        rtreelc->right  = NULL;
        rtreelc->height = 0;
        rtreelc->parent = rtreep;
        rtreep->left = rtreelc;
        new_leaf->rvstree = rtreelc;
        int finished = 0;
        while( !stack_empty(stk) > 0 && !finished )
        {
            int tmp_height, old_height;
            tmp_node = pop(stk);
            old_height= tmp_node->height;
            if( tmp_node->left->height - tmp_node->right->height == 2 )
            {
                if( tmp_node->left->left->height - tmp_node->right->height == 1 )
                {
                    right_rotation_ordertree( tmp_node );
                    tmp_node->right->height = tmp_node->right->left->height + 1;
                    tmp_node->height = tmp_node->right->height + 1;
                }
                else
                {
                    left_rotation_ordertree( tmp_node->left );
                    right_rotation_ordertree( tmp_node );
                    tmp_height = tmp_node->left->left->height;
                    tmp_node->left->height  = tmp_height + 1;
                    tmp_node->right->height = tmp_height + 1;
                    tmp_node->height = tmp_height + 2;
                }
            }
            else if ( tmp_node->left->height - tmp_node->right->height == -2 )
            {
                if( tmp_node->right->right->height - tmp_node->left->height == 1 )
                {
                    left_rotation_ordertree( tmp_node );
                    tmp_node->left->height = tmp_node->left->right->height + 1;
                    tmp_node->height = tmp_node->left->height + 1;
                }
                else
                {
                    right_rotation_ordertree( tmp_node->right );
                    left_rotation_ordertree( tmp_node );
                    tmp_height = tmp_node->right->right->height;
                    tmp_node->left->height  = tmp_height + 1;
                    tmp_node->right->height = tmp_height + 1;
                    tmp_node->height = tmp_height + 2;
                }
            }
            else
            {
                if( tmp_node->left->height > tmp_node->right->height )
                    tmp_node->height = tmp_node->left->height + 1;
                else
                    tmp_node->height = tmp_node->right->height + 1;
            }
            if( tmp_node->height == old_height )
                finished = 1;
        }
        remove_stack(stk);
        finished = 0;
        while( !stack_empty(rvs_stk2) > 0 && !finished )
        {
            int tmp_height, old_height;
            root_t = pop(rvs_stk2);
            old_height= root_t->height;
            if( root_t->left->height - root_t->right->height == 2 )
            {
                if( root_t->left->left->height - root_t->right->height == 1 )
                {
                    right_rotation_reversetree( root_t );
                    root_t->right->height = root_t->right->left->height + 1;
                    root_t->height = root_t->right->height + 1;
                }
                else
                {
                    left_rotation_reversetree( root_t->left );
                    right_rotation_reversetree( root_t );
                    tmp_height = root_t->left->left->height;
                    root_t->left->height  = tmp_height + 1;
                    root_t->right->height = tmp_height + 1;
                    root_t->height = tmp_height + 2;
                }
            }
            else if ( root_t->left->height - root_t->right->height == -2 )
            {
                if( root_t->right->right->height - root_t->left->height == 1 )
                {
                    left_rotation_reversetree( root_t );
                    root_t->left->height = root_t->left->right->height + 1;
                    root_t->height = root_t->left->height + 1;
                }
                else
                {
                    right_rotation_reversetree( root_t->right );
                    left_rotation_reversetree( root_t );
                    tmp_height = root_t->right->right->height;
                    root_t->left->height  = tmp_height + 1;
                    root_t->right->height = tmp_height + 1;
                    root_t->height = tmp_height + 2;
                }
            }
            else
            {
                if( root_t->left->height > root_t->right->height )
                    root_t->height = root_t->left->height + 1;
                else
                    root_t->height = root_t->right->height + 1;
            }
            if( root_t->height == old_height )
                finished = 1;
        }
        remove_stack(rvs_stk1);
        remove_stack(rvs_stk2);
    }
}
void insert_bottom(OrderTree *&tree, long a)
{
    if( tree->left == NULL ) // Tree is empty
    {
        insert_into_emptytree(tree,a);
    }
    else if( tree->right == NULL ) // Tree has one node
    {
        OrderTree *old_leaf, *new_leaf;
        old_leaf = new OrderTree();
        old_leaf->left = tree->left;
        old_leaf->key = tree->key;
        old_leaf->right  = NULL;
        old_leaf->height = 0;
        old_leaf->rvstree = tree->rvstree;
        new_leaf = new OrderTree();
        new_leaf->left = (OrderTree *) (intptr_t)a;
        new_leaf->key = a;
        new_leaf->right  = NULL;
        new_leaf->height = 0;
        if( tree->key < a)
        {
            tree->left  = old_leaf;
            tree->right = new_leaf;
            tree->key = a;
        }
        else
        {
            tree->left  = new_leaf;
            tree->right = old_leaf;
        }
        tree->height = 1;
        tree->rvstree=NULL;
        ReverseTree *rtreelc = new ReverseTree();
        rtreelc->left=NULL;
        rtreelc->right=NULL;
        rtreelc->key=a;
        rtreelc->height=0;
        ReverseTree *rtreep = new ReverseTree();
        rtreep->parent=NULL;
        rtreep->left = rtreelc;
        rtreep->right = old_leaf->rvstree;
        rtreep->height = 1;
        rtreelc->parent = rtreep;
        rtreep->left->parent = rtreep;
        rtreep->right->parent = rtreep;
        new_leaf->rvstree = rtreelc;
    }
    else
    {
        Stack *stk = create_stack();
        OrderTree *tmp_node = tree;
        while( tmp_node->right != NULL )
        {
            push(tmp_node,stk);
            if( a < tmp_node->key )
               tmp_node = tmp_node->left;
            else
               tmp_node = tmp_node->right;
        }
        OrderTree *old_leaf = new OrderTree();
        old_leaf->left = tmp_node->left;
        old_leaf->key = tmp_node->key;
        old_leaf->right  = NULL;
        old_leaf->height = 0;
        old_leaf->rvstree = tmp_node->rvstree;
        OrderTree *new_leaf  = new OrderTree();
        new_leaf->left = (OrderTree *) (intptr_t)a;
        new_leaf->key = a;
        new_leaf->right  = NULL;
        new_leaf->height = 0;
        if( tmp_node->key < a )
        {
            tmp_node->left  = old_leaf;
            tmp_node->right = new_leaf;
            tmp_node->key = a;
        }
        else
        {
            tmp_node->left  = new_leaf;
            tmp_node->right = old_leaf;
        }
        tmp_node->height = 1;
        tmp_node->rvstree = NULL;
        ReverseTree *root_t = get_root(old_leaf->rvstree);
        ReverseStack *rvs_stk = create_reversestack();
        while(root_t->right != NULL)
        {
            push(root_t,rvs_stk);
            root_t=root_t->left;
        }
        ReverseTree *rtreep = new ReverseTree();
        rtreep->height = 1;
        rtreep->parent = root_t->parent;
        if(root_t->parent->left==root_t)
            rtreep->parent->left = rtreep;
        else
            rtreep->parent->right = rtreep;
        root_t->parent = rtreep;
        rtreep->right = root_t;
        ReverseTree *rtreelc = new ReverseTree();
        rtreelc->left = NULL;
        rtreelc->key = a;
        rtreelc->right  = NULL;
        rtreelc->height = 0;
        rtreelc->parent = rtreep;
        rtreep->left = rtreelc;
        new_leaf->rvstree = rtreelc;
        int finished = 0;
        while( !stack_empty(stk) > 0 && !finished )
        {
            int tmp_height, old_height;
            tmp_node = pop(stk);
            old_height= tmp_node->height;
            if( tmp_node->left->height - tmp_node->right->height == 2 )
            {
                if( tmp_node->left->left->height - tmp_node->right->height == 1 )
                {
                    right_rotation_ordertree( tmp_node );
                    tmp_node->right->height = tmp_node->right->left->height + 1;
                    tmp_node->height = tmp_node->right->height + 1;
                }
                else
                {
                    left_rotation_ordertree( tmp_node->left );
                    right_rotation_ordertree( tmp_node );
                    tmp_height = tmp_node->left->left->height;
                    tmp_node->left->height  = tmp_height + 1;
                    tmp_node->right->height = tmp_height + 1;
                    tmp_node->height = tmp_height + 2;
                }
            }
            else if ( tmp_node->left->height - tmp_node->right->height == -2 )
            {
                if( tmp_node->right->right->height - tmp_node->left->height == 1 )
                {
                    left_rotation_ordertree( tmp_node );
                    tmp_node->left->height = tmp_node->left->right->height + 1;
                    tmp_node->height = tmp_node->left->height + 1;
                }
                else
                {
                    right_rotation_ordertree( tmp_node->right );
                    left_rotation_ordertree( tmp_node );
                    tmp_height = tmp_node->right->right->height;
                    tmp_node->left->height  = tmp_height + 1;
                    tmp_node->right->height = tmp_height + 1;
                    tmp_node->height = tmp_height + 2;
                }
            }
            else /* update height even if there was no rotation */
            {
                if( tmp_node->left->height > tmp_node->right->height )
                    tmp_node->height = tmp_node->left->height + 1;
                else
                    tmp_node->height = tmp_node->right->height + 1;
            }
            if( tmp_node->height == old_height )
                finished = 1;
        }
        remove_stack(stk);
        finished = 0;
        while( !stack_empty(rvs_stk) > 0 && !finished )
        {
            int tmp_height, old_height;
            root_t = pop(rvs_stk);
            old_height= root_t->height;
            if( root_t->left->height - root_t->right->height == 2 )
            {
                if( root_t->left->left->height - root_t->right->height == 1 )
                {
                    right_rotation_reversetree( root_t );
                    root_t->right->height = root_t->right->left->height + 1;
                    root_t->height = root_t->right->height + 1;
                }
                else
                {
                    left_rotation_reversetree( root_t->left );
                    right_rotation_reversetree( root_t );
                    tmp_height = root_t->left->left->height;
                    root_t->left->height  = tmp_height + 1;
                    root_t->right->height = tmp_height + 1;
                    root_t->height = tmp_height + 2;
                }
            }
            else if ( root_t->left->height - root_t->right->height == -2 )
            {
                if( root_t->right->right->height - root_t->left->height == 1 )
                {
                    left_rotation_reversetree( root_t );
                    root_t->left->height = root_t->left->right->height + 1;
                    root_t->height = root_t->left->height + 1;
                }
                else
                {
                    right_rotation_reversetree( root_t->right );
                    left_rotation_reversetree( root_t );
                    tmp_height = root_t->right->right->height;
                    root_t->left->height  = tmp_height + 1;
                    root_t->right->height = tmp_height + 1;
                    root_t->height = tmp_height + 2;
                }
            }
            else /* update height even if there was no rotation */
            {
                if( root_t->left->height > root_t->right->height )
                    root_t->height = root_t->left->height + 1;
                else
                    root_t->height = root_t->right->height + 1;
            }
            if( root_t->height == old_height )
                finished = 1;
        }
        remove_stack(rvs_stk);
    }
}
void insert_after(OrderTree *&tree, long a, long b)
{
    if( tree->left == NULL ) // Tree is empty
    {
        insert_into_emptytree(tree,a);
    }
    else if( tree->right == NULL ) // Tree has one node
    {
        OrderTree *old_leaf, *new_leaf;
        old_leaf = new OrderTree();
        old_leaf->left = tree->left;
        old_leaf->key = tree->key;
        if(old_leaf->key!=b)
        {
            return;
        }
        old_leaf->right  = NULL;
        old_leaf->height = 0;
        old_leaf->rvstree = tree->rvstree;
        new_leaf = new OrderTree();
        new_leaf->left = (OrderTree *) (intptr_t)a;
        new_leaf->key = a;
        new_leaf->right  = NULL;
        new_leaf->height = 0;
        if( tree->key < a)
        {
            tree->left  = old_leaf;
            tree->right = new_leaf;
            tree->key = a;
        }
        else
        {
            tree->left  = new_leaf;
            tree->right = old_leaf;
        }
        tree->height = 1;
        tree->rvstree=NULL;
        ReverseTree *rtreerc = new ReverseTree();
        rtreerc->left=NULL;
        rtreerc->right=NULL;
        rtreerc->key=a;
        rtreerc->height=0;
        ReverseTree *rtreep = new ReverseTree();
        rtreep->parent=NULL;
        rtreep->left = old_leaf->rvstree;
        rtreep->right = rtreerc;
        rtreep->height = 1;
        rtreerc->parent = rtreep;
        rtreep->left->parent = rtreep;
        rtreep->right->parent = rtreep;
        new_leaf->rvstree = rtreerc;
    }
    else
    {
        OrderTree *tmp_node = tree;
        ReverseTree *reverse_b;
        while( tmp_node->right != NULL )
        {
            if( b < tmp_node->key )
               tmp_node = tmp_node->left;
            else
               tmp_node = tmp_node->right;
        }
        if(tmp_node->key!=b)
        {
            return;
        }
        reverse_b = tmp_node->rvstree;
        Stack *stk = create_stack();
        tmp_node = tree;
        while( tmp_node->right != NULL )
        {
            push(tmp_node,stk);
            if( a < tmp_node->key )
               tmp_node = tmp_node->left;
            else
               tmp_node = tmp_node->right;
        }
        OrderTree *old_leaf = new OrderTree();
        old_leaf->left = tmp_node->left;
        old_leaf->key = tmp_node->key;
        old_leaf->right  = NULL;
        old_leaf->height = 0;
        old_leaf->rvstree = tmp_node->rvstree;
        OrderTree *new_leaf  = new OrderTree();
        new_leaf->left = (OrderTree *) (intptr_t)a;
        new_leaf->key = a;
        new_leaf->right  = NULL;
        new_leaf->height = 0;
        if( tmp_node->key < a )
        {
            tmp_node->left  = old_leaf;
            tmp_node->right = new_leaf;
            tmp_node->key = a;
        }
        else
        {
            tmp_node->left  = new_leaf;
            tmp_node->right = old_leaf;
        }
        tmp_node->height = 1;
        tmp_node->rvstree = NULL;
        ReverseStack *rvs_stk1 = create_reversestack();
        ReverseStack *rvs_stk2 = create_reversestack();
        ReverseTree *root_t = reverse_b;
        while(root_t->parent != NULL)
        {
            push(root_t->parent,rvs_stk1);
            root_t=root_t->parent;
        }
        reverse_push(rvs_stk1,rvs_stk2);
        ReverseTree *rtreep = new ReverseTree();
        rtreep->height = 1;
        rtreep->parent = reverse_b->parent;
        if(reverse_b->parent->left==reverse_b)
            rtreep->parent->left = rtreep;
        else
            rtreep->parent->right = rtreep;
        reverse_b->parent = rtreep;
        rtreep->left = reverse_b;
        ReverseTree *rtreerc = new ReverseTree();
        rtreerc->left = NULL;
        rtreerc->key = a;
        rtreerc->right  = NULL;
        rtreerc->height = 0;
        rtreerc->parent = rtreep;
        rtreep->right = rtreerc;
        new_leaf->rvstree = rtreerc;
        int finished = 0;
        while( !stack_empty(stk) > 0 && !finished )
        {
            int tmp_height, old_height;
            tmp_node = pop(stk);
            old_height= tmp_node->height;
            if( tmp_node->left->height - tmp_node->right->height == 2 )
            {
                if( tmp_node->left->left->height - tmp_node->right->height == 1 )
                {
                    right_rotation_ordertree( tmp_node );
                    tmp_node->right->height = tmp_node->right->left->height + 1;
                    tmp_node->height = tmp_node->right->height + 1;
                }
                else
                {
                    left_rotation_ordertree( tmp_node->left );
                    right_rotation_ordertree( tmp_node );
                    tmp_height = tmp_node->left->left->height;
                    tmp_node->left->height  = tmp_height + 1;
                    tmp_node->right->height = tmp_height + 1;
                    tmp_node->height = tmp_height + 2;
                }
            }
            else if ( tmp_node->left->height - tmp_node->right->height == -2 )
            {
                if( tmp_node->right->right->height - tmp_node->left->height == 1 )
                {
                    left_rotation_ordertree( tmp_node );
                    tmp_node->left->height = tmp_node->left->right->height + 1;
                    tmp_node->height = tmp_node->left->height + 1;
                }
                else
                {
                    right_rotation_ordertree( tmp_node->right );
                    left_rotation_ordertree( tmp_node );
                    tmp_height = tmp_node->right->right->height;
                    tmp_node->left->height  = tmp_height + 1;
                    tmp_node->right->height = tmp_height + 1;
                    tmp_node->height = tmp_height + 2;
                }
            }
            else
            {
                if( tmp_node->left->height > tmp_node->right->height )
                    tmp_node->height = tmp_node->left->height + 1;
                else
                    tmp_node->height = tmp_node->right->height + 1;
            }
            if( tmp_node->height == old_height )
                finished = 1;
        }
        remove_stack(stk);
        finished = 0;
        while( !stack_empty(rvs_stk2) > 0 && !finished )
        {
            int tmp_height, old_height;
            root_t = pop(rvs_stk2);
            old_height= root_t->height;
            if( root_t->left->height - root_t->right->height == 2 )
            {
                if( root_t->left->left->height - root_t->right->height == 1 )
                {
                    right_rotation_reversetree( root_t );
                    root_t->right->height = root_t->right->left->height + 1;
                    root_t->height = root_t->right->height + 1;
                }
                else
                {
                    left_rotation_reversetree( root_t->left );
                    right_rotation_reversetree( root_t );
                    tmp_height = root_t->left->left->height;
                    root_t->left->height  = tmp_height + 1;
                    root_t->right->height = tmp_height + 1;
                    root_t->height = tmp_height + 2;
                }
            }
            else if ( root_t->left->height - root_t->right->height == -2 )
            {
                if( root_t->right->right->height - root_t->left->height == 1 )
                {
                    left_rotation_reversetree( root_t );
                    root_t->left->height = root_t->left->right->height + 1;
                    root_t->height = root_t->left->height + 1;
                }
                else
                {
                    right_rotation_reversetree( root_t->right );
                    left_rotation_reversetree( root_t );
                    tmp_height = root_t->right->right->height;
                    root_t->left->height  = tmp_height + 1;
                    root_t->right->height = tmp_height + 1;
                    root_t->height = tmp_height + 2;
                }
            }
            else
            {
                if( root_t->left->height > root_t->right->height )
                    root_t->height = root_t->left->height + 1;
                else
                    root_t->height = root_t->right->height + 1;
            }
            if( root_t->height == old_height )
                finished = 1;
        }
        remove_stack(rvs_stk1);
        remove_stack(rvs_stk2);
    }

}
int is_before(OrderTree *tree, long a, long b)
{
    OrderTree *tmp = tree;
    OrderTree *tmp2 = tree;
    if(tmp->left==NULL)
    {
        return 0;
    }
    else
    {
        while( tmp->right != NULL )
        {
            if( a < tmp->key )
               tmp = tmp->left;
            else
               tmp = tmp->right;
        }
        if(tmp->key!=a)
        {
            return 0;
        }
        while( tmp2->right != NULL )
        {
            if( b < tmp2->key )
               tmp2 = tmp2->left;
            else
               tmp2 = tmp2->right;
        }
        if(tmp2->key!=b)
        {
            return 0;
        }
        int x = a_leftof_b(tmp->rvstree,tmp2->rvstree);
        return x;
    }
}
void delete_o(OrderTree *tree, key_t a)
{
    if(tree->left==NULL)
    {
        return;
    }
    else if(tree->right==NULL)
    {
        if(tree->key==a)
        {
            OrderTree *tmp = tree->left;
            tree->left = NULL;
            tree->height = 0;
            ReverseTree *tmp_rev = tree->rvstree;
            tree->rvstree = NULL;
            delete tmp;
            delete tmp_rev;
        }
    }
    else
    {
        Stack *stk = create_stack();
        OrderTree *tmp_node = tree;
        OrderTree *upper_node, *other_node;
        ReverseTree *reverse_a;
        while( tmp_node->right != NULL )
        {   
            push(tmp_node, stk);  
            upper_node = tmp_node;
            if( a < tmp_node->key )
            { 
                tmp_node   = upper_node->left; 
                other_node = upper_node->right;
            } 
            else
            {  
                tmp_node   = upper_node->right; 
                other_node = upper_node->left;
            } 
        }
        if(tmp_node->key!=a)
        {
            return;
        }
        reverse_a = tmp_node->rvstree;
        upper_node->key   = other_node->key;
        upper_node->left  = other_node->left;
        upper_node->right = other_node->right;
        upper_node->height = other_node->height;
        upper_node->rvstree = other_node->rvstree;
        delete tmp_node;
        delete other_node;
        ReverseTree *rtreep = reverse_a->parent;
        ReverseTree *rtreegp = rtreep->parent;
        ReverseTree *rtreechild;
        if(rtreep->left==reverse_a)
            rtreechild =  rtreep->right;
        else
            rtreechild =  rtreep->left;
        if(rtreegp!=NULL)
        {
            if(rtreegp->left==rtreep)
                rtreegp->left=rtreechild;
            else
                rtreegp->right=rtreechild;
            rtreegp->height=rtreep->height;
        }
        rtreechild->parent=rtreegp;
        delete reverse_a;
        delete rtreep; 
        ReverseStack *rvs_stk1 = create_reversestack();
        while(rtreechild->parent!=NULL)
        {
            rtreechild=rtreechild->parent;
            push(rtreechild,rvs_stk1); 
        }
        ReverseStack *rvs_stk2 = create_reversestack();
        reverse_push(rvs_stk1, rvs_stk2);
        int finished = 0;
        pop(stk);
        while( !stack_empty(stk) > 0 && !finished )
        {
            int tmp_height, old_height;
            tmp_node = pop(stk);
            old_height= tmp_node->height;
            if( tmp_node->left->height - tmp_node->right->height == 2 )
            {
                if( tmp_node->left->left->height - tmp_node->right->height == 1 )
                {
                    right_rotation_ordertree( tmp_node );
                    tmp_node->right->height = tmp_node->right->left->height + 1;
                    tmp_node->height = tmp_node->right->height + 1;
                }
                else
                {
                    left_rotation_ordertree( tmp_node->left );
                    right_rotation_ordertree( tmp_node );
                    tmp_height = tmp_node->left->left->height;
                    tmp_node->left->height  = tmp_height + 1;
                    tmp_node->right->height = tmp_height + 1;
                    tmp_node->height = tmp_height + 2;
                }
            }
            else if ( tmp_node->left->height - tmp_node->right->height == -2 )
            {
                if( tmp_node->right->right->height - tmp_node->left->height == 1 )
                {
                    left_rotation_ordertree( tmp_node );
                    tmp_node->left->height = tmp_node->left->right->height + 1;
                    tmp_node->height = tmp_node->left->height + 1;
                }
                else
                {
                    right_rotation_ordertree( tmp_node->right );
                    left_rotation_ordertree( tmp_node );
                    tmp_height = tmp_node->right->right->height;
                    tmp_node->left->height  = tmp_height + 1;
                    tmp_node->right->height = tmp_height + 1;
                    tmp_node->height = tmp_height + 2;
                }
            }
            else
            {
                if( tmp_node->left->height > tmp_node->right->height )
                    tmp_node->height = tmp_node->left->height + 1;
                else
                    tmp_node->height = tmp_node->right->height + 1;
            }
            if( tmp_node->height == old_height )
                finished = 1;
        }
        remove_stack(stk);
        ReverseTree *root_t;
        finished = 0;
        while( !stack_empty(rvs_stk2) > 0 && !finished )
        {
            int tmp_height, old_height;
            root_t = pop(rvs_stk2);
            old_height= root_t->height;
            if( root_t->left->height - root_t->right->height == 2 )
            {
                if( root_t->left->left->height - root_t->right->height == 1 )
                {
                    right_rotation_reversetree( root_t );
                    root_t->right->height = root_t->right->left->height + 1;
                    root_t->height = root_t->right->height + 1;
                }
                else
                {
                    left_rotation_reversetree( root_t->left );
                    right_rotation_reversetree( root_t );
                    tmp_height = root_t->left->left->height;
                    root_t->left->height  = tmp_height + 1;
                    root_t->right->height = tmp_height + 1;
                    root_t->height = tmp_height + 2;
                }
            }
            else if ( root_t->left->height - root_t->right->height == -2 )
            {
                if( root_t->right->right->height - root_t->left->height == 1 )
                {
                    left_rotation_reversetree( root_t );
                    root_t->left->height = root_t->left->right->height + 1;
                    root_t->height = root_t->left->height + 1;
                }
                else
                {
                    right_rotation_reversetree( root_t->right );
                    left_rotation_reversetree( root_t );
                    tmp_height = root_t->right->right->height;
                    root_t->left->height  = tmp_height + 1;
                    root_t->right->height = tmp_height + 1;
                    root_t->height = tmp_height + 2;
                }
            }
            else
            {
                if( root_t->left->height > root_t->right->height )
                    root_t->height = root_t->left->height + 1;
                else
                    root_t->height = root_t->right->height + 1;
            }
            if( root_t->height == old_height )
                finished = 1;
        }
        remove_stack(rvs_stk1);
        remove_stack(rvs_stk2);
    }
}
void inorder(OrderTree *o)
{
    if(o->right==NULL)
    {
        cout << o->key << "->\n";
        cout << o->rvstree->key << "\n";
        return;
    }
    inorder(o->left);
    cout << o->key << "->";
    inorder(o->right);
}
void inorder_reverse(ReverseTree *r)
{
    if(r->right==NULL)
    {
        if(r->parent!=NULL)
            cout << "\n" << r->parent->height <<"  ";
        cout << r->key << "->";
        return;
    }
    inorder_reverse(r->left);
    //if(r->parent!=NULL)
        //cout << "\n" << r->parent->height <<"  ";
    inorder_reverse(r->right);
}
OrderTree *get_smallest_node(OrderTree *ot)
{
    while(ot->right!=NULL)
    {
        ot=ot->left;
    }
    return ot;
}
#include "test_file.cpp"