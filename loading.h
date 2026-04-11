#ifndef loading_H
#define loading_H

#include <ncurses.h> 
#include <unistd.h> 
#include <string.h> 
#include <stdlib.h> 
#include <cdk/cdk.h> 
#include <stdbool.h>

static const char *title[] = {
  "  ######   ######  ##   ##  ###### ",
  "  ##   ## ##    ## ###  ## ##      ",
  "  ######  ##    ## ## # ## ##  ### ",
  "  ##      ##    ## ##  ### ##   ## ",
  "  ##       ######  ##   ##  ###### ",
  NULL
};

static const char *items[] = {
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

#define BAR_W 20

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
#endif