#include "kmps.h"

namespace kmps {
    MemNode::Node * MemNode::operator[](KeyType key) {
        return nullptr;
    }
    MemNode::KeyType MemNode::operator*() const {
        return KeyType();
    }
    const MemNode::Node * MemNode::operator[](KeyType key) const {
        return nullptr;
    }
    void MemNode::operator_delete() {
        
    }
    void MemNode::operator_delete_arr() { }
    MemNode::Node & MemNode::operator()(KeyType Key) {
        return *this;
    }
}