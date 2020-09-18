//
//     See http://fm4dd.com/openssl/eckeycreate.shtm
//

#include <stdio.h>
#include <stdlib.h>
#include <openssl/bio.h>      // bio io streams for openssl
#include <openssl/err.h>
#include <openssl/ssl.h>
#include <openssl/obj_mac.h>  //needed for elliptic curve
#include <openssl/ec.h>       //needed for elliptic curve

#define BuffSize 1024
void report_and_exit(const char* msg) {
  perror(msg);
  ERR_print_errors_fp(stderr);
  exit(-1);
}

void init_ssl() {
  //  SSL_library_init();
  OpenSSL_add_all_algorithms(); //initialize table for all ciphers and digests
  ERR_load_BIO_strings(); 
  SSL_load_error_strings();
}

void cleanup(SSL_CTX* ctx, BIO* bio, EC_KEY *myecc, EVP_PKEY *pkey) {
  EVP_PKEY_free(pkey);
  EC_KEY_free(myecc);
  //SSL_CTX_free(ctx);
  BIO_free_all(bio);
  ERR_free_strings();
}

int main(int c, const char* argv[])
{
  EC_KEY   *key=NULL;    //Key pair
  EVP_PKEY *pkey=NULL;   //PublicKey
  BIO      *outbio=NULL; //Stream
  int      eccgrp;

  init_ssl(); //Initialize OpenSSL
  //
  //.....Create BIOs
  // 
  outbio = BIO_new(BIO_s_file());
  outbio = BIO_new_fp(stdout, BIO_NOCLOSE);
  //
  //.....Create key

  /* ---------------------------------------------------------- *
   * Create a EC key sructure, setting the group type from NID  *
   * ---------------------------------------------------------- */
  eccgrp = OBJ_txt2nid("secp256k1");
  key    = EC_KEY_new_by_curve_name(eccgrp);

  /* -------------------------------------------------------- *
   * For cert signing, we use  the OPENSSL_EC_NAMED_CURVE flag*
   * ---------------------------------------------------------*/
  EC_KEY_set_asn1_flag(key, OPENSSL_EC_NAMED_CURVE);

  /* -------------------------------------------------------- *
   * Create the public/private EC key pair here               *
   * ---------------------------------------------------------*/
  if (! (EC_KEY_generate_key(key)))
    BIO_printf(outbio, "Error generating the ECC key.");

  /* -------------------------------------------------------- *
   * Converting the EC key into a PKEY structure let us       *
   * handle the key just like any other key pair.             *
   * ---------------------------------------------------------*/
  pkey=EVP_PKEY_new();
  if (!EVP_PKEY_assign_EC_KEY(pkey,key))
    BIO_printf(outbio, "Error assigning ECC key to EVP_PKEY structure.");
  /* ---------------------------------------------------------- *
   * Here we print the private/public key data in PEM format.   *
   * ---------------------------------------------------------- */
  if(!PEM_write_bio_PrivateKey(outbio, pkey, NULL, NULL, 0, 0, NULL))
    BIO_printf(outbio, "Error writing private key data in PEM format");

  if(!PEM_write_bio_PUBKEY(outbio, pkey))
    BIO_printf(outbio, "Error writing public key data in PEM format");

  //
  //.....Exit
  //
  cleanup(NULL,outbio,key,pkey);
  exit(0);
}
