#include<stdio.h>
#include<stdlib.h>
void board(char a[6][7],int col,int move);
void original(char a[6][7],int col);
int evaluate(char a[6][7],int col,int move);

//prints the matrix
void print(char a[][7])
{	
	for(int i=0;i<6;i++)
	{
		for(int j=0;j<7;j++)
		{
			printf("%c ",a[i][j]);
		}
		printf("\n");	
	}
}

//gives the sorted list of empty col
int* emptycol(char a[6][7],int move)
{
	int* index=(int *)malloc(sizeof(int)*8);
	int k=0;
	int predict[7];
	for(int j=0;j<7;j++)
	{
		int flag=0;			
		//checks empty col		
		for(int i=0;i<6;i++)
		{
			if(a[i][j]=='.')
			{
				flag=1;
				break;
			}	
		}
		//empty col
		if(flag==1)
		{
			index[k]=j;
			board(a,j,move);		
			predict[k]=evaluate(a,j,move);
			original(a,j);
			int l=k;
			//sort the array with index			
			if(l>=1)
			{
				int x=predict[l];
				int y=index[l];
				while(l>=1 && predict[l]<predict[l-1])
				{
					predict[l]=predict[l-1];
					index[l]=index[l-1];
					l--;
				}
				predict[l]=x;
				index[l]=y;
			}

			k++;
		}
	}
	index[k]=-1;
	//pointer of the index of sorted predicted values	
	return index;
}
 
int func(char a[6][7],int g1,int g2,int move,int depth)
{
	//g2 denotes the value of parent node and g1 denots the value of grandfather node
	//move 1 denotes that the turn is of min and he turns with red
	// move -1 denotes that the turn if of max and he turns with yellow	
	int l,id;	
	if(depth==0)	
	{
		if(move==-1)
		l=-20000;
		else
		l= 20000;
	}	
	
	//check for depth 7	
	if(depth==7)
	{
		int flag=0;		
		for(int j=0;j<7;j++)
		{
			int x;
			flag=0;			
			//checks empty col		
			for(int i=0;i<6;i++)
			if(a[i][j]=='.')
			{
				flag=1;
				break;
			}
			//empty col
			if(flag==1)
			{
				board(a,j,move);				
				x=evaluate(a,j,move);
				original(a,j);
			}
			//alpha beta func
			if(g2==-1) //-1 value denotes it was empty
			{
				g2=x;
			}
			else
			{
				if(move==1)
				{
					if(x<g2)//turn of minima
					{
						g2=x;
						if(g1!=-1)
						{
							if(g2<=g1)
							 return -1; //no use
						}
					}
				}
				if(move==-1)
				{
					if(x>g2)//turn of maxima
					{
						g2=x;
						if(g1!=-1)
						{
							if(g2>=g1) return -1; //no use
						}
					}
				}
			}
		}
		
		//no move left
		if(flag==0)
		return 1;
		return g2;
	}
	
	//return value 1 denotes no move left and -1 donetes it terminates or g2 gives its value
	int *index=emptycol(a,move);
	int k=0;	
	while(index[k]!=-1)
	{
		board(a,index[k],move);	
		int q= evaluate(a,index[k],move);
		int z;			
		if((q>=7000 && q<=13000) || (q<=-7000 && q>=-13000))
			z=q;	
		else		
		{
			z=func(a,g2,-1,(-1)*move,depth+1);		
		}
		
		
		if(z==1)
			z=q;		
		if(z!=-1)//it terminates due to alpha beta
		{
			if(g2==-1)
			g2=z;
			else if(move==1)//min
			g2=g2<z?g2:z;
			else if(move==-1)
			g2=g2>z?g2:z;//maxs
		}		
		original(a,index[k]);
		if(g1!=-1)
		{
			if(move==1)//min
			{
				if(g2<=g1)
				{
					free(index);
					return -1;
				}
			}
			else//max
			{
				if(g2>=g1)
				{free(index);return -1;}
			}

		}
		
		if(depth==0)	
		{
			if(move==1)//min
			{
				if(g2<l)
				{	
					id=index[k];
					l=g2;
				}
			}
			else//max
			{
				if(g2>l)
				{
					id=index[k];
					l=g2;
				}
			}
		}
		k++;
	}
	free(index);
	if(depth==0)	
	{
		board(a,id,move);
		if(k==0)    //game draw--no move left
		return 0;		
		if(l>=7000)   //game y wins
		return 1;
		else if(l<=-7000)  //r wins
		return -1;	
		else
		return 2;  //to show that game continues
	}
	//no move possible	
	if(k==0)
	return -1;	
	//for depth between 1 to 6
	return g2;
}


//sets the board
void board(char a[6][7],int col,int move)
{
	char x;	
	if(move==1)
	x='r';
	else x='y';	
	for(int i=5;i>=0;i--)
	{
		if(a[i][col]=='.')
		{
			a[i][col]=x;return;	
		}
	}
}

//returns to original
void original(char a[6][7],int col)
{
	for(int i=0;i<6;i++)
	{
		if(a[i][col]!='.')
		{
			a[i][col]='.';
			return;
		}
	}
}

//finds the value for the position
int evaluate(char a[6][7],int col,int move)
{
	
	int value=2;	
	//check vertically

	for(int j=0;j<7;j++)
	{
		for(int i=0;i<6;i++)
		{
			if(a[i][j]!='.')
			{	
				char y=a[i][j];
				int count=0;
				while(i<=6 && a[i][j]==y)
				{
					count++;
					i++;
				}
				if(count>=4)
				{
					if(move==-1)//max
					return 10000;
					else  //min
					return -10000;
				}
				
 				else if(count==3)
				{
					if(y=='r' && move==-1)
					value=value-200;
					else if (y=='y' && move==1)
					value=value+200;
					else if(y=='y')
					value=value+50;
					else
					value=value-50;
				}
				else if(count==2)
				{
					if(move==1)
					{
						if(y=='r')
						value+=-10;
						else value+=20;						
					}
					else
					if(move==-1)
					{
						if(y=='r')
						value+=-20;
						else value+=10;
					}
				}
					
			}
		}
	}
	
	//check horizontally
	for(int i=5;i>=0;i--)	
	{
		for(int j=0;j<7;j++)
		{
			int count=0;	
			char y=a[i][j];
			while(j<7 && a[i][j]==y)
			{
				count++;j++;
			}
		
				if(count==4)
				{
					if(y=='r')
					return -10000;
					else if(y=='y') return 10000;
				}
				if(j==7)
				{
					break;
				}
				else
				{
					if(a[i][j]!='.')
					{
						j--;continue;
					}
					else
					{
						if(count==3)
						{
							if(y=='r')
							{
								if(move==1)
								value=value-200;
								else value=value-50;
							}
						}
						else if(y=='y')
						{
							if(move==-1)
							value=value+200;
							else value=value+50;
						}
						else
						continue;
					}
				}
			
		}
	}

	//check diagonally down
	int i;
	for(i=0;i<=5;i++)
	{
		if(a[i][col]!='.')
			break;
	}
	int count=1;
	int j=col;
	int row=i;
	char y;
	while((i>=1 && j>=1) && (a[i][j]==a[i-1][j-1]))
	{
		count++; i--; j--;
	}
	j=col;i=row;
	while((i<5 && j<6) && (a[i][j]==a[i+1][j+1]))
	{
		count++; i++; j++;
	}

	y=a[row][col];
	if(count>=4)
	{
		if(y=='r')
		{
			return -10000;
		}
		else if(y=='y')
		{
			return 10000;
		}
	}
	else if (count==3)
	{
		if(y=='r' && move==-1)
		value=value-200;
		else if (y=='y' && move==1)
		value=value+200;
		else if(y=='y')
		value=value+50;
		else
		value=value-50;
	}
	else if(count==2)
	{
		if(move==1)
		{
			if(y=='r')
				value+=-10;
			else value+=20;						
		}
		else
			if(move==-1)
			{
				if(y=='r')
					value+=-20;
				else value+=10;
					
			}
					
	}
	
	// check diagonally up
	
	i=row;	
	count=1;
	j=col;
	while((i>=1 && j<6) && (a[i][j]==a[i-1][j+1]))
	{
		count++;i--;j++;
	}
	j=col;i=row;
	while((i<5 && j>=1) && (a[i][j]==a[i+1][j-1]))
	{
		count++;i++;j--;
	}

	y=a[row][col];
	if(count>=4)
	{
		if(y=='r')
		return -10000;
		else if(y=='y') return 10000;
	}
	else if (count==3)
	{
		if(y=='r' && move==-1)
		value=value-200;
		else if (y=='y' && move==1)
		value=value+200;
		else if(y=='y')
		value=value+50;
		else
		value=value-50;
	}
	else if(count==2)
	{
		if(move==1)
		{
			if(y=='r')
				value+=-10;
			else value+=20;						
		}
		else
			if(move==-1)
			{
				if(y=='r')
					value+=-20;
				else value+=10;
					
			}
					
	}	
	
	return value;	
}




int main(void)
{
	char a[6][7];
	for(int i=0;i<6;i++)
	{
		for(int j=0;j<7;j++)
		{
			a[i][j]='.';
		}
	}
	int value=0;
	print(a);
	printf("start your move with y by mentioning the col between 0-6\n");
		
	while(1)
	{
		printf("Player Move:\n");		
		int col;
		scanf("%d",&col);
		board(a,col,-1);
		
		print(a);	
		printf("\n");	
		int q=evaluate(a,col,-1);
		if(q>7000)
		{ 
			printf("player wins");
			break;
		}
		int x=func(a,-1,-1,1,0);
				
		if(x==1)
		{
			printf("\n");			
			print(a);			
			printf("player wins\n");			
			break;
		}
		else if(x==-1)
		{
			print(a);			
			printf("computer wins\n");
			break;
		}
		else if(x==0)
		{
			print(a);			
			printf("draw\n");
			break;
		}
		print(a);
		
	}	
return 0;
}
