#include "LFSR.h"
#include <iomanip>
int main(int argc, char **argv)
{
    int64_t seed=atoi(argv[1]);
    unsigned int n=atoi(argv[3]);
    try {
        LFSR a (seed);
        string path=argv[4];
        string poli=argv[2];
        uint64_t chislo=0;
        chislo=a.Polynomial_Converter(poli);
        ofstream fout;
        fout.open(path);
        if(!fout.is_open())
            throw LFSR_error(string("Неверный путь к файлу"));
        for(unsigned int i=0; i<n; i++){
            fout<<a.LFSR_Galois(chislo);
            fout<<" ";
        }
        fout.close();
    } catch(const LFSR_error & e) {
        cerr<<"Error: "<<e.what()<<endl;
        return 1;
    }
    return 0;
}