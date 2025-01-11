#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <conio.h>
#include <iomanip>
using namespace std;

struct guvenlik {
    char isim[20];
    char soyisim[20];
    char no[10];
    char cinsiyet;
    char baslangicSaati[10];
    char bitisSaati[10];
};

guvenlik gorevli;

void GuvenlikEkle();
void GuvenlikListeleme();
void GuvenlikArama();
void GuvenlikSilme();

int main()
{
    setlocale(LC_ALL, "Turkish");

    char secim;
    do {
        system("cls");

        cout << "|---------- G�venlik N�bet Takip Sistemi ----------|" << endl;
        cout << "|                                                  |" << endl;
        cout << "|->->->->->  1- G�venlik G�revlisi Ekle  <-<-<-<-<-|"<< endl;
        cout << "|->->->->->  2- G�revli Listeleme        <-<-<-<-<-|" << endl;
        cout << "|->->->->->  3- G�revli Arama            <-<-<-<-<-|" << endl;
        cout << "|->->->->->  4- G�revli Silme            <-<-<-<-<-|" << endl;
        cout << "|                                                  |" << endl;
        cout << "|--------------------------------------------------|" << endl;

        cout << "\nSE��M : ";
        cin >> secim;

        switch (secim) {
            case '1':
                GuvenlikEkle();
                break;
            case '2':
                GuvenlikListeleme();
                break;
            case '3':
                GuvenlikArama();
                break;
            case '4':
                GuvenlikSilme();
                break;
        }

        cout << endl;
        cout << "\nPROGRAMI TEKRAR �ALI�TIRMAK �STER M�S�N�Z ? (e/h)  : ";
        secim = getche();
    } while (secim == 'e' || secim == 'E');

    return 0;
}

void GuvenlikEkle()
{
    setlocale(LC_ALL, "Turkish");

    ofstream yaz("guvenlik.dat", ios::binary | ios::app);

    char secim;

    do {
        system("cls");

        cout << "\nG�revlinin Ad�n� giriniz: ";
        cin >> gorevli.isim;

        cout << "\nG�revlinin Soyad�n� giriniz: ";
        cin >> gorevli.soyisim;

        cout << "\nG�revlinin Numaras�n� Giriniz: ";
        cin >> gorevli.no;

        cout << "\nG�revlinin Cinsiyetini Giriniz: ";
        gorevli.cinsiyet = getche();
        cout<<endl;
        cout << "\nG�revlisinin N�bet Ba�lang�� Saatini Giriniz (HH:MM): ";
        cin >> gorevli.baslangicSaati;

        cout << "\nG�revlisinin N�bet Biti� Saatini Giriniz (HH:MM): ";
        cin >> gorevli.bitisSaati;

        yaz.write((char*)&gorevli, sizeof(gorevli));

        cout << endl;
        cout << "\nTekrar G�venlik G�revlisi Eklemek �ster misiniz ? (e/h)  : ";
        secim = getche();
    } while (secim == 'e' || secim == 'E');

    yaz.close();
}

void GuvenlikListeleme()
{
    setlocale(LC_ALL, "Turkish");

    system("cls");

    ifstream oku("guvenlik.dat", ios::binary | ios::app);

    system("cls");

    oku.seekg(0, ios::end);

    int adet = oku.tellg() / sizeof(gorevli);

    if (adet > 0) {
        for (int i = 0; i < adet; i++) {
            oku.seekg(i * sizeof(gorevli));//i�aretleme
            oku.read((char*)&gorevli, sizeof(gorevli));

            cout << "\n|--------- " << i + 1 << ". G�REVL� B�LG�LER� ---------|";

            cout << "\n -> G�revlinin Ad�: " << gorevli.isim;
            cout << "\n -> G�revlinin Soyad�: " << gorevli.soyisim;
            cout << "\n -> G�revlinin Numaras�: " << gorevli.no;
            cout << "\n -> G�revlinin Cinsiyeti: " << gorevli.cinsiyet;
            cout << "\n -> N�bet Ba�lang�� Saati: " << gorevli.baslangicSaati;
            cout << "\n -> N�bet Biti� Saati: " << gorevli.bitisSaati;

            cout << endl;
        }
    } else {
        cout << "\nKAYIT BULUNAMADI" << endl;
    }

    oku.close();
}

void GuvenlikArama()
{
    setlocale(LC_ALL, "Turkish");

    system("cls");

    ifstream oku("guvenlik.dat", ios::binary | ios::in);

    oku.seekg(0, ios::end);
    int adet = oku.tellg() / sizeof(gorevli);

    if (adet <= 0) {
        cout << "\nKay�t bulunamad�!" << endl;
        oku.close();
        return;
    }

    char gorevliNo[10];
    char secim;

    do {
        system("cls");
        cout << "\nAramak istedi�iniz g�venlik g�revlisinin numaras�n� giriniz: ";
        cin >> gorevliNo;

        oku.seekg(0, ios::beg);
        bool bulundu = false;

        for (int i = 0; i < adet; i++) {
            oku.read((char*)&gorevli, sizeof(gorevli));

            if (strcmp(gorevli.no, gorevliNo) == 0) {
                cout << "\n|--------- " << i + 1 << ". G�REVL� B�LG�LER� ---------|";
                cout << "\n -> G�revlinin Ad�: " << gorevli.isim;
                cout << "\n -> G�revlinin Soyad�: " << gorevli.soyisim;
                cout << "\n -> G�revlinin Numaras�: " << gorevli.no;
                cout << "\n -> G�revlinin Cinsiyeti: " << gorevli.cinsiyet;
                cout << "\n -> N�bet Ba�lang�� Saati: " << gorevli.baslangicSaati;
                cout << "\n -> N�bet Biti� Saati: " << gorevli.bitisSaati;
                cout << endl;

                bulundu = true;
                break;
            }
        }

        if (!bulundu) {
            cout << "\nBu numaraya ait g�venlik g�revlisi bulunamad�." << endl;
        }

        cout << "\nTekrar arama yapmak ister misiniz? (e/h): ";
        cin >> secim;

    } while (secim == 'e' || secim == 'E');

    oku.close();
}

void GuvenlikSilme()
{
    setlocale(LC_ALL, "Turkish");

    system("cls");

    ifstream oku("guvenlik.dat", ios::binary | ios::in);
    if (!oku.is_open()) {//zorunlu
        cerr << "\nDosya a��lamad� veya mevcut de�il!" << endl;
        return;
    }

    ofstream yaz("gecici.dat", ios::binary | ios::out);
    if (!yaz.is_open()) {//zorunlu
        cerr << "\nGe�ici dosya olu�turulamad�!" << endl;
        oku.close();
        return;
    }

    char gorevliNo[10];
    bool bulundu = false;

    cout << "\nSilmek istedi�iniz g�venlik g�revlisinin numaras�n� giriniz: ";
    cin >> gorevliNo;

    oku.seekg(0, ios::beg);
    while (oku.read((char*)&gorevli, sizeof(gorevli))) {
        if (strcmp(gorevli.no, gorevliNo) == 0) {
            cout << "\nG�revli bulundu ve silindi:\n";
            cout << " -> Ad: " << gorevli.isim << "\n";
            cout << " -> Soyad: " << gorevli.soyisim << "\n";
            cout << " -> Numaras�: " << gorevli.no << "\n";
            cout << " -> Cinsiyeti: " << gorevli.cinsiyet << "\n";
            cout << " -> N�bet Ba�lang�� Saati: " << gorevli.baslangicSaati << "\n";
            cout << " -> N�bet Biti� Saati: " << gorevli.bitisSaati << "\n";
            bulundu = true;
        } else {
            yaz.write((char*)&gorevli, sizeof(gorevli));
        }
    }

    oku.close();
    yaz.close();

    if (bulundu) {
        remove("guvenlik.dat");
        rename("gecici.dat", "guvenlik.dat");
        cout << "\nSilme i�lemi ba�ar�yla tamamland�!" << endl;
    } else {
        remove("gecici.dat");
        cout << "\nBelirtilen numaraya ait g�venlik g�revlisi bulunamad�!" << endl;
    }
}

