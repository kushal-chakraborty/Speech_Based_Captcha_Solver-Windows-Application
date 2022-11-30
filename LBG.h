#include "stdafx.h"
#include "config.h"

/*
long double universe_data[100000][p];
long double codebook[codebook_size][p], newcodebook[codebook_size][p];
int cluster_size[codebook_size];
long double Weights[]={1.0, 3.0, 7.0, 13.0, 19.0, 22.0, 25.0, 33.0, 42.0, 50.0, 56.0, 61.0};
long int assigned_cluster[100000]={0};
long int no_of_rows=0;
int cbook_size=1;*/


extern long double universe_data[500000][p];
extern long double codebook[codebook_size][p], newcodebook[codebook_size][p];
extern int cluster_size[codebook_size];
extern long double Weights[];
extern long int assigned_cluster[500000];
extern long int no_of_rows;
extern int cbook_size;

void initialise_codebook();
long double calculate_tokhura(long double A[p], long double B[p]);
void assign_cluster_to_data();
long double calculate_distortion();
void update_codebook();
void kmeans();
void display_codebook();
void LBG_initialization();
void LBG();
void display_universe_data();
void store_final_codebook(char * output_file);
void read_universe_data(char *input_file);
void generate_codebook();
