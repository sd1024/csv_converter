#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxline 200

void convertcsv (FILE *, FILE *);

int main (int argc, char *argv[]) {
FILE *csv, *xdc;
char* namecsv;
char* namexdc=".xdc";

if (argc == 1) {
	printf ("need argument - convertcsv file.csv");
	return 1;
} else 
	while (--argc > 0){
		namecsv= *++argv;
		printf("CSV file: %s\n",namecsv);
		if ((csv = fopen(namecsv, "r"))== NULL) {
			fprintf (stderr, "can't open file %s\n", namecsv);
			return 1;
		} else {
			char* newname = malloc(strlen(namecsv) + strlen(namexdc) + 1);
			*newname='\0';
			strcat(newname, namecsv);
			strcat(newname, namexdc);
			printf("XDC file: %s\n",newname);
			xdc = fopen(newname , "w");
			convertcsv(csv, xdc);
			fclose(xdc);
			fclose(csv);
			free(newname);
			}			
	}
return 0;
}

void convertcsv ( FILE *csv, FILE *xdc) {

int i, j, k;

int prm=0;
char *pinstd; 
char *pinpkg; 
char *portpkg;

pinstd = "set_property IOSTANDARD LVCMOS33 [get_ports *]\n";
pinpkg = "set_property PACKAGE_PIN ";
portpkg =" [get_ports ";
char pin[10] = {0};
char port[20] = {0};
int linesize;
char s[maxline];
char *pline;
char *line;
fprintf(xdc, "%s", pinstd);
//read file
//do {
//line=fgets(s, maxline, csv);
while ((line=fgets(s, maxline, csv)) != NULL){
//printf("do...\n");
//printf("%s",s);

pline=&s[0];
	for (i=0, j=0, k=0; (*pline != '\0'); i++) {
				//printf("%d\n", lll);
//				printf("cicle\n");

			if (*pline ==',' || *pline =='#') {
				if (prm == 0){
//					printf(",\n");
					prm = 1;
				} else if (prm == 1) {
//					printf(",\n");
					prm = 2;
					} else ;;
			} else	{ 
			switch (prm) {
			case 0 :
//				printf("prm=0\n");
				pin[k]=s[i];
				k++;
				break;
				
			case 1 :
//				printf("prm=1\n");
				port[j]=s[i];
				j++;
				break;
			default : break;
				}
			}
		pline++; //next char
	}

		//line++;	//next line
		pin[i+1]='\0';	
		port[j+1]='\0';
		prm=0;
//		printf("write string\n");


		fprintf(xdc,"%s", pinpkg);
		fprintf(xdc,"%s",pin);
		fprintf(xdc,"%s",portpkg);
		fprintf(xdc,"%s",port);
		fprintf(xdc,"%s","]\n");
		memset(pin, 0, sizeof(pin));
		memset(port, 0, sizeof(port));

}
//	} while (line != NULL);
		
}

