/*
Name - Rohit Kumar Sah
UIN - 831000250
Collaborated with: None
*/


#include<stdio.h>
#include <stdlib.h>
#include<time.h>
#include<sys/time.h>
#include <unistd.h>
#include<string.h>


int queue[2000];
int size;
float avg;


#define LOW 0
#define HIGH 4999


void fcfsDS(int *queue, int head){

  int diff;
  long long int seek = 0;

  queue[0] = head;

  for(int j = 0; j<size; j++){
    diff = abs(queue[j]-queue[j+1]);
    seek += diff;
  }

  printf("Total number of head movements = %lld\n", seek);
  avg = seek/(float)size;
  printf("Average seek time = %f\n", avg);

}

void scanDS(int *queue, int head){

  long long int seekL = 0, seekR = 0;
  int right[1000], left[1000], r= 0, l= 0, i, j, temp, curr;
  int headT = head;

  for(i = 1; i <= size; i++) {

      if(queue[i] >= head){
          right[r] = queue[i];
          r++;
      } else {
          left[l] = queue[i];
          l++;
      }
  }

  for(i = 0; i<r-1; i++){
    for(j = i+1; j<r; j++){
        if(right[i] > right[j]){
          temp = right[i];
          right[i] = right[j];
          right[j] = temp;
      }
    }
  }

  for(i = 0; i<l-1; i++){
    for(j = i+1; j<l; j++){
      if(left[i] > left[j]){
          temp = left[i];
          left[i] = left[j];
          left[j] = temp;
      }
    }
  }

  for(i = 0; i<r; i++)
    printf("%d ",right[i]);

  for(i = 0 ;i<l ;i++)
    printf("%d ",left[i]);



  for(int i = 0; i < r; i++) {
    curr = right[i];
    seekR += abs(curr - head);
    head = curr;
  }

  seekR += abs(HIGH - head);
 
  head = HIGH;
 
  for (int i = l-1; i >=0; i--) {
    curr = left[i];
    seekR += abs(curr - head);
    head = curr;
  }
 
  head = headT;
 
  for (int i = l-1; i >=0; i--) {
    curr = left[i];
    seekL += abs(curr - head);
    head = curr;
  }

  seekL += abs(head - LOW);
  head = LOW;

  for(int i = 0; i < r; i++) {
    curr = right[i];
    seekL += abs(curr - head);
    head = curr;
  }

  printf("\nDirection: Left\n");
  printf("Total number of head movements = %lld\n", seekL);
  avg = seekL/(float)size;
  printf("Average seek time = %f\n", avg);
  printf("\nDirection: Right\n");
  printf("Total number of head movements = %lld\n", seekR);
  avg = seekR/(float)size;
  printf("Average seek time = %f\n", avg);
}



void cscanDS(int *queue, int head){
  
  int i,j, temp, curr, right[1000], left[1000], r=1, l=1;
  long long int seek = 0;

  left[0] = LOW;
  right[0] = HIGH;

  for(i = 1; i <= size; i++) {

      if(queue[i] >= head){
          right[r] = queue[i];
          r++;
      } else {
          left[l] = queue[i];
          l++;
      }
  }

  for(i = 0; i<r-1; i++){
    for(j = i+1; j<r; j++){
        if(right[i] > right[j]){
          temp = right[i];
          right[i] = right[j];
          right[j] = temp;
      }
    }
  }

  for(i = 0; i<l-1; i++){
    for(j = i+1; j<l; j++){
      if(left[i] > left[j]){
          temp = left[i];
          left[i] = left[j];
          left[j] = temp;
      }
    }
  }


  for(int i = 0; i < r; i++) {
    curr = right[i];
    seek += abs(curr - head);
    head = curr;
  }
 
  head = 0;
 
  seek += HIGH;
 
  for (int i = 0; i < l; i++) {
    curr = left[i];
    seek += abs(curr - head);
    head = curr;
  }

  
  printf("Total number of head movements = %lld\n", seek);
  avg = seek/(float)size;
  printf("Average seek time = %f\n", avg);
}


int main(){

  int choice;

  int i;
  time_t t;

    
  srand((unsigned) time(&t));

  printf("\nGenerating 1000 random integers between 0 and 5000\n");
  for(int i = 1;i <= 1000;i++){
    queue[i] = rand() % 5000;
  }

  for(int i = 1; i <= 1000; i++){
      printf("%d ", queue[i]);
  }

  do {
    printf("\nChoose a Disk Replacement Algorithm:\n");
    printf("Enter 1 for FCFS\nEnter 2 for SCAN \nEnter 3 for C-SCAN\nEnter 0 to Exit\n");
    scanf("%d", &choice);
    if (choice == 0){
      printf("Exiting..........");
      break;
    }
    if (choice > 3){
      printf("!!!!!!Invalid Choice!!!!!\n");
      continue;
    }

    printf("\n!!!!!!!!!!!!!!!You chose %s Disk Scheduling Algorithm!!!!!!!!!!!!!!!!\n\n", choice==1? "FCFS"
  : choice == 2 ? "SCAN" : "C-SCAN");

    size = 1000;
    
    int head;
    printf("\n%s\n","Enter initial head position");
    scanf("%d", &head);

    int tmp[2000];

    for(int i=1;i<=size;i++)
        tmp[i] = queue[i];

    if (choice == 1)
      fcfsDS(tmp, head);
    if (choice == 2)
      scanDS(tmp, head);
    if (choice == 3)
      cscanDS(tmp, head);

  } while(1);

  return 0;
}