
#include "enc_dec_message.h"
#include "certificate_function.h"

int enc_dec_init(ENC_DEC_MESSAGE *message, char *pub_key, unsigned int len_pub_key, char *priv_key, unsigned int len_priv){
    
    if (!rsa_set_certificate(&message->rsa_cert, pub_key, len_pub_key, priv_key, len_priv)){
        return 0;
    }
    if (!rsa_init(&message->rsa_cert)){
        return 0;
    }
    
    return 1;
    
}

int enc_message(ENC_DEC_MESSAGE *message, char *src, unsigned len_src, char **enc_msg){
    
    int len;
    char *enc;
    char *sendChar;
    char *encBuff;
    int i, encTotal, parc, encMax;

    encTotal = 0;
    encMax = encript_max_len(&message->rsa_cert);

    
    if ((len_src % encMax)){
        parc = (len_src / encMax) + 1;
    }else{
        parc = (len_src / encMax);
    }
    
    encTotal = (parc) * encript_len_key(&message->rsa_cert);
    encBuff = malloc(encTotal);
    
    if (len_src > encMax) {

        for (i = 0; i < parc; i++) {
            if ((i + 1) * encMax < len_src) {
                if (!rsa_encript_with_pub_key(&message->rsa_cert, &src[i * encMax], encMax, &enc, &len)) {
                    return 0;
                }
                memcpy(&encBuff[i * encript_len_key(&message->rsa_cert)], enc, len);
                free(enc);
            } else {
                if (!rsa_encript_with_pub_key(&message->rsa_cert, &src[i * encMax], len_src - (i * encMax), &enc, &len)) {
                    return 0;
                }
                memcpy(&encBuff[i * encript_len_key(&message->rsa_cert)], enc, len);
                free(enc);
            }
        }


    } else {
        if (!rsa_encript_with_pub_key(&message->rsa_cert, src, len_src, &enc, &len)) {
            return 0;
        }
        
        memcpy(encBuff, enc, len);
        free(enc);
    }

    
    *enc_msg = encBuff;
    
    message->enc_buff = encBuff;


    return encTotal;
    
}


int dec_message(ENC_DEC_MESSAGE *message, char *src, unsigned len_src, char **dec_msg){
   int len;
    char *buffer;
    char *buffer_decrypt;
    char *buffer_rcv;
    char *tmp_recv;
    int len_decrypt,  i, divisor, p;

    len = len_src;
    
    buffer = (char *)malloc(len);
      
    memcpy(buffer, src, len);
    
    divisor = len / rsa_encript_len_key(&message->rsa_cert);
    
    
    p = 0;

    
    for (i = 0; i < divisor; i++){
        rsa_decritp_with_priv_key(&message->rsa_cert, &buffer[i * rsa_encript_len_key(&message->rsa_cert)], rsa_encript_len_key(&message->rsa_cert), &buffer_decrypt, &len_decrypt);
        if (i == 0){
            tmp_recv = malloc(len_decrypt);
        }else{
            tmp_recv = realloc(tmp_recv, p + len_decrypt);
        }
        memcpy(&tmp_recv[p], buffer_decrypt, len_decrypt);
        p += len_decrypt;
        free(buffer_decrypt);
    }
    *dec_msg = tmp_recv;
    message->dec_buff = tmp_recv;

    return p;
}

void enc_dec_free(ENC_DEC_MESSAGE *message){
    free(message->enc_buff);
    free(message->dec_buff);
}