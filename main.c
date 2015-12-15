/* 
 * File:   main.c
 * Author: thiago
 *
 * Created on 14 de Dezembro de 2015, 15:17
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mensagem.h"
#include "enc_dec_message.h"

/*
 * 
 */
int main(int argc, char** argv) {
    
    printf("Teste de criptografia\n");
    
    printf("Teste de mensagem\n");
    
    ENC_DEC_MESSAGE m;
    char escreva[40], *buffer;
    int len, i;
    
    char pub[] = "-----BEGIN PUBLIC KEY-----\n"
                 "MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDXu6FlSBIWXdDiLfpbOFdiJOur\n"
                 "VMXMdiOH9PdBgxE7MGMd/2E2nNoauzicDzg4IwMAgaEgsgPbP3yvDyt/zOFWchoi\n"
                 "vtYp1GKcuXJ0CnxCCMB45LJzxHbnDnZWIk/gMtp2FXAK9dQjIultu5X6mrqYWUf/\n"   
                 "sKX4rTLmCQ4YY6Eq2wIDAQAB\n"
                 "-----END PUBLIC KEY-----";
    unsigned int len_pub = strlen(pub);
    char priv[] = "-----BEGIN PRIVATE KEY-----\n"
"MIICdwIBADANBgkqhkiG9w0BAQEFAASCAmEwggJdAgEAAoGBANe7oWVIEhZd0OIt\n"
"+ls4V2Ik66tUxcx2I4f090GDETswYx3/YTac2hq7OJwPODgjAwCBoSCyA9s/fK8P\n"
"K3/M4VZyGiK+1inUYpy5cnQKfEIIwHjksnPEducOdlYiT+Ay2nYVcAr11CMi6W27\n"
"lfqauphZR/+wpfitMuYJDhhjoSrbAgMBAAECgYAMLEg1INX0cSLCQHnp/8nefdrW\n"
"dhgbK2dh2o7BIZYtUtOk864WmM8txvawx6MSd9dJhgcDg0f4bSKp9h8sPPFSBtZA\n"
"F3DklOitkOdBRW42mGk9rmhjNDq0uycTeHkHkZ5iRpE1384uci0cdGtc9oAqYRvi\n"
"3axVSl3wDImVwXGN4QJBAPrgk/nZuCC406kOtRUdQgKpjYbtbm7F4+dgWouGt26n\n"
"upBZ/WxoyTyULPywJF19pXwODIsnCKBaWBN2XQpwL3MCQQDcI1dFZw0y0IT5WX0B\n"
"3hkt1kFeu+jovCkZQP+iqHs9WRdjD+4tETNijmPx/+iptRCujJusrn+3VdNuEoUA\n"
"5+z5AkEAlq660k+dkzHQF3N4+hSXqEe0dL05HhmH2Fn8KF+i3zipCriySSHq9JK/\n"
"LoqRXQHxmkBJ8m5gdQeubQojufhF1wJADs2VlcYrPgqFlprs7A46VTm+JZevPs9A\n"
"WEFlr1NzDhoKl4+/rWolsW/vypsx0w+o8oPkCAWn8vUjhZhbN0dhSQJBAOamb6Wr\n"
"fV5qRvFL7lHAccRgR7gGDze9/bwFV2Bsdmnjd+dvo/tZTwLTIEO7+3OGI8BAaJ5+\n"
"sWXm8ZJnm1VXIdE=\n"
"-----END PRIVATE KEY-----\n";
    unsigned int len_priv = strlen(priv);
    
    memset(escreva, 0, 40);
    
    printf("Digite a mensagem: ");
    scanf("%s", escreva);
    len = strlen(escreva);
    enc_dec_init(&m, pub, len_pub, priv, len_priv);
    printf("Feito o init\n");
    len = enc_message(&m, escreva, len, &buffer);
    
    for (i = 0; i < len; i++){
        printf("%c", buffer[i]);
    }
    printf(" tamanho %d\n", len);
    
    len = dec_message(&m, buffer, len, &buffer);
     
    printf("Decriptou\n");
    
    
    for (i = 0; i < len; i++){
        printf("%c", buffer[i]);
    }
    
    printf(" tamanho %d\n", len);
    
    enc_dec_free(&m);
    
    return (EXIT_SUCCESS);
}

