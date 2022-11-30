#include "stdafx.h"
#include "LBG.h"


//Initialise the codebook with random data from the universe
//before starting the kmeans algorithm

void initialise_codebook(){

	int index=0, i, j;
	srand(time(0));

	for(i=0;i<cbook_size;i++){
		for(j=0;j<p;j++){
			codebook[i][j]=0.0;
		}
	}

	for(i=0;i<cbook_size;i++){
		index=rand()%no_of_rows;
		//printf("Index chosen is %d for data %d\n", index, i);
		for(j=0;j<p;j++)
			codebook[i][j]=universe_data[index][j];
	}
}

//Function to calculate the tokhura distance between the 2 codebook vectors

long double calculate_tokhura(long double A[p], long double B[p]){

	long int i;
	long double dist=0;

	for(i=0;i<p;i++){
		long double d=abs(A[i]-B[i]);
		dist+=Weights[i]*d*d;
	}
	return dist;
}

//Function to assign data to cluster based on min dist rule

void assign_cluster_to_data(){

	long int i, j, k;
	int cl_no;
	long double ret;


	for(j=0;j<cbook_size;j++)
		cluster_size[j]=0;

	for(i=0;i<no_of_rows;i++){
		long double min=10000000000.0000;
		for(j=0;j<cbook_size;j++){

			long double dist=0;
			/*
			for(k=0;k<p;k++){
				long double d=abs(codebook[j][k]-data[i][k]);
				dist+=tokhuraWeights[k]*d*d;
				//dist=d*d;
			}*/
			dist=calculate_tokhura(codebook[j], universe_data[i]); //distance measure used is Tokhura's distance
			//if(i==250)
				//printf("Tokhura dist for data %d  with respect to cluster %d is %f\n", i, j, dist);
			if(min>dist){
				min=dist;
				cl_no=j;
			}
		}
		assigned_cluster[i]=cl_no;  //Store the assigned cluster no
		++cluster_size[cl_no]; //increase the size of the assigned cluster
		//printf("Data %d is assigned cluster %d and its size is %d now \n", i, cl_no, cluster_size[cl_no]);
	}
}

//Utility function to calculate distortion based on Tokhuras distance

long double calculate_distortion() {

	long double total_dist=0.0;
	long int i,k;

	for(i=0;i<no_of_rows; i++){
		/*
		for(k=0;k<p;k++){
				long double d=abs(codebook[assigned_cluster[i]][k]-data[i][k]);
				total_dist+=tokhuraWeights[k]*d*d;
		}*/
		total_dist+=calculate_tokhura(universe_data[i], codebook[assigned_cluster[i]]);
	}
	return total_dist/no_of_rows;
}

//Function to update the codebook as centroid of the clusters formed by K means 

void update_codebook(){

	long double newcodebook[codebook_size][p]={0};
	long int i, j, cl_no;

	for(i=0;i<no_of_rows;i++){
		cl_no=assigned_cluster[i];
		for(j=0;j<p;j++){
			newcodebook[cl_no][j]+=universe_data[i][j];
		}
	}
	for(i=0;i<cbook_size;i++){
		for(j=0;j<p;j++)
			newcodebook[i][j]/=cluster_size[i]; //calculating centroid of each cluster
	}

	for(i=0;i<cbook_size;i++){
		for(j=0;j<p;j++)
			codebook[i][j]=newcodebook[i][j]; //Assign the newcodebook formed to the codebook table
	}
}

//Function to implement the K Means algorithm

void kmeans(){

	long int i, iter=0;

	assign_cluster_to_data();
	printf("The cluster sizes are \n");
	for(i=0;i<cbook_size;i++)
		printf("%d\t", cluster_size[i]); //print the initial cluster sizes
	
	long double old_dist=0;
	long double new_dist=calculate_distortion();
	printf("\n1st iteration Old distortion %f , New distortion is %f\n", old_dist, new_dist);
	while(abs(new_dist-old_dist)>kmeans_thresh){ //run the K means algorithm until the difference in distortion is >0.0001
		iter++;
		update_codebook();
		assign_cluster_to_data();
		printf("Kmeans iteration %d ------> \n", iter);
		printf("\n\nThe cluster sizes are \n");
		for(i=0;i<cbook_size;i++)
			printf("%d\t", cluster_size[i]);
		old_dist=new_dist;
		new_dist=calculate_distortion();
		printf("\nOld distortion %f , New distortion is %f\n", old_dist, new_dist);
	}
}

//Utility function to display the codebook at any point 

void display_codebook(){

	int i, j;
	printf("c[1]\t  c[2]\t  c[3]\t  c[4]\t  c[5]\t  c[6]\t  c[7]\t  c[8]\t  c[9]\t  c[10]\t  c[11]\t  c[12]\n");
	for(i=0;i<cbook_size;i++) {
		for(j=0;j<p;j++)
			printf("%f\t", codebook[i][j]);
		printf("\n");
	}
}

//Initialisation step of LBG when codebook size is 1

void LBG_initialization(){

	long double arr[p]={0};
	int i, j;

	for(j=0;j<p;j++){
		arr[j]=0;
	}

	for(i=0;i<codebook_size;i++){
		for(j=0;j<p;j++){
			codebook[i][j]=0.0;
		}
	}

	for(i=0;i<no_of_rows;i++){
		for(j=0;j<p;j++){
			arr[j]+=universe_data[i][j];
		}
	}

	for(j=0;j<p;j++)
		codebook[0][j]=arr[j]/no_of_rows; //codebook is avg/centroid of all universe vectors
	display_codebook();

}



//Function to implement the LBG algorithm

void LBG(){

	int i, j, old_cbook_size;
	cbook_size=1;
	LBG_initialization();

	while(cbook_size!=codebook_size){ //start with codebook size 2 and go upto 8
		//cbook_size=2*cbook_size;
		//printf("ITERATION %d -------------------->\n", cbook_size);
		old_cbook_size=cbook_size;
		cbook_size=2*cbook_size;
		for(i=0;i<old_cbook_size;i++){

			for(j=0;j<p;j++) {
				codebook[old_cbook_size+i][j]=codebook[i][j]*(1-epsilon); //split each codebook vectors into 2 vectors by multiplying with 1+e and 1-e 
				codebook[i][j]=codebook[i][j]*(1+epsilon);
			}
		}
		//cbook_size=2*cbook_size;
		printf("The initial codebook is \n");
		display_codebook();
		kmeans();
		//printf("Codebook after Kmeans algorithm is \n");
		//display_codebook();
		//printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
	}

	printf("The Final Codebook is \n");
	display_codebook();
}

void display_universe_data(){

	int i, j;

	for(i=0;i<no_of_rows;i++){
		for(j=0;j<p;j++){
			printf("%0.4f   ",universe_data[i][j]);
		}
		printf("\n");
	}

}

void store_final_codebook(char * output_file){

	int i, j;
	FILE *fp;

	fp=fopen(output_file, "a");
	for(i=0;i<cbook_size;i++) {
		for(j=0;j<p;j++)
			fprintf(fp, "%lf,", codebook[i][j]);
		fprintf(fp, "\n");
	}
	fclose(fp);
}


void read_universe_data(char *input_file){

	char str[300];
	long int i, j;

	FILE *fp;
	fp=fopen(input_file, "r");
	no_of_rows=0;

	while(!feof(fp)){
		j=0;
		fgets(str, 200, fp); //read a line from the file
		//printf("%s", str);
		char *val=strtok(str, ",");
		while(val!=NULL){
			long double d=atof(val);
			universe_data[no_of_rows][j]=d;
			j++;
			val=strtok(NULL, ",");  //cut the string separated by comma
		}
		//printf("The no of columns is %d \n", j);
		//printf("Reading of row %d \n", row);
		no_of_rows++;
	}
	no_of_rows--;
	printf("The no of rows read is %d\n", no_of_rows);
	//display_universe_data();
	fclose(fp);
}

void generate_codebook(){

	char input_file[150];
	char output_file[150];
	long int i, j;
		
	sprintf(&input_file[0], "./Universe/English/Universe_English.csv");
	sprintf(&output_file[0], "./Codebook/English/Codebook_English.csv");
	remove(output_file);
	printf("\n\n\n%s\n\n", input_file);
	printf("\n\n\n%s\n\n", output_file);
	read_universe_data(input_file);
	LBG();
	store_final_codebook(output_file);
}

