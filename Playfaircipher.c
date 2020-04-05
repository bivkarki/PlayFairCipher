#include <stdio.h>
#include <string.h>
#include <ctype.h>
//functions required
char *Improvise(char arr[]);
void GenerateCipherKeyTable(char arr[5][5],char key[]);
void RemoveDuplicates(char arr[]);
void PairPlainText(char arr[]);
void PairProcessing(char arr[]);
void InsertElementat(int position,char arr[],int size);
void Encryption(char encrypted_msg[],char table[][5],char arr[]);
void FindPositionInTable(char table[][5],char element,int *x,int *y);

int main()
{
 char PT[]="hello how are you"; //Plain Text
 char key[]="hello"; //Encryption Key
 char CT[]=""; //Cipher or Encrypted Text
 char cipher_key_table[5][5]; //Cipher Key Table
 printf("The Initial Message: %s",PT);
 printf("\nThe Initial Keyword: %s",key);
 Improvise(PT);
 Improvise(key);
 printf("\n\nThe Improvised Message: %s",PT);
 printf("\nThe Improvised Keyword: %s",key);
 GenerateCipherKeyTable(cipher_key_table,key);
 printf("\n\nThe Improvised Message before pairing: %s",PT);
 PairPlainText(PT);
 Encryption(CT,cipher_key_table,PT);
 printf("\n\nThe Encrypted Message is: %s",CT);
 return 0;	
 }

char *Improvise(char arr[])
{   int i, count = 0; 
    for (i = 0; i < strlen(arr); i++) 
        if (arr[i] != ' ') 
            arr[count++] = toupper(arr[i]); 
    arr[count] = '\0'; 
    return arr;
}

void GenerateCipherKeyTable(char ar[5][5],char key[])
{   int i,j,k,size;
    char alphabets[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    size=strlen(key) + strlen(alphabets);
    char elements[size];
    strcat(elements,key);
    strcat(elements,alphabets);
    /*for(i=0;i<size;i++)
    {   elements[i]=key[i];   }
    */
	RemoveDuplicates(elements);
    for(i=0;i<5;i++)
    {   for(j=0;j<5;j++)
        { k=i*5+j;
        ar[i][j]=elements[k]; }
    } 
    printf("\n\nThe Generated Cipher Key Table [I/J are one]:\n\n");
    for(i=0;i<5;i++)
    {
        for(j=0;j<5;j++)
        {   
         printf("\t%c",ar[i][j]);
        }
        printf("\n");
    } 
}

void RemoveDuplicates(char arr[])
{  int i,j,k,n;
    n=strlen(arr);
    //As we only use I/J so we change all J to I
    for(i = 0; i < n; i++)
    { if(arr[i]=='J')
         arr[i]='I';    }
    //for removing repeated keys
    for(i = 0; i < n; i++)
    {   for(j = i+1; j < n; )
        {    if(arr[j] == arr[i])
            {   for(k = j; k < n; k++)
                { arr[k] = arr[k+1]; }
                n--;
            }
            else
                j++;
        }
    }
    //arr[k+1]='\0';
}

void PairPlainText(char arr[])
{   
  PairProcessing(arr);
  int i,j,k;
  int rows=strlen(arr)/2;
  char pairs[rows][2];
  printf("\n\nThe Pairings of the Message is:\n");
  for(i=0;i<rows;i++)
  {
  	for(j=0;j<2;j++)
  	 { k=i*2+j;
	   printf("%c",arr[k]);
	   }
	   printf("   ");
  }
}
void PairProcessing(char arr[])
{
int i,len_msg=strlen(arr);
    //Message Processing
    for(i=0;i<len_msg;i+=2)
    {
      if(arr[i]==arr[i+1])
      {
       InsertElementat(i+1,arr,len_msg);
       len_msg++;
      }
    }
   if(len_msg%2!=0)
   {    InsertElementat(len_msg,arr,len_msg);
        len_msg++;
   }
}
void InsertElementat(int position,char arr[],int size)
{  int i;
    char temp[size+1];
    for(i=0;i<=size;i++)
        { 
        if(i<position)
            temp[i]=arr[i];
        if(i>position)
            temp[i]=arr[i-1];    
        if(i==position)
            temp[i]='X';
        }
     temp[i++]='\0';
    for(i=0;i<=strlen(temp);i++)
    {   arr[i]=temp[i]; 
	}

}
void Encryption(char encrypted_msg[],char table[][5],char arr[])
{   
	int r1,c1,r2,c2; //(r1,c1) and (r2,c2) position of elements of pairs of message 
	int i,j;
	int size=strlen(arr);
    printf("\n\nThe Encrypted Pairs of Message is:\n");
	for(i=0;i<strlen(arr);i+=2)
	{
		FindPositionInTable(table,arr[i],&r1,&c1); //position of 1st element
		FindPositionInTable(table,arr[i+1],&r2,&c2); //position of 2nd element 
		//printf("\n(%d,%d),",r1,c1);
		//printf("(%d,%d)",r2,c2);
		if (r1==r2)
		{   //printf("\nPair Elements are in Same Row");
			encrypted_msg[i]=table[r1][(c1+1)%5];
		    encrypted_msg[i+1]=table[r2][(c2+1)%5];	}
		else if (c1==c2)
		{	//printf("\nPair Elements are in Same Column");
			encrypted_msg[i]=table[(r1+1)%5][c1];
		    encrypted_msg[i+1]=table[(r2+1)%5][c2];	 }
		else 
		{	//printf("\nPair Elements are not in Same row and columns");
			encrypted_msg[i]=table[r1][c2];
		    encrypted_msg[i+1]=table[r2][c1];	}
	printf("%c%c   ",encrypted_msg[i],encrypted_msg[i+1]);  
	}
	encrypted_msg[i]='\0';
}
void FindPositionInTable(char table[][5],char element,int *x,int *y)
{
 int i,j;
 for(i=0;i<5;i++)
	{	for(j=0;j<5;j++)
		{
		  if (table[i][j]==element)
		  { 
	
		  	*x=i;
		  	*y=j;
		  }
		}
	}
}



    
