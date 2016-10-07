#include "kmps.h"
#include "utils.h"
#include <memory>
#include <functional>

int main() {
    auto noom = new ::kmps::MemNode();
    ::kmps::MemNode::operator delete(noom);
    delete noom;
    return 0;
}
