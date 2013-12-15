#include "object.h"
#include <iostream>

using namespace std;

void Foo::print() {
    cout << "!!!" << endl;
}

Foo::Foo() : QObject() {

}
