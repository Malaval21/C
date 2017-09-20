/*
Programmer : Shrunga Malavalli
ID : 11436985
Class : CPTS 411

Assignment 1
Rank 1 sends to rank 0
*/

#include <stdio.h>
#include <mpi.h> 
#include <assert.h>
#include <sys/time.h>
#include <math.h>
#include <stdlib.h>

int main ( int argc, char *argv[])
{
	int rank, p;
	int maxByte = 20;
	struct timeval t1,t2;
	

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
   	MPI_Comm_size(MPI_COMM_WORLD,&p);

   printf("my rank=%d\n",rank);
   printf("Rank=%d: number of processes =%d\n",rank,p);

for(int i = 0;i<=maxByte;i++)
 {


   if(rank==1)
   {  		
   	 	double startTime,endTime,resultTime;
   	 	int dest = 0; 	
   		char *data;
   		int bytes = (int)pow(2.0,(double)i);
   		data = (char *) malloc(bytes);

	    for(int j=0;j<bytes;j++)
	    {
	 		data[j] = (char) rand();
	    }

	 	startTime = MPI_Wtime();
	 	MPI_Send(&data[0],bytes,MPI_BYTE,dest,0,MPI_COMM_WORLD);
	 	endTime = MPI_Wtime();
	 	resultTime = endTime -startTime;
	 	printf("Rank=%d: sent message size %d to rank %d; Send time %f secs\n", rank,bytes,dest,resultTime);
   		
   }
   else if (rank == 0)
   {
   		double startTime,endTime,resultTime;
   		char *dataRecv;
   		int bytes = (int)pow(2.0,(double)i);
   		dataRecv = (char *) malloc(bytes);   		
   		MPI_Status status;

	 	startTime = MPI_Wtime();
	 	MPI_Recv(&dataRecv,i,MPI_BYTE,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
	 	endTime = MPI_Wtime();
	 	resultTime = endTime -startTime;
	 	printf("Rank=%d: received message size %d from rank %d; Recv time %f secs\n",rank,bytes,status.MPI_SOURCE,resultTime);
   }
}

	MPI_Finalize();

return 0;
}