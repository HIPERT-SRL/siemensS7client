#include <iostream>
#include "snap7.h"

#define PLC_IP "10.45.24.31"  // Indirizzo IP del PLC 10
#define RACK 0
#define SLOT 2
#define DB_NUMBER 1  // Numero del blocco dati (Data Block)

int main() {
    std::cout << "Client" << std::endl;
    TS7Client Client;

    int status = Client->ConnectTo(PLC_IP, RACK, SLOT);
    if (result == 0) {
        std::cout << "Connesso al PLC con successo." << std::endl;

        // // Scrittura di un valore nel PLC (ad esempio, un intero)
        // int valoreDaScrivere = 1234;
        // byte buffer[4];
        // memcpy(buffer, &valoreDaScrivere, sizeof(int));

        // // Scrittura dei dati nel Data Block 1
        // result = client.WriteArea(S7AreaDB, DB_NUMBER, 0, sizeof(buffer), S7WLByte, buffer);
        // if (result == 0) {
        //     std::cout << "Dati scritti nel DB" << DB_NUMBER << "." << std::endl;
        // } else {
        //     std::cerr << "Errore durante la scrittura dei dati. Codice errore: " << result << std::endl;
        // }

        // // Lettura dei dati dal Data Block 1
        // byte bufferLetto[4];
        // result = client.ReadArea(S7AreaDB, DB_NUMBER, 0, sizeof(bufferLetto), S7WLByte, bufferLetto);
        // if (result == 0) {
        //     int valoreLetto;
        //     memcpy(&valoreLetto, bufferLetto, sizeof(int));
        //     std::cout << "Dati letti dal DB" << DB_NUMBER << ": " << valoreLetto << std::endl;
        // } else {
        //     std::cerr << "Errore durante la lettura dei dati. Codice errore: " << result << std::endl;
        // }

        // // Disconnessione dal PLC
        // client.Disconnect();
    } else {
        std::cerr << "Impossibile connettersi al PLC. Codice errore: " << result << std::endl;
    }

    std::cout << status << std::endl;

}