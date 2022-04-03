#include <stdio.h>
#include <string.h>
int main(){
        char filename[21];
        FILE * f;
        int a, i, n;
        printf("Input filename:");
        scanf("%20[^\n]", filename);
        scanf("%*[^\n]");
        scanf("%*c");
        f=fopen(filename, "w");
        if (f==NULL){
                perror(filename);
                return 1;
        }
        printf("Input count of elements:");
        if (scanf("%d", &n)!=1){
                printf("Error\n");
                fclose(f);
                return 1;
        }
        for (i=0; i<n; i++){
                printf("[%d]=", i);
                if (scanf("%d", &a)!=1){
                        printf("Error\n");
                        fclose(f);
                        return 1;
                }
                if (fwrite(&a, sizeof(int), 1, f)!=1){
                        perror("fwrite");
                        fclose(f);
                        return 1;
                }
        }
        fclose(f);
        return 0;
}
