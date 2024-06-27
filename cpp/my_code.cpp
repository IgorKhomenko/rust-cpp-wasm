#include <iostream>
#include <string>

#include <sodium.h>

extern "C"
{ 
  void hello()
  {
    std::string str = "World";
    const char *cstr = str.c_str();
    std::cout << "[hello] Hello, " << str << " from C++! (std::cout)" << std::endl;
    printf("[hello] Hello %s from C++! (printf)\n", cstr);

    if (sodium_init() < 0)
    {
      /* panic! the library couldn't be initialized; it is not safe to use */
      printf("the sodium couldn't be initialized!\n");
      return;
    }
    else
    {
      printf("the sodium is initialized!\n");
    }
  }
}