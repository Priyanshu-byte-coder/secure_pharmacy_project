//HELLO
//secure pharmaceutical prescription system
#include <bits/stdc++.h>
using namespace std;
//2 types of the medicine otc and not otc
class Medicine{
    string name;
    float price;
    int quantity;
public:
    void display(){
        cout<<"Medicine name:"<<name<<"\n";
    }
};

class otc_med:public Medicine{
};
class non_otc_med:public Medicine{

};

int main() {

}