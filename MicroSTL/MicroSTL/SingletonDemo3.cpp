#include <string>
#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

class Singleton {
public:
	static Singleton *getInstance() {
		return const_cast<Singleton*>(m_Instance);
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
	static const Singleton *m_Instance;
	int m_Test;
};

const Singleton *Singleton::m_Instance = new Singleton();

int main()
{

	Singleton *singletonObj = Singleton::getInstance();
	cout << singletonObj->getTest() << endl;

	Singleton::destroyInstance();
	return 0;
}
