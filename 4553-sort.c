#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
// defining a new data type to pass indeces around
typedef struct Cell
{
    int startindex;
    int endindex;

} celltype;


int inputarray[50];


void sort_merge(int strt ,int end){

    // get middle to make pointer to second part and move it around
    int middle = (end+strt)/2;
    int pointerleftpart = strt;
    int pointerrightpart = middle+1;
    int arrindex = 0;
    // initializing the splitted array
    int arrsize = end - strt + 1 ;
    int arr[arrsize];

    // when we compare both values of left and right arrays
    while (pointerleftpart <= middle && pointerrightpart <= end)
    {
            if (inputarray[pointerleftpart] > inputarray[pointerrightpart])
            {
                // sort them ascendingly
                arr[arrindex++] = inputarray[pointerrightpart++];
            }else{
                arr[arrindex++] = inputarray[pointerleftpart++];
            }
    }
    // second case when we have elements on left side only
    while(pointerleftpart <= middle){
        arr[arrindex++] = inputarray[pointerleftpart++];
    }
    // third case when we have elements on the right side only
    while(pointerrightpart <= end){
        arr[arrindex++] = inputarray[pointerrightpart++];
    }

    //returning the sorted part in place in input array
    int i=0;
    for ( i = 0; i < arrsize; i++)
    {
        inputarray[strt+i] = arr[i];
    }

}







void * mergesort(void * argument){

    celltype * newcell = (celltype *)argument; // take input from function
    int middleindex = ( newcell->startindex + newcell->endindex )/2;
    celltype lefthalf ;
    lefthalf.startindex = newcell->startindex;
    lefthalf.endindex = middleindex;
    celltype righthalf ;
    righthalf.startindex = middleindex + 1 ;
    righthalf.endindex = newcell->endindex;

    // stoping condition
    if(newcell->startindex >= newcell->endindex) return;

    pthread_t leftthread ;
    pthread_t rightthread ;
    pthread_create(&leftthread,NULL,mergesort,&lefthalf);
    pthread_create(&rightthread,NULL,mergesort,&righthalf);
    pthread_join(leftthread,NULL);
    pthread_join(rightthread,NULL);
    sort_merge(newcell->startindex,newcell->endindex);
    pthread_exit(NULL);
}



//main function
 int main()
{
    //read the array first
    FILE * fptr = fopen("/home/abobakr/Documents/input.txt","r");
    printf("file opened successfully\n");
    celltype inindex;
    int arrsize = 0;
    fscanf(fptr,"%d\n",&arrsize);
    printf("read array size = :: %d\n",arrsize);
    int i=0;
    printf("read array ::\n");
    for ( i = 0; i < arrsize; i++)
    {
        fscanf(fptr,"%d",&inputarray[i]);
        printf("%d  ",inputarray[i]);
    }

    printf("\nfinished reading the array input \n");
    inindex.startindex = 0;
    inindex.endindex = arrsize-1;
    pthread_t thread ;
    pthread_create(&thread,NULL,mergesort,&inindex);
    printf("finished creation of threads\n");
    pthread_join(thread,NULL);
    printf("finished joining\n");
    printf("\n\nSorted Array ::\n");
    for ( i = 0; i < arrsize; i++)
    {
        printf("%d  ",inputarray[i]);
    }
    printf("\n");




    return 0;
}
