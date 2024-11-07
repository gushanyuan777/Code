#include "List.h"  
#include <iostream>  
  
int main()  
{   
    List<int> lst;  
   
    for (int i = 0; i < 10; ++i)  
    {  
        lst.push_back(i);  
    }  
   
    lst.pop_back();  
    
    for (auto it : lst)  
    {  
        std::cout << it << std::endl;  
    }  
    
    for (auto it = lst.begin(); it != lst.end(); ++it)  
    {  
        std::cout << *it << std::endl;  
    }  
    
    List<int> lst_init = {1, 2, 3, 4, 5};  
    for (auto &x : lst_init)  
    {  
        std::cout << x << "\t";  
    }  
    std::cout << std::endl;  
  
    List<int> lst_move = List<int>{5, 6};  
    lst_move = std::move(lst_init);  
    for (auto &x : lst_move)  
    {  
        std::cout << x << "\t";  
    }  
    std::cout << std::endl;  
  
    return 0;  
}  