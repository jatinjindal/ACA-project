
#include<stdio.h>
int max(int n,char a[n][n],int call);
int min(int n,char a[n][n],int call);
//print the matrix
void print(int n,char a[n][n])
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			printf("%c ",a[i][j]);
			
		}
		printf("\n");
	}
}
int abs(int x)
{
	return x>0?x:-x;
}	

int check(int n,char a[n][n],int i,int j,char x)
{
	int count=1;	
	int k;	
	for(k=0;k<n;k++)
	{
		if(a[i][k]!=x)
		count=0;
	}
	if(count==1)
	return 1;
	count=1;

	for(k=0;k<n;k++)
	{
		if(a[k][j]!=x)
		count=0;
	}
	if(count==1)
	return 1;
	if(a[1][1]==x && a[0][0]==x && a[2][2]==x)
	return 1;

	if(a[0][2]==x && a[1][1]==x && a[2][0]==x)
	return 1;
	
	return 0;
}	

int min(int n,char a[n][n],int call)
{
	int value=20;
	int count=0;	
	int row,col;
	int flag=0;
	int y;
	for(int i=0;i<n;i++)
	{	
		for(int j=0;j<n;j++)
		{
			if(a[i][j]=='.')
			{
				if(flag==0)
				{
					flag=1;
					row=i,col=j;
				}				
				count++;
				a[i][j]='0';				
				y=check(n,a,i,j,'0');				
				if(y==1)
				{
					value= -100;
					row=i;
					col=j;
					a[i][j]='.';
					break;
				}
				else
				{
					int x=max(n,a,call+1);					
					if(value>x)
					{
						value=x;
						row=i;col=j;
					}
				}
				a[i][j]='.';			
			}
			if(value==-100)
			break;
		}
		if(value==-100)
		break;
	}
	//no move left
	if(call==1)
	{
		if(count==0)
		{
			return 0;
		}
		a[row][col]='0';
		printf("\n");	
		print(n,a);
		y=check(n,a,row,col,'0');
		if(y==1)
		return 1;
		return 2;

	}
	if(count==0)
	value=0;	
	return value;
}	

int max(int n,char a[n][n],int call)
{
	int value=-20;
	int row,col;
	int count=0;
	int flag=0;
	int y;
	for(int i=0;i<n;i++)
	{	
		for(int j=0;j<n;j++)
		{
							
			if(a[i][j]=='.')
			{
				if(flag==0)
				{
					flag=1;
					row=i,col=j;
				}				
							
				count++;				
				a[i][j]='X';		
				y=check(n,a,i,j,'X');		
				if(y==1)
				{
					value= 100;
					row=i;
					col=j;
					a[i][j]='.';
					break;
				}
				else
				{
					int x=min(n,a,call+1);					
					if(x>value)
					{
						value=x;
						row=i;col=j;
					}
				}
				a[i][j]='.';			
			}
			if(value==100)
			break;
		}
		if(value==100)
		break;
	}
	//no move left
	if(count==0)
	return 0;
	return value;
}	

int main()
{
	int n=3;
	char a[n][n];
	printf("Start the game by mentioning the desired row and col\n");
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)		
		{
			a[i][j]='.';
		}
	}	
	int row,col;
	scanf("%d %d",&row,&col);
	a[row][col]='X';
	
	//print the matrix	
	print(n,a);
	int y=check(n,a,row,col,'X');
	if(y==1)
	{
		printf("Player wins");
		return 0;
	}	
	while(1)
	{
		int x=min(n,a,1);
		if(x==1)
		{
			printf("\nComputer wins");
			return 0;
		}		
		else if(x==0)
		{
			printf("\nDraw\n");
			break;
		}
		printf("Choose the row and col\n");
		while(1)		
		{
			scanf("%d %d",&row,&col);
			if(a[row][col]=='.')
			break;
			printf("Invalid move\n");
		}
		a[row][col]='X';
		printf("\n");
		print(n,a);
		y=check(n,a,row,col,'X');
		//printf("\n%d\n",y);		
		if(y==1)
		{
			printf("\nPlayer wins");
			return 0;
		}	
	
		
	}	
	return 0;
}

