#include <curses.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>

#define DX 5
#define DY 3
#define WIN_LINES LINES - 2 * DY - 2
#define WIN_COLS COLS - 2 * DX - 2

int
main(int argc, char *argv[])
{

    printf("%s\n", argv[0]);
    if (argc < 2) {
        printf("Not file given\n");
        return 0;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("No file named %s found\n", argv[1]);
        return 0;
    }

    WINDOW *frame, *win;
    char *text;
    int c = 0;

    setlocale(LC_ALL, "");
    initscr();
    noecho();
    cbreak();
    refresh();

    frame = newwin(LINES - 2 * DY, COLS - 2 * DX, DY, DX);
    box(frame, 0, 0);
    mvwaddstr(frame, 0, 2, argv[1]);
    wrefresh(frame);

    win = newwin(WIN_LINES, WIN_COLS, DY + 1, DX + 1);
    keypad(win, TRUE);
    scrollok(win, TRUE);

    text = calloc(WIN_COLS + 1, sizeof(char)); // len(line) + '\0'

    for (int idx = 0; idx < WIN_LINES && fgets(text, WIN_COLS + 1, fp); idx++) {
        if (strlen(text) == WIN_COLS) {
            for (int j = 'g'; j != EOF && j != '\n'; j = fgetc(fp))
                ;
        }
        wprintw(win, "%s", text);
    }
    wrefresh(win);
    while ((c = wgetch(win)) != 27) {
        if (c == 32 && fgets(text, WIN_COLS + 1, fp)) {
            if (strlen(text) == WIN_COLS) {
                for (int j = 'g'; j != EOF && j != '\n'; j = fgetc(fp))
                    ;
            }
            wprintw(win, "%s", text);
            wrefresh(win);
        }
    }
    free(text);

    delwin(win);
    delwin(frame);
    endwin();
    fclose(fp);

    return 0;
}