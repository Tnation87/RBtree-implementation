//
//  main.cpp
//  red black tree
//
//  Created by toka magdy ragab  on 11/19/18.
//  Copyright © 2018 toka magdy ragab . All rights reserved.
//

#include <iostream>
#include <vector>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

enum Color {RED, BLACK, DOUBLE_BLACK};

class redblacktree
{
    
    struct node
    {
        int data;
        int color;
        node *left, *right, *parent;
        
        node()
        {
            color = RED;
            left = right = parent = 0;
        }
        
        node(int data)
        {
            this->data = data;
            color = RED;
            left = right = parent = 0;
        }
    };
    
    node *root;
    
    void rotateLeft(node *& n)
    {
        node *right = n->right;
        n->right = right->left;
        if (n->right != NULL)
            n->right->parent = n;
        right->parent = n->parent;
        if (n->parent == NULL)
            root = right;
        else if (n == n->parent->left)
            n->parent->left = right;
        else n->parent->right = right;
        
        right->left = n;
        n->parent = right;
    }
    
    void rotateRight(node *& n)
    {
        node *left = n->left;
        n->left = left->right;
        if (n->left != NULL)
            n->left->parent = n;
        left->parent = n->parent;
        if (n->parent == NULL)
            root = left;
        else if (n == n->parent->left)
            n->parent->left = left;
        else n->parent->right = left;
        
        left->right = n;
        n->parent = left;
    }
    
    int getColor(node *&node)
    {
        if (node == nullptr)
            return BLACK;
        
        return node->color;
    }
    
    void setColor(node *&node, int color)
    {
        if (node == nullptr)
            return;
        
        node->color = color;
    }
    
    void fixInsert(node *&newNode)
    {
        node *parent = NULL;
        node *grandparent = NULL;
        while (newNode != root && getColor(newNode) == RED && getColor(newNode->parent) == RED)
        {
            parent = newNode->parent;
            grandparent = parent->parent;
            if (parent == grandparent->left)
            {
                node *uncle = grandparent->right;
                if (getColor(uncle) == RED)
                {
                    setColor(uncle, BLACK);
                    setColor(parent, BLACK);
                    setColor(grandparent, RED);
                    newNode = grandparent;
                }
                else
                {
                    if (newNode == parent->right)
                    {
                        rotateLeft(parent);
                        newNode = parent;
                        parent = newNode->parent;
                    }
                    rotateRight(grandparent);
                    swap(parent->color, grandparent->color);
                    newNode = parent;
                }
            }
            else
            {
                node *uncle = grandparent->left;
                if (getColor(uncle) == RED)
                {
                    setColor(uncle, BLACK);
                    setColor(parent, BLACK);
                    setColor(grandparent, RED);
                    newNode = grandparent;
                }
                else
                {
                    if (newNode == parent->left)
                    {
                        rotateRight(parent);
                        newNode = parent;
                        parent = newNode->parent;
                    }
                    rotateLeft(grandparent);
                    swap(parent->color, grandparent->color);
                    newNode = parent;
                }
            }
        }
        setColor(root, BLACK);
    }
    
    node* insertNode(node *&NodePtr, node *&newNode)
    {
        if (NodePtr == nullptr)
            return newNode;
        
        if (newNode->data < NodePtr->data)
        {
            NodePtr->left = insertNode(NodePtr->left, newNode);
            NodePtr->left->parent = NodePtr;
        }
        else if (newNode->data > NodePtr->data)
        {
            NodePtr->right = insertNode(NodePtr->right, newNode);
            NodePtr->right->parent = NodePtr;
        }
        
        return NodePtr;
        
    }
    
    node* minValueNode(node *&n)
    {
         node* ptr = n;
        while (ptr->left != NULL)
            ptr = ptr->left;
        return ptr;
    }
    
    node* Delete(node *& n, int v)
    {
        if (n == NULL)
            return n;
        
        if (v < n->data)
            return Delete(n->left, v);
        
        if (v > n->data)
            return Delete(n->right, v);
        
        if (n->left == NULL || n->right == NULL)
            return n;
        
        node *temp = minValueNode(n->right);
        n->data = temp->data;
        return Delete(n->right, temp->data);
    }
    
    void fixDelete(node *& n)
    {
        if (n == NULL)
            return;
        
        if (n == root)
        {
            root = NULL;
            return;
        }
        
        if (getColor(n) == RED || getColor(n->right) == RED || getColor(n->left) == RED)
        {
            node* child;
            if (n->right != NULL)
                child = n->right;
            else child = n->left;
            if (child != NULL)
                child->parent = n->parent;
            setColor(child, BLACK);
            if (n->parent->right == n)
                n->parent->right = child;
            else n->parent->left = child;
            delete n;
            n = NULL;
        }
        else
        {
            node *sibling = NULL;
            node *parent = NULL;
            node *ptr = n;
            setColor(ptr, DOUBLE_BLACK);
            while (ptr != root && getColor(ptr) == DOUBLE_BLACK)
            {
                parent = ptr->parent;
                if (parent->right == ptr)
                {
                    sibling = parent->left;
                    if (getColor(sibling) == RED)
                    {
                        setColor(sibling, BLACK);
                        setColor(parent, RED);
                        rotateRight(parent);
                    }
                    else
                    {
                        if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK)
                        {
                            setColor(sibling, RED);
                            if(getColor(parent) == RED)
                                setColor(parent, BLACK);
                            else
                                setColor(parent, DOUBLE_BLACK);
                            ptr = parent;
                        }
                        else
                        {
                            if (getColor(sibling->left) == BLACK)
                            {
                                setColor(sibling->right, BLACK);
                                setColor(sibling, RED);
                                rotateLeft(sibling);
                                sibling = parent->left;
                            }
                            setColor(sibling, parent->color);
                            setColor(parent, BLACK);
                            setColor(sibling->left, BLACK);
                            rotateRight(parent);
                            break;
                        }
                    }
                }
                else
                {
                    sibling = parent->right;
                    if (getColor(sibling) == RED)
                    {
                        setColor(sibling, BLACK);
                        setColor(parent, RED);
                        rotateLeft(parent);
                    }
                    else
                    {
                         if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK)
                         {
                             setColor(sibling, RED);
                             if(getColor(parent) == RED)
                                 setColor(parent, BLACK);
                             else
                                 setColor(parent, DOUBLE_BLACK);
                             ptr = parent;
                         }
                         else
                         {
                             if (getColor(sibling->right) == BLACK)
                             {
                                 setColor(sibling->left, BLACK);
                                 setColor(sibling, RED);
                                 rotateRight(sibling);
                                 sibling = parent->right;
                             }
                             setColor(sibling, parent->color);
                             setColor(parent, BLACK);
                             setColor(sibling->right, BLACK);
                             rotateLeft(parent);
                             break;
                         }
                    }
                }
                
                
            }
            if (n == n->parent->left)
                n->parent->left = NULL;
            else
                n->parent->right = NULL;
            delete n;
            setColor(root, BLACK);
        }
            
    }
    
    bool isEmpty()
    {
        return root == NULL;
    }
    
    void displayInOrder(node *nodeptr) const
    {
        if (nodeptr == 0)
            return;
        if (nodeptr->left)
            displayInOrder(nodeptr->left);
        cout << nodeptr->data << endl;
        if (nodeptr->right)
            displayInOrder(nodeptr->right);
        
    }
    
public:
    // public interface
    redblacktree(){
        root = NULL;
    }
    
    void print()
    {
        displayInOrder(root);
    }
    
    ~redblacktree()
    {
        clear();
    }
    
    void clear()
    {
        while (!isEmpty())
            erase(root->data);
    }
    
    void insert(int v){
        node *newNode = new node(v);
        root = insertNode(root, newNode);
        fixInsert(newNode);
    }
    
    void erase(int v)
    {
        node *temp = Delete(root, v);
        fixDelete(temp);
    }
    
    bool find(int v)
    {
        node *tmp = root;
        while (tmp != NULL)
        {
            if (v == tmp->data)
                return true;
            if (v > tmp->data)
                tmp = tmp->right;
            else tmp = tmp->left;
        }
        return false;
    }
};


int main(int argc, const char * argv[]) {
    redblacktree tree;
    cout << "Inserting nodes.\n";
    tree.insert(2);
    tree.insert(1);
    tree.insert(3);
    tree.insert(0);
    tree.insert(8);
    tree.insert(9);
    tree.insert(4);
    tree.insert(5);
    tree.insert(0);
    tree.insert(35);
    tree.insert(40);
    tree.insert(50);
    tree.insert(0);
    tree.insert(13);
    tree.insert(15);
    tree.print();
    tree.erase(9);
    tree.print();
    return 0;
}
