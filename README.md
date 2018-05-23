# PC-Tema2

Student: **George Neacșu**\
Grupă: **321CD**\
Email: **[george@neacsugeorge.com](mailto:george@neacsugeorge.com)**

# Detalii implementare

Am implementat structurile din PDF.\

Am creat niste functii pentru creare Header,
recunoastere tip query, creare question si 
in cele din urma o functie care combina un
Header cu un Question pentru a obtine un request
pentru serverul dns.

Ulterior am creat o structura Connection si
functii aceasta. In aceasta structura tin un
vector de string-uri cu IP-urile serverelor dns
precum si alte informatii utile pentru a transmite
date intre client si server. Avem functiile sendQuery
si getReponse care se ocupa de trimitere si primire
mesaje. Transferul se face pe TCP. Functia sendQuery
incearca sa se conecteze pe rand la fiecare server DNS
pana cand reuseste sa se conecteze la unul, iar apoi
trimite query-ul pastrand in structura Connection un
file descriptor pentru server-ul la care a reusit sa
trimita query-ul.

Urma mai apoi sa decodez raspunsurile de la server-ul
DNS dar nu mai am timp (bad time management). Am verificat
cu WireShark si pachetele query se trimit corect, sper sa iau
macar punctaj partial.

M-am apucat foarte tarziu de tema, cu cateva ore inainte de
deadline-ul hard si astfel nu am reusit sa o termin.
