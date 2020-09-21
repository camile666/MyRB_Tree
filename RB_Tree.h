#ifndef RB_TREE_HPP
#define RB_TREE_HPP
#include "RB_Tree_Node.h"

template<class K>
class RB_Tree
{
    //typedef RB_Tree_Node<K> Node;
public:
    RB_Tree() : _pRoot(nullptr);
    ~RB_Tree();

    void preOrder();
    void inOrder();
    void postOrder();

    RB_Tree_Node<K>* Search(const K& key);
    bool Insert(const K& key);
    bool Remove(const K& key);
    
private:
    void preOrder(RB_Tree_Node<K>* &root) const;
    void inOrder(RB_Tree_Node<K>* &root) const;
    void postOrder(RB_Tree_Node<K>* &root) const;

    RB_Tree_Node<K>* Search(RB_Tree_Node<K>* &root, const K& key);
    bool Insert(RB_Tree_Node<K>* &root, const K& key);
    bool Remove(RB_Tree_Node<K>* &root, const K& key);
    bool removeFixUp(RB_Tree_Node<K>* &root, RB_Tree_Node<K>* node, RB_Tree_Node<K>* parent);

    void RotateL(RB_Tree_Node<K>* &root, RB_Tree_Node<K>* pParent);
    void RotateR(RB_Tree_Node<K>* &root, RB_Tree_Node<K>* pParent);
    void RotateRL(RB_Tree_Node<K>* &root, RB_Tree_Node<K>* pParent);
    void RotateLR(RB_Tree_Node<K>* &root, RB_Tree_Node<K>* pParent);

    RB_Tree_Node<K>* _pRoot;
}

#endif