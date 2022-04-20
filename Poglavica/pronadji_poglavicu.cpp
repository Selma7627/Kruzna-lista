#include <iostream>
#include <list>
struct Clan{
    int redni_broj;
    Clan *sljedeci;
};
// N - broj clanova, M - korak razbrajanja
Clan *KreirajKruznuListu(int broj_cvorova){
        Clan *pocetak=nullptr, *prethodni;
        for(int i=0; i<broj_cvorova; i++){
            Clan *novi(new Clan{i+1, nullptr});
            if(!pocetak) pocetak=novi;
            else prethodni->sljedeci=novi;
            prethodni=novi;
        }
        prethodni->sljedeci=pocetak;
        return pocetak;
}
int Poglavica(int N, int M, bool ispisi_odstranjene=false){
        Clan *pocetak=KreirajKruznuListu(N);
    int brojac(1),vel=N;
    Clan *trenutni=pocetak, *prethodni=pocetak;
    while(vel>1){
        if(brojac%M==0) {
            if(ispisi_odstranjene) std::cout << trenutni->redni_broj << " ";
            Clan *temp_pok;
            temp_pok=trenutni->sljedeci;
            delete trenutni;
            prethodni->sljedeci=temp_pok;
            trenutni=temp_pok;
            vel--;
        }
        else {
            prethodni=trenutni;
            trenutni=trenutni->sljedeci;
        }
        brojac++;
    }
    
    int trazeni_redni_broj=trenutni->redni_broj;
    trenutni->sljedeci=nullptr;
    delete trenutni;
    return trazeni_redni_broj;
}
int SigurnoMjesto(int M, int N1, int N2){
    std::list<int> lista_poglavica;
    for(int i=N1; i<=N2; i++)
        lista_poglavica.push_back(Poglavica(i,M));
    
    for(int i=1; i<=N2; i++){
        int brojac=0;
        for(std::list<int>::iterator it= lista_poglavica.begin(); it!=lista_poglavica.end(); it++)
            if(i==*it) brojac++;
        if(brojac==0) return i;
    }
    return 0;
}
int main ()
{
    std::cout << "Unesi broj punoljetnih clanova (N): ";
    int broj_punoljetnih;
    std::cin >> broj_punoljetnih;
    std::cout << "Unesi korak razbrajanja (M): ";
    int korak_razbrajanja;
    std::cin >> korak_razbrajanja;
    std::cout << "Unesi raspon (N1-N2): ";
    int pocetak,kraj;
    std::cin >> pocetak>> kraj;
    std::cout << "Redni broj osobe koja postaje poglavica: ";
    std::cout << Poglavica(broj_punoljetnih, korak_razbrajanja)<< " ";
    std::cout << "Sigurno mjesto: ";
    std::cout << SigurnoMjesto(korak_razbrajanja,pocetak,kraj);
	return 0;
}
