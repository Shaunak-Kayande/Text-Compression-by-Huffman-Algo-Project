#include<string.h>
#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
        char ch;
        int freq;
        struct node *left;
        struct node *right;
}node;

node * heap[1000];
int heapSize=0;

void Insert(node * element)
{
        heapSize++;
        heap[heapSize] = element;
        int now = heapSize;
        while(heap[now/2] -> freq > element -> freq)
        {
                heap[now] = heap[now/2];
                now /= 2;
        }
        heap[now] = element;
}
node * DeleteMin()
{
        node * minElement,*lastElement;
        int child,now;
        minElement = heap[1];
        lastElement = heap[heapSize--];
        for(now = 1; now*2 <= heapSize ;now = child)
        {
             child = now*2;
                 if(child != heapSize && heap[child+1]->freq < heap[child] -> freq )
                {
                        child++;
                }
                if(lastElement -> freq > heap[child] -> freq)
                {
                        heap[now] = heap[child];
                }
                else
                {
                        break;
                }
        }
        heap[now] = lastElement;
        return minElement;
}
void print(node *temp,char *code)
{
        if(temp->left==NULL && temp->right==NULL)
        {
                printf("\t \t char %c frequency %d code %s\n",temp->ch,temp->freq,code);
                return;
        }
        int length = strlen(code);
        char leftcode[10],rightcode[10];
        strcpy(leftcode,code);
        strcpy(rightcode,code);
        leftcode[length] = '0';
        leftcode[length+1] = '\0';
        rightcode[length] = '1';
        rightcode[length+1] = '\0';
        print(temp->left,leftcode);
        print(temp->right,rightcode);
}

void main()
{
FILE *fptr;
 heap[0] = (node *)malloc(sizeof(node));
 heap[0]->freq = 0;

int i=0,freq1[26]={0} ,freq2[26]={0};
char filename[15];
char ch, str[2000];
str[0]='\0';

    printf("\n \n \t \t Welcome to HUFFMAN CODING \n \n");
    printf("\t \t Project by \n \t \t Shaunak Kayande \n \t \t Sahil Pandhade \n");
    printf("\n \t \t Enter Target File : \t");
    scanf("%s", filename);
    printf("\n");

    fptr = fopen(filename, "r");

    if (fptr == NULL)
    {
       printf("Cannot open file \n");
       exit(0);
    }

    while (ch != EOF)
    {
      ch = fgetc(fptr);
      str[i] = ch;
      i++;
    }

    fclose(fptr);

      for(i=0;str[i] != '\0';i++)
      {
        if(str[i]>='a' && str[i]<='z')
        {
          freq1[str[i]-'a']++;
        }
        else if (str[i]>='A' && str[i]<='Z')
        {
          freq2[str[i]-'A']++;
        }
      }
      for(i=0;i<26;i++)
      {
        node * temp = (node *) malloc(sizeof(node));
        if(freq2[i] != 0 )
        {
          temp -> ch = i+'A';
          temp -> freq = freq2[i];
          temp -> left = temp -> right = NULL;
          Insert(temp);
        }
      }
      for(i=0;i<26;i++)
      {
        node * temp = (node *) malloc(sizeof(node));
        if(freq1[i] != 0 )
        {
          temp -> ch = i+'a';
          temp -> freq = freq1[i];
          temp -> left = temp -> right = NULL;
          Insert(temp);
        }
      }
      while(heapSize!=1)
      {
        node * left = DeleteMin();
        node * right = DeleteMin();
        node * temp = (node *) malloc(sizeof(node));
        temp -> ch = 0;
        temp -> left = left;
        temp -> right = right;
        temp -> freq = left->freq + right -> freq;
        Insert(temp);
      }
      node *tree = DeleteMin();
      char code[30];
      code[0] = '\0';
      print(tree,code);

      printf("\n \t \t THANK YOU \n");

    }

