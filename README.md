# Реализация численного решения стационарного уравнения Шредингера для модели Кронига-Пенни

Данный проект представляет собой программную реализацию численного решения стационарного уравнения Шредингера для модели Кронига-Пенни с периодическим потенциалом в виде "гребёнки" дельта-функций.

$$
U(x) = V_0 \sum_{n=-N}^{N} \delta(x - a \cdot n)
$$

### Ввод
Через интерфейс пользователь задаёт:

| Параметр | Описание |
|----------|----------|
| $k$ | Номер уровня энергии (0,1,2,...) |
| $k_{\text{max}}$ | Максимальный отображаемый уровень |
| $R$ | Полуширина области интегрирования $[-R, R]$ |
| $C$ | Коэффициент гармонического потенциала |
| $v_0$ | Амплитуда дельта-пиков |
| $x_0$ | Период решётки (аналог $a$) |
| $\sigma$ | Ширина гауссиана (имитация дельта-функции) |

### Вывод
- График фазовой функции $\phi(E)$ с горизонтальными линиями для квантовых чисел $k$.
- График волновой функции $\Psi(x)$ вместе с потенциалом.

## **Среда разработки**
- Visual Studio 2022 с компонентами:
  - "Разработка классических приложений на C++"
  - "Пакет SDK для Windows 10/11"
  - "MSVC версии 141 - средства сборки C++"
  - "MSVC версии 141 - библиотеки C++"

## Результат работы программы

<img width="890" height="603" alt="image" src="https://github.com/user-attachments/assets/28e1d657-e867-4529-9b18-a17464c40208" />

**Рис. 1.** Фазовая $\phi(R,\varepsilon)$ и волновая $\psi_k(z)$ функции при $k=0$, $\varepsilon_k=2,59693$, $R=1$ и $v_0=0$.

<img width="890" height="603" alt="image" src="https://github.com/user-attachments/assets/67f476e2-2a2f-4f26-a662-0941850d2660" />

**Рис. 2.** Фазовая $\phi(R,\varepsilon)$ и волновая $\psi_k(z)$ функции при $k=1$, $\varepsilon_k=3,0000$, $R=4$ и $v_0=0$.

<img width="890" height="603" alt="image" src="https://github.com/user-attachments/assets/1244d605-db2c-47ed-98c8-f773602b4bda" />

**Рис. 3.** Фазовая $\phi(R,\varepsilon)$ и волновая $\psi_k(z)$ функции при $k=2$, $\varepsilon_k=5,0004$, $R=4$ и $v_0=0$.

<img width="890" height="603" alt="image" src="https://github.com/user-attachments/assets/cf6c25b2-16e8-4a10-836b-fc4e41a33799" />

**Рис. 4.** Фазовая $\phi(R,\varepsilon)$ и волновая $\psi_k(z)$ функции при $k=3$, $\varepsilon_k=7,0034$, $R=4$ и $v_0=0$.

<img width="890" height="603" alt="image" src="https://github.com/user-attachments/assets/787cc4c8-d7c3-4625-bb23-611e80dee54f" />

**Рис. 5.** Фазовая $\phi(R,\varepsilon)$ и волновая $\psi_k(z)$ функции при $k=4$, $\varepsilon_k=9,0193$, $R=4$ и $v_0=0$.

<img width="890" height="603" alt="image" src="https://github.com/user-attachments/assets/a0fdde03-7eb3-4be0-9f0a-4a61022f0009" />

**Рис. 6.** Фазовая $\phi(R,\varepsilon)$ и волновая $\psi_k(z)$ функции при $k=12$, $\varepsilon_k=25,0105$, $R=6$ и $v_0=0$.

<img width="890" height="603" alt="image" src="https://github.com/user-attachments/assets/13b11f97-1910-4e0b-80a1-0dd81755fb52" />

**Рис. 7.** Фазовая $\phi(R,\varepsilon)$ и волновая $\psi_k(z)$ функции при $k=2$, $\varepsilon_k=5,2920$, $R=4$ и $v_0=10$.

<img width="890" height="603" alt="image" src="https://github.com/user-attachments/assets/6d5d6742-10ff-40ba-8bc3-e1c2a29fb22b" />

**Рис. 8.** Фазовая $\phi(R,\varepsilon)$ и волновая $\psi_k(z)$ функции при $k=2$, $\varepsilon_k=5,7833$, $R=4$ и $v_0=30$.

<img width="890" height="603" alt="image" src="https://github.com/user-attachments/assets/f9a0d108-f2a8-425b-aad9-78a204a1bbd4" />

**Рис. 9.** Фазовая $\phi(R,\varepsilon)$ и волновая $\psi_k(z)$ функции при $k=2$, $\varepsilon_k=6,4279$, $R=4$ и $v_0=80$.

<img width="890" height="603" alt="image" src="https://github.com/user-attachments/assets/b27c0a28-0501-4f77-9a8e-9d3340ddcb3a" />

**Рис. 10.** Фазовая $\phi(R,\varepsilon)$ и волновая $\psi_k(z)$ функции при $k=2$, $\varepsilon_k=6,7575$, $R=4$ и $v_0=150$.

<img width="890" height="603" alt="image" src="https://github.com/user-attachments/assets/b7d3e722-c7d7-424b-a93a-227339c37f8a" />

**Рис. 11.** Фазовая $\phi(R,\varepsilon)$ и волновая $\psi_k(z)$ функции при $k=3$, $\varepsilon_k=7,0127$, $R=4$ и $v_0=30$.

<img width="890" height="603" alt="image" src="https://github.com/user-attachments/assets/3bfedf0c-7b03-49a6-ac59-6e363f9c44e3" />

**Рис. 12.** Фазовая $\phi(R,\varepsilon)$ и волновая $\psi_k(z)$ функции при $k=3$, $\varepsilon_k=7,0470$, $R=4$ и $v_0=100$.
 
## Литература
- Морозов О.А., Семин Ю.А., - “Моделирование физических процессов и систем. Часть 1: Учебно-методическое пособие.”
