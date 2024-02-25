# Cpp-sdl-adventure-game-template

# Task 8: World of Zuul

## Lärandemål
I denna uppgift är det tänkt att ni ska lära er
* Förstå och utveckla vidare på kod skriven av någon annan
* Repetera hashmaps, stränghantering, arv
* Programmera kreativt
* Dokumentera kod

## Uppgift: World of Zuul

Den här C++ uppgiften är inspirerad av dess motsvarande java uppgift. Så skumma gärna igenom den vanliga java uppgiften för att få ett hum om vad som ska göras i denna uppgift.

Den här uppgiften går ut på att ni ska skapa ett äventyrsspel i C++. Det går själv att välja om man vill göra spelet med SDL eller utan SDL. Så ifall du inte fått SDL att fungera hittills så är det okej! Projektet `/src/world_of_zuul` stöder båda alternativ. Du måste dock ha en fungerande matrisklass för att projektet ska kunna kompilera. Projektet använder sig av matris klassen för att skapa flera matriser av shared pointers som ska representera alla rum i spelet.

Följ nedanstående instruktion för att bygga projektet.

Börja med att lägga in `Matrix.cpp` i `src/world_of_zuul/src` och `Matrix.h` i `src/world_of_zuul/include`. 

skapa en mapp `build` i `src`. Gå in i mappen. 

Skriv sedan 
* `cmake ../world_of_zuul` om du vill bygga projektet med SDL.
* `cmake -DTERMINAL_ONLY=TRUE ../world-of-zuul/` om du vill bygga projektet utan SDL.

#### Felsökning

Ifall du inte får `-DTERMINAL_ONLY` flaggan att fungera kan du också stänga av SDL beroendet manuellt genom att
1. gå in i `world_of_zuul/include/properties.h` och lägga till en rad där det står `#define TERMINAL_ONLY`
2. gå in i `world_of_zuul/CMakeLists.txt` och på rad 9, ändra `OFF` till `ON`. 

### Kompilera spelet

Nu när du har byggfilerna för projektet skriver du `make` för att kompilera det.

#### Felsökning

Ifall den säger "Could not open room file!". Öppna `world_of_zuul/include/properties.h`. Ändra `INPUT_DIR` så att det blir filsökvägen till `world_of_zuul/src/rooms.txt`.

Ifall du får en massa matris-relaterade länknings errors, skulle jag rekommendera att skriva om din matrisklass så att alla implementationer ligger i `Matrix.h`. Så då har du en tom `Matrix.cpp` och en `Matrix.h` som innehåller implementationer av alla funktioner.

### Köra spelet

Starta spelet.
1. Om du kör med SDL kontrollerar du spelaren med `w`, `a`, `d`, `s`. Stäng av spelet genom att stänga SDL fönstret
2. Om du kör spelet utan SDL kontrollerar du spelaren genom att skriva `w`, `a`, `d` eller `s` och sedan trycka `ENTER`. Du kan köa upp rörelser genom att skriva flera bokstäver i rad och sedan `ENTER`. Du avslutar spelet genom att mata in `q`.

Om du kör projektet med SDL märker du att kartan visualiseras i fönstret, och textutdata printas i terminalen. När du har spelat spelet och utforskat vad det är man kan göra, börja kika på källkoden i `world_of_zuul/src` och `world_of_zuul/include`. Försök förstå hur spelet fungerar. Du behöver inte förstå allt, det borde räcka med en övergripande bild. Du borde dock försöka förstå dig på `parseRooms` funktionen, då du ska modifiera den i nästa uppgift. Se till att också läsa de kommentarer jag lagt i `gameManager.h` filen. De beskriver övergripande hur spelet är konstruerat.

### Uppgift 1: Ladda entities från fil

Betrakta filen `world_of_zuul/src/rooms.txt`. Inne här finner vi alla rum som `parseRooms` funktionen i `gameManager` läser in. Just nu dock läser den bara in tomma rutor och väggar för kartorna. Om du kollar i konstruktorn för `gameManager` ser man att det är där alla entities skapas. Vi vill ta bort den koden i kontsruktorn och ändra `parseRooms` så att den även kan läsa in entities på fil. Gör `ctrl+f` "TODO" i gameManager.cpp för att se vilka delar av koden du kommer behöva ändra.

### Uppgift 2: Speldesign

Du är nu mogen att kontemplera dig ett spelscenario mycket roligare än det exempelspel du blivit given. Oroa dig inte över hur det ska implementeras, utan fokusera på att komma på ett intressant spel som du skulle vilja spela. Det kan vara vilket spel som helst vars huvudfokus är att ha en spelare röra sig mellan platser. Se vanliga javauppgiften under `Exercise 6.1` för exempel.

Om du känner att du har brist på idèer skulle du också kunna besöka en hemsida som tex. [denna](https://letsmakeagame.net/game-idea-generator/).

Anteckna gärna ned vad din spelidè går ut på. Gör det för din egen skull. Alternativt rita ut kartan i förväg för hand eller med mjukvara.

### Uppgift 3: Implementera designen

När du har bestämt dig för spelet du skulle vilja skapa, så är det bara att implementera det! Utgå ifrån `world_of_zuul` projeket och ändra koden på vilket sätt du vill. Om du märker att din spelidè är för ambitiös eller komplicerad, var inte rädd att avgränsa designen medan du utvecklar spelet.

Ditt spel måste uppfylla följande krav:
1. Du får inte återanvända några rum från första versionen av spelet (Du får designa ett spel som tar plats på KTH, men du måste skapa dina egna rum, utgångar och entities då)
2. Alla rum, entities och utgångar *måste* läsas från fil
3. Det ska vara möjligt att vinna eller förlora spelet med rätt eller fel handling. När spelet är slut ska spelslingan avslutas och olika meddelanden ska skrivas ut beroende på om man vann eller förlorade. Tips: Sätt `quit` variablen till `true`.
4. Du måste skapa åtminstone två nya klasser som ärver av Entity och en klass som ärver av båda dessa två nyskapade klasser. Alla tre klasser ska användas i ditt spel. Klasserna kan tex. vara "Monster with shield", "Monster with sword", "Monster with sword and shield". Eller "Throwable item", "Consumable item", "Throwable and consumable item". Eller tex. "Minecart", "Chest", "Minecart with chest". Kom ihåg att använda virtual inheritance så att den klassen som ärver dubbelt fortfarande kan komma åt `Entity` funktionerna.
5. Spelet ska ha åtminstone 5 rum
6. Du måste lägga till en karta av ditt spel i `/docs/`. Det kan vara en scanning av en handskriven karta, eller skapad via mjukvara som tex. [diagrams.net](https://app.diagrams.net/).
7. Du måste lägga till följande information i `docs/README.md` filen:
   * kort beskrivning av spelet
   * Hur man vinner och förlorar
   * vilka klasser du har implementerat, och hur dessa används i spelet.
   * En överblick på vilka klasser som ärver av vilka
8. Du lägger till någon valfri funktionalitet till spelmotorn. Vad detta kan innebära är mycket upp till egen tolkning. Men här är några exempel för att ge dig idéer:
   * Genom hålla ned `shift` kommer spelaren nu hoppa istället för att gå. Så den skippar över en ruta och flyttas istället direkt 2 rutor framåt.
   * Spelaren kan genom piltangenterna skapa projektiler i respektive riktning som färdas tills de träffar en annan entity.
   * Det finns nu items i rum som spelaren kan plocka upp, lägga i sin inventory och sedan droppa i andra rum.
   * rum kan ha ett godtyckligt antal utgångar, istället för bara 4 stycken (norr, väst, öst, söder).
   * alla entities (inte bara spelaren) kan nu också byta rum genom att gå till kanten av ett rum.
   * flerspelarstöd med splitscreen (troligen rätt klurigt).
   * När spelet körs i SDL och spelaren byter rum, så går spelaren en ruta framåt i det nya rummet istället för att stanna kvar på kantrutan i det nya rummet. Fixa denna bugg! Obs: Detta sker inte om man kör projektet utan SDL.

Om du är osäker på ifall din idè till utökad funktionalitet är tillräcklig, fråga mig!

### Uppgift 4: Skapa dokumentation

För varje klass och metod du skapar ska du dokumentera den enligt javadoc standarden. Läs veckasn javauppgift för instruktioner.

Sammanfattningsvis behöver du följa följande regler:
1. Klasser ska ha en kommentar som innehåller
   * beskrivning av den övergripande syftet och egenskaperna av klassen
   * författarens namn, använd `@author`
2. Publika metoder ska ha en kommentar (inte nödvändigtvis privata) som innehåller
   * En beskrivning med funktionens syfte och funktionalitet
   * En beskrivning av det returnerade värdet. Använd `@return`
   * Beskrivning av varje indataparameter. Använd `@param`


Vad jag vet har inte C++ någon etablerad kommentarstandard på det vis Java har. 

Så jag tänker att vi bara använder javas standard
¯\\\_(\~\_\~)_/¯

## Tips

i `world_of_zuul/include/properties.h` finns många användbara konstanter som du kan ändra på
* Ändra fönsterstorleken
* Ändra spelarens färg
* Ändra väggarnas färg
* Ändra vilken fil som koden ska läsa rummen ifrån
* Ändra debugläge. Om `DEBUG` är 1 kommer en massa debugmeddelanden skrivas ut.
* `NORTH`, `WEST` `EAST` `SOUTH` och `STATIONARY` används för att beskriva rörelse för entities samt avgöra vilken utgång som ska väljas när en spelare går till nästa rum.

När du skapar dina klasser för flerarv borde du överväga att skriva `class Derived : virtual public Entity`. Genom att ärva virtuelt arv så förhindrar du att flera entities skapas när du har en klass som ärver från två klasser som i sig ärver av entity.

en std::shared_ptr är i princip en pekare som har direkt ägandeskap över ett objekt. En shared pointer kan bara äga ett objekt, flera shared pointers kan dock dela ägandeskap över samma objekt. Objektet som en shared pointer äger raderas endast när det inte finns några shared pointers kvar som inte längre äger det objektet.
