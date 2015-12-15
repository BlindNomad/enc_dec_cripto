/* 
 * File:   enc_dec_message.h
 * Author: thiago
 *
 * Created on 14 de Dezembro de 2015, 16:41
 */

#ifndef ENC_DEC_MESSAGE_H
#define	ENC_DEC_MESSAGE_H

#include "certificate_function.h"
#include "mensagem.h"


#ifdef	__cplusplus
extern "C" {
#endif
    
    typedef struct enc_dec_message{
        
        CERTIFICATE rsa_cert;
        
        char *enc_buff;
        char *dec_buff;
        
    }ENC_DEC_MESSAGE;

    int enc_dec_init(ENC_DEC_MESSAGE *message, char *pub_key, unsigned int len_pub_key, char *priv_key, unsigned int len_priv);
    
    int enc_message(ENC_DEC_MESSAGE *message, char *src, unsigned len_src, char **enc_msg);
    
    int dec_message(ENC_DEC_MESSAGE *message, char *src, unsigned len_src, char **dec_msg);
    
    void enc_dec_free(ENC_DEC_MESSAGE *message);
    

#ifdef	__cplusplus
}
#endif

#endif	/* ENC_DEC_MESSAGE_H */

