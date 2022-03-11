#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

//Sabitler
#define TARLA_BOYUT 8
#define MAYIN_SAYI 3
#define KAZANMA_D 1
#define KAYBETME_D -1
#define DEVAM 0

//Global değişkenler
char tab[TARLA_BOYUT+2][TARLA_BOYUT+2];    //Normal tablo
int alttablo[TARLA_BOYUT+2][TARLA_BOYUT+2];   //#,* tablo
int mayin_sayisi,y=0;
int b_say = 0;

//Kullanılan fonksiyonlar
void alt_tablo_olustur();
void ilk_tablo_olustur();
void alt_tablo_bas();
void tablo_bas();
void mayin_yerlestir();
int oyun_durumu();
void kesif(int satir,int sutun);
int koordinat(int satir,int sutun);




int main(void)
{
  int satir,sutun;
    int ilerleme;

    int yeniden;
    char action;//Harf işlemli
    printf("Mayin Tarlasi\n");
    alt_tablo_olustur();
    ilk_tablo_olustur();
    do
    {
        tablo_bas();
        printf("\n");
        printf("A(Ac),Satir,Sutun  B(Bayrak),Satir,Sutun  K(Bayrak Kaldir),Satir,Sutun\n");
        scanf("%c,%d,%d",&action,&satir,&sutun);
        printf("\n");

        if(action == 'A')
        {

            ilerleme=koordinat(satir,sutun);
        }
        else if(action == 'B')
        {
            if(mayin_sayisi >b_say)
            {
                b_say++;
                tab[satir][sutun]='D';
                ilerleme=oyun_durumu();
            }
        }
        else if(action == 'K')
        {
            if(b_say>0)
            {
                b_say--;
            }
            tab[satir][sutun]='#';
            ilerleme=koordinat(satir,sutun);
        }


        if(ilerleme==KAYBETME_D)
        {
            printf("Oyun Bitti,Kaybettiniz\n");
            alt_tablo_bas();
            printf("Yeniden Oyna -> [1-Evet][0-Hayir] \n");
            scanf("%d",&yeniden);
            switch(yeniden)
            {
            case 0:
                printf("Iyi Gunler\n");
                return 0;
                break;
            case 1:
                b_say=0;
                ilerleme=DEVAM;
                alt_tablo_olustur();
                ilk_tablo_olustur();
                break;
            default:
                printf("Yanlis Bir Deger Girdiniz!\n");
                break;
            }
        }

        if(ilerleme==KAZANMA_D)
        {
            printf("Oyun Bitti,KAZANDINIZ<3\n");
            alt_tablo_bas();
            printf("Yeniden Oyna -> [1-Evet][0-Hayir] \n");
            scanf("%d",&yeniden);
            switch(yeniden)
            {
            case 0:
                printf("Iyi Gunler\n");
                return 0;
                break;
            case 1:
                b_say=0;
                ilerleme=DEVAM;
                alt_tablo_olustur();
                ilk_tablo_olustur();
                break;
            default:
                printf("Yanlis Bir Deger Girdiniz!\n");
                break;
            }

        }

    }
    while(1);
    return 0;

}

void alt_tablo_olustur()
{
	int i,j,mayin_sayisi;


	//Création du sous-tableau
	for(i=0;i<=TARLA_BOYUT+1;i++)
	{
		for(j=0;j<=TARLA_BOYUT+1;j++)
		{
			alttablo[i][j]= 0;
		}
	}
	for(i=0;i<=TARLA_BOYUT;i++)//Alt tablonun çerçevelenmesi
	{
		alttablo[i][0]= 1;
		alttablo[i][TARLA_BOYUT+1]= 1;
	}
	for(j=0;j<=TARLA_BOYUT;j++)
	{
		alttablo[0][j]= 1;
		alttablo[TARLA_BOYUT+1][j]= 1;
	}
    mayin_sayisi =MAYIN_SAYI;
	mayin_yerlestir();

}

void ilk_tablo_olustur()
{
	int i,j;

	//Tablonun oluşturulması
	for(i=0;i<=TARLA_BOYUT+1;i++)
	{
		for(j=0;j<=TARLA_BOYUT+1;j++)

			tab[i][j]= '#';
		}
	for(i=0;i<=TARLA_BOYUT;i++)
		{
			tab[i][0]= '*';
			tab[i][TARLA_BOYUT+1]= '*';
		}
	for(j=0;j<=TARLA_BOYUT;j++)
		{
			tab[0][j]= '*';
			tab[TARLA_BOYUT+1][j]= '*';
		}

}

void tablo_bas(){
	int i,j;

	printf("\n");
	//Sütunları numaralandırma
	for(i=1;i<=TARLA_BOYUT;i++){
		printf("%3d",i);
	}
	printf("\n");

	//Tablonun üstünü sınırlandırma
	for(i=1;i<=TARLA_BOYUT;i++){
		printf("---");
	}
	printf("\n");

	//Tabloyu ekrana yazdır
	for(i=1;i<=TARLA_BOYUT;i++){
		for(j=1;j<=TARLA_BOYUT;j++){
			printf("%3c",tab[i][j]);
		}
		printf(" |%d",i);	//Satir numaralandırma
		printf("\n");
	}

	//Tablonun altını sınırlandırma
	for(i=1;i<=TARLA_BOYUT;i++){
		printf("___");
	}
}

void alt_tablo_bas(){
	int i,j;

	printf("\n");
	//Sütunları numaralandırma
	for(i=1;i<=TARLA_BOYUT;i++){
		printf("%3d",i);
	}
	printf("\n");

	//Tablonun üstünü sınırlandırma
	for(i=1;i<=TARLA_BOYUT;i++){
		printf("---");
	}
	printf("\n");

	//Tabloyu ekrana yazdırma
	for(i=1;i<=TARLA_BOYUT;i++){
		for(j=1;j<=TARLA_BOYUT;j++){
			printf("%3d",alttablo[i][j]);
		}
		printf(" |%d",i);
		printf("\n");
	}

	//Tablonun altını sınırlandırma
	for(i=1;i<=TARLA_BOYUT;i++){
		printf("___");
	}
	printf("\n");
}


void mayin_yerlestir()
{
	srand(time(NULL)); //Mayın yerleştirmesi için random değer üretme
 	int i,j,k,p,satir,sutun;
	mayin_sayisi = MAYIN_SAYI;

		//Zorluk derecesine göre mayınların rastgele konumu
		for(i=1;i<=mayin_sayisi;i++)
		{
			satir=1+rand()%TARLA_BOYUT;
			sutun=1+rand()%TARLA_BOYUT;//Sütunu rastgele seçiyoruz
			if(alttablo[satir][sutun]== -1) i--;//Mayın varsa önce ki adıma dön
			alttablo[satir][sutun]= -1;
                            for(k=-1;k<=1;k++)
                                {//Sol Orta Sağ
                                for(p=-1;p<=1;p++){//üst Orta Alt
                                    if(alttablo[satir][sutun]==-1){//Bombaysa
                                    if(alttablo[satir+k][sutun+p]!=-1)//Komşusu bomba değilse
                                    {
                                    alttablo[satir+k][sutun+p]++;//Çevresindeki bomba sayısını bir arttır
                                    }
                            }
                        }
                    }

                }



        }









int oyun_durumu()
{
	int i,j,y=0,status;
	for(i=1;i<=TARLA_BOYUT;i++)
	{
        for(j=1;j<=TARLA_BOYUT;j++)
        {
            if(tab[i][j]=='b')//Yerleştirilen bayrak sayısını sayıyoruz // Bayraksa
			{
                if(alttablo[i][j]==-1)
                {
                    y++;
                }
			}

        }
	}
	if(y==MAYIN_SAYI)//Yerleştirilen bayrakların ve ortaya çıkarılan karelerin toplamı mayın sayısına eşittir.
   	{
		status=KAZANMA_D;
	}
	else
		status=DEVAM;

	return status;
}

void kesif(int satir, int sutun) {
	int i, j;


	tab[satir][sutun] = '0' + alttablo[satir][sutun];//Alt tablodaki değeri üst tabloya karakter olarak atıyoruz açma işlemi
    //Tüm komşular için
	for (i = -1; i <= 1; i++) {
		for (j = -1; j <= 1; j++) {
			//Sayı varsa (komşusu mayınlıysa)ve açık de�ilse
			if (alttablo[satir + i][sutun + j] > 0 && tab[satir + i][sutun + j] == '#')
			{
				tab[satir + i][sutun + j] = '0'+ alttablo[satir + i][sutun + j];//Komşuyu aç
			}
			//Sayı 0 sa (komşusu mayınsızsa)
			else if (alttablo[satir + i][sutun + j] == 0 && tab[satir + i][sutun + j] == '#')
			{
				kesif(satir + i, sutun + j);//Komşuya geç aynı işlemi tekrar olarak yap
			}
		}
	}
}


int koordinat(int satir, int sutun)
{
	int x=0;
    if (alttablo[satir][sutun] == -1)//Bomba mı?
    {
    	x=KAYBETME_D;
    }

    else if (alttablo[satir][sutun] > 0)//Sayı  mı (komşusu mayınlıysa)
    {
        tab[satir][sutun] = ('0' + alttablo[satir][sutun]);//Aç
            x=DEVAM;
	}
    else//Boşsa(Komşusu bossa)
    {
    	kesif(satir, sutun);//Komşularını açarak ilerle
    }

    return x;//Oyun durumunu döndür
}
