#include "kmps.h"

namespace kmps {
    MemNode::MyTy * MemNode::operator[](Ty key) {
        return nullptr;
    }
    const MemNode::MyTy * MemNode::operator[](Ty key) const {
        return nullptr;
    }
    void MemNode::operator_delete() {
        
    }
    void MemNode::operator_delete_arr() { }
}