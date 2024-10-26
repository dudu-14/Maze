//���������Windows����������conio.h��
#include <chrono>
#include <thread>
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <cstdlib>
#include <ctime>

const long long map_y = 10; // ��ͼ���
const long long map_x = 6;  // ��ͼ�߶�
int y = 1, x = 1;           // �����ʼλ��
char ch;

// ��ͼ����
char map[map_x][map_y + 1]; // ��1�Ա��ڴ洢 '\0'

char Clear() {
#ifdef _WIN32
    system("cls");
    return 'W';
#elif __linux__
    system("clear");
    return 'L';
#endif
}

// �������ͼ
void generate_Map() {
    Clear();
    std::cout << "Generating map..." << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    std::srand(static_cast<unsigned int>(std::time(NULL))); // �õ�ǰʱ����Ϊ�������
    for (int i = 0; i < map_x; i++) {
        for (int j = 0; j < map_y; j++) {
            if (i == 0 || i == map_x - 1 || j == 0 || j == map_y - 1) {
                map[i][j] = '#'; // �߽�
            } else {
                map[i][j] = (std::rand() % 4 == 0) ? '#' : ' '; // Լ25%����Ϊǽ��
            }
        }
        map[i][map_y] = '\0'; // �����ַ�
    }

    // ���������ҵ���ʼλ�ã���ȷ����λ�ò���ǽ�ڸ���
    do {
        x = std::rand() % (map_x - 2) + 1; // ���Ʒ�Χ�� 1 �� map_x-2
        y = std::rand() % (map_y - 2) + 1; // ���Ʒ�Χ�� 1 �� map_y-2
    } while (map[x][y] == '#' || (x == 1 && y == 1)); // ����ѡ��ֱ��ѡ����Чλ��

    map[x][y] = 'O'; // �����ʼλ��

    // ��������յ�λ��
    int end_x, end_y;
    do {
        end_x = std::rand() % (map_x - 2) + 1;
        end_y = std::rand() % (map_y - 2) + 1;
    } while (map[end_x][end_y] == '#' || (end_x == x && end_y == y)); // ȷ���յ㲻��ǽ�ϻ����λ��

    map[end_x][end_y] = '*'; // �յ�

    Clear();
}


// ��ӡ��ͼ
void print_Map() {
    for (int i = 0; i < map_x; i++) {
        puts(map[i]);
    }
}

// ������
int main() {
    std::cout << "W=UP, A=LEFT, S=DOWN, D=RIGHT, E=Regenerate map,Q=Exit" << std::endl;
    _getch();
    _getch();
    char w = 38, a = 39, s = 40, d = 39;
MainProgram:

    Clear();
    generate_Map(); // ���������ͼ
    int c = 0, e = 0;
    print_Map();

    while (true) {
        ch = _getch();
        ++c;
        if (e>=3){
            Clear();
            std::cout << "Game Over! (:\nToo many restarts\nThis game is exiting..."<<std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            std::cout << "God-bye! ��*��-��*��";
            return 0;
            //������������
        }
        if (c >= 20) {
            Clear();
            //��Ϸ��������
            std::cout<<"Game over! \nGame steaps over 10. \nPlease restart the game."<<std::endl;
            _getch();
            c = 0;
            //return 0;
            e++;
            goto MainProgram;
            //�����¿�ʼ��Ϸ
        }
        if (ch == 'q' || ch == 'Q') {
            std::cout << "Exiting game..." << std::endl;
            //��ͣһ��
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            return 0;
        }
        // ����ƶ��߼�
        if (ch == 'w' || ch == 'W' || ch == w ) { // ����
            if (x > 1 && map[x - 1][y] != '#' && map[x - 1][y] != '*') {
                map[x][y] = ' ';
                x--;
                map[x][y] = 'O';
            } else if (map[x - 1][y] == '*')
                break;
        } else if (ch == 'a' || ch == 'A' || ch == a) { // ����
            if (y > 1 && map[x][y - 1] != '#' && map[x][y - 1] != '*') {
                map[x][y] = ' ';
                y--;
                map[x][y] = 'O';
            } else if (map[x][y - 1] == '*')
                break;
        } else if (ch == 's' || ch == 'S' || ch == s) { // ����
            if (x < map_x - 2 && map[x + 1][y] != '#' && map[x + 1][y] != '*') {
                map[x][y] = ' ';
                x++;
                map[x][y] = 'O';
            } else if (map[x + 1][y] == '*')
                break;
        } else if (ch == 'd' || ch == 'D' || ch == d ) { // ����
            if (y < map_y - 1 && map[x][y + 1] != '#' && map[x][y + 1] != '*') {
                map[x][y] = ' ';
                y++;
                map[x][y] = 'O';
            } else if (map[x][y + 1] == '*')
                break;
        } else if (ch == 'e' || ch == 'E') {
            goto MainProgram;
        }

        // ��������ӡ��ͼ
        Clear();
        print_Map();
    }
    Clear();
    // ���ʤ��
    printf("You Win!");
    _getch();
    goto MainProgram;
    return 0;
}
