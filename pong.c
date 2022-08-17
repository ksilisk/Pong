#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define base_ball_y 12
#define base_ball_x1 2
#define base_ball_x2 77
#define base_racket_y 12

void draw_winner(int a);
void display(int racket1_x, int racket1_y, int racket2_x, int racket2_y, int ball_x, int ball_y, int screen1,
             int screen2);
void start_screen();

int main() {
    int racket1_x = 1, racket1_y = 12, racket2_x = 78, racket2_y = 12;
    int ball_x = 2, ball_y = 12;
    int screen1 = 0, screen2 = 0;
    int flag = 0;
    int move_ball_x = 1, move_ball_y = 1;
    initscr();
    cbreak();
    noecho();
    scrollok(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    clear();
    start_screen();
    char tap;
    tap = getch();
    while (tap == -1) {
        tap = getch();
    }
    clear();
    display(racket1_x, racket1_y, racket2_x, racket2_y, ball_x, ball_y, screen1, screen2);
    while (1) {
        usleep(75000);
        int goalF = 0;
        char comd;
        if (ball_y == 1 || ball_y == 23) {
            move_ball_y *= -1;
        }
        ball_x += move_ball_x;
        ball_y += move_ball_y;
        if ((((ball_y == racket1_y - 1) || (ball_y == racket1_y) || (ball_y == racket1_y + 1)) &&
             ball_x == 2) ||
            (((ball_y == racket2_y - 1) || (ball_y == racket2_y) || (ball_y == racket2_y + 1)) &&
             ball_x == 77)) {
            move_ball_x *= -1;
        } else if (ball_x == 1) {
            screen2++;
            ball_x = base_ball_x1;
            ball_y = base_ball_y;
            racket1_y = base_racket_y, racket2_y = base_racket_y;
            move_ball_x = 1;
            goalF = 1;
        } else if (ball_x == 78) {
            screen1++;
            ball_x = base_ball_x2;
            ball_y = base_ball_y;
            racket1_y = base_racket_y, racket2_y = base_racket_y;
            move_ball_x = -1;
            goalF = 1;
        }
        comd = getch();
        if (comd == 'A' || comd == 'a' || comd == 'z' || comd == 'Z' || comd == 'K' || comd == 'k' ||
            comd == 'M' || comd == 'm') {
            if (goalF != 1) {
                if ((comd == 'A' || comd == 'a') && racket1_y - 2 > 0) {
                    racket1_y--;
                } else if ((comd == 'Z' || comd == 'z') && racket1_y + 2 < 24) {
                    racket1_y++;
                } else if ((comd == 'K' || comd == 'k') && racket2_y - 2 > 0) {
                    racket2_y--;
                } else if ((comd == 'M' || comd == 'm') && racket2_y + 2 < 24) {
                    racket2_y++;
                }
            }
        }
        clear();
        display(racket1_x, racket1_y, racket2_x, racket2_y, ball_x, ball_y, screen1, screen2);
        if (screen1 == 10) {
            flag = 1;
            break;
        }
        if (screen2 == 10) {
            flag = 2;
            break;
        }
    }
    clear();
    draw_winner(flag);
    nocbreak();
    echo();
    return 0;
}

void display(int racket1_x, int racket1_y, int racket2_x, int racket2_y, int ball_x, int ball_y, int screen1,
             int screen2) {
    char vertical = '|';
    char horizontal = '-';
    char space = ' ';
    char racket1 = '$', racket2 = '$';
    char ball = '0';
    printw("              Player 1                 ");
    printw("                  Player 2\n");
    if (screen1 < 10) {
        for (int i = 0; i < 80; i++) {
            if (i == 35) {
                printw("%d", screen1);
            } else if (i == 45) {
                printw("%d", screen2);
            } else if (i == 40) {
                printw(":");
            } else {
                printw("%c", space);
            }
        }
    } else {
        for (int i = 0; i < 80; i++) {
            if (i == 34) {
                printw("%d", screen1);
            } else if (i == 44) {
                printw("%d", screen2);
            } else if (i == 39) {
                printw(":");
            } else {
                printw("%c", space);
            }
        }
    }
    printw("\n");
    for (int y = 0; y <= 24; y++) {
        for (int x = 0; x <= 79; x++) {
            if (y == 0 || y == 24) {
                printw("%c", horizontal);
            } else if (x == ball_x && y == ball_y) {
                printw("%c", ball);
            } else if (x == 0 || x == 40 || x == 79) {
                printw("%c", vertical);
            } else if ((x == racket1_x && y == racket1_y) || (x == racket1_x && y - 1 == racket1_y) ||
                       (x == racket1_x && y + 1 == racket1_y)) {
                printw("%c", racket1);
            } else if ((x == racket2_x && y == racket2_y) || (x == racket2_x && y - 1 == racket2_y) ||
                       (x == racket2_x && y + 1 == racket2_y)) {
                printw("%c", racket2);
            } else {
                printw("%c", space);
            }
        }
        printw("\n");
    }
}
void start_screen() {
    printw("--------------------------------------------------------------------------------\n");
    printw("|                                                                              |\n");
    printw("|                      ____     ____              ______                       |\n");
    printw("|                     |    |   |    |   |\\    |  |      |                      |\n");
    printw("|                     |    |   |    |   | \\   |  |      |                      |\n");
    printw("|                     |____|   |    |   |  \\  |  |   ___                       |\n");
    printw("|                     |        |    |   |   \\ |  |      |                      |\n");
    printw("|                     |        |____|   |    \\|  |______|                      |\n");
    printw("|                                                                              |\n");
    printw("|                                                                              |\n");
    printw("|                            TWO PLAYERS ONE WINNER                            |\n");
    printw("|                                                                              |\n");
    printw("|                                    RULES:                                    |\n");
    printw("|                                                                              |\n");
    printw("|                      1. each player must move                                |\n");
    printw("|                         his racket to catch the ball                         |\n");
    printw("|                                                                              |\n");
    printw("|                      2. if the ball does not hit                             |\n");
    printw("|                         the racket, the opponent gets                        |\n");
    printw("|                         a point and a new round begins                       |\n");
    printw("|                                                                              |\n");
    printw("|                      3. the game ends when the score                         |\n");
    printw("|                         becomes 10 points                                    |\n");
    printw("|                                                                              |\n");
    printw("|                                                                              |\n");
    printw("--------------------------------------------------------------------------------\n");
}

void draw_winner(int a) {
    if (a == 1) {
        clear();
        printw("--------------------------------------------------------------------------------\n");
        printw("|                                                                              |\n");
        printw("|                                                                              |\n");
        printw("|                                                                              |\n");
        printw("|                       |       |        |   |    |\\     |                     |\n");
        printw("|                       |       |        |   |    | \\    |                     |\n");
        printw("|                       |       |        |   |    |  \\   |                     |\n");
        printw("|                       |       |        |   |    |   \\  |                     |\n");
        printw("|                       |        \\  /\\  /    |    |    \\ |                     |\n");
        printw("|                       |         \\/  \\/     |    |     \\|                     |\n");
        printw("|                                                                              |\n");
        printw("|                                                                              |\n");
        printw("|                                                                              |\n");
        printw("|                                CONGRATULATIONS!                              |\n");
        printw("|                                ---------------                               |\n");
        printw("|                                                                              |\n");
        printw("--------------------------------------------------------------------------------\n");
        refresh();
        char x = getchar();
        printw("%c", x);
    } else if (a == 2) {
        clear();
        printw("--------------------------------------------------------------------------------\n");
        printw("|                                                                              |\n");
        printw("|                                                                              |\n");
        printw("|                     ____                                                     |\n");
        printw("|                    |    |      |        |   |    |\\     |                    |\n");
        printw("|                    |    |      |        |   |    | \\    |                    |\n");
        printw("|                        /       |        |   |    |  \\   |                    |\n");
        printw("|                       /        |        |   |    |   \\  |                    |\n");
        printw("|                      /          \\  /\\  /    |    |    \\ |                    |\n");
        printw("|                     /____        \\/  \\/     |    |     \\|                    |\n");
        printw("|                                                                              |\n");
        printw("|                                                                              |\n");
        printw("|                                                                              |\n");
        printw("|                                CONGRATULATIONS!                              |\n");
        printw("|                                ---------------                               |\n");
        printw("|                                                                              |\n");
        printw("--------------------------------------------------------------------------------\n");
        refresh();
        char x = getchar();
        printw("%c", x);
    }
}
