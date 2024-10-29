//Grupo: Gabriel Costa (14785489), Isabella Arão (9265732), Marina Fagundes (9265405)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_READ_LENGTH 200

int calculateOverlap(char *str1, char *str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
        
    if (len1 >= len2 && strstr(str1, str2) != NULL) {
        return len2;
    }
    
    if (len2 > len1 && strstr(str2, str1) != NULL) {
        return len1;
    }
    
    int overlap = 0;
    for (int i = 1; i <= len1; i++) {
        if (strncmp(str1 + len1 - i, str2, i) == 0) {
            overlap = i;
        }
    }
    
    return overlap;
}

void assembleDNA(char **reads, int numReads) {
    while (numReads > 1) {
        int maxOverlap = -1;
        int idx1 = -1, idx2 = -1;

        for (int i = 0; i < numReads; i++) {
            for (int j = 0; j < numReads; j++) {
                if (i != j) {
                    int overlap = calculateOverlap(reads[i], reads[j]);
                    if (overlap > maxOverlap) {
                        maxOverlap = overlap;
                        idx1 = i;
                        idx2 = j;
                    }
                }
            }
        }

        if (maxOverlap >= 0) {
            int len1 = strlen(reads[idx1]);
            int len2 = strlen(reads[idx2]);
            
            char *assembledSeq;
            
            if (len1 >= len2 && strstr(reads[idx1], reads[idx2]) != NULL) {
                assembledSeq = (char *)malloc((len1 + 1)* sizeof(char));
                strcpy(assembledSeq, reads[idx1]);
            } else if (len2 > len1 && strstr(reads[idx2], reads[idx1]) != NULL) {
                assembledSeq = (char *)malloc((len2 + 1) * sizeof(char));
                strcpy(assembledSeq, reads[idx2]);
            } else {
                assembledSeq = (char *)malloc(MAX_READ_LENGTH * sizeof(char));
                strcpy(assembledSeq, reads[idx1]);
                strcat(assembledSeq, reads[idx2] + maxOverlap);
            }
            
            free(reads[idx1]);
            free(reads[idx2]);
            
            if (idx1 > idx2) {
                int aux = idx1;
                idx1 = idx2;
                idx2 = aux;
            }
            
            for (int i = idx2 + 1; i < numReads; i++) {
                reads[i - 1] = reads[i];
            }
            
            for (int i = idx1 + 1; i < numReads; i++) {
                reads[i - 1] = reads[i];
            }
            
            for (int i = numReads - 1; i > 0; i--) {
                reads[i] = reads[i - 1];
            }
            
            reads[0] = assembledSeq;
            numReads--;
        }
    }

    printf("%s\n", reads[0]);
    free(reads[0]);
}

int main() {
    int numReads;

    scanf("%d", &numReads);

    char **reads = (char **)malloc(numReads * sizeof(char *));
    for (int i = 0; i < numReads; i++) {
            reads[i] = (char *)malloc(MAX_READ_LENGTH * sizeof(char));
            scanf("%s", reads[i]);
    }

    assembleDNA(reads, numReads);

    free(reads);

    return 0;
}