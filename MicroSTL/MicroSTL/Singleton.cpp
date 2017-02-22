#include <string>
#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

class Number {
public:
	// 2. Define a public static accessor function in the class
	static Number *instance();
	static void setType(string t) {
		type = t;
		delete inst;
		inst = 0;
	}
	virtual void setValue(int in) {
		value = in;
	}
	virtual int getValue() {
		return value;
	}
protected:
	int value;
	// 4. Define all ctors to be protected or private
	Number() {
		cout << ":ctor: ";
	}
// 1. Define a private static attribute in the "single instance" class
private:
	static string type;
	static Number *inst;
};

string Number::type = "decimal";
Number *Number::inst = 0;

class Octal: public Number {
// 6. Inheritance can be supported, but static functions may not be overridden. The base class must be declared a friend of the derived class (in order to access the protected constructor).
public:
	friend class Number;
	void setValue(int in) {
		char buf[10];
		sprintf(buf, "%o", in);
		sscanf(buf, "%d", &value);
	}
protected:
	Octal() {}
};

Number *Number::instance() {
	if( !inst ) {
		// 3. Do "lazy initialization" (creation on demand) in the accessor function
		if( type == "octal" ) inst = new Octal();
		else inst = new Number();
	}
	return inst;
}

class Singleton {
public:
	static Singleton *getInstance() {
		if( m_Instance == NULL ) {
			m_Instance = new Singleton();
		}
		return m_Instance;
	}
	static void destroyInstance() {
		if( m_Instance != NULL ) {
			delete m_Instance;
			m_Instance = NULL;
		}
	}
	int getTest() {
		return m_Test;
	}
private:
	Singleton() {
		m_Test = 10;
	}
	static Singleton *m_Instance;
	int m_Test;
};

Singleton *Singleton::m_Instance = NULL;

int main()
{
	// Number  myInstance; - error: cannot access protected constructor
	// 5. Clients may only use the accessor function to manipulate the Singleton
	Number::instance()->setValue(42);
	cout << "value is " << Number::instance()->getValue() << endl;
	Number::setType("octal");
	Number::instance()->setValue(64);
	cout << "value is " << Number::instance()->getValue() << endl;

	Singleton *singletonObj = Singleton::getInstance();
	cout << singletonObj->getTest() << endl;

	Singleton::destroyInstance();
	return 0;
}
