#include<stdio.h>
#include<time.h>

#define W//文字列の最大長さ
#define m//ハッシュ表のサイズ
struct cell
{
    int keyW[W+1];int next;int parent;int dist;//構造体cellの定義
}
int hash_val(char *a);
int chained_hash_search(int *A, struct cell *L, char *a);
int chained_hash_insert(int *A,struct cell *L,int x);
int allocate_object(struct cell *L, int *f);
int hash_length(int *A,struct cell *L,int num);
void enqueue(int a,int n);
int  dequeue(int n);
void BFS(int v0,int *color,int *p,int *d,int n);
int main(void){
    clock_t start_t,end_t;
    double utime;//時間測定に用いる変数
    int numbers[5];//入力された数値を代入する配列
    char fname[128];//読み込むファイルの頂点
    int i,j;//ループ制御変数
    FILE *fp;
    printf("input filename:");
    fgets(fname,sizeof(fname),stdin);
    fname[strlen(fname)-1]='\0';
    fflush(stdin);
    fp=fopen(fname,"r");
    for(i=0;i<5;i++){
        fscanf(fp,"%d",&numbers[i]);
    }
    //変数宣言
    start_t=clock();
    //主要処理


    end_t=clock();
    utime=(end_t-start_t)/CLOCKS_PER_SEC;
    printf("time=%lf\n",utime);
}
//以下，関数 hash val のコード
int hash_val(char *a) /* 文字列はポインタ渡し */
{
    int h, i;
    h = 0; i = 0;
    while (a[i] != '\0' && i < W){ /* 文字の整数コードの和を計算 */
        h = h + (int)a[i];
        i = i + 1;}

    h = h % m; /* m で割った余りを取る */
    return h;
}
int chained_hash_search(int *A, struct cell *L, char *a){//ハッシュ表,リスト,対象のword
    int x;
    x=A[hash_val(a)];
    while(x!=-1&&strcmp(a,L[x].key))//xが-1またはkeyとaが一致したらループを抜ける
        x=L[x].next;
    return x;
}
int chained_hash_insert(int *A,struct cell *L,int x){
    int h;
    h=hash_val(L[x].key);
    L[x].next=A[h];//はじめにinsertされた要素はnextが-1
    A[h]=x;
}
int allocate_object(struct cell *L, int *f){
    int x;
    if(*f==-1){
        printf("out of space\n");
        exit(0);
    }
    else{
        x=*f;
        *f=L[x].next;}
    return x;
}
int hash_length(int *A,struct cell *L,int num){
    int i,count,j;

    for(i=0;i<m;i++){
        count=0;
        j=A[i];
        if(A[i]==-1)
            printf("A[%d]: 0\n",i);
        else{count++;
            for(;;){
                j=L[j].next;
                if(j!=-1)count++;
                else break;
            }
            printf("A[%d]:%2d\n",i,count);
        }

    }
}


void chained_hash_delete(int *A,struct cell *L,char *a,int y){//xのアドレス渡したい
    int z=hash_val(a);
    z=A[z];
    if(!strcmp(L[z].key,a)){//aと一致する要素が先頭にあるとき
        z=-1;
    }
    else{
        while(strcmp(L[L[z].next].key,a)){
            if(z==-1){
                printf("error\n");
                exit(0);}
            z=L[z].next;
        }
    }

    if(z!=-1){
        L[z].next=L[y].next;}
    else{
        A[hash_val(a)]=L[y].next;}
}
void free_object(struct cell *L,int *f,int a){
    L[a].next=*f;
    *f=a;
}
//以下BFSの関数
void enqueue(int a,int n){
    Q[t++]=a;
    if(t==n)t=0;
    if(t==h){printf("overflow\n");
        exit(0);}

}
int  dequeue(int n){
    int a;
    if(h==t){
        printf("underflow\n");
        exit(0);}
    else {
        a=Q[h++];
        if(h==n)h=0;}
    return a;
}
void BFS(int v0,int *color,int *p,int *d,int n){

    int i,j,v;
    for(v=0;v<n;v++){
        if(v==v0)continue;
        color[v]=0;
        d[v]=inf;
        p[v]=-1;
    }
    enqueue(v0,n);
    color[v0]=1;
    d[v0]=0;
    p[v0]=-1;//初期化

    while(1){
        v=dequeue(n);
        for(i=v;i<n;i++){
            if(Adj[v][i]==1&&color[i]==0){
                enqueue(i,n);
                color[i]=1;d[i]=d[v]+1;p[i]=v;
            }
        }
        color[v]=2;
        if(h==t)break;//Qが空なら
    }
}

