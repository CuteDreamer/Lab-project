#include <iostream>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include <string>

using namespace std;

void gotoxy(int x, int y);
void setup_console();
int gifts(char map[][107], int HEIGHT, int WIDTH);
int cout_map(char map[][107], int HEIGHT, int WIDTH);
void start_player(int playerX, int playerY, string player1, string player2);
void move_down(char map[][107], int& playerX, int& playerY, const string player1, const string player2, int* p_count);
void move_up(char map[][107], int& playerX, int& playerY, const string player1, const string player2, int *p_count);
void move_left(char map[][107], int& playerX, int& playerY, const string player1, const string player2, int* p_count);
void move_right(char map[][107], int& playerX, int& playerY, const string player1, const string player2, int* p_count);
void hideCursor();




enum direction { DOWN = 80, UP = 72, LEFT = 75, RIGHT = 77 };

enum color { green = 33, white = 39, black = 32 };



void ChangeColor(color color)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(consoleHandle, color);
}


void hideCursor()                                             // <summary> Эта функция прячет курсор </summary>
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);    
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void gotoxy(int x, int y) {                                   // <summary> Эта функция перемещает курсор в заданную позицию х у </summary> 
    COORD pos = { x, y };                                     // <param name = x> индекс столбца консоли для ячейки, от 0 до 107 </param>
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);          // <param name = y> индекс строки консоли для ячейки, от 0 до 47 </param>
    SetConsoleCursorPosition(output, pos);
}

void setup_console()                                             // <summary> Комплексная функция для настройки окна консоли </summary>
{
    srand(time(0));                                              // подключили рандом
    HWND consoleWindow = GetConsoleWindow();                     // Получаем дескриптор окна консоли     

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);             // <summary> Получаем разрешение экрана </summary>
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);            // <param name> Размеры по оси х или y;

    RECT r;                                                      // Магическим образом, путём заклинания CTRL + С - CTRL + V (порядок очень важен), Получаем размеры окна консоли.
    GetWindowRect(consoleWindow, &r);
    int width = r.right - r.left;
    int height = r.bottom - r.top;

    // Вычисляем новые координаты окна                               
    int x = (screenWidth - width) / 2 + 60;
    int y = (screenHeight - height) / 2 - 150;

    MoveWindow(consoleWindow, x, y, width, height, TRUE);        // <summary> И размещаем его по центру экрана 15,6 </summary>
    // <param names> дескриптор окна, новые координаты окна консоли по х у, новые размеры окна, если TRUE, то перерисовываем.

    system("mode con cols=107 lines=55");                        // <summary> Функция изменяет размеры консоли</summary>
                                                                 // <param name> размеры консольного окна на 107 столбцов и 49 строк </param name>
    hideCursor(); 
}

int gifts(char map[][107], int HEIGHT, int WIDTH)                // <summary> Функция размещает награды в случайных ячейках </summary>
                                                                 // <param names> принимаем двухмерный массив и его размеры </param names>
{

    int gifts = 0;                                               // счётчик гифтов
    while (gifts < 300) {
        int x = rand() % HEIGHT;
        int y = rand() % WIDTH;                                  // случайные координаты по х и у;
        if (map[x][y] != '#' && map[x][y] != 'O' && x < HEIGHT - 1 && y < WIDTH - 1 && x > 0 && y > 0) {    // тут проверка на размещение гифтов, чтобы они в стенах не генерились
            map[x][y] = '7';
            gifts++;
        }
    }
    
    return 0;
}

int cout_map(char map[][107], int HEIGHT, int WIDTH)             // <summary> Отрисовываем карту </summary>
{                                                                // <param names> принимаем двухмерный массив и его размеры </param names>
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)                          // выводим циклами карту на экран
        {
            if (map[i][j] == '7') {
                ChangeColor(color::black);
                cout << map[i][j];
                ChangeColor(color::green);
            }
            else {
                cout << map[i][j];
            }
            

        }
        cout << "\n";
    }
    return 0;
}


void start_player(int playerX, int playerY, string player1, string player2)    // <summary> Функция размещает игрока на стартовую позицию </summary>
{   
    ChangeColor(color::white);                                                                          // <param names> координаты игрока по х , у и две строки, которыми отрисовывается персонаж </param names>
    gotoxy(playerX, playerY);
    cout << player1;
    gotoxy(playerX, playerY + 1);
    cout << player2;
    ChangeColor(color::green);
}

void harvest(char map[][107], int *playerY, int *playerX, int *count)
{
    if (map[*playerY][*playerX] == '7') {
        map[*playerY][*playerX] = ' ';
        *count += 1;
    }
    else if (map[*playerY][*playerX + 1] == '7') {
        map[*playerY][*playerX + 1] = ' ';
        *count += 1;
    }
    else if (map[*playerY][*playerX + 2] == '7') {
        map[*playerY][*playerX + 2] = ' ';
        *count += 1;
    }
    else if (map[*playerY + 1][*playerX] == '7') {
        map[*playerY + 1][*playerX] = ' ';
        *count += 1;
    }
    else if (map[*playerY + 1][*playerX + 1] == '7') {
        map[*playerY + 1][*playerX + 1] = ' ';
        *count += 1;
    }
    else if (map[*playerY + 1][*playerX + 2] == '7') {
        map[*playerY + 1][*playerX + 2] = ' ';
        *count += 1;
    }
  
}

void move_down(char map[][107], int& playerX, int& playerY, const string player1, const string player2, int* p_count)    // <summary> Функция отвечает за движение вниз </summary>                                                                                                          
{          
                                                                                            // <param names> передаём массив, передаём оригиналы координат х и у, передаём персонажа </param names>
    if (map[playerY + 2][playerX] != '#' && map[playerY + 2][playerX + 1] != '#' && map[playerY + 2][playerX + 2] != '#') {



        gotoxy(playerX, playerY);
        cout << "   ";
        gotoxy(playerX, playerY + 1);                     // стираем предыдущее положение
        cout << "   ";

        playerY++;        // Обновляем координаты

        gotoxy(playerX, playerY);
        cout << player1;
        gotoxy(playerX, playerY + 1);                     // Рисуем новое положение персонажа
        cout << player2;
    }
    
}        

void move_up(char map[][107], int& playerX, int& playerY, const string player1, const string player2, int *p_count)      // <summary> Функция отвечает за движение вверх </summary>
{                                                                                                            // <param names> передаём массив, передаём оригиналы координат х и у, передаём персонажа </param names>
    if (playerY > 0 && map[playerY - 1][playerX] != '#' && map[playerY - 1][playerX + 1] != '#' && map[playerY - 1][playerX + 2] != '#') {




        gotoxy(playerX, playerY);
        cout << "   ";
        gotoxy(playerX, playerY + 1);
        cout << "   ";

        playerY--;

        gotoxy(playerX, playerY);
        cout << player1;
        gotoxy(playerX, playerY + 1);
        cout << player2;
    }
}

void move_left(char map[][107], int& playerX, int& playerY, const string player1, const string player2, int* p_count)     // <summary> Функция отвечает за движение влево </summary>
{                                                                                                             // <param names> передаём массив, передаём оригиналы координат х и у, передаём персонажа </param names>
    if (playerX > 0 && map[playerY][playerX - 1] != '#' && map[playerY + 1][playerX - 1] != '#') {
        

        gotoxy(playerX, playerY);
        cout << "   ";
        gotoxy(playerX, playerY + 1);
        cout << "   ";

        playerX--;

        gotoxy(playerX, playerY);
        cout << player1;
        gotoxy(playerX, playerY + 1);
        cout << player2;
    }
}

void move_right(char map[][107], int& playerX, int& playerY, const string player1, const string player2, int* p_count)    // <summary> Функция отвечает за движение вправо </summary>
{                                                                                                             // <param names> передаём массив, передаём оригиналы координат х и у, передаём персонажа </param names>
    if (map[playerY][playerX + 3] != '#' && map[playerY + 1][playerX + 3] != '#') {
        

        gotoxy(playerX, playerY);
        cout << "   ";
        gotoxy(playerX, playerY + 1);
        cout << "   ";

        playerX++;

        gotoxy(playerX, playerY);
        cout << player1;
        gotoxy(playerX, playerY + 1);
        cout << player2;
    }
}




int main()                                                                           // <summary> Даже не знаю зачем здесь это </summary>


{
    int count = 0;
   
    int playerX = 55;
    int playerY = 43;
    int playerX2 = 55;                                                               // координаты изначального положения игрока
    int playerY2 = 42;
    string player1 = "OOO";
    string player2 = "OOO";                                                          // обозначение самого игрока двумя строками
    const int WIDTH = 107;                                                           // размеры карты
    const int HEIGHT = 47;

    setup_console();

                        // сьём значений с клавиатуры, вернее задаём соответствия
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, color::green);                                                  // меняем цвета фона и текста


    char map[HEIGHT][WIDTH] = {                                                      // наверное это карта
        {"##########################################################################################################"},
        {"#              #    #         #              #         #         #         #    #         #    #         #"},
        {"#              #    #         #              #         #         #         #    #         #    #         #"},
        {"######    #    #    #    #    #    ######    ######    #    #    #    ######    #    #    #    #    #    #"},
        {"#         #    #         #    #    #    #                   #    #    #              #    #         #    #"},
        {"#         #    #         #    #    #    #                   #    #    #              #    #         #    #"},
        {"#    ######    ###########    #    #    #####################    #    #         ######    ###########    #"},
        {"#         #                   #    #         #              #         #              #                   #"},
        {"#         #                   #    #         #              #         ######         #                   #"},
        {"######    #####################    ######    #    ######    ###########         #    #####################"},
        {"#    #                             #              #    #    #                   #                        #"},
        {"#    #                             #              #    #    #                   #                        #"},
        {"#    ###########    ################    ###########    #    #    ###########    ###########    ###########"},
        {"#    #              #              #    #              #    #         #         #              #         #"},
        {"#    #              #              #    #              #    #         #         #              #         #"},
        {"#    #    #    ######    ######    #    #    ######    #    ######    #         #    #    ######    ######"},
        {"#    #    #         #         #    #    #         #    #    #         #    #    #    #         #         #"},
        {"#    #    #         #         #    #    #         #    #    #         #    #    #    #         #         #"},
        {"#    #    #    #    ######    #    ###########    #    #    #    #    ######    #    #    #    ######    #"},
        {"#    #    #    #              #                   #    #         #    #    #    #    #    #              #"},
        {"#    #    #    #              #                   #    #         #    #    #    #    #    #              #"},
        {"#    #    #####################    #    ######    #    ###########    #         #    #####################"},
        {"#         #                   #    #         #    #                   #              #                   #"},
        {"#         #                   #    #         #    #                   #              #                   #"},
        {"#    ######    ###########    #    #    ######    ##########################    ######    ###########    #"},
        {"#    #         #         #         #    #         #              #              #         #         #    #"},
        {"#    #         #         #         #    #         #              #              #         #         #    #"},
        {"#    #    ######    #    ################    ######    ######    ######         #    ######    #    ######"},
        {"#    #    #         #    #         #         #    #         #         #         #    #         #    #    #"},
        {"#    #    #         #    #         #         #    #         #         #    #    #    #         #    #    #"},
        {"#    #    ###########    #    #    #    ######    ######    ######    #    #    #    ###########    #    #"},
        {"#    #                   #    #    #              #    #         #         #    #                   #    #"},
        {"#    #                   #    #    #              #    #         #         #    #                   #    #"},
        {"#    #    ################    #    ################    ######    ################    ################    #"},
        {"#    #                   #    #              #    #    #                   #    #                   #    #"},
        {"#    #                   #    #              #    #    #                   #    #                   #    #"},
        {"###########    ######    #    ###########    #    #    ################         ######    ######    #    #"},
        {"#         #         #         #         #                             #              #         #         #"},
        {"#         #    #    #         #         #                             #              #    #    #         #"},
        {"######    #    #    ################    ######    #    ###########    ######    ######    #    ###########"},
        {"#         #    #         #              #    #    #              #    #              #    #         #    #"},
        {"#         #    #         #              #    #    #              #    #              #    #         #    #"},
        {"#    ######    ######    #    #    ######    #    ###########    #    #         ######    ######    #    #"},
        {"#                             #              #                   #         #                             #"},
        {"#                             #              #                   #         #                             #"},
        {"##########################################################################################################"}

    };

    gifts(map, HEIGHT, WIDTH);

    cout_map(map, HEIGHT, WIDTH);

    while (true) {

        start_player(playerX, playerY, player1, player2);

        if (_kbhit()) {

            int direct = _getch();                                                    //   берём ввод с клавиатуры
            if (direct == 224)
                direct = _getch();

            if (direct == direction::DOWN) {

                move_down(map, playerX, playerY, player1, player2, &count);
            }
            else if (direct == direction::UP) {

                move_up(map, playerX, playerY, player1, player2, &count);
            }
            else if (direct == direction::LEFT) {

                move_left(map, playerX, playerY, player1, player2, &count);
            }
            else if (direct == direction::RIGHT) {

                move_right(map, playerX, playerY, player1, player2, &count);

            }
        }
        harvest(map, &playerY, &playerX, &count);
        gotoxy(0, HEIGHT + 2);
        cout << "Level of your degradation = " << count;
    }


    return 0;




}
