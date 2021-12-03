#pragma once

#include <iostream>
#include "Node.h"

using namespace std;

typedef Node<Game> treeNode;

class BinTree
{
private:
    treeNode* m_root;
public:
    BinTree() { m_root = NULL; }
    BinTree(treeNode* root) { m_root = root; }
    
    treeNode* getRoot() { return m_root; }
    
    // Adds a new node to the tree
    void addRecord(treeNode* node)
    {
        if (m_root == nullptr)
        {
            m_root = node;
            return;
        }
        
        treeNode* curNode = m_root;
        
        // compares the new node to the curNode
        // if it's less then the next node is left child of curNode
        // else it's right child of curNode
        while (true)
            if (curNode->getGame() < node->getGame())
            {
                if (curNode->getRight() != nullptr)
                    curNode = curNode->getRight();
                else
                {
                    curNode->setRight(node);
                    break;
                }
            }
            else
            {
                if (curNode->getLeft() != nullptr)
                    curNode = curNode->getLeft();
                else
                {
                    curNode->setLeft(node);
                    break;
                }
            }
    }
    
    // Returns the number of children a node has
    int getChildrenNum(treeNode* node)
    {
        int cnt = 0;
        
        if (node->getLeft() != nullptr)
            cnt++;
            
        if (node->getRight() != nullptr)
            cnt++;
        
        return cnt;
    }
    
    // assuming the node has onlhy 1 child
    // Find the only child
    treeNode* getTheChild(treeNode* node)
    {
        if (node->getLeft() != nullptr)
            return node->getLeft();
        else
            return node->getRight();
    }
    
    // Finds the parent of the node
    treeNode* findParent(treeNode* node)
    {
        treeNode* prevNode = nullptr;
        treeNode* curNode = m_root;
        
        while (curNode != nullptr)
        {
            // checks if it's found
            if (curNode == node)
                return prevNode;
            else
            {
                // traverses trhough the tree
                if (curNode->getGame() < node->getGame())
                {
                    prevNode = curNode;
                    curNode = curNode->getRight();
                }
                else
                {
                    prevNode = curNode;
                    curNode = curNode->getLeft();
                }
            }
        }
        
        return nullptr;
    }
    
    // if there's no smaller child the node itself is returned
    treeNode* findSmRightNode(treeNode* node)
    {
        treeNode* curNode = node->getRight();
        
        if (curNode == nullptr) // Checks if there's at least one right node
            return nullptr;
        
        while (curNode->getLeft() != nullptr) // looks for the smallest node
        {
            curNode = curNode->getLeft();
        }
        
        return curNode; // if no smaller node was found, the original node is returned
    }
    
    // Swaps the values of 2 nodes
    void swap(treeNode* node1, treeNode* node2)
    {
        Game copy = node1->getGame();
        node1->setGame(node2->getGame());
        node2->setGame(copy);
    }
    
    treeNode* removeRecord(treeNode *node)
    {
        if (m_root == nullptr)
            return nullptr;
        
        treeNode* curNode = m_root;
        treeNode* prevNode = nullptr;
        
        while (curNode != nullptr)
        {
            int childrenNum = getChildrenNum(curNode);
            
            if (curNode->getGame() == node->getGame()) // the node is found
            {
                if (childrenNum == 0)
                {
                    if (prevNode == nullptr) // deleting head
                    {
                        treeNode* copy = curNode; // copying head before deleting it
                        m_root = nullptr;
                        return copy;
                    }
                    else // deleting a leaf
                    {
                        if (curNode->getGame() < prevNode->getGame())
                            prevNode->setLeft(nullptr);
                        else
                            prevNode->setRight(nullptr);
                        
                        return curNode;
                    }
                }
                else if (childrenNum == 1)
                {
                    treeNode* child = getTheChild(curNode);
                             
                    if (prevNode == nullptr)
                    {
                        m_root = child;
                    }
                    else
                    {
                        if (curNode->getGame() < prevNode->getGame())
                            prevNode->setLeft(child); // deleting left child of prev node
                        else
                            prevNode->setRight(child); // deleting right child of prev node
                    }
         
                    return curNode;
                }
                else // childrenNum == 2
                {
                    treeNode* smRightNode = findSmRightNode(curNode);
                    treeNode* parNode = findParent(smRightNode);

                    if (curNode == parNode) // deleting root
                    {
                        swap(curNode, smRightNode);
                        curNode->setRight(nullptr);
                    }
                    else // deleting other node that is not node
                    {
                        swap(curNode, smRightNode);
                        parNode->setLeft(nullptr);
                    }
                    
                    return smRightNode;
                }
            }
            else // the node is not found yet
            {
                prevNode = curNode;

                if (curNode->getGame() > node->getGame())
                    curNode = curNode->getLeft();
                else
                    curNode = curNode->getRight();
            }
        }
        
        return nullptr; // the node was not found 
    }
    
    // curNode is root when the function is first called
    treeNode* search(treeNode* curNode, string name)
    {
        if (curNode == nullptr)
            return nullptr;
        else if (curNode->getGame().getName().find(name) != string::npos)
            return curNode;
        else
        {
            treeNode* node = search(curNode->getLeft(), name);
            
            if (node == nullptr)
                node = search(curNode->getRight(), name);
            
            return node;
        }
    }
    
    // Print a node in a single line
    void printRecord(treeNode* node)
    {
        Game g = node->getGame();
        
        cout << g.getName() << ", "
             << g.getScore() << ", "
             << g.getInitials() << ", "
             << g.getPlays() << ", $"
             << g.getRev() << endl;
    }
    
    // Displays the tree in ascending order
    void displayTreeAsc(treeNode* node) 
    {
        if (node == nullptr)
            cout << "";
        else
        {
            displayTreeAsc(node->getLeft());
            printRecord(node);
            displayTreeAsc(node->getRight());
        }
    }
    
    // Displays the tree in descending order
    void displayTreeDes(treeNode* node)
    {
        if (node == nullptr)
            cout << "";
        else
        {
            displayTreeDes(node->getRight());
            printRecord(node);
            displayTreeDes(node->getLeft());
        }
    }
};
