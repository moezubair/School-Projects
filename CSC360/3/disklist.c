/*Name: Muhammad Zubair
Student Number: V00757068
gets info of disk
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Structure that holds the information for all the files*/
typedef struct{
	char type,*name,*ext,*fullFileName;
	int size,ctime,cdate;
}files;	
files file[223];

/*Gets the information for the files*/
void getFiles(FILE *fp){
	char *name = malloc(sizeof(char)*8);	
	int base = 9728;  /*the first byte of the root directory i.e 19th sector: 19*512*/
   	int cur = base;   /* point to the first byte of the current entry*/
	int offset = 32;  /* Each entry has 32 bytes in root directory*/
	int counter,i = 0;
   	int nameLength;
	unsigned char tmp;
	char tmp2;
   	fseek(fp,0x2B,SEEK_SET);

	fseek(fp, base, SEEK_SET);
	fread(&tmp,1,1,fp);

	while(tmp != 0x00)  
	{
        /*search for files*/
		if (tmp != 0xE5)
		{
           		/*Get the attribute of the file*/
			file[i].type = 'D';
			file[i].name = malloc(sizeof(char)*8);
			file[i].ext = malloc(sizeof(char)*3);
           		file[i].fullFileName = (char *) malloc(sizeof(file[i].name) + sizeof(file[i].ext) + 2);
    
			fseek(fp,-1,SEEK_CUR);			
			fread(file[i].name,1,8,fp);
			fread(file[i].ext,1,3,fp);
          		for (nameLength = 0; nameLength < 8; nameLength++) {
				if (file[i].name[nameLength] != 0x20)
					file[i].fullFileName[nameLength] = file[i].name[nameLength];
				else
					break;
			}
            		/*Cocatinate the file information*/
			strncat(file[i].fullFileName, ".", 1);
			strncat(file[i].fullFileName, file[i].ext, 3);
			/*GEt the time*/
			fseek(fp,cur+14,SEEK_SET);
           		fread(&file[i].ctime,1,2,fp);
            		fread(&file[i].cdate,1,2,fp);
            		fseek(fp,cur+28,SEEK_SET);
			/*get the size*/
			fread(&file[i].size,1,4,fp);
			fseek(fp, cur+11, SEEK_SET);
			fread(&tmp2,1,1,fp);
            
			/*Test if it's a file*/
			if( tmp2!=0x0F && (tmp2 & 0x10) != 0x10 && (tmp2 & 0x08) != 0x08)
			{
				file[i].type = 'F';				
			}
         	 	else if(tmp2 == 0x10){
                		file[i].type = 'D';
            		}
            
			else{
				cur = cur + offset;
				fseek(fp, cur, SEEK_SET);
				fread(&tmp,1,1,fp);
				continue;
            		}
            
		}
		
		// Go to next entry in Root Directory
		cur = cur + offset;
		fseek(fp, cur, SEEK_SET);
		fread(&tmp,1,1,fp);
		i++;
	}
	file[i].name = NULL;	/*NULL marks the end of file list*/

}
/*Extracts the time and date from the data read earlier*/
char *convertDate(int ctime,int cdate){
	char *result = (char *) malloc(sizeof(char));
	/*Extracting the day*/
	int day = 0;
	day = cdate & 0x1F;
	/*Extracting the month*/
	int month = 0;
	month = cdate & 0x1E0;
	month >>= 5;
	/*Extracting the date*/
	int year = 0;
	year = cdate & 0xFE00;
	year >>= 9;
	year += 1980;

	/*Extracting the time-seconds*/
	int sec = 0;
	sec = ctime & 0x3F;
	/*Extracting the time-minutes*/
	int min = 0;
	min = ctime & 0x7E0;
	min >>= 5;
	/*Extracting the time-hours*/
	int hour = 0;
	hour = ctime & 0xFC00;
	hour >>= 11;

	/*Prepare the string and return for printing*/
	sprintf(result,"%4d-%1d-%2d %.2d:%.2d:%.2d",year,month,day, hour, min, sec * 2);

	return result;
}
/*Loops through the files structure and prints information read earlier*/
void listFiles(){
	int i = 0;
	int len = 0;
	while(file[i].name != NULL){
        if(file[i].type == 'F'){
            printf("%c %10d %20s %s\n",file[i].type,file[i].size,file[i].fullFileName,convertDate(file[i].ctime,file[i].cdate));
		}
		else{
			printf("%c %s\n",file[i].type,file[i].name);
		}
		i++;
	}
}
int main(int argc, char** argv){
	FILE *fp;					/*File pointer*/

	if (((fp=fopen(argv[1], "r")))!=NULL)		/*Check to see if file is readable*/
	{
		getFiles(fp);
		listFiles();

	}
	else {
		printf("Fail to open the image file.\n");
	}

}
