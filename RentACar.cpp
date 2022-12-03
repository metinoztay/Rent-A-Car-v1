#include <iostream>
#include <string>
#include <iomanip>
#include <conio.h>
#include <fstream>
using namespace std;


//Değişken Tanımlamaları
int secim;
//Arac Degiskenleri
string plaka,marka, model, tip, yakit, vites, sigorta, kasko, uygunluk;
//Musteri Degiskenleri
string isim, soyisim, tel, tc;
//Rezervasyon Degiskenleri
//plaka,tc
string kiraTarihi, teslimTarihi, kiraSaati, teslimSaati;
//Odeme Alma Degiskenleri
int para, ay, gun, yil,ucret;
//Fonksiyon Prototipleri
void AnaMenu();
void AracTeslimEt();
void MusteriEkle();
string MusteriSec();
string AracSec();
int UcretHesapla();
void OdemeAl();
void AracTeslimAl();
void MaliIslemler();
void OdemeAl();
void AylikDurum();
void YillikDurum();
void BorcSorgula();
void AracKiralamaKosullari();
void TeslimEdilenRezervasyonSil(string musteriTC);
void AracUygunlukDegistir(string aracPlaka, string yeniDurum);
void Rezervasyon();
void RezervasyonEkle();
void RezervasyonSil();
void AracEkle();
void AracCikar();
void AracListesi();
void AracBilgisiDuzenle();
int Secenek();

int main()
{   
    system("color 71");

    AnaMenu();
   
    return 0;
}

void AnaMenu()
{
    system("CLS");
    cout << "\t-------------------- ANA MENU -------------------" << endl;
    cout << "\t1.Arac Teslim Et\t\t 2.Arac Teslim Al" << endl;
    cout << "\t3.Arac Listesi \t\t\t 4.Rezervasyon" << endl;
    cout << "\t5.Arac Ekle \t\t\t 6.Arac Cikar" << endl;
    cout << "\t7.Arac Bilgisi Duzenle \t\t 8.Mali Islemler" << endl;

    secim = Secenek();

    switch (secim)
    {
    case 1: AracTeslimEt();
        break;
    case 2: AracTeslimAl();
        break;
    case 3: AracListesi();
        cout << "\n\tAnaMenuye donmek icin bir tusa basiniz.";
        _getch();
        AnaMenu();
        break;
    case 4: Rezervasyon();
        break;
    case 5: AracEkle();
        break;
    case 6: AracCikar();
        break;
    case 7: AracBilgisiDuzenle();
        break;
    case 8: MaliIslemler();
        break;
    default: AnaMenu();
        break;
    }
    
}

void AracTeslimEt()
{   
    AracKiralamaKosullari();

    system("CLS");
    cout << "\t-------------- ARAC TESLIM -------------" << endl;
    cout << "\t1.Musteri Ekle \t\t 2.Musteri Sec" << endl;
    secim = Secenek();

    if (secim==1)
    {
        MusteriEkle();
        AracTeslimEt();
    }
    else if (secim==2)
    {
        string teslimTC;
        string plakaYedek;

        ofstream AracTeslimEt;
        AracTeslimEt.open("AracTeslim.txt", ios::app);

        teslimTC=MusteriSec();
        plakaYedek = AracSec();
        cout << "\n\tKiralanan Tarih: ";
        cin >> kiraTarihi;
        cout << "\n\tKiralanan Saat: ";
        cin >> kiraSaati;
        cout << "\n\tArac Teslim Tarihi: ";
        cin >> teslimTarihi;
        cout << "\n\tArac Teslim Saati: ";
        cin >> teslimSaati;

        ucret = UcretHesapla();

        AracTeslimEt << endl << teslimTC << ' ' << plakaYedek << ' ' << kiraTarihi << ' '
            << kiraSaati << ' ' << teslimTarihi << ' ' << teslimSaati << ' ' << ucret;
        AracTeslimEt.close();
        cout << "\n\n\tBilgi girisi tamamlandi. Odeme ekranina geciniz.";

        TeslimEdilenRezervasyonSil(teslimTC);
        AracUygunlukDegistir(plakaYedek,"Kirada");

        _getch();
        OdemeAl();

    }
}

void AracKiralamaKosullari()
{
    system("CLS");
    cout << "\t-------------- ARAC KIRALAMA KOSULLARI -------------" << endl;
    cout << "\t1.Maksimum Kilometre Siniri: 1000km" << endl;
    cout << "\t2.Yas Siniri: Minimum 21" << endl;
    cout << "\t3.Ehliyet Yasi: Minimum 1 yil" << endl;
    cout << "\t4.En az 1 adet kredi karti gereklidir." << endl << endl;
    cout << "\n\n\t1.Onay\t\t0.AnaMenu" << endl;

    secim = Secenek();

    if (secim!=1)
    {
        AnaMenu();
    }
}

void TeslimEdilenRezervasyonSil(string musteriTC)
{
    ifstream RezervasyonListele;
    ofstream RezervasyonSil;
    RezervasyonSil.open("RezervasyonlarYedek.txt", ios::out);
    RezervasyonListele.open("Rezervasyonlar.txt", ios::in);
    while (!RezervasyonListele.eof())
    {
        RezervasyonListele >> tc >> plaka >> kiraTarihi >> kiraSaati >> teslimTarihi >> teslimSaati;
        if (tc == musteriTC)
        {
            continue;
        }
        RezervasyonSil << endl << tc << ' ' << plaka << ' ' << kiraTarihi << ' '
            << kiraSaati << ' ' << teslimTarihi << ' ' << teslimSaati;
    }
    RezervasyonSil.close();
    RezervasyonListele.close();

    remove("Rezervasyonlar.txt");
    rename("RezervasyonlarYedek.txt", "Rezervasyonlar.txt");

   /* ofstream YedekYukle;
    YedekYukle.open("Rezervasyonlar.txt", ios::out);
    ifstream YedekOku;
    YedekOku.open("RezervasyonlarYedek.txt", ios::in);

    while (!YedekOku.eof()) 
    {
        YedekOku >> tc >> plaka >> kiraTarihi >> kiraSaati >> teslimTarihi >> teslimSaati;
        YedekYukle << endl << tc << ' ' << plaka << ' ' << kiraTarihi << ' '
            << kiraSaati << ' ' << teslimTarihi << ' ' << teslimSaati;
    }

    YedekOku.close();
    YedekYukle.close();*/
}

void AracUygunlukDegistir(string aracPlaka, string yeniDurum)
{
    ofstream AracDuzenle;
    ifstream AracListele;
    AracDuzenle.open("AraclarYedek.txt", ios::out);
    AracListele.open("Araclar.txt", ios::in);

    while (!AracListele.eof())
    {
        AracListele >> plaka >> marka >> model >> tip >> yakit >> vites >> sigorta >> kasko >> uygunluk;
        if (plaka == aracPlaka)
        {
            uygunluk = yeniDurum;
            AracDuzenle << endl << plaka << ' ' << marka << ' ' << model << ' ' << tip << ' '
                << yakit << ' ' << vites << ' ' << sigorta << ' ' << kasko << ' ' << uygunluk;

        }
        else
        {
            AracDuzenle << endl << plaka << ' ' << marka << ' ' << model << ' ' << tip << ' '
                << yakit << ' ' << vites << ' ' << sigorta << ' ' << kasko << ' ' << uygunluk;
        }

    }
    AracDuzenle.close();
    AracListele.close();

    ofstream YedekYukle;
    YedekYukle.open("Araclar.txt", ios::out);
    ifstream YedekOku;
    YedekOku.open("AraclarYedek.txt", ios::in);

    while (!YedekOku.eof())
    {
        YedekOku >> plaka >> marka >> model >> tip >> yakit >> vites >> sigorta >> kasko >> uygunluk;
        YedekYukle << endl << plaka << ' ' << marka << ' ' << model << ' ' << tip << ' '
            << yakit << ' ' << vites << ' ' << sigorta << ' ' << kasko << ' ' << uygunluk;
    }

    YedekOku.close();
    YedekYukle.close();


}

void MusteriEkle()
{
    system("CLS");
    cout << "\t-------------- MUSTERI EKLEME -------------" << endl;

    ofstream MusteriEkle;
    MusteriEkle.open("Musteriler.txt", ios::app);

    if (MusteriEkle.is_open())
    {
        cout << "\n\tIsim: ";
        cin >> isim;
        cout << "\n\tSoyisim: ";
        cin >> soyisim;
        cout << "\n\tTel: ";
        cin >> tel;
        cout << "\n\tTC: ";
        cin >> tc;
       

        MusteriEkle << endl << isim << ' ' << soyisim << ' '
            << tel << ' ' << tc ;
        cout << "\n\tKisi Bilgileri Basariyla Eklendi. Devam etmek icin bir tusa basin" << endl;

        MusteriEkle.close();
    }
    else
    {
        cout << "\n\tIslem suan gerceklestirilemiyor.";
    }


    _getch();
}

string MusteriSec()
{
    string arananTC;
    char musteriOnay;
    system("CLS");
    cout << "\n\t-------------- MUSTERI SECIMI -------------" << endl;
    cout << "\n\tMusteri bilgisi bulmak icin TC no giriniz: ";
    cin >> arananTC;

    ifstream MusteriBul;
    MusteriBul.open("Musteriler.txt", ios::in);
    while (!MusteriBul.eof())
    {
        MusteriBul >> isim >> soyisim >> tel >> tc;
        if (arananTC == tc)
        {
            cout << "\n\tIsim: " << isim << endl;
            cout << "\tSoyisim: " << soyisim << endl;
            cout << "\tTel: " << tel << endl;
            cout << "\tTC: " << tc << endl;
            cout << "\n\tMusteri bilgileri ile devam etmek istiyor musunuz? (e/E) - (h/H): ";
            cin >> musteriOnay;
            if (musteriOnay == 'h' || musteriOnay == 'H') 
            {
                continue;
            }
            else if (musteriOnay == 'e' || musteriOnay == 'E') //Musteri Onayı
            {
                MusteriBul.close();
                return string(arananTC);
            }
        }

    }
    MusteriBul.close();

    cout << "\n\tKisi bilgileri bulunamadi." << endl;
    cout << "\n\t1.Musteri Ekle \t\t 0.AnaMenu" << endl;
    secim = Secenek();
    if (secim==1)
    {
        MusteriEkle();
    }
    else if (secim==0)
    {
        AnaMenu();
    }
      
}

string AracSec()
{
    int aracNo = 0;
    int secilenAracNo;
    char aracOnay;
    string tcYedek;
    string plakaYedek;
    
    ifstream AracListele;
    ifstream RezervasyonListele;
    ifstream MusteriBul;
    while(true)
    {
        system("CLS");
        cout << "\t-------------- ARAC SECIM -------------" << endl << endl;
        AracListele.open("Araclar.txt", ios::in);
        cout << "\t" << setw(13) << left << "Arac No" << setw(19) << "Marka" << setw(13) << "Model" << setw(13) << "Tip" << setw(13) << "Yakit" << setw(13) << "Vites" << setw(13) << "Uygunluk" << endl << endl;


        while (!AracListele.eof())
        {
            aracNo++;
            AracListele >> plaka >> marka >> model >> tip >> yakit >> vites >> sigorta >> kasko >> uygunluk;
           /* cout << "\t" << aracNo << "\t\t" << marka << "\t\t" << model << "\t\t" << tip << "\t\t" << yakit << "\t\t" << vites << "\t\t" << uygunluk << endl;*/
            cout << "\t" << setw(13) << left << aracNo << setw(19) << marka << setw(13) << model << setw(13)
                << tip << setw(13) << yakit << setw(13) << vites << setw(13) << uygunluk << endl;
        }

        AracListele.close();

        cout << "\tSecmek istediginiz arac numarasini giriniz: ";
        cin >> secilenAracNo;

        system("CLS");
        cout << "\n\tArac Bilgileri"<<endl;
        aracNo = 0;
        AracListele.open("Araclar.txt", ios::in);
        while (!AracListele.eof())
        {
            aracNo++;

            AracListele >> plaka >> marka >> model >> tip >> yakit >> vites >> sigorta >> kasko >> uygunluk;
            if (aracNo != secilenAracNo) //Secilen aracı kontrol etme
            {
                continue;
            }
            //cout << "\t" << aracNo << "\t\t" << marka << "\t\t" << model << "\t\t" << tip << "\t\t" << yakit << "\t\t" << vites << "\t\t" << uygunluk << endl;
            cout << "\t" << setw(13) << left << aracNo << setw(19) << marka << setw(13) << model << setw(13)
                << tip << setw(13) << yakit << setw(13) << vites << setw(13) << uygunluk << endl;
            plakaYedek = plaka;
        }
        AracListele.close();
        

        cout << "\n\tAraca Ait Rezervasyonlar:" << endl;
        cout << "\t---------------------------------" << endl;
       // cout << "\tIsim Soyisim\t\tKiralama T.\tKiralama S.\tTeslim T.\tTeslim S."<<endl;
        cout << "\t" << setw(8) << left << "Isim" << setw(13) << "Soyisim" << setw(13) << "Kiralama T." << setw(13) << "Kiralama S." << setw(13) << "Teslim T." << setw(13) << "Teslim S." << endl << endl;
       
        RezervasyonListele.open("Rezervasyonlar.txt", ios::in);
        
        while (!RezervasyonListele.eof())
        {
            RezervasyonListele >> tc >> plaka >> kiraTarihi >> kiraSaati >> teslimTarihi >> teslimSaati;

            tcYedek = tc;

            if (plaka == plakaYedek)
            {
                MusteriBul.open("Musteriler.txt", ios::in);
                while (!MusteriBul.eof())
                {
                    MusteriBul >> isim >> soyisim >> tel >> tc;

                    if (tc == tcYedek)
                    {
                        break;
                    }
                }
                MusteriBul.close();
                //cout << "\t" << isim << ' ' << soyisim << "\t\t" << kiraTarihi << "\t\t" << kiraSaati << "\t\t" << teslimTarihi << "\t\t" << teslimSaati << endl;
            
                cout << "\t" << setw(8) << left << isim << setw(13) << soyisim << setw(13) << kiraTarihi << setw(13) << kiraSaati << setw(13)
                    << teslimTarihi << setw(13) << teslimSaati << endl;
            }

        }

        RezervasyonListele.close();
        

        cout << "\n\tAraci secmek istiyor musunuz? (e/E) - (h/H) : ";
        cin >> aracOnay;

        if (aracOnay == 'e' || aracOnay == 'E')
        {
            break;
        }

        aracNo = 0;
    }


    AracListele.close();

    return string(plakaYedek);
}

int UcretHesapla()
{
    int gunlukFiyat, gunSayisi, toplam, indirimOrani=0;
    cout << "\n\tAracin gunluk kiralama fiyatini giriniz: ";
    cin >> gunlukFiyat;
    cout << "\n\tKiralanacak gun sayisini giriniz: ";
    cin >> gunSayisi;

    if (gunSayisi>=4 && gunSayisi < 8)
    {
        indirimOrani = 10;
    }
    else if (gunSayisi>=8 && gunSayisi < 12)
    {
        indirimOrani = 15;
    }
    else if (gunSayisi>=12)
    {
        indirimOrani = 20;
    }

    cout << "\n\tToplam ucret: " << gunlukFiyat * gunSayisi << " TL";
    cout << "\n\tIndirim Orani: %" << indirimOrani;
    cout << "\n\tSon Fiyat: " << gunSayisi * ((gunlukFiyat * (100 - indirimOrani)) / 100) <<" TL";

    return gunSayisi * ((gunlukFiyat * (100 - indirimOrani)) / 100);
}

void OdemeAl()
{
    
    tc = MusteriSec();

    cout << "\tYapilan odeme miktarini giriniz: ";
    cin >> para;

    cout << "\tOdeme yapilan tarihi giriniz (Gun Ay Yil): ";
    cin >> gun >> ay >> yil;

    ofstream OdemeAl;
    OdemeAl.open("Odemeler.txt", ios::app);
    
    OdemeAl << endl << tc << ' ' << para << ' ' << gun << ' ' << ay << ' ' << yil;

    OdemeAl.close();

    cout << "\tOdeme tamamlandi. AnaMenuye donmek icin bir tusa basiniz.";
    _getch();
    AnaMenu();

}

void AracTeslimAl()
{
    string musteriTC, aracPlaka;
    char hasarVarMi;
    int hasarTutari;

    musteriTC = MusteriSec();
    aracPlaka = AracSec();

    cout << endl <<"\tAracta hasar var mi? (e/E) - (h/H): ";
    cin >> hasarVarMi;
    if (hasarVarMi == 'e' || hasarVarMi == 'E')
    {
        cout << "\tHasar tutarini giriniz: ";
        cin >> hasarTutari;
        cout << "\tTeslim tarihini giriniz (Gun/Ay/Yil): ";
        cin >> teslimTarihi;

        ofstream HasarBorcuEkle;
        HasarBorcuEkle.open("AracTeslim.txt", ios::app);
        HasarBorcuEkle << endl << musteriTC << ' ' << aracPlaka << ' ' << teslimTarihi << ' ' << "Hasar" << ' ' << "Borcu" << ' ' << "tutari" << ' ' << hasarTutari;
        HasarBorcuEkle.close();
        AracUygunlukDegistir(aracPlaka, "Hasarli");
        cout << "\tHasar bilgisi eklendi. Odeme ekranina gecebilirsiniz. " << endl;
        cout << "\t1.Odeme Al\t\t0.AnaMenu";
        secim = Secenek();
        switch (secim)
        { 
        case 1: OdemeAl();
            break;
        case 0: AnaMenu();
            break;
        default:
            AnaMenu();
            break;
        }

    }
    else if (hasarVarMi == 'h' || hasarVarMi == 'H')
    {
        AracUygunlukDegistir(aracPlaka, "Uygun");
        cout << "\tArac teslim alindi. Odeme ekranina gecebilirsiniz. " << endl;
        cout << "\t1.Odeme Al\t\t0.AnaMenu";
        secim = Secenek();
        switch (secim)
        {
        case 1: OdemeAl();
            break;
        case 0: AnaMenu();
            break;
        default:
            AnaMenu();
            break;
        }
    }

    _getch();
    AnaMenu();
}

void AylikDurum()
{
    int aylikKazanc=0,arananAy,arananYil;
    string aylar[12] = { "Ocak","Subat","Mart","Nisan","Mayis","Haziran","Temmuz","Agustos","Eylul","Ekim","Kasim","Aralik"};
    system("CLS");
    cout << "\t-------------- AYLIK DURUM -------------" << endl;
    cout << "\n\tLutfen Ay ve Yil bilgisi giriniz: (Ay Yil): ";
    cin >> arananAy >> arananYil;

    ifstream KazancOku;
    KazancOku.open("Odemeler.txt", ios::in);
    while (!KazancOku.eof())
    {
        KazancOku >> tc >> para >> gun >> ay >> yil;

        if (arananAy==ay && arananYil==yil)
        {
            aylikKazanc += para;
        }
    }
    yil = arananYil;
    ay = arananAy;
    KazancOku.close();
    cout << "\t" << yil << " yili " << aylar[ay-1] << " ayi kazanci: " << aylikKazanc << " TL";
    cout << endl << "\tGeri donmek icin bir tusa basin.";
    _getch();
    MaliIslemler();
}

void YillikDurum()
{
    int yillikKazanc = 0,aylikKazanc, arananYil;
    string aylar[12] = { "Ocak","Subat","Mart","Nisan","Mayis","Haziran","Temmuz","Agustos","Eylul","Ekim","Kasim","Aralik" };
    system("CLS");
    cout << "\t-------------- YILLIK DURUM -------------" << endl;
    cout << "\n\tLutfen Yil bilgisi giriniz: ";
    cin >> arananYil;
    cout <<"\n\t" << arananYil << " Detayli Durumu: " << endl <<endl;
    ifstream KazancOku;
    for (int i = 1; i <= 12; i++)
    {
        aylikKazanc = 0;
        KazancOku.open("Odemeler.txt", ios::in);
        while (!KazancOku.eof())
        {
            KazancOku >> tc >> para >> gun >> ay >> yil;

            if (i == ay && arananYil == yil)
            {
                aylikKazanc += para;
                yillikKazanc += para;
            }
        }
        ay = i;

        cout << "\t" << aylar[ay - 1] << " ayi kazanci: " << aylikKazanc << " TL" <<endl;
        KazancOku.close();
    }

    cout << "\n\t" << yil << " Yilinin toplam kazanci: " << yillikKazanc << " TL" <<endl;
    cout << endl << "\tGeri donmek icin bir tusa basin.";
    _getch();
    MaliIslemler();
}

void BorcSorgula()
{
    string arananTC;
    int toplamBorc = 0, toplamOdenen=0;
    system("CLS");
    cout << "\t---------------- BORC SORGULAMA ---------------" << endl;
    arananTC = MusteriSec();

    ifstream BorcSorgula;
    BorcSorgula.open("AracTeslim.txt", ios::in);
    ifstream OdemeKontrol;
    OdemeKontrol.open("Odemeler.txt", ios::in);
    while (!BorcSorgula.eof())
    {
        BorcSorgula >> tc >> plaka >> kiraTarihi >> kiraSaati >> teslimTarihi >> teslimSaati >> ucret;
        if (arananTC==tc)
        {
            toplamBorc += ucret;
        }
    }
    while (!OdemeKontrol.eof())
    {
        OdemeKontrol >> tc >> para >> gun >> ay >> yil;
        if (arananTC == tc)
        {            
            toplamOdenen += para;
        }
    }
    BorcSorgula.close();
    OdemeKontrol.close();
    cout << "\tSecilen musterinin borc bilgisi: " << toplamBorc - toplamOdenen << " TL" << endl;
    cout << "\n\t1.Odeme Al\t\t\t0.AnaMenu";
    secim = Secenek();
    if (secim == 1)
    {
        OdemeAl();
    }
    else
    {
        AnaMenu();
    }
}

void Rezervasyon()
{
    system("CLS");
    cout << "\t-------------- REZERVASYON -------------" << endl;
    cout << "\t1.Rezervasyon Ekle \t\t 2.Rezervasyon Sil" << endl;
    secim = Secenek();

    if (secim == 1)
    {
        system("CLS");
        cout << "\t-------------- REZERVASYON -------------" << endl;
        cout << "\t1.Musteri Ekle \t\t 2.Musteri Sec" << endl;
        secim = Secenek();
        if (secim==1)
        {
            MusteriEkle();
            Rezervasyon();
        }
        else if(secim==2)
        {
            RezervasyonEkle();
        }
        
    }
    else if (secim == 2)
    {
        RezervasyonSil();
    }
}

void RezervasyonEkle()
{
    string rezervasyonTC;
    system("CLS");
    cout << "\t-------------- REZERVASYON EKLEME -------------" << endl;

    ofstream RezervasyonEkle;
    RezervasyonEkle.open("Rezervasyonlar.txt", ios::app);

    if (RezervasyonEkle.is_open())
    {
        rezervasyonTC = MusteriSec();
        plaka = AracSec();
        cout << "\n\tKiralanacak Tarih: ";
        cin >> kiraTarihi;
        cout << "\n\tKiralanacak Saat: ";
        cin >> kiraSaati;
        cout << "\n\tArac Teslim Tarihi: ";
        cin >> teslimTarihi;
        cout << "\n\tArac Teslim Saati: ";
        cin >> teslimSaati;
        

        RezervasyonEkle << endl << rezervasyonTC << ' ' << plaka << ' ' << kiraTarihi << ' '
            << kiraSaati << ' ' << teslimTarihi << ' ' << teslimSaati;     
        cout << "\n\tRezervasyon Basariyla Eklendi. Menuye donmek icin bir tusa basin." << endl;

        RezervasyonEkle.close();
    }
    else
    {
        cout << "\tIslem suan gerceklestirilemiyor.";
    }
 

    _getch();
    AnaMenu();

}

void RezervasyonSil()
{
    string silinecekTC;
    char silmeOnay;
    system("CLS");
    cout << "\t-------------- REZERVASYON SILME -------------" << endl << endl;
    silinecekTC = MusteriSec();
    cout << endl;

    ifstream RezervasyonListele;
    RezervasyonListele.open("Rezervasyonlar.txt", ios::in);
    while (!RezervasyonListele.eof()) //Rezervasyon kontrol
    {
        RezervasyonListele >> tc >> plaka >> kiraTarihi >> kiraSaati >> teslimTarihi >> teslimSaati;
        if (tc == silinecekTC)
        {
            cout << "\tIsim Soyisim\tKiralama T.\tKiralama S.\tTeslim T.\tTeslim S." << endl;
            cout << "\t" << isim << ' ' << soyisim << "\t" << kiraTarihi << "\t" << kiraSaati << "\t" << teslimTarihi << "\t" << teslimSaati;
            break;
        }
        else
        {
            continue;
        }
    }
    RezervasyonListele.close();
    if (tc != silinecekTC)
    {
        cout << "\tRezervasyon bulunamadi. Anamenuye donmek icin bir tusa basin.";
        _getch();
        AnaMenu();
    }
  

    cout << "\n\n\tRezervasyonu silmeyi onayliyor musunuz? (e/E) - (h/H): ";
    cin >> silmeOnay;

    if (silmeOnay=='e'|| silmeOnay=='E')
    {


        ofstream RezervasyonSil;
        RezervasyonSil.open("RezervasyonlarYedek.txt", ios::out);
        RezervasyonListele.open("Rezervasyonlar.txt", ios::in);
        while (!RezervasyonListele.eof())
        {
            RezervasyonListele >> tc >> plaka >> kiraTarihi >> kiraSaati >> teslimTarihi >> teslimSaati;
            if (tc==silinecekTC)
            {
                continue;
            }
            RezervasyonSil << endl << tc << ' ' << plaka << ' ' << kiraTarihi << ' '
                << kiraSaati << ' ' << teslimTarihi << ' ' << teslimSaati;
        }
        RezervasyonSil.close();
        RezervasyonListele.close();
       
        ofstream YedekYukle;
        YedekYukle.open("Rezervasyonlar.txt", ios::out);
        ifstream YedekOku;
        YedekOku.open("RezervasyonlarYedek.txt", ios::in);

        while (!YedekOku.eof()) //Yedek dosyadaki aracları ana dosyaya yükleme
        {
            YedekOku >> tc >> plaka >> kiraTarihi >> kiraSaati >> teslimTarihi >> teslimSaati;
            YedekYukle << endl << tc << ' ' << plaka << ' ' << kiraTarihi << ' '
                << kiraSaati << ' ' << teslimTarihi << ' ' << teslimSaati;
        }

        YedekOku.close();
        YedekYukle.close();

        cout << "\tRezervasyon silindi. AnaMenuye donmek icin bir tusa basiniz.";
        _getch();
        AnaMenu();

    }
    else if (silmeOnay == 'h' || silmeOnay == 'H')
    {
        AnaMenu();
    }


}

void AracEkle()
{
    system("CLS");
    cout << "\t-------------- ARAC EKLEME -------------" << endl;

    ofstream AracEkle;
    AracEkle.open("Araclar.txt", ios::app);
    
    if (AracEkle.is_open())
    {
        cout << "\n Plaka: ";
        cin >> plaka;
        cout << "\n Marka: ";
        cin >> marka;
        cout << "\n Model: ";
        cin >> model;
        cout << "\n Tip: ";
        cin >> tip;
        cout << "\n Yakit: ";
        cin >> yakit;
        cout << "\n Vites: ";
        cin >> vites;
        cout << "\n Sigorta Bitis Tarihi: ";
        cin >> sigorta; 
        cout << "\n Kasko Bitis Tarihi: ";
        cin >> kasko;
        cout << "\n Uygunluk Durumu: ";
        cin >> uygunluk;

        AracEkle << endl << plaka << ' ' << marka << ' ' << model << ' '
            << tip << ' ' << yakit << ' ' << vites 
            << ' ' << sigorta << ' ' << kasko << ' ' << uygunluk;
        cout << "\n\tArac Basariyla Eklendi. Menuye donmek icin bir tusa basin." << endl;

        AracEkle.close();
    }
    else
    {
        cout << "Islem suan gerceklestirilemiyor.";
    }
    

    _getch();
    AnaMenu();
}

void AracCikar() {

    int aracNo = 0;
    int silinecekNo;
    char silmeTercihi;

    system("CLS");
    AracListesi();
    cout << "\n\tCikarmak istediginiz araci seciniz: ";
    cin >> silinecekNo;

    system("CLS");
    cout << "\tArac No\t\tMarka\t\tModel\t\tTip\t\tYakit\t\tVites" << endl << endl;
    aracNo = 0;

    ifstream AracListele;
    AracListele.open("Araclar.txt", ios::in);
    while (!AracListele.eof()) {
        aracNo++;

        AracListele >> plaka >> marka >> model >> tip >> yakit >> vites >> sigorta >> kasko >> uygunluk;
        if (aracNo != silinecekNo) //Silinecek aracı kontrol etme
        {
            continue;
        }
        cout << "\t" << aracNo << "\t\t" << marka << "\t\t" << model << "\t\t" << tip << "\t\t" << yakit << "\t\t" << vites << endl;
        cout << "\n\tAraci silmek istediginize emin misiniz ? (e/E) - (h/H): ";
    }
    AracListele.close();
    cin >> silmeTercihi;

    if (silmeTercihi == 'h' || silmeTercihi == 'H') //Onay verilmezse geri dön
    {
        AnaMenu();
    }
    else if (silmeTercihi == 'e' || silmeTercihi == 'E') //Silme Onayı
    {

        ofstream AracSil;
        AracSil.open("AraclarYedek.txt", ios::out);
        AracListele.open("Araclar.txt", ios::in);
        aracNo = 0;
        while (!AracListele.eof()) //Silinen arac haric diğer aracları dosyaya yedekleme.
        {
            AracListele >> plaka >> marka >> model >> tip >> yakit >> vites >> sigorta >> kasko >> uygunluk;
            aracNo++;
            if (aracNo == silinecekNo) {
                continue;
            }
            else {

                AracSil << endl << plaka << ' ' << marka << ' ' << model << ' ' <<
                    tip << ' ' << yakit << ' ' << vites <<
                    ' ' << sigorta << ' ' << kasko << ' ' << uygunluk;

            }
        }
        AracSil.close();
        AracListele.close();

        if (aracNo == 1)
        {
            plaka = marka = model = tip = yakit = vites = sigorta = kasko = uygunluk = " ";
        }

        remove("Araclar.txt");
        rename("AraclarYedek.txt", "Araclar.txt");

        //ofstream YedekYukle;
        //YedekYukle.open("Araclar.txt", ios::out);
        //ifstream YedekOku;
        //YedekOku.open("AraclarYedek.txt", ios::in);

        //while (!YedekOku.eof()) //Yedek dosyadaki aracları ana dosyaya yükleme
        //{
        //    YedekOku >> plaka >> marka >> model >> tip >> yakit >> vites >> sigorta >> kasko >> uygunluk;
        //    YedekYukle << endl << plaka << ' ' << marka << ' ' << model << ' '
        //        << tip << ' ' << yakit << ' ' << vites
        //        << ' ' << sigorta << ' ' << kasko << ' ' << uygunluk;
        //}

        //YedekOku.close();
        //YedekYukle.close();

        cout << "\tArac basari ile cikarildi.";
        cout << "\n\tAnaMenuye donmek icin bir tusa basiniz.";
        _getch();
        AnaMenu();

    }
    else {
        cout << "\tGecersiz tercih yaptiniz. Arac Listesine donmek icin bir tusa basiniz.";
        _getch();
        AracListesi();
        cout << "\n\tAnaMenuye donmek icin bir tusa basiniz.";
        _getch();
        AnaMenu();
    }

    AracListele.close();

}

void AracListesi()
{
    int aracNo = 0;
    system("CLS");
    cout << "\t-------------- ARAC LISTESI -------------" << endl << endl;
    ifstream AracListele;
    AracListele.open("Araclar.txt", ios::in);

    cout << "\t" << setw(13) << left << "Arac No" << setw(19) << "Marka" << setw(13) << "Model" << setw(13) << "Tip" << setw(13) << "Yakit" << setw(13) << "Vites" << setw(13) << "Uygunluk" << endl << endl;

    while (!AracListele.eof())
    {
        aracNo++;
        AracListele >> plaka >> marka >> model >> tip >> yakit >> vites >> sigorta >> kasko >> uygunluk;
        cout << "\t" << setw(13) << left << aracNo << setw(19) << marka << setw(13) << model << setw(13)
            << tip << setw(13) << yakit << setw(13) << vites << setw(13) << uygunluk <<endl;
      
    }
    
    AracListele.close();
}

void AracBilgisiDuzenle()
{
    int aracNo = 0;
    int duzenlenecekNo;
    char duzenlemeTercihi;

    system("CLS");
    cout << "\t-------------- ARAC LISTESI -------------" << endl << endl;
    ifstream AracListele;
    AracListele.open("Araclar.txt", ios::in);

    //cout << "\tArac No\t\tMarka\t\tModel\t\tTip\t\tYakit\t\tVites\t\tUygunluk" << endl << endl;
    cout << "\t" << setw(13) << left << "Arac No" << setw(19) << "Marka" << setw(13) << "Model" << setw(13) << "Tip" << setw(13) << "Yakit" << setw(13) << "Vites" << setw(13) << "Uygunluk" << endl << endl;

    while (!AracListele.eof())
    {
        aracNo++;
        AracListele >> plaka >> marka >> model >> tip >> yakit >> vites >> sigorta >> kasko >> uygunluk;
       /* cout << "\t" << aracNo << "\t\t" << marka << "\t\t" << model << "\t\t"
            << tip << "\t\t" << yakit << "\t\t" << vites << "\t\t" << uygunluk << endl;*/
        cout << "\t" << setw(13) << left << aracNo << setw(19) << marka << setw(13) << model << setw(13)
            << tip << setw(13) << yakit << setw(13) << vites << setw(13) << uygunluk << endl;

    }

    AracListele.close();
    
    cout << "\n\tDuzenlemek istediginiz araci seciniz: ";
    cin >> duzenlenecekNo;

    system("CLS");
    //cout << "\tArac No\t\tPlaka\t\tMarka\t\tModel\t\tTip\t\tYakit\t\tVites\t\tSigorta\t\tKasko\t\tUygunluk" << endl << endl;
    cout << "\t" << setw(13) << left << "Arac No" << setw(19) << "Marka" << setw(13) << "Model" << setw(13) << "Tip" << setw(13) << "Yakit" << setw(13) << "Vites" << setw(13) << "Uygunluk" << endl << endl;
    aracNo = 0;

    AracListele.open("Araclar.txt", ios::in);
    while (!AracListele.eof())
    {
        aracNo++;

        AracListele >> plaka >> marka >> model >> tip >> yakit >> vites >> sigorta >> kasko >> uygunluk;
        if (aracNo != duzenlenecekNo) //Duzenlenecek aracı kontrol etme
        {
            continue;
        }
       /* cout << "\t" << aracNo << "\t\t" << plaka << "\t\t" << marka << "\t\t" << model
            << "\t\t" << tip << "\t\t" << yakit << "\t\t" << vites
            << "\t\t" << sigorta << "\t\t" << kasko << "\t\t" << uygunluk << endl;*/
        cout << "\t" << setw(13) << left << aracNo << setw(19) << marka << setw(13) << model << setw(13)
            << tip << setw(13) << yakit << setw(13) << vites << setw(13) << uygunluk << endl;
        AracListele.close();
        cout << "\n\tAraci duzenlemek istediginize emin misiniz ? (e/E) - (h/H): ";
        cin >> duzenlemeTercihi;

        if (duzenlemeTercihi == 'h' || duzenlemeTercihi == 'H') //Onay verilmezse geri dön
        {
            AracListele.close();
            AnaMenu();
        }
        else if (duzenlemeTercihi == 'e' || duzenlemeTercihi == 'E') //Duzenleme Onayı
        {

            ofstream AracDuzenle;
            AracDuzenle.open("AraclarYedek.txt", ios::out);
            AracListele.open("Araclar.txt", ios::in);
            aracNo = 0;
            while (!AracListele.eof()) 
            {
                aracNo++;
                if (aracNo == duzenlenecekNo)
                {
                    AracListele >> plaka >> marka >> model >> tip >> yakit >> vites >> sigorta >> kasko >> uygunluk;
                    cout << "\tSigorta Bitis Tarihi: ";
                    cin >> sigorta;
                    cout << "\tKasko Bitis Tarihi: ";
                    cin >> kasko;
                    cout << "\tUygunluk Durumu: ";
                    cin >> uygunluk;
                    AracDuzenle << endl << plaka << ' ' << marka << ' ' << model << ' ' << tip << ' '
                        << yakit << ' ' << vites << ' ' << sigorta << ' ' << kasko << ' ' << uygunluk;
                    
                }
                else
                {
                    AracListele >> plaka >> marka >> model >> tip >> yakit >> vites >> sigorta >> kasko >> uygunluk;
                    AracDuzenle << endl << plaka << ' ' << marka << ' ' << model << ' ' << tip << ' '
                        << yakit << ' ' << vites << ' ' << sigorta << ' ' << kasko << ' ' << uygunluk;

                }

            }
            AracDuzenle.close();
            AracListele.close();

            ofstream YedekYukle;
            YedekYukle.open("Araclar.txt", ios::out);
            ifstream YedekOku;
            YedekOku.open("AraclarYedek.txt", ios::in);

            while (!YedekOku.eof()) //Yedek dosyadaki aracları ana dosyaya yükleme
            {
                YedekOku >> plaka >> marka >> model >> tip >> yakit >> vites >> sigorta >> kasko >> uygunluk;
                YedekYukle << endl << plaka << ' ' << marka << ' ' << model << ' ' << tip << ' '
                    << yakit << ' ' << vites << ' ' << sigorta << ' ' << kasko << ' ' << uygunluk;
            }

            YedekOku.close();
            YedekYukle.close();

            cout << "\tArac basari ile duzenlendi. Arac listesine donmek icin bir tusa basiniz.";
            _getch();
            AracListesi();
            cout << "\n\tAnaMenuye donmek icin bir tusa basiniz.";
            _getch();
            AnaMenu();

        }
        else
        {
            cout << "\tGecersiz tercih yaptiniz. Arac Listesine donmek icin bir tusa basiniz.";
            _getch();
            AracListesi();
            cout << "\n\tAnaMenuye donmek icin bir tusa basiniz.";
            _getch();
            AnaMenu();
        }


    }

}

void MaliIslemler()
{
    system("CLS");
    cout << "\t-------------- MALI ISLEMLER -------------" << endl << endl;
    cout << "\t1.Odeme Al\t\t\t2.Borc Sorgula" << endl;
    cout << "\t3.Aylik Durum\t\t\t4.Yillik Durum" << endl;
    cout << "\t0.AnaMenu" << endl;
    secim = Secenek();

    switch (secim)
    {
    case 1: OdemeAl();
        break;
    case 2: BorcSorgula();
        break;
    case 3: AylikDurum();
        break;
    case 4:YillikDurum();
        break;
    case 0: AnaMenu();
        break;
    default:
        break;
    }

}

int Secenek()
{
    secim = _getch();

    return secim - 48;
}