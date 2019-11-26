# zad1

Popraw program używając wzorca RAII

---

Konfiguracja w Visual Studio:
- Wybieramy folder projektu używając opcji `Open a local folder`
- W `Solution Explorer` szukamy pliku `CMakeLists.txt` i klikamy prawym przyciskiem myszy
- Następnie klikamy `Debug and Launch Settings` i `Default`
- W pliku `launch.vs.json` który się otworzy upewniamy się że mamy wszystkie pola uzupełnione zgodnie z przykładem:

```json
{
  "version": "0.2.1",
  "defaults": {},
  "configurations": [
    {
      "type": "default",
      "project": "CMakeLists.txt",
      "name": "CMakeLists.txt",
      "args": ["text-file"],
      "currentDir": "${workspaceRoot}"
    }
  ]
}
```

---

Konfiguracja w CLion:
- Używając opcji `Open` / `File/Open` otwieramy folder projektu
- W prawym górnym rogu rozwijamy menu znajdujące się obok ikonki młotka i klikamy `Edit Configurations...`
- Wypełniamy pole `Program arguments` i  ustawiamy `Working Directory` na główny katalog projektu
