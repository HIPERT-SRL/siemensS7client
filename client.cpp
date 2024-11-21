#include <iostream>
#include "snap7.h"

#define PLC_IP "10.45.24.31"  // Indirizzo IP del PLC 10
#define RACK 0
#define SLOT 2
#define DB_NUMBER 1  // Numero del blocco dati (Data Block)

bool Check(TS7Client &Client, int Result, const char * function)
{
    printf("\n");
    printf("+-----------------------------------------------------\n");
    printf("| %s\n",function);
    printf("+-----------------------------------------------------\n");
    if (Result==0) {
        printf("| Result         : OK\n");
        printf("| Execution time : %d ms\n",Client.ExecTime());
        printf("+-----------------------------------------------------\n");
        // ok++;
    }
    else {
        printf("| ERROR !!! \n");
        if (Result<0)
            printf("| Library Error (-1)\n");
        else
            printf("| %s\n",CliErrorText(Result).c_str());
        printf("+-----------------------------------------------------\n");
        // ko++;
    }
    return Result==0;
}
void S7API CliCompletion(void *usrPtr, int opCode, int opResult)
{
}

int main() {
    std::cout << "Client" << std::endl;
    TS7Client Client;
    Client->SetAsCallback(CliCompletion,NULL);

    int status = Client.ConnectTo(PLC_IP, RACK, SLOT);
    if (Check(Client, status,"UNIT Connection")) {
          printf("  Connected to   : %s (Rack=%d, Slot=%d)\n",PLC_IP,RACK,SLOT);
          printf("  PDU Requested  : %d bytes\n",Client.PDURequested());
          printf("  PDU Negotiated : %d bytes\n",Client.PDULength());
    };
    if (status == 0) {
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
        std::cerr << "Impossibile connettersi al PLC. Codice errore: " << status << std::endl;
    }

    std::cout << status << std::endl;

}