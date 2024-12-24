
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ctimer.h"
#include <thread>
#include <vector>
#include <algorithm>
#include <future>

using namespace std;

int main(int argc, char *argv[])
{

  int v, i;
  double suma;

  if (argc < 2)
  {
    printf("Usage: %s n_vectores [tam_max] \n", argv[0]);
    return 1;
  }
  int n_vectores;
  sscanf(argv[1], "%d", &n_vectores);
  int tam_max = 10000;
  if (argc > 2)
  {
    sscanf(argv[2], "%d", &tam_max);
  }

  double **M = (double **)malloc(n_vectores * sizeof(double *));
  int *tam = (int *)malloc(n_vectores * sizeof(int));
  for (v = 0; v < n_vectores; v++)
  {
    tam[v] = rand() % tam_max;
    M[v] = (double *)malloc(tam[v] * sizeof(double));
    for (i = 0; i < tam[v]; i++)
    {
      M[v][i] = (double)rand() / RAND_MAX * 2.0 * tam[v] - 1.0 * tam[v];
    }
  }

  double elapsed, ucpu, scpu;
  ctimer(&elapsed, &ucpu, &scpu);
  double *media = (double *)malloc(n_vectores * sizeof(double));
  double *desvt = (double *)malloc(n_vectores * sizeof(double));

  /*********************************************************/
  // Usando async no hace falta este vector
  future<void>* task = new future<void>[n_vectores];

  // Bucle a paralelizar
  // (media, desvt, M y tam) son variables compartidas
  for (int v = 0; v < n_vectores; v++)
  {
    auto calculate = [&media, &desvt, &M, &tam](int v) { 
        // Cálculo de la media 
        double sum = 0.0; 
        for (int i = 0; i < tam[v]; i++) { sum += M[v][i]; } 
        media[v] = sum / tam[v]; 
        // Cálculo de la desviación típica 
        sum = 0.0; 
        for (int i = 0; i < tam[v]; i++) 
        { sum += (M[v][i] - media[v]) * (M[v][i] - media[v]); } 
        desvt[v] = std::sqrt(sum / tam[v]); 
    };

    task[v] = async(launch::deferred, calculate, v);
  }
  // sincronizamos todos los hilos
  // Nota: con async no hace falta
  for (int i = 0; i < n_vectores; i++)
  {
    task[i].wait();
  }
  /*********************************************************/
  ctimer(&elapsed, &ucpu, &scpu);
  printf("Tiempo = %f segundos\n", elapsed);

  FILE *fp;
  fp = fopen("media_desvt", "wb");
  fwrite(media, sizeof(double), n_vectores, fp);
  fwrite(desvt, sizeof(double), n_vectores, fp);
  fclose(fp);

  free(desvt);
  free(media);
  free(tam);
  for (i = 0; i < n_vectores; i++)
  {
    free(M[i]);
  }
  free(M);
  delete [] task;
  return 0;
}