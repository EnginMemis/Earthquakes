#include<stdio.h>
#include<stdlib.h>
#include<string.h>

   struct quake{
		char date_str[15];
 		char hour_str[15];
 		double Latitude;
 		double Longitude;
 		double depth;
 		double ML; 
 		char location_str[50];

		
	}QUAKE[1000];


int menu();
void read_quake_bin_file(FILE *file);
void display_QUAKE_List(struct quake *QUAKE);
void search_city_in_list(struct quake *QUAKE);
void search_magnitude_in_list(struct quake *QUAKE);
void search_sort_magnitude_in_list(struct quake *QUAKE);

int main(){
	int choice;
	int exit=0;
	int count;	
	FILE *file;
	
	
	while(exit==0){
		choice = menu();
		system("cls");
		switch(choice){
		case 1:
			read_quake_bin_file(file);
			break;
		case 2:
			printf("Date         Hour       Latitude(N)  Logitude(E)  Depth(km)   ML          Location\n");
			display_QUAKE_List(QUAKE);
			break;
		case 3:
			search_city_in_list(QUAKE);
			
			break;
		case 4:
			search_magnitude_in_list(QUAKE);
			break;
		case 5:
			 search_sort_magnitude_in_list(QUAKE);
			break;
		case 6:
			exit=1;
			break;
		
		}
	}
	
	
	return 0;
}

int menu(){
	
	int input;	
	printf("Earthquake file processing prog.\n");
	printf("***********************************\n");
	printf("1-Read Binary quake file\n2-Display all records\n3-Search CITY in records\n");
	printf("4-Search magnitude in records\n5-Search magnitude and sort in descending order\n6-Exit\nChoice: ");
	scanf("%d",&input);
	return input;
	
}

void read_quake_bin_file(FILE *file){
	int i=0;
	file = fopen("earthquakes.txt","r");
	if(file==NULL){
		exit(0);
	}
	
	while(!feof(file)){
		fscanf(file,"%s",&QUAKE[i].date_str);
		fscanf(file,"%s",&QUAKE[i].hour_str);
		fscanf(file,"%lf",&QUAKE[i].Latitude);
		fscanf(file,"%lf",&QUAKE[i].Longitude);
		fscanf(file,"%lf",&QUAKE[i].depth);
		fscanf(file,"%lf",&QUAKE[i].ML);
		fgets(QUAKE[i].location_str,50,file);
		i++;
	}
	fclose(file);
	printf("Reading quake struct data (records) from file.\nDone.");
	printf("************************************\n");
	
}

void display_QUAKE_List(struct quake *QUAKE){
	int i=0;
	while(QUAKE[i].ML!=0){
		printf("%s   ",QUAKE[i].date_str);
		printf("%s   ",QUAKE[i].hour_str);
		printf("%.4lf      ",QUAKE[i].Latitude);
		printf("%.4lf     ",QUAKE[i].Longitude);
		printf("%6.2lf       ",QUAKE[i].depth);
		printf("%.2lf   ",QUAKE[i].ML);
		printf("%s   ",QUAKE[i].location_str);
		i++;
		printf("\n");
	}
	
}


void search_city_in_list(struct quake *QUAKE){
	
	char city[20];
	char *found;
	int total=0;
	int i=0;
	printf("Enter city name (in capital letters) to search quakes.");
	printf("\nCity: ");
	scanf("%s",&city);
	
	printf("\nDate         Hour       Latitude(N)  Logitude(E)  Depth(km)   ML          Location\n");
	
	while(QUAKE[i].ML!=0){
		found=strstr(QUAKE[i].location_str,city);
		if(found != NULL){
			printf("%s   ",QUAKE[i].date_str);
			printf("%s   ",QUAKE[i].hour_str);
			printf("%.4lf      ",QUAKE[i].Latitude);
			printf("%.4lf     ",QUAKE[i].Longitude);
			printf("%6.2lf       ",QUAKE[i].depth);
			printf("%.2lf   ",QUAKE[i].ML);
			printf("%s   ",QUAKE[i].location_str);
			printf("\n");
			total++;
		}
		i++;
	}

		printf("*************************************\n");
		printf("Total of %d records found for %s\n\n",total,city);
	
}


void search_magnitude_in_list(struct quake *QUAKE){
	
	float magnitude;
	int i=0,total=0;
	printf("Enter magnitude value to search quakes which are greater than.\n");
	printf("Magnitude: ");
	scanf("%f",&magnitude);
	
	printf("\nDate         Hour       Latitude(N)  Logitude(E)  Depth(km)   ML          Location\n");
	
	while(QUAKE[i].ML!=0){
		if(QUAKE[i].ML >= magnitude){
			printf("%s   ",QUAKE[i].date_str);
			printf("%s   ",QUAKE[i].hour_str);
			printf("%.4lf      ",QUAKE[i].Latitude);
			printf("%.4lf     ",QUAKE[i].Longitude);
			printf("%6.2lf       ",QUAKE[i].depth);
			printf("%.2lf   ",QUAKE[i].ML);
			printf("%s   ",QUAKE[i].location_str);
			printf("\n");
			total++;
		}
		i++;
	}
	
		printf("*************************************\n");
		printf("Total of %d records found\n\n",total);

}

void search_sort_magnitude_in_list(struct quake *QUAKE){
	
	int i,j,total=0;
	float magnitude;
	float temp;
	int max;
	
	printf("Enter magnitude value to search quakes which are greater than.\n");
	printf("Magnitude: ");
	scanf("%f",&magnitude);
	i=0;
	j=0;
	while(QUAKE[i].ML!=0){
		max=i;
		j=i+1;
		while(QUAKE[j].ML!=0){
			if(QUAKE[j].ML>QUAKE[max].ML){
				max=j;
			}
			j++;
		}
		temp=QUAKE[max].ML;
		QUAKE[max].ML=QUAKE[i].ML;
		QUAKE[i].ML=temp;
		i++;
	}
	
	i=0;
	while(QUAKE[i].ML>=magnitude){
		total++;
		i++;	
	}
	printf("Date         Hour       Latitude(N)  Logitude(E)  Depth(km)   ML          Location\n");
	for(i=0;i<total;i++){
		printf("%s   ",QUAKE[i].date_str);
		printf("%s   ",QUAKE[i].hour_str);
		printf("%.4lf      ",QUAKE[i].Latitude);
		printf("%.4lf     ",QUAKE[i].Longitude);
		printf("%6.2lf       ",QUAKE[i].depth);
		printf("%.2lf   ",QUAKE[i].ML);
		printf("%s   ",QUAKE[i].location_str);
		printf("\n");
	}
	printf("***********************************\n");
	printf("Total of %d records.\n\n",total);
	
	getch();
	
}






