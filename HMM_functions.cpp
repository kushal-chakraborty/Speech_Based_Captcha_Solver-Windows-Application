#include "stdafx.h"
#include "HMM_functions.h"


void display_aij(){

	int i, j;
	printf("\n\nThe a(i, j) matrix is \n");
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("%le\t", aij[i][j]);
		}
		printf("\n");
	}

}

void read_aij(char * filename){

	FILE *fp;
	int i, j;
	long double val;

	fp= fopen(filename, "r");
	i=0,j=-1;
	while(!feof(fp)){
		fscanf(fp, "%le", &val);
		j++;
		if(j==N){
			j=0;
			i++;
		}
		aij[i][j]=val;
	}
	//display_aij();
	fclose(fp);
}

void display_bjk(){

	int i, j;
	long double sum;
	printf("\n\nThe b(j, k) matrix is \n");

	for(i=0;i<N;i++){
		sum=0;
		for(j=0;j<M;j++){
			//printf("%le\t", bjk[i][j]);
			sum+=bjk[i][j];
		}
		//printf("\n");
		//printf("\nThe sum of 1st row is %le\n", sum);
	}
}


void read_bjk(char *filename){

	FILE *fp;
	int i, j;
	long double val;

	i=0, j=-1;
	fp=fopen(filename, "r");
	while(!feof(fp)){
		fscanf(fp, "%le", &val);
		j++;
		if(j==M){
			j=0;
			i++;
		}
		bjk[i][j]=val;
	}
	fclose(fp);
	//display_bjk();
}


void read_obs_seq(char *filename){

	FILE *fp;
	int no;

	T=0;
	fp=fopen(filename, "r");

	while(!feof(fp)){
		fscanf(fp, "%d", &no);
		obs[T++]=no;
	}
	/*
	printf("The value of  T is %d\n", T);
	printf("\n\n The observation sequence is: \n");
	for(i=0;i<T;i++)
		printf("%d\t", obs[i]);
	printf("\n");*/
	fclose(fp);
}

void set_aij_bjk(){
	int i, j, k;

	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			aij[i][j]=0;
		}
	}

	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			bjk[i][j]=0;
		}
	}
}

void set_allmatrix(){
	int i, j, k;

	
	for(i=0;i<MAX_T;i++){
		for(j=0;j<N;j++){
			alpha[i][j]=0;
			beta[i][j]=0;
			gamma[i][j]=0;
			delta[i][j]=0;
			psi[i][j]=0;
			for(k=0;k<N;k++){
				xi[i][j][k]=0;
			}
		}
	}
}


long double forward_prc(){

	int i, j, s=0, si, sj, t;
	long double alpha_t_sum=0;
	prob_of_obs_given_lambda=0;
	
	for(i=0;i<T;i++){
		for(j=0;j<N;j++){
			alpha[i][j]=0;
		}
	}
	
	for(s=0; s<N; ++s){
		alpha[0][s] = Pi[s]*(bjk[s][obs[0]]);
	}

	for(t=0; t<T-1; t++){
		for(sj=0; sj<N; sj++){
			alpha_t_sum=0;
			for(si=0; si<N; si++){
					alpha_t_sum+=alpha[t][si]*aij[si][sj];
			}
			alpha[t+1][sj] = alpha_t_sum*bjk[sj][obs[t+1]];
		}
	}
	for(s=0; s<N; s++){
		 prob_of_obs_given_lambda += alpha[T-1][s];
	}

	/*
	printf("\n\nThe values of alpha matrix are: \n\n");
	for(i=0;i<T;i++){
		for(j=0;j<N;j++){
			printf("%le\t", alpha[i][j]);
		}
		printf("\n");
	}*/
	//printf("\n \nThe prob of the seq is %le\n", prob_of_obs_given_lambda);
	return prob_of_obs_given_lambda;
	
}


void backward_prc() {
	int i, j, t;
	long double sum=0;

	for(i=0;i<N;i++)
		beta[T-1][i]=1;

	for(t=T-2;t>=0;t--){
		for(i=0;i<N;i++){
			sum=0;
			for(j=0;j<N;j++){
				sum+=aij[i][j]*bjk[j][obs[t+1]]*beta[t+1][j];
			}
			beta[t][i]=sum;
		}
	}
	/*
	printf("\n\nThe values of beta matrix are: \n\n");

	for(i=0;i<T;i++){
		for(j=0;j<N;j++){
			printf("%le\t", beta[i][j]);
		}
		printf("\n");
	}*/
}


void calculate_gamma(){

	int i, j, k, t;
	for(t=0;t<T;t++){
		for(j=0;j<N;j++){
			long double sum=0;
			for(k=0;k<N;k++){
				sum += alpha[t][k] * beta[t][k];
			}
			gamma[t][j]=(alpha[t][j] * beta[t][j])/sum;
		}
	}
	/*
	printf("\n\nThe values of gamma matrix are :\n\n");
	for(i=0;i<T;i++){
		for(j=0;j<N;j++){
			printf("%le\t", gamma[i][j]);
		}
		printf("\n");
	}*/

}

void viterbi(){

	int i, j, t, ind=0;
	long double mx=0;

	for(i=0;i<N;i++){
		delta[0][i]=Pi[i]*(bjk[i][obs[0]]);
		psi[0][i]=-1;
	}

	for(t=1;t<T;t++){
		for(j=0;j<N;j++){
			mx=INT_MIN;
			for(i=0;i<N;i++){
				if(delta[t-1][i]*aij[i][j]>mx){
					ind=i;
					mx=delta[t-1][i]*aij[i][j];
				}
			}
			delta[t][j]=mx*bjk[j][obs[t]];
			psi[t][j]=ind;
		}
		//delta[t][j]=mx*bjk[j][obs[t]-1];
		//psi[t][j]=ind;
	}

	mx=0,ind=0;
	for(i=0;i<N;i++){
		if(delta[T-1][i]>mx){
			mx=delta[T-1][i];
			ind=i;
		}
	}
	Pstar=mx;
	Qstar[T-1]=ind;

	for(t=T-2;t>=0;t--)
		Qstar[t]=psi[t+1][Qstar[t+1]];

	//printf("P* got from Viterbi algorithm is %le\n", Pstar);

	/*
	printf("The state sequence is \n");
	for(t=0;t<T;t++)
			printf("%d\t", Qstar[t]+1);
	printf("\n");
	*/
}


void baum_welch_calculate_xi(){

	int i, j, t;
	long double sum=0;

	for(t=0;t<T-1;t++){
		sum=0;
		for(i=0;i<N;i++){
			for(j=0;j<N;j++){
				sum+=alpha[t][i]*aij[i][j]*bjk[j][obs[t+1]]*beta[t+1][j];
			}
		}

		for(i=0;i<N;i++){
			for(j=0;j<N;j++){
				xi[t][i][j]=(alpha[t][i]*aij[i][j]*bjk[j][obs[t+1]]*beta[t+1][j])/sum;
			}
		}
	}

	/*
	printf("The values of the Baum Welch matrix are :\n");
	for(t=0;t<T;t++){
		for(i=0;i<N;i++){
			for(j=0;j<N;j++){
				printf("%le\t", xi[t][i][j]);
			}
			printf("\n");
		}
		printf("\n\n");
	}*/
}


void reestimate_parameters(){

	int i, j, t, k, ind;
	long double sum, mx;
	long double exp_no_trans_from_si_to_sj, exp_no_trans_from_si;
	long double exp_no_times_in_sj_and_obs_k, exp_no_times_in_sj;

	for(i=0;i<N;i++)
		Pi_bar[i]=gamma[0][i];

	for(i=0;i<N;i++){
		for(j=0;j<N;j++){

			exp_no_trans_from_si_to_sj=0;
			exp_no_trans_from_si=0;

			for(t=0;t<T-1;t++){
				exp_no_trans_from_si_to_sj+=xi[t][i][j];
				exp_no_trans_from_si+=gamma[t][i];
			}
			aij_bar[i][j]=exp_no_trans_from_si_to_sj/exp_no_trans_from_si;
		}
	}

	for(j=0;j<N;j++){
		for(k=0;k<M;k++){
			exp_no_times_in_sj_and_obs_k=0;
			exp_no_times_in_sj=0;
			for(t=0;t<T;t++){
				if(obs[t]==k)
					exp_no_times_in_sj_and_obs_k+=gamma[t][j];
				exp_no_times_in_sj+=gamma[t][j];
			}
			bjk_bar[j][k]=exp_no_times_in_sj_and_obs_k/exp_no_times_in_sj;
		}
	}
}

void update_aij(){
	int i, j, ind;
	long double sum, mx;

	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			aij[i][j]=aij_bar[i][j];
		}
	}
	
	for(i=0;i<N;i++){
		sum=0, mx=-1, ind=-1;
		for(j=0;j<N;j++){
			if(aij[i][j]>mx){
				ind=j;
				mx=aij[i][j];
			}
			sum+=aij[i][j];
		}
		//sum=1-sum;
		sum-=1;
		//aij_bar[i][ind]+=sum;
		//aij_bar[i][ind]-=sum;
		aij[i][ind]-=sum;
	}
}


void update_bjk(){
	int j, k, ind;
	long double sum, mx;


	for(j=0;j<N;j++){
		for(k=0;k<M;k++){
			bjk[j][k]=bjk_bar[j][k];
		}
	}
	//printf("The bjk matrix before is \n");
	//display_bjk();

	for(j=0;j<N;j++){
		for(k=0;k<M;k++){
			if(bjk[j][k]<RESET_VAL){
				bjk[j][k]=RESET_VAL;
			}
		}
		sum=0, mx=-1, ind=-1;
		for(k=0;k<M;k++){
			if(bjk[j][k]>mx){
				ind=j;
				mx=bjk[j][k];
			}
			sum+=bjk[j][k];
		}
		sum-=1;
		bjk[j][ind]-=sum;
	}

	//printf("The bjk matrix after stochastic check is \n");
	//display_bjk();
	/*
	for(j=0;j<N;j++){
		sum=0;
		for(k=0;k<M;k++){
			sum+=bjk[j][k];
		}
		printf("%le\t", sum);
	}*/
}


void HMM_model(char *filename_aij, char *filename_bjk, char *filename_obs_seq ){

	int i;

	/*******************************STEP 1******************************/
	read_aij(filename_aij);
	read_bjk(filename_bjk);
	read_obs_seq(filename_obs_seq);

	/*****************************STEP 2*******************************/
	//for(i=1;i<=20;i++){
	//while(prob_of_obs_given_lambda>Pstar){
	i=0;
	do {
		set_allmatrix();
		forward_prc();
		backward_prc();
		calculate_gamma();
		viterbi();
		baum_welch_calculate_xi();
		reestimate_parameters();
		update_aij();
		update_bjk();
		i++;
	}while(prob_of_obs_given_lambda>Pstar && i<100);
	
}



void generate_HMM_model(){

	int i;
	i=0;
	do {
		set_allmatrix();
		forward_prc();
		backward_prc();
		calculate_gamma();
		viterbi();
		baum_welch_calculate_xi();
		reestimate_parameters();
		update_aij();
		update_bjk();
		i++;
	}while(prob_of_obs_given_lambda>Pstar && i<100);
}


void store_aij_to_file(char *filename){
	int i, j;
	FILE *fp;
	fp=fopen(filename, "w");
	if(fp==NULL){
		printf("File couldn't be opened\n");
	}

	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			fprintf(fp, "%le\t", aij[i][j]);
		}
		fprintf(fp,"\n");
	}
	fclose(fp);

}


void store_bjk_to_file(char *filename){

	int j, k;
	FILE *fp;
	fp=fopen(filename, "w");

	for(j=0;j<N;j++){
		for(k=0;k<M;k++){
			fprintf(fp, "%le\t",bjk[j][k]);
		}
		fprintf(fp,"\n");
	}
	fclose(fp);

}



void read_trained_aij(char *filename){

	FILE *fp;
	int i, j;
	long double val;

	//printf("File ------------->%s\n\n", filename);

	fp= fopen(filename, "r");
	i=0,j=-1;
	while(!feof(fp)){
		fscanf(fp, "%le", &val);
		//printf("%le\t", val);
		j++;
		if(j==N){
			j=0;
			i++;
			//printf("\n");
		}
		trained_aij[i][j]+=val;
	}
	//printf("\nThe (0,0) value is %le\n", trained_aij[0][0]);
	//display_aij();
	fclose(fp);

}


void read_trained_bjk(char *filename){

	
	FILE *fp;
	int i, j;
	long double val;

	i=0, j=-1;
	fp=fopen(filename, "r");
	while(!feof(fp)){
		fscanf(fp, "%le", &val);
		j++;
		if(j==M){
			j=0;
			i++;
		}
		trained_bjk[i][j]+=val;
	}
	fclose(fp);

}

void set_matrix_trained_aij(){
	int i, j;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			trained_aij[i][j]=0;
		}
	}
}

void set_matrix_trained_bjk(){
	int j, k;
	for(j=0;j<N;j++){
		for(k=0;k<M;k++){
			trained_bjk[j][k]=0;
		}
	}

}

void avg_out_aij_bjk(int digit){

	
	char trained_model_aij_file[150];
	char trained_model_bjk_file[150];
	int ind, i, j, k;
	long double sum, mx;

	set_matrix_trained_aij();
	set_matrix_trained_bjk();

	for(i=0;i<no_of_training_samples;i++){
		sprintf(&trained_model_aij_file[0], "./Models/English/digit_%d/aij/aij_digit_%d_utterance_%d.txt", digit,digit, i);
		sprintf(&trained_model_bjk_file[0], "./Models/English/digit_%d/bjk/bjk_digit_%d_utterance_%d.txt", digit,digit, i);
		read_trained_aij(trained_model_aij_file);
		read_trained_bjk(trained_model_bjk_file);

	}
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			//printf("%le", trained_aij[i][j]);
			trained_aij[i][j]/=no_of_training_samples;
			//printf("(%le)\t", trained_aij[i][j]);
		}
		//printf("\n");
	}


	for(i=0;i<N;i++){
		sum=0, mx=-1, ind=-1;
		for(j=0;j<N;j++){
			if(trained_aij[i][j]>mx){
				ind=j;
				mx=trained_aij[i][j];
			}
			sum+=trained_aij[i][j];
		}
		//sum=1-sum;
		sum-=1;
		trained_aij[i][ind]-=sum;
	}

	for(j=0;j<N;j++){
		for(k=0;k<M;k++){
			trained_bjk[j][k]/=no_of_training_samples;;
		}
	}


	for(j=0;j<N;j++){
		for(k=0;k<M;k++){
			if(trained_bjk[j][k]<RESET_VAL){
				trained_bjk[j][k]=RESET_VAL;
			}
		}
		sum=0, mx=-1, ind=-1;
		for(k=0;k<M;k++){
			if(trained_bjk[j][k]>mx){
				ind=j;
				mx=trained_bjk[j][k];
			}
			sum+=trained_bjk[j][k];
		}
		sum-=1;
		trained_bjk[j][ind]-=sum;
	}


	/*
	printf("\n\nThe computed new aij data is \n");
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("%le\t",trained_aij[i][j]);
		}
		printf("\n");
	}

	printf("\n\nThe computed new bjk data is \n");
	
	for(j=0;j<N;j++){
		for(k=0;k<M;k++){
				printf("%le\t",trained_bjk[j][k]);
		}
		printf("\n");
	}*/
}

void write_to_aij_file(char *filename){
	int i, j;
	FILE *fp;
	fp=fopen(filename, "w");
	if(fp==NULL){
		printf("File couldn't be opened\n");
	}

	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			fprintf(fp, "%le\t", trained_aij[i][j]);
		}
		fprintf(fp,"\n");
	}
	fclose(fp);
}

void write_to_bjk_file(char *filename){
	
	int j, k;
	FILE *fp;
	fp=fopen(filename, "w");

	for(j=0;j<N;j++){
		for(k=0;k<M;k++){
			fprintf(fp, "%le\t",trained_bjk[j][k]);
		}
		fprintf(fp,"\n");
	}
	fclose(fp);

}


void copy_file_aij(char * input_file, char *output_file){

	FILE *fp, *fp1;
	int i, j;
	long double val;

	fp= fopen(input_file, "r");
	fp1= fopen(output_file, "w");
	i=0,j=-1;
	while(!feof(fp)){
		fscanf(fp, "%le", &val);
		//fprintf(fp1, "%le\t", val);
		j++;
		if(j==N){
			j=0;
			i++;
			fprintf(fp1, "\n");
		}
		if(i<N && j<N)
			fprintf(fp1, "%le\t", val);
		//aij[i][j]=val;
	}
	fclose(fp);
	fclose(fp1);
}

void copy_file_bjk(char * input_file, char *output_file){

	FILE *fp, *fp1;
	int i, j;
	long double val;

	fp= fopen(input_file, "r");
	fp1= fopen(output_file, "w");
	i=0,j=-1;
	while(!feof(fp)){
		fscanf(fp, "%le", &val);
		//fprintf(fp1, "%le\t", val);
		j++;
		if(j==M){
			j=0;
			i++;
			fprintf(fp1, "\n");
		}
		if(i<N && j<M)
			fprintf(fp1, "%le\t", val);
		//aij[i][j]=val;
	}
	fclose(fp);
	fclose(fp1);
}


void store_probabilities(char *filename){
	FILE *fp;
	int j;

	fp=fopen(filename, "w");
	for(int j=0;j<no_of_training_samples;j++){
		fprintf(fp, "Utterance %d ------->%le\n", j, prob_arr[j]);
	}
	fclose(fp);
}


void HMM_training(){

	int i, j, k, ind;
	long double mx;

	char HMM_trained_model_aij[150], HMM_best_model_aij[150];
	char HMM_trained_model_bjk[150], HMM_best_model_bjk[150];
	char HMM_prob[150];

	char filename_aij[150], filename_bjk[150];
	char digit_aij[150], digit_bjk[150];
	char filename_obs_seq[150];

	sprintf(&filename_aij[0], "./a.txt");
	sprintf(&filename_bjk[0], "./b.txt");

	/*
	read_aij(filename_aij);
	read_bjk(filename_bjk);
	read_obs_seq(filename_obs_seq);*/

	for(i=0;i<no_of_digits;i++){ 

		sprintf(&digit_aij[0], "./Final_Model/English/aij/digit_%d.txt", i);
		sprintf(&digit_bjk[0], "./Final_Model/English/bjk/digit_%d.txt", i);
		sprintf(&HMM_prob[0], "./HMM_probabilities/English/digit_%d.txt", i);

		copy_file_aij(filename_aij,digit_aij);
		copy_file_bjk(filename_bjk, digit_bjk);

		for(k=1;k<=3;k++){
		//k=1;
			printf("Iteration %d for digit %d\n",k, i);
			mx=0, ind=0;
			for(j=0;j<no_of_training_samples;j++){

				sprintf(&filename_obs_seq[0],  "./Observations/English/digit_%d/Obs_Eng_digit_%d_utterance_%d.txt", i, i, j);	
				sprintf(&HMM_trained_model_aij[0], "./Models/English/digit_%d/aij/aij_digit_%d_utterance_%d.txt", i,i, j);
				sprintf(&HMM_trained_model_bjk[0], "./Models/English/digit_%d/bjk/bjk_digit_%d_utterance_%d.txt", i,i, j);

				set_aij_bjk();
				read_aij(digit_aij);
				read_bjk(digit_bjk);
				if(j==0){
					printf("\n\nFresh round with new aij and bjk \n\n");
					display_aij();
					display_bjk();
				}
				read_obs_seq(filename_obs_seq);
				
				//HMM_model(filename_aij, filename_bjk, filename_obs_seq);
				
				generate_HMM_model();
				//display_aij();
				//display_bjk();

				store_aij_to_file(HMM_trained_model_aij);
				store_bjk_to_file(HMM_trained_model_bjk);
				prob_arr[j]=prob_of_obs_given_lambda;
			}
			
			for(j=0;j<no_of_training_samples;j++){
				if(prob_arr[j]>mx){
					mx=prob_arr[j];
					ind=j;
				}
			}
			printf("\n\n");
			
			avg_out_aij_bjk(i);
			write_to_aij_file(digit_aij);
			write_to_bjk_file(digit_bjk);
			
			/*
			if(k==3){
				sprintf(&HMM_best_model_aij[0], "./Models/English/digit_%d/aij/aij_digit_%d_utterance_%d.txt", i,i, ind);
				sprintf(&HMM_best_model_bjk[0], "./Models/English/digit_%d/bjk/bjk_digit_%d_utterance_%d.txt", i,i, ind);

				copy_file_aij(HMM_best_model_aij, digit_aij);
				copy_file_bjk(HMM_best_model_bjk, digit_bjk);
			}
			else{
				write_to_aij_file(digit_aij);
				write_to_bjk_file(digit_bjk);
			}*/

		}
		printf("\n\n\n The digit trained is %d\n", i);
		printf("The final prob got are \n");
		for(j=0;j<no_of_training_samples;j++){
				printf("%d-> %le\n",j,prob_arr[j]);
		}
		printf("\n\n");
		remove(HMM_prob);
		store_probabilities(HMM_prob);
		printf("\n\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n\n");
	}

}
