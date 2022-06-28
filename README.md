# Praca-inzynierska
Sterownik silnika synchronicznego ze zmiennym momentem magnetycznym wirnika

Poniższe repozytorium zawiera materiały dotyczące budowy sterownika silnika. Docelowo silnik ma powstać na bazie zmodyfikowanego alternatora Magneti Marelli 14V/55A i udostępniać następujące metody sterowania:
- z wykorzystaniem czujników Halla
- z wykorzystaniem sygnału BEMF
- z pomiarem położenia przez enkoder optyczny
- przez pomiar prądów fazowych

Założenia projektowe sterownika:
- budowa modularna - płyta główna + 3 płyty z półmostkami
- separacja galwaniczna części sterowania i mocy
- sterowanie poprzez mikrokontroler Raspberry Pi RP2040
