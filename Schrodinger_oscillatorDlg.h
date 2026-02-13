
// Schrodinger_oscillatorDlg.h: файл заголовка
//

#pragma once
#include <vector>
#include <cmath>


// Диалоговое окно CSchrodinger_oscillatorDlg
class CSchrodinger_oscillatorDlg : public CDialogEx
{
	// Создание
public:
	CSchrodinger_oscillatorDlg(CWnd* pParent = nullptr);	// стандартный конструктор

	// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_POTENTIAL_PIT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


	// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


public:
	int k; //уровень энергии
	int k_max; //максимальное количество уровней энергии
	double ek;
	double R;
	double С1;
	double V01;
	double X01;
	double Sigma1;
	std::vector <double> phi; //фаза фи
	std::vector <double> energy; //энергия
	std::vector <double> wave; //волновая функция
	std::vector <double> z; //координата

	//фазовая функция
	void DrawFuncPhi(std::vector <double> phi, std::vector <double> e);
	void DrawFuncWave(std::vector <double> wave, std::vector <double> z);

	afx_msg void OnBnClickedOk();
	CButton KmaxK;
	afx_msg void OnBnClickedCheck1();
	CEdit k_max_control;
	afx_msg void OnEnChangek();
};



