/*
** EPITECH PROJECT, 2022
** print_win.c
** File description:
** lol
*/

void do_win(void)
{
    clear();
    refresh();
    while (1) {
	printw("CONGRATULATIONS, YOU WON !");
        if (getch() == ' ') {
            endwin();
            exit(0);
        }
    }
}
