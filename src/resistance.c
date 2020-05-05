#include "resistance.h"

double custom_abs(double p){
  return sqrt(p*p);
}

void print_vect(double* v, int n){
  printf("(");
  for (int i = 0; i < n; i++){
    printf("%f, ", v[i]);
  }
  printf(")\n");
}

void print_m(double** mat, int n){
  for (int i = 0; i < n; i++){
    printf("(");
    for (int j = 0; j < n; j++){
      printf("%f ",  mat[i][j]);
    }
    printf(")\n");
  }
}

double get_resistance(const struct graph_t* g, int color, int i, int j){
  double res = 0.1;
  if (gsl_spmatrix_get(g->o, color == 0, i) > 0 ||
      gsl_spmatrix_get(g->o, color == 0, j) > 0){
    res += 10.;
  }
  if ((gsl_spmatrix_get(g->o, color == 0, i) <= 0.01 &&
       gsl_spmatrix_get(g->o, color , i) <= 0.01 ) ||
      (gsl_spmatrix_get(g->o, color == 0, j) <= 0.01 &&
       gsl_spmatrix_get(g->o, color , j) <= 0.01)){
    res += 1.;
  }
  return res;
}
 
double** generate_meshes(const struct graph_t* g, int color){
  int n = (sqrt(g->num_vertices) - 1);
  int mesh_nb = n*n;
  double** mat_sys = malloc(sizeof(double*) * (mesh_nb + 1));
  for (int i = 0; i < mesh_nb + 1; i++){
    mat_sys[i] = malloc(sizeof(double) * (mesh_nb + 1));
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
      mat_sys[position][position] = get_resistance(g, color, position + c, position + c + 1);

     

      mat_sys[position][position] += get_resistance(g, color, position + c, position + c + 1 + n);

     
	     
      mat_sys[position][position] += get_resistance(g, color, position + 1 + c, position + n + 2 + c);
		   
     
	     
      mat_sys[position][position] += get_resistance(g, color, position + c + n + 1, position + c + n + 2);
				
     
      
      if (position >= n){ //pas première ligne
	mat_sys[position][position - n] -= get_resistance(g, color, position + c, position + c + 1);
      }

      if (position < mesh_nb - n){ //pas dernière ligne
	mat_sys[position][position + n] -= get_resistance(g, color, position + c + n + 1, position + c + n + 2);
      }
      if (position % n){ //pas première col
	mat_sys[position][position - 1] -= get_resistance(g, color, position + c, position + c + n + 1);
      }

      if ((position + 1)%n){ //pas dernière col
	mat_sys[position][position + 1] -= get_resistance(g, color, position + c + 1, position + c + n + 2);
      } 
    }
    c++;
  }

  //DERNIERE LIGNE
  if(color){
    for(int i = 0; i < n; i++){
      mat_sys[mesh_nb][mesh_nb] += get_resistance(g, color, i, i+1);
      mat_sys[mesh_nb][mesh_nb] += get_resistance(g, color, i * (n+1), (i+1) * (n+1));

      mat_sys[mesh_nb][i] -= get_resistance(g, color, i, i+1);      
      mat_sys[mesh_nb][i*n] -= get_resistance(g, color, i * (n+1), (i+1) * (n+1));
    }
  }
  else{
    for(int i = 0; i < n; i++)
      {
	mat_sys[mesh_nb][mesh_nb] += get_resistance(g, color, i, i+1);
	mat_sys[mesh_nb][mesh_nb] += get_resistance(g, color, (i+1) * (n+1) - 1, (i+2) * (n+1) - 1);
	mat_sys[mesh_nb][i] -= get_resistance(g, color, i, i+1);
	mat_sys[mesh_nb][(i+1) * n - 1] -= get_resistance(g, color, (i+1) * (n+1) - 1, (i+2) * (n+1) - 1);
      }
  }

  //DERNIERE COLONNE

  if (color){
    for(int i = 0; i < n; i++)
      {
	mat_sys[i][mesh_nb] -= get_resistance(g, color, i, i+1);
	mat_sys[i*n][mesh_nb] -= get_resistance(g, color, i * (n+1), (i+1) * (n+1));
      }
  }
  else{
    for(int i = 0; i < n; i++)
      {	
	mat_sys[i][mesh_nb] -= get_resistance(g, color, i, i+1);
	mat_sys[(i+1) * n - 1][mesh_nb] -= get_resistance(g, color, (i+1) * (n+1) - 1, (i+2) * (n+1) - 1);
      }
  }
  
  return mat_sys;
}

void free_sys(double** mat, int n){
  for (int i = 0; i < n; i++){
    free(mat[i]);
  }
  free(mat);
}


void gauss(double** mat, double* b, double* x, int n){
  int i, j, k ;
  int imin ;
  double p ;
  double sum, min, s, ss ;
  for (int i = 0; i < n-1; i++){
    min = mat[i][i];
    imin = i;
    for (int j = i+1; j < n; j++){
      if (custom_abs(min) > 0.001 ){
	if ((custom_abs(mat[j][i]) < custom_abs(min)) && (custom_abs(mat[j][i]) > 0.001)){
	  min = mat[j][i];
	  imin = j;
	}
      }
      else{
        min = mat[j][i];
	imin = i;
      }
    }
    if (custom_abs(min) <= 0.001){
      printf("\n\n====== problème gauss ======\n   Underflow probable  \n");
      printf("%f <= 0\n", min);
      printf("\n\n");
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
      for (int k = 0; k < n; k++){
	mat[j][k] -= p * mat[i][k];
      }
      b[j] -= p * b[i];
    }
  }
  if (!mat[n-1][n-1]){
    printf("\n\n====== Problème, dernier élément nul ======\n\n");
  }
  x[n-1] = b[n-1] / (mat[n-1][n-1] + mat[n-1][n-1]);
  for (int i = n-2; i+1; i--){
    sum = 0;
    for (int j = n-1; j > i; j--){
      sum += mat[i][j] * x[j];
    }
    x[i] = (b[i] - sum) / mat[i][i];
  }
}
      
double get_ratio(const struct graph_t* g, struct move_t mec){
  struct graph_t* g_copy = copy_graph(g);
  int n = sqrt(g_copy->num_vertices) - 1; 
  double* b = malloc(sizeof(double) * (n * n + 1));
  double* x = malloc(sizeof(double) * (n * n + 1));
  for (int i = 0; i < n*n + 1; i++){
    x[i] = 0.;
    b[i] = 0.;
  }
  b[n*n] = 10.;
  coloriate__graph_t(g_copy, mec.c, mec);
  double** mat_b = generate_meshes(g_copy, 0);
  double** mat_w = generate_meshes(g_copy, 1);

  gauss(mat_b, b, x, n*n + 1);
  double res_b = (double) 10. / x[n*n];  

  for (int i = 0; i < n*n + 1 ; x[i++] = 0);
  for (int i = 0; i < n*n + 1; b[i++] = 0);
  b[n*n] = 10;
  
  gauss(mat_w, b, x, n*n + 1);
  double res_w = (double) 10. / x[n*n];
  
  free(b);
  free(x);
  free_sys(mat_w, n*n + 1);
  free_sys(mat_b, n*n + 1);
  free__graph_t(g_copy);

  if (!res_w){
    return 2000000000.;
  }

  return res_b/res_w;
}











    
