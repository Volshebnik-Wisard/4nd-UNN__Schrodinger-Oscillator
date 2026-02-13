
// Schrodinger_oscillatorDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include <algorithm>
#include <fstream>
#include <thread>
#include "Schrodinger_oscillator.h"
#include "Schrodinger_oscillatorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Диалоговое окно CSchrodinger_oscillatorDlg

CSchrodinger_oscillatorDlg::CSchrodinger_oscillatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_POTENTIAL_PIT_DIALOG, pParent)

	, k(4)
	, R(4)
	, k_max(4)
	, ek(0)
	, С1(1)
	, V01(80)
	, X01(0.05)
	, Sigma1(0.07)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSchrodinger_oscillatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_k, k);
	DDX_Text(pDX, IDC_R, R);
	DDX_Text(pDX, IDC_ek, ek);
	DDX_Text(pDX, IDC_k_max, k_max);
	DDX_Text(pDX, IDC_C, С1);
	DDX_Text(pDX, IDC_V0, V01);
	DDX_Text(pDX, IDC_X0, X01);
	DDX_Text(pDX, IDC_Sigma, Sigma1);
	DDX_Control(pDX, IDC_CHECK1, KmaxK);
	DDX_Control(pDX, IDC_k_max, k_max_control);
}

BEGIN_MESSAGE_MAP(CSchrodinger_oscillatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CSchrodinger_oscillatorDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK1, &CSchrodinger_oscillatorDlg::OnBnClickedCheck1)
	ON_EN_CHANGE(IDC_k, &CSchrodinger_oscillatorDlg::OnEnChangek)
END_MESSAGE_MAP()


// Обработчики сообщений CSchrodinger_oscillatorDlg

BOOL CSchrodinger_oscillatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CSchrodinger_oscillatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialogEx::OnSysCommand(nID, lParam);
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CSchrodinger_oscillatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		if (phi.size() > 0 || wave.size() > 0) {
			DrawFuncPhi(phi, energy); //фи от энергии
			DrawFuncWave(wave, z);
		}
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CSchrodinger_oscillatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}






double C;
double V0;
double X0;
double Sigma;
double R1;

const double pi = 3.1415926535;

template <typename T>
int signphi(T x) {
	if (x > 0) return 1;
	else if (x == 0) return 0;
	else return -1;
}

double Pow2(double x)
{
	return x * x;
}
double PotentialFunc(double z) {

	//for (int i = 0; i < KolToch; i++)
	//{
	//	SignalMass[i] = Ampl1 * exp(-(x1 - i) * (x1 - i) / (Sigma1 * Sigma1));
	//}

	if (Sigma == 0)
	{
		return C * Pow2(z);
	}
	else
	{
		for (int n = 1; n <= 10;)
		{
			return C * Pow2(z) + V0 * exp(-Pow2(X0 * n - z) / Pow2(Sigma));
			n++;
		}
	}

}

double PhaseFunc(double fi, double z, double e)
{
	double potential = PotentialFunc(z);
	return (Pow2(cos(fi)) * (potential - e) - Pow2(sin(fi)));
}

double RadiusFunc(double r, double e, double z, double fi)
{
	double potential = PotentialFunc(z);
	return r * (1 + potential - e) * cos(fi) * sin(fi);
}

double SolutionPF(int k)
{
	return -0.5 * pi * (2. * k + 1.);
}

//Рунге-Кутта
double Runge_Kutta(double R, double e)
{
	int numStep = 500;
	double step = 2 * R / numStep;

	std::vector<double> massR(numStep + 1);
	std::vector<double> massFi(numStep + 1);
	massFi[0] = pi / 2.;
	massR[0] = -R;

	for (int i = 0; i < numStep; i++)
	{
		double r = massR[i] + step;

		double k1 = PhaseFunc(massFi[i], r, e);
		double k2 = PhaseFunc(massFi[i] + step * k1 / 2, r + step / 2, e);
		double k3 = PhaseFunc(massFi[i] + step * k2 / 2, r + step / 2, e);
		double k4 = PhaseFunc(massFi[i] + step * k3, r + step, e);

		massFi[i + 1] = massFi[i] + step * (k1 + 2 * k2 + 2 * k3 + k4) / 6;
		massR[i + 1] = r;
	}

	return massFi[numStep];
}

//Рунге-Кутта в след точке
double Runge_Kutta(double lastfi, double z, double e, double step)
{
	double k1 = PhaseFunc(lastfi, z, e);
	double k2 = PhaseFunc(lastfi + step * k1 / 2, z + step / 2, e);
	double k3 = PhaseFunc(lastfi + step * k2 / 2, z + step / 2, e);
	double k4 = PhaseFunc(lastfi + step * k3, z + step, e);

	return lastfi + step * (k1 + 2 * k2 + 2 * k3 + k4) / 6;
}

std::vector<double> DoWaveFunc(double R, double ek, std::vector<double>& masZ)
{
	int numStep = 2000 * R;
	double step = 2 * R / numStep;

	std::vector<double> masR(numStep + 1);
	std::vector<double> masPsi(numStep + 1);
	masZ.clear();
	masZ = std::vector<double>(numStep + 1, 0);

	masR[0] = 1;
	masZ[0] = -R;
	masPsi[0] = 0;
	double fik = pi / 2;
	for (int i = 0; i < numStep; i++)
	{
		double zi = masZ[i] + step;
		fik = Runge_Kutta(fik, zi, ek, step);
		double k1 = RadiusFunc(masR[i], ek, zi, fik);
		double k2 = RadiusFunc(masR[i] + step * k1 / 2, ek, zi + step / 2, fik);
		double k3 = RadiusFunc(masR[i] + step * k2 / 2, ek, zi + step / 2, fik);
		double k4 = RadiusFunc(masR[i] + step * k3, ek, zi + step, fik);

		masR[i + 1] = masR[i] + step * (k1 + 2 * k2 + 2 * k3 + k4) / 6.0;
		masPsi[i + 1] = masR[i + 1] * cos(fik);
		masZ[i + 1] = zi;
	}

	return masPsi;
}


std::vector<double> DoPhaseFunc(double R, int k, std::vector<double>& masE)
{
	double solFi = SolutionPF(k + 1);


	double step = 0.004 / R;

	std::vector<double> listFi;
	std::vector<double> listE;

	for (int i = 0; ; i++)
	{
		double e = step * i;
		double valueFi = Runge_Kutta(R, e);
		listFi.push_back(valueFi);
		listE.push_back(e);

		if (valueFi <= solFi) break;
	}

	masE = listE;
	return listFi;
}

double MethodDevision(double R, double solFi, double fi_right, double e_right, double& fik) //fik - out
{
	double accuracy = 1e-8;
	double e_left = -1000, ek = 0;
	fik = 0;

	for (int iter = 0; iter < 2000; iter++)
	{
		ek = (e_right + e_left) / 2;
		fik = Runge_Kutta(R, ek);

		if (abs(fik - solFi) <= accuracy) break;
		else if (signphi(fik - solFi) == signphi(fi_right - solFi))
		{
			e_right = ek;
			fi_right = fik;
		}
		else e_left = ek;

	}

	return ek;
}


void CSchrodinger_oscillatorDlg::DrawFuncPhi(std::vector <double> phi, std::vector <double> e)
{
	//рисование модели
	CDC* dc = GetDlgItem(IDC_phase)->GetDC();
	HDC hdc = *dc;
	Gdiplus::Graphics gr(hdc); //gr будет рисовать на IDC_Object
	CRect obj_rect; //прямоугольник области рисования
	GetDlgItem(IDC_phase)->GetClientRect(&obj_rect); //получаем размеры прямоугольника
	Gdiplus::Bitmap myBitmap(obj_rect.Width(), obj_rect.Height()); //создаем битовый образ

	Gdiplus::Graphics* grr = Gdiplus::Graphics::FromImage(&myBitmap); //создаем дополнительный объект класса для рисования объектов
	grr->SetSmoothingMode(Gdiplus::SmoothingModeHighSpeed); //устанавливаем сглаживание в режиме наилучшего качества

	grr->Clear(Gdiplus::Color::WhiteSmoke);//очистим фон


	Gdiplus::Matrix mtx(1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);//создаем матрицу с осью у, направленной вверх

	double phi_max = *max_element(phi.begin(), phi.end()),
		phi_min = *min_element(phi.begin(), phi.end()),
		e_max = *max_element(e.begin(), e.end());

	mtx.Translate(obj_rect.Width() * 0.05, obj_rect.Height() * (phi_max + (0.04 * (phi_max - phi_min))) / (phi_max - phi_min), Gdiplus::MatrixOrderAppend);//перенос начала координат
	mtx.Scale(obj_rect.Width() / (1.05 * e_max), obj_rect.Height() / (1.04 * (phi_max - phi_min))); //изменяем масштаб
	grr->SetTransform(&mtx); //применяем преобразования


	//рисуем сетку координат
	Gdiplus::Pen pGrid(Gdiplus::Color::Color(0, 0, 0), 0.01); //ручка для основной сетки
	Gdiplus::Pen pSubGrid(Gdiplus::Color::Color(200, 200, 200), 0.005); //ручка для основной сетки


	//рисуем уровни энергий
	for (int i = 0; i <= k_max; i++) {
		int k = SolutionPF(i);
		grr->DrawLine(&pSubGrid, (Gdiplus::REAL)-0.1 * e_max, (Gdiplus::REAL)k, (Gdiplus::REAL)e_max, (Gdiplus::REAL)k);
	}

	//рисуем оси
	grr->DrawLine(&pGrid, (Gdiplus::REAL)(-0.05 * e_max), (Gdiplus::REAL)(0), (Gdiplus::REAL)(e_max), (Gdiplus::REAL)(0));
	grr->DrawLine(&pGrid, (Gdiplus::REAL)(0), (Gdiplus::REAL)(phi_max + 0.04 * (phi_max - phi_min)), (Gdiplus::REAL)(0), (Gdiplus::REAL)(phi_min));

	Gdiplus::REAL font_size = min((Gdiplus::REAL)(obj_rect.Width() / (2. * 20)), (Gdiplus::REAL)(obj_rect.Height() / (2. * 20)));
	//добавляем подписи
	Gdiplus::Font font(L"Arial", font_size, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel); //создаем шрифт
	Gdiplus::SolidBrush brText(Gdiplus::Color::Black); //кисть для шрифта
	grr->SetTextRenderingHint(Gdiplus::TextRenderingHintClearTypeGridFit); //сглаживание в стиле cleartype


	Gdiplus::Pen pObj(Gdiplus::Color::Color(222, 12, 98), e_max / 5000); //ручка для рисования объектов
	Gdiplus::SolidBrush brObj(Gdiplus::Color::Black); //ручка для рисования объектов
	//рисуем график
	int phi_size = phi.size();
	double step = 0.0005;
	for (int i = 0; i < phi_size - phi_size * step; i += phi_size * step) {
		grr->DrawLine(&pObj, (Gdiplus::REAL)e[i], (Gdiplus::REAL)phi[i], (Gdiplus::REAL)e[i + phi_size * step], (Gdiplus::REAL)phi[i + phi_size * step]);

	}

	//сбрасываем матрицу преобразования
	mtx.Reset();
	mtx.Translate(obj_rect.Width() * 0.05, obj_rect.Height() * (phi_max + (0.04 * (phi_max - phi_min))) / (phi_max - phi_min), Gdiplus::MatrixOrderAppend);//перенос начала координат

	grr->SetTransform(&mtx); //применяем преобразования



	//подпись оси x
	double x = 0;
	for (double i = -obj_rect.Width() * 0.1; i <= obj_rect.Width(); i += obj_rect.Width() * 0.1) {
		CString str;
		str.Format(_T("%.1f"), x);
		grr->DrawLine(&pGrid, (Gdiplus::REAL)(i + 23), (Gdiplus::REAL)(2), (Gdiplus::REAL)(i + 23), (Gdiplus::REAL)(-2));
		grr->DrawString(str, -1, &font, Gdiplus::PointF(i + 13, 0), &brText);
		x += 0.1 * e_max;
	}

	//подпись оси y
	double k2 = 0;
	//рисуем уровни энергий
	for (double i = 0; i <= k_max; i++) {
		k2 = SolutionPF(i);
		CString str;
		str.Format(_T("%.0f"), k2);
		CString str2;

		str2.Format(_T("k=%.0f"), i);
		if (k_max > 2) {
			grr->DrawString(str, -1, &font, Gdiplus::PointF(-20, (i * 45 * (log(k_max - 2) + 7) / k_max) + 10), &brText);
			grr->DrawString(str2, -1, &font, Gdiplus::PointF(obj_rect.Width() - 55, (i * 45 * (log(k_max - 2) + 7) / k_max) + 10), &brText);
		}
		else
		{
			grr->DrawString(str, -1, &font, Gdiplus::PointF(-20, (i * 200 / k_max) + 10), &brText);
			grr->DrawString(str2, -1, &font, Gdiplus::PointF(obj_rect.Width() - 55, (i * 200 / k_max) + 10), &brText);

		}
	}


	//рисовка из буфера
	gr.DrawImage(&myBitmap, 0, 0, obj_rect.Width(), obj_rect.Height());
	delete grr;//очистка памяти
}

void CSchrodinger_oscillatorDlg::DrawFuncWave(std::vector<double> wave, std::vector<double> z)
{
	//рисование модели
	CDC* dc = GetDlgItem(IDC_pits)->GetDC();
	HDC hdc = *dc;
	Gdiplus::Graphics gr(hdc); //gr будет рисовать на IDC_Object
	CRect obj_rect; //прямоугольник области рисования
	GetDlgItem(IDC_pits)->GetClientRect(&obj_rect); //получаем размеры прямоугольника
	Gdiplus::Bitmap myBitmap(obj_rect.Width(), obj_rect.Height()); //создаем битовый образ

	Gdiplus::Graphics* grr = Gdiplus::Graphics::FromImage(&myBitmap); //создаем дополнительный объект класса для рисования объектов
	grr->SetSmoothingMode(Gdiplus::SmoothingModeHighSpeed); //устанавливаем сглаживание в режиме наилучшего качества

	grr->Clear(Gdiplus::Color::WhiteSmoke);//очистим фон


	Gdiplus::Matrix mtx(1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);//создаем матрицу с осью у, направленной вверх

	double wave_max = *max_element(wave.begin(), wave.end()),
		wave_min = *min_element(wave.begin(), wave.end()),
		z_max = *max_element(z.begin(), z.end()),
		z_min = *min_element(z.begin(), z.end());

	//wave_max = max(abs(wave_max), abs(wave_min));
	mtx.Translate(obj_rect.Width() * 0.5, obj_rect.Height() * 0.5, Gdiplus::MatrixOrderAppend);//перенос начала координат
	mtx.Scale(obj_rect.Width() / (z_max - z_min), obj_rect.Height() / (2 * wave_max)); //изменяем масштаб
	grr->SetTransform(&mtx); //применяем преобразования

	Gdiplus::Pen pGrid(Gdiplus::Color::Color(50, 50, 50), z.back() / 10000); //ручка для основной сетки
	Gdiplus::Pen pGrid2(Gdiplus::Color::Color(50, 50, 50), 0.03); //ручка для основной сетки

	grr->DrawLine(&pGrid, (Gdiplus::REAL)0, (Gdiplus::REAL)-wave_max, (Gdiplus::REAL)0, (Gdiplus::REAL)+wave_max);
	grr->DrawLine(&pGrid, (Gdiplus::REAL)z_min, (Gdiplus::REAL)0, (Gdiplus::REAL)z_max, (Gdiplus::REAL)0);

	Gdiplus::Pen pObj(Gdiplus::Color::Color(90, 170, 160), z.back() / 80000); //ручка для рисования объектов
	Gdiplus::Pen pPits(Gdiplus::Color::Color(84, 0, 153), z.back() / 90000); //ручка для рисования объектов

	Gdiplus::SolidBrush brObj(Gdiplus::Color::Black); //ручка для рисования объектов


	for (int i = 0; i < wave.size() - 1; i++) {
		double potential = PotentialFunc(z[i]);
		double potential_next = PotentialFunc(z[i + 1]);

		grr->DrawLine(&pPits, (Gdiplus::REAL)z[i], (Gdiplus::REAL)potential, (Gdiplus::REAL)z[i + 1], (Gdiplus::REAL)potential_next);
		grr->DrawLine(&pObj, (Gdiplus::REAL)z[i], (Gdiplus::REAL)wave[i], (Gdiplus::REAL)z[i + 1], (Gdiplus::REAL)wave[i + 1]);

	}



	//рисовка из буфера
	gr.DrawImage(&myBitmap, 0, 0, obj_rect.Width(), obj_rect.Height());
	delete grr;//очистка памяти

}



void CSchrodinger_oscillatorDlg::OnBnClickedOk()
{
	double eps = 1e-3;

	if (KmaxK.GetCheck() == 1)
	{
		UpdateData(TRUE);
		k_max = k;
		UpdateData(FALSE);

	}

	if (k > k_max)
	{
		MessageBox(L"k не должен быть больше k_max!");
		return;
	}
	UpdateData(TRUE);
	R1 = R;
	C = С1;
	V0 = V01;
	X0 = X01;
	Sigma = Sigma1;

	BeginWaitCursor();
	phi = DoPhaseFunc(R, k_max, energy);

	//Получаем значение конца интервала, значение ФФ на конце интервала и решение ФФ
	double e_right = energy[energy.size() - 1];
	double fi_right = phi[phi.size() - 1];
	double solFi = SolutionPF(k);

	//С помощью метода половинного деления получаем значение энергии, удолетворяющее решению ФФ, и значение ФФ при такой энергии
	double fik = 0.0;
	ek = MethodDevision(R, solFi, fi_right, e_right, fik);


	//волновая функция
	wave = DoWaveFunc(R, ek, z);
	UpdateData(FALSE);
	DrawFuncPhi(phi, energy); //фи от E
	DrawFuncWave(wave, z); //пси от z


	//-----Вывод_в_файл-----
	std::fstream fout;
	fout.open("Phi_E.txt", std::ios::out);

	fout << "phi" << "\t" << "e" << std::endl;
	for (int i = 0; i < phi.size(); i++) {
		fout << phi[i] << "\t" << energy[i] << std::endl;
	}
	fout.close();


	fout.open("Ek_Z.txt", std::ios::out);
	fout << "\n\nek " << ek << "k " << k << std::endl;
	fout << "wave" << "\t" << "z" << std::endl;
	for (int i = 0; i < wave.size(); i++) {
		fout << wave[i] << "\t" << z[i] << std::endl;
	}
	fout.close();

	EndWaitCursor();
}



void CSchrodinger_oscillatorDlg::OnBnClickedCheck1()
{
	// TODO: добавьте свой код обработчика уведомлений
	if (KmaxK.GetCheck() == 1)
	{
		k_max_control.EnableWindow(FALSE);
	}
	else
	{
		k_max_control.EnableWindow(TRUE);
	}
}


void CSchrodinger_oscillatorDlg::OnEnChangek()
{
	if (KmaxK.GetCheck() == 1)
	{
		UpdateData(TRUE);
		k_max = k;
		UpdateData(FALSE);
	}
}
