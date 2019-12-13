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
    
    
    for(int i=0;i<200;i++){
        tree.add(i);
    }
    for(int i=0;i<200;i++){
        std::cout << tree.isVal(i) << "    " << i << std::endl;
    }
      
    for(int i =0;i<80;i++){
        int temp = std::rand()%200;
        tree.remove(temp);
    }
    for(int i=0;i<200;i++){
        std::cout << tree.isVal(i) << "    " << i << std::endl;
    }
    
   // tree.remove(1,true);
    int i = 0;
    return 0;
}
