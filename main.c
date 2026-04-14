#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <ncurses.h>
// maybe loan some ideas
// https://patorjk.com/software/taag/#p=display&f=Alphabet&t=Type+Something+&x=none&v=4&h=4&w=80&we=false
// definitely remember https://www.youtube.com/watch?v=FLlDt_4EGX4
int main() {
    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1) {
        perror("ioctl");
        return 1;
    }
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr,TRUE);

    int c = 0; // I did not expect KEY_LEFT to be beyond the values for the char type.
    // these could be unsigned, perhaps even (gasp!) short
    int col = 0;
    int row = 0;
    constexpr char curChar[] = {'x','v'};
    unsigned long curCharIdx = 0;

    while (c != 'q' && c != 'Q') {
        c = getch();
        switch (c) {
            case KEY_LEFT:
                col--;
                if (col < 0) {
                    col = ws.ws_col - 1;
                }
                break;
            case KEY_RIGHT:
                col++;
                if (col > ws.ws_col - 1) {
                    col = 0;
                }
                break;
            case KEY_UP:
                row--;
                if (row < 0) {
                    row = ws.ws_row - 1;
                }
                break;
            case KEY_DOWN:
                row++;
                if (row > ws.ws_row - 1) {
                    row = 0;
                }
                break;
            case KEY_NPAGE:
                curCharIdx = (curCharIdx + 1) % sizeof(curChar);
                break;
            case KEY_PPAGE:
                curCharIdx = (curCharIdx + sizeof(curChar) - 1) % sizeof(curChar);
                break;
            default:
                // do naught, for naught is warranted
                ;
        }
        move(row, col);
        addch(curChar[curCharIdx]);
        refresh();
    }
    endwin();
    printf("%lu",sizeof(curChar));
    return 0;
}
