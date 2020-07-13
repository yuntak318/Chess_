//2020.02.11 시작
//2020.02.25 기물 움직이기 끝 및 각종 기술(체크 체크메이트 폰 승격 캐슬링 등) 추가 시작
//chess 
/*아이디어 노트:

UI
	- 색 차례마다 색이 앞에 오게 만들기 예)적색이 앞이면 적색 기준으로 판돌리기
		* map[i][j]를 그릴때 i,j++ 을 하지 않고 i--,j-- 를하면 맵이 바뀜
	- (마지막에 하기) 힌트만들기 수에 중요도를 기여하여 중요도가 가장 높은수를 힌트로
		예) enum 으로 1. 체크메이트 2. 체크 3. 캐슬링 4. 기물 교환 이라고 정헤서 갈 수 있는수에서 중요도가 가장 높은것을 맵에 표시
	- 맵 옆쪽 공간에 표기법 적기 요 코드는 system(cls) 를 한다음 맵을 다시 그리는 map_draw 함수 마지막에 적으면 될 것 같음
		*코드알고리즘 코드 표기법을 *move[100][3]에 저장(첫번째: 기물 이름(Q,K 등) 두번째: x,y 차례대로 저장) map_draw 함수 맨뒤에
			표기법 출력하는 함수 호출.(특수 표기법(캐슬링 승격 등)도 표기)
	- 기권, 되돌리기, 움직일려고 잡은 기물 취소 등 기타 세부사항 추가


*/
# include <Stdio.h>
# include <Windows.h>
# include <conio.h>
# include <wchar.h>
# include <string.h>
# define UP 72
# define DOWN 80
# define RIGHT 75
# define LEFT 77
# define ENTER 13
int map[8][8] = { 0 , }, oldi, oldj, count = 1;
FILE* fp;
void start_();
int move_check(int it, int i, int j, int oldi, int oldj);
int move_choose(int i, int j);
int map_read();
int map_draw();
int choose_char();
int move_char(int i, int j);
void gotoxy(int x, int y);
void setColor(unsigned short text, unsigned short back);
void setFontColor(int color);
int main() {
	system("mode con cols=70 lines=15");
	start_();
	map_read();
	map_draw();
	choose_char();
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

int choose_char() {

	int x = 0, y = 0, dire;
	gotoxy(0, 9);
	printf("                                                   ");
	gotoxy(0, 9);
	if (count % 2 == 1)
		printf("(청색 차례)움직일 기물을 선택하세요...");
	if (count % 2 == 0)
		printf("(적색 차례)움직일 기물을 선택하세요...");
	gotoxy(0, 0);
	while (1) {

	a:
		dire = getch();
		if (dire == ENTER && map[y][x / 2] != 0) {

			if (map[y][x / 2] < 10 && count % 2 == 0) {				//지우면 안됨!!
				move_char(y, x / 2);
				goto b;
			}
			if (map[y][x / 2] >= 10 && count % 2 == 1) {
				move_char(y, x / 2);
				goto b;
			}
			else {
				if (count % 2 == 1) {
					gotoxy(0, 9);
					printf("                                                                                        ");
					gotoxy(0, 9);
					printf("청색 차례 입니다!! 청색기물만 움직일 수 있습니다....");
					Sleep(1000);
					gotoxy(0, 9);
				}
				if (count % 2 == 0) {
					gotoxy(0, 9);
					printf("                                                                                       ");
					gotoxy(0, 9);
					printf("적색 차례 입니다!! 적색기물만 움직일 수 있습니다....");
					Sleep(1000);
					gotoxy(0, 9);
				}

			}
		b:

			gotoxy(0, 9);
			printf("                                                                               ");
			gotoxy(0, 9);
			if (count % 2 == 1)
				printf("(청색 차례)움직일 기물을 선택하세요...");
			if (count % 2 == 0)
				printf("(적색 차례)움직일 기물을 선택하세요...");
			gotoxy(0, 0);
			x = 0, y = 0;
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
}
int move_check(int it, int i, int j, int oldi, int oldj) {
	int n, n_2;
	//if (count % 2 == 0) {				/지우면 안됨!!
	switch (it) {
	case 1:											//PAWN_B

		if (oldi + 1 == i && oldj == j) {				//한칸 앞으로 갈때
			if (map[i][j] == 0) {
				return 0;
			}
		}
		if (oldi + 2 == i && oldj == j && oldi == 1) {		//두칸 앞으로 갈떄
			if (map[i][j] == 0 && map[i - 1][j] == 0) {
				return 0;
			}
		}
		if (oldi + 1 == i) {		//대각선으로 갈 떄
			if (oldj - 1 == j || oldj + 1 == j) {
				if (map[i][j] >= 10) {									//하얀색기물은 10보다 큼
					return 0;
				}
			}
		}
		return 1;
		break;
		//===========================================================================
	case 20:									//ROOK_W
	case 2:										//ROOK_B
		if (map[oldi][oldj] >= 10) {					//청색이면,
			if (map[i][j] >= 10) {
				return 1;
			}
		}
		if (map[oldi][oldj] < 10) {							//적색이면,
			if (map[i][j] != 0 && map[i][j] < 10) {
				return 1;
			}
		}
		if (oldi > i&& oldj == j) {				//위쪽으로 움직일때
			for (n = i + 1; n < oldi; n++) {
				if (map[n][j] != 0) {
					return 1;
				}
			}
			return 0;
		}

		if (oldi < i&& oldj == j) {					//아래쪽으로 움직일떄
			for (n = i - 1; n > oldi; n--) {
				if (map[n][j] != 0) {
					return 1;
				}
			}
			return 0;
		}

		if (oldi == i && oldj > j) {				//왼쪽으로 움직일떄
			for (n = j + 1; n < oldj; n++) {
				if (map[i][n] != 0) {
					return 1;
				}
			}
			return 0;
		}

		if (oldi == i && oldj < j) {				//오른쪽으로 움직일떄
			for (n = j - 1; n > oldj; n--) {
				if (map[i][n] != 0) {
					return 1;
				}
			}
			return 0;
		}

		break;
		//=============================================================================
	case 30:															//KNIGHT_W
	case 3:																//KNIGHT_B
		if (map[oldi][oldj] >= 10) {					//청색이면,
			if (map[i][j] >= 10) {
				return 1;
			}
		}
		if (map[oldi][oldj] < 10) {							//적색이면,
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
	case 40:															//BISHOP_W
	case 4:																//BISHOP_B
		if (map[oldi][oldj] >= 10) {					//청색이면,
			if (map[i][j] >= 10) {
				return 1;
			}
		}
		if (map[oldi][oldj] < 10) {							//적색이면,
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
	case 50:																//QUEEN_W
	case 5:																	//QUEEN_B
		if (map[oldi][oldj] >= 10) {					//청색이면,
			if (map[i][j] >= 10) {
				return 1;
			}
		}
		if (map[oldi][oldj] < 10) {							//적색이면,
			if (map[i][j] != 0 && map[i][j] < 10) {
				return 1;
			}
		}
		if (oldi > i&& oldj == j) {				//위쪽으로 움직일때
			for (n = i + 1; n < oldi; n++) {
				if (map[n][j] != 0) {
					return 1;
				}
			}
			return 0;
		}

		if (oldi < i&& oldj == j) {					//아래쪽으로 움직일떄
			for (n = i - 1; n > oldi; n--) {
				if (map[n][j] != 0) {
					return 1;
				}
			}
			return 0;
		}

		if (oldi == i && oldj > j) {				//왼쪽으로 움직일떄
			for (n = j + 1; n < oldj; n++) {
				if (map[i][n] != 0) {
					return 1;
				}
			}
			return 0;
		}

		if (oldi == i && oldj < j) {				//오른쪽으로 움직일떄
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
				for (n = oldi + 1, n_2 = oldj - 1; n > i; n++, n_2--) {
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
	case 60:															//KING_W
	case 6:																//KING_B
		if (map[oldi][oldj] >= 10) {					//청색이면,
			if (map[i][j] >= 10) {
				return 1;
			}
		}
		if (map[oldi][oldj] < 10) {							//적색이면,
			if (map[i][j] != 0 && map[i][j] < 10) {
				return 1;
			}
		}
		if (oldi + 1 == i || oldi - 1 == i) {				//한칸 앞,뒤로 갈때
			if (oldj == j) {
				return 0;
			}
		}
		if (oldj + 1 == i || oldj - 1) {			//한칸 옆로 갈때
			if (oldi == i) {
				return 0;
			}
		}
		if (oldi + 1 == i || oldi - 1 == i) {		//대각선으로 갈 떄
			if (oldj - 1 == j || oldj + 1 == j) {
				return 0;
			}
		}

		return 1;
		break;
		//==================================================================================
	case 10:														//PAWN_W

		if (oldi - 1 == i && oldj == j) {				//한칸 앞으로 갈때
			if (map[i][j] == 0) {
				return 0;
			}
		}
		if (oldi - 2 == i && oldj == j && oldi == 6) {		//두칸 앞으로 갈떄
			if (map[i][j] == 0 && map[i + 1][j] == 0) {
				return 0;
			}
		}
		if (oldi - 1 == i) {		//대각선으로 갈 떄
			if (oldj - 1 == j || oldj + 1 == j) {
				if (map[i][j] < 10) {									//검은색기물은 10보다 작음
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


	gotoxy(0, 9);
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
	gotoxy(0, 9);
	printf(" %s 을(를) 옮기실 곳을 선택하세요...", chess);
	gotoxy(j + 2, i);
	x = j * 2; y = i;
	while (1) {
		dire = getch();
		if (dire == 67) {
			return 0;
		}
		if (dire == ENTER) {
			//printf("%d  %d %d  %d %d", map[i][j], y, x / 2, i, j);
			if (0 == move_check(map[i][j], y, x / 2, i, j)) {		//인자  무슨기물인지?    움직일 자리가 어디인지?  움직이기 전 자리
				map[y][x / 2] = map[i][j];
				map[i][j] = 0;

				return 0;
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
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\nver 1.0.0");
	gotoxy(0, 0);
	//printf("▣");

	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			if ((i + 1) % 2 == 0) {
				if ((j + 1) % 2 == 1) {
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
			switch (map[i][j]) {
			case 0:
				if ((i + 1) % 2 == 0) {
					if ((j + 1) % 2 == 1) {
						printf("  ");
					}//■ □
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
				/*case 0:
					if ((i + 1) % 2 == 0) {
						if ((j + 1) % 2 == 1) {
							printf("■");
						}//■
						if ((j + 1) % 2 == 0) {
							printf("□");
						}
					}
					if ((i + 1) % 2 == 1) {
						if ((j + 1) % 2 == 0) {
							printf("■");
						}
						if ((j + 1) % 2 == 1) {
							printf("□");
						}
					}
					break;*/

			case 1:																	//색상 바꾸기
				setFontColor(4);
				printf("▲");

				break;

			case 2:
				setFontColor(4);
				printf("▣");
				break;

			case 3:
				setFontColor(4);
				printf("♣");
				break;

			case 4:
				setFontColor(4);
				printf("∮");
				break;

			case 5:
				setFontColor(4);
				printf("∫");
				break;

			case 6:
				checkmate_B++;
				setFontColor(4);
				printf("∬");
				break;

			case 10:
				setFontColor(1);
				printf("▲");
				break;

			case 20:
				setFontColor(1);
				printf("▣");
				break;

			case 30:
				setFontColor(1);
				printf("♣");
				break;

			case 40:
				setFontColor(1);
				printf("∮");
				break;

			case 50:
				setFontColor(1);
				printf("∫");
				break;

			case 60:
				checkmate_W++;
				setFontColor(1);
				printf("∬");
				break;
			}		//switch문
		}			//for j문
		printf("\n");
	}				//for i문
	setColor(7, 0);
	if (checkmate_B == 0) {
		printf("청색 승!!");
		Sleep(3000);
		exit(0);
	}
	if (checkmate_W == 0) {
		printf("적색 승!!\n\n");
		Sleep(3000);
		exit(0);
	}
}					//map_draw 함수
void start_() {
	printf("\n\n\n\n\t\t\t      CHESS\n\n\n\t\t\t     v 1.0.0\n\n\n\nby yuntak");
	Sleep(5000);
	system("cls");
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


