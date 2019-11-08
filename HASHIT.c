#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int numberofkeys;
int hash(char arr[],int size){
    int i;
    int h=0;
    for(i=0;i<size;i++){
        int k=(int)(arr[i]);
        h=h+(k)*(i+1);
    }
    h=19*h;
    return h;
}
int check(char arr[][17],char* c,int h){
    int j=0;
    int hash;
    while(j<20){
        hash=((int)(h)+(j*j)+(23*j))%101;
        int check=strcmp(arr[hash],c);
        if(check==0)
            return hash;
        j++;
        }
    return -1;
}
void spaceinarr(char arr[][17],char c[],int h,int size){
    int j=0;
    int hash=h;
    if(check(arr,c,h)==-1)
        while(j<20){
            if(arr[(hash+j*j+23*j)%101][0]=='\0'){
                strcpy(arr[(hash+j*j+23*j)%101],c);
                numberofkeys++;
                break;
            }
            j++;
        }
    return;
}
void delete(char arr[][17],char s[],int h)
{
    int j=0;
    int hash=h%101;
    int flag=check(arr,s,h);
    if(flag!=-1){
        numberofkeys--;
        //printf("after deletion %s\n",arr[flag] );
        arr[flag][0]='\0';
        //printf("after deletion %s\n",arr[flag] );
    }
    return;
    }
int main(){
    int test;
    scanf("%d",&test);
    while(test--){
        numberofkeys=0;
        char arr[101][17]={'\0'};
        int n1;
        scanf("%d",&n1); //number of queries
        while(n1--){
            char c[30];
            scanf("%s",c);
            if (c[0]=='A')
            {
                char s[17];
                int size = strlen(c);
                int k = 0;
                for(k=0;k<size-4;k++){
                    s[k]=c[k+4];
                }
                s[k] = '\0';
                int sizeofs=strlen(s);
                int h=hash(s,sizeofs);
                //printf("this is s %s\n",s);
                spaceinarr(arr,s,h,sizeofs);
            }
            else if(c[0]=='D'){
                char s[17];    
                 int size = strlen(c);
                int k = 0;
                for(k=0;k<size-4;k++){
                    s[k]=c[k+4];
                }
                s[k] = '\0';
                int sizeofs=strlen(s);
                int h=hash(s,sizeofs);      
                //printf("this is s%s\n",s);          
                delete(arr,s,h);
            }
          }
        printf("%d \n",numberofkeys);
        for(int i=0;i<101;i++){
            if(arr[i][0]!='\0'){
                printf("%d:%s\n",i,arr[i]);
            }
        }
        }
    } 