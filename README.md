# Thread-safe лічильник (C++17)

## Опис

Цей проєкт реалізує потокобезпечний лічильник (thread-safe counter) на C++17 з використанням C-інтерфейсу.

### Функціональність

* атомарне збільшення та зменшення значення
* безпечне читання значення
* скидання до нуля
* захист від переповнення (INT_MAX) та недоповнення (INT_MIN)

Усі операції є потокобезпечними.

---

## Збірка проєкту

### Вимоги

* CMake ≥ 3.14
* C++17 компілятор
* Visual Studio / GCC / Clang

### Збірка

```bash
cmake -B build
cmake --build build
```

### Запуск тестів

```bash
ctest --test-dir build
```

---

## Потокобезпечність

Використовується `std::atomic<int>`, що дозволяє:

* виконувати lock-free операції
* уникнути використання mutex
* забезпечити коректну роботу в багатопотоковому середовищі

Для оновлення значення застосовується compare-and-swap (CAS).

---

## Тестування

Використовується Google Test.

### Покриті сценарії:

* базові операції (increment / decrement / get / reset)
* багатопотокове збільшення
* переповнення (INT_MAX)
* недоповнення (INT_MIN)
* обробка NULL аргументів
* життєвий цикл (create / destroy)

---

## Очікуваний результат

```
100% tests passed
```

---

## Android Build

### Вимоги

* Android NDK
* CMake
* Ninja

### Збірка

```bash
export ANDROID_NDK_HOME=path_to_ndk
./scripts/build_android.sh
```

### Результат

```
dist/android/arm64-v8a/libcounter.so
dist/android/armeabi-v7a/libcounter.so
dist/android/x86_64/libcounter.so
```

---

## iOS Build

iOS збірка потребує macOS (Xcode + clang toolchain).

На Windows не підтримується.

---

## Структура проєкту

```
counter_project/
├── include/
│   └── counter.h
├── src/
│   └── counter.cpp
├── tests/
│   └── counter_test.cpp
├── scripts/
│   └── build_android.sh
├── CMakeLists.txt
└── README.md
```

---

## .gitignore (рекомендовано)

```
build/
dist/
```

---

## Примітки

* Функція `__counter_set_value_for_tests` використовується лише для тестування
* У production-версії її слід приховати або видалити

---

## Висновок

У проєкті продемонстровано:

* роботу з багатопоточністю в C++
* використання атомарних операцій
* написання юніт-тестів
* використання CMake для збірки
* крос-компіляцію під Android (NDK)
