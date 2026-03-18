#include <ncurses.h>
int up_down = 0;
int down_up = 0;
int main()
{
//setup//
initscr();
cbreak();				
noecho();
keypad(stdscr, TRUE);
nodelay(stdscr, TRUE);
curs_set(0);
//setup//
//vars//
int x = 0;
int dx = 1; //speed (column per second)
int y = 0;
int dy = 1; // speed (row per second)
int player_1_y = 0;						
//vars//		

while (1) {

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

	//updown counter first player//
	mvprintw(0,5,"updown is %2d",up_down);
	//updown counter first player//

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
	//second player bounds check//

	//updown counter first player//
	mvprintw(0,70,"downup is %2d",down_up);
	//updown counter first player//

}
endwin();
return 0;
}

