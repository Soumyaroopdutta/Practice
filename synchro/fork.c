#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
    
int sum = 0;
int x = 0;

int pid;

if((pid = fork()) == 0){
    x = 1;
    sum = sum+10;
    printf("child task, %d\n", sum );
 }
 else{
     x = 2;
     sum = sum + 5;
     printf("parent, %d\n", sum);
     sleep(2); 
 }

 printf(" x= %d, task %d \n", x, sum);

sum = sum + 20;
 printf(" x= %d, task %d \n", x, sum);
 return 1;   
}
