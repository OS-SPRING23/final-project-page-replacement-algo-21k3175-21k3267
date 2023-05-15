#include <stdio.h>
#include <stdlib.h>


/*Function prototypes*/
void initializer();
void display();
int pagehits(int);

/* Global variables*/
int length=0,nframes=0;
int refstrng[50];
int frames[50];
int pagehit=0;
int g=0,status=0,z=0;




/* Comparison Variables*/

int L_pagehit,L_pagefault;
int O_pagehit,O_pagefault;
int F_pagehit,F_pagefault;

/*FIFO ALGORITHM*/
void FIFO()
{
	system("cls");
	
	printf("\n\n \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	printf("\n\t\t\t\tWELCOME TO FIRST-IN-FIRST-OUT(FIFO)\n\n\n");
     
	pagehit=0;
	int count=0;
	initializer();	/*initialize the frame array with space*/
	for(int i=0; i<length; i++)
	{
		printf("%d) For %d => ",(i+1),refstrng[i]);
		g=pagehits(refstrng[i]); /*finding the pagehits or frame is empty*/
		if(g==0)
		{
			if(count==nframes)
			count=0;
			frames[count]=refstrng[i];
			count++;
			//printf("	MISS %d",g);
		}
		/*
		else if(g!=0)
		{
			printf("	hit %d",g);
		}*/
		if(status==1 && g==1)
		{	
		printf("	HIT->	");
			
		}
		else
		{
			printf("	MISS->	");
		}
		display(); //display the refstring
	}
	
	printf("\n\n \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	
	printf("\n\n ~Page Hits: %d",pagehit);
	printf("\n ~Page Faults: %d\n",length-pagehit);
	F_pagehit = pagehit;
	F_pagefault = length-pagehit;
	
	system("pause");

}

//LRU ALGORITHM
void LRU()
{
	system("cls");
	
	printf("\n\n \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	printf("\n\t\t\t\tWELCOME TO LEAST-RECENTLY-USED(LRU) \n\n\n");
    
	pagehit=0;
	int count=0;
	initializer();	//initialize the frame array with space
	for(int i=0; i<length; i++)
	{
		printf(" For %d => ",refstrng[i]);
		g=pagehits(refstrng[i]); //finding the pagehits or frame is empty
		if(g==0)
		{
			if(status==1) // it will update about the previous hit
			{
				if(z==count) //z is the index where hit occur previously
				{
					count++;
					if(count==nframes)
					count=0;
					frames[count]=refstrng[i];
				}
				else
				{
					frames[count]=refstrng[i];
				}
				z=0;
				status=0;
			}
			else
			{
				frames[count]=refstrng[i];
			}
			count++;
			if(count==nframes)
			count=0;
		}
		if(status==1 && g==1)
		{	
			printf("	HIT ->	");
			//printf("g=%d z=%d status=%d count=%d HIT ->	",g,z,status,count);	
		}
		else
		{
			printf("	MISS ->	");
			//printf("g=%d z=%d status=%d count=%d MISS ->	",g,z,status,count);
		}
		display(); //display the frames
	}
	
	printf("\n\n \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	
	printf("\n\n ~Page Hits: %d",pagehit);
	printf("\n ~Page Faults: %d\n",length-pagehit);
	L_pagehit = pagehit;
	L_pagefault = length-pagehit;
	
	system("pause");
}

//OPTIMAL ALGORITHM
void Optimal()
{
	int fc=0;
	system("cls");

    printf("\n\n \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	printf("\n\t\t\t\tWELCOME TO OPTIMAL PAGE REPLACEMENT \n\n\n");
    
	pagehit=0;
	int count=0;
	initializer(); //initialize the frame array with space
	for(int i=0; i<length; i++)
	{
		printf(" For %d => ",refstrng[i]);
		g=pagehits(refstrng[i]); //finding the pagehits or frame is empty 
		if(g==0)
		{
			int max=0,min=0,z=0,flag=0; //z stores location.
			for(int l=0;l<nframes;l++)
			{
				flag=0; // flag is used if there is no character in refstring 
				for(int k=i+1;k<length;k++)
				{
					
					if(frames[l]==refstrng[k])
					{
						flag=1;
						min=k;
						if(max<min)
						{
							max=min;
							z=l;
						}
						break;
					}
				}
				if(flag==0)
				{
					z=l;
					break;
				}
				fc=flag;

			}
			frames[z]=refstrng[i];
		}
		if(g==1&&status==1)
		{	
			printf("	HIT ->	");
			//printf("g=%d z=%d status=%d flag=%d count=%d HIT ->	",g,z,status,fc,count);
			
		}
		else
		{
			printf("	MISS ->	");
			//printf("g=%d z=%d status=%d flag=%d count=%d MISS->	",g,z,status,fc,count);
		}
		display(); //display the refstring
	}
	
	printf("\n\n \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	
	printf("\n\n ~Page Hits: %d",pagehit);
	printf("\n ~Page Faults: %d\n",length-pagehit);
	
	O_pagehit = pagehit;
	O_pagefault = length-pagehit;
	
	system("pause");

}

// COMPARE ALL 3 ABOVE ALGO RESULTS
void COMPARE()
{
	system("cls");
	
	printf("\n\n\t\t\t COMPARE THE RESULT OF ALL 3 ALGOS STATED ABOVE \n\n");
	
	printf("ENTERED REFERENCE STRING: ");
	for(int i=0 ; i<length ; i++)
	{
		printf("%d ",refstrng[i]);
	}
	
	int P_hit[3],P_fault[3];
	
	P_hit[0] = F_pagehit;
	P_hit[1] = O_pagehit;
	P_hit[2] = L_pagehit;
	
	P_fault[0] = F_pagefault;
	P_fault[1] = O_pagefault;
	P_fault[2] = L_pagefault;
	
	char *arr[3];
	arr[0]=" FIFO:";
	arr[1]=" OPTIMAL";
	arr[2]=" LRU: ";
	

	printf("\n\n\t\t~RESULT GIVEN BY FIRST-IN-FIRST-OUT(FIFO):");
	printf("\n\t\t PAGE-HITS: %d",F_pagehit);
	printf("\n\t\t PAGE-FAULTS: %d",F_pagefault);
	
	printf("\n\n\t\t~RESULT GIVEN BY OPTIMAL PAGE REPLACEMENT:");
	printf("\n\t\t PAGE-HITS: %d",O_pagehit);
	printf("\n\t\t PAGE-FAULTS: %d",O_pagefault);
	
	printf("\n\n\t\t~RESULT GIVEN BY LEAST-RECENTLY-USED(LRU):");
	printf("\n\t\t PAGE-HITS: %d",L_pagehit);
	printf("\n\t\t PAGE-FAULTS: %d",L_pagefault);
	
	printf("\n\n\n\t\t RESULT CONCLUDED:");
	
	printf("\n\n\t\t BASED ON PAGE-FAULTS:\n");
	printf("\n");
	if(L_pagefault < O_pagefault && L_pagefault < F_pagefault)
	{
		printf("\t~LEAST-RECENTLY-USED(LRU) ALGORITHM GIVES LESSER PAGE-FAULTS AS COMPARE TO OTHERS ALGORITHMS IN GIVEN REFERENCE STRING");
	}
	
	else if(O_pagefault < L_pagefault && O_pagefault < F_pagefault)
	{
		printf("\t~OPTIMAL PAGE REPLACEMENT ALGORITHM GIVES LESSER PAGE-FAULTS AS COMPARE TO OTHERS ALGORITHMS IN GIVEN REFERENCE STRING");
	}
	
	else
	{
		printf("\t~FIRST-IN-FIRST-OUT(FIFO) ALGORITHM GIVES LESSER PAGE-FAULTS AS COMPARE TO OTHERS ALGORITHMS IN GIVEN REFERENCE STRING");
	}
	printf("\n");
	for(int i=0 ; i < 3 ;i++)
	{
		printf(" %s \t\t\t",arr[i]);
		for (float j = 0; j < P_fault[i]; j += 0.2) // change the incrementor depending upoun the difference coming //
		{
			printf("\xB2");
		}
		printf("%d\n\n",P_fault[i]);
	}
 
	printf("\n\n\t\t BASED ON PAGE-HITS:\n");
	printf("\n");
	if(L_pagehit > O_pagehit && L_pagehit > F_pagehit)
	{
		printf("\t~LEAST-RECENTLY-USED(LRU) ALGORITHM GIVES LESSER PAGE-HITS AS COMPARE TO OTHERS ALGORITHMS IN GIVEN REFERENCE STRING");
	}
	
	else if(O_pagehit > L_pagehit && O_pagehit > F_pagehit)
	{
		printf("\t~OPTIMAL PAGE REPLACEMENT ALGORITHM GIVES LESSER PAGE-HITS AS COMPARE TO OTHERS ALGORITHMS IN GIVEN REFERENCE STRING");
	}
	
	else
	{
		printf("\t~FIRST-IN-FIRST-OUT(FIFO) ALGORITHM GIVES LESSER PAGE-HITS AS COMPARE TO OTHERS ALGORITHMS IN GIVEN REFERENCE STRING");
	}
	printf("\n");
	for(int i=0 ; i < 3 ;i++)
	{
		printf(" %s \t\t\t",arr[i]);
		for (float j = 0; j <= P_hit[i]; j += 0.2) // change the incrementor depending upoun the difference coming //
		{
			printf("\xB2");
		}
		printf(" %d\n\n",P_hit[(int)i]);
		//printf(" \n\n");
	}

	system("pause");

}

void showgraph()
{
	system("cls");
	int P_hit[3],P_fault[3];
	
	P_hit[0] = F_pagehit;
	P_hit[1] = O_pagehit;
	P_hit[2] = L_pagehit;
	
	P_fault[0] = F_pagefault;
	P_fault[1] = O_pagefault;
	P_fault[2] = L_pagefault;
	
	char *arr[3];
	arr[0]=" FIFO:";
	arr[1]=" OPTIMAL";
	arr[2]=" LRU: ";
	
	printf("\n\n\t\t BASED ON PAGE-FAULT:\n");
	
	printf("\n");
	for(int i=0 ; i < 3 ;i++)
	{
		printf(" %s \t\t\t",arr[i]);
		for (float j = 0; j < P_fault[i]; j += 0.2) // change the incrementor depending upoun the difference coming //
		{
			printf("\xB2");
		}
		printf("%d\n\n",P_fault[i]);
	}
	
	printf("\n\n\t\t BASED ON PAGE-HITS:\n");
	printf("\n");
	
	printf("\n");
	for(int i=0 ; i < 3 ;i++)
	{
		printf(" %s \t\t\t",arr[i]);
		for (float j = 0; j <= P_hit[i]; j += 0.2) // change the incrementor depending upoun the difference coming //
		{
			printf("\xB2");
		}
		printf(" %d\n\n",P_hit[(int)i]);
		//printf(" \n\n");
	}
	system("pause");
}



// REST OF FUNC. DEF //
int pagehits(int variable)
{
	for(int j=0; j<nframes; j++)
	{
		if(frames[j]==(char)32)
		{
			frames[j]=variable;		
			return 1;
		}
		else if(variable==frames[j])
		{
			status=1;
			z=j;
			pagehit++;			
			return 1;
		}
	}
	return 0;	
}

void initializer()
{
	for(int q=0 ; q < nframes ; q++)
	{
		frames[q]=(char)32;
	}
}


void display()
{
	for(int k=0;k<nframes;k++)
	{
		if(frames[k]==32)
		{
		   printf("  |%c| ",frames[k]);
	    }
	    
		else
		{
		   printf("  |%d| ",frames[k]);
        }
	}
	printf("\n");
}


void ENTER_DATA()
{
	system("cls");
	printf("\n\n\n\t\t\t\t\t       \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	printf("\n\n\t\t\t\t\t\t   ENTER DATA");
	printf("\n\t\t\t\t               \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n\n\n");
	
	printf("\n\t\t*ENTER THE NUMBER OF FRAMES: ");
	scanf("%d",&nframes);
	
	printf("\n\t\t*ENTER THE LENGTH OF REFERENCE STRING: ");
	scanf("%d",&length);
	
	printf("\n\n\t\t-----------------------------------------------------\n\n");
	
	for(int i=0 ; i < length ; i++)
	{
		printf("\t\tENTER %d ELEMNET OF REFERENCE STRING: ",i+1);
		scanf("%d",&refstrng[i]);
	}
	
	system("pause");

}

void Title_Page()
{
	system("cls");
	system("color f1");
	printf( "\n\n\n\t                       \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	printf( "\n\t                       \xB2\xB2                                 \xB2\xB2");
	printf( "\n\t                       \xB2\xB2     @@@@@@@@@@@@@@@@@@@@@@@     \xB2\xB2");
	printf( "\n\t                       \xB2\xB2     @                     @     \xB2\xB2");
	printf( "\n\t                       \xB2\xB2     @      WELCOME TO     @     \xB2\xB2");
	printf( "\n\t                       \xB2\xB2     @                     @     \xB2\xB2");
	printf( "\n\t                       \xB2\xB2     @         PAGE        @     \xB2\xB2");
	printf( "\n\t                       \xB2\xB2     @      REPLACEMNET    @     \xB2\xB2");
	printf( "\n\t                       \xB2\xB2     @       ALGORITHM     @     \xB2\xB2");
	printf( "\n\t                       \xB2\xB2     @         HUB         @     \xB2\xB2");
	printf( "\n\t                       \xB2\xB2     @                     @     \xB2\xB2");
	printf( "\n\t                       \xB2\xB2     @@@@@@@@@@@@@@@@@@@@@@@     \xB2\xB2");
	printf( "\n\t                       \xB2\xB2                                 \xB2\xB2");
	printf( "\n\t                       \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n\n");
	
	system("pause");
}





// PROGRAM MAIN 

int main()
{	
    int choice;
    Title_Page();
    while(1)
    {
    	f:
	    system("cls");
     	printf( "\n\n\n\n\t\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
        printf("\n\t\t\t\tWELCOME TO PAGE REPLACEMENT ALGORITHMS ");
     	printf( "\n\t\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		printf("\n\n\n\n\t\t\t\t  1.ENTER DATA\n\t\t\t\t  2.FIRST-IN-FIRST-OUT(FIFO)\n\t\t\t\t  3.OPTIMAL PAGE REPLACEMENT \n\t\t\t\t  4.LEAST-RECENTLY-USED(LRU) \n\t\t\t\t  5.COMPARE RESULTS OF ABOVE ALGOS \n\t\t\t\t  6.SHOW GRAPH  \n\t\t\t\t  7.EXIT");
		printf( "\n\n\n\t\t                \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		printf("\n\t\t\t\tENTER YOUR CHOICE: ");
        scanf("%d",&choice);
        switch(choice)
        {
		case 1:
		    ENTER_DATA();
		    break;
		case 2:
		    FIFO();
		    z=0;g=0;status=0;pagehit=0;
		    break;
		case 3:
		    Optimal();
		    z=0;g=0;status=0;pagehit=0;
			break;
		case 4:
		    LRU();
		    z=0;g=0;status=0;pagehit=0;
		    break;
		case 5:
		    COMPARE();
		    z=0;g=0;status=0;pagehit=0;
		   break;
		case 6:
		   showgraph();
		   break;
		case 7:
			return 0;
		   break;
		   
        }
    }
    
    return 0;
}
