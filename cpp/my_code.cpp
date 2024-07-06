#include <iostream>
#include <string>

#include <sodium.h>

#include <openssl/ssl.h>

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
      printf("ERROR: the sodium couldn't be initialized!\n");
      return;
    }
    else
    {
      printf("The sodium is initialized!\n");
    }
    uint32_t rand_val = randombytes_random();
    printf("sodium randombytes: %d\n", rand_val);

    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
  }
}