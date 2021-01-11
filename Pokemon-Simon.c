//
// Created by Dell on 2020/12/2.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pokemon{
    int id;
    char *name;
    float height;
    char *type1;
    char *type2;
};

struct pokemon *pkm[500];

//int maxsize = sizeof(pkm)/sizeof(struct pokemon);
int maxsize = 500;
int maxlength = 50;

void init_pkm()
{
    int i = 0;
    //printf("%d", maxlength);
    for (i = 0; i < maxsize; i++)
    {
        pkm[i] = (struct pokemon*)malloc(sizeof(struct pokemon));
        pkm[i]->id = 0;
        pkm[i]->height = 0;
        pkm[i]->name = (char *)malloc(sizeof(char)*maxlength);
        pkm[i]->type1 = (char *)malloc(sizeof(char)*maxlength);
        pkm[i]->type2 = (char *)malloc(sizeof(char)*maxlength);
        memset(pkm[i]->name, '\0',sizeof(char )*maxlength);
        memset(pkm[i]->type1, '\0',sizeof(char )*maxlength);
        memset(pkm[i]->type2, '\0',sizeof(char )*maxlength);
    }
    //printf("1\n");
}



int insert (int Id, char *Name, float Height, char *Type)
{
    int res = 0;
    if (Id > maxsize)
    {
        res = 1;
    }
    const char *s = ",";
    pkm[Id]->id = Id;
    strcpy(pkm[Id]->name, Name);
    pkm[Id]->height = Height;


    char *temp = strtok(Type, s);
    strcpy(pkm[Id]->type1,temp);
    temp = strtok(NULL,s);
    if (temp == NULL || strcmp(temp,pkm[Id]->type1) == 0)
    {
        strcpy(pkm[Id]->type2, " ");
    }else{
        strcpy(pkm[Id]->type2, temp);
    }
    return res;
}


void show(int i)
{
    printf("%d  %s  %.3f  %s",pkm[i]->id, pkm[i]->name, pkm[i]->height, pkm[i]->type1);
    if (pkm[i]->type2[0] != 0)
    {
        printf(",%s\n", pkm[i]->type2);
    } else{
        printf("\n");
    }
    printf("\n");
}


//int delete_id(int id)
//{
//    int res;
//    int id_input;
//    for ( id_input = 0; id_input < maxsize; ++id_input)
//    {
//        if (pkm[id_input]->id == id)
//        {
//            printf("%s", pkm[id_input]->name);
//            free(pkm[id_input]);
//            pkm[id_input] = NULL;
//            for (int i = id_input + 1; i < maxsize; ++i)
//            {
//                pkm[i-1] = pkm[i];
//            }
//
//            pkm[--maxsize] = NULL;
//            printf("%s\n", "The pokemon of given id has been deleted successfully!");
//
//            res = 0;
//            return res;
//        }
//    }
//
//    if (id_input >= maxsize)
//    {
//        res = 1;
//        printf("%s\n", "The pokemon of given id doesn't exist in the database!");
//    }
//}

//void find_height(int param)
//{
//    float max = pkm[0]->height;
//    float min = INT_MAX;
//    int id_max = 0;
//    int id_min = 0;
//
//    switch (param)
//    {
//        case 1:
//            for (int j = 0; j < maxsize; ++j)
//            {
//                if (pkm[j]->height >= max)
//                {
//                    id_max = j;
//                    max = pkm[j]->height;
//                }
//            }
//            for (int k = 0; k < maxsize; ++k)
//            {
//                if (0<=pkm[k]->height - pkm[id_max]->height && pkm[k]->height - pkm[id_max]->height<0.001)
//                {
//                    printf("%s ", pkm[k]->name);
//                }
//            }
//            printf("\n");
//            break;
//
//
//        case 2:
//            for (int j = 0; j < maxsize; ++j)
//            {
//                if (pkm[j]->height <= min && pkm[j]->height > 0.01)
//                {
//                    id_min = j;
//                    min = pkm[j]->height;
//                }
//            }
//            for (int k = 0; k < maxsize; ++k)
//            {
//                if ((-0.001 <= pkm[k]->height - pkm[id_min]->height) && (pkm[k]->height - pkm[id_min]->height < 0.001))
//                {
//                    printf("%s ", pkm[k]->name);
//                }
//            }
//            printf("\n");
//            break;
//    }
//
//
//}


int ascending(int a, int b)
{
    return b<a;
}
int descending(int a,int b)
{
    return b>a;
}

void swap(int i, int j)
{
    struct pokemon *temp = pkm[i];
    pkm[i] = pkm[j];
    pkm[j] = temp;
}

typedef int (*Comparator)(int a,int b);


int partition(int left, int right, Comparator comparator1, Comparator comparator2)
{
    int i,j;
    struct pokemon *pivo = pkm[(left+right)/2];
    int pivo_id = pivo->id;
    i = left;
    j = right;

    while (1)
    {
        while (comparator1(pkm[i]->id,pivo_id)) {i++;}
        while (comparator2(pkm[j]->id,pivo_id)) {j--;}
        if (i<j)
        {
            swap(i,j);
        } else{
            break;
        }
    	return i;
    }
    
}

void quick_sort(int start, int end, Comparator comparator1, Comparator comparator2)
{
    int i;
    if (start<end)
    {
        i = partition(start,end,comparator1,comparator2);
        quick_sort(start,i-1,comparator1,comparator2);
        quick_sort(i+1, end,comparator1,comparator2);
    }
}


void sort_id_plus(int param)
{
	int i = 0;
    switch (param)
    {
        case 1:
        {	
            quick_sort(0, maxsize-1,&descending, &ascending);
            for (i = 0; i < maxsize; ++i)
            {
                //printf("%s", pkm[i]->name);
                if (pkm[i]->id != 0){
                    printf("%s ", pkm[i]->name);
                }
            }
            printf("\n");
            break;
        }

        case 2:
        {
            quick_sort(0, maxsize-1, &ascending, &descending);
            
            for (i = 0; i < maxsize; ++i)
            {
                //printf("%s", pkm[i]->name);
                if (pkm[i]->id != 0){
                    printf("%s ", pkm[i]->name);
                }
            }
            printf("\n");
            break;
        }
    }
    printf("\n");
}

void sort_id()
{
    sort_id_plus(1);
}

void group(char *type)
{
    int i;
    for ( i = 0; i < maxsize; ++i)
    {
        if ((strcmp(pkm[i]->type1, type) == 0 || strcmp(pkm[i]->type2, type) == 0))
        {
            printf("%s\t", pkm[i]->name);
        }
    }
    printf("\n");
}


void free_space()
{
	int i = 0;
    for (i = 0; i < maxsize; ++i)
    {
            free(pkm[i]);
    }

    free(*pkm);
}


int main()
{
    init_pkm();
    int cnt;
    freopen("input.txt","r",stdin);
    scanf("%d\n", &cnt);
    printf("%d\n", cnt);

	int i = 0;
    for (i = 0; i < cnt; ++i)
    {
        int Id = 0;
        char *Name =malloc(sizeof(char )*maxlength);
        char *Type = malloc(sizeof(char )*maxlength);
        float Height = 0;

        scanf("%d", &Id);
        scanf("%s",Name);
        scanf("%f",&Height);
        scanf("%s", Type);

        //printf("%d\n", Id);
        insert(Id, Name, Height, Type);
        //show(Id);
    }

    sort_id_plus(1);
    //sort_id_plus(2);


    //group("fire");
    //group("poison");


}








