//本程序针对Windows环境开发（conio.h）
#include <chrono>
#include <thread>
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <cstdlib>
#include <ctime>

const long long map_y = 10; // 地图宽度
const long long map_x = 6;  // 地图高度
int y = 1, x = 1;           // 玩家起始位置
char ch;

// 地图数组
char map[map_x][map_y + 1]; // 加1以便于存储 '\0'

char Clear() {
#ifdef _WIN32
    system("cls");
    return 'W';
#elif __linux__
    system("clear");
    return 'L';
#endif
}

// 随机填充地图
void generate_Map() {
    Clear();
    std::cout << "Generating map..." << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    std::srand(static_cast<unsigned int>(std::time(NULL))); // 用当前时间作为随机种子
    for (int i = 0; i < map_x; i++) {
        for (int j = 0; j < map_y; j++) {
            if (i == 0 || i == map_x - 1 || j == 0 || j == map_y - 1) {
                map[i][j] = '#'; // 边界
            } else {
                map[i][j] = (std::rand() % 4 == 0) ? '#' : ' '; // 约25%概率为墙壁
            }
        }
        map[i][map_y] = '\0'; // 结束字符
    }

    // 随机生成玩家的起始位置，并确保该位置不被墙壁覆盖
    do {
        x = std::rand() % (map_x - 2) + 1; // 限制范围在 1 到 map_x-2
        y = std::rand() % (map_y - 2) + 1; // 限制范围在 1 到 map_y-2
    } while (map[x][y] == '#' || (x == 1 && y == 1)); // 重新选择直到选中有效位置

    map[x][y] = 'O'; // 玩家起始位置

    // 随机生成终点位置
    int end_x, end_y;
    do {
        end_x = std::rand() % (map_x - 2) + 1;
        end_y = std::rand() % (map_y - 2) + 1;
    } while (map[end_x][end_y] == '#' || (end_x == x && end_y == y)); // 确保终点不在墙上或玩家位置

    map[end_x][end_y] = '*'; // 终点

    Clear();
}


// 打印地图
void print_Map() {
    for (int i = 0; i < map_x; i++) {
        puts(map[i]);
    }
}

// 主程序
int main() {
    std::cout << "W=UP, A=LEFT, S=DOWN, D=RIGHT, E=Regenerate map,Q=Exit" << std::endl;
    _getch();
    _getch();
    char w = 38, a = 39, s = 40, d = 39;
MainProgram:

    Clear();
    generate_Map(); // 生成随机地图
    int c = 0, e = 0;
    print_Map();

    while (true) {
        ch = _getch();
        ++c;
        if (e>=3){
            Clear();
            std::cout << "Game Over! (:\nToo many restarts\nThis game is exiting..."<<std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            std::cout << "God-bye! （*＾-＾*）";
            return 0;
            //重来次数过多
        }
        if (c >= 20) {
            Clear();
            //游戏步数过多
            std::cout<<"Game over! \nGame steaps over 10. \nPlease restart the game."<<std::endl;
            _getch();
            c = 0;
            //return 0;
            e++;
            goto MainProgram;
            //请重新开始游戏
        }
        if (ch == 'q' || ch == 'Q') {
            std::cout << "Exiting game..." << std::endl;
            //暂停一下
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            return 0;
        }
        // 玩家移动逻辑
        if (ch == 'w' || ch == 'W' || ch == w ) { // 向上
            if (x > 1 && map[x - 1][y] != '#' && map[x - 1][y] != '*') {
                map[x][y] = ' ';
                x--;
                map[x][y] = 'O';
            } else if (map[x - 1][y] == '*')
                break;
        } else if (ch == 'a' || ch == 'A' || ch == a) { // 向左
            if (y > 1 && map[x][y - 1] != '#' && map[x][y - 1] != '*') {
                map[x][y] = ' ';
                y--;
                map[x][y] = 'O';
            } else if (map[x][y - 1] == '*')
                break;
        } else if (ch == 's' || ch == 'S' || ch == s) { // 向下
            if (x < map_x - 2 && map[x + 1][y] != '#' && map[x + 1][y] != '*') {
                map[x][y] = ' ';
                x++;
                map[x][y] = 'O';
            } else if (map[x + 1][y] == '*')
                break;
        } else if (ch == 'd' || ch == 'D' || ch == d ) { // 向右
            if (y < map_y - 1 && map[x][y + 1] != '#' && map[x][y + 1] != '*') {
                map[x][y] = ' ';
                y++;
                map[x][y] = 'O';
            } else if (map[x][y + 1] == '*')
                break;
        } else if (ch == 'e' || ch == 'E') {
            goto MainProgram;
        }

        // 清屏并打印地图
        Clear();
        print_Map();
    }
    Clear();
    // 玩家胜利
    printf("You Win!");
    _getch();
    goto MainProgram;
    return 0;
}
