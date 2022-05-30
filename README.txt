ICP-projekt 2020
Zobrazenie liniek hromadnej dopravy a sledovanie pohybu jednotlivých spojov na daných linkách.
Simulácia začína pri spustení vždy na čase 05:00:00 a postupuje chronologicky v čase.

Autori:
Martin Fekete xfeket00@stud.fit.vutbr.cz
Lukáš Perina xperin11@stud.fit.vutbr.cz

Zadanie:
Navrhněte a implementujte aplikaci pro zobrazení linek hromadné dopravy a sledování jejich pohybu.

Reprezentácia mapy a liniek:
Mapa a cestovný poriadok sú reprezentované CSV s vlastným formátom. Počas spustenia programu je skotrolovaná 
validita vstupných údajov v CSV súboroch (napr. či sa jednotlivé ulice na seba nadpájajú), následne je 
vykreslená mapa s autobusovými zastávkami a spustená simulácia hromadnej dopravy. V súbore lines.csv je
možné zmeniť maximálny počet autobusov z danej linky na trase zmenením posledného atribútu riadku. Časy odchodov 
zo zastávok sú uvedené pre prvý autobus danej linky, pre zvyšné autobusy sa počas behu programu dopočítajú.

Popis riešenia:
Po spustení programu prebehne parsovanie vstupných dát z pripojených .csv súborov.
Súbor lines.csv obsahuje informácie o linkách, roads.csv obsahuje informácie o jednotlivých cestách,
a stops.csv obsahuje informácie o autobusových zastávkach. Každý csv súbor obsahuje informácie potrebné pre 
vygenerovanie a vykreslenie jednotlivých objektov na mape.

Po parsovaní sa vykreslia zparsované údaje v podobe do QGraphicsScene. Ako prvé sa vykreslia cesty
a zastávky. Následne sa vygeneruje prvý autobus z každej linky. Dalšie autobusy pribúdajú do linky
s postupom času vždy v 6 minutovom rozptyle. Po vygenerovaní všetkých autobusov sa generovanie ukončí.

Animácia pohybu autobusov je aktívna od začiatku spustenia programu a je možné ju zrýchliť, spomaliť,
alebo nastaviť do počiatočného stavu pomocou tlačidla RESET.

Ak sa užívatel rozhodne definovať spomalenie alebo zatvorenie cesty na trase, môže tak urobiť pomocou
programových tlačidiel uvedených vo vrchnej časti programu. Pri definícií uzavrení cesty je nutné definovať
obchádzku tak, aby neprišlo k znefunkčnení ktorejkolvek linky tak, že nebude možné linku napojiť naspäť na cestu.
Pri zlej definícií obchádzky je preto užívatel varovaný na túto skutočnosť a obchádzka nieje vytvorená.
Po vytvorení obchádzky je následne aktualizovaná linka každého autobusu ktorý danou cestou prechádza tak,
aby mohol bezproblémovo pokračovať v jazde.