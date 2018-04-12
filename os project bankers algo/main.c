#include<stdio.h>
int main()
{
    printf("\n\t\t\t\t************WELCOME TO BANKERS ALGORITHM****************");
    printf(("\n\t\t\t\t***********DEADLOCK DETECTION PROGRAM******************"));
    printf(("\n----------------------------------------------------------------------------------------------------------------"));
    printf("\n");

	int resource,proc,a,b,p_no;int process,counter = 0;int safsequence[20];
	printf("\nenter the numbers of processes here :");
	scanf("%d",&proc);
	printf("\nenter the number of resources here :");
	scanf("%d",&resource);
	int alloc[proc][resource],maxim[proc][resource],available[resource],need[proc][resource],reqst[resource];
	printf("\nenter the allocated resource instance to processes\n");

	//enter allocation
	for(int a=0;a<proc;a++)
	{
		printf("\nenter the allocation for P%d resource :",a);
		for(int b=0;b<resource;b++)
		{
			scanf("%d",&alloc[a][b]);
		}
	}

	//enter maxim numbers
	for(int a=0;a<proc;a++)
	{
		printf("\nenter the maxim instance to processes P%d\n",a);
		for(int b=0;b<resource;b++)
		{
			scanf("%d",&maxim[a][b]);
		}
	}

	printf("\nenter the availableable number of resource :");
	for(a=0;a<resource;a++)
	{
		scanf("%d",&available[a]);
	}
	//calculate need
	for(a=0;a<proc;a++)
	{
		for(b=0;b<resource;b++)
		{
			need[a][b]=maxim[a][b]-alloc[a][b];
		}
	}
	//display maxim and allocation
	printf("\nTHE ALLOCATION MATRIX\t THE maxim MATRIX \n");
	for(a=0;a<proc;a++)
	{
		for(b=0;b<resource;b++)
		{
			printf("%d  ",alloc[a][b]);
		}
		printf("\t\t\t");
		for(b=0;b<resource;b++)
		{
			printf("%d  ",maxim[a][b]);
		}
		printf("\n");

	}
	//display need
	printf("\n need matrix is \n");
	for(a=0;a<proc;a++)
	{
		for(b=0;b<resource;b++)
		{
			printf("%d  ",need[a][b]);
		}
		printf("\n");
	}
	while(1)
	{
		//enter reqst
		printf("\nname the process that request? ## enter from 0 to %d ## : ",proc-1);
		scanf("%d",&p_no);
		printf("\n Please Enter the request for process P%d : ",p_no);
		for(a=0;a<resource;a++)
			scanf("%d",&reqst[a]);

		//comparision for valid reqst
		int compArr[resource];
		for(a=0;a<resource;a++)
		{
			compArr[a]=0;
		}
		int sum = 0;
		for(a=0;a<resource;a++)
		{
			if(reqst[a]<=need[p_no][a] && reqst[a]<=available[a])
			{
				compArr[a]=1;
			}
		}
		for(a=0;a<resource;a++)
		{
			sum = sum+compArr[a];
		}
		//printf("%d",sum);
		if(sum == resource)
		{
			printf("YOU HAVE ENTERED A  valid reqst ");
			for(a=0;a<resource;a++)
			{
				available[a] -= reqst[a];
				need[p_no][a]  -= reqst[a];
				alloc[p_no][a] += reqst[a];

			}
			break;


		}
		else
		{
			printf("invalid entry of the reqst <<<<>>>>> Sorry please enter entries again");

		}


	}

	//display of new allocation and need
		printf("\nTHE ALLOCATION MATRIX IS \t THE NEED MATRIX IS \n");
	for(a=0;a<proc;a++)
	{
		for(b=0;b<resource;b++)
		{
			printf("%d  ",alloc[a][b]);
		}
		printf("\t\t\t");
		for(b=0;b<resource;b++)
		{
			printf("%d  ",need[a][b]);
		}
		printf("\n");

	}
	//display of new availableable list
	printf("\nthe available list is :");
	for(a=0;a<resource;a++)
	{
		printf("%d ",available[a]);
	}
	printf("\n");

	//following will cheack the occurence of the deadlock in the system
	int finish[resource];
	for(a=0;a<resource;a++)
		finish[a]=0;

	do
	{
		process = -1;

		for(a = 0;a<proc;a++)
		{
			if(finish[a]==0)
			{
				process = a;
				for(b=0;b<resource;b++)
				{
					if(available[b]<need[a][b])
					{
						process = -1;
						break;
					}
				}
			}
			if(process != -1)
				break;
		}
		if(process != -1)
		{
			printf("\n process P%d executed",process);
			safsequence[counter] = process + 1;
			counter++;
			for(a = 0;a<resource;a++)
			{
				available[a] += alloc[process][a];
				finish[process] = 1;
			}

		}

	}while(counter != proc && process != -1);

	if(counter == proc)
	{   // if the system is in safe state means all the process are executed
		printf("\n the system is in safe state");
		// below line will print the safe sequence
		printf("\n SAFE SEQUENCE IS : ");
		for(a=0;a<proc;a++)
		{
			printf("%d  ",safsequence[a]);
		}

	}
	else
	{
	    // unsafe state means the one or more process has been remains unexecuted
		printf("\n UNSAFE STATE HAS OCCURRED !!");
	}
}
