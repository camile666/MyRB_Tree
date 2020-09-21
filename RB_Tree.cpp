#ifndef RB_TREE_CPP
#define RB_TREE_CPP
#include "RB_Tree.h"

template<class K>
RB_Tree<K>::RB_Tree() : _pRoot(nullptr)
{}

template<class K>
RB_Tree<K>::~RB_Tree()
{}

template<class K>
void RB_Tree<K>::preOrder(RB_Tree_Node<K>* &root) const
{
    if(!root) return;
    else{
        cout << "<" << root->_data << ">" << endl;
        preOrder(root->_pLeft);
        preOrder(root->pRight);
    }
}

template<class K>
void RB_Tree<K>::preOrder()
{
    preOrder(_pRoot);
}

template<class K>
void RB_Tree<K>::inOrder(RB_Tree_Node<K>* &root) const
{
    if(!root) return;
    else{
        inOrder(root->_pLeft);
        cout << "<" << root->_data << ">" << endl;       
        inOrder(root->pRight);
    }
}

template<class K>
void RB_Tree<K>::inOrder()
{
    inOrder(_pRoot);
}

template<class K>
void RB_Tree<K>::postOrder(RB_Tree_Node<K>* &root) const
{
    if(!root) return;
    else{
        postOrder(root->_pLeft);
        postOrder(root->pRight);
        cout << "<" << root->_data << ">" << endl;                
    }
}

template<class K>
void RB_Tree<K>::postOrder()
{
    postOrder(_pRoot);
}

template<class K>
RB_Tree_Node<K>* RB_Tree<K>::Search(const K& key)
{
     return Search(_pRoot, key);
}

template<class K>
RB_Tree_Node<K>* Search(RB_Tree_Node<K>* &root, const K& key)
{
    RB_Tree_Node<K>* pCur = root;
    while(pCur && pCur->_data.first != key)
    {
        if(pCur->_data.first < key) pCur = pCur->_pRight;
        else pCur = pCur->_pLeft;
    }
    return pCur;
}

template<class K>
void RB_Tree<K>::RotateL(RB_Tree_Node<K>* &root, RB_Tree_Node<K>* pParent)
{
    if(!pParent) return;
    
    RB_Tree_Node<K>* pSubR = pParent->_pRight;
    RB_Tree_Node<K>* pSubRL = pSubR->_pLeft;

    pParent->_pRight = pSubRL;
    if(pSubRL) pSubRL->_pParent = pParent;

    RB_Tree_Node<K>* pGrandParent = pParent->_pParent;
    pParent->_pParent = pSubR;
    pSubR->_pLeft = pParent;

    if(_pRoot == pParent){
        _pRoot == pSubR;
        pSubR->_pParent = nullptr;
    }
    else
    {
        if(pGrandParent)
        {
            if(pGrandParent->_pLeft == pParent) pGrandParent->_pLeft = pSubR;
            else pGrandParent->_pRight = pSubR;
        }
        pSubR->pParent = pGrandParent;
    }
}

template<class K>
void RB_Tree<K>::RotateR(RB_Tree_Node<K>* &root, RB_Tree_Node<K>* pParent)
{
    if(!pParent) return;

    RB_Tree_Node<K>* pSubL = pParent->_pLeft;
    RB_Tree_Node<K>* pSubLR = pSubL->_pRight;

    pParent->_pLeft = pSubLR;
    if(pSubLR) pSubLR->_pParent = pParent;

    RB_Tree_Node<K>* pGrandParent = pParent->_pParent;
    pParent->_pParent = pSubL;
    pSubL->_pRight = pParent;

    if(_pRoot == pParent){
        _pRoot == pSubL;
        pSubL->_pParent = nullptr;
    }
    else
    {
        if(pGrandParent)
        {
            if(pGrandParent->_pLeft == pParent) pGrandParent->_pLeft = pSubL;
            else pGrandParent->_pRight = pSubL;
        }
        pSubL->pParent = pGrandParent;
    }
}

template<class K>
void RB_Tree<K>::RotateRL(RB_Tree_Node<K>* &root, RB_Tree_Node<K>* pParent)
{
    if(!pParent) return;
    RotateR(root, pParent->_pRight);
    RotateL(root, pParent);
}

template<class K>
void RB_Tree<K>::RotateLR(RB_Tree_Node<K>* &root, RB_Tree_Node<K>* pParent)
{
    if(!pParent) return;
    RotateL(root, pParent->_pLeft);
    RotateR(root, pParent);
}

template<class K>
bool RB_Tree<K>::Insert(RB_Tree_Node<K>* &root, const K& key)
{
    //空树插入节点，直接为黑
    if(root == nullptr)
    {
        root = new RB_Tree_Node<K>(key);
        root->_color = BLACK;
        return true;
    }

    //树非空
    RB_Tree_Node<K>* pParent = nullptr;
    RB_Tree_Node<K>* pCur = root;
    //按照BST的规则寻找新节点应在那个parent节点下插入
    while(pCur)
    {
        if(pCur->_data.first < kv.first)
        {
            pParent = pCur;
            pCur = pCur->_pRight;
        }
        else if(pCur->_data.first > kv.first)
        {
            pParent = pCur;
            pCur = pCur->_pLeft;
        }
        else return false;//红黑树数据不可重复
    }

    //插入，新节点首先为红
    RB_Tree_Node<K>* pNewNode = new RB_Tree_Node<K>(key);
    pCur = pNewNode;
    pCur->_color = RED;
    if(pParent->_data.first < kv.first)
    {
        pParent->_pRight = pCur;
        pCur->_pParent = pParent;
    }
    else{
        pParent->_pLeft = pCur;
        pCur->_pParent = pParent;
    }

    //插入节点父节点为黑色，不违反任何性质，直接插入
    //父节点为红时，开始调整红黑树节点颜色
    while(pParent && pParent->_color == RED)//父亲节点存在 且父亲节点为红 开始调整节点颜色
    {
        RB_Tree_Node<K>* pGrandFather = pParent->_pParent;
        if(pParent == pGrandFather->_pLeft)
        {
            //如果插入节点cur的父亲节点是祖父的左节点， 那么叔叔节点肯定是祖父的右节点
            RB_Tree_Node<K>* pUncle = pGrandFather->pRight;
            //情况A，pCur为红色节点，pParent为红色节点，grand为黑色节点，uncle存在且为红色节点
            //将pParent 和 uncle改成黑色节点；若grand为根节点，则不用再处理；若grand不为根节点，则令grand为红色节点，然后把grand 当成pCur,继续朝上更新；
            if(pUncle && pUncle->_color == RED)
            {
                pParent->_color = pUncle->_color = BLACK;
                pGrandFather->_color = RED;

                //向上调整
                pCur = pGrandFather;
                pParent = pCur->_pParent;
            }
            else//uncle不存在 或 uncle存在且为黑
            {
                //情况B pCur节点颜色为红色，pParent节点颜色为红，grand节点颜色为黑，uncle不存在 或是 uncle为黑色
                //pParent为grand的左孩子，pCur为pParent的左孩子，则进行右单旋转,最后令pParent颜色变为黑色，grand颜色变为红色
                //    g
                //  p
                //c
                if(cur == pParent->_pLeft)
                {
                    //右旋+变色
                    RotateR(root, pGrandFather);//旋转后grand变为parent的右子树
                    pGrandFather->_color = RED;
                    pParent->_color = BLACK;
                }
                //情况C pCur节点颜色为红色，pParent节点颜色为红，grand节点颜色为黑，uncle不存在 或是 uncle为黑色
                //pParent为grand的左孩子，pCur为pParent的右孩子，则进行LR双旋,最后令pParent颜色变为黑色，grand颜色变为红色
                //    g
                //  p
                //    c
                else if(pCur == pParent->_pRight)
                {
                    RotateLR(root, pGrandFather);
                    pGrandFather->_color = RED;
                    pParent->_color = BLACK;
                }
                break;//这两种情况不需要向上继续处理，直接break
            }            
        }
        else
        {
            RB_Tree_Node<K>* pUncle = pGrandFather->_pLeft;
            //情况A uncle存在且为红
            if(pUncle && pUncle->_color == RED){
                pParent->_color = pUncle->color = BLACK;
                pGrandFather->_color = RED;

                //向上检查
                pCur = pGrandFather;
                pParent = pCur->_pParent;
            }
            else//uncle不存在 或 存在且为黑
            {
                //情况D pCur节点颜色为红色，pParent节点颜色为红，grand节点颜色为黑，uncle不存在 或是 uncle为黑色
                //pParent为grand的右孩子，pCur为pParent的右孩子，则进行左单旋,最后令pParent颜色变为黑色，grand颜色变为红色
                //g
                //  p
                //    c
                if(pCur = pParent->_pRight)
                {
                    RotateL(root, pGrandFather);
                    pGrandFather->_color = RED;
                    pParent->_color = BLACK;
                }
                //情况E pCur节点颜色为红色，pParent节点颜色为红，grand节点颜色为黑，uncle不存在 或是 uncle为黑色
                //pParent为grand的右孩子，pCur为pParent的左孩子，则进行右左双旋,最后令pParent颜色变为黑色，grand颜色变为红色
                //g
                //  p
                //c
                else
                {
                    RotateRL(root, pGrandFather);
                    pGrandFather->_color = RED;
                    pParent->_color = BLACK;
                }
                break;                
            }            
        }
    }
    root->_color = BLACK;
    return true;
}

template<class K>
bool Insert(const K& key)
{
    return Insert(_pRoot, key);
}

template<class K>
bool RB_Tree<K>::RemoveFixUp(RB_Tree_Node<K>* &root, RB_Tree_Node<K>* pNode, RB_Tree_Node<K>* pParent)
{
    RB_Tree_Node<K>* pUncle;
    while ((!pNode || pNode->_color == BLACK) && pNode != root)
    {
        if(pParent->_pLeft == pNode)
        {
            pUncle = pParent->_pRight;//替换节点的兄弟节点
            if(pUncle->_color == RED)
            {
                //case 2.1.1 替换节点的兄弟节点是红色
                pUncle->_color = BLACK;
                pParent->_color = RED;
                RotateL(root, pParent);
                pUncle = pParent->_pRight;
            }
            if((!pUncle->_pLeft || pUncle->_pLeft == BLACK) && (!pUncle->_pRight || pUncle->_pRight == BLACK))
            {
                //case 2.1.2.3 替换节点的兄弟是黑色，且孩子不存在或为黑色
                pUncle->_color = RED;
                pNode = pParent;
                pParent = pNode->_pParent;
            }
            else
            {
                if(!pUncle->_pRight || pUncle->_pRight == BLACK)
                {
                    //case 2.1.2.2 替换节点的兄弟是黑色，其左子树为红，右子树为黑
                    pUncle->_pLeft->_color = BALCK;
                    pUncle->_color = RED;
                    RotateR(root, pUncle);
                    pUncle = pParent->_pRight;
                }
                //case 2.1.2.1 替换节点的兄弟是黑色，其左子树任意颜色，右子树为红色
                pUncle->_color = pParent->_color;
                pParent->_color = BLACK;
                pUncle->_pRight->_color = BLACK;
                RotateL(root, pParent);
                pNode = root;
                break;
            }            
        }
        else
        {
            pUncle = pParent->_pLeft;//替换节点的兄弟节点
            if(pUncle->_color == RED)
            {
                //case 2.2.1 替换节点的兄弟节点是红色
                pUncle->_color = BLACK;
                pParent->_color = RED;
                RotateR(root, pParent);
                pUncle = pParent->_pLeft;
            }
            if((!pUncle->_pLeft || pUncle->_pLeft == BLACK) && (!pUncle->_pRight || pUncle->_pRight == BLACK))
            {
                //case 2.2.2.3 替换节点的兄弟是黑色，且孩子不存在或为黑色
                pUncle->_color = RED;
                pNode = pParent;
                pParent = pNode->_pParent;
            }
            else
            {
                if(!pUncle->_pLeft || pUncle->_pLeft == BLACK)
                {
                    //case 2.2.2.2 替换节点的兄弟是黑色，其右子树为红，左子树为黑
                    pUncle->_pRight->_color = BALCK;
                    pUncle->_color = RED;
                    RotateL(root, pUncle);
                    pUncle = pParent->_pLeft;
                }
                //case 2.2.2.1 替换节点的兄弟是黑色，其右子树任意颜色，左子树为红色
                pUncle->_color = pParent->_color;
                pParent->_color = BLACK;
                pUncle->_pLeft->_color = BLACK;
                RotateR(root, pParent);
                pNode = root;
                break;
            }     
        }        
    } 
    if(pNode) pNode->_color = BLACK; 
    return true;  
}

template<class K>
bool RB_Tree<K>::Remove(const K& key)
{
    Node* pDeletedNode = Search(key);
    if(pDeletedNode = nullptr) return false;
    else
    {
        /*
        //左右子树为空则直接删除
        if(!pDeletedNode->_pLeft && !pDeletedNode->_pRight)
        {
            delete pDeletedNode;//TODO write a function to fix the memory leak
        }
        //左子树为空,右子树不为空
        else if (!pDeletedNode->_pLeft && pDeletedNode->_pRight)
        {
            //不为根节点
            if(pDeletedNode != _pRoot)
            {
                if(pDeletedNode->_pParent->_pLeft == pDeletedNode)
                {
                    pDeletedNode->_pParent->_pLeft = pDeletedNode->_pRight;
                    pDeletedNode->_pRight->_pParent = pDeletedNode->_pParent;
                }
                else
                {
                    pDeletedNode->_pParent->_pRight = pDeletedNode->_pRight;
                    pDeletedNode->_pRight->_pParent = pDeletedNode->_pParent;
                }
                
            }
            else//删的就是根节点
            {
                _pRoot = pDeletedNode->_pRight;
                pDeletedNode->_pRight->_pParent = _pRoot;
            }
            
        }
        //左子树不为空,右子树为空
        else if (pDeletedNode->_pLeft && !pDeletedNode->_pRight)
        {
            if(pDeletedNode != _pRoot)
            {
                if(pDeletedNode->_pParent->_pLeft == pDeletedNode)
                {
                    pDeletedNode->_pParent->_pLeft = pDeletedNode->_pLeft;
                    pDeletedNode->_pLeft->_pParent = pDeletedNode->_pParent;
                }
                else
                {
                    pDeletedNode->_pParent->_pRight = pDeletedNode->_pLeft;
                    pDeletedNode->_pLeft->_pParent = pDeletedNode->_pParent;
                }
                
            }
            else//删的就是根节点
            {
                _pRoot = pDeletedNode->_pLeft;
                pDeletedNode->_pLeft->_pParent = _pRoot;
            }
        }*/
        if (pDeletedNode->_pLeft && pDeletedNode->_pRight)
        {
            //获取删除节点的后继节点，即比删除节点大的节点中最小的那个
            Node* pReplaceNode = pDeletedNode;
            pReplaceNode = pReplaceNode->_pRight;
            while(pReplaceNode->_Left) pReplaceNode = pReplaceNode->_pLeft;

            if(pDeletedNode != _pRoot)//根节点不存在父节点
            {
                //删除节点是其父节点的左子树
                if(pDeletedNode == pDeletedNode->_pParent->_pLeft)
                {
                    pDeletedNode->_pParent->_pLeft = pReplaceNode;
                }
                //删除节点是其父节点的右子树
                else
                {
                    pDeletedNode->_pParent->_pRight = pReplaceNode;
                }
            }
            else//是根节点，更新根节点
            {
                _pRoot = pReplaceNode;
            }
            // child是"取代节点"的右孩子，也是需要"调整的节点"。
            // "取代节点"肯定不存在左孩子！因为它是一个后继节点。
            Node* pChild = pReplaceNode->_pRight;
            Node* pParent = pReplaceNode->_pParent;
            Color color = pReplaceNode->_color;

            if(pParent == pDeletedNode)
            {
                pParent = pReplaceNode //TODO check
            }
            else
            {
                if(pChild) 
                {
                    pChild->_pParent = pParent;
                    pParent->_pLeft = pChild;
                //pReplaceNode->_pRight = pDeletedNode->pRight;
                //pReplaceNode->_pRight_pParent = pReplaceNode;
                }
            }
            pReplaceNode->_pLeft = pDeletedNode->pLeft;
            pReplaceNode->_pParent = pDeletedNode->_pParent;
            pReplaceNode->_color = pDeletedNode->_color;
            pReplaceNode->_pLeft->_pParent = pReplaceNode;   

            if(color == BLACK) 
            {    
                if(RemoveFixUp(pChild, pParent))
                {
                    delete pDeletedNode;
                    pDeletedNode = NULL;
                    return true;
                }
                return false;
            }         
        }
        else
        {
            if(pDeletedNode->_pLeft) Node* pChild = pDeletedNode->_pLeft;
            else if(pDeletedNode->_pRight) Node* pChild = pDeletedNode->_pRight;
            Node* pParent = pDeletedNode->_pParent;
            Color color = pDeletedNode->_color;
            if(pChild) pChild->_pParent = pParent;
            if(pParent)
            {
                if(pParent->_pLeft == pDeletedNode) pParent->_pLeft = pChild;
                else pParent->right == pChild;
            }
            else _pRoot = pChild;
            if(color == BLACK) 
            {    
                if(RemoveFixUp(pChild, pParent))
                {
                    delete pDeletedNode;
                    pDeletedNode = NULL;
                    return true;
                }
                return false;
            }    
        }        
        return true;
    }    
}

template<class K>
bool RB_Tree<K>::Remove(const K& key)
{
    Remove(_pRoot, key);
}

#endif