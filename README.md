Imię: Patryk <br>
Nazwisko: Kamela <br>
Tytuł projektu: Arkanoid <br>

Prosta gra zręcznościowa typu Arkanoid napisana w języku C++ z wykorzystaniem biblioteki graficznej SFML.

## 📖 Scenariusz
Twoim zadaniem jest sterowanie paletką i odbijanie piłki tak, aby zbić wszystkie cegiełki na planszy.
Każda cegiełka posiada **3 punkty życia**:
1. **Czerwona** (3 życia)
2. **Żółta** (2 życia)
3. **Zielona** (1 życie)

Po trzecim uderzeniu cegiełka znika. Jeśli piłka spadnie poniżej dolnej krawędzi ekranu – przegrywasz i wracasz do menu.

## 🎮 Funkcjonalności
* **Menu Główne:** Nawigacja klawiaturą (Nowa Gra, Wczytaj grę, Wyjście).
* **System Zapisu i Odczytu:** Możliwość zapisania postępu gry do pliku i wznowienia go później (nawet po ponownym uruchomieniu programu).
* **Pauza:** Możliwość zatrzymania rozgrywki w dowolnym momencie.
* **Fizyka:** Odbicia piłki od ścian, paletki i bloków.
* **Logika bloków:** Bloki zmieniają kolory w zależności od pozostałego życia.

## ⌨️ Sterowanie

| Klawisz | Akcja |
| :--- | :--- |
| **Strzałka Lewo / Prawo** | Poruszanie paletką |
| **P** | Pauza (Stop) / Wznowienie |
| **S** | Zapisz grę (Save) |
| **L** | Wczytaj grę (Load) |
| **ESC** | Powrót do Menu Głównego |
| **Enter** | Zatwierdzenie opcji w Menu |

## 🚀 Sposób uruchomienia

### Wymagania
* Visual Studio 2022 (lub inny kompilator C++).
* Biblioteka **SFML 2.5.1** (skonfigurowana w projekcie).
* System operacyjny Windows (gra korzysta z systemowej czcionki Arial).

### Instrukcja
1.  Otwórz projekt w Visual Studio.
2.  Upewnij się, że pliki `.dll` biblioteki SFML znajdują się w folderze z plikiem `.exe` (lub są poprawnie podlinkowane).
3.  Skompiluj i uruchom grę (Ctrl + F5).
4.  Plik zapisu `save.txt` utworzy się automatycznie w folderze gry po naciśnięciu klawisza **Z**.
