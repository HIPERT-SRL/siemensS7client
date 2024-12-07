#include "snap7/examples/cpp/snap7.h"
#include <cstdint>
#include <cstring>
#include <iostream>

#define PLC_IP "10.45.24.31" // Indirizzo IP del PLC 10
#define RACK 0
#define SLOT 2
#define DB_NUMBER 200 // Numero del blocco dati (Data Block)

bool Check(TS7Client &Client, int Result, const char *function) {
  printf("\n");
  printf("+-----------------------------------------------------\n");
  printf("| %s\n", function);
  printf("+-----------------------------------------------------\n");
  if (Result == 0) {
    printf("| Result         : OK\n");
    printf("| Execution time : %d ms\n", Client.ExecTime());
    printf("+-----------------------------------------------------\n");
    // ok++;
  } else {
    printf("| ERROR !!! \n");
    if (Result < 0)
      printf("| Library Error (-1)\n");
    else
      printf("| %s\n", CliErrorText(Result).c_str());
    printf("+-----------------------------------------------------\n");
    // ko++;
  }
  return Result == 0;
}

//------------------------------------------------------------------------------
// List blocks in AG
//------------------------------------------------------------------------------
void ListBlocks(TS7Client &Client) {
  TS7BlocksList List;
  int res = Client.ListBlocks(&List);
  if (Check(Client, res, "List Blocks in AG")) {
    printf("  OBCount  : %d\n", List.OBCount);
    printf("  FBCount  : %d\n", List.FBCount);
    printf("  FCCount  : %d\n", List.FCCount);
    printf("  SFBCount : %d\n", List.SFBCount);
    printf("  SFCCount : %d\n", List.SFCCount);
    printf("  DBCount  : %d\n", List.DBCount);
    printf("  SDBCount : %d\n", List.SDBCount);
  };
}

void S7API CliCompletion(void *usrPtr, int opCode, int opResult) {}

//------------------------------------------------------------------------------
// Multi Read
//------------------------------------------------------------------------------
void MultiRead(TS7Client &Client) {
  int res;

  // Multiread buffers
  word ponte;    // 1 word
  word carrello; // 1 word

  // Prepare struct
  TS7DataItem Items[2];

  // NOTE : *AMOUNT IS NOT SIZE* , it's the number of items

  // Merkers
  Items[0].Area = S7AreaDB;
  Items[0].WordLen = S7WLWord;
  Items[0].DBNumber = 200; // Don't need DB
  Items[0].Start = 26;     // Starting from 0
  Items[0].Amount = 1;     // 16 Items (bytes)
  Items[0].pdata = &ponte;
  // Digital Input bytes
  Items[1].Area = S7AreaDB;
  Items[1].WordLen = S7WLWord;
  Items[1].DBNumber = 200; // Don't need DB
  Items[1].Start = 28;     // Starting from 0
  Items[1].Amount = 1;     // 16 Items (bytes)
  Items[1].pdata = &carrello;

  res = Client.ReadMultiVars(Items, 2);
  if (Check(Client, res, "Multiread Vars")) {
    // Result of Client->ReadMultivars is the "global result" of
    // the function, it's OK if something was exchanged.

    // But we need to check single Var results.
    // Let shall suppose that we ask for 5 vars, 4 of them are ok but
    // the 5th is inexistent, we will have 4 results ok and 1 not ok.

    printf("Dump DB200.DBW26 - Var Result : %d\n", Items[0].Result);
    if (Items[0].Result == 0) {
      byte *buf = reinterpret_cast<byte *>(&ponte);
      ponte = buf[0] * 256 + buf[1]; // Fix endianness
      std::cout << "Posizione Ponte: " << static_cast<float>(ponte) / 100
                << " m \n";
    }
    printf("Dump DB200.DBW28 - Var Result : %d\n", Items[1].Result);
    if (Items[1].Result == 0) {
      byte *buf = reinterpret_cast<byte *>(&carrello);
      carrello = buf[0] * 256 + buf[1]; // Fix endianness
      std::cout << "Posizione Carrello: " << static_cast<float>(carrello) / 100
                << " m \n";
    }
  }
}

int main() {
  std::cout << "Client" << std::endl;
  TS7Client Client;
  // Client->SetAsCallback(CliCompletion,NULL);

  int status = Client.ConnectTo(PLC_IP, RACK, SLOT);
  if (Check(Client, status, "UNIT Connection")) {
    printf("  Connected to   : %s (Rack=%d, Slot=%d)\n", PLC_IP, RACK, SLOT);
    printf("  PDU Requested  : %d bytes\n", Client.PDURequested());
    printf("  PDU Negotiated : %d bytes\n", Client.PDULength());
  };
  if (status == 0) {
    std::cout << "Connesso al PLC con successo." << std::endl;

    ListBlocks(Client);

    MultiRead(Client);

    // Disconnessione dal PLC
    Client.Disconnect();
  } else {
    std::cerr << "Impossibile connettersi al PLC. Codice errore: " << status
              << std::endl;
  }

  std::cout << status << std::endl;
}