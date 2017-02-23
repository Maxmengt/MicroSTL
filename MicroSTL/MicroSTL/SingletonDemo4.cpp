#include <string>
#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

class Singleton {
public:
	static Singleton *getInstance() {
		return m_Instance;
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

	class GC {
	public:
		~GC() {
			if( m_Instance != NULL ) {
				cout << "GC" << endl;
				delete m_Instance;
				m_Instance = NULL;
			}
		}
	};
	static GC gc;
};

Singleton *Singleton::m_Instance = new Singleton();
Singleton::GC Singleton::gc;

int main()
{

	Singleton *singletonObj = Singleton::getInstance();
	cout << singletonObj->getTest() << endl;

	return 0;
}
