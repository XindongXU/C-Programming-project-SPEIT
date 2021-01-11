#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct pokemon {
	int id;
	char *name;
	float height;
	char *type;
	char *type2;
};
//struct pokemon existepas = {0, '0', 0, '0', '0'};
struct pokemon pkdb[1000];
int maxsize = sizeof(pkdb)/sizeof(struct pokemon);
int maxleng = 50;

void init_pkdb(){
	int i;
	for (i = 0; i < maxsize; i++){
		pkdb[i].id = 0;
		pkdb[i].height = 0;
		pkdb[i].name = (char*)malloc(sizeof(char)*maxleng);
		pkdb[i].type = (char*)malloc(sizeof(char)*maxleng);
		pkdb[i].type2 = (char*)malloc(sizeof(char)*maxleng);
		memset(pkdb[i].name,'\0',sizeof(char)*maxleng);
		memset(pkdb[i].type,'\0',sizeof(char)*maxleng);
		memset(pkdb[i].type2,'\0',sizeof(char)*maxleng);
	}
}

int insert(int id_temp, char* name_temp, float height_temp, char* type_temp){
	int res = 0;
	if(id_temp >= maxsize){
		res = 1;
	}
	char* tmp;
	const char s[2] = ",";
	
	pkdb[id_temp].id = id_temp;
	
	strcpy(pkdb[id_temp].name, name_temp);
	
	pkdb[id_temp].height = height_temp;
	
	tmp = strtok(type_temp, s);
    strcpy(pkdb[id_temp].type, tmp);
    tmp = strtok(NULL, s);
    if (tmp == NULL || strcmp(tmp, pkdb[id_temp].type) == 0) {
        strcpy(pkdb[id_temp].type2, "");
    }else{
    	strcpy(pkdb[id_temp].type2, tmp);
    }
    
	return res;
}

void display(int i){
	printf("%d\n%s\n%.2f\n%s", pkdb[i].id, pkdb[i].name, pkdb[i].height, pkdb[i].type);
    if (pkdb[i].type2[0] != 0){
       	printf(",%s\n", pkdb[i].type2);
    }else{
       	printf("\n");
    }
    printf("\n");
}

int delete_id(int id_temp){
	int res;
	int index;
	int j;
	for (index = 0; index < maxsize; index++){
		if(pkdb[index].id == id_temp){
			printf("%s ", pkdb[index].name);
			break;
		}
	}
	
	if(index == maxsize){
		res = 1;
		printf("Pokemon of id %d doesn¡¯t exist in the database.\n", id_temp);
	}else{
//		free(pkdb[index].name);
//		free(pkdb[index].type);
//		free(pkdb[index].type2);
//		pkdb[index].height = 0;
//		pkdb[index].id = 0;
//		
//        for (j = index + 1; j < maxsize; ++j) {
//            pkdb[j - 1] = pkdb[j];
//        }
//		pkdb[maxsize - 1].height = 0;
//		pkdb[maxsize - 1].id = 0;
//        pkdb[maxsize - 1].name = (char*)malloc(sizeof(char)*maxleng);
//		pkdb[maxsize - 1].type = (char*)malloc(sizeof(char)*maxleng);
//		pkdb[maxsize - 1].type2 = (char*)malloc(sizeof(char)*maxleng);
//		free(pkdb[index].name);
//		free(pkdb[index].type);
//		free(pkdb[index].type2);

		pkdb[index].height = 0;
		pkdb[index].id = 0;
		*(pkdb[index].name) = '\0';
		*(pkdb[index].type) = '\0';
		*(pkdb[index].type2) = '\0';

		printf("Deleted successfully!\n");
		res = 0;
	}
	return res;
}

void find_height(int param){
	int res;
	float max = 0;
	float min = 999;
	int index = 0;
	int id_max = 0;
	int id_min = 0;
	
	switch (param) {
        case 1:
            for (index = 0; index < maxsize; index ++){
				if (pkdb[index].height >= max){
					max = pkdb[index].height;
					id_max = index;
				}
			}
			for (index = 0; index < maxsize; index ++){
				if (0 <= (pkdb[index].height - pkdb[id_max].height) && (pkdb[index].height - pkdb[id_max].height) < 0.001){
					printf("%s ", pkdb[index].name);
				}
			}
			printf("\b");
			printf("\n");
            break;
        case 2:
            for (index = 0; index < maxsize; index ++){
				if (pkdb[index].height <= min && pkdb[index].height > 0.01){
					min = pkdb[index].height;
					id_min = index;
				}
			}
			for (index = 0; index < maxsize; index ++){
				if (0 <= (pkdb[index].height - pkdb[id_min].height) && (pkdb[index].height - pkdb[id_min].height) < 0.001){
					printf("%s ", pkdb[index].name);
				}
			}
			printf("\b");
			printf("\n");
            break;

        default:
            printf("Invalid Parameter\n");
    }
}

//void sort_id2(){
//	int i;
//	for (i = 500 - 1; i >= 0; i --){
//		if (pkdb[i].id != 0){
//			printf("%d\n%s\n", pkdb[i].id, pkdb[i].name);
//		}
//	}
//}

int ascending(int a, int b) {
 	return b < a; 
}
int descending(int a, int b) {
 	return b > a;
}
void swap(int i, int j) {
 	struct pokemon tmp = pkdb[i];
 	pkdb[i] = pkdb[j];
	pkdb[j] = tmp;
}


int partition(int left, int right, int(*compare1) (int, int),  int(*compare2) (int, int)){
	int i, j; 
 	struct pokemon pivo = pkdb[(left + right) / 2];
 	int pivo_id = pivo.id;
	i = left;
 	j = right;
	//while (1) {
		while ((*compare1)(pkdb[i].id, pivo_id)){
			i++; 
		} 
  		while ((*compare2)(pkdb[j].id, pivo_id)){
		    j--;
		}
		
 		if (i < j){
  			swap(i, j);
 		}else{
  			//break;
 		}
 	return i;
//	}
}

void pokemon_quicksort(int start, int end, int (*compare1) (int, int),  int (*compare2) (int, int)){
 	int i;
 	if (end > start) {
 		i = partition(start, end, compare1, compare2);
        pokemon_quicksort(start, i - 1, compare1, compare2);
        pokemon_quicksort(i + 1, end, compare1, compare2);
    }
}

void sort_id_plus(int param){
	switch (param){
		case 1:{
			pokemon_quicksort(0, maxsize - 1, descending, ascending);
			int i = 0;
			for (i = 0; i < maxsize; i++){
				if (pkdb[i].id != 0){
					printf("%s ", pkdb[i].name);
				}
			}
			printf("\b");
			break; 
		}
		case 2:{
			pokemon_quicksort(0, maxsize - 1, ascending, descending);
			int i = 0;
			for (i = 0; i < maxsize; i++){
				if (pkdb[i].id != 0){
					printf("%s ", pkdb[i].name);
				}
			}
			printf("\b");
			break;
		}
	}
	printf("\n");
}

void sort_id(){
	sort_id_plus(1);
}

void group(char* type){
	int index;
	for (index = 0; index < maxsize; index++){
		if(strcmp(pkdb[index].type, type)==0||strcmp(pkdb[index].type2, type)==0){
			printf("%s ", pkdb[index].name);
		}
	}
	printf("\b");
	printf("\n");
}

void free_design(char* name){
	int res = -5;
	int index;
	for (index = 0; index < maxsize; index++){
		if(MyStrCmp(pkdb[index].name, name)==0){
			res = index;
		}
}
	if(res != -5){
		printf("%s, with pokemon id%d, are pokemons in type of %s.\n", pkdb[res].name, pkdb[res].id, pkdb[res].type);
		if (strlen(pkdb[res].type2) != 0){
			printf("They also have attribute of %s.\n", pkdb[res].type2);
		} 
		if (strcmp(pkdb[res].type, "fire")==0 || strcmp(pkdb[res].type2, "fire")==0){
			printf("Their habitat is usually the desert or the area around the volcano.\n");
		}
		if (strcmp(pkdb[res].type, "water")==0 || strcmp(pkdb[res].type2, "water")==0){
			printf("Their habitat is usually the ocean or deep in the sea.\n");
		}
		if (strcmp(pkdb[res].type, "grass")==0 || strcmp(pkdb[res].type2, "grass")==0){
			printf("Their habitat is usually the jungle and the grassland.\n");
		}
		if (strcmp(pkdb[res].type, "rock")==0 || strcmp(pkdb[res].type2, "rock")==0){
			printf("Their habitat is usually the montain or the area around the mine.\n");
		}
		if (strcmp(pkdb[res].type, "bug")==0 || strcmp(pkdb[res].type2, "bug")==0){
			printf("Their habitat is usually the jungle or under the groud.\n");
		}
		printf("The average height of them is %.2f.\n", pkdb[res].height);
	}else {
		printf("%s, this pokemon is too rare to have been recorded in the database.", name);
	}
}

int MyStrCmp(char *pStr1,char *pStr2){
	int i=0;
	while(pStr1[i]!='\0'&& pStr2[i]!='\0'){
		if(pStr1[i]==pStr2[i]) i++;
		else if(pStr1[i]>pStr2[i]) { 
			if((pStr1[i]>='a' && pStr1[i]<='z') && (pStr2[i]>='A' && pStr2[i]<='Z') && (pStr1[i]-32)==pStr2[i]){
		    		i++;
				}
 
			else return 1;
		}
		else if(pStr1[i]<pStr2[i]){
			if((pStr1[i]>='A' && pStr1[i]<='Z') && (pStr2[i]>='a' && pStr2[i]<='z') && pStr1[i]==(pStr2[i]-32)){
					i++;
				}
			else 
				return -1;
		}
	}
	if(pStr1[i]=='\0' && pStr2[i]=='\0')
		return 0;
    else if(pStr1[i]=='\0'&& pStr2[i]!='\0')
		return -1;
	else if(pStr1[i]!='\0'&& pStr2[i]=='\0')
		return 1;
}

void endline(){
	int i;
	for (i = 0; i < maxsize; i++){
		free(pkdb[i].name);
		free(pkdb[i].type);
		free(pkdb[i].type2);
	}
}

int main(){
//	char type0[maxleng];
//	scanf("%s", type0);
//	printf("%s\n",type0);
//	char name0[maxleng];
//	scanf("%s", name0);
	init_pkdb();
	freopen("input_plus.txt","r",stdin);
//	freopen("input_plus.txt","r",stdin);
	int cnt;
	scanf("%d", &cnt);
	printf("%d\n", cnt);
	while (cnt){
//		char name[maxleng], type[maxleng], type2[maxleng];
		char *type = malloc(sizeof(char) * maxleng);
		char *name = malloc(sizeof(char) * maxleng);
		float height;
		int id;
		scanf("%d", &id);
		scanf("%s", name);
		scanf("%f", &height);
		scanf("%s", type);
		insert(id, name, height, type);
		//display(id);
		cnt--;
		free(type);
		free(name);
	}
//	delete_id(29);
//	int i = 0;
//	for (i = 0; i < maxsize; i++){
//		if (pkdb[i].id != 0){
//			display(i);
//		}
//	}
//	delete_id(40);
	find_height(1);
	find_height(2);
//	sort_id();
	sort_id_plus(1);
	sort_id_plus(2);
//	group("fire");
//	group("electric"); 
//	free_design(name0);
//	free_design(name0);
//	printf("%s\n", pkdb[87].name);

//
//	int i = 0;
//	int nbco = 0;
//	printf("Hello, this is a database of Pokemon, we can help you to realise several fonctions introduced below.\n");
//	printf("First of all, please enter the number of fonctions you would like to realise.\n");
//    scanf("%d", &nbco);
//    printf("Now please enter the enumeration of the fonction to realise : \n");
//    printf("1 represents insert a Pokemon to the database, its id, name, height, type should be given in order;\n");
//    printf("2 represents delete a Pokemon, its id should be given;\n");
//    printf("3 represents find Pokemons with maximal height or minimal height in the database, enter 3 1 to print the max, enter 3 2 to print min;\n");
//    printf("4 represents sorting the database with id-ascending order;\n");
//    printf("5 1 represents sorting the database with id-ascending order, 5 1 represents sorting the database with id-descending order;\n");
//    printf("6 represents printing the name of all the Pokemons belonging to the given type;\n");
//    printf("7 represents printing all the information of a given Pokemon, if it has been recorded in the database;\n");
//	printf("\n");
//    int idco = 0;
//    int pmco = 0;
//    for (i = 0; i < nbco; i++) {
//        scanf("%d", &idco);
//        int id_temp = 0;
//    	char *name_temp = malloc(sizeof(char) * maxleng);
//   		char *type_temp = malloc(sizeof(char) * maxleng);
//   		float height_temp = 0;
//        switch (idco) {
//            case 1:
//                scanf("%d", &id_temp);
//                scanf("%s", name_temp);
//                scanf("%f", &height_temp);
//                scanf("%s", type_temp);
//                insert(id_temp, name_temp, height_temp, type_temp);
//                break;
//            case 2: 
//                scanf("%d", &pmco);
//                delete_id(pmco);
//                break;
//            case 3:
//                scanf("%d", &pmco);
//                find_height(pmco);
//                break;
//            case 4:
//                sort_id_plus(1);
//                break;
//            case 5:
//                scanf("%d", &pmco);
//                sort_id_plus(pmco);
//                break;
//            case 6:
//                scanf("%s", type_temp);
//                group(type_temp);
//                break;
//            case 7:
//            	scanf("%s", name_temp);
//            	free_design(name_temp);
//        }
//        free(name_temp);
//        free(type_temp);
//    }
	
	endline();
	return 0;
}
