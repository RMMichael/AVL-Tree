//
//  main.cpp
//  AVLTree
//
//  Created by Richard Michael on 10/12/19.
//  Copyright © 2019 Richard Michael. All rights reserved.
//

#include <iostream>
#include "AVLTree.hpp"

int main(int argc, const char * argv[]) {
    
    AVLTree<int> tree;
    bool g = true;
    tree.add(2,g);
    tree.add(1,g);
    tree.add(3,g);
    tree.add(4,g);
    tree.add(5,g);
    tree.remove(1,true);
    int i = 0;
    return 0;
}
