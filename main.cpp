#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>

using namespace std;

#define nDadi 5
#define FILENAME "risultati.txt"
/*
cose da fare:
Lancio dei dadi

Ad ogni turno il giocatore pu� lanciare i dadi 3 volte. Al primo, si tirano i 5 dadi. Ai successivi 2 lanci, il giocatore pu� scegliere di trattenere uno o pi� dadi favorevoli per concretizzare la combinazione desiderata. Tuttavia, si pu� scegliere anche di non trattenere alcun dado o di non fare ricorso a successivi lanci (ad esempio, nel caso in cui si sia gi� realizzata una combinazione utile).

Combinazioni

Dadi Uguali con 1 (Punteggio = somma dei dadi con 1): si ottiene quando almeno un dado � 1. Il punteggio � la somma dei dadi che riportano 1. Ad esempio: 1-3-4-6-1 vale 2.
Dadi Uguali con 2 (Punteggio = somma dei dadi con 2): si ottiene quando almeno un dado � 2. Il punteggio � la somma dei dadi che riportano 2. Ad esempio: 2-1-2-2-1 vale 6.
Dadi Uguali con 3 (Punteggio = somma dei dadi con 3): si ottiene quando almeno un dado � 3. Il punteggio � la somma dei dadi che riportano 3. Ad esempio: 3-1-3-4-3 vale 9.
Dadi Uguali con 4 (Punteggio = somma dei dadi con 4): si ottiene quando almeno un dado � 4. Il punteggio � la somma dei dadi che riportano 4. Ad esempio: 4-1-2-2-1 vale 4.
Dadi Uguali con 5 (Punteggio = somma dei dadi con 5): si ottiene quando almeno un dado � 5. Il punteggio � la somma dei dadi che riportano 5. Ad esempio: 5-1-5-5-1 vale 15.
Dadi Uguali con 6 (Punteggio = somma dei dadi con 6): si ottiene quando almeno un dado � 6. Il punteggio � la somma dei dadi che riportano 6. Ad esempio: 6-3-2-6-1 vale 12.
Bonus (Punteggio = 35): si ottiene quando la somma dei punteggi per le 6 combinazioni precedenti supera 62.
Scala con 4 (Punteggio = 30): si ottiene quando 4 dei 5 dadi sono ordinati in modo crescente. Ad esempio 2-3-4-5-2 oppure 1-2-3-4-6.
Scala con 5 (Punteggio = 40): si ottiene quando i 5 dadi sono ordinati in modo crescente. Le sole due combinazioni possibili sono: 1-2-3-4-5 oppure 2-3-4-5-6.
Tre dadi uguali (Punteggio = somma dei 5 dadi): si ottiene quando 3 dei cinque dadi solo uguali. Ad esempio 3-3-3-5-2 ecc... Naturalmente � valida anche la combinazione 3-3-3-3-2.
Quattro dadi uguali (Punteggio = somma dei 5 dadi): si ottiene quando 4 dei 5 dadi sono uguali. Ad esempio 5-5-5-5-1 ecc...
Full (Punteggio = 25): coincide con la combinazione del Poker e cio� 3 dadi di un tipo e due di un altro. Ad esempio 4-4-4-1-1 ecc...
Yahtzee (Punteggio = 50): si ottiene con 5 dadi uguali. Ad esempio 1-1-1-1-1 o 4-4-4-4-4 ecc... Se lo Yahtzee viene ripetuto lo si utilizza in un'altra combinazione libera e si aggiungono 100 punti di bonus.
Chance (Punteggio = somma dei 5 dadi): qualsiasi combinazione ottenuta. Questa � una possibilit� da sfruttare quando non si riesce a realizzare nessuna delle combinazioni precedenti o la combinazione realizzata � gi� stata utilizzata precedentemente. Anche questa combinazione pu� essere utilizzata una sola volta.
Segnapunti

Il gioco pu� essere pensato come una tabella da riempire.

Per semplicit�, il conteggio dei punti e lo svolgimento del gioco possono essere annotati in una tabella dove ogni giocatore corrisponde ad una colonna mentre le combinazioni rappresentano le righe. Ad ogni turno deve essere utilizzata una casella a scelta, cio� ogni giocatore deve necessariamente utilizzare una combinazione e prendere il punteggio ottenuto.

 	Giocatore 1	Giocatore 2	Giocatore N
dadi con 1 [tot]
dadi con 2 [tot]
dadi con 3 [tot]
dadi con 4 [tot]
dadi con 5 [tot]
dadi con 6 [tot]
 totale
Bonus se maggiore di 62 [35]
3 dadi uguali [tot]
4 dadi uguali [tot]
Full [25]
Scala con 4 dadi [30]
Scala con 5 dadi [40]
Yahtzee [50]
Chance [tot]
Totale generale
Varianti - Nel corso del tempo, ci sono state numerose variazioni delle regole dello Yahtzee. Alcune semplici, come Yahtzee "obbligata", che si deve giocare riempendo in ordine crescente la tabella dello Yahtzee. Una variante, che sembra nata in italia, � chiamata Jetsi. Le regole indicano tre partite di Yahtzee (con caselle un po' differenti) simultanee, una libera, una obbligata da su in gi�, una obbligata da gi� in su. Simile allo Yahtzee � anche il Kismet, edito da Lakeside.

/*
punteggio = pt
smpt = sommapt*/
int apertureFile(FILE *file);
void inserisciNome(string &nome, FILE *file);
void inserisciData(string &data, FILE *file);
void lancioDadi(int dadi[], bool Scelta[]);
void stampaDadi(int dadi[], bool Scelta[]);
void sceltaDadi(int dadi[], bool Scelta[]);
int calcola(int dadi[], int pt[], int &smPt);
void stampa(int &smPt, int &smPtComputer);
bool FullHouse(int pt[], int dadi[]);
bool Yahtzee(int pt[], int dadi[]);
bool SmallStraight(int pt[], int dadi[]);
bool LargeStraight(int pt[], int dadi[]);
bool ThreeOfAKind(int pt[], int dadi[]);
bool FourOfAKind(int pt[], int dadi[]);
bool Chance(int pt[], int dadi[]);
bool ifSei(int pt[], int dadi[]);
bool ifCinque(int pt[], int dadi[]);
bool ifQuattro(int pt[], int dadi[]);
bool ifTre(int pt[], int dadi[]);
bool ifDue(int pt[], int dadi[]);
void salvataggioPunteggio(int pt[], string nome, int &smPt, FILE *file);
void Computer(int dadi[], bool SceltaComputer[]);
void sceltaPunteggioComputer(int dadi[], int pt[], int &smPtComputer);
int rigiocare();

int main()
{
    srand(time(NULL));
    int pt[12] = {0};
    bool Scelta[nDadi] = {true, true, true, true, true};
    bool SceltaComputer[nDadi] = {true, true, true, true, true};
    int dadi[nDadi];
    int difficolta = 0, smPt = 0, smPtComputer = 0;
    string nome;
    string data;
    FILE *file = fopen(FILENAME, "a");

    apertureFile(file);
    inserisciNome(nome, file);
    inserisciData(data, file);

    while(true){
    Computer(dadi, SceltaComputer);
    Computer(dadi, SceltaComputer);
    Computer(dadi, SceltaComputer);
    sceltaPunteggioComputer(dadi, pt, smPtComputer);
    lancioDadi(dadi, Scelta);
    stampaDadi(dadi, Scelta);
    sceltaDadi(dadi, Scelta);
    lancioDadi(dadi, Scelta);
    stampaDadi(dadi, Scelta);
    sceltaDadi(dadi, Scelta);
    lancioDadi(dadi, Scelta);
    stampaDadi(dadi, Scelta);
    sceltaDadi(dadi, Scelta);
    calcola(dadi, pt, smPt);
    stampa(smPt, smPtComputer);
    salvataggioPunteggio(pt, nome, smPt, file);
    rigiocare();
    }

    fclose(file);
    return 0;
}

int rigiocare()
{
    int scelta = 0;
    cout << "rigiocare si=1no=0" << endl;
    cin >> scelta;
    if (scelta == 1)
    {
        return 1;
    }
    else
    {
        exit(0);
    }
}

void sceltaPunteggioComputer(int dadi[], int pt[], int &smPtComputer)
{
    int punteggioTemp = 0;

    if (Yahtzee(pt, dadi) == true)
    {
        punteggioTemp = 50;
    }
    else if (FullHouse(pt, dadi) == true)
    {
        punteggioTemp = 25;
    }
    else if (LargeStraight(pt, dadi) == true)
    {
        punteggioTemp = 40;
    }
    else if (SmallStraight(pt, dadi) == true)
    {
        punteggioTemp = 30;
    }
    else if (FourOfAKind(pt, dadi) == true)
    {
        punteggioTemp = dadi[0] + dadi[1] + dadi[2] + dadi[3] + dadi[4];
    }
    else if (ThreeOfAKind(pt, dadi) == true)
    {
        punteggioTemp = dadi[0] + dadi[1] + dadi[2] + dadi[3] + dadi[4];
    }
    else if (ifDue(pt, dadi) == true)
    {
        punteggioTemp = 2;
    }
    else if (ifTre(pt, dadi) == true)
    {
        punteggioTemp = 3;
    }
    else if (ifQuattro(pt, dadi) == true)
    {
        punteggioTemp = 4;
    }
    else if (ifCinque(pt, dadi) == true)
    {
        punteggioTemp = 5;
    }
    else if (ifSei(pt, dadi) == true)
    {
        punteggioTemp = 6;
    }
    else if (Chance(pt, dadi) == true)
    {
        punteggioTemp = dadi[0] + dadi[1] + dadi[2] + dadi[3] + dadi[4];
    }
    else
    {
        punteggioTemp = 0;
    }
    smPtComputer += punteggioTemp;
}

void Computer(int dadi[], bool SceltaComputer[])
{
    lancioDadi(dadi, SceltaComputer);
    for (int i = 0; i < nDadi; i++)
        {
            SceltaComputer[i] = rand() % 2;
        }
    return;
}


int apertureFile(FILE *file)
{
    if (file == NULL)
    {
        cout << "errore" << endl;
        cout << "creazione" << endl;
        file = fopen(FILENAME, "w");
        return -1;
    }
    else
    {
        return 0;
    }
    return 0;
}

void inserisciNome(string &nome, FILE *file)
{
    cout << "nome: ";
    cin >> nome;

    fprintf(file, "nome: %s\n", nome.c_str());
}

void inserisciData(string &data, FILE *file)
{
    cout << "data: ";
    cin >> data;

    fprintf(file, "data: %s\n", data.c_str());
}

void lancioDadi(int dadi[], bool Scelta[])
{
    for (int i = 0; i < nDadi; i++)
    {
        if (Scelta[i] == true)
        {
            dadi[i] = rand() % 6 + 1;
        }
    }
}

void stampaDadi(int dadi[], bool Scelta[])
{
    cout << "risultato lancio:" << endl;
    for (int i = 0; i < nDadi; i++)
    {
        cout << i + 1 << " dado -> " << dadi[i] << endl;
    }
}

void sceltaDadi(int dadi[], bool Scelta[])
{
    int scelta = 0;
    cout << "scegli il dado da tenere 0 = exit" << endl;

    while (true)
    {
        cout << "-> ";
        cin >> scelta;
        if (scelta == 0)
        {
            return;
        }

        for (int i = 0; i < nDadi; ++i)
        {
            if (scelta == i + 1)
            {
                if (Scelta[i])
                {
                    Scelta[i] = false;
                    cout << "dado " << i + 1 << " block" << endl;
                }
                else
                {
                    Scelta[i] = true;
                    cout << "dado " << i + 1 << " unblock" << endl;
                }
                break;
            }
        }
    }
}

bool FullHouse(int pt[], int dadi[])
{
    bool FullHouse = false;
    if (dadi[0] == dadi[1] && dadi[2] == dadi[3] && dadi[3] == dadi[4])
    {
        FullHouse = true;
    }
    else if (dadi[0] == dadi[1] && dadi[1] == dadi[2] && dadi[3] == dadi[4])
    {
        FullHouse = true;
    }
    return FullHouse;
}

bool Yahtzee(int pt[], int dadi[])
{
    bool Yahtzee = false;
    if (dadi[0] == dadi[1] && dadi[1] == dadi[2] && dadi[2] == dadi[3] && dadi[3] == dadi[4])
    {
        Yahtzee = true;
    }
    return Yahtzee;
}

bool SmallStraight(int pt[], int dadi[])
{
    bool SmallStraight = false;
    int count = 0;
    for (int i = 0; i < nDadi - 1; i++)
    {
        if (dadi[i] == dadi[i + 1] - 1)
        {
            count++;
        }
    }
    if (count >= 3)
    {
        SmallStraight = true;
    }
    return SmallStraight;
}

bool LargeStraight(int pt[], int dadi[])
{
    bool LargeStraight = false;
    int count = 0;
    for (int i = 0; i < nDadi - 1; i++)
    {
        if (dadi[i] == dadi[i + 1] - 1)
        {
            count++;
        }
    }
    if (count == 4)
    {
        LargeStraight = true;
    }
    return LargeStraight;
}

bool ThreeOfAKind(int pt[], int dadi[])
{
    bool ThreeOfAKind = false;
    if (dadi[0] == dadi[1] && dadi[1] == dadi[2])
    {
        ThreeOfAKind = true;
    }
    else if (dadi[1] == dadi[2] && dadi[2] == dadi[3])
    {
        ThreeOfAKind = true;
    }
    else if (dadi[2] == dadi[3] && dadi[3] == dadi[4])
    {
        ThreeOfAKind = true;
    }
    return ThreeOfAKind;
}

bool FourOfAKind(int pt[], int dadi[])
{
    bool FourOfAKind = false;
    if (dadi[0] == dadi[1] && dadi[1] == dadi[2] && dadi[2] == dadi[3])
    {
        FourOfAKind = true;
    }
    else if (dadi[1] == dadi[2] && dadi[2] == dadi[3] && dadi[3] == dadi[4])
    {
        FourOfAKind = true;
    }
    return FourOfAKind;
}

bool Chance(int pt[], int dadi[])
{
    bool Chance = false;
    int count = 0;
    for (int i = 0; i < nDadi; i++)
    {
        count += dadi[i];
    }
    if (count >= 0)
    {
        Chance = true;
    }
    return Chance;
}

bool ifSei(int pt[], int dadi[])
{
    bool ifSei = false;
    int count = 0;
    for (int i = 0; i < nDadi; i++)
    {
        if (dadi[i] == 6)
        {
            count++;
        }
    }
    if (count >= 1)
    {
        ifSei = true;
    }
    return ifSei;
}

bool ifCinque(int pt[], int dadi[])
{
    bool ifCinque = false;
    int count = 0;
    for (int i = 0; i < nDadi; i++)
    {
        if (dadi[i] == 5)
        {
            count++;
        }
    }
    if (count >= 1)
    {
        ifCinque = true;
    }
    return ifCinque;
}

bool ifQuattro(int pt[], int dadi[])
{
    bool ifQuattro = false;
    int count = 0;
    for (int i = 0; i < nDadi; i++)
    {
        if (dadi[i] == 4)
        {
            count++;
        }
    }
    if (count >= 1)
    {
        ifQuattro = true;
    }
    return ifQuattro;
}

bool ifTre(int pt[], int dadi[])
{
    bool ifTre = false;
    int count = 0;
    for (int i = 0; i < nDadi; i++)
    {
        if (dadi[i] == 3)
        {
            count++;
        }
    }
    if (count >= 1)
    {
        ifTre = true;
    }
    return ifTre;
}

bool ifDue(int pt[], int dadi[])
{
    bool ifDue = false;
    int count = 0;
    for (int i = 0; i < nDadi; i++)
    {
        if (dadi[i] == 2)
        {
            count++;
        }
    }
    if (count >= 1)
    {
        ifDue = true;
    }
    return ifDue;
}

int calcola(int dadi[], int pt[], int &smPt)
{
    int scelta = 0;
    int punteggioTemp = 0;

    cout << "dadi:" << endl;
    for (int i = 0; i < nDadi; i++)
    {
        cout << i + 1 << " dado: " << dadi[i] << endl;
    }

    cout << "combinazioni:" << endl;

    if (ifSei(pt, dadi) == true)
    {
        cout << "1) Sei" << endl;
    }
    if (ifCinque(pt, dadi) == true)
    {
        cout << "2) Cinque" << endl;
    }
    if (ifQuattro(pt, dadi) == true)
    {
        cout << "3) Quattro" << endl;
    }
    if (ifTre(pt, dadi) == true)
    {
        cout << "4) Tre" << endl;
    }
    if (ifDue(pt, dadi) == true)
    {
        cout << "5) Due" << endl;
    }
    if (ThreeOfAKind(pt, dadi) == true)
    {
        cout << "6) Three of a kind" << endl;
    }
    if (FourOfAKind(pt, dadi) == true)
    {
        cout << "7) Four of a kind" << endl;
    }
    if (SmallStraight(pt, dadi) == true)
    {
        cout << "8) Small straight" << endl;
    }
    if (LargeStraight(pt, dadi) == true)
    {
        cout << "9) Large straight" << endl;
    }
    if (FullHouse(pt, dadi) == true)
    {
        cout << "10) Full house" << endl;
    }
    if (Yahtzee(pt, dadi) == true)
    {
        cout << "11) Yahtzee" << endl;
    }
    if (Chance(pt, dadi) == true)
    {
        cout << "12) Chance" << endl;
    }

    cout << "inserisci combinazione 0 = exit" << endl;

    while (true)
    {
        cout << "-- ";
        cin >> scelta;
        if (scelta == 0)
        {
            return 0;
        }

        switch (scelta)
        {
        case 1:
            if (ifSei(pt, dadi) == true)
            {
                punteggioTemp = 6;
            } else {
                cout << "nn puoi ottenere 6" << endl;
            }
            break;
        case 2:
            if (ifCinque(pt, dadi) == true)
            {
                punteggioTemp = 5;
            } else {
                cout << "nn puoi ottenere 5" << endl;
            }
            break;
        case 3:
            if (ifQuattro(pt, dadi) == true)
            {
                punteggioTemp = 4;
            } else {
                cout << "nn puoi ottenere 4" << endl;
            }
            break;
        case 4:
            if (ifTre(pt, dadi) == true)
            {
                punteggioTemp = 3;
            } else {
                cout << "nn puoi ottenere 3" << endl;
            }
            break;
        case 5:
            if (ifDue(pt, dadi) == true)
            {
                punteggioTemp = 2;
            } else {
                cout << "nn puoi ottenere 2" << endl;
            }
            break;
        case 6:
            if (ThreeOfAKind(pt, dadi) == true)
            {
                punteggioTemp = dadi[0] + dadi[1] + dadi[2] + dadi[3] + dadi[4];
            } else {
                cout << "nn puoi ottenere Three Of A Kind" << endl;
            }
            break;
        case 7:
            if (FourOfAKind(pt, dadi) == true)
            {
                punteggioTemp = dadi[0] + dadi[1] + dadi[2] + dadi[3] + dadi[4];
            } else {
                cout << "nn puoi ottenere Four Of A Kind" << endl;
            }
            break;
        case 8:
            if (SmallStraight(pt, dadi) == true)
            {
                punteggioTemp = 30;
            } else {
                cout << "nn puoi ottenere Small Straight" << endl;
            }
            break;
        case 9:
            if (LargeStraight(pt, dadi) == true)
            { punteggioTemp = 40;} else {
                cout << "nn puoi ottenere ottenere Large Straight" << endl;
            }
            break;
        case 10:
            if (FullHouse(pt, dadi) == true)
            { punteggioTemp = 25; } else {
                cout << "nn puoi ottenere Full House" << endl;
            }
            break;
        case 11:
            if (Yahtzee(pt, dadi) == true)
            {
                punteggioTemp = 50;
            } else {
                cout << "nn puoi ottenere Yahtzee" << endl;
            }
            break;
        case 12:
            if (Chance(pt, dadi) == true)
            { punteggioTemp = dadi[0] + dadi[1] + dadi[2] + dadi[3] + dadi[4]; }
            else {
                cout << "nn puoi ottenere Chance" << endl;
            }
            break;
        }
        if (punteggioTemp != 0)
        {
            pt[scelta - 1] = punteggioTemp;
            break;
        }
    }
    for (int i = 0; i < 12; i++)
    {
        smPt += pt[i];
    }
    return 0;
}
void stampa(int &smPt, int &smPtComputer)
{
    cout << "punt. totale " << smPt << " punti" << endl;
    cout << "punt. avv " << smPtComputer << " punti" << endl;
}
void salvataggioPunteggio(int pt[], string nome, int &smPt, FILE *file)
{
    fprintf(file, "pt: ");
    fprintf(file, "%d ", smPt);
}
