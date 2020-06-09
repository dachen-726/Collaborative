#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void operate1(char *, char *, char *, char *, int, int);//Interval comparison
void operate2(char *, char *, char *, char *, int, int);//Sequence comparison

int main(int argc, char *argv[]){
  int arg = argc, start, end;
  char filenameA[20], filenameB[20];

  if (arg == 1) {
    printf("no file inputed");
    return 0;
  }

  if (argv[1][1] == 'c') {
    start = (argv[3][0] - '0' + 1);
    end = (argv[5][0] - '0' + 1);
      
    strcpy(filenameA,argv[6]);
    strcpy(filenameB,argv[7]);
      
    operate1(filenameA,filenameB,"A&B_A.txt","A-B.txt",start,end);//get "A&B_A.txt","A-B.txt"
    operate1(filenameB,filenameA,"A&B_B.txt","B-A.txt",end,start);//get "A&B_B.txt","B-A.txt"
  }

  if (argv[1][1] == 'n') {
    start = argv[3][0] - '0' + 1;
    end = argv[5][0] - '0' + 1;
   
    strcpy(filenameA,argv[6]);
    strcpy(filenameB,argv[7]);

    operate2(filenameA,filenameB,"A&B_A.txt","A-B.txt",start,end);//get "A&B_A.txt","A-B.txt"
    operate2(filenameB,filenameA,"A&B_B.txt","B-A.txt",end,start);//get "A&B_B.txt","B-A.txt"
  }

  return 0;
}

void operate1(char *filenamea, char *filenameb, char *target1, char *target2, int start, int end)
{
  FILE *fp1, *fp2, *fp3, *fp4;
  int i = 0, k = 0, flag = 1, jud = 0, s = start, e = end, jud1, jud2, jud3, jud4;
  char a1[50], a2[50], b[500], c1[50], c2[50], d[500];
  if ((fp1 = fopen(filenamea,"r")) == NULL) exit(1);
  if ((fp2 = fopen(filenameb,"r")) == NULL) exit(1);
  if ((fp3 = fopen(target1,"w")) == NULL) exit(1);
  if ((fp4 = fopen(target2,"w")) == NULL) exit(1);
  
  while (fgets(b,500,fp1) != NULL){//1
    if (b[0] == '#') continue;
    while (flag != s){//2
      if(b[i] == '\t') flag++;
      i++;
    }//2
    while (flag == s){//3
      a1[k++]=b[i++];
      a1[k]='\0';
      if (b[i] == '\t') flag++;
    }//3
    k=0;i++;

    while (flag == (s+1)){//4
      a2[k++]=b[i++];
      a2[k]='\0';
      if (b[i] == '\t') flag++;
      if (b[i] == '\0' || b[i] == '\n') break;
    }//4
    flag=1; i=0; k=0; jud=0;
    
    while (fgets(d,1000,fp2) != NULL){//5
      jud = 0;
      if (d[0] == '#') continue;
      while (flag != e){//6
        if (d[i] == '\t') flag++;
        i++;
      }//6
      while (flag == e){//7
        c1[k++]=d[i++];
        c1[k]='\0';
	if (d[i] == '\t') flag++;
      }//7
      k=0;i++;

      while (flag == (e+1)){//8
        c2[k++]=d[i++];
        c2[k]='\0';
	if (d[i] == '\t') flag++;
	if (d[i] == '\0' || d[i] == '\n') break;
      }//8
      flag=1; i=0; k=0;

      jud1=atoi(a1);
      jud2=atoi(a2);
      jud3=atoi(c1);
      jud4=atoi(c2);
      if (jud1 <= jud4 && jud3 <= jud2) jud = 1;
      if (jud == 1){//9
        fputs(b,fp3);
        break;
      }//9
    }//5
    if (jud == 0) fputs(b,fp4);
    rewind(fp2);
    flag=1; i=0; k=0;
  }//1

  fclose(fp1);
  fclose(fp2);
  fclose(fp3);
  fclose(fp4);
}
 

void operate2(char *filename1, char *filename2, char *target1, char *target2, int start, int end)//two inputs files  two output files  two positional parameter
{
  FILE *fp5, *fp6, *fp7, *fp8;
  int i = 0, k = 0, flag = 1, s = start, e = end, jud = 0;
  char A[50]={'\0'}, B[500]={'\0'}, C[50]={'\0'}, D[500]={'\0'};

  if ((fp5 = fopen(filename1,"r")) == NULL) exit(1);
  if ((fp6 = fopen(filename2,"r")) == NULL) exit(1);
  if ((fp7 = fopen(target1,"w")) == NULL) exit(1);
  if ((fp8 = fopen(target2,"w")) == NULL) exit(1);

  while(fgets(B,500,fp5) != NULL){//1
    if (B[0] == '#') continue;
    while (flag != s){//2
      if (B[i] == '\t') flag++;
      i++;
    }//2
    while (flag == s){//3
      if (B[i] == '\t' || B[i] == '\0') {flag++; break;}
      A[k++]=B[i++];
      A[k]='\0';
      if (B[i] == ';' || B[i] == '\t' || B[i] == '\n') break;
    }//3
    i=0; k=0; flag=1;

    while(fgets(D,500,fp6) != NULL){//4

      jud=0;
      if (D[0] == '#') continue;
      while (flag != e) {//5
	if (D[i] == '\t') flag++;
	i++;
      }//5

      while (flag == e){//6
	if (D[i] == '\t' || D[i] == '\0') flag++;
	C[k++]=D[i++];
	C[k]='\0';
	if (D[i] == ';' || D[i] == '\t' || D[i] == '\n') break;
      }//6

      if (strstr(C,A)) jud = 1;
      if (strstr(A,C)) jud = 1;

      if (jud == 1) fputs(B,fp7);
      if (jud == 1) break;
      i=0; k=0; flag=1;
    }
    if (jud == 0) fputs(B,fp8);
      rewind(fp6);
    i=0; k=0; flag=1;
  }

  fclose(fp5);
  fclose(fp6);
  fclose(fp7);
  fclose(fp8);
}
