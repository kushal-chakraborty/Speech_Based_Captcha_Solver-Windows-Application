#include "stdafx.h";
#include "hmm_backend.h"

int no_of_training_samples=90;
int no_of_testing_samples=5;

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
int T;

long double universe_data[500000][p];
long double codebook[codebook_size][p], newcodebook[codebook_size][p];
int cluster_size[codebook_size];
long double Weights[]={1.0, 3.0, 7.0, 13.0, 19.0, 22.0, 25.0, 33.0, 42.0, 50.0, 56.0, 61.0};
long int assigned_cluster[500000]={0};
long int no_of_rows=0;
int cbook_size=1;

//long double tokhuraWeights[]={1.0, 3.0, 7.0, 13.0, 19.0, 22.0, 25.0, 33.0, 42.0, 50.0, 56.0, 61.0};
long double my_weights[]={0.3, 0.6, 1.0, 0.6, 0.3};
long int file_no, acc=0, no_of_frames;
long double nfactor, dcshift, sum=0.0, d, dist, final_dist, mindst;
long int dsize, start, end, i, j, k, m, f, index, v, fno;
long double data[500000], frames_data[max_no_frames+10][frame_size], energy_data[500000];
long double R[max_no_frames+10][p+1], E[p+1], a[p+1][p+1], K[p+1], C[max_no_frames+10][p+1], Alpha[max_no_frames+10][p+1], read_Ci[max_no_frames+10][p+1];

long double cepstral_values[MAX_T][p];
long double raw_data[500000];
long double *avg;
int result;
string captcha_str;
int arg1, arg2;

void read_cep_values(char *filename){

	FILE *fp;
	char str[300];
	long int j;


	fp=fopen(filename, "r");
	no_of_rows=-1;

	while(!feof(fp)){
		j=0;
		fgets(str, 200, fp); //read a line from the file
		//printf("%s", str);
		char *val=strtok(str, ",");
		no_of_rows++;
		while(val!=NULL){
			long double d=atof(val);
			cepstral_values[no_of_rows][j]=d;
			j++;
			val=strtok(NULL, ",");  //cut the string separated by comma
		}
		//printf("The no of columns is %d \n", j);
		//printf("Reading of row %d \n", row);
		//no_of_rows++;
	}
}

void generate_sequence(char *filename){

	int i, j, obs_no;
	FILE *fp;
	fp=fopen(filename, "w");

	for(i=0;i<no_of_rows;i++){
		long double min=10000000000.0000;
		for(j=0;j<codebook_size;j++){

			long double dist=0;
			/*
			for(k=0;k<p;k++){
				long double d=abs(codebook[j][k]-data[i][k]);
				dist+=tokhuraWeights[k]*d*d;
				//dist=d*d;
			}*/
			dist=calculate_tokhura(codebook[j], cepstral_values[i]); //distance measure used is Tokhura's distance
			//if(i==250)
				//printf("Tokhura dist for data %d  with respect to cluster %d is %f\n", i, j, dist);
			if(min>dist){
				min=dist;
				obs_no=j;
			}
		}
		obs[i]=obs_no;
		fprintf(fp, "%d\n", obs_no);
	}
	fclose(fp);
}


void read_codebook(char *filename){
	
	FILE *fp;
	char str[300];
	long int j;

	no_of_rows=0;

	fp=fopen(filename, "r");

	while(!feof(fp)){
		j=0;
		fgets(str, 200, fp); //read a line from the file
		//printf("%s", str);
		char *val=strtok(str, ",");
		//no_of_rows++;
		while(val){
			long double d=atof(val);
			//printf("Value read is %lf\n", d);
			if(no_of_rows<codebook_size && j<p)
				codebook[no_of_rows][j]=d;
			j++;
			val=strtok(NULL, ",");  //cut the string separated by comma
		}
		printf("\n");
		//printf("The no of columns is %d \n", j);
		//printf("Reading of row %d \n", row);
		no_of_rows++;
	}
	no_of_rows--;
	fclose(fp);
}



void generate_observation_sequence_training(){

	char inp_cep_file[150];
	char codebook_filename[150];
	char out_obs_seq_file[150];
	int i, j;

	sprintf(&codebook_filename[0], "./Codebook/English/Codebook_English.csv");
	read_codebook(codebook_filename);
	cbook_size=32;
	//display_codebook();


	for(i=0;i<no_of_digits;i++){
		//for(j=0;j<total_samples;j++){
		for(j=0;j<no_of_training_samples;j++){
			sprintf(&inp_cep_file[0], "./Cepstral_values/English/digit_%d/utterance_%d.csv", i, j);
			sprintf(&out_obs_seq_file[0], "./Observations/English/digit_%d/Obs_Eng_digit_%d_utterance_%d.txt", i, i, j);
			read_cep_values(inp_cep_file);
			remove(out_obs_seq_file);
			generate_sequence(out_obs_seq_file);
		}
	}
}


void generate_observation_sequence_testing(){

	char inp_cep_file[150];
	char codebook_filename[150];
	char out_obs_seq_file[150];
	int i, j;

	sprintf(&codebook_filename[0], "./Codebook/English/Codebook_English.csv");
	read_codebook(codebook_filename);
	cbook_size=32;
	//display_codebook();


	for(i=0;i<no_of_digits;i++){
		//for(j=0;j<total_samples;j++){
		for(j=0;j<no_of_testing_samples;j++){
			sprintf(&inp_cep_file[0], "./Cepstral_values/English/digit_%d/test_utterance_%d.csv", i, j);
			sprintf(&out_obs_seq_file[0], "./Observations/English/digit_%d/Obs_Eng_digit_%d_test_utterance_%d.txt", i, i, j);
			read_cep_values(inp_cep_file);
			remove(out_obs_seq_file);
			generate_sequence(out_obs_seq_file);
		}
	}

}


void testing_with_stored_data(){

	char test_file_obs_seq[150];
	char aij_file[150];
	char bjk_file[150];
	int acc=0, ind, i, j, k;
	long double mx;

	for(i=0;i<no_of_digits;i++){
		for(j=0;j<no_of_testing_samples;j++){
			sprintf(&test_file_obs_seq[0], "./Observations/English/digit_%d/Obs_Eng_digit_%d_test_utterance_%d.txt", i, i, j);
			read_obs_seq(test_file_obs_seq);
			mx=0, ind=-1;
			for(k=1;k<no_of_digits;k++){
				sprintf(&aij_file[0], "./Final_Model/English/aij/digit_%d.txt", k);
				sprintf(&bjk_file[0], "./Final_Model/English/bjk/digit_%d.txt", k);
				read_aij(aij_file);
				read_bjk(bjk_file);
				forward_prc();
				//printf("The prob from %d is %le\n", k, prob_of_obs_given_lambda);
				if(prob_of_obs_given_lambda>mx){
					mx=prob_of_obs_given_lambda;
					ind=k;
				}
			}
			printf("The actual digit is %d and the prediction is %d\n", i, ind);
			if(ind==i) acc++;
		}
	}
	//printf("The accuracy is %lf\n", acc/(1.0*((total_samples-no_of_training_samples)*(no_of_digits))));
	printf("The accuracy is %lf\n", acc/(1.0*(no_of_testing_samples*(no_of_digits))));
}


void helper2(char *filename){

	FILE *fp;
	char str[100];
	long int no_of_frames=0, zcr=0;
	long double sum=0.0, count=0, prev=0.0, x, temp;
	avg=(long double* )malloc(2*sizeof(long double));

	avg[0]=0.0;
	avg[1]=0.0;
	
	fp=fopen(filename, "r");

	if(NULL==fp){
        printf("File not found\n");
		getch();
        exit(1); //File Read Failure
    }

	while(fgets(str, 100, fp)!=NULL) {
		x=atof(str);
		x=(x-dcshift)*nfactor;
		count++;
		if(x!=0){
			//add the individual energies as square of the amplitude
			sum+=x*x;
			if(prev!=0){
				// Checking if the prev and present is of opposite sign
				if((x<0 && prev>0) || (x>0 && prev<0)) {
					zcr=zcr+1;
				}
			}
			prev=x;
		}
	
		if(count==f_size){
			avg[0]+=zcr;
			avg[1]+=sum/f_size;
			no_of_frames++;
			//reinitialize all the variables for the next frame
			zcr=0; sum=0;
			prev=0; count=0;
		}
	}
	//printf("The total no of frames is %ld\n", no_of_frames);
	//avg[0] contains average ZCR
	avg[0]/=no_of_frames;
	//avg[1] contains average of Short Term Energies
	avg[1]/=no_of_frames;
	printf("Average ZCR %lf \t Average Energy %lf\n", avg[0], avg[1]);
	fclose(fp);
}

void seggregation_and_detection(long double *avg, char * input_file, char *output_file){

	FILE *fp, *fp1;
	double energy[10000], zcr[10000];
	char str[100];
	long int no_of_frames=0, z=0, strt=-1, end=-1, size, i, ctr=0;
	long double sum=0.0, count=0, prev=0.0, x, x_prime, temp, testavgE=0, testavgZ=0, diff;

	fp=fopen(input_file, "r");
	fp1=fopen(output_file, "w");

	if(fp == NULL){
        printf("File not found\n");
		getch();
        exit(1);
    }
	i=0;
	while(!feof(fp)){
		fgets(str, 100, fp);
		x=atof(str);
		raw_data[i++]=x;
		//printf("%lf---->%lf\n", raw_data[i-1], x);
		count++;
		if(x!=0){
			x_prime=(x-dcshift)*nfactor;
			sum+=x_prime*x_prime;
			if(prev!=0){
				if((x_prime<0 && prev>0) || (x_prime>0 && prev<0)) {
					z=z+1;
				}
			}
			prev=x_prime;
		}
		if(count==f_size){
			//if(ctr>ignore_initial_frames){
				zcr[no_of_frames]=z;
				energy[no_of_frames]=sum/f_size;
				no_of_frames++;
			//}
			//ctr++;
			z=0; sum=0;
			prev=0; count=0;
		}
	}
	//printf("The no of data are %d and no of frames are %d\n", i, no_of_frames);
	
	for(i=0;i<no_of_frames;i++){
		//&& ((zcr[i+1]<avg[0]*zcr_thresh)
		if(strt==-1 && end==-1  && (energy[i+1]>thresh*avg[1]) && (energy[i+2]>thresh*avg[1]) && (energy[i+3]>thresh*avg[1])){
			strt=i;
			printf("Strt condition statisfied for frame %d\n", i);
		}
		else if(strt!=-1 && (energy[i]<=thresh*avg[1]) && (energy[i-1]<=thresh*avg[1]) && (energy[i-2]<=thresh*avg[1])){
			end=i;
			printf("End condition satisfied for frame %d\n", i);
			break;
		}
		//&& (zcr[i]>avg[0]*zcr_thresh)
	}
	if(end==-1) end=no_of_frames;
	diff=23-(end-strt+1);
	strt=max(0, strt-(diff/2));
	end=min(no_of_frames, end+(diff/2));

	printf(" The start is %d and the end is %d \n", strt, end);

	//Calculate the average energy and ZCR of the word spoken
	dsize=0;
	for(i=strt*f_size;i <=end*f_size;i++){
		fprintf(fp1, "%lf\n", raw_data[i]);
		//printf("%lf\n", raw_data[i]);
	}
	fclose(fp);
	fclose(fp1);
}

int test_with_live_data(){

	long double mx;
	int ind, k;
	char input_file[150];
	char input_file_new[150];
	char modified_input_file[150];
	char output_cepstral_file[150];
	char output_obs_seq_file[150];
	char codebook_filename[150];
	char aij_file[150];
	char bjk_file[150];

	sprintf(&input_file[0], "./Live_input/English/input_file.txt");
	sprintf(&input_file_new[0], "./Live_input/English/input_file_new.txt");
	sprintf(&modified_input_file[0], "./Live_input/English/modified_input_file.txt");
	sprintf(&output_cepstral_file[0], "./Live_input/English/input_file_cepstral.csv");
	sprintf(&output_obs_seq_file[0], "./Live_input/English/input_file_obs_seq.txt");
	sprintf(&codebook_filename[0], "./Codebook/English/Codebook_English.csv");
	
	system("Recording_Module.exe 2 ./Live_input/English/input_wav_file.wav ./Live_input/English/input_file.txt");
	
	calc_dcshift("silence.txt");

	calc_nfactor(input_file);
	helper2(input_file);
	seggregation_and_detection(avg, input_file, input_file_new);
	//printf("--------------------------------------------");
	

	calc_nfactor(input_file_new);
	//calc_nfactor(input_file);
	normalize_data(input_file_new);
	//normalize_data(input_file);
	


	//printf("The data size is %d\n", dsize);
	extract_frames(modified_input_file);
	calculate_Ris();
	apply_durbins_algo();

	store_Cis_to_file(output_cepstral_file);

	read_codebook(codebook_filename);
	read_cep_values(output_cepstral_file);
	remove(output_obs_seq_file);
	generate_sequence(output_obs_seq_file);

	read_obs_seq(output_obs_seq_file);
	mx=0, ind=-1;
	
	for(k=0;k<no_of_digits;k++){
		sprintf(&aij_file[0], "./Final_Model/English/aij/digit_%d.txt", k);
		sprintf(&bjk_file[0], "./Final_Model/English/bjk/digit_%d.txt", k);

		read_aij(aij_file);
		read_bjk(bjk_file);
		forward_prc();
		//printf("The prob from %d is %le\n", k, prob_of_obs_given_lambda);
		if(prob_of_obs_given_lambda>mx){
			mx=prob_of_obs_given_lambda;
			ind=k;
		}
		printf("For digit %d the prob is %le\n", k, prob_of_obs_given_lambda);
		//Console.WriteLine("The 
	}
	printf("The prediction is %d\n", ind);
	return ind;
}


void live_training(){

	int i, ch;
	char input_file[150];
	char input_file_new[150];
	char modified_input_file[150];
	char output_cepstral_file[150];
	char output_obs_seq_file[150];
	char unv_file[150];

	sprintf(&input_file[0], "./Live_input/English/input_file.txt");
	sprintf(&unv_file[0], "./Universe/English/Universe_English.csv");

	for(i=0;i<no_of_digits;i++){

		sprintf(&input_file_new[0], "./Data/English/English_digits_txt/E_%d_%d.txt", i, no_of_training_samples);
		sprintf(&output_cepstral_file[0], "./Cepstral_values/English/digit_%d/utterance_%d.csv", i, no_of_training_samples);
		sprintf(&modified_input_file[0], "./Modified_Data/English/digit_%d/utterance_%d.txt", i, no_of_training_samples);
		printf("\n\nPlease record for digit %d now. Press 1 and enter to continue\n", i);
		delay(50);
		system("Recording_Module.exe 2 ./Live_input/English/input_wav_file.wav ./Live_input/English/input_file.txt");

		calc_dcshift("silence.txt");
		calc_nfactor(input_file);
		helper2(input_file);
		seggregation_and_detection(avg, input_file, input_file_new);
	
		calc_nfactor(input_file_new);
		normalize_data(input_file_new);
		extract_frames(modified_input_file);

		calculate_Ris();
		apply_durbins_algo();
		add_Cis_to_universe(unv_file);
		store_Cis_to_file(output_cepstral_file);
	}
	printf("\n\nNew Codebook will be generated now\n");
	//delay(50);
	generate_codebook();

	for(i=0;i<no_of_digits;i++){
			sprintf(&output_cepstral_file[0], "./Cepstral_values/English/digit_%d/utterance_%d.csv", i, no_of_training_samples);
			sprintf(&output_obs_seq_file[0], "./Observations/English/digit_%d/Obs_Eng_digit_%d_utterance_%d.txt", i, i, no_of_training_samples);

			read_cep_values(output_cepstral_file);
			remove(output_obs_seq_file);
			generate_sequence(output_obs_seq_file);
	}
	no_of_training_samples++;

	HMM_training();
}

int generate_captcha(){

	srand(time(0));
	arg1=rand()%(no_of_digits-1);
	int ch=rand()%4;

	switch(ch){

		case 0:
						//if(arg1==0) arg1++;
						arg2=rand()%(no_of_digits-arg1);
						result=arg1+arg2;
						captcha_str=to_string((long long)arg1)+" + "+to_string((long long)arg2);
						break;
		case 1:
						if(arg1==0) arg1++;
						arg2=rand()%arg1;
						result=arg1-arg2;
						captcha_str=to_string((long long)arg1)+ " - "+to_string((long long)arg2);
						break;

		case 2: 
						arg1=1;
						arg2=2;
						result=arg1*arg2;
						captcha_str=to_string((long long)arg1)+ " * "+to_string((long long)arg2);
						break;
		case 3:
						arg2=rand()%no_of_digits;
						result=arg2;
						arg2*=arg1;
						captcha_str=to_string((long long)arg2)+ " / "+to_string((long long)arg1);
						break;
	}
	return result;
}

void delay(int time)
{
	// this function will create a pause in the runtime process for the number of milliseconds that is given in 'time'
	long pause;
	clock_t time1,time2; // data_type variable_name
	pause = time ; // if you want to be more accurate replace time with ' time * (CLOCKS_PER_SEC/1000); ' // i.e. 1000
	time2 = time1 = clock(); // the clock() returns back the number of ticks till it has been called .
	while( (time1-time2) < pause ){
		time1 = clock(); // this will initialize the current number of ticks to time1 ;
	}
}

/*
int _tmain(int argc, _TCHAR* argv[])
{
	int ch;
	//no_of_training_samples=training_samples;
	no_of_training_samples=25;
	no_of_testing_samples=5;
	while(true){
		printf("Enter your choice 1.Process Data 2. Train HMM Model 3. Test Model 4. Test with Live data 5. Live Training 6. Exit\n");
		scanf("%d", &ch);
		switch(ch){
			case 1:
					build_universe();
					generate_codebook();
					generate_observation_sequence_training();
					break;
			case 2: 
					HMM_training();
					break;
			case 3: 
					compute_cepstral_testing();
					generate_observation_sequence_testing();
					testing_with_stored_data();
					break;
			case 4:
					test_with_live_data();
					break;
			case 5: 
					live_training();
					break;
			case 6:
					return 0;
		}
	}
	getch();
	return 0;
}
*/

