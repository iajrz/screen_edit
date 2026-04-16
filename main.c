#include <assert.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <ncurses.h>
// maybe loan some ideas
// https://patorjk.com/software/taag/#p=display&f=Alphabet&t=Type+Something+&x=none&v=4&h=4&w=80&we=false
// definitely remember https://www.youtube.com/watch?v=FLlDt_4EGX4
int main() {
    initscr();
    cbreak();
    noecho();
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);
    WINDOW *diag = newwin(5, 30, 0, 0);
    assert(curs_set(0) != ERR);
    keypad(stdscr,TRUE);

    // I did not expect KEY_LEFT to be beyond the values for the char type. if I were pushing it, short?
    // I think if I was really pushing it, it'd be uint16_t, which iirc gets fished from stdint.h or something.
    int userInput = 0;
    // these could also be uint16_t.
    int col = 0;
    int row = 0;
    // IDE recommended this was a constexpr;
    // this is annoying as I want to have this be a C project and constexpr is C++.
    constexpr char curChar[] = {'x', 'v'};
    unsigned long curCharIdx = 0;

    while (userInput != 'q' && userInput != 'Q') {
        userInput = getch();
        switch (userInput) {
            case KEY_LEFT:
                col--;
                if (col < 0) {
                    col = maxX - 1;
                }
                break;
            case KEY_RIGHT:
                col++;
                if (col > maxX - 1) {
                    col = 0;
                }
                break;
            case KEY_UP:
                row--;
                if (row < 0) {
                    row = maxY - 1;
                }
                break;
            case KEY_DOWN:
                row++;
                if (row > maxY - 1) {
                    row = 0;
                }
                break;
            case KEY_NPAGE:
                curCharIdx = (curCharIdx + 1) % sizeof(curChar);
                break;
            case KEY_PPAGE:
                curCharIdx = (curCharIdx + sizeof(curChar) - 1) % sizeof(curChar);
                break;
            case KEY_RESIZE:
                getmaxyx(stdscr, maxY, maxX);
            default:
                // do naught, for naught is warranted
                ;
        }
        int moveResult = move(row, col);
        // addch(curChar[curCharIdx]);
        refresh();
        werase(diag); // clear only diag
        box(diag, 0, 0); // border
        mvwprintw(diag, 1, 1, "row=%d col=%d", row, col);
        mvwprintw(diag, 2, 1, "move=%d", moveResult);
        wrefresh(diag); // draw on top
    }
    endwin();
    printf("%lu", sizeof(curChar));
    return 0;
}
