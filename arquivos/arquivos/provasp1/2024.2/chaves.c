#include <stdio.h>

int main(int argc, char **argv){
    if(argc != 2){
        fprintf(stderr, "Uso: %s [ARQUIVO]", argv[0]);
    }
    
    FILE *f = fopen(argv[1], "rb");
    
    if(!f){
        fprintf(stderr, "Não foi possível abrir o arquivo %s", argv[1]);
        return 1;
    }
    
    int count = 0;
    int c;
    
    c = fgetc(f);
    
    while(c != EOF){
        if (c == '{')
            count++;
        if (c == '}'){
            count--;
            
            if(count < 0){
                printf("Há uma chave fechada } sem uma chave aberta { correspondente.\n");
                fclose(f);
                return 1;
            }
        }
                
        c = fgetc(f);
    }
    
    if(count > 0)
        printf("Há alguma chave ( { ) pendente no programa. Precisa ser fechada.");
    else if(count < 0)
        printf("Há alguma chave ( { ) a mais no programa. Precisa ser corrigido.");
    else
        printf("Todas as chaves estao certas.");
        
    fclose(f);
    
    return 0;
}
