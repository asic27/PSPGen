#include "LFSR.h"
#include <cctype>
#include <cstdlib>
LFSR::LFSR(int64_t n)
{
    Seed=getValidSeed(n);
}
uint64_t LFSR::Polynomial_Converter(string poli)
{
    poli=getValidPolynomial(poli);
    int deg;
    string prov;
    uint64_t x;
    prov.clear();
    uint64_t chislo=0;
    int len=poli.size();
    for(int i=0; i<=len; i++) {
        if (poli[i]=='^') {
            for(int k=1; poli[i+k]!='+' && (i+k)!=len; k++) {
                prov=prov+poli[i+k];
            }
            deg=atoi(prov.c_str());
            x=1LL<<(deg-1);
            chislo=chislo+x;
            prov.clear();
        }
    }
    return chislo;
}
uint64_t LFSR::LFSR_Galois(uint64_t branch)
{
    uint64_t cont=0;
    for(int i=0; i<64; i++) {
        if (Seed & 0x00000001LL) {
            cont=(cont<<1) | 1;
            Seed = ((Seed ^ branch) >> 1) | 0x8000000000000000LL;
        } else {
            cont=cont<<1;
            Seed >>= 1;
        }
    }
    return cont;
}
string LFSR:: getValidPolynomial(const string poli)
{
    if (poli.empty())
        throw LFSR_error("Empty polynominal");
    for (char  c:poli) {
        if (!isdigit(c) && c!='x' && c!='^' && c!='+')
            throw LFSR_error(string("Invalid polynominal ")+poli);
    }
    for(unsigned int i=0; i<poli.size(); i++)
        if(poli[i]=='^') {
            for(int k=1; poli[i+k]!='+' && (i+k)!=poli.size(); k++) {
                if(!isdigit(poli[i+k]))
                    throw LFSR_error(string("Wrong degree ")+"x"+poli[i]+poli[i+k]);
            }
        }
    if(poli.find("64")==string::npos)
        throw LFSR_error(string("Polynominal degree must be 64"));
    string prov;
    string checktmp="65";
    for(uint i=0; i<=poli.size(); i++) {
        if (poli[i]=='^') {
            prov.clear();
            for(uint k=1; poli[i+k]!='+' && (i+k)!=poli.size(); k++) {
                prov=prov+poli[i+k];
                if(atoi(prov.c_str())>64 || atoi(prov.c_str())>=atoi(checktmp.c_str())) {
                    throw LFSR_error(string("Degree is largest than 64 or either the elements are not entered in descending order of degree or there are elements in one degree"));
                }
            }
            checktmp=prov;
        }
    }
    return poli;
}
int64_t LFSR:: getValidSeed(const int64_t seed)
{
    if(seed<=0LL)
        throw LFSR_error(string("Seed not a number or zero or <1"));
    return seed;
}
