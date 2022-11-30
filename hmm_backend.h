#include "stdafx.h"
#pragma once
#include "config.h"
#include "durbin_functions.h"
#include "HMM_functions.h"
#include "LBG.h"

/*
long double cepstral_values[MAX_T][p];
long double raw_data[100000];
long double *avg;
int result;
string captcha_str;*/

extern long double cepstral_values[MAX_T][p];
extern long double raw_data[500000];
extern long double *avg;
extern int result;
extern string captcha_str;
extern int arg1, arg2;


void read_cep_values(char *filename);
void generate_sequence(char *filename);
void read_codebook(char *filename);
void generate_observation_sequence_training();
void generate_observation_sequence_testing();
void testing_with_stored_data();
void helper2(char *filename);
void seggregation_and_detection(long double *avg, char * input_file, char *output_file);
int test_with_live_data();
void live_training();
int generate_captcha();
void delay(int time);

