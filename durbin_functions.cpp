#include "stdafx.h"
#include "durbin_functions.h"


int max(int a, int b){
	if(a>b) return a;
	else return b;
}

int min(int a, int b){
	if(a<b) return a;
	else return b;
}


/*
 * This function calculates the DC shift by averaging 
 * out the data of the background noise
 */
void calc_dcshift(char *filename){

	FILE *fp;
	char str[100];
	long int count=0;
	long double n;
	fp=fopen(filename, "r");

	if(NULL==fp){
        printf("File not found\n");
		getch();
        exit(1); // Failure status
    }

	while(fgets(str, 100, fp)!=NULL){
		if(!isalpha(str[0])){ //The first few lines are configurations of the speech data
			n=atof(str);
			dcshift+=n;
			count++;
		}
	}
	dcshift/=count;
	fclose(fp);
}


/*
 * This function calculates the normalization factor 
 * which is max allowed amplitude / present max amplitude 
 */
void calc_nfactor(char *filename){

	FILE *fp;
	char str[100];
	long double mx=0.0;
	
	fp=fopen(filename, "r");

	if(NULL==fp){
        printf("File not found\n");
		getch();
        exit(1); //File read failure
    }

	while(fgets(str, 100, fp)!=NULL) {
		if(isalpha(str[0])==0){ //The first few lines are configurations of the speech data
			if(mx<abs(atof(str)))
				mx=abs(atof(str));
		}
	}
	nfactor=mx_amp/mx;
	//printing the normalization factor
	//printf("The nfactor is %f\n", nfactor);
	fclose(fp);
}


/*
 * This functions normalizes the data by 
 * subtracting the dc shift and then 
 * multiplying it with the normalization factor
 * and writing it into an output file
 */

void normalize_data(char * inpfile){

	FILE *inp;
	char str[100];
	long double n;
	dsize=0;

	inp=fopen(inpfile, "r");
	//remove(outfile);
	//op=fopen(outfile, "w");

	if(NULL==inp){
        printf("File not found\n");
		getch();
        exit(1); //File Read Failure
    }

	while(fgets(str, 100, inp)!=NULL){
		if(isalpha(str[0])==0){ //The first few lines are configurations of the speech data
			n=atof(str);
			n=(n-dcshift)*nfactor; // normalization
			//fprintf(op, "%0.4f\n", n); //writing to an output file
			data[dsize++]=n;
		}
	}
	fclose(inp);
	/*
	for(i=0;i<dsize;i++)
		printf("%0.4f\n", data[i]);
		*/
	//fclose(op);

}

/*
	* This function applies a tapered function 
	* called the hamming window on the frame
	*/


void apply_hamming_window(){

	long int i, j;
	for(i=0;i<no_of_frames;i++){
		for(j=0;j<frame_size;j++){
			frames_data[i][j] *= (0.54-0.46*cos((2*PI*j)/(frame_size-1)));
			//steady_frames_data[i][j] *= (0.54-0.46*cos((2*PI*steady_frames_data[i][j])/(frame_size-1)));
		}
	}
}


/*
	*This function applies a raised tapered window 
	*on the Ci's calculated. Process called liftering
	*/

void apply_raisedsine_window(){

	long double weight=0;
	long int f, m;

	for(f=0;f<no_of_frames;f++){
		for(m=1;m<=p;m++){
			weight=1+((p/2)*sin((PI*m)/(p*1.0)));
			//weight=((p/2)*sin((PI*m)/(p*1.0)));
			C[f][m]*=weight;
		}
	}

}

/* 
	* This function store the Ci's of all steady frames 
	* of all training vowels in a 3D array
	*/

void add_Cis_to_universe(char *filename){
	long int f, m;

	FILE *fp;
	fp=fopen(filename, "a");
	for(f=0;f<no_of_frames;f++){
		for(m=1;m<=p;m++){
			fprintf(fp,"%lf,", C[f][m]);
			//all_Cis[file_no][f][m]=C[f][m];
			//printf("Inside....C[f][m] is %lf and all_Cis[file_no][f][m] is %lf\n", C[f][m], all_Cis[file_no][f][m]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
}


void store_Cis_to_file(char *filename){
	long int f, m;

	FILE *fp;
	fp=fopen(filename, "w");
	for(f=0;f<no_of_frames;f++){
		for(m=1;m<=p;m++){
			fprintf(fp,"%lf,", C[f][m]);
			//all_Cis[file_no][f][m]=C[f][m];
			//printf("Inside....C[f][m] is %lf and all_Cis[file_no][f][m] is %lf\n", C[f][m], all_Cis[file_no][f][m]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
}

/*
	*This function calculates the Ci's from the ai's
	*/

void calculate_cis(){

	long double sum=0;
	long int f, m;

	for(f=0;f<no_of_frames;f++){

		C[f][0]=log(R[f][0]*R[f][0]);

		for(m=1;m<=p;m++){
			sum=0;
			for(k=1;k<m;k++)
				sum+=(k*C[f][k]*Alpha[f][m-k])/(m*1.0);
			C[f][m]=sum+Alpha[f][m];
		}
	}
	/*
	printf("Before raised sine window\n");
	for(f=0;f<no_steady_frames;f++){
		//printf("The Ci's are :\n");
		for(m=1;m<=p;m++)
			printf("%0.4f\t", C[f][m]);
		printf("\n");
	}
	printf("\nAfter Raised sine window\n");
	*/
	apply_raisedsine_window();
	for(f=0;f<no_of_frames;f++){
		//printf("The Ci's are :\n");
		for(m=1;m<=p;m++)
			printf("%0.4f\t", C[f][m]);
		printf("\n");
	}
	//file_no=0;
	//store_Cis();
}


/*
	*This function calculates the coefficients of LPC 
	* using durbin's algorithm
	*/

void apply_durbins_algo(){

	long double sum=0;
	long int f, i, j;
    
    for(f=0;f<no_of_frames;f++){
		E[0]=R[f][0];
		//sum=0;
		for(i=1;i<=p;i++){
			//sum=R[f][i];
			sum=0;
			for(j=1;j<=i-1;j++){
				sum+=a[i-1][j]*R[f][i-j];
				//a[i][j]=a[i-1][j]-K[i]*a[i-1][i-j];
			}
			//sum/=(double)E[i-1];
			K[i]=(R[f][i]-sum)/(double)E[i-1];
			a[i][i]=K[i];
			for(j=1;j<=i-1;j++){
				a[i][j]=a[i-1][j]-K[i]*a[i-1][i-j];
			}
			E[i]=(1-(K[i]*K[i]))*E[i-1];
		}
		
		//printf("The A(i)'s are as follows : \n");
		for(i=1;i<=p;i++){
            //printf("%0.4f\t", a[p][i]);
			Alpha[f][i]=a[p][i];
		}
		//printf("\n");
		
    }
	printf("The alpha's are computed successfully\n");
	calculate_cis();
}

/*
	*This function computes the correlation matrix
	*for the auto correlation method of LPC model
	*/


void calculate_Ris(){
	long int i, j;

	for(i=0;i<no_of_frames;i++){
		for(j=0;j<=p;j++) {
			R[i][j]=0;
			for(k=0;k<frame_size-j;k++)
				R[i][j]+=frames_data[i][k]*frames_data[i][k+j];
		}
	}
	
	for(i=0;i<1;i++){
		for(j=0;j<=p;j++) {
			printf("%0.4f\t", R[i][j]);
		}
		printf("\n");
	}
	
}

/*
	*This function extracts the steady frames from each samples
	* by taking highest energy frame along with 2 adjacent frames on either side
	*/

void extract_frames(char * filename) {

	long int n, i, j, start, end, diff;
	FILE *fp;

	printf("The datasize is %d\n", dsize);
	fp=fopen(filename, "w");
	n=dsize/window_shift;
	diff=max(0,n-max_no_frames);
	printf("The diff is %d \n", diff);
	start=diff/2;
	end=n-(diff/2);

	if((end-start+1)>max_no_frames)
		start=start+1;

	no_of_frames=0;
	printf("The start time is %d and end time is %d\n", start, end);
	printf("The no of frames are %d\n", n);
	for(i=start;i<end;i++){
		if(((dsize-(i*window_shift))+1)>=frame_size){
			for(j=0;j<frame_size;j++){
				frames_data[no_of_frames][j]=data[(i*window_shift)+j];
			}
			no_of_frames++;
		}
	}
	for(i=start*window_shift;i<((end*window_shift)+frame_size);i++){
		fprintf(fp, "%lf\n", (data[i]/nfactor)+dcshift);
	}
	printf("The actual no of frames are %d\n", no_of_frames);
	apply_hamming_window();
	/*
	for(i=0;i<no_of_frames;i++){
		for(j=0;j<frame_size;j++)
			printf("%0.4f\t", frames_data[i][j]);
		printf("\n********************************************************\n");
	}
	*/
	fclose(fp);
}

void compute_cepstral_testing(){

	char input_file[150];
	char output_file[150];
	char modified_input_file[150];
	long int i, j;
	calc_dcshift("silence.txt");
	file_no=0;

	for(i=0;i<no_of_digits;i++){
		for(j=0;j<no_of_testing_samples;j++){
			sprintf(&input_file[0], "./Test_Data/English/English_digits_txt/224101032_E_%d_%d.txt", i, j);
			sprintf(&output_file[0], "./Cepstral_values/English/digit_%d/test_utterance_%d.csv", i, j);
			sprintf(&modified_input_file[0], "./Modified_Data/English/digit_%d/test_utterance_%d.txt", i, j);
			remove(output_file);
			printf("\n\n\n%s\n\n", input_file);
			printf("\n\n\n%s\n\n", output_file);
			calc_nfactor(input_file);
			normalize_data(input_file);
			extract_frames(modified_input_file);
			calculate_Ris();
			apply_durbins_algo();
			store_Cis_to_file(output_file);
		}
	}
	/*
	for(i=0;i<file_no;i++){
		for(f=0;f<no_steady_frames;f++){
			for(m=1;m<=p;m++){
				printf("%lf",all_Cis[i][f][m]);
			}
			printf("\n");
		}
		printf("\n");
	}*/

}

void build_universe() {
	char input_file[150];
	char output_file[150];
	char modified_input_file[150];
	char unv_file[150];
	long int i, j;
	calc_dcshift("silence.txt");
	file_no=0;

	sprintf(&unv_file[0], "./Universe/English/Universe_English.csv");
	remove(unv_file);

	for(i=0;i<no_of_digits;i++){
		printf("\n\n\n%s\n\n", unv_file);
		//for(j=0;j<total_samples;j++){
		for(j=0;j<no_of_training_samples;j++){
			sprintf(&input_file[0], "./Data/English/English_digits_txt/224101032_E_%d_%d.txt", i, j);
			sprintf(&output_file[0], "./Cepstral_values/English/digit_%d/utterance_%d.csv", i, j);
			sprintf(&modified_input_file[0], "./Modified_Data/English/digit_%d/utterance_%d.txt", i, j);
			remove(output_file);
			printf("\n\n\n%s\n\n", input_file);
			printf("\n\n\n%s\n\n", output_file);
			calc_nfactor(input_file);
			normalize_data(input_file);
			extract_frames(modified_input_file);
			calculate_Ris();
			apply_durbins_algo();
			add_Cis_to_universe(unv_file);
			store_Cis_to_file(output_file);
		}
	}
	/*
	for(i=0;i<file_no;i++){
		for(f=0;f<no_steady_frames;f++){
			for(m=1;m<=p;m++){
				printf("%lf",all_Cis[i][f][m]);
			}
			printf("\n");
		}
		printf("\n");
	}*/
}
