#include <stdio.h>
#include <stdlib.h>

void preencherInscr(int n, int *inscr);
void preencherNotas(int n, float *t1, float *t2, int *inscr);
int *premiados(int n, int *inscr, float *t1, int p1, float *t2, int p2, int *tam);

int main(){

    int n;

    printf("\nDigite a quantidade de participantes: ");
    scanf("%d",&n);

    int inscr[n];
    preencherInscr(n, inscr);

    float t1[n];
    float t2[n];
    preencherNotas(n, t1, t2, inscr);

    int p1, p2;
    printf("\nDigite o peso da nota 1: ");
    scanf("%d", &p1);
    printf("Digite o peso da nota 2: ");
    scanf("%d", &p2);

    int tam;
    int *premiados_indices = premiados(n, inscr, t1, p1, t2, p2, &tam);

    printf("\nInscrições dos participantes premiados:\n");
    for (int i = 0; i < tam; i++) {
        printf("%d\n", premiados_indices[i]);
    }
    printf("\n")

    free(premiados_indices);

    return 0;
}

void preencherInscr(int n, int *inscr){
    printf("\nRecebendo as inscrições de %d participantes!\n",n );
    for(int i = 0; i < n; i++){
        printf("Participante %d: ", i+1);
        scanf("%d", &inscr[i]);
    }
    printf("\nInscrições feitas!\n");
}

void preencherNotas(int n, float *t1, float *t2, int *inscr){
    printf("\nPreenchendo as notas 1 de cada participante!\n");
    for(int i = 0; i < n; i++){
        printf("Nota 1 da inscrição %d: ", inscr[i]);
        scanf("%f", &t1[i]);
    }
    printf("\nPreenchendo as notas 2 de cada participante!\n");
    for(int i = 0; i < n; i++){
        printf("Nota 2 da inscrição %d: ", inscr[i]);
        scanf("%f", &t2[i]);
    }
    printf("\nNotas preenchidas!\n");
}

int *premiados(int n, int *inscr, float *t1, int p1, float *t2, int p2, int *tam) {
    float *media_ponderada = (float *)malloc(n * sizeof(float));

    for (int i = 0; i < n; i++) {
        media_ponderada[i] = (t1[i] * p1 + t2[i] * p2) / (p1 + p2);
    }

    float maior_media = media_ponderada[0];
    for (int i = 1; i < n; i++) {
        if (media_ponderada[i] > maior_media) {
            maior_media = media_ponderada[i];
        }
    }

    *tam = 0;
    for (int i = 0; i < n; i++) {
        if (media_ponderada[i] == maior_media) {
            (*tam)++;
        }
    }

    int *premiados_indices = (int *)malloc((*tam) * sizeof(int));

    int index = 0;
    for (int i = 0; i < n; i++) {
        if (media_ponderada[i] == maior_media) {
            premiados_indices[index] = inscr[i];
            index++;
        }
    }

    free(media_ponderada);

    return premiados_indices;
}
