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

        cout << "|---------- Güvenlik Nöbet Takip Sistemi ----------|" << endl;
        cout << "|                                                  |" << endl;
        cout << "|->->->->->  1- Güvenlik Görevlisi Ekle  <-<-<-<-<-|"<< endl;
        cout << "|->->->->->  2- Görevli Listeleme        <-<-<-<-<-|" << endl;
        cout << "|->->->->->  3- Görevli Arama            <-<-<-<-<-|" << endl;
        cout << "|->->->->->  4- Görevli Silme            <-<-<-<-<-|" << endl;
        cout << "|                                                  |" << endl;
        cout << "|--------------------------------------------------|" << endl;

        cout << "\nSEÇÝM : ";
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
        cout << "\nPROGRAMI TEKRAR ÇALIÞTIRMAK ÝSTER MÝSÝNÝZ ? (e/h)  : ";
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

        cout << "\nGörevlinin Adýný giriniz: ";
        cin >> gorevli.isim;

        cout << "\nGörevlinin Soyadýný giriniz: ";
        cin >> gorevli.soyisim;

        cout << "\nGörevlinin Numarasýný Giriniz: ";
        cin >> gorevli.no;

        cout << "\nGörevlinin Cinsiyetini Giriniz: ";
        gorevli.cinsiyet = getche();
        cout<<endl;
        cout << "\nGörevlisinin Nöbet Baþlangýç Saatini Giriniz (HH:MM): ";
        cin >> gorevli.baslangicSaati;

        cout << "\nGörevlisinin Nöbet Bitiþ Saatini Giriniz (HH:MM): ";
        cin >> gorevli.bitisSaati;

        yaz.write((char*)&gorevli, sizeof(gorevli));

        cout << endl;
        cout << "\nTekrar Güvenlik Görevlisi Eklemek Ýster misiniz ? (e/h)  : ";
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
            oku.seekg(i * sizeof(gorevli));//iþaretleme
            oku.read((char*)&gorevli, sizeof(gorevli));

            cout << "\n|--------- " << i + 1 << ". GÖREVLÝ BÝLGÝLERÝ ---------|";

            cout << "\n -> Görevlinin Adý: " << gorevli.isim;
            cout << "\n -> Görevlinin Soyadý: " << gorevli.soyisim;
            cout << "\n -> Görevlinin Numarasý: " << gorevli.no;
            cout << "\n -> Görevlinin Cinsiyeti: " << gorevli.cinsiyet;
            cout << "\n -> Nöbet Baþlangýç Saati: " << gorevli.baslangicSaati;
            cout << "\n -> Nöbet Bitiþ Saati: " << gorevli.bitisSaati;

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
        cout << "\nKayýt bulunamadý!" << endl;
        oku.close();
        return;
    }

    char gorevliNo[10];
    char secim;

    do {
        system("cls");
        cout << "\nAramak istediðiniz güvenlik görevlisinin numarasýný giriniz: ";
        cin >> gorevliNo;

        oku.seekg(0, ios::beg);
        bool bulundu = false;

        for (int i = 0; i < adet; i++) {
            oku.read((char*)&gorevli, sizeof(gorevli));

            if (strcmp(gorevli.no, gorevliNo) == 0) {
                cout << "\n|--------- " << i + 1 << ". GÖREVLÝ BÝLGÝLERÝ ---------|";
                cout << "\n -> Görevlinin Adý: " << gorevli.isim;
                cout << "\n -> Görevlinin Soyadý: " << gorevli.soyisim;
                cout << "\n -> Görevlinin Numarasý: " << gorevli.no;
                cout << "\n -> Görevlinin Cinsiyeti: " << gorevli.cinsiyet;
                cout << "\n -> Nöbet Baþlangýç Saati: " << gorevli.baslangicSaati;
                cout << "\n -> Nöbet Bitiþ Saati: " << gorevli.bitisSaati;
                cout << endl;

                bulundu = true;
                break;
            }
        }

        if (!bulundu) {
            cout << "\nBu numaraya ait güvenlik görevlisi bulunamadý." << endl;
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
        cerr << "\nDosya açýlamadý veya mevcut deðil!" << endl;
        return;
    }

    ofstream yaz("gecici.dat", ios::binary | ios::out);
    if (!yaz.is_open()) {//zorunlu
        cerr << "\nGeçici dosya oluþturulamadý!" << endl;
        oku.close();
        return;
    }

    char gorevliNo[10];
    bool bulundu = false;

    cout << "\nSilmek istediðiniz güvenlik görevlisinin numarasýný giriniz: ";
    cin >> gorevliNo;

    oku.seekg(0, ios::beg);
    while (oku.read((char*)&gorevli, sizeof(gorevli))) {
        if (strcmp(gorevli.no, gorevliNo) == 0) {
            cout << "\nGörevli bulundu ve silindi:\n";
            cout << " -> Ad: " << gorevli.isim << "\n";
            cout << " -> Soyad: " << gorevli.soyisim << "\n";
            cout << " -> Numarasý: " << gorevli.no << "\n";
            cout << " -> Cinsiyeti: " << gorevli.cinsiyet << "\n";
            cout << " -> Nöbet Baþlangýç Saati: " << gorevli.baslangicSaati << "\n";
            cout << " -> Nöbet Bitiþ Saati: " << gorevli.bitisSaati << "\n";
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
        cout << "\nSilme iþlemi baþarýyla tamamlandý!" << endl;
    } else {
        remove("gecici.dat");
        cout << "\nBelirtilen numaraya ait güvenlik görevlisi bulunamadý!" << endl;
    }
}

