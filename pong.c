
#include <ncurses.h> 
#include <unistd.h> 
#include <string.h> 
#include <stdlib.h> 
#include <cdk/cdk.h> 
#include <stdbool.h>

#define CENTER_Y LINES / 2
#define CENTER_X COLS / 2
#define BAR_W 20

	//globals//
	int up_down = 0;
	int down_up = 0;
	int point_counter1 = 0;
	int point_counter2 = 0;
	CDKSCREEN *cdk;
	//globals//

	//prototypes//
	void draw_loading_screen(void);
	void game(int,int,int,int,int);
	int menu(void);
	int difficulty_menu(CDKSCREEN *cdk);
	//prototypes//
	
int main()
{	
	//loading screen//
	initscr();	
	draw_loading_screen();
	clear();
	//loading screen//
	//vars//
	int x = 0;
	int dx = 2; 
	int y = 0;
	int dy = 1;	
	//vars//

	int perma_diff_choice; // place to store return value of difficulty_menu
	switch(menu())
	{
		case 2: perma_diff_choice = difficulty_menu(cdk); game(x,dx,y,dy,perma_diff_choice); break;
		case 1: game(x,dx,y,dy,1); break;
		case 0: break;
	}
	destroyCDKScreen(cdk);
	endCDK();
	endwin();
	return 0;
}

void game(int x, int dx, int y, int dy,int perma_diff_choice)
{	
	int speed;
	switch(perma_diff_choice)
	{
		case 0: speed = 80; break;	// NAH ID WIN
		case 1:	speed = 50; break;	// NORMAL
		case 2:	speed = 30; break;	// MASOCHISM
		case 3:	speed = 1; break;	// YUTA
	}
	//setup//
	cbreak();				
	nodelay(stdscr, TRUE);
	curs_set(0);
	mousemask(0, NULL);
	noecho();
	keypad(stdscr,TRUE);
	//setup//

	while (1) 
	{
		mvaddch(y, x, '+'); 
		refresh();
		mvaddch(y, x, ' ');
		napms(speed); // place where difficulty gets applied

		x += dx;
		y += dy;

		//boundscheck ball//
		mvprintw(0,10,"left %-4d",point_counter1);
		mvprintw(0,80,"right %-4d",point_counter2);

		if (x >= COLS-1){	
			point_counter1 += 1;
			x = CENTER_X;
			y = CENTER_Y;
			dx = -dx;
		}	
		if (x < 0){
			point_counter2 += 1;
			x = CENTER_X;
			y = CENTER_Y;
			dx = -dx;
		}	
		if (y <= 0 || y >= LINES-1)
		{
			dy = -dy;
		}
		//bounds check ball//

		//first player//
		refresh();
		int p = getch();
		if (p == 'w')
		{
			mvvline(up_down,0,' ',10);
			up_down--;
			if (up_down < 0) up_down = 30;
			mvvline(up_down,0,'|',10);
		}
		else if (p == 's')
		{
			mvvline(up_down,0,' ',10);
			up_down++;
			if (up_down > 30) up_down = 0;
			mvvline(up_down,0,'|',10);
		}
		
		if (x == 2 && y >= up_down && y < up_down + 9)
		{
			dx = -dx;
		}
		//first player//

		//second player//
		refresh();
		mvvline(down_up, COLS-2, '|', 10);

		if (p == KEY_UP)
		{
			mvvline(down_up, COLS-2, ' ', 10);
			down_up--;
			if (down_up < 0) down_up = 30;
			mvvline(down_up, COLS-2, '|', 10);
		}
		else if (p == KEY_DOWN)
		{
			mvvline(down_up, COLS-2, ' ', 10);
			down_up++;
			if (down_up > 30) down_up = 0;
			mvvline(down_up, COLS-2, '|', 10);
		}

		if (x == COLS-3 && y >= down_up && y < down_up + 9)
		{
			dx = -dx;
		}
		//second player//
	}
}

int menu(void)
{
	WINDOW *win = initscr();
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	cdk = initCDKScreen(win);

	char *items[] = {
		"START(normal difficulty)",
		"DIFFICULTY",
		"EXIT"
	};

	CDKSCROLL *m = newCDKScroll(
		cdk,
		CENTER, CENTER,
		RIGHT,
		6, 33,
		"MENU",
		items,
		3,
		TRUE,
		A_REVERSE | COLOR_PAIR(1),
		TRUE,
		FALSE
	);

	int choice = activateCDKScroll(m, 0);
	destroyCDKScroll(m);
	return choice + 1; // 1=START, 2=DIFFICULTY, 3=EXIT
}

int difficulty_menu(CDKSCREEN *cdk)
{
	init_pair(1, COLOR_GREEN, COLOR_BLACK);

	char *items[] = {
		"EASY",
		"NORMAL",
		"HARD",
		"YUTA BUSHCAMPER"
	};

	CDKSCROLL *m = newCDKScroll(
		cdk,
		CENTER, CENTER,
		RIGHT,
		9, 28,
		"DIFFICULTY",
		items,
		4,
		TRUE,
		A_REVERSE | COLOR_PAIR(1),
		TRUE,
		FALSE
	);

	int difficulty_choice = activateCDKScroll(m, 0);
	destroyCDKScroll(m);
	return difficulty_choice;
}
/////////////////////////////////////////////
////////////////////////////////////////////
////////////////////////////////////////////

	static const char *title[] = {
	"  ######   ######  ##   ##  ###### ",
	"  ##   ## ##    ## ###  ## ##      ",
	"  ######  ##    ## ## # ## ##  ### ",
	"  ##      ##    ## ##  ### ##   ## ",
	"  ##       ######  ##   ##  ###### ",
	NULL
	};
	static const char *items[] = { //text to be printed before each [#####] 100%
	"ncurses terminal init  ",
	"allocating framebuffer ",
	"loading paddle physics ",
	"calibrating ball vector",
	"torturing minorities   ",
	"setting up score table ",
	"__init__ char bjelkan[]",
	"coding herobrine logic ",
	"starting game loop     ",
	"pondering life choices ",
	"implementing herobrine ",
	"nah id win yuji        ",
	NULL
	};

void draw_loading_screen(void) {
	int rows, cols;
	getmaxyx(stdscr, rows, cols);
	clear();
	curs_set(0);
	/* title */
	int y = 1;
	for (int i = 0; title[i]; i++, y++) {
	int x = (cols - (int)strlen(title[i])) / 2;
	mvprintw(y, x < 0 ? 0 : x, "%s", title[i]);
	}
	y++;
	const char *court[] = {
	"+------------------------------------+",
	"|  ||             .              ||  |",
	"|  ||      .      O      .       ||  |",
	"|  ||             .              ||  |",
	"+------------------------------------+",
	NULL
	};
	for (int i = 0; court[i]; i++, y++) {
	int x = (cols - (int)strlen(court[i])) / 2;
	mvprintw(y, x < 0 ? 0 : x, "%s", court[i]);
	}
	y++;
	mvprintw(y++, 2, "INITIALIZING SUBSYSTEMS");
	y++;
	/* loading bars */
	for (int i = 0; items[i]; i++, y++) {
	mvprintw(y, 2, "> %s [", items[i]);
	refresh();
	int bx = 2 + 2 + (int)strlen(items[i]) + 2;
	for (int b = 0; b < BAR_W; b++) {
	usleep(12000);
	mvprintw(y, bx + b, "#");
	refresh();
		}
	mvprintw(y, bx + BAR_W, "] 100%%");
	refresh();
	}
	y++;
	mvprintw(y++, 2, "ALL SYSTEMS READY.");
	mvprintw(y,   2, "Press [ ENTER ] to serve.");
	refresh();
	getch();
}
