#include "stdafx.h"
#include "config.h"

/*
 long double aij[N][N], alpha[MAX_T][N], beta[MAX_T][N], gamma[MAX_T][N], delta[MAX_T][N], psi[MAX_T][N]; 
 long double trained_aij[N][N];
 long double trained_bjk[N][M];
 int Qstar[MAX_T];
long double bjk[N][M], Pstar, xi[MAX_T][N][N], prob_of_obs_given_lambda;
long double aij_bar[N][N];
long double bjk_bar[N][M], Pi_bar[N];
long double Pi[N]={1.00, 0.00, 0.00, 0.00, 0.00};
long double prob_arr[max_samples];
int obs[MAX_T];
int T;*/


extern long double aij[N][N], alpha[MAX_T][N], beta[MAX_T][N], gamma[MAX_T][N], delta[MAX_T][N], psi[MAX_T][N]; 
extern long double trained_aij[N][N];
extern long double trained_bjk[N][M];
extern int Qstar[MAX_T];
extern long double bjk[N][M], Pstar, xi[MAX_T][N][N], prob_of_obs_given_lambda;
extern long double aij_bar[N][N];
extern long double bjk_bar[N][M], Pi_bar[N];
extern long double Pi[N];
extern long double prob_arr[max_samples];
extern int obs[MAX_T];
extern int T;

void display_aij();
void read_aij(char * filename);
void display_bjk();
void read_bjk(char *filename);
void read_obs_seq(char *filename);
void set_aij_bjk();
void set_allmatrix();
long double forward_prc();
void backward_prc();
void calculate_gamma();
void viterbi();
void baum_welch_calculate_xi();
void reestimate_parameters();
void update_aij();
void update_bjk();
void HMM_model(char *filename_aij, char *filename_bjk, char *filename_obs_seq );
void generate_HMM_model();
void store_aij_to_file(char *filename);
void store_bjk_to_file(char *filename);
void read_trained_aij(char *filename);
void read_trained_bjk(char *filename);
void set_matrix_trained_aij();
void set_matrix_trained_bjk();
void avg_out_aij_bjk(int digit);
void write_to_aij_file(char *filename);
void write_to_bjk_file(char *filename);
void copy_file_aij(char * input_file, char *output_file);
void copy_file_bjk(char * input_file, char *output_file);
void store_probabilities(char *filename);
void HMM_training();


			