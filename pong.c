#include <ncurses.h>
#include <stdlib.h>
#include <cdk/cdk.h>
#include <time.h>

	//globals//
	int up_down = 0;
	int down_up = 0;
	//globals//

	//prototypes//
	void game(int,int,int,int);
	void menu(void);
	//prototypes//
	
int main()
{
	//setup//
	initscr();
	cbreak();				
	noecho();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	curs_set(0);
	mousemask(0, NULL);
	//setup//
	//vars//
	int x = 0;
	int dx = 1;
	int y = 0;
	int dy = 1;					
	//vars//

	menu();
	
	
	
}

void game(int x, int dx, int y, int dy)
{	
	while (1) 
	{

    	mvaddch(y, x, '+'); 
    	refresh();
		mvaddch(y, x, ' ');
    	napms(50);

    	x += dx;
		y += dy;

 		//boundscheck ball//
    	if (x <= 0 || x >= COLS-1)
		{
			dx = -dx;
		}
			if (y <= 0 || y >= LINES-1)
		{
			dy = -dy;
		}
 		//bounds check ball//

														
		//first player bounds check//
		switch(up_down)
		{
		case -1: up_down = 30; mvvline(-1,0,' ',10); mvvline(up_down,0,'|', 10);
		break;
		case 31: up_down = 0; mvvline(31,0,' ',10); mvvline(up_down,0,'|', 10);
		break;
		}
		//first player bounds check//

		//first player//
    	refresh();
		int p = getch();
		if ( p == 'w')
		{
        mvvline(up_down,0,' ',10);
        up_down--;
        mvvline(up_down,0,'|',10);
		}else
    	if(p == 's')
    	{
        mvvline(up_down,0,' ',10);
        up_down++;
        mvvline(up_down,0,'|',10); 
    	}
		//first player//
		//
		if ( p == KEY_BACKSPACE)
		{
			break;
		}
		//
		//second player//
		refresh();
		mvvline(down_up,168,'|',10);

		if ( p == KEY_UP)
		{
        mvvline(down_up,168,' ',10);
        down_up--;
        mvvline(down_up,168,'|',10);
		}else
    	if(p == KEY_DOWN)
    	{
        mvvline(down_up,168,' ',10);
        down_up++;
        mvvline(down_up,168,'|',10);
    	}
		//second player//

		//second player bounds check//
		switch(down_up)
		{
		case -1: down_up = 30; mvvline(down_up,168,' ',10); 
		break;
		case 31: down_up = 0; mvvline(31,168,' ',10);
		break;
		}
	}
	endwin();	
}

void menu()
{
	 WINDOW *win = initscr();

    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK); 

    CDKSCREEN *cdk = initCDKScreen(win);

    char *items[] = {
        "START",
        "EXIT"
    };

    CDKSCROLL *menu = newCDKScroll(
        cdk,
        CENTER, CENTER,
        RIGHT,
        7, 28,
        "MENU",
        items,
        2,
        TRUE,
        A_REVERSE | COLOR_PAIR(1),
        TRUE,
        FALSE
    );

    activateCDKScroll(menu, 0);

    destroyCDKScroll(menu);
    endCDK();
    endwin();
}


