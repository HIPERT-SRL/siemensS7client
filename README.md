Protocollo s7

Il protocollo S7 è il protocollo di comunicazione a livello applicativo utilizzato dai PLC Siemens della serie S7 (come S7-300, S7-400, S7-1200, S7-1500) per la comunicazione tra i PLC stessi, con i dispositivi di campo, e con i dispositivi di controllo esterni (come i PC) ed è basato su una comunicazione via MPI (Multi-Point Interface), Profibus, Ethernet (in particolare tramite Profinet).
Questa comunicazione avviene tramite Ethernet e può avvenire in modalità client-server o peer-to-peer, dove un dispositivo S7 (solitamente un PLC) può agire come client o server, a seconda delle necessità dell'applicazione.
Viene utilizzato per leggere e scrivere variabili di memoria del PLC(es. Data Block, IO e Memory) e per comunicare tra PLC e HMI/SCADA(supervisory control and data acquisition).

![Layer](https://github.com/user-attachments/assets/f5aafd65-27a3-4663-bd3f-dcf850e383cc)

A livello hardware la comunicazione tra PLC e la rete avviene attraverso il CP(Communication Processor). Che ne gestisce appunto i vari protocolli di rete e altre funzionalità(es. eleborazione dei pacchetti).

![Architettura_PLC](https://github.com/user-attachments/assets/03241153-4e55-487a-b8b5-ddeb75cec85a)

Il protocollo s7 usa un'implementazione Ethernet che si affida sul ISO TCP (RFC1006) ed è orientato a blocchi.
Le strutture dati che invia sono:
1) Variabili di processo: che possono essere valori numerici, segnali di stati, ecc..
2) Data Block(DB)
3) Stato delle I/0: come segnali di input/output provenienti dai dispositivi di campo(sensori, attuatori)

Il protocollo è function oriented o Command oriented(ad esempio ogni trasmissione contiene un comando o una replica allo stesso).

I comandi inviati hannno la struttura: 
- A header.
- A set of parameters.
- A parameters data.
- A data block.

![Data_Structure](https://github.com/user-attachments/assets/df1fe777-9d7e-42f6-99fb-ed5b09b4ee29)

un esempio può essere:

Leggi 2 byte da DB1 nel PLC con IP 192.168.0.2

La comunicazione è simile al paradigma client/server, dove i server possono essere uno o più PLC e i client possono essere i vari pc attaccati alla rete.

un esempio tra PLC-Pc:

1) Connessione

il client(Pc) stabilisce una connessione di rete con il PLC(Server). Se si utilizza una rete Ethernet, il client si connetterà al PLC tramite l'indirizzo IP del PLC (ad esempio, 192.168.1.100).
La connessione avviene tramite un driver di comunicazione che supporta il protocollo S7, come ad esempio il driver S7-300 o S7-1200 di Siemens.

2) Invio della Richiesta dal Client

Il client invia una richiesta di lettura al PLC Server. La richiesta contiene:

- Il tipo di operazione (in questo caso, una lettura).
- L'indirizzo del blocco dati o della variabile da leggere (ad esempio, la variabile in ingresso I0.0).
- La lunghezza dei dati da leggere (ad esempio, 1 byte).
    
es:
    
Richiesta: "Leggi 1 byte dalla variabile I0.0 nel PLC con IP 192.168.1.100"

3) Elaborazione della Richiesta nel PLC Server

- Il PLC Server riceve la richiesta di lettura dal client.
- Il PLC accede alla variabile di ingresso I0.0 o al blocco dati richiesto, recuperando il valore di stato o il dato desiderato.
- Se la richiesta riguarda un blocco dati, il PLC può leggere i dati dalla memoria interna (Data Block) o dalle variabili di ingresso/uscita.

4) Invio della Risposta dal PLC Server

Il PLC Server invia una risposta al client con i dati richiesti. La risposta contiene i dati letti, che possono essere una singola variabile o una sequenza di byte, a seconda della richiesta.

es:

Risposta: "Dati letti: I0.0 = 1"

5) Utilizzo dei Dati nel Client

Il client riceve i dati inviati dal PLC Server e può utilizzarli per:

- Aggiornare un'interfaccia grafica (come un HMI).
- Utilizzare i dati per scopi di monitoraggio, analisi o controllo.
- Inviare nuove richieste di lettura o scrittura.

![Architettura](https://github.com/user-attachments/assets/50ebb322-d815-4838-bd89-290744defdf9)

le funzioni interne ai plc sono gli FC e gli FB(vedere il glossario per una loro descrizione).

Il principale software per integrare questo protocollo è il TIA Portal che consente agli utenti di configurare la rete, definire gli indirizzi e i parametri di comunicazione e programmare i PLC.

Note:
i dati interni al PLC sono BIg-Endin mentre i dati interni al Pc sono Little-Endin

Glossaro:

Profinet (Ethernet Industrial): Un protocollo di rete basato su Ethernet, specifico per la comunicazione in tempo reale nei sistemi di automazione industriale. 
MPI (Multi-Point Interface): Un protocollo di rete Siemens utilizzato per la comunicazione tra dispositivi Siemens (principalmente per la comunicazione tra PLC o tra PLC e HMI).
FC: è un tipo di blocco di programma in cui il codice esegue una specifica funzione. La caratteristica principale di un FC è che è un blocco senza memoria interna: ogni volta che viene chiamato, esegue le operazioni definite all'interno del blocco e non conserva alcun stato tra le chiamate.
FB(Function Block ): è simile a un FC, ma con una differenza fondamentale: un FB ha memoria interna. Questo significa che può memorizzare lo stato delle sue variabili tra una chiamata e l'altra, e quindi può mantenere informazioni sulla sua esecuzione in corso.
DB: questi blocchi sono usati per strutturare e raggruppare variabili legate ad una funzione specifica 
SCADA:  sono software utilizzati per il monitoraggio remoto e il controllo di impianti industriali. Raccoglie i dati dai PLC S7 e dai dispositivi I/O, li visualizza all'operatore e fornisce strumenti per il controllo e l'analisi in tempo reale.
