#include "kmps.h"
#include <memory>
int main() {
    auto p = new kmps::MemNode;
    delete p;
    return 0;
}
