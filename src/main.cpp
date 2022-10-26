#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include "Interp4Command.hh"
#include "MobileObj.hh"

using namespace std;


int main()
{
  void *pLibHnd_Move = dlopen("libInterp4Move.so",RTLD_LAZY);
  void *pLibHnd_Rotate = dlopen("libInterp4Rotate.so",RTLD_LAZY);
  void *pLibHnd_Set = dlopen("libInterp4Set.so",RTLD_LAZY);
  void *pLibHnd_Pause = dlopen("libInterp4Pause.so",RTLD_LAZY);
  Interp4Command *(*pCreateCmd_Move)(void);
  Interp4Command *(*pCreateCmd_Rotate)(void);
  Interp4Command *(*pCreateCmd_Set)(void);
  Interp4Command *(*pCreateCmd_Pause)(void);
  void *pMove;
  void *pRotate;
  void *pSet;
  void *pPause;

  if (!pLibHnd_Move) {
    cerr << "!!! Brak biblioteki: Interp4Move.so" << endl;
  }
  if (!pLibHnd_Rotate){
    cerr << "!!! Brak biblioteki: Interp4Rotate.so" <<endl;
  }
  if (!pLibHnd_Set){
    cerr << "!!! Brak biblioteki: Interp4Set.so"<<endl;
  }
  if (!pLibHnd_Pause){
    cerr << "!!! Brak biblioteki: Interp4Pause.so"<<endl;
  }
  if (!pLibHnd_Move || !pLibHnd_Rotate || !pLibHnd_Set || !pLibHnd_Pause){
    return 1;
  }


  pMove = dlsym(pLibHnd_Move,"CreateCmd");
  pRotate = dlsym(pLibHnd_Rotate, "CreateCmd");
  pSet = dlsym(pLibHnd_Set, "CreateCmd");
  pPause = dlsym(pLibHnd_Pause, "CreateCmd");
  if (!pMove) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
  }
  if (!pRotate) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
  }
  if (!pSet) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
  }
  if (!pPause) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
  }
  if (!pMove || !pRotate || !pSet || !pPause){
    return 1;
  }
  pCreateCmd_Move = *reinterpret_cast<Interp4Command* (**)(void)>(&pMove);
  pCreateCmd_Rotate = *reinterpret_cast<Interp4Command* (**)(void)>(&pRotate);
  pCreateCmd_Set = *reinterpret_cast<Interp4Command* (**)(void)>(&pSet);
  pCreateCmd_Pause = *reinterpret_cast<Interp4Command* (**)(void)>(&pPause);
  


  Interp4Command *pCmdMove = pCreateCmd_Move();
  Interp4Command *pCmdRotate = pCreateCmd_Rotate();
  Interp4Command *pCmdSet = pCreateCmd_Set();
  Interp4Command *pCmdPause = pCreateCmd_Pause();

  cout << endl;
  cout << pCmdMove->GetCmdName() << endl;
  cout << endl;
  pCmdMove->PrintSyntax();
  cout << endl;
  pCmdMove->PrintCmd();
  cout << endl;

  cout << endl;
  cout << pCmdRotate->GetCmdName() << endl;
  cout << endl;
  pCmdRotate->PrintSyntax();
  cout << endl;
  pCmdRotate->PrintCmd();
  cout << endl;

  cout << endl;
  cout << pCmdSet->GetCmdName() << endl;
  cout << endl;
  pCmdSet->PrintSyntax();
  cout << endl;
  pCmdSet->PrintCmd();
  cout << endl;

  cout << endl;
  cout << pCmdPause->GetCmdName() << endl;
  cout << endl;
  pCmdPause->PrintSyntax();
  cout << endl;
  pCmdPause->PrintCmd();
  cout << endl;
  
  delete pCmdMove;
  delete pCmdRotate;
  delete pCmdSet;
  delete pCmdPause;

  dlclose(pLibHnd_Move);
  dlclose(pLibHnd_Rotate);
  dlclose(pLibHnd_Set);
  dlclose(pLibHnd_Pause);
}
