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
	if ((neighbours == 2 || neighbours == 3) && A[xpos][ypos] == 1) 
		return 1;
	if (neighbours > 3) return 0;
	if (neighbours == 3) return 1;
}

void displaygrid(int **A, int n){
	int i, j;
	for(i = 0; i < n+2; i++) 
		printf("-");
	printf("\n");
	for( i = 0; i< n; i++){
		printf("|");
		for(j = 0; j< n; j++){
			if(A[i][j] == 1) 
				printf("x");
			else 
				printf(" ");
		}
		printf("|\n");
	}
	for(i = 0; i < n+2; i++)
                printf("-");

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

int main(int argc, char *argv[]){
        int **A, **B;
	FILE *fp;
	int N;
	int i, j;
	
	if( argc != 2){
		fprintf(stderr,"%s: At least one arguement in required\n", argv[0]);
		exit(1);
	}

	if( (fp = fopen(argv[1], "r")) == NULL){
		fprintf(stderr, "%s: Error opening file %s\n", argv[0], argv[1]);
		exit(1);
	}
	
	fscanf(fp, "%d",&N);

       	A = malloc(N * sizeof(int *));
	B = malloc(N * sizeof(int *));
       	for (i = 0; i < N; i++) {
		A[i] = malloc(N * sizeof(int));
		B[i] = malloc(N * sizeof(int));
	}

	for (i=0;i<N;i++)
      		for (j=0;j<N;j++)
			fscanf(fp, "%d", &A[i][j]);

	fclose(fp);

	char c = ' ';
	while(c != 'q'){
		system("clear");
       		displaygrid(A, N);

		for (i=0;i<N;i++)
                	for (j=0;j<N;j++)
                        	B[i][j]= getvalue(A, i, j, N);
		copyarray(A,B, N);
		c = getchar();
	}
	
	return 0;
}
