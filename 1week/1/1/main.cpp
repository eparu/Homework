//
//  main.cpp
//  1
//
//  Created by Kate on 11.02.2021.
//  Copyright © 2021 Kate. All rights reserved.
//
// ==================


#include <iostream>
int g(int a);

int main(int argc, const char * argv[]) {
    g(3);

    // insert code here...
    std::cout << std::endl;
    std::cout << "Hello, World!\n";
    
    g(7);
    
    g(10);
    return 0;
}

int g(int a)
{
    std::cout << a;
}
