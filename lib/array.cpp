#include <array.h>
#include <iostream>
#include <iomanip>
#include <type_traits>

template <typename T>
void printMatrix(const T **arr, int rows, int cols){
    for(int i=0; i < rows; i++){
        for(int j=0; j < cols; j++){
            if constexpr (std::is_floating_point_v(T)){
                std::cout << std::fixed << std::setprecision(2) << << arr[i][j] << " "; 
            }
            else{
                std::cout << std::setw(3) << arr[i][j] << " ";
            }
        }
    }
}