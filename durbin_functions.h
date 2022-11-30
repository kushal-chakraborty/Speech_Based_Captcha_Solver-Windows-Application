#include "stdafx.h"
#include "config.h"

/*
//long double tokhuraWeights[]={1.0, 3.0, 7.0, 13.0, 19.0, 22.0, 25.0, 33.0, 42.0, 50.0, 56.0, 61.0};
long double my_weights[]={0.3, 0.6, 1.0, 0.6, 0.3};
long int file_no, acc=0, no_of_frames;
long double nfactor, dcshift, sum=0.0, d, dist, final_dist, mindst;
long int dsize, start, end, i, j, k, m, f, index, v, fno;
long double data[100000], frames_data[max_no_frames+10][frame_size], energy_data[100000];
long double R[max_no_frames+10][p+1], E[p+1], a[p+1][p+1], K[p+1], C[max_no_frames+10][p+1], Alpha[max_no_frames+10][p+1], read_Ci[max_no_frames+10][p+1];
*/

extern long double my_weights[];
extern long int file_no, acc, no_of_frames;
extern long double nfactor, dcshift, sum, d, dist, final_dist, mindst;
extern long int dsize, start, end, i, j, k, m, f, index, v, fno;
extern long double data[500000], frames_data[max_no_frames+10][frame_size], energy_data[500000];
extern long double R[max_no_frames+10][p+1], E[p+1], a[p+1][p+1], K[p+1], C[max_no_frames+10][p+1], Alpha[max_no_frames+10][p+1], read_Ci[max_no_frames+10][p+1];


void calc_dcshift(char *filename);
void calc_nfactor(char *filename);
void normalize_data(char * inpfile);
void apply_hamming_window();
void apply_raisedsine_window();
void add_Cis_to_universe(char *filename);
void store_Cis_to_file(char *filename);
void calculate_cis();
void apply_durbins_algo();
void calculate_Ris();
void extract_frames(char * filename);
void compute_cepstral_testing();
void build_universe();
int max(int a, int b);
int min(int a, int b);

