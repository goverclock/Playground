#include <iostream>
#include <memory>
#include <string>
#include <list>
using namespace std;

int main() {
    int *pia = new int[10];
    int *pia2 = new int[10]();

    for(int i = 0; i < 10; i++) cout << pia[i] << endl;
    for(int i = 0; i < 10; i++) cout << pia2[i] << endl;
    
    return 0;
}
