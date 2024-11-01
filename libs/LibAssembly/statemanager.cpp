#include "statemanager.h"

#include <QLabel>

void StateManager::set(QString r, uint64_t v, bool a) {
    if(_state.contains(r)) {
        if(!a && !_state[r].direct) {
            qDebug() << r;
            throw std::invalid_argument("invalid register");
        }
        _state[r].value = v;
    } else if(_aliases.contains(r)) {
        uint64_t orig = get(_aliases[r].src, a);
        set(_aliases[r].src, (orig & ~_aliases[r].mask) | (v << _aliases[r].shift), a);
    } else {
        qDebug() << r;
        throw std::invalid_argument("invalid register");
    }
    if(_representation) {
        QLabel* label = _representation->findChild<QLabel*>(r);
        if(label) {
            label->setText(toHex(v, w));
        }
    }
}

void StateManager::addRegister(QString r, bool d) {
    _state[r] = {.value = 0, .direct = d};
}

void StateManager::addAlias(QString r, QString src, uint64_t mask, int shift) {
    _aliases[r] = {.src = src, .mask = mask, .shift = shift};
}

bool StateManager::hasRegister(QString r) const {
    return _state.contains(r) || _aliases.contains(r);
}

uint64_t StateManager::get(QString v, bool a) const {
    if(_state.contains(v)) {
        if(!a && !_state[v].direct) {
            qDebug() << v;
            throw std::invalid_argument("invalid register");
        }
        return _state[v].value;
    } else if(_aliases.contains(v)) {
        return (get(_aliases[v].src) & _aliases[v].mask) >> _aliases[v].shift;
    } else {
        qDebug() << v;
        throw std::invalid_argument("invalid register");
    }
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
