Variant 2

---

## Code File

The main code file - [`main.cpp`](main.cpp).

The child 1 code file - [`child1.cpp`](child1.cpp).

The child 2 code file - [`child2.cpp`](child2.cpp).

## Example Usages

<details>
<summary>Click to expand</summary>

### Create Directories and Files
```cpp
createDirectoriesAndFiles();
```
Creates the directory structure `FILE11`, `FILE12`, `FILE13`, and `FILE21`, and copies files from `C:\source` to `FILE11` and `FILE21`.

### Resize Files
```cpp
resizeFiles();
```
Resizes specified files in `FILE11` and `FILE21` by truncating them to their first line.

### Create and Run Child Processes
```cpp
// Create pipes and run child processes
HANDLE hReadPipe, hWritePipe;
SECURITY_ATTRIBUTES saAttr;
saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
saAttr.bInheritHandle = TRUE;
saAttr.lpSecurityDescriptor = NULL;

CreatePipe(&hReadPipe, &hWritePipe, &saAttr, 0);

STARTUPINFO si1, si2;
PROCESS_INFORMATION pi1, pi2;
ZeroMemory(&si1, sizeof(si1));
si1.cb = sizeof(si1);
ZeroMemory(&pi1, sizeof(pi1));
ZeroMemory(&si2, sizeof(si2));
si2.cb = sizeof(si2);
ZeroMemory(&pi2, sizeof(pi2));

std::string cmdLine1 = "child1.exe " + std::to_string((intptr_t)hWritePipe);
CreateProcess(NULL, (LPSTR)cmdLine1.c_str(), NULL, NULL, TRUE, 0, NULL, NULL, &si1, &pi1);

std::string cmdLine2 = "child2.exe " + std::to_string((intptr_t)hReadPipe);
CreateProcess(NULL, (LPSTR)cmdLine2.c_str(), NULL, NULL, TRUE, 0, NULL, NULL, &si2, &pi2);

WaitForSingleObject(pi1.hProcess, INFINITE);
WaitForSingleObject(pi2.hProcess, INFINITE);

CloseHandle(pi1.hProcess);
CloseHandle(pi1.hThread);
CloseHandle(pi2.hProcess);
CloseHandle(pi2.hThread);
CloseHandle(hReadPipe);
CloseHandle(hWritePipe);
```
Creates pipes and runs `child1.exe` and `child2.exe` processes, passing the pipe handles as arguments.

### Read Result File
```cpp
std::ifstream inFile("result.txt");
std::string line;
while (std::getline(inFile, line)) {
    std::cout << line << std::endl;
}
inFile.close();
```
Reads and prints the contents of `result.txt`.

</details>

---

## Control Questions

<details>
<summary>Click to expand</summary>

1. **Яку функцію виконує `CreateProcess`?**
    - `CreateProcess` створює новий процес і його первинний потік. Функція виконує ініціалізацію нового процесу, завантажує в нього вказану програму і починає її виконання.

2. **Яку функцію виконує `OpenProcess`?**
    - `OpenProcess` відкриває існуючий процес і повертає дескриптор, який можна використовувати для доступу до процесу.

3. **Яку функцію виконує `ExitProcess`?**
    - `ExitProcess` завершує виконання поточного процесу і повертає код завершення системі операцій.

4. **Яку функцію виконує `WaitForSingleObject`?**
    - `WaitForSingleObject` очікує на сигнал від об'єкта синхронізації або завершення процесу/потоку протягом вказаного часу.

5. **В якій структурі записуються дескриптори процесу?**
    - Дескриптори процесу записуються в структурі `PROCESS_INFORMATION`.

6. **Якою функцією можна зробити “знімок” процесу?**
    - Функція `CreateToolhelp32Snapshot` створює знімок всіх процесів, потоків, модулів і використання пам'яті в системі.

7. **Як запускається програма паралельної обробки файлів?**
    - Програма паралельної обробки файлів запускається за допомогою створення декількох потоків або процесів, які працюють одночасно над різними частинами файлу або різними файлами.

8. **Яким чином успадковуються ресурси батьківського процесу?**
    - Ресурси батьківського процесу, такі як дескриптори файлів і каналів, можуть бути успадковані дочірніми процесами, якщо вони створені з прапором `bInheritHandles` встановленим в `TRUE`.

9. **Як встановити клас пріоритету процесу при його створенні?**
    - Клас пріоритету процесу можна встановити при його створенні за допомогою параметра `dwCreationFlags` функції `CreateProcess`, використовуючи значення, такі як `HIGH_PRIORITY_CLASS`, `IDLE_PRIORITY_CLASS`, `NORMAL_PRIORITY_CLASS`, або `REALTIME_PRIORITY_CLASS`.

10. **Що собою являють анонімні канали?**
    - Анонімні канали (anonymous pipes) - це засоби міжпроцесної взаємодії, які дозволяють передавати дані між процесами без використання іменованих об'єктів. Вони створюються за допомогою функції `CreatePipe` і використовуються для передачі даних між батьківським і дочірнім процесами.

### Поясніть роботу програми паралельної обробки файлів та обміну між процесами

Програма паралельної обробки файлів використовує декілька потоків або процесів
для одночасної обробки різних частин файлу або різних файлів. 
Це дозволяє значно підвищити продуктивність і скоротити час обробки. 
Обмін даними між процесами може здійснюватися за допомогою анонімних або іменованих каналів, 
спільної пам'яті, черг повідомлень або інших засобів міжпроцесної взаємодії. 
Наприклад, батьківський процес може створити анонімний канал і передати його дескриптори дочірнім процесам, 
які будуть використовувати цей канал для обміну даними.

</details>