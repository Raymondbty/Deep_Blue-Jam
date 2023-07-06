/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-aurelien.duval
** File description:
** core
*/
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <dirent.h>
#include <unistd.h>
#include <iostream>
#include <ostream>
#include <dlfcn.h>
#include <filesystem>
#include <vector>
#include <string>

void make_choice(const std::string& selected_game_library, const std::string& selected_graphical_library);


int print_title()
{
    int title_x = (COLS - 31) / 2 - 10;
    int title_y = 1;
    
    mvprintw(title_y, title_x, "      /\\      ");
    mvprintw(title_y+1, title_x, "     /  \\     ");
    mvprintw(title_y+2, title_x, "    / /\\ \\    ");
    mvprintw(title_y+3, title_x, "   / ____ \\   ");
    mvprintw(title_y+4, title_x, "  /_/    \\_\\  ");

    mvprintw(title_y, title_x+7, " _____  ");
    mvprintw(title_y+1, title_x+7, "|  __ \\ ");
    mvprintw(title_y+2, title_x+7, "| |__) |");
    mvprintw(title_y+3, title_x+7, "|  _  / ");
    mvprintw(title_y+4, title_x+7, "| | \\ \\ ");
    mvprintw(title_y+5, title_x+7, "|_|  \\_\\");

    mvprintw(title_y, title_x+15, "   _____ ");
    mvprintw(title_y+1, title_x+15, "  / ____|");
    mvprintw(title_y+2, title_x+15, " | |     ");
    mvprintw(title_y+3, title_x+15, " | |     ");
    mvprintw(title_y+4, title_x+15, " | |____ ");
    mvprintw(title_y+5, title_x+15, "  \\_____|");

    mvprintw(title_y, title_x+23, "    /\\    ");
    mvprintw(title_y+1, title_x+23, "   /  \\   ");
    mvprintw(title_y+2, title_x+23, "  / /\\ \\  ");
    mvprintw(title_y+3, title_x+23, " / ____ \\ ");
    mvprintw(title_y+4, title_x+23, "/_/    \\_\\");

    mvprintw(title_y, title_x+31, " _____  ");
    mvprintw(title_y+1, title_x+31, "|  __ \\ ");
    mvprintw(title_y+2, title_x+31, "| |  | |");
    mvprintw(title_y+3, title_x+31, "| |  | |");
    mvprintw(title_y+4, title_x+31, "| |__| |");
    mvprintw(title_y+5, title_x+31, "|_____/ ");

    mvprintw(title_y, title_x+39, " ______ ");
    mvprintw(title_y+1, title_x+39, "|  ____|");
    mvprintw(title_y+2, title_x+39, "| |__   ");
    mvprintw(title_y+3, title_x+39, "|  __|  ");
    mvprintw(title_y+4, title_x+39, "| |____ ");
    mvprintw(title_y+5, title_x+39, "|______|");

    refresh();
    return 0;
}

std::vector<std::string> list_files_in_directory(const std::string& directory_path)
{
    std::vector<std::string> file_paths;
    
    std::filesystem::directory_iterator iter(directory_path);
    std::filesystem::directory_iterator end;
    
    while (iter != end) {
        const std::filesystem::directory_entry &entry = *iter;
        
        if (entry.is_regular_file()) {
            std::string file_name = entry.path().filename().string();
            
            if (file_name != "." && file_name != "..")
            {
                file_paths.push_back(entry.path().string());
            }
        }
        iter++;
    }
    
    return file_paths;
}


int main(int argc, char* argv[])
{
    srand(time(nullptr));
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(5, COLOR_RED, COLOR_BLACK);
    refresh();
    print_title();

    const int height = 20, width = 60, padding = 5;
    const int x_start = (COLS - (3 * width + 2 * padding)) / 2;
    const int y_start = (LINES - height) / 2;

    WINDOW* games_win = newwin(height, width, y_start, x_start);
    wbkgd(games_win, COLOR_PAIR(1));
    box(games_win, 0, 0);
    mvwprintw(games_win, 0, (width - 12) / 2, "Games Library");
    wrefresh(games_win);

    WINDOW* graphics_win = newwin(height, width, y_start, x_start + width + padding);
    wbkgd(graphics_win, COLOR_PAIR(2));
    box(graphics_win, 0, 0);
    mvwprintw(graphics_win, 0, (width - 16) / 2, "Graphics Library");
    wrefresh(graphics_win);

    WINDOW* scoreboard_win = newwin(height, width, y_start, x_start + 2 * (width + padding));
    wbkgd(scoreboard_win, COLOR_PAIR(3));
    box(scoreboard_win, 0, 0);
    mvwprintw(scoreboard_win, 0, (width - 9) / 2, "Scoreboard");
    wrefresh(scoreboard_win);

    std::vector<std::string> games_libraries = list_files_in_directory("./games");
    std::vector<std::string> graphics_libraries = list_files_in_directory("./lib");


    int y = 2;
    int selected_game = 0;
    for (int i = 0; i < games_libraries.size(); i++)
    {
        if (i == selected_game) {
            wattron(games_win, COLOR_PAIR(4));
        }
        mvwprintw(games_win, y, 2, games_libraries[i].c_str());
        if (i == selected_game) {
            wattroff(games_win, COLOR_PAIR(4));
        }
        y++;
    }
    wrefresh(games_win);
    
    int selected_graphics = 0;
    y = 2;
 
    for (int i = 0; i < graphics_libraries.size(); i++)
    {
        if (i == selected_graphics) {
            wattron(graphics_win, COLOR_PAIR(4));
        }
        mvwprintw(graphics_win, y, 2, graphics_libraries[i].c_str());
        if (i == selected_graphics) {
            wattroff(graphics_win, COLOR_PAIR(4));
        }
        y++;
    }
    wrefresh(graphics_win);

    mvprintw(LINES - 2, 2, "Enter your name: ");
    refresh();

    char name[256];
    echo();
    getstr(name);
    noecho();

std::vector<std::pair<std::string, int>> scores;
std::string user_name(name);
scores.push_back(std::make_pair(user_name, 0));
for (int i = 0; i < 4; i++) {
    std::string name;
    int score = rand() % 101;
    switch (i) {
        case 0:
            name = "Aurelien";
            break;
        case 1:
            name = "Benjin";
            break;
        case 2:
            name = "Amaury";
            break;
        case 3:
            name = "God";
            break;
    }
    scores.push_back(std::make_pair(name, score));
}
y = 2;
for (const auto &score : scores)
{
    mvwprintw(scoreboard_win, y, 2, (score.first + ": " + std::to_string(score.second)).c_str());
    y++;
}
for (auto& score : scores) {
    if (score.first == user_name) {
        score.first = user_name;
        break;
    }
}
wrefresh(scoreboard_win);

int ch;
int highlight = 2;
int wait = 0;

std::string selected_game_library;
while ((ch = getch()) != 27 && wait != 1) {
    switch (ch) {
        case 'a':
            mvwchgat(games_win, highlight, 2, -1, A_NORMAL, 0, NULL);
            highlight--;
            if (highlight < 2) {
                highlight = games_libraries.size() + 1;
            }
            mvwchgat(games_win, highlight, 2, -1, A_REVERSE, 0, NULL);
            wrefresh(games_win);
            break;
        case 'z':
            mvwchgat(games_win, highlight, 2, -1, A_NORMAL, 0, NULL);
            highlight++;
            if (highlight > games_libraries.size() + 1) {
                highlight = 2;
            }
            mvwchgat(games_win, highlight, 2, -1, A_REVERSE, 0, NULL);
            wrefresh(games_win);
            break;
        case 'e':
            if (highlight >= 2 && highlight <= games_libraries.size() + 1) {
                selected_game_library = games_libraries[highlight - 2];
                wait = 1;
            }
            break;
        default:
            break;
    }
}

std::string selected_graphical_library;
while ((ch = getch()) != 27 && wait != 0) { // 27 is the escape key code
    switch (ch) {
        case 'a': // move selection up
            mvwchgat(graphics_win, highlight, 2, -1, A_NORMAL, 0, NULL);
            highlight--;
            if (highlight < 2) {
                highlight = graphics_libraries.size() + 1;
            }
            mvwchgat(graphics_win, highlight, 2, -1, A_REVERSE, 0, NULL);
            wrefresh(graphics_win);
            break;
        case 'z': // move selection down
            mvwchgat(graphics_win, highlight, 2, -1, A_NORMAL, 0, NULL);
            highlight++;
            if (highlight > graphics_libraries.size() + 1) {
                highlight = 2;
            }
            mvwchgat(graphics_win, highlight, 2, -1, A_REVERSE, 0, NULL);
            wrefresh(graphics_win);
            break;
        case 'e':
            if (highlight >= 2 && highlight <= graphics_libraries.size() + 1) {
               selected_graphical_library = graphics_libraries[highlight - 2];
               make_choice(selected_game_library, selected_graphical_library);
            }
            break;
        default:
            break;
}
    }
endwin();

return 0;
}