#include<stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10  
#define MINE_NUM 12 

//菜单函数 
void menu_1(){
	printf("*****************\n") ;
	printf("*****1.play******\n") ;
	printf("*****0.exit******\n") ;
	printf("*****************\n") ;
	printf("choose: "); 
	return;
} 

void menu_2(){
	printf("1.show\n") ;
	printf("2.sweep\n") ;
	printf("choose: "); 
} 

void display(char current[SIZE + 2][SIZE + 2]){
	int i = 0;
	int j = 0;
	printf("  ");
	for (int k = 1; k <= SIZE; k++) {
		printf("%-2d", k);
	}
	
	putchar('\n');
	
	for (i = 1; i <= SIZE; i++){
		printf("%-2d", i);
		for (j = 1; j <= SIZE; j++){
			printf("%c ",current[i][j]);
		}
		putchar('\n');
	}
}

void expand_blank(char current[SIZE + 2][SIZE + 2] ,int num[SIZE + 2][SIZE + 2],
                 int visited[SIZE + 2][SIZE + 2] , int* count, int x, int y){
    if (x < 1 || x > SIZE || y < 1 || y > SIZE) {
        return;
    }
    
    if (visited[x][y] || current[x][y] != '*') {
        return;
    }
    
    visited[x][y] = 1;
	int sur[] = {-1, 0, 1};
	if (num[x][y] > 0){
		current[x][y] = num[x][y] + '0';
		(*count)++;
		return;
	}
	
	
	current[x][y] = ' ';
	(*count)++; 
	
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			expand_blank(current, num, visited, count, x + sur[i], y + sur[j]);
		}
	}
	
	
}

void show_win(int num[SIZE + 2][SIZE + 2]){
	for (int i = 1; i <= SIZE; i++){
		for (int j = 1; j <= SIZE; j++){
			if (num[i][j] == -1){
				printf("%c ", '!');
			}
			else {
				printf("%c ", num[i][j] + '0');
			}
		}
		putchar('\n'); 
			
	}
	putchar('\n') ;
	return;
}

//游戏函数
void game(){
	char current[SIZE + 2][SIZE + 2] = { 0 };//当前盘面 
	char ans[SIZE + 2][SIZE + 2] = { 0 };//显示雷的位置的盘面 
	int num[SIZE + 2][SIZE + 2] = { 0 };//显示数字的盘面 
	int visited[SIZE + 2][SIZE + 2] = { 0 };
	int i = 0;
	int j = 0;
	int sur[] = {-1, 0, 1};
	for (i = 0; i < SIZE + 2; i++){
		for (j = 0; j < SIZE + 2; j++){
			ans[i][j] = '0';
			current[i][j] = '*';
			
			
		}	
	} 
	
	//随机生成12个雷 
	int count  = 0;
	do {
		while(1){
			i = rand()%SIZE+1;
			j = rand()%SIZE+1;
			if (ans[i][j] == '0'){
				ans[i][j] = '1';
				count++;
				break;
			}
			
		}
		
	}while(count < MINE_NUM);
	
	for (i = 0; i < SIZE + 2; i++){
		for (j = 0; j < SIZE + 2; j++){
			if (ans[i][j] == '1'){
				num[i][j] = -1;
			}
			else {
				//统计周围雷的个数
				int temp = 0;
				for (int k = 0; k < 3; k++){
					for (int t = 0; t < 3; t++){
						if (ans[i + sur[k]][j + sur[t]] == '1'){
							temp++;
						}
					}
				} 
				num[i][j] = temp;
			}
		}	
	} 
	 
	int win = 0; 
	int swep = 0; 
	int x = 0;
	int y = 0;
	int rec = 0;
	
	
	
	while(1){
		display(current);
	    if (win == SIZE * SIZE - MINE_NUM || swep == MINE_NUM){
	    	printf("you win!\n");
	    	show_win(num); 
	    	break;
		}
		menu_2();
		scanf("%d", &rec);
		if (rec == 1){
			printf("choose the coordinate: ");
			scanf("%d %d",&x,&y);
			
			if (x < 1 || x > SIZE || y < 1 || y > SIZE){
				printf("error input! please choose again!\n");
				continue;
			}
		
		    //选中雷了 
		    if (ans[x][y] == '1'){
			    printf("you lose!\n");
			    break;
		    }
		
		    else{
			    //计算选中的位置应该显示什么 
			    expand_blank(current ,num ,visited, &win, x ,y);
			
		    }
		}
		
		if (rec == 2){
			printf("choose the coordinate: ");
			scanf("%d %d",&x,&y);
			
			if (x < 1 || x > SIZE || y < 1 || y > SIZE){
				printf("error input! please choose again!\n");
				continue;
			}
			
			if (current[x][y] == '*'){
				current[x][y] = '#';
				if (ans[x][y] == '1'){
					swep++;
				}
			}
			else if (current[x][y] == '#'){
				current[x][y] = '*';
				if (ans[x][y] == '1'){
					win--;
				}
			}
		}
		
		
	}
}

int main(){
	srand(time(NULL));
	rand();
	int input = 0;
	

	do {
		menu_1();
		scanf("%d", &input);
		switch(input){
			case 0:{
				printf("game over\n");
				break;
			}
			case 1:{
				printf("game start\n");
				game(); 
				break;
			}
			default:{
				printf("error! input again!\n");
				break;
			}
		}
		
	} while(input);
	
}
