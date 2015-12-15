#include <string.h>
#include <stdlib.h>

#include "mensagem.h"

void m_init(MESSAGE *message){
    
    message->buff = (char *) malloc(3);
    memset(message->buff, 0, 3);
    message->length = 3;
    memcpy(message->buff, &message->length, 2);
    
}

void m_set_type(MESSAGE *message, char type){
    message->buff[2] = type;
}
    
int m_add(MESSAGE *message, char *dat, unsigned short int len){
    
    unsigned short int lenOld = message->length;
    
    message->length += len;
    message->buff = (char *) realloc(message->buff, message->length);
    if (message->buff == NULL){
        return 0;
    }
    
    memcpy(message->buff, &message->length, 2);
    
    memcpy(&message->buff[lenOld], dat, len);
    
    return 1;
    
}


    
char m_get_type(MESSAGE *message){
    return message->buff[2];
}

unsigned short int m_get_buffer(MESSAGE *message, char **buff){
    
    *buff = message->buff;
    
    return message->length;
}

unsigned short int m_get(MESSAGE *message, char **buff){
    *buff = &message->buff[3];
    return message->length - 3;
}

void m_free(MESSAGE *message){
    free(message->buff);
    message->length = 0;
}
