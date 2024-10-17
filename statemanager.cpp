#include "statemanager.h"

void StateManager::set(QString r, uint64_t v) {
    if(!hasRegister(r)) {
        throw std::invalid_argument("invalid register");
    }
    if(_representation) {
        QLabel* label = _representation->findChild<QLabel*>(r);
        if(label) {
            label->setText(toHex(v, w));
        }
    }
    _state[r] = v;
}

void StateManager::addRegister(QString r) {
    _state[r] = 0;
}

bool StateManager::hasRegister(QString r) const {
    return _state.contains(r);
}

uint64_t StateManager::get(QString v) const {
    if(!hasRegister(v)) {
        throw std::invalid_argument("invalid register");
    }
    return _state[v];
}

void StateManager::setRepresentationWidget(QWidget* w) {
    _representation = w;
}

QWidget* StateManager::getReprentationWidget() {
    return _representation;
}

void StateManager::setWidth(int w) {
    this->w = w;
}

int StateManager::getWidth() {
    return w;
}

void StateManager::reset() {
    for(auto kvp : _state.keys()) {
        set(kvp, 0);
    }
}
