/* 
 * File:   load_certificate.h
 * Author: thiago
 *
 * Created on 30 de Julho de 2015, 10:12
 */

#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <stdio.h>

#ifndef CERTIFICATE_FUNCTION_H
#define	CERTIFICATE_FUNCTION_H

#ifdef	__cplusplus
extern "C" {
#endif

#define ERROR_LOAD_FILE -1
    
   
    
    typedef struct certificate{
        FILE *fp;
        RSA *privateKey;
        RSA *publicKey;
        RSA *remotePublicKey;
        char *private_key_char;
        char *public_key_char;
        unsigned int private_len;
        unsigned int public_len;
        
        
    }CERTIFICATE;
    
    
    int certificate_load(CERTIFICATE *cert, const char *chave_privada, const char *chave_publica);
    
    int rsa_set_certificate(CERTIFICATE *cert, char *pub_key, unsigned int len_pub, char *priv_key, unsigned int len_priv);
    
    int rsa_init(CERTIFICATE *cert);
    
    int rsa_encript_max_len(CERTIFICATE *cert);
    
    int rsa_encript_len_key(CERTIFICATE *cert);
    
    int rsa_encript_with_pub_key(CERTIFICATE *certs, char *src, unsigned int src_len, char **enc, int *enc_len);
    
    int rsa_decritp_with_priv_key(CERTIFICATE *cert, char *src, unsigned int src_len, char **decript, int *dec_len);
    
    int encript_max_len(CERTIFICATE *cert);
    
    int encript_len_key(CERTIFICATE *cert);
    
    int certificate_set_pub_key(CERTIFICATE *cert, const char *pubKey);


#ifdef	__cplusplus
}
#endif

#endif	/* CERTIFICATE_FUNCTION_H */

