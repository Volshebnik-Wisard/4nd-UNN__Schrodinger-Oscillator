
// Schrodinger_oscillator.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CSchrodinger_oscillatorApp:
// Сведения о реализации этого класса: Schrodinger_oscillator.cpp
//

class CSchrodinger_oscillatorApp : public CWinApp
{
private:
	Gdiplus::GdiplusStartupInput input;
	ULONG_PTR token;
public:
	CSchrodinger_oscillatorApp();

// Переопределение
public:
	virtual BOOL InitInstance();
	virtual BOOL ExitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CSchrodinger_oscillatorApp theApp;
