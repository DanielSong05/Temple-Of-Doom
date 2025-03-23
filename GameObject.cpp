#include "GameObject.h"

GameObject::GameObject(char symbol, std::string name, int x, int y)
	:m_Symbol(symbol), m_name(name), m_Objx(x), m_Objy(y)
{}
GameObject::~GameObject(){}

std::string GameObject::getName() {
	return m_name;
}
char GameObject::getObjectSymbol() const {
	return m_Symbol;
}
int GameObject::getX() const{
	return m_Objx;
}
int GameObject::getY() const{
	return m_Objy;
}