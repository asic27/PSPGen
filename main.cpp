#include "LFSR.h"
#include <fstream>
int main(int argc, char **argv)
{
    if (argc!=5 ) {
        throw LFSR_error(string("Wrong arguments"));
    }
    int64_t seed=stoull(argv[1]);
    int n=atoi(argv[3]);
    try {
        if(n<=0) {
            throw LFSR_error(string("Длина последовательности меньше или равна 0"));
        }
        LFSR a (seed);
        string path=argv[4];
        string poli=argv[2];
        uint64_t chislo=0;
        chislo=a.Polynomial_Converter(poli);
        ofstream fout;
        fout.open(path);
        if(!fout.is_open())
            throw LFSR_error(string("Неверный путь к файлу"));
        for(int i=0; i<n; i++) {
            if(fout.good()) {
                fout<<a.LFSR_Galois(chislo);
                fout<<" ";
            }
        }
        fout.close();
    } catch(const LFSR_error & e) {
        cerr<<"Error: "<<e.what()<<endl;
        return 1;
    }
    return 0;
}
