#ifndef OBJECT_INCLUDED
#define OBJECT_INCLUDED
#include <string>
class GameObject
{
public:
	GameObject(char symbol, std::string name, int x, int y);
	virtual ~GameObject();
	std::string getName();
	int getX() const;
	int getY() const;
	char getObjectSymbol() const;
	virtual std::string callAction() const = 0;


private:
	char m_Symbol;
	std::string m_name;
	int m_Objx;
	int m_Objy;
};

#endif
