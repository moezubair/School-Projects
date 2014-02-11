/*Name: Muhammad Zubair
Student Number: V00757068
Displays the file info
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h> 
#include <fcntl.h>
#include <string.h>

/*Gets os name and stores in the char passed in parameter*/
void getOsName(char* oem, char * mmap){
	int i;
	int offset = 3;
	for (i=0;i<8;i++){
		oem[i]=mmap[offset+i];
	}
}
/*Retrieves and returns total sectors*/
int getTotalSize(char *mmap){
	int tmp1,tmp2;
	int retVal;

	tmp1 = mmap[19];
	tmp2 = mmap[20];
	retVal = tmp1+((tmp2)<<8);		/*convert two bytes to 16-bit value*/

	return retVal;
};
/*Returns the number of sectors in data section that have corresponding FAT tables of 0x00*/
int getFreeSectors(char *mmap){
	int base = 0x200;				/*starting byte number*/
	int n = 2;					/*first sector in data area*/
	int tmp1;
	int tmp2;
	int counter=0;
	int result=0;
	for(n;n<=2848;n++){
		tmp1=mmap[1+base+(3*n)/2];		/*first 8 bits*/
		tmp2=mmap[base+(3*n)/2];		/*second 8 bits*/
		if (n%2==0) {				/*algorithm for even n*/
			result = tmp2+ ((tmp1&0x0F)<<8);
		}
		else{					/*Algorithm for odd n*/
			result = (tmp1<<4) +(tmp2>>4);
		}
		if (result== 0x00){			/*Increment counter of sectors that are free*/
			counter++;
		}
	}
	return counter;

}
/*Gets the number of files in root directory and the label of the disk*/
void getDirectoryInfo(int *counter, char* label, char* mmap){


	int base = 9728;  	//the first byte of the root directory i.e 19th sector: 19*512
	int cur = base;   	//point to the first byte of the current entry
	int offset = 32;  	//each entry has 32 bytes in root directory
	int i;
	*counter=0;
	char tmp;
	char tmp2;
	tmp = mmap[base];
	while(tmp != 0x00)  	/*I.e not empty*/
	{

		if (tmp != 0xE5)/*Not deleted*/
		{
			//locate the byte for the current entry's attribute
			tmp2=mmap[cur+11];
			//what is the attribute of a file ?
			//not 0x0F(not part of a long file name), not suddirectory, not volume label
			if( tmp2!=0x0F && (tmp2 & 0x10) != 0x10 && (tmp2 & 0x08) != 0x08)
			{
				*counter=*counter+1;

			}
			
			//volume label			
			if (tmp2 == 0x08)		
			{
				for (i=0;i<11;i++){
					label[i]=mmap[i+cur];
				}
			}
		}
		//go to next entry in Root Directory
		cur = cur + offset;
		tmp=mmap[cur];
	}

}
/*get number of fat copies*/
int getFatCopies(char* mmap){
	int offset = 0x0010;
	return mmap[offset];
}
/*Get sectors per fat*/
int sectorsFat(char *mmap){
	int offset = 0x0016;				/*Starting point to read*/
	int tmp1 = mmap[offset];			/*read first byte*/
	int tmp2 = mmap[offset+1];			/*read second byte*/
	return (tmp1+(tmp2<<8));			/*COnvert to 16bit and return*/
}
int main(int argc, char** argv){
	FILE *fp;					/*File pointer*/
	char *oem = malloc(sizeof(char)*8);		/*name of operating system*/
	char *label = malloc(sizeof(char)*11);					/*Label*/
	int totalSize, freeSize;
	int numFiles;
	int fd;
	struct stat sf;
	char *p;

	if (((fd=open(argv[1], O_RDONLY)))>=0)		/*Check to see if file is readable*/
	{

		fstat(fd, &sf);
		p = mmap(NULL,sf.st_size, PROT_READ, MAP_SHARED, fd, 0);
		printf("Successfully open the image file.\n");

		getOsName(oem,p);				/*Get the operating system name*/
		totalSize = getTotalSize(p);			/*Get the size*/
		freeSize = getFreeSectors(p);			/*Get the free size*/
		getDirectoryInfo(&numFiles,label,p);		/*Get number of files, and label*/
		fprintf(stdout,"Os Name: %s\n",oem);
		fprintf(stdout,"Label of the disk: %s\n",label);
		fprintf(stdout,"Total size of the disk: %d bytes\n",totalSize*512);
		fprintf(stdout,"Free size of the disk: %d bytes (%d free sectors in the data area)\n",freeSize*512,freeSize);
		fprintf(stdout,"\n===========\n");
		fprintf(stdout,"The number of files in the root directory(not including subdirectories):%d\n",numFiles);
		fprintf(stdout,"\n===========\n");
		fprintf(stdout,"Number of FAT copies: %d\n",getFatCopies(p));
		fprintf(stdout,"Sectors per FAT:%d\n",sectorsFat(p)); 
	}
	else {
		printf("Fail to open the image file.\n");
	}
	close(fd);
	free(oem);
	free(label);
}
