#include <iostream>
#include "Prog1.h"

namespace Prog1 {
    

 


    CSR input() {
        CSR coord;
        int* help_row;
        try {
            int msize{0}, row{0};
            std::cout << "Enter size of matrix (format: row * column):" << std::endl;
            row = getNum<int>();
            coord.row = row;
            coord.col = getNum<int>();
            std::cout << "Enter number of elements != 0" << std::endl;
            msize = getNum<int>();
            coord.msize = msize;
            help_row = new int[msize];
            coord.arr_col = new int[msize]();
            coord.arr_row = new int[row + 1]();
            coord.arr_val = new int[msize]();
            coord.arr_row[0] = 0;
            
            for (int i = 0; i < coord.msize; i++) {
                
                std::cout << "Enter column coord (start with 0): " << std::endl;
                coord.arr_col[i] = getNum<int>();
                while (coord.arr_col[i] > coord.col || coord.arr_col[i] < 0) {
                    std::cout << "Incorrect! Repeat pls" << std::endl;
                    coord.arr_col[i] = getNum<int>();
                } 
                std::cout << "Enter row coord (start with 0): " << std::endl;
                help_row[i] = getNum<int>();
                while (help_row[i] > coord.col || help_row[i] < 0) {
                    std::cout << "Incorrect! Repeat pls" << std::endl;
                    help_row[i] = getNum<int>();
                }
                
                std::cout << "Enter value: " << std::endl;
                coord.arr_val[i] = getNum<int>();
            }

            for (int i = 0; i < coord.msize; i++) {
                for (int j = 0; j < coord.msize - 1; j++) {
                    if (help_row[j] > help_row[j + 1]) {
                        int tmp1 = help_row[j];
                        help_row[j] = help_row[j + 1];
                        help_row[j + 1] = tmp1;
                        
                        tmp1 = coord.arr_col[j];
                        coord.arr_col[j] = coord.arr_col[j + 1];
                        coord.arr_col[j + 1] = tmp1;
                        
                        tmp1 = coord.arr_val[j];
                        coord.arr_val[j] = coord.arr_val[j + 1];
                        coord.arr_val[j + 1] = tmp1;
                    }
                }
            }
            
            for(int i = 0; i < coord.row; i++){
                int count{0}; 
                for (int j = 0; j < coord.msize; j++) {
                    if(help_row[j] == i){
                        count++;
                    }
                }
                coord.arr_row[i + 1] = count;
            }

            for (int i = 0; i < coord.row; i++) {
                coord.arr_row[i + 1] += coord.arr_row[i];
            }
            delete[] help_row;

        }
        catch (...) {
            erase(coord);
            delete[] help_row;
            throw;
        }
        
        return coord;
    }



    void specialfunc(CSR& coord) {
        //���������� �� �����
        for (int i = 0; i < coord.row; i++) {
            for (int j = coord.arr_row[i]; j < coord.arr_row[i + 1]; j++) {
                for (int m = coord.arr_row[i]; j < coord.arr_row[i + 1] - 1; j++) {
                    if (coord.arr_col[m] > coord.arr_col[m + 1]) {
                        int tmp1 = coord.arr_col[m];
                        coord.arr_col[m] = coord.arr_col[m + 1];
                        coord.arr_col[m + 1] = tmp1;
                        int tmp2 = coord.arr_val[m] ;
                        coord.arr_val[m] = coord.arr_val[m + 1];
                        coord.arr_val[m + 1] = tmp2;
                    }
                }
            }
        }
        //�������� ��������� �� �������
        int count{ 0 };
        for (int i = 0; i < coord.row; i++) {
            if (coord.arr_row[i] == coord.arr_row[i + 1]) {
                continue;
            }
            int min = coord.arr_val[coord.arr_row[i]];
            int index = coord.arr_row[i];
            //����� ��������
            for (int j = coord.arr_row[i]; j < coord.arr_row[i + 1]; j++) {
                if (coord.arr_val[j] < min) {
                    min = coord.arr_val[j];
                    index = j;
                }
            }
            //���� ��������
            for (int j = coord.arr_row[i]; j < index; j++) {
                if (coord.arr_val[j] > min) {
                    for (int m = j; m < coord.msize - 1; m++) {
                        coord.arr_col[m] = coord.arr_col[m + 1];
                        coord.arr_val[m] = coord.arr_val[m + 1];
                    }
                    for (int m = i; m < coord.row; m++) {
                        coord.arr_row[m + 1] = coord.arr_row[m + 1] - 1;
                    }
                    count++;  
                }
            }  
        }
        int* tmp1 = new int[coord.msize - count];
        std::copy(coord.arr_val, coord.arr_val + coord.msize - count, tmp1);
        delete[] coord.arr_val;
        coord.arr_val = tmp1;
        int* tmp2 = new int[coord.msize - count];
        std::copy(coord.arr_col, coord.arr_col + coord.msize - count, tmp2);
        delete[] coord.arr_col;
        coord.arr_col = tmp2;
        coord.msize = coord.msize - count;
    }
    



    void erase(CSR& coord) {
        delete[] coord.arr_col;
        delete[] coord.arr_row;
        delete[] coord.arr_val;
        coord.col = 0;
        coord.row = 0;
        coord.msize = 0;
    }

   /* int** initMatr(int row, int col) {
        int** arr = new int* [row]();
        for (int i = 0; i < row; i++) {
            arr[i] = new int[col]();
        }
        return arr;
    }*/

    /*void erase(int** arr, int row) {
        for (int i = 0; i < row; i++) {
            delete[] arr[i];
        }
        delete[] arr;
    }*/

    /*void printMatr(int** arr, int row, int col) {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                std::cout << arr[i][j] << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }*/

    /*void made_and_print(CSR& coord) {
        int** matr = initMatr(coord.row, coord.col);
        for (int i = 0; i < coord.msize; i++) {
             
            int x{ 0 }, y{ 0 }, val{ 0 };
            val = coord.arr_val[i];
            x = coord.arr_col[i];
            int j;
            for (j = 0; j < coord.row + 1; j++) {
                if (coord.arr_row[j + 1] >= i + 1) {
                    break;
                }
            }
            y = j;
            matr[y][x] = val;
            std::cout << x << " " << y << " " << val <<std::endl;
        }
        printMatr(matr, coord.row, coord.col);
        erase(matr, coord.row);
    }*/


    int get_value(CSR& coord, int row, int col){
        for(int i = coord.arr_row[row]; i < coord.arr_row[row + 1]; i++){
            if(coord.arr_col[i] == col){
                return coord.arr_val[i];
            }
        }
        return 0;
    }


    void output(CSR& coord){
        for(int i = 0; i < coord.row; i++){
            for(int j = 0; j < coord.col; j++){
                int value = get_value(coord, i, j);
                std::cout << value << "\t";
            }
            std::cout << std::endl;
        }

    }



    
   
}



