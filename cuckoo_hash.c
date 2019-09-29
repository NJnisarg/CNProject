#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#define int_max 2147483647
#define int_min -2147483648

void swap(int *a,int *b){
    int temp=*a;
    *a=*b;
    *b=temp;
}
bool search(int x,int t[],int size){
    for(int i=0;i<size;i++)
    if(t[i]==x)
    return true;
    return false;
}
bool lookup(int x,int t1[],int t2[],int size){
    if(search(x,t1,size)||search(x,t2,size))
    return true;
    else
    return false;    
}
int hashFunction(int functionNo,int size, int key){
    switch(functionNo){
        case 1: return (key%size);
        case 2: return ((key/size)%size);
        default:    return -1;
    }
}
void rehash(int x){
    printf("\n%d is not hashed. Rehash required.\n",x);
    return;
}
void insert(int x,int t1[],int t2[], int size){
    if(lookup(x,t1,t2,size))
    return;
    int temp_index;
    for(int i=0;i<size;i++){
        //Hash the key in the 1st table 

        //printf("i=%d, x=%d ",i,x);
        temp_index=hashFunction(1,size,x);
        //printf("1: %d, x=%d  ",temp_index,x);
        if(t1[temp_index]==int_min){
            t1[temp_index]=x;
            return;
        }
        else
        swap(&x,&t1[temp_index]);

        //No. of iterations increased by 1
        i++;
        if(i>=size)
        break;

        //Hash the key in the 2nd table
        temp_index=hashFunction(2,size,x);
        //printf("2: %d, x=%d  ",temp_index,x);
        if(t2[temp_index]==int_min){
            t2[temp_index]=x;
            return;
        }
        else
        swap(&x,&t2[temp_index]); 
        //printf("\n");    
    }
    rehash(x);
    return;
}
void showHashTable(int t[],int size){
    printf("\n");
    for(int i=0;i<size;i++){
        if(t[i]==int_min)
        printf("- ");
        else
        printf("%d ",t[i]);        
    }
}
void cuckoo(int size,int t1[],int t2[],int arr[]){
    for(int i=0;i<size;i++){
        insert(arr[i],t1,t2,size);
        //showHashTable(t1,size);
        //showHashTable(t2,size);
        //printf("\n");
    }
    printf("\nFinal Hash Tables:");
    showHashTable(t1,size);
    showHashTable(t2,size);
}
int main(){
    int size;
    printf("Enter size of hash tables: ");scanf("%d",&size);
    int *t1,*t2,*arr;
    t1=(int*)malloc(size*sizeof(int));
    t2=(int*)malloc(size*sizeof(int));
    arr=(int*)malloc(size*sizeof(int));
    printf("Enter array of keys to be inserted:\n");
    for(int i=0;i<size;i++)
    scanf("%d",&arr[i]);
    for(int i=0;i<size;i++){
        t1[i]=int_min;
        t2[i]=int_min;
    }
    cuckoo(size,t1,t2,arr);
    printf("\n");
    return 0;
}