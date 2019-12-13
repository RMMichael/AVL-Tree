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
#include <queue>
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
    bool all;
    Node* head;
    int size;
    
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
        if(temp->left!=nullptr)
            temp->left->height = updateHeightOnRotate(temp->left);
        if(temp->right!=nullptr)
            temp->right->height = updateHeightOnRotate(temp->right);
        if(temp!=nullptr)
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
        temp->left = node;
        if(temp->left!=nullptr)
            temp->left->height = updateHeightOnRotate(temp->left);
        if(temp->right!=nullptr)
            temp->right->height = updateHeightOnRotate(temp->right);
        if(temp!=nullptr)
            temp->height = updateHeightOnRotate(temp);
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
    Node* delNode(Node* node){
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
           // Node* ins = node;
            std::stack<Node*> st;
            st.push(node);
            Node* find = node->right;
            st.push(find);
            while(find->left!=nullptr){
                find = find->left;
                st.push(find);
            }
            node->val = find->val;
            Node* temp = delNode(find);
            st.pop();
            (st.top()->right!=nullptr&&st.top()->right->val==node->val)?
                    st.top()->right = temp:
                    st.top()->left = temp;
            bool done = false;
            while(!st.empty()){
                st.top()->height = std::max(getHeight(st.top()->left),getHeight(st.top()->right))+1;
                
                int balance = getHeight(st.top()->left) - getHeight(st.top()->right);
                
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
                        }else{
                            node = temp;
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
                        }else{
                            node = temp;
                        }
                    }
                }else if(balance<-1){
                    if(st.top()->right!=nullptr&&st.top()->right->right!=nullptr){
                        Node* check = st.top();
                        Node* temp = leftRotate(st.top());
                        st.pop();
                        done = true;
                        if(!st.empty()){
                            (st.top()->left==check)?
                                st.top()->left = temp:
                                st.top()->right =temp;
                        }else{
                            node = temp;
                        }
                    }else{
                        Node* check = st.top();
                        Node* temp = rightLeft(st.top());
                        st.pop();
                        done = true;
                        if(!st.empty()){
                            (st.top()->left==check)?
                                st.top()->left = temp:
                                st.top()->right =temp;
                        }else{
                            node = temp;
                        }
                    }
                }else{
                    st.pop();
                }
            }
            //return node;
        }
        return node;
    }
    int updateHeightOnRotate(Node* node){
        if(node!=nullptr){
        return std::max(getHeight(node->left),getHeight(node->right))+1;
        }
        else{
            return 0;
        }
    }
    int getHeight(Node* node){
        if(node!=nullptr){
            return node->height;
        }else{
            return 0;
        }
    }
    Node* append(Node* node,Node* append){
        if(node!=nullptr){
            if(node->val<append->val){
                
            }
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
    AVLTree(bool all);
    ~AVLTree();
    AVLTree(const AVLTree &c);
    AVLTree(AVLTree &&c);
    AVLTree &operator=(const AVLTree &c);
    AVLTree &operator=(AVLTree &&c);
    bool isVal(T value) const;
    void add(T value);
    int remove(T value);
};

template <typename T>
AVLTree<T>::AVLTree()
:head{nullptr},size{0},all{false}{
}
template <typename T>
AVLTree<T>::AVLTree(bool all)
:head{nullptr},size{0}{
    this->all = all;
}
template <typename T>
AVLTree<T>::~AVLTree(){
    
}
template <typename T>
bool AVLTree<T>::isVal(T value) const{
    Node* searchNode = head;
    while(searchNode!=nullptr){
        if(searchNode->val==value){
            break;
        }
        (searchNode->val < value)?
            searchNode= searchNode->right:
            searchNode = searchNode->left;
    }
    return(searchNode!=nullptr);
}

template <typename T>
void AVLTree<T>::add(T value){
    size++;
    if(head==nullptr){
        head = new Node(value);
        head->isHead = 0;
        return;
    }
    std::stack<Node*> st;
    Node* it = head;
    while(it!=nullptr){
        st.push(it);
        if(value==st.top()->val){
        if(all==false){
            return;
        }else{
            st.top() = addExist(st.top(), value);
            it = nullptr;
            }
        }
        else if(value < it->val){
            it = it->left;
        }else{
            it=it->right;
        }
    }
    if(value<st.top()->val){
        st.top()->left = new Node(value);
    }else if(value!=st.top()->val){
        st.top()->right = new Node(value);
    }
    bool done = false;
    while(!st.empty()){
        
        st.top()->height = std::max(getHeight(st.top()->left), getHeight(st.top()->right))+1;
        
        int balance = getHeight(st.top()->left) - getHeight(st.top()->right);
        
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
                Node* check = st.top();
                Node* temp = leftRotate(st.top());
                st.pop();
                done = true;
                if(!st.empty()){
                    (st.top()->left==check)?
                        st.top()->left = temp:
                        st.top()->right =temp;
                }
            }else{
                Node* check = st.top();
                Node* temp = rightLeft(st.top());
                st.pop();
                done = true;
                if(!st.empty()){
                    (st.top()->left==check)?
                        st.top()->left = temp:
                        st.top()->right =temp;
                }
            }
        }else{
            st.pop();
        }
    }
}
//return 0 if not found, -1 if error, 1 if success
template <typename T>
int AVLTree<T>::remove(T value){
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
            if(st.top()==head){
                head = delNode(st.top());
                break;
            }
            Node* temp = st.top();
            st.pop();
            if(st.top()->left!=nullptr&&st.top()->left->val==value){
                st.top()->left = delNode(temp);
            }
            else{
                st.top()->right = delNode(temp);
            }
            break;
        }
        else if(value<it->val){
            it = it->left;
            st.push(it);
            if(it==nullptr){
                return 0;
            }
            
        }
        else if(value >it->val){
            it = it->right;
            st.push(it);
            if(it==nullptr){
                return 0;
            }
        }
        
    }
    bool done = false;
    while(!st.empty()){
        st.top()->height = std::max(getHeight(st.top()->left),getHeight(st.top()->right))+1;
        int balance = getHeight(st.top()->left) - getHeight(st.top()->right);
        
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
                Node* check = st.top();
                Node* temp = leftRotate(st.top());
                st.pop();
                done = true;
                if(!st.empty()){
                    (st.top()->left==check)?
                        st.top()->left = temp:
                        st.top()->right =temp;
                }
            }else{
                Node* check = st.top();
                Node* temp = rightLeft(st.top());
                st.pop();
                done = true;
                if(!st.empty()){
                    (st.top()->left==check)?
                        st.top()->left = temp:
                        st.top()->right =temp;
                }
            }
        }else{
            st.pop();
        }
    }
    return 1;
}



#endif /* AVLTree_hpp */
