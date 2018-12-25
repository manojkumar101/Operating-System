#include <stdio.h>
#include <pthread.h>

int MAT1[10][10];
int MAT2[10][10];
int MAT3[10][10];

int r1,c1,r2,c2;

void *thread_Multiply_Matrix(void *);

int main()
{
    pthread_t tid;    
    int i,j,k;
    
    printf("Enter Number of Rows For Matrix 1 :");
    scanf("%d",&r1);
    
    printf("Enter Number of Columns For Matrix 1 :");
    scanf("%d",&c1);
    
    for(i=0;i<r1;i++)
    {
        for(j=0;j<c1;j++)
        {
            scanf("%d",&MAT1[i][j]);
        }
    }
    
    printf("\n");
    
    printf("Enter Numer of Rows For Matrix 2 :");
    scanf("%d",&r2);
    
    printf("Enter Number of Columns For Matrix 2 :");
    scanf("%d",&c2);
    
    for(i=0;i<r2;i++)
    {
        for(j=0;j<c2;j++)
        {
            scanf("%d",&MAT2[i][j]);
        }
    }
    
    if(c1!=r2)
    {
        printf("Multipication not Possible !!!");
    }
    else
    {
       
        
        pthread_create(&tid,NULL,thread_Multiply_Matrix,NULL);
        
        for(i=0;i<r1;i=i+2)
        {
            for(j=0;j<c2;j++)
            {
                for(k=0;k<c1;k++)
                {
                    MAT3[i][j]+=MAT1[i][k] * MAT2[k][j];
                }
            }
        }
        
        pthread_join(tid,NULL);
    }
    
    printf("\n Matrix 1 \n");
    
    for(i=0;i<r1;i++)
    {
        for(j=0;j<c1;j++)
        {
            printf("%d \t",MAT1[i][j]);
        }
        printf("\n");
    }    
    
    printf("\n Matrix 2 \n");
    
    for(i=0;i<r2;i++)
    {
        for(j=0;j<c2;j++)
        {
            printf("%d \t",MAT2[i][j]);
        }
        printf("\n");
    }    
    
    printf("\n Multipication of Matrix ...\n");
    
    for(i=0;i<r1;i++)
    {
        for(j=0;j<c2;j++)
        {
            printf("%d \t",MAT3[i][j]);
        }
        printf("\n");
    }    
    return 0;
}

void *thread_Multiply_Matrix(void *para)
{
    int i,j,k;
    for(i=1;i<r1;i=i+2)
        {
            for(j=0;j<c2;j++)
            {
                for(k=0;k<c1;k++)
                {                    
                    MAT3[i][j]+=MAT1[i][k] * MAT2[k][j];
                }
            }
        }
        
    printf("thread finished ...");
    pthread_exit(NULL);
}
