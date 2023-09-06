#include <windows.h>
#include <iostream>

//������ �������� ������� ����
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

char szProgName[] = "Progname"; //��� ���������
char szText[] = "";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	HWND hWnd; //������������� ����
	MSG lpMsg; //������������� ���������
	WNDCLASS w; //������ ��������� ��������� WNDCLASS

	//� �������� � ���������
	w.lpszClassName = szProgName; //��� ���������
	w.hInstance = hInstance; //������������� �������� ����������
	w.lpfnWndProc = WndProc; //��������� �� ������� ����
	w.hCursor = LoadCursor(NULL, IDC_ARROW);
	w.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	w.lpszMenuName = 0; //���� ���� �� �����
	w.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //���� ���� ����
	w.style = CS_HREDRAW | CS_VREDRAW; //����� - ���������������� �� � � �� �
	w.cbClsExtra = 0;
	w.cbWndExtra = 0;

	//���� �� ������� ���������������� ����� ���� - �������
	if (!RegisterClass(&w))
		return 0;

	//�������� ���� � ������, �������� ��������� CreateWindow
	hWnd = CreateWindow(szProgName, //��� ���������
		"Keyboard Code Viewer - 1.0", //��������� ����
		WS_OVERLAPPEDWINDOW, //����� ���� - ���������������
		100, //��������� ���� �� ������ �� �
		100, //�� �
		100, //������� �� �
		80, //�� �
		(HWND)NULL, //������������� ������������� ����
		(HMENU)NULL, //������������� ����
		(HINSTANCE)hInstance, //������������� ���������� ���������
		(HINSTANCE)NULL); //���������� �������������� ����������

		//������� ���� �� ������ �� �����
	ShowWindow(hWnd, nCmdShow);
	//������� ���������� ����
	UpdateWindow(hWnd);

	//���� ��������� ���������

	while (GetMessage(&lpMsg, NULL, 0, 0)) { //�������� ��������� �� �������
		TranslateMessage(&lpMsg); //����������� ��������� ������ � �������
		DispatchMessage(&lpMsg); //������� ��������� ��������������� ������� ����
	}
	return(lpMsg.wParam);
}

//������� ����
LRESULT CALLBACK WndProc(HWND hWnd, UINT messg,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc; //������ ������������� ��������� ����������

	//���� ��������� ���������
	switch (messg)
	{

		unsigned int key;

		//��������� ������� �������
	case WM_KEYDOWN:
		key = wParam; //�������� ��� ������� �������
		_itoa(key, szText, 10); //����������� ��� � ������
		hdc = GetDC(hWnd); //�������� �������� ���������
		std::cout<<hdc<<szText<<std::endl; //������� ����� �� �����
		
										 //��������� ������� ������
		switch (key) {
		case 83:

			std::cout<<hWnd<<"���� ������ ���������"<<""<<MB_OK<<std::endl;

			break;
			//����� ����� ���� � ������ case
		}
		break;

		//��������� ������
	case WM_DESTROY:
		PostQuitMessage(0); //�������� ��������� ������ � ����� 0 - ���������� ����������
		break;

	default:
		return(DefWindowProc(hWnd, messg, wParam, lParam)); //����������� ������� ���������� �� �������������
	}
	return 0;
}