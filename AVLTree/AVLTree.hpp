//
//  AVLTree.hpp
//  AVLTree
//
//  Created by Richard Michael on 10/12/19.
//  Copyright © 2019 Richard Michael. All rights reserved.
//

#ifndef AVLTree_hpp
#define AVLTree_hpp

#include <stdio.h>
#include <stack>
template<typename T>
class AVLTree{
private:
    
    struct Node{
        T val;
        Node* left;
        Node* right;
        int isHead;
        int height;
        Node(T V)
        :left{nullptr},right{nullptr},isHead{-1},height{1}
        {
            val = V;
        }
        Node(T V,int height)
        :left{nullptr},right{nullptr},isHead{-1}
        {
            this->height = height;
            val = V;
        }
        ~Node(){
        }
    };
    
    Node* head;
    
    Node* rightRotate(Node* node){
        Node* temp = node->left;
        if(!node->isHead){
            node->isHead = -1;
            temp->isHead = 0;
            head = temp;
        }
        node->left = temp->right;
        temp->right = node;
        //update heights
        temp->left->height = updateHeightOnRotate(temp->left);
        temp->right->height = updateHeightOnRotate(temp->right);
        temp->height = updateHeightOnRotate(temp);
        return temp;
    }
    Node* leftRotate(Node* node) {
        Node* temp = node->right;
        if(!node->isHead){
            node->isHead = -1;
            temp->isHead = 0;
            head = temp;
        }
        node->right = temp->left;
        if(temp->left!=nullptr){
            Node* temp2 = temp->left;
            temp->left = node;
            temp->left->right = temp2;
            temp->left->right->height = updateHeightOnRotate(temp->left->right)+1;
        }else{
            temp->left = node;
        }
        temp->left->height = updateHeightOnRotate(temp->left)+1;
        temp->right->height = updateHeightOnRotate(temp->right)+1;
        temp->height = updateHeightOnRotate(temp)+1;
        return temp;
    }
    Node* leftRight(Node* node) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    Node* rightLeft(Node* node){
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    Node* delNode(Node* node, bool all){
        //two null children
        if(node->left==nullptr&&node->right==nullptr){
            delete node;
            return nullptr;
        }
        //one null child
        else if(node->left==nullptr||node->right==nullptr){
            if(node->left==nullptr){
                Node* temp = node->right;
                delete node;
                return temp;
            }else{
                Node* temp = node->left;
                delete node;
                return temp;
            }
            //both non-null
        }else{
            std::stack<T> st;
            return node;
        }
        
    }
    int updateHeightOnRotate(Node* node){
        return std::max(getHeight(node->left),getHeight(node->right));
    }
    int getHeight(Node* node){
        if(node!=nullptr){
            return node->height;
        }else{
            return 0;
        }
    }
    Node* addExist(Node* node,T v){
        Node* temp = node->left;
        node->left = new Node(v,std::max(getHeight(node->left),getHeight(node->right))+1);
        node->left->left = temp;
        return node;
        
        
    }
    
    
public:
    AVLTree();
    ~AVLTree();
    AVLTree(const AVLTree &c);
    AVLTree(AVLTree &&c);
    AVLTree &operator=(const AVLTree &c);
    AVLTree &operator=(AVLTree &&c);
    void add(T value,bool all);
    int remove(T value, bool all);
};

template <typename T>
AVLTree<T>::AVLTree()
:head{nullptr}{
}
template <typename T>
AVLTree<T>::~AVLTree(){
    
}

template <typename T>
void AVLTree<T>::add(T value, bool all){
    if(head==nullptr){
        head = new Node(value);
        head->isHead = 0;
        return;
    }
    std::stack<Node*> st;
    Node* it = head;
    while(it!=nullptr){
        st.push(it);
        if(value < it->val){
            it = it->left;
        }else{
            it=it->right;
        }
    }
    if(value==st.top()->val){
        if(all==false){
            return;
        }else{
            st.top() = addExist(st.top(), value);
        }
    }else{
        if(value<st.top()->val){
            st.top()->left = new Node(value);
        }else{
            st.top()->right = new Node(value);
        }
    }
    while(!st.empty()){
        st.top()->height = std::max(getHeight(st.top()->left), getHeight(st.top()->right))+1;
        int balance = getHeight(st.top()->left) - getHeight(st.top()->right);
        
        bool done = false;
        if(balance > 1){
            if(st.top()->left!= nullptr&&st.top()->left->left!=nullptr){
                Node* check = st.top();
                Node* temp = rightRotate(st.top());
                st.pop();
                done = true;
                if(!st.empty()){
                    (st.top()->left==check)?
                    st.top()->left = temp:
                    st.top()->right =temp;
                }
            }else{
                Node* check = st.top();
                Node* temp = leftRight(st.top());
                st.pop();
                done = true;
                if(!st.empty()){
                    (st.top()->left==check)?
                    st.top()->left = temp:
                    st.top()->right =temp;
                }
                
            }
        }else if(balance<-1){
            if(st.top()->right!=nullptr&&st.top()->right->right!=nullptr){
                Node* temp = leftRotate(st.top());
                st.pop();
                done = true;
                if(!st.empty()){
                    st.top()->right = temp;
                }
            }else{
                Node* temp = rightLeft(st.top());
                st.pop();
                done = true;
                if(!st.empty()){
                    st.top()->right = temp;
                }
            }
        }else{
            if(!done)
                done = false;
            st.pop();
        }
    }
}
//return 0 if not found, -1 if error, 1 if success
template <typename T>
int AVLTree<T>::remove(T value, bool all){
    std::stack<Node*> st;
    Node* it;
    if(head==nullptr){
        return 0;
    }else{
        it = head;
        st.push(it);
    }
    while(it!=nullptr){
        if(it->val==value){
            if(st.top()->left!=nullptr&&st.top()->left->val==value){
                st.top()->left = delNode(st.top(), all);
            }
            else{
                st.top()->right = delNode(st.top()->right,all);
            }
        }
        if(value<=it->val){
            it = it->left;
            if(it!=nullptr&&it->val<value){
                return 0;
            }
        }else{
            it = it->right;
            if(it!=nullptr&&it->val>value){
                return 0;
            }
        }
        st.push(it);
    }
    if(it==nullptr)
        return 0;
    while(!st.empty()){
        
        int balance = getHeight(st.top()->left)-getHeight(st.top()->right);
        //off to left
        if(balance>1){
            //check left left
            if(st.top()->left!=nullptr&&st.top()->left!=nullptr){
                Node* check = st.top();
                Node* temp = rightRotate(st.top());
                if(!st.empty()){
                    st.pop();
                    (st.top()->left==check)?
                    st.top()->left = temp:
                    st.top()->right =temp;
                    continue;
                }
            }else{//node is left right
                Node* check = st.top();
                Node* temp = leftRight(st.top());
                if(!st.empty()){
                    st.pop();
                    (st.top()->left==check)?
                    st.top()->left = temp:
                    st.top()->right = temp;
                    continue;
                }
            }
        }else if(balance<1){
            if(st.top()->right!=nullptr&&st.top()->left!=nullptr){
                Node* check = st.top();
                Node* temp = leftRotate(st.top());
                if(!st.empty()){
                    st.pop();
                    (st.top()->left==check)?
                    st.top()->left = temp:
                    st.top()->right =temp;
                    continue;
                }
            }else{
                Node* check = st.top();
                Node* temp = rightLeft(st.top());
                if(!st.empty()){
                    st.pop();
                    (st.top()->left==check)?
                    st.top()->left = temp:
                    st.top()->right =temp;
                    continue;
                }
            }
        }
        st.pop();
    }
    return 0;
}



#endif /* AVLTree_hpp */
