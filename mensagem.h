/* 
 * File:   mensagem.h
 * Author: thiago
 *
 * Created on 14 de Dezembro de 2015, 15:34
 */

#ifndef MENSAGEM_H
#define	MENSAGEM_H

#ifdef	__cplusplus
extern "C" {
#endif


    typedef struct message{
        
        unsigned short int length;
        char *buff;
        
    }MESSAGE;
    
    void m_init(MESSAGE *message);
    
    void m_set_type(MESSAGE *message, char type);
    
    int m_add(MESSAGE *message, char *dat, unsigned short int len);
    
    char m_get_type(MESSAGE *message);
    
    unsigned short int m_get_buffer(MESSAGE *message, char **buff);
    
    unsigned short int m_get(MESSAGE *message, char **buff);
    
    void m_free(MESSAGE *message);
    

#ifdef	__cplusplus
}
#endif

#endif	/* MENSAGEM_H */

