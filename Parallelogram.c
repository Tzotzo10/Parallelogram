#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
struct point{
	float x,y;
};

struct rectangle{
	struct point top_left, bottom_right;
	char color;
};

int intersection(struct rectangle *p1,struct rectangle *p2);
int max_area( int N, struct rectangle ptr[], char cl);
int max_perim( int N, struct rectangle ptr[], char cl);
int main()
{
	int i,ar,N,choice,c,k;
	struct rectangle *ptr,*p1,*p2;
	char line[256];
	FILE * fp;
	char colors,cl;
		do
	{
		N=fscanf(fp,"%s",&ar);
	}
	while (N!='\n');
	{
	if (fp=fopen("data.txt","r")==NULL);
	{
		printf("Trouble opening the file");
		exit(1);
	}
		ptr=(struct rectangle *)malloc(sizeof(N));
		if (ptr==NULL)
		{
			printf("Problem commiting the memory");
			exit(1);
		}
	}
for (i=0;i<N;i++)
{
	strcpy(ptr[i].color,fgets(line, 256, fp));
}
fclose(fp);
printf("Pick color\n");
scanf("%s", &cl);
printf("1.Intersection\n 2.Max Area\n 3.Max Perimeter\n");
scanf("%d", &choice);
while(cl!="STOP")
{
	if (c>=2)
	{
	switch(choice)
	{
		case 1 :
			intersection(&p1,&p2);
			printf("The coordinates of x and y: %rectangle %rectangle %rectangle %rectangle", &p1->top_left.x, &p1->bottom_right.x, &p1->top_left.y, &p1->bottom_right.y);
			break;
		case 2:
			k=max_area(N,ptr[N].color,choice);
			printf("Max area %d", k);
			break;
		case 3:
		printf("Max perimeter %d", max_perim(N,ptr[N].color,choice));
		break;
		default:
			printf("invalid input");
	}
	}
printf("Pick color\n");
scanf("%s", &cl);
printf("1.Intersection\n 2.Max Area\n 3.Max Perimeter\n");
scanf("%d", &choice);
}
free(ptr);
return 0;
}

int intersection(struct rectangle *p1, struct rectangle *p2)
{
	if(p1->top_left.x>p2->bottom_right.x || p1->bottom_right.x<p2->top_left.x || p1->top_left.y<p2->bottom_right.y || p1->bottom_right.y>p2->top_left.y)
	{
	p1->top_left.x=0;
	p1->bottom_right.x=0;
	p1->top_left.y=0;
	p1->bottom_right.y=0;
	return 0;
}
	else
	{
	if(p1->top_left.x<p2->top_left.x && p1->bottom_right.x>p2->bottom_right.x && p1->bottom_right.y<p2->bottom_right.y && p1->top_left.y>p2->top_left.y)
	{
	p1->top_left.x=p2->top_left.x;
	p1->top_left.y=p2->top_left.y;
	p1->bottom_right.x=p2->bottom_right.x;
	p1->bottom_right.y=p2->bottom_right.y;
}
if (p1->bottom_right.x>p2->top_left.x && p1->top_left.y>p2->top_left.y)
{
	p1->top_left.x=p2->top_left.x;
	p1->top_left.y=p2->top_left.y;
}
if(p1->top_left.x>p2->bottom_right.x && p1->top_left.y>p2->bottom_right.y)
{
	p1->top_left.x=p2->top_left.x;
	p2->bottom_right.y=p2->bottom_right.y;
}
if (p1->top_left.y<p2->bottom_right.y && p1->top_left.x<p2->bottom_right.x)
{
	p1->bottom_right.x=p2->bottom_right.x;
	p1->bottom_right.y=p2->bottom_right.y;
}
if (p1->bottom_right.x>p2->bottom_right.x && p1->top_left.y>p2->top_left.y)
{
	p1->top_left.y=p2->top_left.y;
	p1->bottom_right.x=p2->bottom_right.x;
}
return 1;
}
}

int max_area( int N, struct rectangle ptr[], char cl)
{
	int a,pos;
	struct rectangle max;
	for (a=0;a<N;a++)
	{
		if (a=0)
		{
			pos=0;
			max=ptr[0];
		}
		else if ((ptr[a].bottom_right.x - ptr[a].top_left.x) * (ptr[a].top_left.y - ptr[a].bottom_right.y)>max)
		{
			max=ptr[a];
			pos=a;
		}
	}
	return pos;
	}
	
	int max_perim(int N, struct rectangle ptr[], char cl)
	{
		int b,pos;
		struct rectangle max;
		for (b=0;b<N;b++)
		{
			if (b=0)
			{
				pos=0;
				max=ptr[0];
			}
			else if ((ptr[b].bottom_right.x - ptr[b].top_left.x) + (ptr[b].top_left.y - ptr[b].bottom_right.y)>max)
			{
				pos=b;
				max=ptr[b];
			}
		}
		return pos;
	}
