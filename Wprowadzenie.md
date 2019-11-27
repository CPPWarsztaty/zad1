---
marp: true
---

# Jak będziemy pisać:

1. Nie używamy new, delete, malloc, free itp.
2. Nie używamy NULL
3. Używamy auto
4. Nie piszemy komentarzy z redundantnymi informacjami
5. Implementacja odseparowana od nagłówka
6. Nie wymyślamy koła na nowo

---

# new, delete, malloc, free itp.

```cpp
class Foo {
public:
    void bar() { throw std::exception(); }
};
```

```cpp
auto foo = new Foo();
foo->bar(); // (┛ಠ_ಠ)┛彡┻━┻
delete foo;
```

Używając powyższych operatorów i funkcji w C++ zwiększamy ryzyko błędów.

---

# NULL

W C++11 `NULL` został zastąpiony przez `nullptr`, by odróżnić nullowe wskaźniki od innych typów. W C `NULL` to po prostu `0`.

```cpp
void foo(int variable) {
    std::cout << "It's an integer: " << variable << std::endl;
}
void foo(int* variable) {
    std::cout << "It's a pointer: " << variable << std::endl;
}
```
(•ิ_•ิ)?
```cpp
foo(NULL);
foo(nullptr);
foo(0);
```

---

# auto

W standardzie C++11 zostało wprowadzone słowo kluczowe `auto`. Umożliwia ono automatyczną dedukcję typu, co znacznie poprawia czytelność kodu:

```cpp
std::unordered_map<std::string, boost::optional<int>> map;
std::unordered_map<std::string, boost::optional<int>>::const_iterator iterator = map.begin();

(＞﹏＜)
```



(つ✧ω✧)つ `auto iterator = map.begin();`

---

# nadmiarowe komentarze

```cpp
// this method removes key
void remove(const KeyType& key);
```

```cpp
// Key not found, throwing exception
throw std::runtime_error("Couldn't find key:" + key);
```
┐(￣ヘ￣;)┌
Po co? 

--- 

# Implementacja odseparowana od nagłówka

Odseparownie implementacji metod i funkcji do pliku .cpp przyśpiesza kompilacje i zwiększa czytelność (przynajmniej wg mnie)

--- 

# Nie wymyślamy koła na nowo
i korzystamy z dokumentacji. cppreference.com przyjacielem `(*＾ω＾)人(＾ω＾*)`

```cpp
const auto MAX_ITERATIONS = 100ul;
for (auto i = 0ul; i < data.size() < MAX_ITERATIONS ? data.size() : MAX_ITERATIONS; ++i) {
    process(data[i]);
}
```

⬇  ⬇⬇  ⬇⬇  ⬇⬇  ⬇⬇  ⬇⬇  ⬇⬇  ⬇

```cpp
const auto MAX_ITERATIONS = 100ul;                                                       
for (auto i = 0ul; i < std::min(data.size(), MAX_ITERATIONS); ++i)
    process(data[i]);
}
```
