#define maxn 100000
#define maxl 3
#define bufsize (maxl+1) *maxn+2 \

/*1:*/
#line 14 "makedigraph.w"

#include <stdio.h> 
#include <stdlib.h> 
#include "gb_graph.h"
#include "gb_save.h"

char buf[bufsize+1];
char names[maxn][maxl+1];
char nbuf[maxl+1];
char filenamebuf[ID_FIELD_SIZE+8]= "/tmp/makegraph.gb";
int main(int argc,char*argv[]){
register int j,k,m,n,s;
register long d;
Graph*g;
Vertex*u,*v;
/*2:*/
#line 34 "makedigraph.w"

buf[bufsize]= '\n';
if(!fgets(buf,bufsize,stdin)){
fprintf(stderr,"Couldn't read the variable-name line!\n");
exit(-1);
}
for(n= k= 0;n<maxn;n++){
while(buf[k]==' ')k++;
if(buf[k]=='\n')break;
for(j= 0;buf[k]!=' '&&buf[k]!='\n'&&j<=maxl;j++,k++)names[n][j]= buf[k];
if(j> maxl){
fprintf(stderr,"Vertex name is too long! %s",buf-k-j);
exit(-2);
}
}
g= gb_new_graph(n);
for(k= 0;k<n;k++)
(g->vertices+k)->name= gb_save_string(names[k]);
hash_setup(g);
printf("I've created a graph with %d vertices...\n",n);

/*:2*/
#line 29 "makedigraph.w"
;
/*3:*/
#line 55 "makedigraph.w"

for(m= 0;;m++){
if(!fgets(buf,bufsize,stdin))break;
for(k= 0;buf[k]==' ';k++);
for(j= 0;buf[k]!=' '&&j<maxl;j++,k++)nbuf[j]= buf[k];
nbuf[j]= '\0';
u= hash_out(nbuf);
if(!u){
fprintf(stderr,"Unknown first vertex: %s",buf);
exit(-3);
}
for(;buf[k]==' ';k++);
for(j= 0;buf[k]!=' '&&j<maxl;j++,k++)nbuf[j]= buf[k];
nbuf[j]= '\0';
v= hash_out(nbuf);
if(!v){
fprintf(stderr,"Unknown second vertex: %s",buf);
exit(-4);
}
for(;buf[k]==' ';k++);
if(buf[k]=='-')s= -1,k++;else s= +1;
for(d= 0;buf[k]>='0'&&buf[k]<='9';k++)d= 10*d+buf[k]-'0';
gb_new_arc(u,v,s*d);
}
printf(" and %d arcs...\n",m);

/*:3*/
#line 30 "makedigraph.w"
;
/*4:*/
#line 81 "makedigraph.w"

if(argc> 1){
sprintf(g->id,"%.*s",ID_FIELD_SIZE-1,argv[1]);
sprintf(filenamebuf,"/tmp/%.*s.gb",ID_FIELD_SIZE-1,argv[1]);
}
save_graph(g,filenamebuf);
printf(" and file %s holds the result.\n",filenamebuf);

/*:4*/
#line 31 "makedigraph.w"
;
}

/*:1*/
