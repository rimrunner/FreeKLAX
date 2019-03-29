/*

UNIX port of Klax game (1990, atari games), copyright Jari Sihvola 2019 (this code), unreleased

compile: g++ klax.cpp -lSDL2 -lSDL2_image -lSDL2_ttf -std=gnu++11 -o klax

compile for gperftools: g++ -lSDL2 -lSDL2_image -lSDL2_ttf -std=gnu++11 -DWITHGPERFTOOLS -lprofiler -g klax.cpp -o klax

--
//KYSYMYS: Tarvitaanko funktioita, jotka antaa luokan sis‰llˆst‰ tietoa? Ehk‰ niit‰ tarvitaan, koska luokan instanssit ovat nimettˆmi‰ vektori-olentoja, joten niihin kaiketi ei voi viitata kovin helposti???

//Vinkki: uudet framet voisi piirt‰‰ sivummaksi eik‰ alas, niin eiv‰t ole tiell‰ ainakaan

//Seuraavaksi?
-buginetsint‰coutit
-phase myˆs tekstiruutuun? tai tekstiruudun yl‰puolelle mahtuisi joku kyltti
-tarvitaanko oma vektori heitett‰ville tiilille vai riitt‰‰kˆ, jos tehd‰‰n se heitto kunnolla
(-liev‰ bugi-ep‰ily: kun yritt‰‰ t‰ytt‰‰ koko poolin tiilill‰, l‰htee niin yll‰tt‰v‰sti tiilej‰ pois, ett‰ her‰‰ ep‰ilys)
-pois erilliset tiilipalakuvat?
-pseudo3d:n suunnittelu. riitt‰‰kˆ amiga-versio, millainen olisi arcade? (palikkapinon logiikka)
-tileclass structiksi kun ei n‰kˆj‰‰n ole eik‰ tule constructoria eik‰ destructoria?
--
-roundit ja phaset, miten menee alkuper‰isess‰ peliss‰?
-nopeuden tai tiilten tulon kasvu - vaihtuu gameroundissa nopeammaksi?
---
-X:n tarkistus
-voisiko tilepoolin rendata vain, kun siin‰ tapahtuu muutoksia. Multicolour-tiili‰ pit‰‰ rendata koko ajan. Samoin kai pit‰isi aina clearata vain tietty osa ruudusta
-‰‰net
-hiscore -listan tarkistus, kuten siin‰ hiscore.cpp:ss‰
-demo-moodi
-vektorien capacityt, shufflessa list-v‰livaihe?
--
-konstruktorit c++ primerin mallin mukaiseksi?


-t‰h‰n tiedostoon on siirretty klax-vara17:sta kaikki kolme oleellista per‰tt‰ist‰ funktiota (uudempi check_pool on klax-bug.cpp:ss‰). T‰ss‰ bugia ei n‰yt‰ olevan
-funktioiden vertailua: is_win_string on sama molemmissa, string_analysis on sama molemmissa, check poolissa on jotain eroja - selitt‰isikˆ ne asioita
//KADONNUT (?) BUGI. Ilmestyi toisenkin kerran, mutta korjaantui, kun otin is_win_string -funktion klax_vara17.cpp:st‰. Muistikuviakin oli, ett‰ joku t‰mmˆinen selvitettiin.
-Bugi: j‰i m-palan pudottamisen j‰lkeen jumiin, kun oli alarivi mrrvy ja viel‰ y:n p‰‰ll‰ v. toinen jumitilanne: tiputti m:n kahden y:n p‰‰lle (kolumni 4/5, muut palat r ja c kolumnien 2/5 ja 5/5 pohjalla)
-bugi n‰ytt‰‰ esiintyv‰n tilanteissa, joissa rivin alussa on m
-bugi-string selvi‰‰ testist‰ sik‰li, ett‰ siit‰ lˆytyy se voittolauseke, mutta jostain syyst‰ koodi j‰‰ kuitenkin jumiin
-tile_tumble tuntuu tulevan useampia kertoja. j‰‰kˆ se jotenkin siihen looppiin jumiin, kun tile_tumblea kutsutaan uudestaan
-n‰ytt‰‰ vastaavan true jostain syyst‰, winrows on yksi (mutta ilmeisesti sama tulee wincolseilla). eli se antaa voittostringin string analysist‰... olisiko jotenkin niin, ett‰ se ei pyyhi sit‰ tilepoolia?
-Winrows on yksi, mutta winpoolissa ei n‰y mit‰‰n ...joten se ei poista sit‰ ja tile_tumble tulee aina uudestaan
--
-bugi: pohjalla oikealla sivulla pelkk‰ mgg pys‰ytti koko pelin (m pudotettiin vikana), samoin m:n pudotus kahden keskell‰ olevan v:n p‰‰lle pys‰ytti (molemmilla puolilla yksi pala, r ja g). T‰‰ pit‰is saada profiloinnilla helposti selville, ett‰ mihin funktioon se j‰‰ pyˆrim‰‰n.
-Miten n‰hd‰‰n mihin koodi j‰‰ pyˆrim‰‰n? Laitetaan ne merkit johonkin kohtaan. Mihin kohtaan?
-ei n‰yt‰ menev‰n tile tumbleen, menee check pooliin
-kutsutaan jostain syyst‰ uudestaan eli check_pool palauttaa truen, vaikkei pit‰isi
-kun on alariviss‰ mrr ja m:n p‰‰ll‰ kaksi r:‰‰, se lˆyt‰‰ columnin, muttei rivi‰ (tavallisilla paloilla lˆyt‰‰ molemmat). t‰m‰ vahvistaisi k‰sityst‰, ett‰ bugi tulee, jos m on rivin alussa.
--
-bugia ei esiinny klax_vara17 -tiedostossa. funktioista vain check_pool n‰ytt‰‰ eroavan.
-bugi katosi, kun klax_vara17:sta tuotiin oleelliset funktiot (3) t‰h‰n.
-t‰ydensin check_poolin vastaamaan uudempaa versiota ja silti bugi n‰ytt‰isi yh‰ puutuvan.
--
-jos winrows, wincols tai windias > 0, answer = true
-voisi olla ehk‰ joku bugi, joka tulee esiin vasta bugi-versiossa
-menee tile_tumbleen klax-bugissakin
-klax-bugissa winpool on tyhj‰ ensimm‰isell‰kin kerralla! silti wincoliin tulee 1. 


//Heitetyn tiilen rendautuminen...
-4:03 n‰kyy keskikolumniin heitettyj‰ tiili‰
-Hyv‰ uutinen: ongelma n‰ytt‰isi rajautuvan saman kolumnin tiileihin (t‰m‰ saattoi kyll‰ muuttua, kun n‰in arcade-videolta, miten hulppeasti ne lent‰v‰t). Eli heitt‰ess‰ pit‰isi l‰hinn‰ katsoa, ett‰ tiili asettuisi samalla kolumnilla olevien l‰hempien tiilien taakse jonossa (nyt se on niiden edess‰). T‰h‰nkˆ funktio, joka luo jonkun kopio-jonon ja palauttaa sen?
-Heitetty tiili laitetaan nyt push_frontilla ja se rendataan takana olevien tiilien eteen.
-Oliko j‰rkev‰‰ muuttaa vektori listiksi? Piti sitten laittaa se reverse_iterator. Vectorissakin olisi ollut insert push_frontin tilalle.
-Heitetty tiili laitetaan vektorin loppuun. Ja vektoria luetaan lopusta p‰in. Eli heitetty tiili rendataan ensin ja sen pit‰isi siis olla kauempana kuin aiemmat tiilet, jotta se n‰ytt‰isi hyv‰lt‰.
-Olisiko parempi, jos heitetty tiili laitettaisiin vektorin alkuun? T‰llˆin olisi hyv‰, ett‰ se asettuisi aiempien tiilien eteen? Keskim‰‰rin useimmat tiilet ovat kai kauempana, joten olisi kyll‰ parempi, jos se laitettaisiin vektorin eteen.

//vector/list
-laittaa uusia tiilej‰ sinne vektorin per‰lle
-poistaa tiilen (kun siepataan) yleens‰ p‰‰dyst‰
-reshufflessa laitetaan se sinne keskelle, mutta reshufflea ei tehd‰ niin usein

//Heittobugi1:
-Segfaulttasi tai corrupted double-link list
-segfaultin kohdalla j‰i throw_tileen, mutta yleens‰ meni pidemm‰lle
-korjaantuiko, kun iteraattorin ja luomisen v‰list‰ paikkaa vaihdettiin?

//kun vektori vaihtui listiksi
-piti vaihtaa ainakin reverse_iterator, kun ei voinut niit‰ aritmetiikkoja soveltaa niin hyvin iteraattoriin sitten

//Tiiliframet
-tiiliframe vaihtuu nyt aina, kun tiilej‰ liikutetaan. t‰t‰ voi hidastaa sdl:n timerin arvon perusteella helposti
-framet eiv‰t taida vaihtua nopeutuksessa
--kuten render_tile, switchit eri v‰reille, mutta renderfunctionille l‰hetet‰‰n animaation tarvitsemat tiedot ottaen huomioon annettu frame
-voisikohan render_tilen laittaa lopuksi main_looppiin tai muuten yksinkertaistaa
-Tiilet hihnalla (paitsi takaisin heitetty) rendautuu n‰tisti nyt, kun molemmat tiilivektoriloopit on laitettu kulkemaan takaperin
-j‰lkimm‰inen looppi ei liikuta tiili‰, mutta ilman sit‰ alkaa v‰lke, jos FPS on gamespeedi‰ nopeampi

//JERKING
-Nyt on ylimm‰r‰inen pseudo-frame 3.1, jolla ei myˆsk‰‰n liikuta. Jos tuo ei ole hyv‰ ja muu ei auta, pit‰isi ehk‰ tuplata gamespeed ja laittaa normaali framen vaihto joka toisella askelmalla ja pseudo-frame saisi yhden askeleen. Mutta pit‰isi ensin s‰‰t‰‰ nopeus kuntoon ja katsoa milt‰ se n‰ytt‰‰ sitten.

//Lopullinen grafiikka: renderfunction ja render_tile sis‰lt‰‰ ylim‰‰r‰isen ispool -parametrin, jota ei tarvita, jos tehd‰‰n omat spritet palikoiden eri asennoille. Samoin render_tiless‰ on paljon pelattu t‰ll‰ ispool-parametrill‰, mutta vanhemmissa tiedoston versioissa on se koodi oikeanlaisena.

29:61 on suhde palikoiden l‰himp‰n‰ ja kauimpana olevan framen sivun kokojen v‰lill‰ eli l‰hin frame on ~2.1 kertaa isompi

//Clipin rendaaminen
-Jos parametri-rect ei ole NULL eli se on annettu funktiokutsussa, sitten otetaan w ja h siit‰ source-neliˆst‰ destination neliˆˆn
-Nyt haasteena on viel‰ saada renderfunktioon animated_sprites.cpp -tiedoston tavoin destination-rectiin oikea koko, ettei se rendaa koko sprite-arkin kokoisena sit‰.
-Lis‰tty renderfunctioon source-rect ja koodi ei ilmeisesti hajonnut siit‰. Sen avulla voi m‰‰ritell‰ sourcen koon.

Enn‰tyslista
-https://en.wikipedia.org/wiki/Setuid


//Mit‰ voisi implementoida tai huomioida jossain vaiheessa:
-Kaksinpeli on Amigalla toteutettu niin, ett‰ grafiikka on samankokoinen. Yksinpeliss‰ on puolet tyhj‰‰ sivuilla. N‰in kannattaa menetell‰ t‰ss‰kin.
-voisiko katsoa jossain vaiheessa, miten tuolle vektorille varataan muistitilaa elementeille ja pit‰isikˆ se asettaa itse
-voisi myˆs pohtia sit‰, mit‰ toimintoja sill‰ tehd‰‰n, ett‰ olisiko list tai deque sittenkin parempia
-Voisiko eri main-loopin kountterit korvata yhdell‰, jos k‰ytet‰‰n sit‰ kikkaa, ett‰ otetaan ne viimeiset numerot

--
Opittua:
-Kun valitaan kontaineria, voi ensin kysy‰, pit‰‰kˆ sen s‰ilytt‰‰ j‰rjestys. https://stackoverflow.com/questions/471432/in-which-scenario-do-i-use-a-particular-stl-container
-Miten rangen voi tehd‰ ilman else if -puita (framejen lasku contile -funktiossa)
-Pistelaskun bughunt: Jos joku prosessi ei mene loppuun, kaikki prosessin mahdollisesti keskeytt‰v‰t if-lauseet pit‰‰ kokeilla, ett‰ auttaako niiden poisto. Ne voivat olla ongelma, vaikka niiden pit‰isi p‰te‰ vasta prosessin loputtua. If-lauseiden poisto on usein hyvin nopeasti kokeiltu.
-Kesti kauan huomata, ett‰ ongelma oli vektorin-luku-loopissa. T‰m‰n olisi kai huomannut heti debuggeria k‰ytt‰m‰ll‰, ett‰ se koodi j‰‰ siihen looppiin pyˆrim‰‰n.
-Debuggerilla seuraamalla olisi kai lˆytynyt nopeasti ongelma, kun alkoi laittaa koodia ihan v‰‰r‰‰n kohtaan (pudotettaviin tiileihin, kun piti laittaa putoaviin tiileihin) 
-Vaikka oli varoitettu asiasta, ei tajunnu tuota, ett‰ tuli vektori-iteraattori-looppin laitettua itse vektorin elementtirakenteen muutosta. Aina kun tekee vektoriloopin, pit‰‰ katsoa, muokataanko (esim poistetaan tai lis‰t‰‰n) siin‰ elementtien m‰‰r‰‰, se tapahtuu hyvin usein. Samoin viel‰ yksi variaatio ongelmasta: Jos luot elementin ja teet siihen kohdistuvalla iteraattorilla jotain, tee ensin se luonti ja sitten iteraattori
-Jos v‰h‰nk‰‰n isompi looppien rykelm‰ tai no ehk‰ mik‰ tahansa yksitt‰inen looppi tehd‰‰n, niin testataan heti ja testataan aina vaihevaiheelta kaikki loopit
-Tarkat selitykset omiin funktioihin ihan vaan joka riville, etenkin jos on jotain looppirykelm‰‰ tai muuta hankalaa, niin bugien etsint‰ on sitten paljon helpomaa. Jos kirjoittaa loopin eik‰ ole selityksi‰, sit‰ on vaikea tajuta myˆhemmin.
-vektorilla voi monistaa nimettˆmi‰ olioita omatekem‰st‰ luokasta, mutta pit‰‰ tehd‰ ensin yksi instanssi, joka syˆtet‰‰n push_back -komentoihin. T‰ss‰ t‰ytyy muistaa, ett‰ jokainen instanssi on sitten samanlainen (kopio alkuper‰isest‰) ja sen takia ei voi laittaa luokan konstruktoriin mit‰‰n randomisaattoria, koska se vaikuttaa vain siihen instanssiin, josta loput kopioidaan
-Kun luodaan jotain rendausfunktioita, niin pit‰‰ katsoa, ett‰ ne ei jatkuvasti multiploidu ne objektit, mit‰ siell‰ luodaan (textrend-funktiosta puuttui ne vapautusk‰skyt)
-Joku virhe tapahtui tuossa, ett‰ joku vanha buginen funktio oli p‰‰tynyt k‰yttˆˆn uudestaan. Vaikea sanoa, mit‰ tapahtui, mutta t‰m‰n kanssa pit‰isi olla varovainen.

--

Ei tarvitse sit‰ arrayta hihnalla olevista palikoista. Sijainnit saa otettua j‰lkik‰teenkin jos niit‰ tarvitsee pistelaskuun

Mites t‰m‰ palikoiden hallinta menee? 
-sijainti (monesko rivi plus Y-sijainti pikselein‰) ja v‰ri (sis. jokeri) eli yhteens‰ kolme muuttujaa (jos haluaa eri nopeuksia, sen voi tehd‰ helposti j‰lkik‰teen)
-textureclass merkkaa vain kuvaa ja yhdest‰ luokasta saa monta palaa, siin‰ ei ole mit‰‰n ongelmaa (ilmeisesti lopullinen grafiikan k‰yttˆ ei muuta t‰t‰)
-olisiko hyv‰ joku palikka-vektori/array? pit‰isikˆ sille luoda oma palikkadatatyyppi.
-dynaaminen vektori voisi olla paras t‰h‰n tarkoitukseen. ei tarvitsisi lyˆd‰ lukkoon palikoiden m‰‰r‰‰k‰‰n etuk‰teen.
-voisiko uuden palikan luoda normaalin constructorin kautta? varmaankin.

--

19 kohtaa hihnalla
leveys: 5
altaan korkeus: 5

palikat: oranssi, syaani, violetti, keltainen, valkoinen, sininen, punainen, vihre‰

kasa muuttujia, jotka kuvaa, mitk‰ palikat ovat peliv‰lineen p‰‰ll‰ (monta niit‰ voi olla?)

Kysymyksi‰:
onko textureclassin height & width tarpeellisia?

--
Pelin muutettavia s‰‰ntˆj‰:
Kuinka usein moniv‰rinen-pala tulee?
nopeus ja sen kiihtyminen

--
irc-logit iteraattori-ongelmasta, ja t‰ss‰ on muutakin oleellista lopussa:

-randomize_iterator: laitetaan randomize_iterator yksi ennen endi‰ ja sitten haetaan [1]:st‰, joka on sama kuin end. Mutta end():i‰ ei voi derensoida
-Loopissa taas first-iteraattoria inkrementoidaan, kunnes se ei ole end(). Eli iteraation viimeisess‰ loopissa ollaan yksi ennen loppua. Koska vektorissa on kaksi itemi‰, kountteri on 1:ss‰ viimeisell‰ iteraatiossa ja yritet‰‰n samalla tarttua 1:een, joka on sama kuin end()
-it[0].thing() on hyvin ep‰tavallinen keino sanoa it->thing()
*/

#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <array>
#include <vector>
#include <algorithm>
#include <stdlib.h> //rand, srand
#include <time.h> //time, for randomizing
#include <cstdlib> //atoi
#include <stdlib.h> //for getting username
#include <ctime>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
//#include <gperftools/profiler.h>  //DEBUGGING
using namespace std;

const int SCREEN_WIDTH = 570;
const int SCREEN_HEIGHT = 360;

void reset_phase();

TTF_Font* font;
SDL_Surface* textsurface;
SDL_Texture* texttexture;
SDL_Color textcolour = {0,0,0};
int text_width;
int text_height;
SDL_Texture* score_texture;
SDL_Texture* pattern_texture;
SDL_Texture* diag_texture;
SDL_Texture* points_texture;
SDL_Texture* phase_texture;

SDL_Rect paddlerect[2];
SDL_Rect* paddown = &paddlerect[0];
SDL_Rect* padup = &paddlerect[1];
//bool paddleup = false;

SDL_Rect tilesheetrect[24];
SDL_Rect* tilerect; //T‰h‰n pit‰nee ehk‰ rendaus vaiheessa laittaa esim tilerect = &tilesheetrect[...]
SDL_Rect onlyhererect = {134, 116, 294, 208}; //When tiles fall, only area where they should be seen is rendered

//gamespeed tells what is the current speed of the game. It is used in the mainloop.
int gamespeed = 77;  //montako millisekunttia pit‰‰ menn‰, ett‰ liikutaan. Mit‰ suurempi, sen hitaammin edet‰‰n.

//A variable measuring when tiles were moved
Uint32 tiletimer = 0;

//Whether player is accelerating tile speed by pressing up or not
bool accel = false;

//A counter handling how much winning tiles blink 
int blinkcounter = 0;

//0 = column phase (player needs to form columns to pass to next round), 0 = normal phase, 1 = diagonal phase, 2 = points sphase ...time phase????
//goal refers to how many units are left before the phase is complete
int phase_type = 0;
int goal = 5;
int gameround = 1;
int phase = 1;

//This is a variable which the mainloop uses for checking whether it should draw any approaching tiles and player's paddle on the screen. 0 = No any tiles, 1 = Normal game mode, 2 = Blinking winning tiles to be removed, otherwise graphics is static, 3 = A phase completed, static tiles. Decimal values indicate more detailed stages.
double tileflow = 0;

//Variables for a falling tile that is dropped by the player (yd = destination, cn = column, cr = colour)
int fall_y = 0;
int fall_yd = 0;
int fall_cn = 0;
char fall_cr = 'x';

//Main loop checks this variable and sets a new random tile rolling from the horizon if it is true.
bool new_tile = true;

//Counter which tells which colour to render multicolour tiles, incremented in the main loop
int multicounter = 1;

//Variables telling to the main loop if the phase or the game ends
bool game_over = false;
int gaov_counter = 0;
bool phase_end = false;

//Player loses damage every time a tile falls off without being caught. Zero means game over.
int damage = 0;

//A variable which tells in which row player's paddle is positioned. To make it more convenient to work with tilepool array's indeces, values 0-4 are used (instead of 1-5). Note that the paddle is always positioned somewhere. So it is always ready to fetch tile from one of the columns.
int paddle_position = 3;

//A variable which tells on which screen's x position the paddle is positioned in case it is moving and not steadily positioned and above that const values for its non-moving positions.
//HUOM. Ainakin t‰ll‰ hetkell‰ koodi on semmoinen, ett‰ n‰iss‰ luvuissa pit‰‰ olla sama viimeinen numero, koska paddle liikkuu +/-10 askelin
//matemaattisen tarkasti laskettuna nuo olisi: 146, 203.25, 260.5, 317.75, 375 (146 on conveyorin vasen reuna, 375 on oikea miinus paddlen pituus)
//const int PX0 = 146;
//const int PX1 = 206;
//const int PX2 = 266;
//const int PX3 = 316;
//const int PX4 = 376;
const int PX0 = 146;
const int PX1 = 203;
const int PX2 = 260;
const int PX3 = 317;
const int PX4 = 375;
int paddle_x_position = PX3;

//A variable - and its possible values as const ints - which indicates paddle's y position which changes depending on how much tiles it is holding. PY0 = 0 tiles, PY1 = 1 tiles, PY2 = 2 tiles etc.
const int PY0 = 176;
const int PY1 = 189;
const int PY2 = 202;
const int PY3 = 215;
const int PY4 = 228;
const int PY5 = 241;
int paddle_y_position = PY0;

//A variable which tells if player's paddle is moving (after pressing a key that controls it) or not. 'L' = moving left, 'R' = moving right, 'S' = steady
char paddle_dir = 'S';

//Array which represents tiles (or their absence) on player's paddle. 'x' is an empty space, other letters represent colours (m = multicolor, a color changing tile). The leftmost [0] is the uppest position, the rightmost is the lowest (and the first one to be used)
char paddletiles[5] = {'x', 'x', 'x', 'x', 'x'};

//Array which represents the pool of tiles (in which tiles fall from the track and in which they are supposed to form patterns of three or longer). Row length is five and the depth is also five (4 and 4 converted to array indeces). 'x' is an empty space, other letters represent colours (m = multicolor, a color changing tile). Right ends (index 4) of each array refers to the bottom tiles of columns. Columns are rendered from the bottom up (from the right end of an array to left) so that any 'x' in the way breaks the process. When testing this array note that the game engine does not draw tiles which are not supported by other tiles even though these tiles are otherwise taken in account.
//char tilepool[5][5] = {{'x', 'x', 'x', 'x', 'x'}, {'x', 'x', 'x', 'x', 'x'}, {'x', 'x', 'x', 'x', 'x'}, {'x', 'x', 'x', 'x', 'x'}, {'x', 'x', 'x', 'x', 'x'}};
//char tilepool[5][5] = {{'r', 'b', 'c', 'w', 'v'}, {'x', 'x', 'x', 'o', 'b'}, {'x', 'x', 'x', 'o', 'o'}, {'x', 'w', 'c', 'v', 'g'}, {'v', 'r', 'r', 'o', 'y'}};
//char tilepool[5][5] = {{'x', 'r', 'c', 'w', 'v'}, {'b', 'b', 'b', 'b', 'b'}, {'x', 'x', 'x', 'r', 'r'}, {'x', 'x', 'x', 'x', 'g'}, {'x', 'x', 'o', 'o', 'o'}};

//edellinenchar tilepool[5][5] = {{'x', 'x', 'x', 'x', 'g'}, {'x', 'x', 'x', 'g', 'r'}, {'x', 'b', 'g', 'r', 'o'}, {'x', 'g', 'o', 'b', 'v'}, {'x', 'x', 'x', 'x', 'b'}};

//char tilepool[5][5] = {{'x', 'x', 'x', 'x', 'm'}, {'x', 'x', 'x', 'x', 'r'}, {'x', 'x', 'x', 'x', 'r'}, {'x', 'x', 'x', 'x', 'v'}, {'x', 'x', 'x', 'v', 'y'}};
char tilepool[5][5] = {{'x', 'x', 'x', 'x', 'x'}, {'x', 'x', 'x', 'x', 'r'}, {'x', 'x', 'x', 'x', 'x'}, {'x', 'x', 'm', 'y', 'y'}, {'x', 'x', 'x', 'x', 'c'}};
//-Bugi: j‰i m-palan pudottamisen j‰lkeen jumiin, kun oli alarivi mrrvy ja viel‰ y:n p‰‰ll‰ v. toinen jumitilanne: tiputti m:n kahden y:n p‰‰lle (kolumni 4/5, muut palat r ja c kolumnien 2/5 ja 5/5 pohjalla)

//char tilepool[5][5] = {{'b', 'b', 'b', 'b', 'b'}, {'x', 'b', 'b', 'b', 'b'}, {'x', 'b', 'b', 'b', 'b'}, {'x', 'b', 'b', 'b', 'b'}, {'b', 'b', 'b', 'b', 'b'}};

//FULL
//char tilepool[5][5] = {{'x', 'r', 'c', 'w', 'v'}, {'r', 'b', 'g', 'o', 'b'}, {'g', 'v', 'v', 'r', 'r'}, {'v', 'r', 'r', 'w', 'g'}, {'w', 'o', 'v', 'r', 'o'}};

//EMPTY
//char tilepool[5][5] = {{'x', 'x', 'x', 'x', 'x'}, {'x', 'x', 'x', 'x', 'x'}, {'x', 'x', 'x', 'x', 'x'}, {'x', 'x', 'x', 'x', 'x'}, {'x', 'x', 'x', 'x', 'x'}};

//Array indicating removed "winning tiles" from the pool
char winpool[5][5] = {{'x', 'x', 'x', 'x', 'x'}, {'x', 'x', 'x', 'x', 'x'}, {'x', 'x', 'x', 'x', 'x'}, {'x', 'x', 'x', 'x', 'x'}, {'x', 'x', 'x', 'x', 'x'}};

int score = 0;

bool init();
bool loadmedia();
void shutdown();

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

ifstream scorestream; 
vector<pair<string,int> > hiscores;
string hiscofile = "hiscore.txt";

class textureclass {
  //Private
  SDL_Texture* texture;  //Hardware texture
  int width;
  int height;
public:
  textureclass(); //Initialises variables
  ~textureclass(); //De-allocates memory
  bool loadmedia(string filename);
  void erase(); //De-allocates texture
  //  void renderfunction(int x, int y, SDL_Rect* sourect = NULL, bool ispool = false, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE); //Renderˆi tekstuurin annettuun kohtaan
  void renderfunction(int x, int y, SDL_Rect* sourect = NULL, bool ispool = false);
  int get_width();
  int get_height();
};

//Declaring image objects
textureclass sign;
textureclass damlight;
textureclass indlight;
textureclass round1;
textureclass round2;
textureclass round3;
textureclass blue_tile;
textureclass blue_movtile;
textureclass cyan_tile;
textureclass cyan_movtile;
textureclass green_tile;
textureclass green_movtile;
textureclass orange_tile;
textureclass orange_movtile;
textureclass red_tile;
textureclass red_movtile;
textureclass violet_tile;
textureclass violet_movtile;
textureclass white_tile;
textureclass white_movtile;
textureclass yellow_tile;
textureclass yellow_movtile;
textureclass playerpad;

void textureclass::erase() {
  if(texture != NULL) {
    SDL_DestroyTexture(texture);
    texture = NULL;
    width = 0;
    height = 0;
  }
}

//Constructor - primerin sivulla 617 t‰m‰ n‰ytt‰‰ aika erilt‰...
textureclass::textureclass() {
  texture = NULL;
  width = 0;
  height = 0;
}

//Destructor
textureclass::~textureclass() {
  erase();
}

bool textureclass::loadmedia(string filename) {
  erase(); //olemassa oleva tekstuuri pois
  SDL_Texture* newtexture = NULL;
  SDL_Surface* surface = IMG_Load(filename.c_str());
  if(surface == NULL) {
    cerr << "Image load fail: " << filename.c_str() << " " << IMG_GetError() << endl;
  }
  else {
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));
    //T‰ss‰ kuva colorkey‰t‰‰n, ennen kuin siit‰ luodaan tekstuuri. Ensimm‰inen argumentti on, mik‰ surface colorkey‰t‰‰n, seuraava argumentti laittaa colorkeyingin p‰‰lle, kolmas argumentti on pikseli, joka halutaan colorkey‰t‰. T‰h‰n laitetaan sitten toinen funktio, jossa ensimm‰inen argumentti on formaatti pikseleille (k‰ytetyss‰ oliossa on formaatin kertova j‰senmuuttuja), seuraavat muuttujat ovat v‰ri, t‰ss‰ tapauksessa syaani.

    //Creating a texture from surface
    newtexture = SDL_CreateTextureFromSurface(renderer, surface);
    if(newtexture == NULL) {
      cerr << "Texture creation fail - " << SDL_GetError << endl;
    }
    else {
      //Storing the height and width of a texture
      width = surface->w;
      height = surface->h;
    }
    //Freeing the used surface
    SDL_FreeSurface(surface);
  }
  texture = newtexture;
  return texture != NULL;
}

//Full-screen imagejen kanssa riitti SDL_RenderCopy ja kaksi viimmeist‰ argumenttia NULLiksi, mutta nyt tiettyyn paikkaan renderˆit‰ess‰ tarvitaan alkuper‰isen kuvan dimensiot leveyden ja korkeuden spesifioimiseen eli luodaan ensin tuommoinen neliskulmio, johon luokasta leveys ja korkeus ja se sitten annetaan RenderCopyyn
void textureclass::renderfunction(int x, int y, SDL_Rect* sourect, bool ispool) {
  //  if(ispool) width += 20;
  SDL_Rect rendrect;
  if(ispool) rendrect = {x,y,width+10, height};
  else rendrect = {x,y,width, height};
  if(sourect != NULL) {
    rendrect.w = sourect->w;
    rendrect.h = sourect->h;
  }
  /*
  if(ispool) SDL_Rect rendrect = {x,y,(width+20), height};
  else SDL_Rect rendrect = {x,y,width, height};
  if(sourect != NULL) {
    rendrect.w = sourect->w;
    rendrect.h = sourect->h;
  }
  */
  //  SDL_RenderCopyEx(renderer, texture, sourect, &rendrect, angle, center, flip);
  SDL_RenderCopy(renderer, texture, sourect, &rendrect);
 }

 int textureclass::get_width() {
   return width;
 }

 int textureclass::get_height() {
   return height;
 }

//REMOVE!!!!!!!!!!!11111111
 void debug_function() {
   cout << "debug function" << endl;
 }

//SDL's init function
 bool init() {
   bool success = true;
   if(SDL_Init(SDL_INIT_VIDEO)<0) {
     cerr << "SDL init fail - " << SDL_GetError() << endl;
     success = false;
   }
   else {
     //Setting texture filtering to linear
     if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
       cerr << "Linear filtering failed" << endl;
     }
     //Creating the Window
     window = SDL_CreateWindow("FREE KLAX", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
     if(window == NULL) {
       cerr << "Window creation failed - " << SDL_GetError() << endl;
       success = false;
     }
     else {
       //Creating the renderer
       renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
       SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
       if(renderer == NULL) {
 	cerr << "Renderer creation fail - " << SDL_GetError() << endl;
 	success = false;
       }
       else {
 	//Setting renderer's draw color
 	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
 	//Initializing PNG loading
 	int imgFlags = IMG_INIT_PNG;
 	if(!(IMG_Init(imgFlags)&imgFlags)) {
 	  cerr << "SDL_image fail - " << IMG_GetError() << endl;
 	  success = false;
 	}
 	else {
 	  if(TTF_Init() == -1) {
 	    cerr << "TTF Init fail" << TTF_GetError() << endl;
 	    success = false;
 	  }
	}
      }
    }
  }
  return success;
}

bool loadmedia() {
  bool success = true;
  if(!round1.loadmedia("klaxpng/round1.png")) {cerr << "Image load fail - round1" << endl; success = false;}
  if(!round2.loadmedia("klaxpng/round2.png")) {cerr << "Image load fail - round2" << endl; success = false;}
  if(!round3.loadmedia("klaxpng/round3.png")) {cerr << "Image load fail - round3" << endl; success = false;}
  if(!sign.loadmedia("klaxpng/pancarte.png")) {cerr << "Tile image load fail - sign" << endl; success = false;}
  if(!indlight.loadmedia("klaxpng/indlight.png")) {cerr << "Image load fail - indlight" << endl; success = false;}
  if(!damlight.loadmedia("klaxpng/damlight.png")) {cerr << "Image load fail - damage light" << endl; success = false;}
  //Loading tile images
  if(!blue_tile.loadmedia("klaxpng/bluestattile.png")) {cerr << "Tile image load fail" << endl; success = false;}
  if(!yellow_tile.loadmedia("klaxpng/yellowstattile.png")) {cerr << "Tile image load fail" << endl; success = false;}
  if(!cyan_tile.loadmedia("klaxpng/cyanstattile.png")) {cerr << "Tile image load fail" << endl; success = false;}
  if(!green_tile.loadmedia("klaxpng/greenstattile.png")) {cerr << "Tile image load fail" << endl; success = false;}
  if(!red_tile.loadmedia("klaxpng/redstattile.png")) {cerr << "Tile image load fail" << endl; success = false;}
  if(!orange_tile.loadmedia("klaxpng/orangestattile.png")) {cerr << "Tile image load fail" << endl; success = false;}
  if(!white_tile.loadmedia("klaxpng/whitestattile.png")) {cerr << "Tile image load fail" << endl; success = false;}
  if(!violet_tile.loadmedia("klaxpng/violetstattile.png")) {cerr << "Tile image load fail" << endl; success = false;}
  
  if(!yellow_movtile.loadmedia("klaxpng/yellowtile.png")) {
    cerr << "Tile image load fail" << endl;
    success = false;
  }
  if(!blue_movtile.loadmedia("klaxpng/bluetile.png")) {
    cerr << "Tile image load fail" << endl;
    success = false;
  }
  if(!cyan_movtile.loadmedia("klaxpng/cyantile.png")) {
    cerr << "Tile image load fail" << endl;
    success = false;
  }
  if(!green_movtile.loadmedia("klaxpng/greentile.png")) {
    cerr << "Tile image load fail" << endl;
    success = false;
  }
  if(!orange_movtile.loadmedia("klaxpng/orangetile.png")) {
    cerr << "Tile image load fail" << endl;
    success = false;
  }
  if(!red_movtile.loadmedia("klaxpng/redtile.png")) {
    cerr << "Tile image load fail" << endl;
    success = false;
  }
  if(!violet_movtile.loadmedia("klaxpng/violettile.png")) {
    cerr << "Tile image load fail" << endl;
    success = false;
  }
  if(!white_movtile.loadmedia("klaxpng/whitetile.png")) {
    cerr << "Tile image load fail" << endl;
    success = false;
  }
  if(!playerpad.loadmedia("klaxpng/pad.png")) {
    cerr << "Pad image load fail" << endl;
    success = false;
  }
  else {
    paddlerect[0].x = 0;
    paddlerect[0].y = 0;
    paddlerect[0].w = 51;
    paddlerect[0].h = 31;
    paddlerect[1].x = 52;
    paddlerect[1].y = 0;
    paddlerect[1].w = 51;
    paddlerect[1].h = 31;

  }
  //Closest tile frames
  tilesheetrect[0].x = 0;
  tilesheetrect[0].y = 0;
  tilesheetrect[0].w = 46;
  tilesheetrect[0].h = 50;
  tilesheetrect[1].x = 46;
  tilesheetrect[1].y = 0;
  tilesheetrect[1].w = 46;
  tilesheetrect[1].h = 50;
  tilesheetrect[2].x = 92;
  tilesheetrect[2].y = 0;
  tilesheetrect[2].w = 46;
  tilesheetrect[2].h = 50;
  tilesheetrect[3].x = 138;
  tilesheetrect[3].y = 0;
  tilesheetrect[3].w = 46;
  tilesheetrect[3].h = 50;
  //Second closest tile frames ...and so on
  tilesheetrect[4].x = 0;
  tilesheetrect[4].y = 51;
  tilesheetrect[4].w = 41;
  tilesheetrect[4].h = 50;
  tilesheetrect[5].x = 41;
  tilesheetrect[5].y = 51;
  tilesheetrect[5].w = 41;
  tilesheetrect[5].h = 50;
  tilesheetrect[6].x = 82;
  tilesheetrect[6].y = 51;
  tilesheetrect[6].w = 41;
  tilesheetrect[6].h = 50;
  tilesheetrect[7].x = 123;
  tilesheetrect[7].y = 51;
  tilesheetrect[7].w = 41;
  tilesheetrect[7].h = 50;

  tilesheetrect[8].x = 0;
  tilesheetrect[8].y = 101;
  tilesheetrect[8].w = 36;
  tilesheetrect[8].h = 50;
  tilesheetrect[9].x = 36;
  tilesheetrect[9].y = 101;
  tilesheetrect[9].w = 36;
  tilesheetrect[9].h = 50;
  tilesheetrect[10].x = 72;
  tilesheetrect[10].y = 101;
  tilesheetrect[10].w = 36;
  tilesheetrect[10].h = 50;
  tilesheetrect[11].x = 108;
  tilesheetrect[11].y = 101;
  tilesheetrect[11].w = 36;
  tilesheetrect[11].h = 50;

  tilesheetrect[12].x = 0;
  tilesheetrect[12].y = 151;
  tilesheetrect[12].w = 32;
  tilesheetrect[12].h = 50;
  tilesheetrect[13].x = 32;
  tilesheetrect[13].y = 151;
  tilesheetrect[13].w = 32;
  tilesheetrect[13].h = 50;
  tilesheetrect[14].x = 64;
  tilesheetrect[14].y = 151;
  tilesheetrect[14].w = 32;
  tilesheetrect[14].h = 50;
  tilesheetrect[15].x = 96;
  tilesheetrect[15].y = 151;
  tilesheetrect[15].w = 32;
  tilesheetrect[15].h = 50;

  tilesheetrect[16].x = 0;
  tilesheetrect[16].y = 201;
  tilesheetrect[16].w = 26;
  tilesheetrect[16].h = 50;
  tilesheetrect[17].x = 26;
  tilesheetrect[17].y = 201;
  tilesheetrect[17].w = 26;
  tilesheetrect[17].h = 50;
  tilesheetrect[18].x = 53;
  tilesheetrect[18].y = 201;
  tilesheetrect[18].w = 26;
  tilesheetrect[18].h = 50;
  tilesheetrect[19].x = 80;
  tilesheetrect[19].y = 201;
  tilesheetrect[19].w = 26;
  tilesheetrect[19].h = 50;

  tilesheetrect[20].x = 0;
  tilesheetrect[20].y = 251;
  tilesheetrect[20].w = 22;
  tilesheetrect[20].h = 50;
  tilesheetrect[21].x = 22;
  tilesheetrect[21].y = 251;
  tilesheetrect[21].w = 22;
  tilesheetrect[21].h = 50;
  tilesheetrect[22].x = 44;
  tilesheetrect[22].y = 251;
  tilesheetrect[22].w = 22;
  tilesheetrect[22].h = 50;
  tilesheetrect[23].x = 67;
  tilesheetrect[23].y = 251;
  tilesheetrect[23].w = 22;
  tilesheetrect[23].h = 50;
  //l‰himm‰t 0-3, toiseksil‰himm‰t 4-7, 8-11, 12-15, 16-19, kauimmat: 20-23
  return success;
}

void shutdown() {
  sign.erase();
  damlight.erase();
  indlight.erase();
  playerpad.erase();
  round1.erase();
  round2.erase();
  round3.erase();
  red_tile.erase();
  red_movtile.erase();
  blue_tile.erase();
  blue_movtile.erase();
  cyan_tile.erase();
  cyan_movtile.erase();
  green_tile.erase();
  green_movtile.erase();
  orange_tile.erase();
  orange_movtile.erase();
  violet_tile.erase();
  violet_movtile.erase();
  white_tile.erase();
  white_movtile.erase();
  yellow_tile.erase();
  yellow_movetile.erase();

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  window = NULL;
  renderer = NULL;

  SDL_DestroyTexture(texttexture);
  SDL_DestroyTexture(score_texture);
  SDL_DestroyTexture(pattern_texture);
  SDL_DestroyTexture(diag_texture);
  SDL_DestroyTexture(points_texture);
  SDL_DestroyTexture(phase_texture);
  SDL_FreeSurface(textsurface);

  TTF_CloseFont(font);
  scorestream.close(); 
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

//Each tile is an object of the tileclass and has three features represented as variables: colour, position on Y-axis (which is a screen coordinate), and column position (which tells on which column (1-5, from left to right) of the track the tile is), reverse (is 1 for thrown tiles which are moving backwards).
class tileclass {
  //Private
  char colour;
  int y_axis_pos;
  int column_pos;
  float frame;
  bitset<1> reverse;
  bitset<1> fall;
public:
  tileclass(); 
  ~tileclass();
  //  void erase(); //De-allocates texture
  //  void renderfunction(int x, int y, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE); //Renderˆi tekstuurin annettuun kohtaan
  //  int get_width();
  //  int get_height();
  //These functions exist only for thrown tiles: show_reverse, set_tilecolour, switch_reverse, set_colpos, set_y_pos
  char show_colour();
  int show_y_axis_pos();
  int show_column_pos();
  int show_frame();
  void incr_frame();
  void set_y_pos(int);
  void set_colpos(int);
  bool show_fall();
  void switch_fall();
  bool show_reverse();
  void switch_reverse();
  bool advance_tile();
  void randomize_tile();
  void set_tilecolour(char);
};

char tileclass::show_colour() {return colour;}
int tileclass::show_y_axis_pos() {return y_axis_pos;}
int tileclass::show_column_pos() {return column_pos;}
int tileclass::show_frame() {return frame;}
void tileclass::incr_frame() {frame < 3 ? frame++ : frame += 0.1; if(frame >= 3.1) frame = 0;} //3.1 is a "pseudo frame" during which a tile does not advance producing an intended jerking movement
bool tileclass::show_reverse() {return reverse.any();}
void tileclass::switch_reverse() {reverse.flip();}
bool tileclass::show_fall() {return fall.any();}
void tileclass::switch_fall() {fall.flip();}
void tileclass::set_tilecolour(char c) {colour = c;}
void tileclass::set_y_pos(int x) {y_axis_pos = x;}
void tileclass::set_colpos(int x) {column_pos = x;}

//Creating a generic instance of the tileclass that we use to make elements to the tile_vector
tileclass generic_tile;

//T‰ss‰ tuo konverttaus taitaa olla turhaa, kun se tehd‰‰n molemmissa p‰iss‰. Ehk‰ voisi poistaa konverttauksen sek‰ t‰‰lt‰ ett‰ kutsusta. MUTTA asia voi muuttua, jos t‰t‰ k‰ytet‰‰n myˆs muualla
//A function that takes the column of a tile pool and returns the lowest empty row on that pool column. Note that columns are 1-5 while array indeces are 0-4. The function returns 4 for an empty column, 3 for a column with one tile, 2 for a column with two tiles, 1 for three tiles, 0 for four tiles, -1 for a full column
int where_empty_col(int col) {
  col--; //converting col (1-5) to indeces (0-4)
  int empty = -1;
  //The loop goes from down to up, breaking when the first empty ('x') is found
  for(int col_counter = 4; col_counter > -1; col_counter--) {
    if(tilepool[col][col_counter] == 'x') {empty = col_counter; break;}
  }
  return empty;
}

//Class function for randomizing values of a new tile and intializing other values. NOTE: Randomizer changes its value on each second, thus this function should not be used twice during the same second
void tileclass::randomize_tile() {
  int random = rand()%8;
  switch(random) {
  case 0: colour = 'b'; break;
  case 1: colour = 'c'; break;
  case 2: colour = 'g'; break;
  case 3: colour = 'o'; break;
  case 4: colour = 'r'; break;
  case 5: colour = 'v'; break;
  case 6: colour = 'w'; break;     
  case 7: colour = 'y'; break;
  }
  if((rand()%30) == 1) colour = 'm';
  //  column_pos = 5; //TEMPORARY LINE
  column_pos = rand()%5+1;
  y_axis_pos = -31;
  frame = 0;
  //  colour = 'b'; //TEMPORARY LINE
}


//KONSTRUKTORI EI TEE NYT SITTEN MITƒƒN, KOSKA NƒYTTƒƒ, ETTƒ SITƒ RANDOMISAATIOTA EI VOI TEHDƒ TƒSSƒ. PITƒISIK÷ SEN KUITENKIN LAITTAA NOLLA-ARVOT (ne voi kai yht‰ hyvin laittaa randomize_tile -funktiossa) TAI PITƒISIK÷ NE LAITTAA JO LUOKANMƒƒRITTELYSSƒ?
tileclass::tileclass() {
  /*  srand((int)time(0));
  int random = rand()%9;
  switch(random) {
  case 0:
    colour = "blue";
    break;
  case 1:
    colour = "cyan";
    break;
  case 2:
    colour = "green";
    break;
  case 3:
    colour = "orange";
    break;
  case 4:
    colour = "red";
    break;
  case 5:
    colour = "violet";
    break;
  case 6:
    colour = "white";
    break;     
  case 7:
    colour = "yellow";
    break;
  case 8:
    colour = "multi";
    break;
  }
  column_pos = rand()%4+1;
  y_axis_pos = 0;*/
}

//Destructor
tileclass::~tileclass() {
  //Mit‰kˆh‰n t‰ss‰ tapahtuu. Tarvitaanko t‰t‰? Vektorista poistetaan se?
}

//void textrend(int width, int height, string text, TTF_Font* textfont) {
void textrend(int width, int height, string text, TTF_Font* textfont) {
  SDL_Surface* textsurface = TTF_RenderText_Solid(textfont, text.c_str(), textcolour);
  int text_width = textsurface->w;
  int text_height = textsurface->h;
  SDL_Texture* texttexture = SDL_CreateTextureFromSurface(renderer, textsurface);
  SDL_Rect textrect = {width, height, text_width, text_height}; 
  SDL_RenderCopy(renderer, texttexture, NULL, &textrect);
  SDL_FreeSurface(textsurface);
  SDL_DestroyTexture(texttexture);
}

//tile_list is a list containing tileclass objects and thus representing the tiles on a track. Whenever a new tile appears to the horizon, it is preceded by a creation of a new element to this class and when a list 
vector<tileclass> tile_vector;

//POISTA??
//Function that prints the tile_list - for debugging purposes.
void print_tiles() {
  int counter = 0;
  vector<tileclass>::iterator printer;
  for(printer = tile_vector.begin(); printer != tile_vector.end(); ++printer) {
    counter++;
    cout << "tile_list: " << counter << endl;
  }
}

//This function goes through the tile_list and removes one element (tile) from there by using given y-axis location and column of a tile
void remove_tile(int remy, int remcol) {
  for(vector<tileclass>::iterator remiter = tile_vector.begin(); remiter != tile_vector.end(); ++remiter) {
    if((remiter->show_y_axis_pos()) == remy) {
      if((remiter->show_column_pos()) == remcol) {
	tile_vector.erase(remiter);
	break;
      }
    }
  }
}

//A Function that takes tile's column_pos and paddle_x_pos and tells if the player catches a tile
bool is_catch(int colpos, int padx) {
  bool answer = false;
  //T‰h‰n saa kaavalla, ett‰ jos colpos ja padx samat --> true
  //((padx - 117) / 58) +1 antaa, ett‰ mik‰ colpos on kyseess‰ (175 - 58 = 117), siin‰ vaan pit‰isi saada desimaalit pois. Sitten voisi verrata colposiin, onko sama
  //padx:n tilalle paddle_x_position ja erillinen funktio t‰st‰ pois ...ehk‰

  if(colpos == (padx-117)/58+1) answer = true;  //This formula tells which colpos value padx value corresponds (colpos has values 1-5 corresponding x-axis ranges each of which is 58 screen width pixels. Ranges begin at the width 117)
     
  /*
  if (colpos == 1 and padx < 175) answer = true;
  else if (colpos == 2 and padx >= 175 and padx < 233) answer = true;
  else if (colpos == 3 and padx >= 233 and padx < 291) answer = true;
  else if (colpos == 4 and padx >= 291 and padx < 349) answer = true;
  else if (colpos == 5 and padx >= 349) answer = true;
  */
  return answer;
}

//A function that reshuffles the order of tile_list after a thrown tile has landed to the conveyor (so that they get rendered in a proper order and closer tiles will not be rendered behind further tiles). A tile vector is copied but thrown tile is skipped and it is re-created to its new position. Function's code is repetitive in order to gain efficiency in execution.

/*
-BUGI: joskus tiili katoaa accel-p‰‰ll‰ heitt‰ess‰ ja se katoaa aina ilmankin accelia, jos ei ole muita tiilej‰. tai jos heitt‰‰ kaksi tiilt‰ per‰kk‰in tyhj‰lle radalle, molemmat katoaa. jos heitt‰‰ tiilen ainoan radan tiilen eteen, se ei katoa, mutta jos heitt‰‰ sen taakse, se katoaa

Jos heitt‰‰ tiilen radan ainoan tiilen taakse:
-tilanteessa vektorissa on kaksi elementti‰
-Molemmat muuttujat on alussa false, joten aina ensin menn‰‰n ekaan iffiin
-eka iffi:
--heitt‰ess‰ tiili laitetaan frontiksi eli se on vektorissa ensimm‰isen‰
--jos heitetty lˆytyi, merkit‰‰n se heitetyksi eik‰ tehd‰ muuta
-eli ilmeisesti tiili lˆytyy ensimm‰isell‰ kierroksella
-vanhaa tiilt‰ ei siis kopioida ja sitten siirryt‰‰n seuraavalle kierrokselle
-seuraavalla kierroksella menn‰‰n seuraavaan else iffiin (koska foundold = true)
-Nyt sitten seuraavalla kierroksella se yritt‰‰ lˆyt‰‰ elementin, jonka y-arvo on pienempi, mutta eih‰n sellaista ole, joten se j‰tt‰‰ uuden piirt‰m‰tt‰.

Ratkaisut:
-Ratkaisu yll‰ kuvattuun ongelmaan on ainakin, ett‰ jos foundnew on lopussa false, sitten piirret‰‰n se uusi sinne loppuun. Ratkaisee kaiketi tuon tyhj‰n radan tilanteen myˆskin.
-jos tyhj‰n radan tilanne on oma juttunsa, pit‰isi olla ehk‰ alussa iffi, ett‰ jos vektorissa on vain se heitetyn elementti. Toisaalta peli ei taida oikein edes sallia t‰llaista tilannetta


*/

//A function that reshuffles the tilevector so that a thrown tile (that is now landed on the conveyor) is put on the right place in the tilevector (which determines in which order tiles are drawn on the screen)
void tile_reshuffle(int colpos, int ypos, char colour) {
  //ilmeisesti t‰h‰n l‰hetet‰‰n col-pos ja ypos ja v‰ri, joiden avulla identifioidaan se tiili. jos on kaksi p‰‰llekk‰ist‰, samahan se on, kumpi niist‰ l‰htee

  vector<tileclass> tempvec;

  bool foundold = false; //Whether a tile thrown is encountered
  bool foundnew = false; //Whether a new place is found
  
  for(vector<tileclass>::iterator rsiter = tile_vector.begin(); rsiter != tile_vector.end(); ++rsiter) {
    
    if(!foundold and !foundnew) {
      if(rsiter->show_y_axis_pos() == ypos and rsiter->show_column_pos() == colpos and rsiter->show_colour() == colour) {
	foundold = true;
	//Jos vanha tiili lˆytyy ja skipataan, sill‰ kierroksella ei tehd‰ mit‰‰n muuta, joten loput voidaan laittaa elseen
	//When a thrown tile is found from its old place, we can just skip it, no need to adjust iterator
      }
      else {
	if(rsiter->show_y_axis_pos() < ypos) {
	  foundnew = true;
	  tempvec.push_back(generic_tile);
	  vector<tileclass>::iterator thrt_iterator = --tempvec.end();
	  thrt_iterator->set_tilecolour(colour);
	  thrt_iterator->set_y_pos(ypos);
	  thrt_iterator->set_colpos(colpos);
  	  tempvec.push_back(*rsiter);
	}
	else tempvec.push_back(*rsiter);
      }
    }
    else if(foundold and !foundnew) {
      if(rsiter->show_y_axis_pos() < ypos) {
	foundnew = true;
	tempvec.push_back(generic_tile);
	vector<tileclass>::iterator thrt_iterator = --tempvec.end();
	thrt_iterator->set_tilecolour(colour);
	thrt_iterator->set_y_pos(ypos);
	thrt_iterator->set_colpos(colpos);
	tempvec.push_back(*rsiter);
      }
      else tempvec.push_back(*rsiter);
    }
    else if(!foundold and foundnew) {
      if(rsiter->show_y_axis_pos() == ypos and rsiter->show_column_pos() == colpos and rsiter->show_colour() == colour) {
	foundold = true;
      }
      else tempvec.push_back(*rsiter);
    }
    else tempvec.push_back(*rsiter); //(foundold and foundnew)
  }
  if(!foundnew) { //In case there is no tiles behind a thrown tile foundnew may still be false at this point
    tempvec.push_back(generic_tile);
    vector<tileclass>::iterator thrt_iterator = --tempvec.end();
    thrt_iterator->set_tilecolour(colour);
    thrt_iterator->set_y_pos(ypos);
    thrt_iterator->set_colpos(colpos);
  }
  tile_vector = tempvec;
}


/*
sattuuko luku x alueelle x, joka on m‰‰ritelty 
  
  	accel == true ? frame = 3 + ((128-tile_y)/27)*4 : frame += ((128-tile_y)/27)*4;

pelataan arvoilla  0 - 229 ja lopuksi plussataan (146)

  jokaisessa v‰liss‰ on 58, joten ensimm‰inen v‰li alkaa 0 - 29, ja loppuu +29. seuraava 29 ja loppuu 87,
  -29 - 29  //kertoimet 0 ja 1
  29 - 87  //1 ja 2
  87 - 145  //2 ja 3
  145 - 203
  203 - 261
  261 - 319   //t‰m‰ viimenen tulee, kun kertoo kuudella
  
  rangen alun saa siis -29 + 0 x 58 ja seuraavan kohdan -29 + 1 x 58, kolmannen -29 + 3 x 58

  rangeja on kuusi, mutta kolumneja vain viisi. pit‰‰ katsoa, ett‰ mit‰ kolumnia range nappaa.
  range 1 nappaa kolumnia 1, r2 nappaa kolumneja 1-2, r3 k2-3, r4 k3-4, r5 k4-5, r6 k5
	    voidaan muuntaa col_pos 
  onko arvo X luku Z, kun se konvertoidaan
  onko 1-5 vertailuluku. vertailuluku pit‰isi saada 
  
  146 -x- 203 --- 260 - 317 - 375
  57 on se v‰li. esim jos esim arvo on 1 niin (117.5 + 1 x 28,5 viiva 117 + 2 x 28,5) on se range, jos kaksi niin (2 x 28,5 + 117 viiva 3 x 28,5 + 117) jne.
  const int PX0 = 146;
const int PX1 = 203;
const int PX2 = 260;
const int PX3 = 317;
const int PX4 = 375;
*/

/*
BUGI:
tiili napataan ja siin‰ on ilmeisesti oikea column_pos. sen j‰lkeen tuleekin k‰sittelyyn taas tiili, jonka column_pos on nolla.
 */
//Function that advances tiles on the track and deals with tiles going off the end of the track
bool tileclass::advance_tile() {
  bool tile_removed = false;
  //Dealing with tiles thrown back by the player
  if(show_reverse()) {
    if(!accel) y_axis_pos-=15;
    if(accel) y_axis_pos-=75;
    if(y_axis_pos < 43) {
      y_axis_pos = 42;
      switch_reverse();
      tile_reshuffle(column_pos, y_axis_pos, colour);
    }
  }
  else if(!show_fall()) {
    if(accel == false and frame < 3) y_axis_pos+=2; //TƒHƒN NOLLA, JOS HALUAA KOKEILLA ILMAN LIIKKUMISTA //OLI 2
    if(accel == true) {
      if(y_axis_pos > 107) y_axis_pos = 127; //MITENK÷HƒN NƒMƒ PITƒISI MENNƒ
      else y_axis_pos+=10;
    }
    if((y_axis_pos > 126 and accel == true) or (y_axis_pos > 126 and frame > 3)) {   //If a tile has reached the end and goes off the track... (frame does not matter in an accelerated motion, otherwise it does)

      //If a player catches a tile with the paddle
      if(is_catch(show_column_pos(), paddle_x_position)) { //Note that paddle_position is converted here because it is index-like whereas column_pos is not
	if(paddletiles[4] == 'x') {paddletiles[4] = show_colour(); paddle_y_position = PY1; remove_tile(show_y_axis_pos(), show_column_pos()); tile_removed = true;}
	else if(paddletiles[3] == 'x') {paddletiles[3] = show_colour(); paddle_y_position = PY2; remove_tile(show_y_axis_pos(), show_column_pos()); tile_removed = true;}
	  else if(paddletiles[2] == 'x') {paddletiles[2] = show_colour(); paddle_y_position = PY3;  remove_tile(show_y_axis_pos(), show_column_pos()); tile_removed = true;}
	    else if(paddletiles[1] == 'x') {paddletiles[1] = show_colour(); paddle_y_position = PY4;  remove_tile(show_y_axis_pos(), show_column_pos()); tile_removed = true;}
	      else if(paddletiles[0] == 'x') {paddletiles[0] = show_colour(); paddle_y_position = PY5;  remove_tile(show_y_axis_pos(), show_column_pos()); tile_removed = true;}
	else { //If no empty positions, then the paddle must be full and a tile falls
	  switch_fall();
	}
	//	print_tiles();
      }
      //    cout << "paddle: " << paddletiles[0] << paddletiles[1] << paddletiles[2] << paddletiles[3] << paddletiles[4] << endl;

      //If a player does not catch a tile
      else if(!is_catch(show_column_pos(), paddle_x_position)) {
	switch_fall();
      }															   

     
      
      //COUTING TILEPOOL
      /*
	for(int arr_count = 0 ; arr_count < 5; arr_count++) {
	cout << tilepool[0][arr_count] << " ";
	cout << tilepool[1][arr_count] << " ";
	cout << tilepool[2][arr_count] << " ";
	cout << tilepool[3][arr_count] << " ";
	cout << tilepool[4][arr_count] << " ";
	cout << endl;
      */

      //  if(arr_count2 = 4){cout << endl;}
      /*
	for(int arr_count = 0 ; arr_count != 5; arr_count++) {
	for(int arr_count2 = 0; arr_count2 != 5; arr_count2++) {
	cout << tilepool[arr_count][arr_count2] << " ";
	if(arr_count2 = 4){cout << endl;}
	}	  
	}

      */
      //palalla on joku kolumni, sen voi syˆtt‰‰ funktioon, sitten saa takaisin arvon, mik‰ on kolumnin ensimm‰inen (alhaalta laskettuna) tyhj‰ paikka
      
      //TƒHƒN: JOS ARRAYN 0 -KOLUMNISSA ON VAIN X:ƒƒ, SITTEN SINNE POHJALLE SE PALA, JOS POHJALLA ON MUU KUIN X, SITTEN TOISEKSI ALIMMALLE JNE.
  
      //char tilecol1 = colourconvert(string tilecol2 = show_colour());
      //    if(colpos)

    }
  }
  if(show_fall()) {
    if(!accel) y_axis_pos+=20;
    if(accel) y_axis_pos+=70;
    if(y_axis_pos > 324) {
      remove_tile(show_y_axis_pos(), show_column_pos());
      tile_removed = true;
      damage++;
    }
  }
  tiletimer = SDL_GetTicks();
  return tile_removed;
}



string is_win_string(string analyzed_string) {
  string answer = "no_win";
  string colourcheck = "";
  string checkstring;
  string modified_string = "";
  int how_many_found;
  char winchar;
  for(int i = 0; i != (analyzed_string.size()); i++) {
    //Aletaan k‰yd‰ l‰pi annettua stringi‰. Jos lˆydet‰‰n tiili, joka ei ole m eik‰ ole jo lˆydettyjen v‰rien listassa...
    if(analyzed_string[i] != 'm' and count(colourcheck.begin(), colourcheck.end(), analyzed_string[i]) == 0) {
       //...niin lis‰t‰‰n t‰llˆin lˆydetty v‰rin colourcheck-listaan
      colourcheck += analyzed_string[i];
      //ja seuraavaksi pit‰isi kai k‰yd‰ l‰pi, ett‰ jos m:t muuttaa, t‰ksi v‰riksi, lˆydet‰‰nkˆ sitten kolmen tai pidempi yhdistelm‰. MUTTA sen koe-stringin pit‰‰ olla selv‰sti erillinen muista stringeist‰. Ja loopin uusiutumisen voisi est‰‰ jollain muuttujalla
      //Luodaan siis checkstring2, josta ensin muutetaan kaikki m:t analysoitavan v‰rin v‰risiksi
      checkstring = "";
      for(int j = 0; j != (analyzed_string.size()); j++) {
	if(analyzed_string[j] == 'm') checkstring += analyzed_string[i];
	if(analyzed_string[j] != 'm') checkstring += analyzed_string[j];
      }
      //Nyt meill‰ pit‰isi olla checkstring2, jossa kaikki m:t on muutettu analysoitavan v‰rin v‰risiksi
      //Nyt tehd‰‰n sitten looppi, jossa lasketaan, montako per‰kk‰ist‰ samaa siin‰ on
      how_many_found = 1;
      //T‰ss‰ kohti n‰kyy checkstring oikein
      for(int k = 1; k != (checkstring.size()); k++) {
	if(checkstring[k] == checkstring[k-1]) {
	  how_many_found++;
	  if(how_many_found == 3) winchar = checkstring[k];
	}
	//Jos lˆydet‰‰n ei-per‰tt‰inen kohta... Breikataan koko loopista (ja otetaan voittokirjain ylˆs), jos ollaan lˆydetty jo voitto, muussa tapauksessa aloitetaan alusta
	else {
	  if(how_many_found >= 3) break;
	  else how_many_found = 1;
	}
      }
      if(how_many_found >= 3) break;
    }
    //Jos lˆytyi kolme, voidaan siirty‰ pois loopista ja ottaa voittokirjain ylˆs, koska vain yksi voittoyhdistelm‰ on mahdollinen
    if(how_many_found >= 3) break;
  }
  //If a winning combination has been found, then switching those tiles to x which are not winning tiles and changing answer to a winning string
  if(how_many_found >= 3) {
    for(int l = 0; l != (checkstring.size()); l++) {
      if(checkstring[l] != winchar) {checkstring[l] = 'x';}
    }
    //En tied‰ tarvitaanko n‰it‰ poistoja, mutta ainakin aiemmin koodi oli semmoinen, ett‰ vikoja x:i‰ ei l‰hetet‰:
    if(checkstring[4] == 'x') checkstring.erase(4,1);
    if(checkstring[3] == 'x') checkstring.erase(3,1);
    answer = checkstring;
    cout << "checkstring: " << checkstring[0] << checkstring[1] << checkstring[2] << endl;
  }
  return answer;
}


string string_analysis(string analyzed_string2) {
  //Muuttuja, joka pit‰‰ kirjaa siit‰, montako ei-x:‰‰ on lˆydetty per‰kk‰in
  string checkstring2 ="";
  string answer_string = "no_win";
  int begin_index = 0;
  int how_many_in_row = 0;
  bool three_in_row_found = false;
  int string_counter2 = analyzed_string2.size();
  //  cout << "br test6:" << tilepool[2][4] << endl;
  for(int s2 = 0; s2 != string_counter2; s2++) {
    if(analyzed_string2[s2] != 'x') {
      how_many_in_row++;
      if(how_many_in_row == 3) {three_in_row_found = true;}
      if(checkstring2 == "") {begin_index = s2;}
      //analyzed_string[s1] lis‰t‰‰n checkstringiin
      checkstring2 += analyzed_string2[s2];
      //poistettu pidempi tapa.
      //char countedchar2 = analyzed_string2[s2];
      //checkstring2 += countedchar2;
    }
    if(analyzed_string2[s2] == 'x' and three_in_row_found == false) {checkstring2 = ""; how_many_in_row = 0;}
  }
  if(three_in_row_found == true) {
    answer_string = is_win_string(checkstring2);
    if(answer_string != "no_win") {
      cout << "voittoa" << endl;
      cout << "answer_string: " << answer_string[0] << answer_string[1] << answer_string[2] << endl;
      if(begin_index == 1) {answer_string = "x" + answer_string;}
      if(begin_index == 2) {answer_string = "xx" + answer_string;}
      //JOS ALKUINDEKSI ON 1, LISƒTƒƒN SEN ALKUUN YKSI X, JOS 2, LISƒTƒƒN SEN ALKUUN 2 X:ƒƒ. LOPUSTA PUUTTUVAT X:T JƒƒVƒT POIS
    }
  }
  cout << "analysedstring new: " << analyzed_string2[0] << analyzed_string2[1] << analyzed_string2[2] << endl; 
  return answer_string;
}

//A function that searches the tile for 3+ tile combinations to be scored and removed
bool check_pool() {

  bool answer = false;
  int winrows = 0;
  int wincols = 0;
  int windias = 0;
  int newscore = 0;

  /*
    T‰ll‰ hetkell‰ funktio ottaa koko viitosrivin, sitten nelosrivin...
    Voisiko funktio ottaa koko rivin ja tarkistettavaksi? T‰llˆin sen pit‰isi palauttaa myˆs voittopalojen sijainnit

    Yhden tarkistusfunktion malli. Ensin tarkistetaan, onko tarpeeksi ei-x:i‰. Sitten jos lˆytyy v‰hint‰‰n kolme ei-x:‰‰, otetaan talteen indeksi, mist‰ x alkaa, tarkistetaan is_win_string -funktion tapaan, lˆytyykˆ siit‰ voittoa (mutta ei tarkisteta X:i‰ en‰‰), sitten palautetaan tavalla tai toisella se rivi kokonaisuudessaan, jossa on nyt mahdolliset voittotiilet merkitty ja samalla tieto, onko se voittorivi (jos ei ole, palauttaa jonkun ihan muun stringin)

    Esim, l‰hetet‰‰n uudelle funktiolle koko vaakarivi, joka palauttaa stringin, joka tarkistaa, onko siin‰ v‰hint‰‰n kolme ei-x:‰‰ riviss‰. Jos ei ole, sitten lopetetaan sen kohdan k‰sittely.
    Jos taas on, istten k‰ytet‰‰n is_win_stringi‰, jonka ehk‰ pit‰isi kuitenkin palauttaa myˆs se indeksi, mist‰ rivi kohtaa alkaa
jossa on alussa luku, joka kertoo sen oleellisen indeksin
    iw_win_string -funktiosta pit‰isi 

   */
  
  //Pisteidenlaskun periaatteet: ehk‰ ei tarvitse mietti‰ mit‰‰n komboja sen kummemmin, kuin ett‰ saa lis‰pisteit‰ sen mukaan, jos saa kerralla poistettua useampia komboja, niin sitten katsotaan kuinka monta palaa poistui kerralla ja siit‰ annetaan lis‰pisteit‰. Mutta miten erotetaan kombot? Ainakin esim siten, ett‰ katsotaan, tuliko useampia juttuja muuttujiin, eli voisi pit‰‰ kirjaa niist‰kin. Ei tarvitse pit‰‰ kirjaa, tuliko kuinka pitk‰ rivi tai muu, koska niist‰ voi suoraan antaa jo pisteit‰ pituuden mukaan.

  cout << "br test3:" << tilepool[2][4] << endl;
  string teststring;
  teststring.push_back(tilepool[0][4]);
  teststring.push_back(tilepool[1][4]);
  teststring.push_back(tilepool[2][4]);
  teststring.push_back(tilepool[3][4]);
  teststring.push_back(tilepool[4][4]);
  cout << "teststring test" << teststring << endl;
  

  //Checking rows for winning combinations
  for(int r = 0; r != 5; r++) {
    string rowstring;
    for(int i = 0; i !=5; i++) {
      cout << "br test1:" << tilepool[2][4] << endl;
      rowstring.push_back(tilepool[i][r]);
      cout << "br test:" << tilepool[2][4] << endl;
      cout << "rowstring: " << rowstring << endl;
    }
    string analysed_string = string_analysis(rowstring);
    cout << "analysed string: " << analysed_string << endl;
    cout << analysed_string[0] << analysed_string[1] << analysed_string[2] << endl; 
    if(analysed_string != "no_win") {
      //T‰ss‰ pit‰isi kirjoittaa analysed string winpooliin (huom. analysed_stringin lopusta puuttuu x:t, mutta eih‰n se vaikuta t‰ss‰ mitenk‰‰n. kirjoitetaan vaan koko string winpooliin, niin se menee kohdalleen). Sitten pit‰‰ laskea, kuinka iso se voitto on siin‰ (5 miiinus x:t)
      //Writing win string to winpool.
      winrows++;
      int wintiles = 0;
      int counter = 0;
      if(analysed_string[0] == 'x') counter++;
      if(analysed_string[1] == 'x') counter++;
      for(; counter != (analysed_string.size()); counter++) {
	if(analysed_string[counter] != 'x') {
	  winpool[counter][r] = 'w';
	  wintiles++;
	}
      }
      if(wintiles == 3) newscore += 100;
      if(wintiles == 4) newscore += 300;
      if(wintiles == 5) newscore += 500;
    }
  }
  
  //Checking columns for winning combinations
  for(int c = 0; c != 5; c++) {
    string colstring;
    for(int j = 0; j != 5; j++) {
      colstring.push_back(tilepool[c][j]);
    }
    string analyzed_col = string_analysis(colstring);
    if(analyzed_col != "no_win") {
      wincols++;
      cout << "WINCOL: " << wincols << endl;
      int wintiles2 = 0;
      int counter2 = 0;
      if(analyzed_col[0] == 'x') counter2++;
      if(analyzed_col[1] == 'x') counter2++;
      for(; counter2 != (analyzed_col.size()); counter2++) {
	if(analyzed_col[counter2] != 'x') {
	  winpool[c][counter2] = 'w';
	  wintiles2++;
	}
      }
      if(wintiles2 == 3) newscore += 100;
      if(wintiles2 == 4) newscore += 300;
    }
  }

  //Checking ascending (from left to right) diagonals for winning combinations
  //Note that logic of this handling of diagonals is a bit different to rows and columns, now a nested loop includes the whole section
  for(int k = 0, l; k != 3; k++) {
    for(l = 2; l != 5; l++) {
      if(k > 0 and l < 4) {l = 4;} //In order to avoid some overlapping pool scanning
      string diastring;
      diastring.push_back(tilepool[k][l]);
      diastring.push_back(tilepool[(k+1)][(l-1)]);
      diastring.push_back(tilepool[(k+2)][(l-2)]);
      if(l > 2 and k < 2) {diastring.push_back(tilepool[(k+3)][(l-3)]);}
      if(l == 4 and k == 0) {diastring.push_back(tilepool[(k+4)][(l-4)]);}

      string analyzed_dia = string_analysis(diastring);
      if(analyzed_dia != "no_win") {
	windias++;
	int wintiles3 = 0;
	if(analyzed_dia[0] != 'x') {winpool[k][l] = 'w'; wintiles3++;}
	if(analyzed_dia[1] != 'x') {winpool[k+1][l-1] = 'w'; wintiles3++;}
	winpool[k+2][l-2] = 'w'; wintiles3++;
	if(analyzed_dia.size() == 4) {winpool[k+3][l-3] = 'w'; wintiles3++;}
	if(analyzed_dia.size() == 5) {winpool[4][0] = 'w'; wintiles3++;}
	if(wintiles3 == 3) newscore += 200;
	if(wintiles3 == 4) newscore += 500;
	if(wintiles3 == 5) newscore += 1000;
      }
    }
  }

  //Checking for descending (from left to right) diagonals
  for(int m = 0, n; m != 3; m++) {
    for(n = 2; n >= 0; n--) {
      if(m > 0 and n < 0) n = 0; //In order to avoid some overlapping pool scanning
      string diastring2;
      diastring2.push_back(tilepool[m][n]);
      diastring2.push_back(tilepool[(m+1)][(n+1)]);
      diastring2.push_back(tilepool[(m+2)][(n+2)]);
      if((m == 0 and n == 1) or (m == 1 and n == 0)) diastring2.push_back(tilepool[(m+3)][(n+3)]);
      if(n == 0 and m == 0) diastring2.push_back(tilepool[(4)][(4)]);

      string analyzed_dia2 = string_analysis(diastring2);
      if(analyzed_dia2 != "no_win") {
	windias++;
	int wintiles4 = 0;
	if(analyzed_dia2[0] != 'x') {winpool[m][n] = 'w'; wintiles4++;}
	if(analyzed_dia2[1] != 'x') {winpool[m+1][n+1] = 'w'; wintiles4++;}
	winpool[m+2][n+2] = 'w'; wintiles4++;
	if(analyzed_dia2.size() == 4) {winpool[m+3][n+3] = 'w'; wintiles4++;}
	if(analyzed_dia2.size() == 5) {winpool[4][4] = 'w'; wintiles4++;}
	if(wintiles4 == 3) newscore += 200;
	if(wintiles4 == 4) newscore += 500;
	if(wintiles4 == 5) newscore += 1000;
      }
    }
  }

  if(winrows == 0 and wincols == 0 and windias == 0) {
    game_over = true;

    for(int o = 0; o != 5; o++) {
      for(int p = 0; p !=5; p++) {
	if(tilepool[o][p] == 'x') {
	  game_over = false;
	  goto out;
	}
      }
    }
  }
 out:  
  
  //DRAWING WINTILES
  /*
  cout << endl;
  cout << "winrows: " << winrows << endl;
  for(int arr_count = 0 ; arr_count < 5; arr_count++) {
    cout << winpool[0][arr_count] << " ";
    cout << winpool[1][arr_count] << " ";
    cout << winpool[2][arr_count] << " ";
    cout << winpool[3][arr_count] << " ";
    cout << winpool[4][arr_count] << " ";
    cout << endl;
  }  
  */

  //Each additional winpattern the beyond first one gives 1000 extra points
  newscore += ((windias + winrows + wincols) * 1000 - 1000);
  
  score += newscore;
  if(phase_type == 0 and wincols > 0) goal -= wincols;
  if(phase_type == 0 and winrows > 0) goal -= winrows;
  if(phase_type == 1 and windias > 0) goal -= windias;
  if(phase_type == 2 and newscore > 0) goal -= newscore;
  if(goal < 0) goal = 0;
  cout << "winrows: " << winrows << " wincols: " << wincols << " windias: " << windias << endl;
  if(winrows > 0 or wincols > 0 or windias > 0) {answer = true; tileflow = 2;}
  cout << "answer: " << answer << endl;
  return answer;
}


//A function that returns the color of the uppest tile currently on the paddle
char uppest_paddletile() {
  char uppest;
  for(int padcounter = 0 ; padcounter != 5 ; padcounter++) {
    if(paddletiles[padcounter] != 'x') {uppest = paddletiles[padcounter]; break;}
  }
  return uppest;
}

//A function that returns how many tiles the paddle currently holds
int tiles_num_tile() {
  int tiles_num = 0;
  for(int padcounter3 = 0; padcounter3 != 5; padcounter3++) {
    if(paddletiles[padcounter3] != 'x') tiles_num++;
  }
  return tiles_num;
}

//Updating paddle's y-position after a tile is dropped or thrown
void update_paddle_y() {
  int tiles = tiles_num_tile();
  //  cout << "tiles num:" << tiles << endl;
  switch(tiles) {
  case 0: paddle_y_position = PY0; break;
  case 1: paddle_y_position = PY1; break;
  case 2: paddle_y_position = PY2; break;
  case 3: paddle_y_position = PY3; break;
  case 4: paddle_y_position = PY4; break;
  }
}

//If a button is pressed when the paddle holds a tile this function is called
void drop_tile() {
  //Checking if tilepool's column in question is already full. In this case only a sound effect follows.
  if(where_empty_col((paddle_position+1)) == -1) {cout << "column full!" << endl;}

  else {
    //paddle_positionista se column. Sitten uppest tilest‰ se v‰ri, Sitten destination tilepoolin avulla. ja y-arvo on joku
    fall_y = PY0; //(176)
    fall_cr = uppest_paddletile();
    fall_yd = 317-(13 * (5-(1+where_empty_col(paddle_position+1))));  //where_empty_col gives 0-4 but adding 1 and subtracting from 5 gives us 4-1 which is more useful

    switch(paddle_position) {
    case 0: fall_cn = PX0; break;
    case 1: fall_cn = PX1; break;    
    case 2: fall_cn = PX2; break;
    case 3: fall_cn = PX3; break;    
    case 4: fall_cn = PX4; break;
    }
    //and a dropped tile is erased from paddletiles
    for(int padcounter2 = 0; padcounter2 != 5; padcounter2++) {
      if(paddletiles[padcounter2] != 'x') {paddletiles[padcounter2] = 'x'; break;}
    }
  }
}

//The second drop_tile function is called after a tile dropped by the player has falled
void drop_tile2() {
  //Tilepool is updated to have a new tile at the lowest free place in the column in question
  switch(fall_cn) {
  case PX0: fall_cn = 0; break;
  case PX1: fall_cn = 1; break;    
  case PX2: fall_cn = 2; break;
  case PX3: fall_cn = 3; break;    
  case PX4: fall_cn = 4; break;
  }

  tilepool[(fall_cn)][(where_empty_col((fall_cn+1)))] = fall_cr;
  fall_y = 0;
  //After a tile is dropped, the tilepool will be checked for winning combinations
  cout << "check_pool at drop_tile2" << endl;
  check_pool();
  update_paddle_y();
}

void throw_tile() {
  //Inserting a thrown tile to the tile_list, taking its colour from the uppest paddle tile and switching it to moving backwards

  //VANHA PUSH_BACK
  //tile_vector.push_back(generic_tile);
  //vector<tileclass>::iterator throw_iterator = --tile_vector.end();

  //UUSI:
  //  vector<tileclass>::iterator throw_iterator = tile_vector.begin();
  //  tile_vector.insert(throw_iterator, generic_tile); //Vectorin alkuun pit‰isi saada

  //UUSI, MUTTA VANHA JƒRJESTYS
  tile_vector.insert(tile_vector.begin(), generic_tile);
  vector<tileclass>::iterator throw_iterator = tile_vector.begin();

  //VAIHTOEHTOISET: (ilman iteraattoriobjektia)
  //tile_vector.insert(tile_vector.begin(), generic_tile);
  //tile_vector.begin()->set_tilecolour(uppest_paddletile());  //N‰ytt‰‰ niinkuin segfaultti sijoittuisi t‰h‰n kohtaan
  
  //T‰ss‰ n‰kyy cout
  throw_iterator->set_tilecolour(uppest_paddletile());  //N‰ytt‰‰ niinkuin segfaultti sijoittuisi t‰h‰n kohtaan
  //T‰ss‰ ei n‰y cout - aina, joskus n‰kyy
  throw_iterator->switch_reverse();
  throw_iterator->set_y_pos(145); //oli 175
  throw_iterator->set_colpos(paddle_position+1);
  //T‰ss‰ pit‰‰ luoda tiili, joka lent‰‰ jonkun matkaa ja k‰‰ntyy sitten normaaliksi. Pit‰isikˆ k‰ytt‰‰ samaa vektoria vai luoda uusi?
  //T‰t‰ funktiota tarvitsee  uppest_paddletile()

  //A thrown tile is erased from paddletiles
  for(int padcounter = 0; padcounter != 5; padcounter++) {
    if(paddletiles[padcounter] != 'x') {paddletiles[padcounter] = 'x'; break;}
  }
  update_paddle_y();
}


//Function which converts column value (refering 1th-to-5th column of a track) to pixel values corresponding column position (their left borders) on the screen.
/*
int convert_column(int column) {
    switch(column) {
  case 1: 
    column = 200;
    break;
  case 2:
    column = 250;
    break;
  case 3:
    column = 300;
    break;
  case 4:
    column = 350;
    break;
  case 5:
    column = 400;
    break;
  }
  return column;
}
*/

void key_up() {
  if(tileflow == 1 and paddletiles[4] != 'x') throw_tile();
}

void key_down() {
  if(tileflow == 1) accel = true;
}

void key_left() {
  if(tileflow==1 and paddle_position !=0) paddle_dir = 'L'; //Paddle does not start moving left if it is already in the left end, otherwise it does
}

void key_right() {
  if(tileflow==1 and paddle_position !=4) paddle_dir = 'R'; //Like above
}

void key_control() {
  if(tileflow == 1 and paddletiles[4] != 'x' and fall_y == 0) drop_tile();
  if(tileflow == 2.4) tileflow = 1;
  //check_pool();
}

void key_meta() {
  if(tileflow == 2.4) tileflow = 1;
  if(tileflow < 1) {tileflow = 2.4; reset_phase(); phase = 1;}
  //if(tileflow >= 1) print_tiles(); //DEBUG
}

//Rendering tiles on the conveyor. Tile_cx indicates first column but is converted to x-coordinates
void render_contile(int tile_cx, int tile_y, char tile_colour, int frame, bool rev, bool fall) {
  //  176 on matalin y-arvo ehk‰, riitt‰‰, ett‰ on sit‰ edellist‰ suurempi (ei olekaan matalin, koska seh‰n lasketaan sielt‰ ylh‰‰lt‰)


  if(fall) SDL_RenderSetClipRect(renderer, &onlyhererect);
  //For falling tiles it is convenient to use the same values that mark paddle's static positions
  if(fall) {
    frame = 1;
    switch(tile_cx) {
    case 1: tile_cx = PX0; break;
    case 2: tile_cx = PX1; break;    
    case 3: tile_cx = PX2; break;
    case 4: tile_cx = PX3; break;    
    case 5: tile_cx = PX4; break;
    }
  }

  //The position on Y-axis determines which frame to use  
  else {
    if(rev) frame = 1 + ((128-tile_y)/27)*4;
    else if(tile_y <= 101) {
	accel == true ? frame = 3 + ((128-tile_y)/27)*4 : frame += ((128-tile_y)/27)*4;
      }

    //y-arvo jaetaan 27:ll‰ * 4
  
    /*
      if(tile_y < -5) frame +=20;
      else if(tile_y >= -6 and <= 21) frame +=16;
      else if(tile_y >= 22 and <= 48) frame +=12;
      else if(tile_y >= 49 and <= 74) frame +=8;
      else if(tile_y >= 75 and <= 101) frame +=4;
    */

    //Calculating the paths of tiles depending on the column
    //Ottamalla k‰yttˆˆn uuden muuttujan voisi konvertoida tile_cx:n kolumneista x-koordinaateiksi heti, mutta sitten tarviisi tosiaan sen uuden muuttujan 
    switch(tile_cx) {
    case 1:
      //HUOM!!!    Y-arvon rangesta otetaan tuo, miten paljon framea lis‰t‰‰n ja seh‰n on kaikille caseille yhteinen
      tile_y == -31 ? tile_cx = 229 : (tile_cx += 228) -= ((tile_y + 31) * 0.50); //T‰ss‰ ik‰‰n kuin muunnetaan columnit x-koordinaateiksi. 228, koska 1 on jo siin‰, ja poistetaan samalla etumerkki
      //    tile_cx -= ((tile_y + 31) * 0.50);
      break;
    case 2:
      tile_y == -31 ? tile_cx = 254 : tile_cx += 252;
      tile_cx -= ((tile_y + 31) * 0.30);
      break;    
    case 3:
      tile_y == -31 ? tile_cx = 278 : tile_cx += 275;
      tile_cx -= ((tile_y + 31) * 0.09);
      break;
    case 4:
      tile_y == -31 ? tile_cx = 300 : tile_cx += 296;
      tile_cx += ((tile_y + 31) * 0.12);
      break;    
    case 5:
      tile_y == -31 ? tile_cx = 319 : tile_cx += 314;
      tile_cx += ((tile_y + 31) * 0.36);
      break;
    }
  }
    
  //l‰himm‰t 0-3, toiseksil‰himm‰t 4-7, 8-11, 12-15, 16-19, kauimmat: 20-23
  //pit‰isi tiet‰‰, mist‰ y-arvosta l‰hdet‰‰n liikkeelle, ett‰ voisi tiet‰‰, mit‰ tapahtuu
  //  0-23 framet    
  //Frameja on nyt 0-8. Pit‰isikˆ frameen aina lis‰t‰ numero sen pohjalta, mik‰ X-arvo on. Pit‰isi myˆs katsoa mik‰ alin y-arvo on
  //126 voisi olla alustava alin y-arvo
  tilerect = &tilesheetrect[frame];

  switch(tile_colour) {
  case 'b':
    //Kun yll‰ jaetaan frame 4:ll‰, frame p‰ivittyy vain nelj‰n framen v‰lein eli animaatio hidastuu. T‰m‰ johtuu siit‰, ett‰ int-datatyypiss‰ 0/4=0, 1/4=0, 2/4=0, 3/4=0, 4/4=1, 5/4=1 jne.
    blue_movtile.renderfunction(tile_cx, tile_y, tilerect);
    break;
  case 'c':
    cyan_movtile.renderfunction(tile_cx, tile_y, tilerect);
    break;
  case 'g':
    green_movtile.renderfunction(tile_cx, tile_y, tilerect);
    break;
  case 'o':
    orange_movtile.renderfunction(tile_cx, tile_y, tilerect);
    break;
  case 'r':
    red_movtile.renderfunction(tile_cx, tile_y, tilerect);
    break;
  case 'v':
    violet_movtile.renderfunction(tile_cx, tile_y, tilerect);
    break;
  case 'w':
    white_movtile.renderfunction(tile_cx, tile_y, tilerect);
    break;
  case 'y':
    yellow_movtile.renderfunction(tile_cx, tile_y, tilerect);
    break;
  case 'z':
    white_movtile.renderfunction(tile_cx, tile_y, tilerect);
    break;
  case 'm':
    switch(multicounter) {
    case 1:
      blue_movtile.renderfunction(tile_cx, tile_y, tilerect);
      break;
    case 2:
      cyan_movtile.renderfunction(tile_cx, tile_y, tilerect);
      break;
    case 3:
      green_movtile.renderfunction(tile_cx, tile_y, tilerect);
      break;
    case 4:
      orange_movtile.renderfunction(tile_cx, tile_y, tilerect);
      break;
    case 5:
      red_movtile.renderfunction(tile_cx, tile_y, tilerect);
      break;
    case 6:
      violet_movtile.renderfunction(tile_cx, tile_y, tilerect);
      break;
    case 7:
      white_movtile.renderfunction(tile_cx, tile_y, tilerect);
      break;
    case 8:
      yellow_movtile.renderfunction(tile_cx, tile_y, tilerect);
      break;
    }
    break;
  }
  if(fall) SDL_RenderSetClipRect(renderer, NULL);
}



void render_tile(int tile_x, int tile_y, char tile_colour, bool is_pool = false) {
  switch(tile_colour) {
  case 'b':
    //AIEMPI: blue_tile.renderfunction(tile_x, tile_y);
    is_pool == true ? blue_tile.renderfunction(tile_x, tile_y, NULL, 1) : blue_tile.renderfunction(tile_x, tile_y, NULL);
    break;
  case 'c':
    is_pool == true ? cyan_tile.renderfunction(tile_x, tile_y, NULL, 1) : cyan_tile.renderfunction(tile_x, tile_y, NULL);
    break;
  case 'g':
    is_pool == true ? green_tile.renderfunction(tile_x, tile_y, NULL, 1) : green_tile.renderfunction(tile_x, tile_y, NULL);
    break;
  case 'o':
    is_pool == true ? orange_tile.renderfunction(tile_x, tile_y, NULL, 1) : orange_tile.renderfunction(tile_x, tile_y, NULL);
    break;
  case 'r':
    is_pool == true ? red_tile.renderfunction(tile_x, tile_y, NULL, 1) : red_tile.renderfunction(tile_x, tile_y, NULL);
    break;
  case 'v':
    is_pool == true ? violet_tile.renderfunction(tile_x, tile_y, NULL, 1) : violet_tile.renderfunction(tile_x, tile_y, NULL);
    break;
  case 'w':
    is_pool == true ? white_tile.renderfunction(tile_x, tile_y, NULL, 1) : white_tile.renderfunction(tile_x, tile_y, NULL);
    break;
  case 'y':
    is_pool == true ? yellow_tile.renderfunction(tile_x, tile_y, NULL, 1) : yellow_tile.renderfunction(tile_x, tile_y, NULL);
    break;
  case 'z':
    is_pool == true ? white_tile.renderfunction(tile_x, tile_y, NULL, 1) : white_tile.renderfunction(tile_x, tile_y, NULL);
    break;
  case 'm':
    switch(multicounter) {
    case 1:
      is_pool == true ? blue_tile.renderfunction(tile_x, tile_y, NULL, 1) : blue_tile.renderfunction(tile_x, tile_y, NULL);
      break;
    case 2:
      is_pool == true ? green_tile.renderfunction(tile_x, tile_y, NULL, 1) : green_tile.renderfunction(tile_x, tile_y, NULL);
      break;
    case 3:
      is_pool == true ? orange_tile.renderfunction(tile_x, tile_y, NULL, 1) : orange_tile.renderfunction(tile_x, tile_y, NULL);
      break;
    case 4:
      is_pool == true ? red_tile.renderfunction(tile_x, tile_y, NULL, 1) : red_tile.renderfunction(tile_x, tile_y, NULL);
      break;
    case 5:
      is_pool == true ? violet_tile.renderfunction(tile_x, tile_y, NULL, 1) : violet_tile.renderfunction(tile_x, tile_y, NULL);
      break;
    case 6:
      is_pool == true ? white_tile.renderfunction(tile_x, tile_y, NULL, 1) : white_tile.renderfunction(tile_x, tile_y, NULL);
      break;
    case 7:
      is_pool == true ? yellow_tile.renderfunction(tile_x, tile_y, NULL, 1) : yellow_tile.renderfunction(tile_x, tile_y, NULL);
      break;
    case 8:
      is_pool == true ? white_tile.renderfunction(tile_x, tile_y, NULL, 1) : white_tile.renderfunction(tile_x, tile_y, NULL);
      break;
    }
    break;
  }
}



//A function which renders tiles on the paddle when it knows the number of tiles
void render_paddletiles(int tile_num) {
  //Kun paddle oli 460, niin tiili oli 436 eli 24 vaikuttaisi olevan sopiva v‰li ensimm‰isen tiilen ja paddlen v‰lill‰
  switch(tile_num) {
  case 1:
    render_tile(paddle_x_position, (paddle_y_position-13), paddletiles[4]);
    break;
  case 2:
    render_tile(paddle_x_position, paddle_y_position-13, paddletiles[4]);
    render_tile(paddle_x_position, paddle_y_position-(13+13), paddletiles[3]); //22-9 = 13
    break;
  case 3:
    render_tile(paddle_x_position, paddle_y_position-13, paddletiles[4]);
    render_tile(paddle_x_position, paddle_y_position-(13+13), paddletiles[3]);
    render_tile(paddle_x_position, paddle_y_position-(13+26), paddletiles[2]);
    break;
  case 4:
    render_tile(paddle_x_position, paddle_y_position-13, paddletiles[4]);
    render_tile(paddle_x_position, paddle_y_position-(13+13), paddletiles[3]);
    render_tile(paddle_x_position, paddle_y_position-(13+26), paddletiles[2]);
    render_tile(paddle_x_position, paddle_y_position-(13+39), paddletiles[1]);
    break;
  case 5:
    render_tile(paddle_x_position, paddle_y_position-13, paddletiles[4]);
    render_tile(paddle_x_position, paddle_y_position-(13+13), paddletiles[3]);
    render_tile(paddle_x_position, paddle_y_position-(13+26), paddletiles[2]);
    render_tile(paddle_x_position, paddle_y_position-(13+39), paddletiles[1]);
    render_tile(paddle_x_position, paddle_y_position-(13+52), paddletiles[0]);
    break;
  }
}

//A function that removes winning tiles after they have seen blinking and updates tilepool (some tiles may fall)
void tile_tumble() {
  
  /*
  cout << "tile tumblea edelt‰v‰  tilepool:" << endl;
  for(int arr_count = 0 ; arr_count < 5; arr_count++) {
    cout << tilepool[0][arr_count] << " ";
    cout << tilepool[1][arr_count] << " ";
    cout << tilepool[2][arr_count] << " ";
    cout << tilepool[3][arr_count] << " ";
    cout << tilepool[4][arr_count] << " ";
    cout << endl;
  }

  cout << "tile tumblea edelt‰v‰ winpool" << endl;
    for(int arr_count = 0 ; arr_count < 5; arr_count++) {
    cout << winpool[0][arr_count] << " ";
    cout << winpool[1][arr_count] << " ";
    cout << winpool[2][arr_count] << " ";
    cout << winpool[3][arr_count] << " ";
    cout << winpool[4][arr_count] << " ";
    cout << endl;
  }  
  */
  
  //  cout << "tile tumble" << endl;

  //Removing winner tiles from tilepool
  for(int i = 0; i != 5; i++) {
    for(int j = 0; j != 5; j++) {
      if(winpool[i][j] == 'w') {tilepool[i][j] = 'x';}
    }
  }

  /*
  cout << "voittotiilien poistamisen j‰lkeinen tilepool:" << endl;
  for(int arr_count = 0 ; arr_count < 5; arr_count++) {
    cout << tilepool[0][arr_count] << " ";
    cout << tilepool[1][arr_count] << " ";
    cout << tilepool[2][arr_count] << " ";
    cout << tilepool[3][arr_count] << " ";
    cout << tilepool[4][arr_count] << " ";
    cout << endl;
  }
  */
  
  //Reseting winpool
  for(int n = 0; n != 5; n++) {
    for(int o = 0; o != 5; o++) {
      winpool[n][o] = 'x';
    }
  }

  //The tumble
    for(int k = 0; k != 5; k++) {
  
    int how_many_move = 0;
    char temparray[5] = {'x', 'x', 'x', 'x', 'x'};
    for(int l = 4; l >= 0; l--) {
      if(tilepool[k][l] != 'x') {
	how_many_move = 0;
	for(int m = (l+1); m != 5; m++) {
	  if(tilepool[k][m] == 'x') {
	    how_many_move++;
	  }
	}
	temparray[l+how_many_move] = tilepool[k][l];
      }
    }
    for(int n = 0; n != 5; n++) {
      tilepool[k][n] = temparray[n];
    }
  }


  //K‰yd‰‰n l‰pi kaikki merkit ja jokaisen ei x:n kohdalla, katsotaan, monta x:‰‰ sen oikealla puolella on ja niin monta indeksi‰ oikealle on se paikka uudessa rivis‰

    /*
  for(int k = 0; k != 5; k++) {
    char newstring[5] = {'x', 'x', 'x', 'x', 'x'};
    int how_many_move = 0;
    for(int l = 4; l != 0; l--) {
      if(tilepool[k][l] != 'x') {
	for(int p = l+1; p != 5; p++) {
	  if(tilepool[k][p] == 'x') {how_many_move++;}
	}
      }
      l += how_many_move;
      newstring[l] = tilepool[k][l];
    }
    for(int q = 0; q != 5; q++) {
      tilepool[k][q] = newstring[q];
    }
  }

*/

    /*
    cout << "tile tumblen j‰lkeinen tilepool:" << endl;
  for(int arr_count = 0 ; arr_count < 5; arr_count++) {
    cout << tilepool[0][arr_count] << " ";
    cout << tilepool[1][arr_count] << " ";
    cout << tilepool[2][arr_count] << " ";
    cout << tilepool[3][arr_count] << " ";
    cout << tilepool[4][arr_count] << " ";
    cout << endl;
  }  
    */
	  //Nyt se yritt‰‰ kysy‰, ett‰ jos kolumnin alin kohta on X, niin..
	  //PITƒISI MIETTIƒ TƒMƒ NYT, MIKƒ ON JƒRKEVIN KEINO. EHKƒ NIIN, ETTƒ KUN L÷YTYY ALHAALTA EDETEN (ELI OIKEALTA VASEMMALLE) X, NIIN AINA TƒLL÷IN VEDETƒƒN MUITA PALOJA YKSI ALAS (siis oikealle) PƒIN. NƒIN SE TAITAISI MENNƒ.
  //Tilepoolissa on jokainen array niinkun vasemmalta oikealle ylh‰‰lt‰-alas-kolumni
  
}

//A function that clears paddletiles, tilepool and winpool. Used when a new game begins and when a new phase (and round) begins
void reset_phase() {
  if(gameround == 1 and phase_type == 0) goal = 5;
  if(gameround == 1 and phase_type == 1) goal = 5;
  if(gameround == 1 and phase_type == 2) goal = 10000;
  if(gameround == 2 and phase_type == 0) goal = 10;
  if(gameround == 2 and phase_type == 1) goal = 10;
  if(gameround == 2 and phase_type == 2) goal = 10000;
  for(int i = 0; i != 5; i++) {
    paddletiles[i] = 'x';
    for(int j = 0; j != 5; j++) {tilepool[i][j] = 'x'; winpool[i][j] = 'x';}
  }
  if(!tile_vector.empty()) {
    for(vector<tileclass>::iterator phase_iter = tile_vector.begin(); phase_iter != tile_vector.end(); ++phase_iter) {tile_vector.erase(phase_iter); --phase_iter;}
  }
  if(!tile_vector.empty()) cout << "vector erase fail" << endl;  //DEBUG
  paddle_position = 3;
  paddle_x_position = PX3;
  paddle_y_position = PY0;
  tiletimer = 0;
  phase_end = false;
  damage = 0;
}

//A function that updates a texture for phase text with the changing phase number on the top of the screen 
void phase_text_update() {
  string phasestr = "Phase ";
  phasestr += to_string(phase);
  SDL_Surface* phase_text = TTF_RenderText_Solid(font, phasestr.c_str(), textcolour);
  text_width = phase_text->w;
  text_height = phase_text->h;
  phase_texture = SDL_CreateTextureFromSurface(renderer, phase_text);
  SDL_Rect phase_textrect = {180, 230, text_width, text_height};
  SDL_FreeSurface(phase_text);
}

//Tuosta gameround -jutusta oma funktionsa ehk‰?
void new_phase() {
  phase++;
  phase_text_update();
  if(gameround == 1) {
    phase_type++;
    if(phase_type == 4) {
      gameround = 2;
      phase_type = 0;
    }
  }
  if(gameround == 2) {
    phase_type++;
    if(phase_type == 4) {
      gameround = 3;
      phase_type = 0;
    }
    
    //JA NIIN EDELLEEN...???
  }
  reset_phase();
  tileflow = 2.4;
}

//A function that fills hiscore vector with contents of the scorestream (which is bound to a hiscore file)
void genhiscore() {
  string name;
  string line;
  for(int count = 0, score ; getline(scorestream, line); count++) {  //PALAUTTAA ISTREAM OBJEKTIN, MUTTA OLEELLISEMMIN MUOKKAA STRINGIƒ ILMEISESTI
    if (count % 2 == 0) { //If odd or zero... that is name line
      name = line;
    }
    else {
      score = atoi(line.c_str());  //Converting line (char string) to score (int)
      hiscores.push_back(make_pair(name, score));
    }
  }
}

//A function that makes a new hiscore list when a score is a high enough after the game over. The function first creates a temporary "tempvec" vector and copies the beginning and the end of an old hiscore vector and adds a new result in between
void new_hilist(string newname, int newscore, int newpos) {
  newpos--; //converting to index
  vector<pair<string,int> > tempvec;
  //Adding elements until newpos is reached
  int counter = 0;
  for(vector<pair<string, int> >::iterator iter = hiscores.begin(); iter != hiscores.begin()+newpos; ++iter) {
    tempvec.insert(tempvec.begin()+counter, *iter);
    counter++;
  }
  //Adding a new result
  vector<pair<string, int> >::iterator resiter = tempvec.begin()+newpos;
  tempvec.insert(tempvec.begin()+newpos, make_pair(newname, newscore));
  counter++;
  //Adding rest of the old hiscore list, dropping the last line away
  for(vector<pair<string, int> >::iterator iter = hiscores.begin()+newpos; iter != hiscores.end()-1; ++iter) {
    tempvec.insert(tempvec.begin()+counter, *iter);
    counter++;
  }
  hiscores = tempvec;
}

int which_pos(int newsco) {
  int pos = 11;
  if(newsco >= hiscores[0].second) {
    pos = 1;
  }
  else {
    for(int var1=0, var2=1; var1 != 10; var1++) {
      if(newsco <= hiscores[var1].second and newsco >= hiscores[var2].second) {pos = var2+1; break;} //+1 is a conversion between index and position values
      var2++;
    }
  }
  return pos;
}


/*
-Jos vektoria lukee alusta k‰sin ja laittaa push_backill‰ elementit uuteen, ne tulee oikeassa j‰rjestyksess‰. T‰ytyy vain osata hyp‰t‰ sen poistettavan yli ja laitettava se oikeaan paikkaan.
-eli l‰hdet‰‰n kopioimaan vektoria push_backilla ja tarkistetaan aina, tuleeko haluttu tapaus vastaan ja tuleeko se oikea kohta. Pit‰‰ ensin tarkistaa haluttu tapaus, ettei se sotke oikean kohdan lˆyt‰mist‰. Jos tulee, sitten hyp‰t‰‰n sen yli

-onko v‰li‰, miten p‰in ne lˆydet‰‰n? ei
-kun tulee se vanha vastaan, skipataan se ja merkit‰‰n lˆydetyksi
-kun menn‰‰n siit‰ tarkistusarvosta ohi, sitten laitetaan se uusi siihen (ei liity mitenk‰‰n, onko vanha lˆydetty vai ei)
-


*/




/*
//A function that reshuffles the order of tile_list after a thrown tile has landed to the conveyor (so that they get rendered in a proper order and closer tiles will not be rendered behind further tiles)
void tile_reshuffle(int colpos, int ypos, char colour) {
  //ilmeisesti t‰h‰n l‰hetet‰‰n col-pos ja ypos ja v‰ri, joiden avulla identifioidaan se tiili. jos on kaksi p‰‰llekk‰ist‰, samahan se on, kumpi niist‰ l‰htee

  vector<tileclass> tempvec;
  
  for(vector<tileclass>::iterator rsiter = tile_vector.begin(); rsiter != tile_vector.end(); ++rsiter) {
    //Luetaan listaa alusta p‰in, eli ensin pit‰isi tulla vastaan
    bool found = false;
    //Tiili‰ piirrett‰ess‰ listaa luetaan takaperin, jolloin takana olevat rendautuu ensin. Nyt kun luetaan listaa etuperin, pit‰isi siis tulla ensin vastaan edess‰ olevia tiili‰, joiden y on siis suurempi kuin heitetyn tiilen. Sitten kun tulee tiili vastaan, jonka y on pienempi, sitten laitetaan siihen se uusi ennen sit‰.

    //kopioidaan tile_listist‰ templistiin elementtej‰, mutta tarkistetaan ennen luomista, ylitettiinkˆ ypos-arvo. jos kyll‰, laitetaan se uusi siihen kohtaan
    if((rsiter->show_y_axis_pos() > ypos) or (found == true)) { //Jos tiili on edemp‰n‰ tai jos on laitettu jo se heitetty tiili
      tempvec.insert(distance(tempvec.begin(), rsiter), *rsiter);
        tile_vector.insert(throw_iterator, generic_tile); //Vectorin alkuun pit‰isi saada
      //laitetaan siihen paikalle, miss‰ rsiter on, distancella saa tuon iterin senhetkisen position
    }
    else {
      found = true;
      tempvec.push_back(generic_tile);
      vector<tileclass>::iterator thrt_iterator = --tile_vector.end();
      thrt_iterator->set_tilecolour(colour);
      thrt_iterator->set_y_pos(ypos);
      thrt_iterator->set_colpos(colpos);
      ++rsiter;
    }
  }
  tile_vector = tempvec;
}
*/



int main(int argc, char*args[]) {

  //  ProfilerStart("klaxprofile1.log");  //DEBUGGING

  scorestream.open(hiscofile.c_str()); //For some reason this has to be declared here, not within the global scope
  if(!scorestream) {cerr << "Cannot open hiscore-file" << endl; return -1;}
  genhiscore();

  srand((int)time(0));
  Uint32 timer1 = 0;
  Uint32 timer2 = 0;

  //  cout << "br test4:" << tilepool[2][4] << endl;
  //"boooo" ja "omooc" ja "obbb" ei selvi‰ t‰st‰? sen sijaan n‰m‰ selvi‰‰: cmcc, omooo, bbbmb.
  //UUDEMPI VANHA TESTI: boooo -> xoooo (OK), omooc -> xxmo, obbb -> xbbb (OK), cmcc --> xxmc, omooo -> xxmoo, bbbmb -> bbbb
  //VANHA TESTI: boooo -> xxooo, omooc -> xxmo, obbb -> xxbb, cmcc -> xxmc, omooo -> xxmoo, bbbmb -> xxbbbb
  //NYKYINEN (13.3.) testi: Ei selvi‰: boooo -> bxxxx, obbb -> oxxx
  //cout << "is_win_string: " << is_win_string("omooo") << endl;
  //  cout << "string analysis: " << string_analysis("obbb") << endl;
  
  //counter checked by the main loop for when to set new tiles to the track
  int tilecounter = 0;
  int bonuscounter = 100;
  int titlecounter = 0;
  int bonuscounter2 = 0;
  int signcounter = 0;
  string signstr;

  //SDL main init
    if(!init()) cerr << "Init fail" << endl;
  else {
    //Loading media
    if(!loadmedia()) cerr << "Media load fail" << endl;
    else {
      bool quit = false; //P‰‰loopin lippu
      SDL_Event occasion; //Event handler
      //      SDL_RendererFlip flipType = SDL_FLIP_NONE;
      const Uint8* keystate = SDL_GetKeyboardState(NULL);

      //THINKCENTRESSƒ TOIMIVA: "/usr/share/fonts/truetype/ttf-dejavu/DejaVuSansMono-Bold.ttf"
      //font = TTF_OpenFont("/usr/share/fonts/TTF/DejaVuSansMono-Bold.ttf", 12);  //Parameters: path to the font, font size. If the path is wrong segfault happens
      font = TTF_OpenFont("/usr/share/fonts/TTF/DejaVuSansMono-Bold.ttf", 12);  //Parameters: path to the font, font size. If the path is wrong segfault happens

      //Some permanent textures for texts that are used through in the active game mode for increasing the performance (otherwise they are constantly created)
      SDL_Surface* score_text = TTF_RenderText_Solid(font, "Score:", textcolour);
      text_width = score_text->w;
      text_height = score_text->h;
      score_texture = SDL_CreateTextureFromSurface(renderer, score_text);
      SDL_Rect score_textrect = {180, 230, text_width, text_height};
      SDL_FreeSurface(score_text);

      SDL_Surface* pattern_text = TTF_RenderText_Solid(font, "Patterns to go:", textcolour);
      text_width = pattern_text->w;
      text_height = pattern_text->h;
      pattern_texture = SDL_CreateTextureFromSurface(renderer, pattern_text);
      SDL_Rect pattern_textrect = {180, 250, text_width, text_height};
      SDL_FreeSurface(pattern_text);

      SDL_Surface* diag_text = TTF_RenderText_Solid(font, "Diagonals to go:", textcolour);
      text_width = diag_text->w;
      text_height = diag_text->h;
      diag_texture = SDL_CreateTextureFromSurface(renderer, diag_text);
      SDL_Rect diag_textrect = {180, 250, text_width, text_height};
      SDL_FreeSurface(diag_text);

      SDL_Surface* points_text = TTF_RenderText_Solid(font, "Points to go:", textcolour);
      text_width = points_text->w;
      text_height = points_text->h;
      points_texture = SDL_CreateTextureFromSurface(renderer, points_text);
      SDL_Rect points_textrect = {180, 250, text_width, text_height};
      SDL_FreeSurface(points_text);
      
      //The main loop
      while(!quit) {
	timer1 = SDL_GetTicks();

	//Pressind key down has a different implementation to other keys since it is meant to be hold down
	SDL_PumpEvents();
	if(keystate[SDL_SCANCODE_DOWN]) key_down();
	if(keystate[SDL_SCANCODE_LEFT]) key_left();
	if(keystate[SDL_SCANCODE_RIGHT]) key_right();
	//	if(keystate[SDL_SCANCODE_RCTRL]) {key_control(); paddleup = true;}
	if(keystate[SDL_SCANCODE_RCTRL]) key_control();
	
	while(SDL_PollEvent(&occasion)!=0) {
	  //If the user quits

	  if(occasion.type == SDL_QUIT) {
	    quit = true;
	  }

	  /*
	  else if(occasion.type == SDL_WINDOWEVENT) {
	    if(occasion.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
	      SCREEN_WIDTH = occasion.window.data1;
      	      SCREEN_HEIGHT = occasion.window.data2;
	      //&window.w = occasion.window.data1;
	      //&window.h = occasion.window.data2;

	      SDL_RenderPresent(renderer);
	    }
	  }*/
	  else if(occasion.type == SDL_KEYDOWN) {
	    switch(occasion.key.keysym.sym) {
	    case SDLK_UP:
	      key_up();
	      break;
	      /*
	    case SDLK_LEFT:
	      key_left();
	      break;
	    case SDLK_RIGHT:
	      key_right();
	      break;
	      */
	    case SDLK_RGUI:
	      key_meta();
	      break;
	    case SDLK_LGUI:
	      key_meta();
	      break;
	    case SDLK_LALT:
	      key_meta();
	      break;
	    case SDLK_ESCAPE:
	      key_meta();
	      break;
	    }
	  }	     
	}

	if(bonuscounter == 0) {phase_end = true; bonuscounter = 100;}
	
	//Clearing the screen
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);


	if(tileflow == 0) {
	  textrend(170, 130, "It is UNIX Epoch time", font);
	  textrend(325, 130, to_string(time(0)), font);
	  textrend(170, 150, "and it is time for...", font);
	  textrend(170, 170, "FreeKLAX", font);
  	  textrend(170, 210, "Press META key to play", font);
	  if(titlecounter == 100) {tileflow = 0.1; titlecounter = 0;}
	}
	if(tileflow == 0.1) {
	  //T‰h‰n pit‰isi saada n‰kyviin myˆs last_score (jos yli 0 eli jos on pelattu yleens‰)
	  textrend(160, 40, "Hi-scores", font);
	  for(int var = 0, ypoint = 90; var != 10; var++) {
	    textrend(160, ypoint, hiscores[var].first, font);
	    textrend(250, ypoint, to_string(hiscores[var].second), font);
	    ypoint += 18;
	  }
	  if(score > 0) {
	  textrend(160, 300, "Last score: ", font);
 	  textrend(245, 300, to_string(score), font);
	  }
	  if(titlecounter == 100) {tileflow = 0; titlecounter = 0;}
	}

	//-Loopissa taas first-iteraattoria inkrementoidaan, kunnes se ei ole end(). Eli iteraation viimeisess‰ loopissa ollaan yksi ennen loppua. Koska vektorissa on kaksi itemi‰, kountteri on 1:ss‰ viimeisell‰ iteraatiossa ja yritet‰‰n samalla tarttua 1:een, joka on sama kuin end()
	//-it[0].thing() on hyvin ep‰tavallinen keino sanoa it->thing()

	//Jos ylimm‰ss‰ (4) on jotain (muuta kuin x), silloinhan voidaan heti piirt‰‰ ne loputkin. sen j‰lkeen voidaan muussa tapauksessa kysy‰, jos 3:ssa on jne. 
	//22 pikseli‰ olisi hyv‰ v‰li
	
	if(tileflow >= 1) {	  
	  
	  if(new_tile == true and tileflow == 1) {
	    //Making a new tile to tile_list, then setting iterator to the last item (=a new tile), then applying randomizing function to that tile
	    tile_vector.push_back(generic_tile);
	    vector<tileclass>::iterator randomizer_iterator = --tile_vector.end();
	    randomizer_iterator->randomize_tile();
	    new_tile = false;
	  }

	  //Background
	  switch(gameround) {
	  case 1: round1.renderfunction(0,0); break;
	  case 2: round2.renderfunction(0,0); break;
	  case 3: round3.renderfunction(0,0); break;
	  }
	  //Damagelights
	  switch(damage) {
	  case 0: ; break;
	  case 1: damlight.renderfunction(210, 193); break;
	  case 2: damlight.renderfunction(210, 193); damlight.renderfunction(267, 193); break;
	  case 3: damlight.renderfunction(210, 193); damlight.renderfunction(267, 193); damlight.renderfunction(323, 193); break;
	  default: damlight.renderfunction(210, 193); damlight.renderfunction(267, 193); damlight.renderfunction(323, 193);
	  }
	  //Paddle position indicator lights
	  indlight.renderfunction(((paddle_x_position-117)/58)*58+167,349);
	  //167 is the x position for the left corner of the first indicator light (from the left). 117 is the difference between the beginning of the first range and pixels on the left side of the screen. 58 is the difference between each range.

  	  textrend(5, 5, "Phase", font);
	  textrend(50, 5, to_string(phase), font);
	  switch(phase_type) {
	  case 0: SDL_RenderCopy(renderer, pattern_texture, NULL, &pattern_textrect); break;
    	  case 1: SDL_RenderCopy(renderer, diag_texture, NULL, &diag_textrect); break;
    	  case 2: SDL_RenderCopy(renderer, points_texture, NULL, &points_textrect); break;
	  }
	  textrend(300, 250, to_string(goal), font);
	  SDL_RenderCopy(renderer, score_texture, NULL, &score_textrect);
	  //	  textrend(180, 230, "Score: ", font);
	  textrend(250, 230, to_string(score), font);

	  //If it is time to move tiles, render and move them, else just render (the second for loop). Having two separate for-loops seems to maximize efficiency
	  if(tileflow == 1 and (SDL_GetTicks() - tiletimer >= gamespeed)) {
	    for(vector<tileclass>::iterator iter = tile_vector.end()-1; iter != tile_vector.begin()-1; --iter) {
	    //	    for(vector<tileclass>::iterator iter = tile_vector.begin(); iter != tile_vector.end(); ++iter) {
	      if(tile_vector.empty()) break;
	      //T‰ss‰ ilmeisesti haetaan siit‰ kulloisestakin vektorin indeksist‰ arvot tilap‰ismuuttujiin ja sitten case-rakenne v‰rin pohjalta -->
	      //	      render_tile((convert_column(iter->show_column_pos())), (iter->show_y_axis_pos()), (iter->show_colour()));
	      render_contile((iter->show_column_pos()), (iter->show_y_axis_pos()), (iter->show_colour()), (iter->show_frame()), (iter->show_reverse()), iter->show_fall());
	      iter->incr_frame();
	      if(iter->advance_tile()) iter++;  //If the current element is removed during the list iterator loop, the iterator must be decremented or otherwise it skips
	    }
	  }
//J‰lkimm‰inen rendauslooppi etuperin:
	  else if(tileflow >= 1) {
	    for(vector<tileclass>::iterator iter2 = tile_vector.end()-1; iter2 != tile_vector.begin()-1; --iter2) {
	      //for(vector<tileclass>::iterator iter2 = tile_vector.begin(); iter2 != tile_vector.end(); ++iter2) {
	      //	      render_tile((convert_column(iter2->show_column_pos())), (iter2->show_y_axis_pos()), (iter2->show_colour()));
	      //VOISIKO TUOSTA POISTAA NOITA SULKEITA
	      render_contile((iter2->show_column_pos()), (iter2->show_y_axis_pos()), (iter2->show_colour()), (iter2->show_frame()), (iter2->show_reverse()), iter2->show_fall());
	    }
	  }
	     
	  
	      /*	  
  	  //If it is time to move tiles, render and move them, else just render (the second for loop). Having two separate for-loops seems to maximize efficiency
	  if(tileflow == 1 and (SDL_GetTicks() - tiletimer >= gamespeed)) {
	    for(list<tileclass>::reverse_iterator iter = tile_list.rbegin(); iter != tile_list.rend(); ++iter) {
	      if(tile_list.empty()) break;
	      //T‰ss‰ ilmeisesti haetaan siit‰ kulloisestakin vektorin indeksist‰ arvot tilap‰ismuuttujiin ja sitten case-rakenne v‰rin pohjalta -->
	      //	      render_tile((convert_column(iter->show_column_pos())), (iter->show_y_axis_pos()), (iter->show_colour()));
	      render_contile((iter->show_column_pos()), (iter->show_y_axis_pos()), (iter->show_colour()), (iter->show_frame()), (iter->show_reverse()), iter->show_fall());
	      iter->incr_frame();
	      if(iter->advance_tile()) iter--;  //If the current element is removed during the list iterator loop, the iterator must be incremented or otherwise it skips the next (or rather: previous) element (because removal causes it to move one step backwards and starting a loop decrements it yet one step)
	    }
	  }
	  else if(tileflow >= 1) {
	    for(list<tileclass>::reverse_iterator iter2 = tile_list.rbegin(); iter2 != tile_list.rend(); ++iter2) {
	      //	      render_tile((convert_column(iter2->show_column_pos())), (iter2->show_y_axis_pos()), (iter2->show_colour()));
	      //VOISIKO TUOSTA POISTAA NOITA SULKEITA
	      render_contile((iter2->show_column_pos()), (iter2->show_y_axis_pos()), (iter2->show_colour()), (iter2->show_frame()), (iter2->show_reverse()), iter2->show_fall());
	    }
	  }
	      */

	  //Rendering player's paddle to its position and moving it if it is moving. Loops will check that it does not go past the points that indicate steady positions (PX0-4)
	  if(paddle_dir == 'L') {
	    //	    for(int i = 0, int != 11; paddle_x_position -= 10;
    	    paddle_x_position -= 10; //JOS MUUTAT TƒTƒ, SITTEN PITƒƒ MUUTTAA TUON LOOPIN RANGEAKIN
	    for(int i = 0; i != 11; i++)
	      if(paddle_x_position - i == PX3 or paddle_x_position - i == PX2 or paddle_x_position - i == PX1 or paddle_x_position - i == PX0) {
		paddle_x_position -= i;
		if(paddle_x_position == PX3) paddle_position = 3;
		else if (paddle_x_position == PX2) paddle_position = 2;
		else if (paddle_x_position == PX1) paddle_position = 1;
		else if (paddle_x_position == PX0) paddle_position = 0;
		paddle_dir = 'S';
		break;
	      }
	    playerpad.renderfunction(paddle_x_position,paddle_y_position, ((keystate[SDL_SCANCODE_RCTRL] == true) ? padup : paddown));
	  }

	  else if(paddle_dir == 'R') {
    	    paddle_x_position += 10;
	    for(int i = 1; i != 11; i++)
	      if(paddle_x_position + i == PX4 or paddle_x_position + i == PX3 or paddle_x_position + i == PX2 or paddle_x_position + i == PX1) {
		paddle_x_position += i;
		if(paddle_x_position == PX4) paddle_position = 4;
		else if (paddle_x_position == PX3) paddle_position = 3;
		else if (paddle_x_position == PX2) paddle_position = 2;
		else if (paddle_x_position == PX1) paddle_position = 1;
		paddle_dir = 'S';
		break;
	      }
	    playerpad.renderfunction(paddle_x_position,paddle_y_position, ((keystate[SDL_SCANCODE_RCTRL] == true) ? padup : paddown));
	    
	    switch(paddle_x_position) {
	    case PX1:
	      paddle_position = 1;
	      paddle_dir = 'S';
	      break;
	    case PX2:
	      paddle_position = 2;
	      paddle_dir = 'S';
	      break;
	    case PX3:
	      paddle_position = 3;
	      paddle_dir = 'S';
	      break;
	    case PX4:
	      paddle_position = 4;
	      paddle_dir = 'S';
	      break;
	    }
	    playerpad.renderfunction(paddle_x_position,paddle_y_position, ((keystate[SDL_SCANCODE_RCTRL] == true) ? padup : paddown));
	  }

	  //if(paddle_dir == 'S') {
	  else {  //if paddle_dir == 'S'
	    switch(paddle_position) {
	    case 0:
	      playerpad.renderfunction(PX0,paddle_y_position, ((keystate[SDL_SCANCODE_RCTRL] == true) ? padup : paddown));
	      break;
	    case 1:
	      playerpad.renderfunction(PX1,paddle_y_position, ((keystate[SDL_SCANCODE_RCTRL] == true) ? padup : paddown));
	      break;
	    case 2:
	      playerpad.renderfunction(PX2,paddle_y_position, ((keystate[SDL_SCANCODE_RCTRL] == true) ? padup : paddown));
	      break;
	    case 3:
	      playerpad.renderfunction(PX3,paddle_y_position, ((keystate[SDL_SCANCODE_RCTRL] == true) ? padup : paddown));
	      break;
	    case 4:
	      playerpad.renderfunction(PX4,paddle_y_position, ((keystate[SDL_SCANCODE_RCTRL] == true) ? padup : paddown));
	      break;
	    }
	  }

	  //Rendering possible tiles on the top of the paddle
	  //The size (non-'x' indeces) of the paddle are derived from paddle's y-position. This supposes that the position is always changed when tiles are loaded/unloaded
	  switch(paddle_y_position) {
	  case PY1: render_paddletiles(1); break;
	  case PY2: render_paddletiles(2); break;
	  case PY3: render_paddletiles(3); break;
	  case PY4: render_paddletiles(4); break;
	  case PY5: render_paddletiles(5); break;
	  }

	  
	  //Rendering the tilepool (from the bottom to up so we can stop when the first empty position is met)
	  for(int columncount = 0, x_count = 141; columncount < 5; columncount++) {
	    for(int poolcount = 4, y_count = 317; poolcount >= 0; poolcount--) {
	      if(tilepool[columncount][poolcount] == 'x' and tileflow < 3) break; //!!!!!!!!!!!!
	      if(winpool[columncount][poolcount] == 'w') {
		if(multicounter <= 5) white_tile.renderfunction(x_count, y_count);
		if(multicounter > 5) cyan_tile.renderfunction(x_count, y_count);
	      }
	      else render_tile(x_count, y_count, tilepool[columncount][poolcount], 1);
	      y_count -= 13;
	    }
	    x_count += 58;
	  }

	  //Rendering a falling tile dropped by the player
	  if(fall_y != 0) {
	    if(!accel) fall_y+=40;
	    if(accel) fall_y+=200;
	    if(fall_y > fall_yd) {
	      drop_tile2();
	    }
	    else {
	      render_tile(fall_cn, fall_y, fall_cr, 1);
	    }
	  }	    
	}

	if(tileflow >= 3 and tileflow < 4) {
	  //Counting the number of empty tiles in the pool
	  if(tileflow == 3.0) {
	    bonuscounter = 0;
	    for(int i = 0; i != 5; i++) {
	      for(int j = 0; j != 5; j++) {
		if(tilepool[i][j] == 'x') bonuscounter++;
	      }
	    }
	    bonuscounter2 = 0;
	    tileflow = 3.1;
	  }
	  for(int k = 0, mark = 0; k != 5; k++) {
	    if(mark == 1) break;
	    for(int l = 0; l != 5; l++) {
	      if(mark == 1) break;
	      if(tilepool[l][k] == 'x') {tilepool[l][k] = 'z'; bonuscounter--; bonuscounter2++; score += 500; mark = 1; break;}
	    }
	  }

	  //Tileflown desimaaleja voi k‰ytt‰‰ taukojen tekemiseen tarvittaessa
	  textrend(250, 230, "Phase completed!", font);
	  textrend(250, 250, "Counting bonuses from empty slots:", font);
	  textrend(250, 270, to_string(bonuscounter2), font);
  	  textrend(265, 270, " x 500 points", font);
	  SDL_Delay(100);
	}

	if(tileflow == 2.4) {
	  sign.renderfunction(100,110);
	  if(score == 0) textrend(200, 130, "Game starts!", font);
  	  else textrend(200, 130, "Next phase", font);
  	  switch(phase_type) {
	  case 0: signstr = "Get "; signstr += to_string(goal); signstr += " patterns"; break;
	  case 1: signstr = "Get "; signstr += to_string(goal); signstr += " diagonals"; break;
	  case 2: signstr = "Get "; signstr += to_string(goal); signstr += " points"; break;
	  }
    	  textrend(200, 165, signstr, font);
  	  textrend(200, 210, "Press meta or control to start", font);
	}

	if(game_over){
	  if(tileflow != 2.5) {tileflow = 2.5; gaov_counter = 0;}
  	  textrend(250, 230, "Game Over!", font);
	  gaov_counter++;
	  if(gaov_counter == 100) {
	    if(which_pos(score) < 11) {
	      new_hilist(getenv("USER"), score, which_pos(score));
	      ofstream writeobj("hiscore.txt");
	      for(int var = 0; var != 10; var++) writeobj << hiscores[var].first << endl << hiscores[var].second << endl;
	      writeobj.close();
	    }
	    game_over = false;
	    tileflow = 0.1;
	  }
	}
	
       	SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0x0);

	//	int lightx = 167;
	//	SDL_RenderDrawPoint(renderer, lightx 
	
	//Refresh screen
	SDL_RenderPresent(renderer);

	if(tileflow < 1) titlecounter++;
	
	if(tileflow == 1 and accel == false) tilecounter++;
	else if(tileflow == 1 and accel == true) tilecounter+=5;
	if(tilecounter >= 80) {new_tile = true; tilecounter = 0;}

	multicounter++;
	if(multicounter == 9) multicounter = 1;
	if(multicounter == 1) accel = false;  //ONKO TƒMƒ JOKIN JƒƒNNE???
   
	if(tileflow == 2) blinkcounter++;
	if(tileflow == 2 and blinkcounter == 20) {
	  blinkcounter = 0;
	  tile_tumble();
	  if(check_pool() == true) tileflow = 2;
	  else {
	    if(goal != 0) tileflow = 1;
	    else tileflow = 3;
	  }
	}
	if(phase_end) new_phase();
	if(bonuscounter == 0) phase_end = true;
	//	if(paddleup) paddleup = false;

	//DEBUG:
	//if(tilecounter = 140) check_pool();
	//FRAMERATE
	timer2 = (SDL_GetTicks() - timer1);
	if((timer2) < 40) SDL_Delay(40 - timer2);   //40 here is derived from 1000 milliseconds divided by 25 (frames per second)
      }
    }
  }
  shutdown();
  return 0;
  //  ProfilerStop(); //DEBUGGING
}


