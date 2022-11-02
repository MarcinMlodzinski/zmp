#include "Reader.hh"

bool Reader::init(std::string cmdFile)
{
    cmdFileName = cmdFile;
    return 0;
}

bool Reader::execPreprocesor(std::istringstream &IStrm4Cmds)
{
    std::string Cmd4Preproc = "cpp -P ";
    char Line[LINE_SIZE];
    std::ostringstream OTmpStrm;
    Cmd4Preproc += cmdFileName;
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

// int main()
// {
//     std::istringstream aaa;
//     ExecPreprocesor("opis_dzialan.cmd", aaa);
//     std::cout << aaa.str();
// }
