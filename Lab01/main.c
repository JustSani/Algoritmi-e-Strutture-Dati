#include <stdio.h>
#include <string.h>

char *cercaRegexp(char *src, char *regexp);

int main() {
    char src[34] = "fAto";
    char regexp[10] = "f\\Ato";
    char* firstOccurence = cercaRegexp(src, regexp);
    printf("Posizione in %s\n", firstOccurence);
    return 0;
}

char *cercaRegexp(char *src, char *regexp){
    int ok;
    char * firstOccurence = NULL;
    for(int j = 0; j < strlen(src) ; j++){ // scoriamo sia src che regexp,
        ok = 1;
        int i,k;
        for(i = 0, k = j; i < strlen(regexp);k++, i++){
            // vari controlli per determinare la correttezza dell elemento src corrente con la regex
            if(regexp[i] == '.')
                ok = 1;
            else if(regexp[i] == '['){
                i++;
                if(regexp[i] != '^')
                    do{
                        ok = 0;
                        if(regexp[i] == src[k]){
                            ok = 1;
                            break;
                        }
                    }while(regexp[++i] != ']');
                else{
                    ok = 1;
                    do{
                        if(regexp[i] == src[k]){
                            ok = 0;
                            break;
                        }
                    }while(regexp[++i] != ']');
                }
            }
            else if(regexp[i] == '\\'){
                i++;
                if(regexp[i] == 'a' && src[k] < 'z' && src[k] > 'a')
                    ok = 1;
                else if(regexp[i] == 'A' && src[k] < 'Z' && src[k] > 'A')
                    ok = 1;
                else ok = 0;
            }
            else if (regexp[i] == src[k])
                ok = 1;
            else ok = 0;
            // end controlli

            printf("ok: %d, ", ok);
            if(ok == 1){ // se è tutto ok fino a adesso incrementiamo la regex e l'elemento j-esimo della src, se è la prima volta che superiamo i controlli allora salviamo l'occorrenza
                if(i == 0)
                    firstOccurence = src + k;
            }
            else{ // se ce stato un errore impostiamo l'occorenza a null
                firstOccurence = NULL;
                break;
            }
        }
        if (i == strlen(regexp))
            return firstOccurence;
    }
    return firstOccurence;

}