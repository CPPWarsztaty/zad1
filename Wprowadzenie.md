---
marp: true
---

# Konstruktor i Destruktor:

```
|                        |            Konstruktor           |             Destruktor            |
|:----------------------:|:--------------------------------:|:---------------------------------:|
|        Wywołanie       | automatycznie, tworzenie obiektu | automatycznie, destrukcja obiektu |
|      Przeciążenia      |                Tak               |                Nie                |
| Domyślna implementacja |                Tak               |                Tak                |
```

```cpp
class Foo {
public:
    Foo(int bar);
    Foo(float bar);
    ~Foo();
};

class Bar {
public:
    // ┬┴┬┴┤\(･ω├┬┴┬┴┬┴┬┴┤_･)├┬┴┬┴
    void baz();
};
```

---

# RAII - Resource Acquisition Is Initialization

Inicjowanie przy pozyskaniu zasobu. `ლ(ಠ_ಠ ლ)`


Bardziej intuicyjne nazwy:
- Constructor Acquires, Destructor Releases (CADRe)
- Scope-Bound Resource Management (SBRM)

---

# źle 

```cpp
void bad(const std::string& path, const std::string& data) {
    auto file = open(path);

    if (write(file, data) == -1) {
        throw std::runtime_error("Error while writing to file"); //(〃＞＿＜;〃)
    }

    close(file);
}
```
```cpp
void also_bad(const std::string& path, const std::string& data) {
    auto file = open(path);

    if (write(file, data) == -1) {
        close(file); // (￢_￢;)
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
    if (write(file, data) == -1) { // (¯ . ¯;)
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
        file = open(path);
    }

    ~FileGuard() {
        close(file);
    }

    void write(const std::string& data) {
        if (write(file, data) == -1) {
            throw std::runtime_error("Error while writing to file");
        }
    }
private:
    File* file;
};

void betterer(const std::string& path, const std::string& data) { //＼(＾▽＾)／
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

#  (－_－) zzZ

https://www.fluentcpp.com/2018/02/13/to-raii-or-not-to-raii/
