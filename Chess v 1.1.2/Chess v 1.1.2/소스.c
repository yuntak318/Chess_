//v 1.1.2   
//패치노트
//시간제한 60분 추가 및 시간에 대한 UI 추가
//퀸이 대각선으로 이동할 때 기물이 있는데도 움직일 수 있는 버그 수정
//goto 문을 없애는 등 소소한 알고리즘 변화



// V 1.1.2    2020.08.27 시작  2020.09.25 끝
//chess

/*


*/
# include <Stdio.h>
# include <Windows.h>
# include <conio.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <io.h>
# include <time.h>

# define UP    72
# define DOWN  80
# define RIGHT 75
# define LEFT  77
# define ENTER 13
# define c     99

int move_check(int it, int i, int j, int oldi, int oldj);
int move_choose(int i, int j);
int map_read();
int map_draw();
int choose_char();
int move_char(int i, int j);
int check(int it, int oldi, int oldj);
int check(int it, int oldi, int oldj);
void start_();
void gotoxy(int x, int y);
void setColor(unsigned short text, unsigned short back);
void setFontColor(int color);
void Time(int i);

//전역변수
int map[8][8] = { 0 , }, oldi, oldj, count = 1, Check = 0;
int Black_Time = 3600, White_Time = 3600;		//3600 =>  초단위  (60분)
int W_min = 60, W_sec = 0,B_min=60,B_sec=0;	//다른 곳에서도 출력할 수 있게 전역 변수
char mark[8] = { 'a','b','c','d','e','f','g','h' };
clock_t Start, End;
//전역변수

FILE* fp;

int main() {
	system("mode con cols=60 lines=15");
	start_();
	map_read();
	map_draw();
	choose_char();
	return 0;
}

int map_read() {			//map 읽기
	gotoxy(0, 0);
	fp = fopen("Chess.txt", "r");
	int i = 0, j = 0;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			fscanf(fp, "%d", &map[i][j]);
		}
	}

}
void Time(int i) {
	double time = 0;
	time=((End - Start)/ CLOCKS_PER_SEC);
	

	if (i == 0) {		//White
		White_Time -= time;
		W_min = White_Time / 60;
		W_sec = White_Time - W_min * 60;
	}
	if (i == 1) {		//Black
		Black_Time-=time;		//가진 초와 이번 턴의 초 뺌
		B_min = Black_Time / 60;
		B_sec = Black_Time - B_min * 60;
	}
	
		gotoxy(26, 5);
		printf("                               ");
		gotoxy(26, 5);
		printf("Time: %d분 %d초 \n", W_min, W_sec);		//시간 출력!

		gotoxy(26, 2);
		printf("                               ");
		gotoxy(26, 2);
		printf("Time: %d분 %d초 \n", B_min, B_sec);		//시간 출력!
}
int choose_char() {
	int x = 8, y = 4, dire=0,Time_check=0;
	gotoxy(0, 9);
	printf("                                                   ");
	gotoxy(0, 9);
	if (count % 2 == 1)
		printf("(백색 차례)움직일 기물을 선택하세요...");
	if (count % 2 == 0)
		printf("(흑색 차례)움직일 기물을 선택하세요...");
	gotoxy(8, 4);		//가운데서 시작
	while (1) {
		if (Time_check == 0) {
			Start = clock();	//시간 시작!
			Time_check = 1;		//start가 반복적으로 초기화 되어 0이 되는 것을 방지
		}
	dire = getch();		
	
		if (dire == ENTER && map[y][x / 2] != 0) {

			if (map[y][x / 2] < 10 && count % 2 == 0) {			//Black
				move_char(y, x / 2);
				End = clock();						//시간 종료!
				Time(1);					//Black은 1
			}
			else if (map[y][x / 2] >= 10 && count % 2 == 1) {		//White
				move_char(y, x / 2);
				End = clock();
				Time(0);					//White면 0
			}
			else {
				if (count % 2 == 1) {
					gotoxy(0, 9);
					printf("                                                                                        ");
					gotoxy(0, 9);
					printf("흰색 차례 입니다!! 흰색기물만 움직일 수 있습니다....");
					Sleep(1000);
					gotoxy(0, 9);
				}
				if (count % 2 == 0) {
					gotoxy(0, 9);
					printf("                                                                                       ");
					gotoxy(0, 9);
					printf("흑색 차례 입니다!! 흑색기물만 움직일 수 있습니다....");
					Sleep(1000);
					gotoxy(0, 9);
				}

			}
			Time_check = 0;	//다시 시간 재기
			gotoxy(0, 9);
			printf("                                                                               ");
			gotoxy(0, 9);
			if (count % 2 == 1)
				printf("(흰색 차례)움직일 기물을 선택하세요...");
			if (count % 2 == 0)
				printf("(흑색 차례)움직일 기물을 선택하세요...");
			x = 8, y = 4;
			gotoxy(x, y);
		}

		switch (dire) {
		case UP:
			if (y - 1 < 0) {
				break;
			}
			y = y - 1;
			gotoxy(x, y);
			break;

		case DOWN:
			if (y + 1 > 7) {
				break;
			}
			y = y + 1;
			gotoxy(x, y);
			break;

		case RIGHT:
			if (x - 2 < 0) {
				break;
			}
			x = x - 2;
			gotoxy(x, y);
			break;

		case LEFT:
			if (x + 2 > 15) {
				break;
			}
			x = x + 2;
			gotoxy(x, y);
			break;


		}			//switch 문
	}				//while 문	
}					//choose_char 함수	


/*int move_char(int x, int y) {				j==x/2  i==y i j 아니고 j i     -> map[i][j] -> map[y][x/2]

}*/
int move_char(int i, int j) {
	int oldi_, oldj_;
	move_choose(i, j);

	system("cls");
	map_draw();
	count++;
	Check = 0;
}
int move_check(int it, int i, int j, int oldi, int oldj) {
	int n, n_2;
	//if (count % 2 == 0) {				/지우면 안됨!!
	switch (it) {
	case 1:											//PAWN_흑색


		if (oldi + 2 == i && oldj == j && oldi == 1) {		//두칸 앞으로 갈 때
			if (map[i][j] == 0 && map[i - 1][j] == 0) {
				return 0;
			}
		}

		if (oldi + 1 == i) {


			if (map[i][j] == 0 && oldj == j) {								//한칸 앞으로 갈 때
				if (i == 7) {
					map[oldi][oldj] = 5;		//폰의 승격   __퀸으로
					gotoxy(0, 9);
					printf("                                                                               ");
					gotoxy(0, 9);
					printf("Pawn이 Queen으로 승격하였습니다!");
					Sleep(1000);
				}
				return 0;
			}

			if (oldj - 1 == j || oldj + 1 == j) {	//대각선으로
				if (map[i][j] >= 10) {									//하얀색기물은 10보다 큼
					if (i == 7) {
						map[oldi][oldj] = 5;		//폰의 승격   __퀸으로
						gotoxy(0, 9);
						printf("                                                                               ");
						gotoxy(0, 9);
						printf("Pawn이 Queen으로 승격하였습니다!");
						Sleep(1000);
					}
					return 0;
				}
			}


		}
		return 1;
		break;
		//===========================================================================
	case 20:									//ROOK
	case 2:										//ROOK
		if (map[oldi][oldj] >= 10) {					//흰색이면,
			if (map[i][j] >= 10) {
				return 1;
			}
		}
		if (map[oldi][oldj] < 10) {							//흑색이면,
			if (map[i][j] != 0 && map[i][j] < 10) {
				return 1;
			}
		}
		if (oldi > i&& oldj == j) {				//위쪽으로 움직일 때
			for (n = i + 1; n < oldi; n++) {
				if (map[n][j] != 0) {
					return 1;
				}
			}
			return 0;
		}

		if (oldi < i&& oldj == j) {					//아래쪽으로 움직일 때
			for (n = i - 1; n > oldi; n--) {
				if (map[n][j] != 0) {
					return 1;
				}
			}
			return 0;
		}

		if (oldi == i && oldj > j) {				//왼쪽으로 움직일 때
			for (n = j + 1; n < oldj; n++) {
				if (map[i][n] != 0) {
					return 1;
				}
			}
			return 0;
		}

		if (oldi == i && oldj < j) {				//오른쪽으로 움직일 때
			for (n = j - 1; n > oldj; n--) {
				if (map[i][n] != 0) {
					return 1;
				}
			}
			return 0;
		}
		return 1;
		break;
		//=============================================================================
	case 30:															//KNIGHT
	case 3:																//KNIGHT
		if (map[oldi][oldj] >= 10) {					//흰색이면,
			if (map[i][j] >= 10) {
				return 1;
			}
		}
		if (map[oldi][oldj] < 10) {							//흑색이면,
			if (map[i][j] != 0 && map[i][j] < 10) {
				return 1;
			}
		}
		if (i == oldi - 2 || i == oldi + 2) {				//위로 두칸 오른쪽, 왼쪽
			if (oldj - 1 == j || oldj + 1 == j) {
				return 0;
			}
		}
		if (j == oldj - 2 || j == oldj + 2) {				//옆으로 두칸 위쪽, 아래쪽
			if (oldi - 1 == i || oldi + 1 == i) {
				return 0;
			}
		}

		return 1;
		break;
		//======================================================================
	case 40:															//BISHOP
	case 4:																//BISHOP
		if (map[oldi][oldj] >= 10) {					//흰색이면,
			if (map[i][j] >= 10) {
				return 1;
			}
		}
		if (map[oldi][oldj] < 10) {							//흑색이면,
			if (map[i][j] != 0 && map[i][j] < 10) {
				return 1;
			}
		}
		if (oldi - i == oldj - j) {
			if (oldi - i > 0) {					//왼쪽위 대각선,
				for (n = oldi - 1, n_2 = oldj - 1; n > i; n--, n_2--) {
					if (map[n][n_2] != 0) {
						return 1;
					}
				}
			}
			if (oldi - i < 0) {					//오른쪽아래 대각선,
				for (n = oldi + 1, n_2 = oldj + 1; n < i; n++, n_2++) {
					if (map[n][n_2] != 0) {
						return 1;
					}
				}
			}
			return 0;
		}
		if ((oldi - i) * (oldi - i) == (oldj - j) * (oldj - j)) {
			if (oldi - i > 0) {					//오른쪽위 대각선,
				for (n = oldi - 1, n_2 = oldj + 1; n > i; n--, n_2++) {
					if (map[n][n_2] != 0) {
						return 1;
					}
				}
			}
			if (oldi - i < 0) {					//왼쪽아래 대각선,
				for (n = oldi + 1, n_2 = oldj - 1; n > i; n++, n_2--) {
					if (map[n][n_2] != 0) {
						return 1;
					}
				}
			}
			return 0;
		}

		return 1;
		break;
		//==================================================================================
	case 50:																//QUEEN
	case 5:																	//QUEEN
		if (map[oldi][oldj] >= 10) {					//흰색이면,
			if (map[i][j] >= 10) {
				return 1;
			}
		}
		if (map[oldi][oldj] < 10) {							//흑색이면,
			if (map[i][j] != 0 && map[i][j] < 10) {
				return 1;
			}
		}
		if (oldi > i&& oldj == j) {				//위쪽으로 움직일 때
			for (n = i + 1; n < oldi; n++) {
				if (map[n][j] != 0) {
					return 1;
				}
			}
			return 0;
		}

		if (oldi < i&& oldj == j) {					//아래쪽으로 움직일 때
			for (n = i - 1; n > oldi; n--) {
				if (map[n][j] != 0) {
					return 1;
				}
			}
			return 0;
		}

		if (oldi == i && oldj > j) {				//왼쪽으로 움직일 때
			for (n = j + 1; n < oldj; n++) {
				if (map[i][n] != 0) {
					return 1;
				}
			}
			return 0;
		}

		if (oldi == i && oldj < j) {				//오른쪽으로 움직일 때
			for (n = j - 1; n > oldj; n--) {
				if (map[i][n] != 0) {
					return 1;
				}
			}
			return 0;
		}
		//=======  대각선
		if (oldi - i == oldj - j) {
			if (oldi - i > 0) {					//왼쪽위 대각선,
				for (n = oldi - 1, n_2 = oldj - 1; n > i; n--, n_2--) {
					if (map[n][n_2] != 0) {
						return 1;
					}
				}
			}
			if (oldi - i < 0) {					//오른쪽아래 대각선,
				for (n = oldi + 1, n_2 = oldj + 1; n < i; n++, n_2++) {
					if (map[n][n_2] != 0) {
						return 1;
					}
				}
			}
			return 0;
		}
		if ((oldi - i) * (oldi - i) == (oldj - j) * (oldj - j)) {
			if (oldi - i > 0) {					//오른쪽위 대각선,
				for (n = oldi - 1, n_2 = oldj + 1; n > i; n--, n_2++) {
					if (map[n][n_2] != 0) {
						return 1;
					}
				}
			}
			if (oldi - i < 0) {					//왼쪽아래 대각선,
				for (n = oldi + 1, n_2 = oldj - 1; n < i; n++, n_2--) {
					if (map[n][n_2] != 0) {
						return 1;
					}
				}
			}	//비숍 왼쪽 아래 if문
			return 0;
		}		//비숍 오른쪽위 왼쪽아래 if문
		return 1;

		break;
		//================================================================================
	case 60:															//KING
	case 6:																//KING
		if (map[oldi][oldj] >= 10) {					//흰색이면,
			if (map[i][j] >= 10) {
				return 1;
			}
		}
		if (map[oldi][oldj] < 10) {							//흑색이면,
			if (map[i][j] != 0 && map[i][j] < 10) {
				return 1;
			}
		}
		if (oldi + 1 == i || oldi - 1 == i) {				//한칸 앞,뒤로 갈 때
			if (oldj == j) {
				return 0;
			}
		}
		if (oldj + 1 == i || oldj - 1) {			//한칸 옆로 갈 때
			if (oldi == i) {
				return 0;
			}
		}
		if (oldi + 1 == i || oldi - 1 == i) {		//대각선으로 갈 때
			if (oldj - 1 == j || oldj + 1 == j) {
				return 0;
			}
		}

		return 1;
		break;
		//==================================================================================
	case 10:														//PAWN_흰색


		if (oldi - 2 == i && oldj == j && oldi == 6) {		//두칸 앞으로 갈 때
			if (map[i][j] == 0 && map[i + 1][j] == 0) {
				return 0;
			}
		}
		if (oldi - 1 == i) {

			if (oldj == j && map[i][j] == 0) {			//한칸 앞으로 갈 때
				if (i == 0) {
					map[oldi][oldj] = 50;		//폰의 승격   __퀸으로
					gotoxy(0, 9);
					printf("                                                                               ");
					gotoxy(0, 9);
					printf("Pawn이 Queen으로 승격하였습니다!");
					Sleep(1000);
				}
				return 0;
			}

			if (oldj - 1 == j || oldj + 1 == j) {	//대각선으로 갈 때
				if (map[i][j] < 10 && map[i][j] != 0) {									//검은색기물은 10보다 작음
					if (i == 0) {
						map[oldi][oldj] = 50;		//폰의 승격   __퀸으로
						gotoxy(0, 9);
						printf("                                                                               ");
						gotoxy(0, 9);
						printf("Pawn이 Queen으로 승격하였습니다!");
						Sleep(1000);
					}
					return 0;
				}
			}

		}


		return 1;




		break;

	}				//switch_1문

//	}			//if
	/*if (count % 2 == 1) {				중요!!! 절대 지우면 안됨!
		switch (it) {
		}
		}*/
}
int move_choose(int  i, int j) {
	int x = 0, y = 0, dire;
	char chess[10];

	if (map[i][j] == 1 || map[i][j] == 10)
		strcpy(chess, "Pawn");

	if (map[i][j] == 2 || map[i][j] == 20)
		strcpy(chess, "Rook");

	if (map[i][j] == 3 || map[i][j] == 30)
		strcpy(chess, "Knight");

	if (map[i][j] == 4 || map[i][j] == 40)
		strcpy(chess, "Bishop");

	if (map[i][j] == 5 || map[i][j] == 50)
		strcpy(chess, "Queen");

	if (map[i][j] == 6 || map[i][j] == 60)
		strcpy(chess, "King");

a:
	gotoxy(0, 9);
	printf("                                                                               ");
	gotoxy(0, 9);
	printf("%c%d에 있는 %s 을(를) 옮기실 곳을 선택하세요...", mark[j], abs(i - 8), chess);	//abs는 절댓값
	gotoxy(j * 2, i);			
	x = j * 2; y = i;
	while (1) {
		dire = getch();
		if (dire == c) {
			count--;
			
			return 0;
		}
		if (dire == ENTER) {
			//printf("%d  %d %d  %d %d", map[i][j], y, x / 2, i, j);
			if (0 == move_check(map[i][j], y, x / 2, i, j)) {		//인자  무슨기물인지?    움직일 자리가 어디인지?  움직이기 전 자리
				map[y][x / 2] = map[i][j];
				map[i][j] = 0;
				check(map[y][x / 2], y, x / 2);
				return 0;
			}
			if (1 == move_check(map[i][j], y, x / 2, i, j)) {
				gotoxy(0, 9);
				printf("                                                                               ");
				gotoxy(0, 9);
				printf("선택하신 곳으로 움직일 수 없습니다!");
				Sleep(1000);
				goto a;  //move_char 처음으로
			}

		}

		switch (dire) {					//움직일곳 고를때 방향
		case UP:
			if (y - 1 < 0) {
				break;
			}
			y = y - 1;
			gotoxy(x, y);
			break;

		case DOWN:
			if (y + 1 > 7) {
				break;
			}
			y = y + 1;
			gotoxy(x, y);
			break;

		case RIGHT:
			if (x - 2 < 0) {
				break;
			}
			x = x - 2;
			gotoxy(x, y);
			break;

		case LEFT:
			if (x + 2 > 15) {
				break;
			}
			x = x + 2;
			gotoxy(x, y);
			break;


		}
	}
}
int map_draw() {			//map 으로 체스판 draw
	int i = 0, j = 0, checkmate_W = 0, checkmate_B = 0;

	gotoxy(0, 0);
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\nver 1.1.2");
	gotoxy(0, 0);

	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			if ((i + 1) % 2 == 0) {
				if ((j + 1) % 2 == 1) {		//하얀색 검정색 체스판 만들기
					setColor(0, 8);
				}
				if ((j + 1) % 2 == 0) {
					setColor(0, 7);
				}
			}
			if ((i + 1) % 2 == 1) {
				if ((j + 1) % 2 == 0) {
					setColor(0, 8);
				}
				if ((j + 1) % 2 == 1) {
					setColor(0, 7);
				}
			}
			_setmode(_fileno(stdout), _O_TEXT);
			gotoxy(j * 2, i);
			switch (map[i][j]) {
			case 0:
				if ((i + 1) % 2 == 0) {
					if ((j + 1) % 2 == 1) {
						printf("  ");
					}
					if ((j + 1) % 2 == 0) {
						printf("  ");
					}
				}
				if ((i + 1) % 2 == 1) {
					if ((j + 1) % 2 == 0) {
						printf("  ");
					}
					if ((j + 1) % 2 == 1) {
						printf("  ");
					}

				}
				break;


			case 1:					//색상 바꾸기
				_setmode(_fileno(stdout), _O_U16TEXT);    //유니코드 출력
				wprintf(L"\x265F \n");
				break;

			case 2:
				_setmode(_fileno(stdout), _O_U16TEXT);    //유니코드 출력
				wprintf(L"\x265C \n");
				break;

			case 3:
				_setmode(_fileno(stdout), _O_U16TEXT);    //유니코드 출력
				wprintf(L"\x265E \n");
				break;

			case 4:
				_setmode(_fileno(stdout), _O_U16TEXT);    //유니코드 출력
				wprintf(L"\x265D \n");
				break;

			case 5:
				_setmode(_fileno(stdout), _O_U16TEXT);    //유니코드 출력
				wprintf(L"\x265B \n");
				break;

			case 6:
				if (Check == 2)						//체크 일 때 색 바꾸기
					setColor(4, 12);
				_setmode(_fileno(stdout), _O_U16TEXT);    //유니코드 출력
				wprintf(L"\x265A \n");
				break;

			case 10:
				_setmode(_fileno(stdout), _O_U16TEXT);    //유니코드 출력
				wprintf(L"\x2659 \n");
				break;

			case 20:
				_setmode(_fileno(stdout), _O_U16TEXT);
				wprintf(L"\x2656 \n");
				break;

			case 30:
				_setmode(_fileno(stdout), _O_U16TEXT);
				wprintf(L"\x2658 \n");
				break;

			case 40:
				_setmode(_fileno(stdout), _O_U16TEXT);
				wprintf(L"\x2657 \n");
				break;

			case 50:
				_setmode(_fileno(stdout), _O_U16TEXT);
				wprintf(L"\x2655 \n");
				break;

			case 60:
				if (Check == 1)				//체크일 때 색 바꾸기
					setColor(1, 12);
				_setmode(_fileno(stdout), _O_U16TEXT);
				wprintf(L"\x2654 \n");
				break;
			}		//switch문
		}			//for j문
		_setmode(_fileno(stdout), _O_TEXT);
		printf("\n");
	}				//for i문
	setColor(7, 0);
	
}					//map_draw 함수


int check(int it, int i, int j) {
	int king_i = 0, king_j = 0;
	for (king_i = 0; king_i < 8; king_i++) {
		for (king_j = 0; king_j < 8; king_j++) {

			if (map[king_i][king_j] == 60 && count % 2 == 0) {				//흑색 체크
				if (0 == move_check(it, king_i, king_j, i, j)) {
					Check = 1;
					printf("\a");
				}

			}


			if (map[king_i][king_j] == 6 && count % 2 == 1) {			//흰색체크
				if (0 == move_check(it, king_i, king_j, i, j)) {
					Check = 2;
					printf("\a");
				}

			}

		}
	}



}


void start_() {
	printf("\n\n\n\n\t\t\t   CHESS\n\n\n\t\t\t  v 1.1.2\n\n\n\n\n\n\n\t\t\t\t\t\t by  yuntak");
	Sleep(3000);
	system("cls");
	Time(3);	//시간 출력
}
void gotoxy(int x, int y)		  //gotoxy함수 만들기 
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void setColor(unsigned short text, unsigned short back) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}

void setFontColor(int color) {
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (info.wAttributes & 0xf0) | (color & 0xf));
}




/*P: ▲
	N : ♣
	B : ∮
	l : ▣
	Q : ∫
	K : ∬*/
	/*ss king	♔
	white chess queen	♕
	white chess rook	♖
	white chess bishop	♗
	white chess knight	♘
	white chess pawn	♙
	black chess king	♚
	black chess queen	♛
	black chess rook	♜
	black chess bishop	♝
	black chess knight	♞
	black chess pawn	♟*/


