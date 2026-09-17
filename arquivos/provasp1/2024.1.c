#include <stdio.h>

int main(){
    char bloco[3] = {0};
    FILE* f = fopen("letras.dat","rb");
    fseek(f,-2,SEEK_END);
    //fread avança. ftell acompanha isso. começa no 0.
    fread(bloco,sizeof(char),3,f);
    printf("(a) %3.3s %ld %d\n", bloco, ftell(f), feof(f));
    fseek(f,-3,SEEK_END);
    fread(bloco,sizeof(char),3,f);
    printf("(b) %3.3s %ld %d\n", bloco, ftell(f), feof(f));
    fseek(f,10,SEEK_SET);
    fread(bloco,sizeof(char),3,f);
    printf("(c) %3.3s %ld %d\n", bloco, ftell(f), feof(f));
    fread(bloco,sizeof(char),3,f);
    printf("(d) %3.3s %ld %d\n", bloco, ftell(f), feof(f));
    fseek(f,-3,SEEK_CUR);
    fread(bloco,sizeof(char),3,f);
    printf("(e) %3.3s %ld %d\n", bloco, ftell(f), feof(f));
    fclose(f);

    return 0;
}