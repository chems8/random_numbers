#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

typedef struct pow_variables_struct
{
	void *x;
	void *y;
	void *z;
};

typedef struct pow_variables_struct *pow_variables;

void* fois_deux(void *x)                                                                                                                                                
{                                                                                                                                                                       
        return (void *) ((int)x *2);                                                                                                                                    
}

void *poww(void *x, void *y, void *z)                                                                                                                                   
{                                                                                                                                                                       
        long *t0;                                                                                                                                                       
        long *t1;                                                                                                                                                       
        long tmp0 = ((*((long *)x))*(*((long *)z)));                                                                                                                    
        *t0 = tmp0;                                                                                                                                                     
        long tmp1 = (*((long *)y))-1;                                                                                                                                   
        t1 = &tmp1;                                                                                                                                                     
        if(*t1 == 0){                                                                                                                                                   
                return (void *)t0;                                                                                                                                      
        }                                                                                                                                                               
        return poww(x, t1, t0);                                                                                                                                         
}

void *pow1(pow_variables pow_vars)                                                                                                                                   
{                                 
	void *x; 
	x = pow_vars->x;
	void *y; 
	y = pow_vars->y;
	void *z; 
	z = pow_vars->z;                                                                                                                                      
        long *t0;                                                                                                                                                       
        long *t1;                                                                                                                                                       
        long tmp0 = ((*((long *)x))*(*((long *)z)));                                                                                                                    
        t0 = &tmp0;                                                                                                                                                     
        long tmp1 = (*((long *)y))-1;                                                                                                                                   
        t1 = &tmp1;                                                                                                                                                     
        if(*t1 == 0){                                                                                                                                                   
                return (void *)t0;                                                                                                                                      
        }
	pow_vars->y = (void *)&tmp1;
	pow_vars->z = (void *)&tmp0;                                                                                                                                                               
        return pow1(pow_vars);                                                                                                                                         
}

long int random_numbers(long int maximum)                                                                                                                               
{                                                                                                                                                                       
        pthread_t thread0;                                                                                                                                              
        pthread_t thread1;                                                                                                                                              
        long int  *thread_resultx = (long int *)malloc(sizeof(long int));                                                                                               
        long int  *thread_resulty = (long int *)malloc(sizeof(long int));  
        long int  *thread_resultz = (long int *)malloc(sizeof(long int));  
	pow_variables pow_vars = (pow_variables)malloc(sizeof(struct pow_variables_struct));
	*thread_resultx = 7;                                                                                     
        *thread_resulty = 100;
        *thread_resultz = 3;
	pow_vars->x = thread_resultx;
	pow_vars->y = thread_resulty;
	pow_vars->z = thread_resultz;
        long int result = 0;                                                                                                                                            
        int c = 100;                                                                                                                                                    
        int u = 1;                                                                                                                                                      
        int i = 0;                                                                                                                                                      
        while(i < 10)                                                                                                                                                  
        {                                                                                                                                                               
                pthread_create(&thread0, NULL, pow1, (void *)pow_vars);                                                                     
                pthread_create(&thread1, NULL, fois_deux, (void *)thread_resultx);                                                                                      
                pthread_join(thread0, (void *)thread_resultx);                                                                                                          
                pthread_join(thread1, (void *)thread_resulty);                                                                                                          
                *((long int *)thread_resultz) = (*(long int *)thread_resultx) * (*(long int *)thread_resulty);                                                          
                result = (*(long int *)thread_resultz);                                                                                                                 
		//random_numbers(maximum);                                                                                                                        
                i = i +1;
	}                                                                                                                                                               
        if (result < 0)                                                                                                                                                 
        {                                                                                                                                                               
                result = 0 - result;                                                                                                                
        }                                                                                                                                                               
        return result % maximum;                                                                                                                                        
}

int main()
{
	long int random_number = random_numbers(26);
	printf("%ld\n", random_number);
	return 0;
}
