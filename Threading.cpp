// Threading.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <thread> 
#include <Windows.h> 

HANDLE Mutex; 

typedef struct Data {
    int num;
    long long int result;
} DATA, *MDATA;

DWORD WINAPI ThreadRealise(LPVOID lpParam) {
	for (size_t i = 1; i < floor(((MDATA)lpParam)-> num / 2); i++)
	{
		WaitForSingleObject(Mutex, INFINITY);
		((MDATA)lpParam)->result += pow((3), i) + pow(i, 2 * i);
		ReleaseMutex(Mutex);
	}
	return 0;
}

int main()
{
	MDATA MyDataArray;
	HANDLE HThread;
	HThread = CreateMutex(NULL, false, L"");
	int n = 0;
	std::cout << "n?\n";
	std::cin >> n;
	MyDataArray = (MDATA)malloc(sizeof(DATA));
	MyDataArray->result = n;
	int nDivTwo = floor(n / 2);
	MyDataArray->result = 0;
	HThread = CreateThread(NULL, 0, ThreadRealise, MyDataArray, 0, NULL);
	for (int i = nDivTwo; i <= n; i++) {
		WaitForSingleObject(Mutex, INFINITY);
		MyDataArray->result += pow((3), i) + pow(i, 2 * i);
		ReleaseMutex(Mutex);
	}
	WaitForSingleObject(HThread, INFINITY);
	std::cout << MyDataArray->result;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
