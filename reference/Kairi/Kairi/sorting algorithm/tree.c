#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 100000
#define tambah 50000
struct btreenode
{
    struct btreenode *leftchild;
    int data;
    struct btreenode *rightchild;
};

void insert(struct btreenode **sr, int num)
{
    if (*sr == NULL)
    {
        *sr = malloc (sizeof(struct btreenode));
        (*sr) -> leftchild = NULL;
        (*sr) -> data = num;
        (*sr) -> rightchild = NULL;
    }
    else
    {
        if((*s) -> leftchild == NULL){
            insert(&((*sr) -> leftchild), num);
        } else if ((*s) -> rightchild == NULL){
insert(&((*sr) -> rightchild), num);
        }
            insert(&((*sr) -> leftchild), num);
        else
            
    }
}
void inorder(struct btreenode *sr, FILE *fp2)
{
    if(sr != NULL)
    {
        inorder(sr -> leftchild, fp2);
        fprintf(fp2, "%d\n", sr -> data);
        inorder(sr -> rightchild, fp2);
    }
}
int main(int argc, char *argv[])
{
    FILE *fp1;
    FILE *fp2;
    int i;
    int number[N];
    struct btreenode *bt;
    bt = NULL;

    if(argc != 2){                         
        puts("Parameter Error");
        return 0;
    }

    if ((fp1 = fopen(argv[1], "r")) == NULL){
        puts("NO FILE WITH THAT NAME");
        return 0;
    }

    for(i = 0; i < N; i++){
        fscanf(fp1, "%d", &number[i]);
    }

    fclose(fp1);

    for (i = 0 ; i < N ; i++){
        insert (&bt, number[i]);
    }
  
    clock_t begin = clock();
    for (i = 0 ; i < tambah ; i++){
        insert (&bt, i);
    }
    fp2 = fopen("./output000.dat", "w");
    inorder(bt, fp2);
    fclose(fp2);
    clock_t end = clock();


    puts("Done!");
    printf("The elapsed time is %lf seconds \n", (double)(end - begin)/CLOCKS_PER_SEC);
    return 0;
}

