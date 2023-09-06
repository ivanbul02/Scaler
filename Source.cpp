#include <windows.h>
#include <iostream>

//Создаём прототип функции окна
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

char szProgName[] = "Progname"; //имя программы
char szText[] = "";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	HWND hWnd; //идентификатор окна
	MSG lpMsg; //идентификатор сообщения
	WNDCLASS w; //создаём экземпляр структуры WNDCLASS

	//И начинаем её заполнять
	w.lpszClassName = szProgName; //имя программы
	w.hInstance = hInstance; //идентификатор текущего приложения
	w.lpfnWndProc = WndProc; //указатель на функцию окна
	w.hCursor = LoadCursor(NULL, IDC_ARROW);
	w.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	w.lpszMenuName = 0; //меню пока не будет
	w.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //цвет фона окна
	w.style = CS_HREDRAW | CS_VREDRAW; //стиль - перерисовываемое по х и по у
	w.cbClsExtra = 0;
	w.cbWndExtra = 0;

	//Если не удалось зарегистрировать класс окна - выходим
	if (!RegisterClass(&w))
		return 0;

	//Создадим окно в памяти, заполнив аргументы CreateWindow
	hWnd = CreateWindow(szProgName, //Имя программы
		"Keyboard Code Viewer - 1.0", //Заголовок окна
		WS_OVERLAPPEDWINDOW, //Стиль окна - перекрывающееся
		100, //положение окна на экране по х
		100, //по у
		100, //размеры по х
		80, //по у
		(HWND)NULL, //идентификатор родительского окна
		(HMENU)NULL, //идентификатор меню
		(HINSTANCE)hInstance, //идентификатор экземпляра программы
		(HINSTANCE)NULL); //отсутствие дополнительных параметров

		//Выводим окно из памяти на экран
	ShowWindow(hWnd, nCmdShow);
	//Обновим содержимое окна
	UpdateWindow(hWnd);

	//Цикл обработки сообщений

	while (GetMessage(&lpMsg, NULL, 0, 0)) { //Получаем сообщение из очереди
		TranslateMessage(&lpMsg); //Преобразует сообщения клавиш в символы
		DispatchMessage(&lpMsg); //Передаёт сообщение соответствующей функции окна
	}
	return(lpMsg.wParam);
}

//Функция окна
LRESULT CALLBACK WndProc(HWND hWnd, UINT messg,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc; //создаём идентификатор контекста устройства

	//Цикл обработки сообщений
	switch (messg)
	{

		unsigned int key;

		//Обработка нажатия клавиши
	case WM_KEYDOWN:
		key = wParam; //Получаем код нажатой клавиши
		_itoa(key, szText, 10); //Преобразуем его в строку
		hdc = GetDC(hWnd); //Получаем контекст рисования
		std::cout<<hdc<<szText<<std::endl; //Выводим текст на экран
		
										 //Обработка нажатия клавиш
		switch (key) {
		case 83:

			std::cout<<hWnd<<"Ваше данные сохранены"<<""<<MB_OK<<std::endl;

			break;
			//Здесь могут быть и другие case
		}
		break;

		//сообщение выхода
	case WM_DESTROY:
		PostQuitMessage(0); //Посылаем сообщение выхода с кодом 0 - нормальное завершение
		break;

	default:
		return(DefWindowProc(hWnd, messg, wParam, lParam)); //освобождаем очередь приложения от нераспознаных
	}
	return 0;
}