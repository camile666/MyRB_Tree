#ifndef RB_TREE_NODE_HPP
#define RB_TREE_NODE_HPP
#include <iostream>
using namespace std;

enum Color
{
    BLACK,
    RED
};

template<class K>
class RB_Tree_Node
{
    RB_Tree_Node(const K& key)
                : _pLeft(nullptr)
                , _pRight(nullptr)
                , _pParent(nullptr)
                , _data(key)
                , _color(RED)
    {}

    RB_Tree_Node<K>* _pLeft;
    RB_Tree_Node<K>* _pRight;
    RB_Tree_Node<K>* _pParent;    
    K _data;
    Color _color;
};

#endif