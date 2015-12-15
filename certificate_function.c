
#include <stdio.h>
#include <unistd.h>
#include "certificate_function.h"

unsigned int file_size(const char *file){
    unsigned int i;
    char c;
    FILE *fp;
    fp = fopen(file, "r");
    
    if (fp){
        for (i=0; fscanf(fp, "%c", &c) != EOF; i++);
        return i;
    }
    fclose(fp);
    
    return 0;
}


int certificate_load(CERTIFICATE *cert, const char *chave_privada, const char *chave_publica) {
    
    int i;
    FILE *fp_priv;
    FILE *fp_pub;
    
    fp_priv = fopen(chave_privada, "rb");
    fp_pub = fopen(chave_publica, "rb");
    
    if (fp_priv == NULL || fp_pub == NULL){
        return -1;
    }
    
    cert->private_len = file_size(chave_privada);
    cert->public_len = file_size(chave_publica);
    
    cert->private_key_char = malloc(cert->private_len + 1);
    memset(cert->private_key_char, 0, cert->private_len);
    cert->public_key_char = malloc(cert->public_len + 1);
    memset(cert->public_key_char, 0, cert->public_len);
    
    for (i = 0; fscanf(fp_priv, "%c", &cert->private_key_char[i]) != EOF; i++);
    for (i = 0; fscanf(fp_pub, "%c", &cert->public_key_char[i]) != EOF; i++);
    
    
    return 1;
}

int rsa_set_certificate(CERTIFICATE *cert, char *pub_key, unsigned int len_pub, char *priv_key, unsigned int len_priv){
    cert->private_len = len_priv;
    cert->public_len = len_priv;
    cert->private_key_char = malloc(cert->private_len + 1);
    if (cert->private_key_char == NULL){
        return 0;
    }
    memset(cert->private_key_char, 0, cert->private_len);
    cert->public_key_char = malloc(cert->public_len + 1);
    if (cert->public_key_char == NULL){
        return 0;
    }
    memset(cert->public_key_char, 0, cert->public_len);
    memcpy(cert->private_key_char, priv_key, cert->private_len);
    memcpy(cert->public_key_char, pub_key, cert->public_len);
    return 1;
}

int certificate_set_pub_key(CERTIFICATE *cert, const char *pubKey){
    
    memcpy(cert->remotePublicKey, pubKey, strlen(pubKey));
    
}

int rsa_encript_max_len(CERTIFICATE *cert){
    return RSA_size(cert->publicKey) - 42;
}

int rsa_encript_len_key(CERTIFICATE *cert){
    return RSA_size(cert->publicKey);
}


int rsa_init(CERTIFICATE *cert){
    RSA *rsaPriv = NULL;
    BIO *keybioPriv;
    RSA *rsaPub = NULL;
    BIO *keybioPub;
    
    keybioPriv = BIO_new_mem_buf(cert->private_key_char, -1);
    keybioPub = BIO_new_mem_buf(cert->public_key_char, -1);

    if (keybioPriv == NULL || keybioPub == NULL){
        
        return -1;
    }
    
    rsaPub = PEM_read_bio_RSA_PUBKEY(keybioPub, &rsaPub, NULL, NULL);
    rsaPriv = PEM_read_bio_RSAPrivateKey(keybioPriv, &rsaPriv, NULL, NULL);
    cert->privateKey = rsaPriv;
    cert->publicKey = rsaPub;
    BIO_free(keybioPriv);
    BIO_free(keybioPub);
    return 1;
}

int rsa_encript_with_pub_key(CERTIFICATE *cert, char *src, unsigned int src_len, char **enc, int *enc_len){
    int ret;
    char *encrypted;
    
    encrypted = malloc(512);
    memset(encrypted, 0, 512);
    
    ret = RSA_public_encrypt(src_len, (unsigned char*) src, (unsigned char *) encrypted, cert->publicKey, RSA_PKCS1_OAEP_PADDING);
    
    (*enc) = malloc(ret);
    memcpy((*enc), encrypted, ret);
    free(encrypted);
    (*enc_len) = ret;
    
    return 1;
}

int rsa_decritp_with_priv_key(CERTIFICATE *cert, char *src, unsigned int src_len, char **decript, int *dec_len){
    int ret;
    char *decrypted;
    decrypted = malloc(4096);
    memset(decrypted, 0, 4096);
    
    ret = RSA_private_decrypt(src_len, (unsigned char *) src, (unsigned char *) decrypted, cert->privateKey, RSA_PKCS1_OAEP_PADDING);
    
        
    (*decript) = malloc(ret);
    memcpy((*decript), decrypted, ret);
    free(decrypted);
    (*dec_len) = ret;
    return 1;
}

void free_key(CERTIFICATE *cert){
    RSA_free(cert->privateKey);
    RSA_free(cert->publicKey);
    
}

int encript_max_len(CERTIFICATE *cert){
    return RSA_size(cert->publicKey) - 42;
}

int encript_len_key(CERTIFICATE *cert){
    return RSA_size(cert->publicKey);
}