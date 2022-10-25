#include <cstdio>
#include <sstream>
#include <string>
#include <iostream>
#define LINE_SIZE 500

bool ExecPreprocesor(const char *NazwaPliku, std::istringstream &IStrm4Cmds)
{
    std::string Cmd4Preproc = "cpp -P ";
    char Line[LINE_SIZE];
    std::ostringstream OTmpStrm;
    Cmd4Preproc += NazwaPliku;
    FILE *pProc = popen(Cmd4Preproc.c_str(), "r");

    if (!pProc)
        return false;

    while (fgets(Line, LINE_SIZE, pProc))
    {
        OTmpStrm << Line;
    }

    IStrm4Cmds.str(OTmpStrm.str());
    return pclose(pProc) == 0;
}

int main()
{
    std::istringstream aaa;
    ExecPreprocesor("src/main.cpp", aaa);
    std::cout << aaa.str();
}
