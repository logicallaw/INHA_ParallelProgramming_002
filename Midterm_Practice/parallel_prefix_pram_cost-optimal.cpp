#include <iostream>
#include <cmath>

using namespace std;

int main() {
    // for (int i = 0; i < 4; i++) {
    //     for (int j = 1; j < 4; j++) {
    //         cout << (i*4+j) << " += " << (i*4+j-1) << "\n";
    //     }
    // }
    
    for (int i = 0; i < 1; i++) {
        for (int j = std::pow(2, i)+1; j <= 4; j++) {
            cout << (j*4-1) << " += " << (j - pow(2, i))*4 - 1 << "\n";
        }
    }
    // for (int i = 1; i < 4; i++) {
    //     for (int j = 0; j < 3; j++) {
    //         cout << (i * 4 + j) << " += " << (i*4+j-1) << "\n";
    //     }
    // }

    // for (int i = 0; i < ceil(log(8)); i++) {
    //     for (int j = pow(2, i); j < 8; j++) {
    //         cout << "reg_" << j << " += A[" << (j-pow(2, i)) << "]" <<"\n";
    //         cout << "A[" << j << "] = reg_" << j << "\n";
    //     }
    // }
}