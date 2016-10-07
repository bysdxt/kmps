#include "kmps.h"

namespace kmps {
    MemNode::Node * MemNode::createChild(KeyType Key) {
        return nullptr;
    }
    MemNode::KeyType MemNode::operator*() const {
        return KeyType();
    }
    const MemNode::Node * MemNode::operator[](KeyType key) const {
        return nullptr;
    }
    MemNode::Node * MemNode::operator[](KeyType key) {
        return nullptr;
    }
}