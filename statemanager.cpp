#include "statemanager.h"

void StateManager::set(QString r, uint64_t v, bool a) {
    if(!hasRegister(r) || (!a && !_state[r].direct)) {
        throw std::invalid_argument("invalid register");
    }
    if(_representation) {
        QLabel* label = _representation->findChild<QLabel*>(r);
        if(label) {
            label->setText(toHex(v, w));
        }
    }
    _state[r].value = v;
}

void StateManager::addRegister(QString r, bool d) {
    _state[r] = {.value = 0, .direct = d};
}

bool StateManager::hasRegister(QString r) const {
    return _state.contains(r);
}

uint64_t StateManager::get(QString v, bool a) const {
    if(!hasRegister(v) || (!a && !_state[v].direct)) {
        throw std::invalid_argument("invalid register");
    }
    return _state[v].value;
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
    for(auto& kvp : _state.keys()) {
        set(kvp, 0, true);
    }
}
