# Labor 07

## FFT projekt

A projekt célja az, hogy alkalmazzuk, gyakoroljuk a tanult felhasználói felületek tervezési fázisait és fogalmait. A projekt célja az emberközpontú tervezési folyamat gyakorlati alkalmazása. A tervezési folyamatnak tartalmaznia kell a következő nagyobb fázisokat:

- Felhasználói kutatás és elemzés:
  - Problémafelvetés: Miről szól a projekt? Milyen valós problémára ad választ az alkalmazás? Mi a motiváció?
  - Célközönség meghatározása (Personák): Legalább 2 fiktív karakter (névvel, célokkal, fájdalompontokkal), akik az elsődleges célcsoportot reprezentálják.
  - Piackutatás: Legalább 2-3 már meglévő megoldás elemzése (erősségek, gyengeségek). Mik az erősségük/hátrányuk? Mivel lehetne kibővíteni őket? Milyen teljesen új ötlettel lehetne előállni?
    - Felhasználók véleményének begyűjtése a jelenlegi megoldásokról: kérdőívek, mélyinterjú potenciális fájdalompontok azonosítására
- Prototípus-készítés:
  - Fő funkciók (use case-k) felsorolása / diagram
  - Papíralapú vázlatok vagy digitális drótvázak (Lo-Fi), amelyek a szerkezeti felépítésre fókuszálnak, nem a dizájnra.
  - High-Fidelity prototípus: interaktív, kattintható prototípus készítése (ajánlott eszköz: [Figma](https://figma.com)). Döntsük el, milyen színeket (_color palette_), betűtípusokat (_typography_) és egyéb komponenseket használunk (például milyen fajta ikonokat - kitöltött vagy sem). Figyeljünk a kontrasztosságra és az olvashatóságra.
- Felületek értékelése:
  - A prototípus formálisabb értékelése. A felhasználók interfészhasználat közben szerzett aktuális tapasztalatait gyűjtjük össze (mélyinterjú, kérdőívek stb). A tesztelés során kapott visszajelzések alapján elvégzett módosítások dokumentálása.

A végső dokumentáció ezt a bejárt **tervezési folyamatot** kell ismertesse fázisonként, és bemutassa az elkészített prototípust (prototípusokat), kiemelve és részletezve a tervezési döntéseket (mi miért lett úgy tervezve, ahogy az a prototípusban szerepel). Személyes tapasztalat megosztása. További fejlesztési lehetőségek taglalása.

**Fontos:** A végső ötlet tényleges implementálása nem szükséges, a projektnek nem célja a kódolás/implementálás. A hangsúly a tervezési folyamatokon van!

A projektet egy PowerPoint bemutató keretén belül az utolsó labor órán kell bemutatni. A projektet lehet párban készíteni. Dokumentáció követheti a fent leírt sémát.

---

### Fájlkezelés

A fájlkezelés egy fontos része az alkalmazásfejlesztésnek, és a Qt lehetőséget kínál erre is. Fájlokat a Qt segítségével a következőképp lehet kezelni, a dokumentációban további részleteket és lehetőségeket találhatsz ezekkel kapcsolatosan:

1. [QFile](https://doc.qt.io/qt-6/qfile.html): fájlok olvasását és írását teszi lehetővé. Ez egy könnyen használható osztály, amely egyszerű módját kínálja a fájlok kezelésének. Például:

```c++
    QFile file("be.txt"); // ebben az esetben a fájt a build mappában kell legyen
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            // hiba esetén
            QMessageBox::warning(0, "Hiba", file.errorString());
            return;
    } else {
        QTextStream in(&file);
        QString myText = in.readAll();
        ...
        file.close();
    }

```

2. [QDir](https://doc.qt.io/qt-6/qdir.html): segítségével könnyedén navigálhatunk a mappastruktúrák között, fájlokat lehet listázni, keresni és módosítani a Qt keretrendszerben. Például:

```c++
    QDir dir(".");
    QStringList files = dir.entryList(QDir::Files);
    foreach (QString file, files) {
        qDebug() << "Fájl:" << file;
    }
```

3. [QFileDialog](https://doc.qt.io/qt-6/qfiledialog.html): ez egy előre elkészített dialógusablak, amely lehetővé teszi a felhasználók számára, hogy kiválasszák a fájlokat és mappákat a rendszeren. Például:

```c++
    QString filename = QFileDialog::getOpenFileName(nullptr, "Select a file", ".", "All files (*.*);;Text files (*.txt)");
    if (!filename.isEmpty()) {
        qDebug() << "Kiválasztott fájl:" << filename;
    }
```

### Qt menüsáv, menük és akciók

A Qt lehetővé teszi, hogy az alkalmazásainkat menüsávval gazdagítsuk. A menürendszer kulcsfontosságú elemei a menüsáv ([`QMenuBar`](https://doc.qt.io/qt-6/qmenubar.html)), a menük ([`QMenu`](https://doc.qt.io/qt-6/qmenu.html)) és az akciók ([`QAction`](https://doc.qt.io/qt-6/qaction.html)). Ezek az elemek lehetővé teszik az alkalmazások számára, hogy strukturált és könnyen navigálható felhasználói felületet biztosítsanak.

A menüsáv a felső részen helyezkedik el az alkalmazásablakban, és általában az alkalmazás főmenüit tartalmazza, például a "File", "Edit", "View" stb. menüket. A menüsávban található menük kattintható elemek, amelyek további almenüket vagy akciók sorait tartalmazhatják. A menük olyan listák, amelyek tartalmazhatnak más menüket vagy akciókat (például egy "File" menü tartalmazhatja az "Open File", "Save File As...", "Exit" stb. akciókat). Az akciók olyan feladatok vagy műveletek, amelyeket a felhasználó az alkalmazáson belül végezhet el, például fájl megnyitása, mentése, szöveg másolása stb.

Mindez kódban:

```cpp
MenuApp::MenuApp(QWidget *parent) : QMainWindow(parent) {
    QMenuBar *menuBar = new QMenuBar(this);
    setMenuBar(menuBar);
    QMenu *fileMenu = menuBar()->addMenu("File");
    QAction *openAction = fileMenu->addAction("Open");
    connect(openAction, &QAction::triggered, this, &MenuApp::myOpenFileHandler);
}
```

## Feladatok

1. Írjunk egy szöveges fájlkereső alkalmazást, megy egy adott könyvtárban megkeresi az összes állományt és visszatéríti azokat melyek tartalmazzák a keresett karakterláncot. Ha a felhasználó nem specifikálja (üres) a keresési karakterláncot, térítsük vissza az összes
   állományt. Az állományok nevét és méretét jelenítsük meg tábálázat formájában.

   - A könyvtár kiválasztásához használjuk [`QFileDialog`](https://doc.qt.io/qt-6/qfiledialog.html) osztályt illetve, a `QDir::currentPath()` függvényt az aktuális könyvtár lekéréséhez.
   - A könyvtárak kezelésére, illetve a könyvtár struktúra bejárásához használjuk a beépített [`QDir`](https://doc.qt.io/qt-6/qdir.html) és [`QDirIterator`](https://doc.qt.io/qt-6/qdiriterator.html) osztályokat.
   - A szöveges fájlok feldolgozásához, tartalmuk beolvasásához a [`QFile`](https://doc.qt.io/qt-6/qfile.html) és [`QTextStream`](https://doc.qt.io/qt-6/qtextstream.html) osztályokat használjuk. Mivel a fájlok feldolgozása sok időt vehet igénybe, a [`QProgressDialog`](https://doc.qt.io/qt-6/qprogressdialog.html) segítségével jelezzük a felhasználó felé, hány százalékát dolgoztuk fel a fájloknak, hol tartunk.
   - A keresés eredményét egy [`QTableWidget`](https://doc.qt.io/qt-6/qtablewidget.html) objektum segítségével jelenítjük meg, a fájlokról információkat (pl. méret) a [`QFileInfo`](https://doc.qt.io/qt-6/qfileinfo.html) segítségével kérhetünk le.
   - [Egy lehetséges megoldás, lépésről lépésre](http://doc.qt.io/qt-6.2/qtwidgets-dialogs-findfiles-example.html)
     ![findfiles-example](https://i.imgur.com/5CcXJON.png)

2. Készítsünk egy CSV állományokat kezelő alkalmazást! A felhasználó legyen képes kinyitni egy CSV állományt, amelyet a felületen egy [QTableWidget](https://doc.qt.io/qt-6/qtablewidget.html) objektum keretén belül megtekinthet.

   - Készítsünk az alkalmazásnak egy [QMenuBar](https://doc.qt.io/qt-6/qmenubar.html) menüsávot! Hozzunk létre egy [QMenu](https://doc.qt.io/qt-6/qmenu.html) menüt, amelyet nevezzünk `File`-nak! A menüben legyen egy [QAction](https://doc.qt.io/qt-6/qaction.html) menüpont: `Open File...`, mely gombnyomásra kinyit egy [QFileDialog](https://doc.qt.io/qt-6/qfiledialog.html) állománymegnyitó dialógust, amely csak CSV állományokat támogat (állítsuk be a filterét)!
   - Az ablak tartalmazzon egy [QTableWidget](https://doc.qt.io/qt-6/qtablewidget.html) táblázatot, amely megjeleníti a CSV adatait!
   - A CSV állomány kiválasztása után az alkalmazás olvassa be a CSV állományból az első sort és állítsa be aszerint a táblázat oszlopait! Ezután olvassa be az állományból az adatokat tartalmazó sorokat is, és tegye be őket a táblázatba!
   - A táblázat ne legyen módosítható!

3. Készítsünk egy motivációs idézeteket megjelenítő alkalmazást! Az alkalmazás indításakor olvassuk be az idézeteket egy állományból. Automatikusan válasszunk ki az idézetek közül egyet, és mutassuk meg azt a felhasználónak. Legyen a felületen egy gomb, amivel új idézetet generálhatunk. Vigyázzunk arra, hogy ne generáljuk ki ugyanazokat az idézeteket egymás után. Díszítsük fel az alkalmazásunkat stylesheetekkel. Példa idézetek találhatóak [ebben az állományban](https://gist.githubusercontent.com/robatron/a66acc0eed3835119817/raw/77493d3ddf69fbd9d69997e22e1a7c6c70c8bdf2/quotes.txt).
