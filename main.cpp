#include <iostream>
#include <string.h>
#include <vector>
/*Tema 13. Se dau următoarele clase:
- Clasa Localitate(char *denumire; int cod; long nr_locuitori)
- Clasa Oras(int nrSpitaledeUrgenta, char* numePrimar) : Localitate
- Clasa ResedintaDeJudet(char* numePresedinteConsiliuJudetean) : Oras
- Clasa Judet(Localitate **l, char* numePrefect)
Se doreste să se afle dacă populatia fiecarui judet din tara este deservita de un numar suficient de spitale
 cunoscandu-se faptul că este necesar să avem macar 2 spitale de urgență la suta de mii de locuitori pentru un oras obisnuit,
 iar fiecare reședința de județ este dotată cu 1 spital judetean în plus,
 gândit să poată deservi 200 de mii de locuitori ai județului.
 În cazul în care un Judet nu este conform, am dori să cunoaștem numele prefectului pentru a îi comunica situația.
*/
using namespace std;
//- Clasa Localitate(char *denumire; int cod; long nr_locuitori)
class Localitate{
protected:
    char *denumire;
    int cod;
    long nr_locuitori;
public:
    //set
    void set_denumire(char s[256]);
    void set_cod(int cod);
    void set_nr_locuitori(long nr_locuitori);
    //get
    char* get_denumire();
    int get_cod();
    long get_nr_locuitori();
    //Constructori
    //Constructor fara parametrii
    Localitate(){
        this->denumire=NULL;
        this->cod=0;
        this->nr_locuitori=0;
    }
    //Constructor de copiere
    Localitate(const Localitate &localitate){
        this->denumire=new char [256];
        strcpy(this->denumire,localitate.denumire);
        this->cod=localitate.cod;
        this->nr_locuitori=localitate.nr_locuitori;
    }
    //Constructor cu parametrii
    Localitate(const char *denumire, int cod,long nr_locuitori){
        this->denumire=new char [256];
        strcpy(this->denumire,denumire);
        this->cod=cod;
        this->nr_locuitori=nr_locuitori;
    }
    //Destructor
    ~Localitate(){
        if(denumire!=NULL){
            delete[]denumire;
        }
        denumire=NULL;
    }
    //supradefinire
    Localitate &operator=(const Localitate &localitate);
    friend istream& operator>>(istream &is, Localitate &localitate){
        return localitate.read(is);
    }
    virtual  istream& read(istream &is){
        cout << "Introduceti denumirea localitatii:\n";
        if( denumire == NULL)
            denumire=new char[256];
        is.getline(denumire,256);
        cout << "Introduceti codul localitatii:\n";
        is >> cod;
        cout << "Introduceti numarul de locuitori: \n";
        is >> nr_locuitori;
        is.get();
        return is;
    }
    friend ostream& operator<<(ostream &os,Localitate &localitate){
        return localitate.print(os);
    }
    virtual ostream &print(ostream &os){
        os << "Denumire Localitate: " << denumire << " Cod Localitate: " << cod << " Numar de Locuitori: " << nr_locuitori;
        os << '\n';
        return os;
    }
    virtual int esteResedinta(){
        return 0;
    }

};
Localitate &Localitate::operator=(const Localitate &localitate) {
    if(localitate.denumire==NULL){
        if(this->denumire!=NULL){
            char *del=this->denumire;
            this->denumire=NULL;
            delete[] del;
        }
    }
    else{
        if(this->denumire==NULL)
            this->denumire=new char[256];
        strcpy(this->denumire,localitate.denumire);
    }
    this->cod=localitate.cod;
    this->nr_locuitori=localitate.nr_locuitori;
    return *this;
}
//set - Localitate
void Localitate::set_denumire(char s[256])  {
    if(this->denumire==NULL)
        this->denumire=new char[256];
    strcpy(this->denumire,s);
}
void Localitate::set_cod(int cod) {
    this->cod=cod;
}
void Localitate::set_nr_locuitori(long nr_locuitori) {
    this->nr_locuitori=nr_locuitori;
}
//get - Localitate
char* Localitate::get_denumire() {
    return this->denumire;
}
int Localitate::get_cod() {
    return this->cod;
}
long Localitate::get_nr_locuitori() {
    return nr_locuitori;
}
//- Clasa Oras(int nrSpitaledeUrgenta, char* numePrimar) : Localitate
class Oras: public Localitate{
protected:
    int nrSpitaledeUrgenta;
    char *numePrimar;
public:
    //set
    void set_nrSpitaledeUrgenta(int nrSpitale);
    void set_numePrimar(char s[256]);
    //get
    int get_nrSpitaledeUrgenta();
    char* get_numePrimar();
    //Constructori
    //Constructor fara parametrii
    Oras():Localitate(){
        this->numePrimar=NULL;
        this->nrSpitaledeUrgenta=0;
    }
    //Constructor de copiere
    Oras(const Oras &oras): Localitate(oras){
        this->nrSpitaledeUrgenta=oras.nrSpitaledeUrgenta;
        this->numePrimar=new char[256];
        strcpy(this->numePrimar,oras.numePrimar);
    }
    //Constructor cu parametrii
    Oras(const char *denumire, int cod, long nr_locuitori,const char *nume, int nrSpitale){
        this->denumire=new char [256];
        strcpy(this->denumire,denumire);
        this->cod=cod;
        this->nr_locuitori=nr_locuitori;
        this->numePrimar=new char [256];
        strcpy(this->numePrimar,nume);
        this->nrSpitaledeUrgenta=nrSpitale;
    }
    //Destructor
    ~Oras(){
        if(denumire!=NULL)
            delete[] denumire;
        denumire=NULL;
        if(numePrimar!=NULL)
            delete[] numePrimar;
        numePrimar=NULL;
    }
    //supradefinirea
    Oras &operator=(const Oras &oras);
    /*friend istream& operator>>(istream &is, Oras &oras){
        return oras.read(is);
    }*/
    virtual istream& read(istream &is){
        cout << "Introduceti denumirea orasului:\n";
        if( denumire == NULL)
            denumire=new char[256];
        is.getline(denumire,256);
        cout << "Introduceti codul orasului:\n";
        is >> cod;
        cout << "Introduceti numarul de locuitori: \n";
        is >> nr_locuitori;
        is.get();
        cout << "Introduceti numele primarului:\n";
        if( numePrimar == NULL)
            numePrimar=new char[256];
        is.getline(numePrimar,256);
        cout << "Introduceti numarul de spitale de urgenta:\n";
        is >> nrSpitaledeUrgenta;
        return is;
    }
    virtual ostream &print(ostream &os){
        os << "Denumire Oras: " << denumire << " Cod Oras: " << cod << " Numar de Locuitori: " << nr_locuitori << " Nume Primar: " << numePrimar << " Numar de Spitale de Urgenta: " << nrSpitaledeUrgenta;
        os << '\n';
        return os;
    }
    virtual int esteResedinta(){
        return 1;
    }
};
Oras & Oras::operator=(const Oras &oras){
    if(oras.numePrimar==NULL){
        if(this->numePrimar!=NULL){
            char *del=this->numePrimar;
            this->numePrimar=NULL;
            delete[] del;
        }
    }
    else{
        if(this->numePrimar==NULL)
            this->numePrimar=new char[256];
        strcpy(this->numePrimar,oras.numePrimar);
    }
    this->nrSpitaledeUrgenta=oras.nrSpitaledeUrgenta;
    Localitate::operator=(oras);
    return *this;
}

void Oras::set_nrSpitaledeUrgenta(int nrSpitale) {
    this->nrSpitaledeUrgenta=nrSpitale;
}
void Oras::set_numePrimar(char *s) {
    if(this->numePrimar==NULL)
        this->numePrimar=new char[256];
    strcpy(this->numePrimar,s);
}
int Oras::get_nrSpitaledeUrgenta() {
    return this->nrSpitaledeUrgenta;
}
char * Oras::get_numePrimar() {
    return this->numePrimar;
}
//- Clasa ResedintaDeJudet(char* numePresedinteConsiliuJudetean) : Oras
class ResedintaDeJudet : public Oras{
protected:
    char *numePresedinteConsiliuJudetean;
public:
    //set
    void set_numePresedinteConsiliuJudetean(char *nume);
    //get
    char* get_numePresedinteConsiliuJudetean();
    //Constructori
    //Constructori fara parametrii
    ResedintaDeJudet():Oras(){
        this->numePresedinteConsiliuJudetean=NULL;
    }
    //Constructor de Copiere
    ResedintaDeJudet(const ResedintaDeJudet &resedintaDeJudet): Oras(resedintaDeJudet){
        this->numePresedinteConsiliuJudetean=new char[256];
        strcpy(this->numePresedinteConsiliuJudetean,resedintaDeJudet.numePresedinteConsiliuJudetean);
    }
    //Constructor cu parametrii
    ResedintaDeJudet(const char *denumire, int cod, long nr_locuitori,const char *nume, int nrSpitale, const char *numePresedinte){
        this->denumire=new char [256];
        strcpy(this->denumire,denumire);
        this->cod=cod;
        this->nr_locuitori=nr_locuitori;
        this->numePrimar=new char [256];
        strcpy(this->numePrimar,nume);
        this->nrSpitaledeUrgenta=nrSpitale;
        this->numePresedinteConsiliuJudetean=new char [256];
        strcpy(this->numePresedinteConsiliuJudetean,numePresedinte);
    }
    //Destructor
    ~ResedintaDeJudet(){
        if(denumire!=NULL)
            delete[] denumire;
        denumire=NULL;
        if(numePrimar!=NULL)
            delete[] numePrimar;
        numePrimar=NULL;
        if(numePresedinteConsiliuJudetean!=NULL)
            delete[] numePresedinteConsiliuJudetean;
        numePresedinteConsiliuJudetean=NULL;
    }
    //supraincarcare
    ResedintaDeJudet &operator=(const ResedintaDeJudet &resedintaDeJudet);
    virtual istream& read(istream &is){
        cout << "Introduceti denumirea orasului:\n";
        if( denumire == NULL)
            denumire=new char[256];
        is.getline(denumire,256);
        cout << "Introduceti codul orasului:\n";
        is >> cod;
        cout << "Introduceti numarul de locuitori: \n";
        is >> nr_locuitori;
        is.get();
        cout << "Introduceti numele primarului:\n";
        if( numePrimar == NULL)
            numePrimar=new char[256];
        is.getline(numePrimar,256);
        cout << "Introduceti numarul de spitale de urgenta:\n";
        is >> nrSpitaledeUrgenta;
        cout << "Introduceti numele presedintelui consiliului judetean:\n";
        is.get();
        if( numePresedinteConsiliuJudetean == NULL)
            numePresedinteConsiliuJudetean = new char[256];
        is.getline(numePresedinteConsiliuJudetean,256);
        return is;
    }
    virtual ostream &print(ostream &os){
        os << "Denumire Oras: " << denumire << " Cod Oras: " << cod << " Numar de Locuitori: " << nr_locuitori << " Nume Primar: " << numePrimar << " Numar de Spitale de Urgenta: " << nrSpitaledeUrgenta << "Numele Presedintelui Consiliului Judetean: " << numePresedinteConsiliuJudetean;
        os << '\n';
        return os;
    }
    int esteResedinta(){
        return 2;
    }

};
ResedintaDeJudet & ResedintaDeJudet::operator=(const ResedintaDeJudet &resedintaDeJudet) {
        if(resedintaDeJudet.numePresedinteConsiliuJudetean==NULL){
            if(this->numePresedinteConsiliuJudetean!=NULL){
                char *del=this->numePresedinteConsiliuJudetean;
                this->numePresedinteConsiliuJudetean=NULL;
                delete[] del;
            }
        }
        else{
            if(this->numePresedinteConsiliuJudetean==NULL)
                this->numePresedinteConsiliuJudetean=new char[256];
            strcpy(this->numePresedinteConsiliuJudetean,resedintaDeJudet.numePresedinteConsiliuJudetean);
        }
        Oras::operator=(resedintaDeJudet);
        return *this;
}
void ResedintaDeJudet::set_numePresedinteConsiliuJudetean(char *nume) {
    if(this->numePresedinteConsiliuJudetean==NULL)
        this->numePresedinteConsiliuJudetean = new char[256];
    strcpy(this->numePresedinteConsiliuJudetean,nume);
}
char * ResedintaDeJudet::get_numePresedinteConsiliuJudetean() {
        return this->numePresedinteConsiliuJudetean;
}
//- Clasa Judet(Localitate *l, char* numePrefect)
/*
class Judet{
protected:
    Localitate *localitati;
    int nrLocalitati;
    char *numePrefect;
public:
    //set
    void set_Localitate(Localitate *v,int n);
    void set_nrLocalitati(int n);
    void set_numePrefect(char *nume);
    //get
    Localitate* get_Localitate();
    int get_nrLocalitati();
    char* get_numePerfect();
    //Constructori
    //Constructor fara parametrii
    Judet(){
        this->localitati=NULL;
        this->nrLocalitati=0;
        this->numePrefect=NULL;
    }
    Judet(const Judet& judet){
        this->localitati=new Localitate[judet.nrLocalitati];
        this->nrLocalitati=judet.nrLocalitati;
        for(int i=0;i<judet.nrLocalitati;++i)
            this->localitati[i]=judet.localitati[i];
        this->numePrefect=new char[256];
        strcpy(this->numePrefect,judet.numePrefect);
    }
    //Constructor cu parametrii
    Judet(const Localitate *v, int n, const char *nume){
        this->localitati=new Localitate[n];
        this->nrLocalitati=n;
        for(int i=0;i<n;++i)
            this->localitati[i]=v[i];
        this->numePrefect=new char[256];
        strcpy(this->numePrefect,nume);
    }
    //Destructor
    ~Judet(){
        if(localitati!=NULL)
            delete[] localitati;
        localitati=NULL;
        if(numePrefect!=NULL)
            delete[] numePrefect;
        numePrefect=NULL;
    }
    //supraincarcare
    Judet &operator=(const Judet &judet);
    friend istream& operator>>(istream &is, Judet &judet);
    friend ostream& operator<<(ostream &os, const Judet &judet);
};
Judet & Judet::operator=(const Judet &judet) {
    if(judet.numePrefect==NULL){
            if(this->numePrefect!=NULL){
                char *del=this->numePrefect;
                this->numePrefect=NULL;
                delete[] del;
            }
        }
        else{
            if(this->numePrefect==NULL)
                this->numePrefect=new char[256];
            strcpy(this->numePrefect,judet.numePrefect);
        }
    if(judet.localitati==NULL){
        if(this->localitati!=NULL){
            Localitate *del=this->localitati;
            this->localitati=NULL;
            delete[] del;
        }
    }
    else{
        if(this->localitati==NULL)
            this->localitati=new Localitate[judet.nrLocalitati];
        for(int i=0;i<judet.nrLocalitati;++i)
            this->localitati[i]=judet.localitati[i];
    }
    this->nrLocalitati=judet.nrLocalitati;
    return *this;
}
istream &operator>>(istream &is, Judet &judet){
    cout<<"Introduceti numarul de localitati din judet:\n";
    is >> judet.nrLocalitati;
    is.get();
    cout<<"Introduceti localitati din judet:\n";
    if(judet.localitati==NULL)
        judet.localitati=new ResedintaDeJudet[judet.nrLocalitati];
    char optiune;
    for(int i=0;i<judet.nrLocalitati;++i){
        cout<<"optiune = \n";
        is.get(optiune);
        is.get();
        if(optiune == 'R'){
            ResedintaDeJudet *resedintaDeJudet;
            is >> *resedintaDeJudet;
            judet.localitati[i] = *resedintaDeJudet;
        }
        else
            if(optiune == 'O'){
                Oras oras;
                is >> oras;
                judet.localitati[i] =  oras;
            }
            else{
                Localitate localitate;
                is >> localitate;
                judet.localitati[i] =  localitate;
            }
    }
    is.get();
    cout<<"Introduceti numele prefectului:\n";
    if(judet.numePrefect==NULL)
        judet.numePrefect=new char[256];
    is.getline(judet.numePrefect,256);
    return is;
}
ostream &operator<<(ostream &os, const Judet &judet){
    os << "Numarul de Localitati: "<<judet.nrLocalitati << '\n';
    os << "Localitati:\n";
    for(int i=0;i<judet.nrLocalitati;++i)
        os << judet.localitati[i];
    os << "Numele Prefectului: " << judet.numePrefect;
    os <<'\n';
    return os;
}
void Judet::set_Localitate(Localitate *v,int n) {
    localitati = new Localitate[n];
    nrLocalitati = n;
    for(int i=0; i<n;++i)
        localitati[i]=v[i];
}
void Judet::set_nrLocalitati(int n) {
    nrLocalitati = n;
}
void Judet::set_numePrefect(char *nume) {
    if(this->numePrefect==NULL)
        this->numePrefect=new char[256];
    strcpy(this->numePrefect,nume);
}
Localitate * Judet::get_Localitate() {
    return this->localitati;
}
int Judet::get_nrLocalitati() {
    return this->nrLocalitati;
}
char * Judet::get_numePerfect() {
    return this->numePrefect;
}*/

class Judet{
protected:
    Localitate **localitati;
    int nrLocalitati;
    char *numePrefect;
public:
    //set
    void set_Localitate(Localitate *v,int n);
    void set_nrLocalitati(int n);
    void set_numePrefect(char *nume);
    //get
    Localitate** get_Localitate();
    int get_nrLocalitati();
    char* get_numePerfect();
    //Constructori
    //Constructor fara parametrii
    Judet(){
        this->localitati=NULL;
        this->nrLocalitati=0;
        this->numePrefect=NULL;
    }
    Judet(const Judet& judet):localitati(NULL){
        *this = judet;
    }
    //Constructor cu parametrii
    /*Judet(const Localitate **v, int n, const char *nume){
        this->localitati=new Localitate*[n];
        this->nrLocalitati=n;
        for(int i=0;i<n;++i)
            this->localitati[i]=v[i];
        this->numePrefect=new char[256];
        strcpy(this->numePrefect,nume);
    }*/
    //Destructor
    ~Judet(){
        for(int i=0;i<nrLocalitati;++i)
            delete localitati[i];
        delete[] localitati;
        if(numePrefect!=NULL)
            delete[] numePrefect;
        numePrefect=NULL;
    }
    //supraincarcare
    Judet &operator=(const Judet &judet);
    friend istream& operator>>(istream &is, Judet &judet);
    friend ostream& operator<<(ostream &os, const Judet &judet);
};
Judet & Judet::operator=(const Judet &judet) {
    if(this->localitati!=NULL){
        for(int i=0;i<this->nrLocalitati;++i)
            delete this->localitati[i];
        delete[] this->localitati;
    }
    if(judet.numePrefect==NULL){
        if(this->numePrefect!=NULL){
            char *del=this->numePrefect;
            this->numePrefect=NULL;
            delete[] del;
        }
    }
    else{
        if(this->numePrefect==NULL)
            this->numePrefect=new char[256];
        strcpy(this->numePrefect,judet.numePrefect);
    }
    this->localitati = new Localitate*[judet.nrLocalitati];
    this->nrLocalitati=judet.nrLocalitati;
    for(int i = 0;i < this->nrLocalitati;++i)
        *(this->localitati[i])=*(judet.localitati[i]);
    return *this;
}
istream &operator>>(istream &is, Judet &judet){
    cout<<"Introduceti numarul de localitati din judet:\n";
    is >> judet.nrLocalitati;
    is.get();
    cout<<"Introduceti localitati din judet:\n";
    if(judet.localitati==NULL)
        judet.localitati=new Localitate*[judet.nrLocalitati];
    char optiune;
    for(int i=0;i<judet.nrLocalitati;++i){
        cout<<"optiune = \n";
        is.get(optiune);
        is.get();
        if(optiune == 'R'){
            ResedintaDeJudet *resedintaDeJudet= new ResedintaDeJudet;
            //ResedintaDeJudet &adr = judet.localitati[i];
            is >> *resedintaDeJudet;
            judet.localitati[i] = resedintaDeJudet;
        }
        else
        if(optiune == 'O'){
            Oras *oras = new Oras;
            is >> *oras;
            judet.localitati[i] =  oras;
        }
        else{
            Localitate *localitate =new Localitate;
            is >> *localitate;
            judet.localitati[i] =  localitate;
        }
    }
    is.get();
    cout<<"Introduceti numele prefectului:\n";
    if(judet.numePrefect==NULL)
        judet.numePrefect=new char[256];
    is.getline(judet.numePrefect,256);
    return is;
}
ostream &operator<<(ostream &os, const Judet &judet){
    os << "Numarul de Localitati: "<<judet.nrLocalitati << '\n';
    os << "Localitati:\n";
    for(int i=0;i<judet.nrLocalitati;++i){
        Localitate *loc;
        (loc) = (judet.localitati[i]);
        if(loc->esteResedinta()==0)
            os << loc;
        else
            if(loc->esteResedinta()==1){
                const Oras *oras=dynamic_cast<const Oras *> (loc);
                cout << oras;
            }
            else
            {
                const ResedintaDeJudet *resedintaDeJudet=dynamic_cast<const ResedintaDeJudet *> (loc);
                cout << resedintaDeJudet;
            }

    }
    os << "Numele Prefectului: " << judet.numePrefect;
    os <<'\n';
    return os;
}
void Judet::set_Localitate(Localitate *v,int n) {
    localitati = new Localitate*[n];
    nrLocalitati = n;
    for(int i=0; i<n;++i)
        *(localitati[i])=v[i];
}
void Judet::set_nrLocalitati(int n) {
    nrLocalitati = n;
}
void Judet::set_numePrefect(char *nume) {
    if(this->numePrefect==NULL)
        this->numePrefect=new char[256];
    strcpy(this->numePrefect,nume);
}
Localitate ** Judet::get_Localitate() {
    return this->localitati;
}
int Judet::get_nrLocalitati() {
    return this->nrLocalitati;
}
char * Judet::get_numePerfect() {
    return this->numePrefect;
}
int main() {
    Localitate **l;
    l=new Localitate*[20];
    //const char *denumire, int cod, long nr_locuitori,const char *nume, int nrSpitale
    Oras o("Campulung", 1, 12, "Lasconi", 7);
    //const char *denumire, int cod, long nr_locuitori,const char *nume, int nrSpitale, const char *numePresedinte
    ResedintaDeJudet r("Pitesti", 2, 18, "Popa", 9, "Taroiu");
    Localitate loc;
    for(int i = 0;i < 2;++i){
        cin>>loc;
        *(l[i])=(loc);
    }
    for(int i=0;i<2;++i)
        cout << *l[i]<<'\n';
    return 0;
}
