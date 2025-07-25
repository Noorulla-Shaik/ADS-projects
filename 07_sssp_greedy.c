//7.Compare the performance of Single Source Shortest Paths using Greedy 
#include<stdio.h> 
 
#include<conio.h> 
 
int main( ) 
 
{ 
 int v,i,j,min,current,nv,source,dest,y,x,T; 
 
 //nv- no. of vertices visited, T-total shortest distance of current node of previous paths 
 int mw=1000;                          //mw-maximum weight(infinity) 
 int visited[10],path[10],distance[10]; 
 int adj[10][10]; 
 clrscr(); 
 printf("Enter no. of vertices in the graph: "); 
 scanf("%d",&v); 
 printf("\nEnter Weight Matrix:\n"); //Ajacency Matrix 
 for(i=1;i<=v;i++) 
 { 
       for(j=1;j<=v;j++) 
 
          { 
                   scanf("%d",&adj[i][j]); 
         } 
  } 
 for(i=1;i<=v;i++) 
       { 
                  visited[i]=0; 
                  path[i]=0; 
                distance[i]=mw; 
        } 
 printf("\nEnter Source Vertex: "); 
 scanf("%d",&source); 
 current=source; 
 visited[current]=1; 
 nv=1; 
 
 T=0; 
 while(nv!=v) 
    { 
        for(i=1;i<=v;i++) 
        if(adj[current][i]!=0) 
         if(visited[i]!=1) 
        if(distance[i]>adj[current][i]+T) 
      { 
             distance[i]=adj[current][i]+T; 
             path[i]=current; 
       } 
      min=mw; 
      for(i=1;i<=v;i++) 
      if(visited[i]!=1) 
      if(distance[i]<min) 
           { 
            min=distance[i]; 
            current=i; 
           } 
            visited[current]=1; 
           nv=nv+1; 
     T=distance[current]; 
 } 
 
printf("Enter Destination Vertex: "); 
scanf("%d",&dest); 
 for(dest=1; dest<v; dest++) 
     { 
      if(dest!=source) 
 
        { 
 
   printf("\n\nShortest distance from %d to %d is %d", source, dest, distance[dest]); 
 
   printf("\nShortest path is as follows: "); 
 
   y=dest; 
   do 
   { 
          x=path[y]; 
          printf("\nVertex %d is connected to %d",y,x); 
            y=x; 
      } 
        while(y!=source); 
       } 
  } 
   getch( ); 
   return 0; 
} 