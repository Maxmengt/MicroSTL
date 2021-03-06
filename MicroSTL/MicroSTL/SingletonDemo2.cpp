#include <string>
#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

class Singleton {
public:
	static Singleton *getInstance() {
		if( m_Instance == NULL ) {
			Lock();
			if( m_Instance == NULL ) {
				m_Instance = new Singleton();
			}
			UnLock();
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

	Singleton *singletonObj = Singleton::getInstance();
	cout << singletonObj->getTest() << endl;

	Singleton::destroyInstance();
	return 0;
}
