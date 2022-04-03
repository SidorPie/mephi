#include <stdio.h>
#include <string.h>
int main(int argc, char * argv[]){
        FILE * fbin, * ftxt;
        int a, re=0;
        if (argc!=3){
                fprintf(stderr, "Usage:%s binaryfile textfile\n", argv[0]);
                return 1;
        }
        fbin=fopen(argv[1], "rb");
        if (fbin==NULL){
                perror(argv[1]);
                return 1;
        }
        ftxt=fopen(argv[2], "w");
        if (ftxt==NULL){
                fclose(fbin);
                perror(argv[2]);
                return 1;
        }
        while (fread(&a, sizeof(int), 1, fbin)==1){
                if (fprintf(ftxt, "%d\n", a)==0){
                        re=1;
                        perror(argv[2]);
                        break;
                }
        }
        fclose(fbin);
        if (fclose(ftxt)){
                re=1;
                perror(argv[2]);
        }
        return re;
}
