#include "resistance.h"

float get_resistance(const struct graph_t* g, int color, int i, int j){
  float res = 0.;
  if (gsl_spmatrix_get(g->o, color == 0, i) > 0 || gsl_spmatrix_get(g->o, color == 0, j) > 0){
    res += 1000.;
  }
  if (gsl_spmatrix_get(g->o, color == 0, i) <= 0.01 || gsl_spmatrix(g->o, colorn j) <= 0.01){
    res += 1.;
  }
  return res;
}
 
float** generate_meshes(const struct graph_t* g, int color){
  int n = (sqrt(g->num_vertices) - 1);
  int mesh_nb = n*n;
  float** mat_sys = malloc(sizeof(float*) * (mesh_nb + 1));
  for (int i = 0; i < mesh_nb + 1; i++){
    mat_sys[i] = malloc(sizeof(float) * (mesh_nb + 1));
  }
  for (int i = 0; i < mesh_nb + 1; i++){
    for (int j = 0; j < mesh_nb + 1; j++){
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
  mat_sys[mesh_nb][1] = -get_resistance(g, color, 0);
  mat_sys[mesh_nb][mesh_nb - 1] = -get_resistance(g, color, 0);
  mat_sys[mesh_nb][mesh_nb] = 2 * get_resistance(g, color, 0);
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
  float sum, min, s, ss ;
  /*
  for (int i = 0; i < n; i++){
    printf("(");
    for (int j = 0; j < n; j++){
      printf("%f ",  mat[i][j]);
    }
    printf(")\n");
  }
  */
  for (int i = 0; i < n-1; i++){
    min = mat[i][i];
    imin = i;
    for (int j = i+1; j < n; j++){
      printf("m = %f, ", min);
      if (abs(min) > 0.001 ){
	if ((abs(mat[j][i]) < abs(min)) && (abs(mat[j][i]) > 0.001)){
	  min = mat[j][i];
	  imin = j;
	}
      }
      else{
        min = mat[j][i];
	imin = i;
      }
    }
    printf("\ni ok: %d\n", i);
    if (abs(min) < 0.01){
      printf("\n\n====== problème ======\n\n");
      //      exit;
    }
    for (int j = 0; j < n; j++){
      s = mat[imin][j];
      mat[imin][j] = mat[i][j];
      mat[i][j] = s;
    }
    ss = b[imin];
    b[imin] = b[i];
    b[i] = ss;

    for (j = i+1; j < n; j++){
      p = mat[j][i] / mat[i][i];
      //      printf("division par: %f\n", mat[i][i]);
      for (int k = 0; k < n; k++){
	mat[j][k] -= p * mat[i][k];
      }
      b[j] -= p * b[i];
    }
    //    printf("x: %f\n", x[0]);
  }
  //  printf("x_sortie: %f\n", x[0]);
  if (!mat[n-1][n-1]){
    printf("\n\n====== dernier élément nul ======\n\n");
  }
  //  printf("division_fin par: %f\n", mat[n-1][n-1]);
  x[n-1] = b[n-1] / (mat[n-1][n-1] + mat[n-1][n-1]);
  for (int i = n-2; i+1; i--){
    sum = 0;
    for (int j = n-1; j > i; j--){
      sum += mat[i][j] * x[j];
    }
    x[i] = (b[i] - sum) / mat[i][i];
  }
}
      
float get_ratio(const struct graph_t* g, struct move_t mec){
  struct graph_t* g_copy = copy_graph(g);
  int n = sqrt(g_copy->num_vertices) - 1; 
  float* b = malloc(sizeof(float) * n * n);
  float* x = malloc(sizeof(float) * n * n);
  for (int i = 0; i < n*n; i++){
    x[i] = 0.;
    b[i] = 0.;
  }
  coloriate__graph_t(g_copy, mec.c, mec);
  float** mat_b = generate_meshes(g_copy, 0);//
  float** mat_w = generate_meshes(g_copy, 1);//
  float res_b = 1;// calcul? gauss(mat_b, b, x, n*n);
  for (int i = 0; i < n*n ; x[i++] = 0);
  float res_w = 1;// calcul? gauss(mat_w, b, x, n*n);

  free(g_copy);
  free(b);
  free(x);
  free(mat_w);
  free(mat_b);
  free__graph_t(g_copy);

  if (!res_w){
    return 2000000000;
  }
  return res_b/res_w;
}











    
