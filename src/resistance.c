#include "resistance.h"

float get_resistance(struct graph_t* g, int color, int n){
  if (gsl_spmatrix_get(g->o, color == 0, n) > 0){
    return 5.;
  }
  if (gsl_spmatrix_get(g->o, color, n) > 0){
    return 0.;
  }
  return 1.;
}

float** generate_meshes(struct graph_t* g, int color){
  int n = (sqrt(g->num_vertices) - 1);
  int mesh_nb = n*n;
  float** mat_sys = malloc(sizeof(float*) * mesh_nb);
  for (int i = 0; i < mesh_nb; i++){
    mat_sys[i] = malloc(sizeof(float) * mesh_nb);
  }
  for (int i = 0; i < mesh_nb; i++){
    for (int j = 0; j < mesh_nb; j++){
      mat_sys[i][j] = 0.;
    }
  }
  int position = 0;
  int c = 0;
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      position = n * i + j;
      mat_sys[position][position] = get_resistance(g, color, position + c);

      mat_sys[position][position] += get_resistance(g, color, position + 1 + c);

      mat_sys[position][position] += get_resistance(g, color, position + n + 1 + c);
	     
      mat_sys[position][position] += get_resistance(g, color, position + n + 2 + c);

      //mat_sys[position][position] = mat_sys[position][position] * 2;
      
      if (position >= n){ //pas première ligne
	mat_sys[position][position - n] -= get_resistance(g, color, position + c);
	mat_sys[position][position - n] -= get_resistance(g, color, position + 1 + c);
      }

      if (position < mesh_nb - n){ //pas dernière ligne
	mat_sys[position][position + n] -= get_resistance(g, color, position + c + n + 1);
	mat_sys[position][position + n] -= get_resistance(g, color, position + c + n + 2);
      }

      if (position % n){ //pas première col
	mat_sys[position][position - 1] -= get_resistance(g, color, position + c);
	mat_sys[position][position - 1] -= get_resistance(g, color, position + c + n + 1);
      }

      if ((position + 1)%n){ //pas dernière col
	mat_sys[position][position + 1] -= get_resistance(g, color, position + c + 1);
	mat_sys[position][position + 1] -= get_resistance(g, color, position + c + n + 2);
      }

      if ((position >= n) && (position % n)){ //pas première ligne/col
	mat_sys[position][position - n - 1] -= get_resistance(g, color, position + c);
      }

      if ((position >= n) && ((position + 1)%n)){ //pas première ligne/dernière col
	mat_sys[position][position - n + 1] -= get_resistance(g, color, position + 1 + c);
      }

      if ((position < mesh_nb - n) && (position % n)){ //pas premmière col/première ligne
	mat_sys[position][position + n - 1] -= get_resistance(g, color, position + c + n + 1);
      }

      if ((position < mesh_nb - n) && ((position + 1) % n)){
	mat_sys[position][position + n + 1] -= get_resistance(g, color, position + c + n + 2);
      }
    }
    c++;
  }
  
  return mat_sys;
}

void free_sys(float** mat, int n){
  for (int i = 0; i < n; i++){
    free(mat[i]);
  }
  free(mat);
}


void gauss(float** mat, float* b, float* x, int n){
  int i, j, k ;
  int imin ;
  float p ;
  float sum, min, tump1, tump2 ;
     
  for (int i = 0; i < n-1; i++){
    min = mat[i][i];
    imin = i;
    for (int j = i+1; j < n; j++){
      if (abs(min) > 0.001 ){
	if ((abs(mat[i][j]) < abs(min)) && (abs(mat[j][i]) > 0.001)){
	  min = mat[j][i];
	  imin = j;
	}
      }
      else{
        min = mat[j][i];
	imin = i;
      }
    }
    if (abs(min) < 0.01){
      printf("\n\n====== problème ======\n\n");
      exit;
    }
    for (int j = 0; j < n; j++){
      tump1 = mat[imin][j];
      mat[imin][j] = mat[i][j];
      mat[i][j] = tump1;
    }
    tump2 = b[imin];
    b[imin] = b[i];
    b[i] = tump2;

    for (j = i+1; j < n; j++){
      p = mat[j][i] / mat[i][i];
      printf("division par: %f\n", mat[i][i]);
      for (int k = 0; k < n; k++){
	mat[j][k] -= p * mat[i][i];
      }
      b[j] -= p * b[i];
    }
    //    printf("x: %f\n", x[0]);
  }
  printf("x_sortie: %f\n", x[0]);
  if (!mat[n-1][n-1]){
    printf("\n\n====== problème_fin ======\n\n");
  }
  printf("division_fin par: %f\n", mat[n-1][n-1]);
  x[n-1] = b[n-1] / mat[n-1][n-1];
  for (int i = n-2; i+1; i--){
    sum = 0;
    for (int j = n-1; j > i; j--){
      sum += mat[i][j] * x[j];
    }
    x[i] = (b[i] - sum) / mat[i][i];
  }
}
      















    
