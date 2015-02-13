#include <stdio.h>
#include <stdlib.h>

int local[8][2] = {{-1,-1},{0,-1},{1,-1},{-1,0},{1,0},{-1,1},{0,1},{1,1}};

int getvalue(int **A, int xpos, int ypos, int n){
	int neighbours = 0;
	int i, temp1, temp2;
	for (i = 0; i< 8; i++){
		if(xpos+local[i][0] > n-1){
			temp1 = 0;
		}else if(xpos +local[i][0] < 0){
			temp1 = n-1;
		}else{
			temp1 = xpos+local[i][0];
		}
		
		if(ypos+local[i][1] > n-1){
			temp2 = 0;
		}else if(ypos +local[i][1] < 0){
			temp2 = n-1;
		}else{
			temp2 = ypos+local[i][1];
		}
		
		if(A[temp1][temp2] == 1)
			neighbours++;
	}

	if (neighbours < 2) return 0;
	if (neighbours == 2 || neighbours == 3 ) return A[xpos][ypos];
	if (neighbours > 3) return 0;
	if (neighbours == 3) return 1;
}

void copyarray(int **A, int **B, int n){
	int i,j;
	for (i=0;i<n;i++)
                for (j=0;j<n;j++)
                        A[i][j]=B[i][j];
}

void printarray(int **array, int n){
	int i, j;
	for (i = 0; i < n; i++) {
                for (j = 0; j < n; j++)
                        printf("%d ", array[i][j]);
                printf("\n");
        }
}

int main(void){
        int **A, **B;
	int N = 10;
	int i, j;

       	A = malloc(N * sizeof(int *));
	B = malloc(N * sizeof(int *));
       	for (i = 0; i < N; i++) {
		A[i] = malloc(N * sizeof(int));
		B[i] = malloc(N * sizeof(int));
	}

	for (i=1;i<N;i++)
      		for (j=1;j<N;j++)
			A[i][i]=1;
	char c = ' ';
	while(c != 'q'){
		system("clear");
       		printarray(A, N);

		for (i=0;i<N;i++)
                	for (j=0;j<N;j++)
                        	B[i][j]= getvalue(A, i, j, N);
		//printf("\n");
		//printarray(B, N);

		copyarray(A,B, N);
		c = getchar();
	}
	printf("A[%d][%d] will be %d\n",N-1,N-1,getvalue(A,N-1,N-1,N));
	
	return 0;
}
