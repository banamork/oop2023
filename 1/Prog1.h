#ifndef OOPPROG1_PROG1_H
#define OOPPROG1_PROG1_H

#include <iostream>
#include <string>
#include <limits>
#include <cstring>

namespace Prog1 {
    struct CSR {
        int* arr_val = nullptr; // ��������
        int* arr_col = nullptr; // ������ ������
        int* arr_row = nullptr; // ���������� ������
        int col{ 0 }, row{ 0 }, msize{ 0 };
    };



    // ��������� ������� ����� ������ �����
   template<class T>
    T getNum(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max()) {
        T a;
        while(true) {
            std::cin >> a;
            if(std::cin.eof()) // ��������� ����� �����
                throw std::runtime_error("Failed to read number: EOF");
            else if(std::cin.bad()) // ���������� ��������������� ������ �������� ������
                throw std::runtime_error(std::string("Failed to read number: ") + strerror(errno));
            else if(std::cin.fail()) { // ������ ������ (������������ ������ �����)
                std::cin.clear(); // ������� ����� ��������� ������
                // ���������� ��� ������� �� ����� ������
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "You are wrong; repeat please!" << std::endl;
            }
            else if(a >= min && a <= max) // ���� ����� ������ � �������� ��������
                return a;
        }    
    }




    // ��������� �������
    CSR input();
    void specialfunc(CSR& coord);
    void erase(CSR& coord);
    //int** initMatr(int row, int col);
    //void erase(int** arr, int row, int col);
    //void printMatr(int** arr, int row, int col);
    //void made_and_print(CSR& coord);
    int get_value(CSR& coord, int row, int col);
    void output(CSR& coord);
}

#endif //OOPPROG1_PROG1_H
