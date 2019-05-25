#include "LFSR.h"
#include <iomanip>
int main(int argc, char **argv)
{
    cout<<"Правила ввода"<<endl;
    cout<<setw(80)<<"1.Начальное заполнение регистра-это любое положительное целое число,кроме 0\n2.Полином вводится в формате x^64+x^32+x^2.Полином обязательно должен содержать элемент в степени 64(старшая степень),который должен стоять первым.\n";
    cout<<setw(80)<<"3.Длина последовательности-это целое положительное число."<<endl;
    cout<<"Задайте начальное заполнение регистра: ";
    int64_t seed=0;
    unsigned int n=0;
    cin>>seed;
    try {
        LFSR a (seed);
        string path;
        string poli;
        uint64_t chislo=0;
        cout<<"Введите полином: ";
        cin>>poli;
        chislo=a.Polynomial_Converter(poli);
        ofstream fout;
        cout<<"Введите длину генирируемой последовательности: ";
        cin>>n;
        cout<<"Введите путь к файлу: ";
        cin>>path;
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