/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */

//2015-18525 김세훈
//csapp-2017summer-student09

#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
	int temp;
	int i, j, m, n;
	int x1, x2, x3, x4, x5, x6, x7;	
	if(M==32 && N==32){


		for(m=0; m<4; m++){
			for(n=0; n<4; n++){

				if(n==m){

					for(i=0; i<8; i++){
						for(j=0; j<8; j++){
							B[8*m+7-i][8*n+7-j] = A[8*m+i][8*n+j];
						}
					}

					for(i=0; i<8; i++){
						for(j=0; j<8-i; j++){
							temp = B[8*m+i][8*n+j];
							B[8*m+i][8*n+j] = B[8*m+7-j][8*n+7-i];
							B[8*m+7-j][8*n+7-i] = temp;
						}
					}
					
					continue;

				}

				for(i=8*m; i<8*m+8; i++)
					for(j=8*n; j<8*n+8; j++)
						B[j][i] = A[i][j];

			}
		}

	}
	else if(M==64 && N==64){

		for(m=0; m<8; m++){
		
			for(n=0; n<8; n++){
			
				if(n==m){

					//diagonal
					
					for(i=m*8; i<m*8+4; i++){
						for(j=n*8+4; j<n*8+8; j++){
							B[j][i] = A[i][j];
						}
					}
					

					//copy A to B

					temp = A[m*8][n*8+0];
					x1 = A[m*8][n*8+1];
					x2 = A[m*8][n*8+2];
					x3 = A[m*8][n*8+3];
					x4 = A[m*8+1][n*8+0];
					x5 = A[m*8+1][n*8+1];
					x6 = A[m*8+1][n*8+2];
					x7 = A[m*8+1][n*8+3];
					
					for(i=m*8+2; i<m*8+4; i++){
						for(j=n*8; j<n*8+4; j++){
							B[i-2][j] = A[i][j];
						}
					}

					for(i=m*8+2; i<m*8+4; i++){
						for(j=n*8; j<n*8+4; j++){
							B[i][j] = B[i-2][j];
						}
					}
					
					B[m*8][n*8+0] = temp;
					B[m*8][n*8+1] = x1;
					B[m*8][n*8+2] = x2;
					B[m*8][n*8+3] = x3;
					B[m*8+1][n*8+0] = x4;
					B[m*8+1][n*8+1] = x5;
					B[m*8+1][n*8+2] = x6;
					B[m*8+1][n*8+3] = x7;
					
					//transpose B

					for(i=m*8; i<m*8+4; i++){
						for(j=i+1; j<n*8+4; j++){
							temp = B[i][j];
							B[i][j] = B[j][i];
							B[j][i] = temp;
						}
					}

					//diagonal

					for(i=m*8+4; i<m*8+8; i++){
						for(j=n*8; j<n*8+4; j++){
							B[j][i] = A[i][j];
						}
					}
					

					//copy A to B

					temp = A[m*8+4][n*8+4];
					x1 = A[m*8+4][n*8+5];
					x2 = A[m*8+4][n*8+6];
					x3 = A[m*8+4][n*8+7];
					x4 = A[m*8+5][n*8+4];
					x5 = A[m*8+5][n*8+5];
					x6 = A[m*8+5][n*8+6];
					x7 = A[m*8+5][n*8+7];
	
					for(i=m*8+6; i<m*8+8; i++){
						for(j=n*8+4; j<n*8+8; j++){
							B[i-2][j] = A[i][j];
						}
					}

					for(i=m*8+6; i<m*8+8; i++){
						for(j=n*8+4; j<n*8+8; j++){
							B[i][j] = B[i-2][j];
						}
					}
					
					B[m*8+4][n*8+4] = temp;
					B[m*8+4][n*8+5] = x1;
					B[m*8+4][n*8+6] = x2;
					B[m*8+4][n*8+7] = x3;
					B[m*8+5][n*8+4] = x4;
					B[m*8+5][n*8+5] = x5;
					B[m*8+5][n*8+6] = x6;
					B[m*8+5][n*8+7] = x7;
					
					//transpose B

					for(i=m*8+4; i<m*8+8; i++){
						for(j=i+1; j<n*8+8; j++){
							temp = B[i][j];
							B[i][j] = B[j][i];
							B[j][i] = temp;
						}
					}

					continue;

				}

				for(i=m*8; i<m*8+4; i++){
					for(j=n*8; j<n*8+4; j++){
						B[j][i] = A[i][j];
					}
				}

				temp = A[m*8][n*8+4];
				x1 = A[m*8][n*8+5];
				x2 = A[m*8][n*8+6];
				x3 = A[m*8][n*8+7];
				x4 = A[m*8+1][n*8+4];
				x5 = A[m*8+1][n*8+5];
				x6 = A[m*8+1][n*8+6];
				x7 = A[m*8+1][n*8+7];

				for(i=m*8+4; i<m*8+8; i++){
					for(j=n*8; j<n*8+4; j++){
						B[j][i] = A[i][j];
					}
				}

				
				B[n*8+4][m*8] = temp;
				B[n*8+5][m*8] = x1;
				B[n*8+6][m*8] = x2;
				B[n*8+7][m*8] = x3;
				B[n*8+4][m*8+1] = x4;
				B[n*8+5][m*8+1] = x5;
				B[n*8+6][m*8+1] = x6;
				B[n*8+7][m*8+1] = x7;

				temp = A[m*8+6][n*8+4];
				x1 = A[m*8+6][n*8+5];
				x2 = A[m*8+6][n*8+6];
				x3 = A[m*8+6][n*8+7];
				x4 = A[m*8+7][n*8+4];
				x5 = A[m*8+7][n*8+5];
				x6 = A[m*8+7][n*8+6];
				x7 = A[m*8+7][n*8+7];
				
				for(i=m*8+2; i<m*8+6; i++){
					for(j=n*8+4; j<n*8+8; j++){
						B[j][i] = A[i][j];
					}
				}

				B[n*8+4][m*8+6] = temp;
				B[n*8+5][m*8+6] = x1;
				B[n*8+6][m*8+6] = x2;
				B[n*8+7][m*8+6] = x3;
				B[n*8+4][m*8+7] = x4;
				B[n*8+5][m*8+7] = x5;
				B[n*8+6][m*8+7] = x6;
				B[n*8+7][m*8+7] = x7;




			}
		}
	
	}

	else if(M==61 && N==67){
		
		for(m=0; m<6; m++){
			for(n=0; n<6; n++){
				
				
				for(i=16*m; i<16*m+16; i++){
					for(j=16*n; j<16*n+16; j++){
					
						if(i<67 && j<61)
							B[j][i] = A[i][j];
					
					}
				}

			}
		}	


	}



	else{
		for (i = 0; i < N; i++) {
        	for (j = 0; j < M; j++) {
            	temp = A[i][j];
            	B[j][i] = temp;
        	}
    	} 
	}



}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/* test for 32 by 32 */
char trans_test1_desc[] = "TEST1";
void trans_test1(int M, int N, int A[N][M], int B[M][N]){
	
/*	int temp;
	int i, j, m, n;
	int m_temp, n_temp;
	for(i=0; i<8; i++)
		temp = A[i][8];
	for(j=8; j<16; j++)
		temp = B[j][0];

	for(i=0; i<8; i++)
		for(j=8; j<16; j++)
			B[j][i] = A[i][j];

	for(m=0; m<4; m++){
		for(n=0; n<4; n++){
			
			m_temp = 8*m;
			n_temp = 8*n;

			for(i=m_temp; i<m_temp+8; i++)
				temp = A[i][n_temp];

			for(i=n_temp; i<n_temp+8; i++)
				temp = B[i][m_temp];

			for(i=m_temp; i<m_temp+8; i++)
				for(j=n_temp; j<n_temp+8; j++)
					B[j][i] = A[i][j];

		}
	}*/

	int m, n;
	int i, j;
//	int m_temp, n_temp;
//	int temp;
/*
		for(m=0; m<16; m++){
			for(n=0; n<16; n++){
			
				m_temp = 4*m;
				n_temp = 4*n;

				if(n==m){
					continue;

					for(i=0; i<4; i++){
						for(j=0; j<4; j++){
							B[m_temp+3-i][n_temp+3-j] = A[m_temp+i][n_temp+j];
						}
					}

					for(i=0; i<4; i++){
						for(j=0; j<4-i; j++){
							temp = B[m_temp+i][n_temp+j];
							B[m_temp+i][n_temp+j] = B[m_temp+3-j][n_temp+3-i];
							B[m_temp+3-j][n_temp+3-i] = temp;
						}
					}
					
					continue;

				}

				for(i=m_temp; i<m_temp+4; i++)
					for(j=n_temp; j<n_temp+4; j++)
						B[j][i] = A[i][j];

			}
		}


    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            temp = A[i][j];
            B[j][i] = temp;
        }
    }    
*/

	for(m=0; m<6; m++){
		for(n=0; n<6; n++){
/*
			if(n==m){
				for(i=0; i<8; i++){
					for(j=0; j<8; j++){
						B[8*m+7-i][8*n+7-j] = A[8*m+i][8*n+j];
					}
				}

				for(i=0; i<8; i++){
					for(j=0; j<8-i; j++){
						temp = B[8*m+i][8*n+j];
						B[8*m+i][8*n+j] = B[8*m+7-j][8*n+7-i];
						B[8*m+7-j][8*n+7-i] = temp;
					}
				}
					
				continue;

			}
*/
			for(i=16*m; i<16*m+16; i++){
				for(j=16*n; j<16*n+16; j++){
					
					if(i<67 && j<61)
						B[j][i] = A[i][j];
					
				}
			}

		}
	}





	
}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 
    
	
	registerTransFunction(trans_test1, trans_test1_desc); 
}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

