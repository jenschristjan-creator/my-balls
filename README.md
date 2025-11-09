#Balls and Their Admirers 
Programmet er en lille visuel simulation bygget med Raylib. Ved opstart åbnes et vindue på 1000×1000 pixels, hvor en gruppe bolde bevæger sig som en sværm: én bold er “lederen”, og alle andre bolde følger den. Hver bold får tilfældig startposition, farve og størrelse, så udtrykket varierer for hver kørsel.

Lederen ændrer af og til retning når den rammer kanten af skærmen, mens tilhængerne hele tiden justerer deres bevægelse en smule mod lederens position. Når en bold forlader en kant af vinduet, dukker den op på den modsatte side, så bevægelsen fortsætter uden stop. Hver frame ryddes baggrunden, boldenes positioner opdateres, og de tegnes igen, hvilket skaber en glidende animation.

Adfærden styres af nogle få konstanter for vinduesstørrelse, antal bolde, hastighed og radius. Ideen er at vise, hvordan enkel lokal logik (“følg lederen”) kan give et samlet, dynamisk bevægelsesmønster, som er let at tilpasse ved at justere disse værdier.