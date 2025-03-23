#include "Actor.h"

Actor::Actor(char symbol, int x, int y, int hp, int maxHP, int armor, int strength, int dexterity, int sleepTime, Weapon* weapon)
    :m_symbol(symbol), m_Actx(x), m_Acty(y), m_hitPoints(hp), m_maxHitPoints(hp), m_armor(armor), m_strength(strength), m_dexterity(dexterity), m_sleepTime(sleepTime), m_weapon(weapon)
{
}
Actor::~Actor(){
    delete m_weapon;
}

char Actor::getSymbol() const {
    return m_symbol;
}
int Actor::getHitPoints()const{
    return m_hitPoints;
}
void Actor::changeHitPoints(int hp) {
    m_hitPoints = hp;
}
int Actor::getMaxHitPoints()const {
    return m_maxHitPoints;
}
void Actor::changeMaxHitPoints(int maxhp) {
    m_maxHitPoints = maxhp;
}
int Actor::getArmor()const{
    return m_armor;
}
void Actor::changeArmor(int armor) {
    m_armor = armor;
}
int Actor::getStrength()const{
    return m_strength;
}
void Actor::changeStrength(int strength) {
    m_strength = strength;
}
int Actor::getDexterity()const{
    return m_dexterity;
}
void Actor::changeDexterity(int dexterity) {
    m_dexterity = dexterity;
}
int Actor::getSleepTime()const {
    return m_sleepTime;
}
void Actor::changeSleepTime(int sleepTime) {
    m_sleepTime = sleepTime;
}
Weapon* Actor::getWeapon()const {
    return m_weapon;
}
void Actor::changeWeapon(Weapon* weapon) {
    m_weapon = weapon;
}
int Actor::getX() const {
    return m_Actx;
}
void Actor::changeX(int value) {
    m_Actx += value;
}
int Actor::getY() const {
    return m_Acty;
}
void Actor::changeY(int value) {
    m_Acty += value;
}

void Actor::setPosition(int x, int y) {
    m_Actx = x;
    m_Acty = y;
}