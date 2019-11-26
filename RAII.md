---
marp: true
---

# Konstruktor:

Metoda klasy/struktury, która jest automatycznie wywoływana podczas tworzenia obiektu. Może być przeciążana. W przypadku gdy programista nie napisał konstruktora do swojej klasy, C++ automatycznie tworzy domyślny konstruktor.

```cpp
class Foo {
public:
    Foo(int bar);
    Foo(float baz);
    Foo(int bar, float baz);
};

class Bar {
public:
    void baz();
};
```

---

# Destruktor:

Metoda klasy/struktury, która jest automatycznie wywoływana podczas destrukcji obiektu. Nie przyjmują żadnych argumentów więc nie mogą być przeciążane. Gdy destruktor nie został napisany, automatycznie utworzony zostanie domyślny.

```cpp
class Foo {
public:
    Foo(int bar);
    ~Foo();
};

class Bar {
public:
    void baz();
};
```

---

# RAII - Resource Acquisition Is Initialization

Inicjowanie przy pozyskaniu zasobu.

Bardziej intuicyjne nazwy:
- Constructor Acquires, Destructor Releases (CADRe)
- Scope-Bound Resource Management (SBRM)

---

# źle 

```cpp
void bad(const std::string& path, const std::string& data) {
    auto file = open(path);

    if (write(file, data) == -1) {
        throw std::runtime_error("Error while writing to file");
    }

    close(file);
}
```
```cpp
void also_bad(const std::string& path, const std::string& data) {
    auto file = open(path);

    if (write(file, data) == -1) {
        close(file);
        throw std::runtime_error("Error while writing to file");
    }

    close(file);
}
```

---

# lepiej

```cpp
struct FileGuard {
    FileGuard(const std::string& path) {
        file = open(path);
    }

    ~FileGuard() {
        close(file);
    }

    File* file;
};

void better(const std::string& path, const std::string& data) {
    FileGuard guard(path);
    if (write(file, data) == -1) {
        throw std::runtime_error("Error while writing to file");
    }
}

```

---

# jeszcze lepiej

```cpp

class FileGuard {
public:
    FileGuard(const std::string& path) {
        file = open(path.c_str(), O_RDONLY);
    }

    ~FileGuard() {
        close(file);
    }

    void write(const std::string& data) {
        if (write(file, data) {
            throw std::runtime_error("Error while writing to file");
        }
    }
private:
    int file;
};

void betterer(const std::string& path, const std::string& data) {
    FileGuard file(path);
    file.write(data);
}

```

---

# Przykładowe możliwości użycia RAII:
- otwieranie socketu
- pliku
- alokowanie pamięci
- blokowanie mutexa
- otwieranie połączenia do bazy danych
- ...

Zwracamy uwagę na metody i funkcje typu: 
open(), close(), init(), deinit(), lock(), unlock(), copy(), destroy() itp

---

# Do poczytania

https://www.fluentcpp.com/2018/02/13/to-raii-or-not-to-raii/
