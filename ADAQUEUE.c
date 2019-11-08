#include<stdlib.h>
#include<stdio.h>
#include<string.h>


typedef struct node{
    int value;
    struct node* next;
    struct node* prev;
}node;
node* head=NULL;
node* tail=NULL;
int si=0;
int k=0; //for seeing number of times its reversing

void pushf(int val){
    //si++;
    if(head==NULL){
        head=(node*)malloc(sizeof(node));
        tail=(node*)malloc(sizeof(node));
        head->value=val;
        head->next=NULL;
        head->prev=NULL;
        tail=head;
       // printf("%d",tail->value);
        return;
    }

    node *temp=(node*)malloc(sizeof(node));
    if(k%2==0){
    temp->value=val;
    head->next=temp;
    temp->prev=head;
    temp->next=NULL;
    head=temp;
    }
    else{
        temp->value=val;
        temp->next=tail;
        tail->prev=temp;
        temp->prev=NULL;
        tail=temp;
    }
}
void pushb(int val){
    //si++;
    if(head==NULL){
        head=(node*)malloc(sizeof(node));
        tail=(node*)malloc(sizeof(node));
        head->value=val;
        head->next=NULL;
        head->prev=NULL;
        tail=head;
        return;
    }
    else{
        node *temp=(node*)malloc(sizeof(node));
        if(k%2==0){
        temp->value=val;
        temp->next=tail;
        temp->prev=tail->prev;
        tail->prev=temp;
        tail=temp;
        }
        else{
          temp->value=val;
          head->next=temp;
          temp->prev=head;
          temp->next=NULL;
          head=temp;
        }

    }
}
void back(){
    //si--;
    if(tail==NULL){
        printf("No job for Ada?\n");
    }
    else{
        if (tail!=head){
            if(k%2==0){
            printf("%d \n",tail->value);
            tail=tail->next;
            }
            else{
            printf("%d \n",head->value);
            head=head->prev;
            }
        }
        else if(tail==head){
          printf("%d \n",tail->value);
          tail=NULL;
          k=0;
          head=NULL;
        }
    
    }
}


void front(){
   if(head==NULL){
       printf("No job for Ada? \n"); 
   }
   else{
      // si--;
       if (tail!=head){
        if(k%2==0){
        printf("%d \n",head->value);
        head=head->prev;
        }
        else{
            printf("%d \n",tail->value);
           // printf("%d \n ",tail->prev->value);
             tail=tail->next;
        }}
       else if(tail==head){
          printf("%d \n",head->value);
          k=0;
          head=NULL;
          tail=NULL;
   }

}
}

void reverse(){
    k++;
    
}
int main(){
    /* for(int i=1;i<5;++i){
    pushf(i);
    pushb(i+10);
    }
  
   // front();
    node* tmp;
    reverse();
    //printf("%d \n",k);
    tmp=tail;
     
    for(int i =0;i<si;i++){
        printf("%d \n",tmp->value);
        if(k%2==0){
        tmp=tmp->next;
        }
        else{
            tmp=tmp->prev;
        }
    }  */ 
int n;
  scanf("%d", &n);
  while (n--)
  { 
    //printf("%d \n",n);
    char c[10];
    scanf("%s", c);
    if (strcmp(c, "toFront") == 0)
    {
      int val;
      scanf("%d", &val);
      pushf(val);
   
    }
    else if (strcmp(c, "push_back") == 0)
    {
       int val;
      scanf("%d", &val);
      pushb(val);
    }
    else if(strcmp(c, "reverse") == 0)
    {
      reverse();
    }
    else if(strcmp(c, "front")==0){
        front();
        }
    else if(strcmp(c, "back")==0){
        back();
    }
  }
return 0;
}
  
        
 