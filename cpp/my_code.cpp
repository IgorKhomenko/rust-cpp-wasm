#include <iostream>
#include <string>

#include <sodium.h>

#include <openssl/ssl.h>
#include <openssl/evp.h>
#include <openssl/x509.h>
#include <openssl/err.h>

#include <boost/algorithm/string.hpp>

struct KeyPair
{
  std::vector<uint8_t> public_key;
  std::vector<uint8_t> private_key;
};

extern "C"
{ 
  void hello()
  {
    // Test C++
    //
    std::string str = "World";
    const char *cstr = str.c_str();
    std::cout << "[hello] Hello, " << str << " from C++! (std::cout)" << std::endl;
    printf("[hello] Hello %s from C++! (printf)\n", cstr);

    // Test libsodium
    //
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
    printf("Sodium randombytes: %d\n", rand_val);

    // Test openssl
    //
    KeyPair key_pair;
    //
    // Generate a new Ed448 key pair using the OpenSSL EVP_PKEY_keygen function
    EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_ED448, NULL);
    EVP_PKEY_keygen_init(ctx);
    EVP_PKEY *pkey = EVP_PKEY_new();
    EVP_PKEY_keygen(ctx, &pkey);

    // Extract the raw private key bytes
    size_t private_key_len = 0;
    EVP_PKEY_get_raw_private_key(pkey, NULL, &private_key_len);
    std::vector<unsigned char> private_key_data(private_key_len);
    EVP_PKEY_get_raw_private_key(pkey, private_key_data.data(), &private_key_len);

    // Extract the raw public key bytes
    size_t public_key_len = 0;
    EVP_PKEY_get_raw_public_key(pkey, NULL, &public_key_len);
    std::vector<unsigned char> public_key_data(public_key_len);
    EVP_PKEY_get_raw_public_key(pkey, public_key_data.data(), &public_key_len);

    // Convert the binary encoding of the public and private keys to vectors of uint8_t and return them
    key_pair.public_key = std::vector<uint8_t>(public_key_data.begin(), public_key_data.end());
    key_pair.private_key = std::vector<uint8_t>(private_key_data.begin(), private_key_data.end());

    // Free the resources used by the EVP_PKEY and EVP_PKEY_CTX objects
    EVP_PKEY_free(pkey);
    EVP_PKEY_CTX_free(ctx);

    for (auto i : key_pair.public_key)
      printf("Openssl public_key: %d\n", i);
    for (auto i : key_pair.private_key)
      printf("Openssl private_key: %d\n", i);

    // Test boost
    //
    std::string s = "Boost Libraries";
    boost::to_upper(s);
    printf("[hello] Boost Upper Case test: %s\n", s.c_str());
  }

  pid_t getpid(void) {
    return 1;
  }
}