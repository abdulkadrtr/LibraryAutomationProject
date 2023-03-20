#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define BUF_SIZE 65536
#define SIZE 30

typedef struct yazar{
	int yazarID;
	char yazarAd[30];
	char yazarSoyad[30];
	struct yazar *next;
}yazarINFO;

typedef struct ogrenci{
	char ogrID[9];
	char ad[30];
	char soyad[30];
	int puan;
	struct ogrenci *next;
	struct ogrenci *prev;
}ogrINFO;

typedef struct kitapOrnek{
	char etiketNo[20];
	char durum[8];
	struct kitapOrnek *next;
}kitapOrnek;


typedef struct kitap{
	char kitapAdi[30];
	char ISBN[13];
	int adet;
	struct kitap *next;
	kitapOrnek *head;
}kitapINFO;

typedef struct kitapYazar{
	char ISBN[13];
	int yazarID;
}kitapYazarINFO;

typedef struct tarih{
	unsigned int gun:5;
	unsigned int ay:4;
	unsigned int yil:12;
}TARIH;

yazarINFO* yazarDugumYarat(int yazarID,char yazarAd[],char yazarSoyad[]);
void yazarEkle(yazarINFO** root,int yazarID,char yazarAd[],char yazarSoyad[],int call);
void yazarDosyaKontrol(yazarINFO** root);
void yazarSil(yazarINFO **head,char ad[],char soyad[],kitapYazarINFO* dizi);
void satirSil(int line_num,char file_name[]);
void yazarGuncelle(char eskiAd[],char eskiSoyad[],char yeniAd[],char yeniSoyad[], yazarINFO **root);
void yazarDosyaYaz(int yazarID,yazarINFO* root,char dosyaAd[]);
void yazdir(yazarINFO *root);
ogrINFO* ogrDugumYarat(char ogrID[],char ad[],char soyad[],int puan);
void ogrEkle(ogrINFO** root,char ogrID[],char ad[],char soyad[],int puan,int call);
void ogrDosyaKontrol(ogrINFO** root);
void ogrYazdir(ogrINFO *root);
void ogrGuncelle(char ogrID[],char yeniAd[],char yeniSoyad[],int yeniPuan,ogrINFO **root);
void ogrGuncelleV1(char eskiAd[],char eskiSoyad[],char yeniAd[],char yeniSoyad[],int yeniPuan,ogrINFO **root);
void ogrDosyaYaz(ogrINFO* root,char dosyaAd[]);
void ogrSil(char ogrID[],ogrINFO **root);
kitapINFO* kitapDugumYarat(char kitapAdi[],char ISBN[],int adet);
void kitapEkle(kitapINFO** root,char kitapAdi[],char ISBN[],int adet,int call);
void kitapDosyaKontrol(kitapINFO** root);
void yazarListeSil(yazarINFO** root);
void ogrListeSil(ogrINFO** root);
void kitapListeSil(kitapINFO** root);
void kitapYazdir(kitapINFO *root);
void kitapSil(kitapINFO **head,char ISBN[]);
void kitapDataGuncelle(char ISBN[],char yeniAd[],int stok, kitapINFO **root);
void kitapDosyaYaz(kitapINFO* root,char dosyaAd[]);
int satirSay(char file_path[]);
void kitapYazarOku(kitapYazarINFO* dizi);
void kitapOduncDosyaKontrol(kitapINFO** root);
void ogrKitapAl(ogrINFO* oroot,kitapINFO* kroot,char ogrID[],char kitapAd[]);
int ogrPuan(ogrINFO* root,char ogrID[]);
int ogrVarM(ogrINFO* root,char ogrID[]);
void ogrKitapVer(ogrINFO* oroot,kitapINFO* kroot,char ogrID[],char kitapAd[]);
void ogrCeza(ogrINFO* root,char ogrID[],char etiket[],int day2,int mon2,int year2);
int tarihF(int day1,int mon1,int year1,int day2,int mon2,int year2);
void cezaliListele(ogrINFO* root);
void kitapTeslimE();
void ogrBilgiYazdir(char bilgi[],ogrINFO* root);
void rafKitapListele(kitapINFO* root);
void teslimGKitap();
void yazarBilgiYazdir(char bilgi[],yazarINFO* root);
void yazarKitapDuzenle(int a,kitapYazarINFO* dizi);
void kitapYazarDosyaYaz(kitapYazarINFO* dizi,int k);
void kitapYazarEslestir(kitapINFO* kroot,yazarINFO* yroot,kitapYazarINFO** dizi);
void kitapYazarGuncelle(kitapINFO* kroot,yazarINFO* yroot,kitapYazarINFO** dizi);
void kitapBilgiYazdir(char ad[],kitapINFO* kroot,yazarINFO* yroot,kitapYazarINFO* dizi);
void yazdirF(char dosyaYol[],void(*yaz)(char satir[]));//Fonksiyon pointer
void ogrYaz(char satir[]);
void yazarYaz(char satir[]);
int yazarIDH(yazarINFO* root);

int main(){
	kitapINFO* kitapINF=NULL;
	ogrINFO* ogrINF = NULL;
	yazarINFO* yazarINF = NULL;
	int n,c,t,puan,loop=1,yazarID;
	char ogrID[SIZE],ad[SIZE],soyad[SIZE],adY[SIZE],soyY[SIZE],ISBN[SIZE];
	kitapDosyaKontrol(&kitapINF);
	ogrDosyaKontrol(&ogrINF);
	yazarDosyaKontrol(&yazarINF);
	kitapOduncDosyaKontrol(&kitapINF);
	int satirSayisi = satirSay("KitapYazar.csv");
	kitapYazarINFO* dizi = (kitapYazarINFO*)malloc(satirSayisi*sizeof(kitapYazarINFO));
	if(dizi==NULL){
		printf("\nERROR");
		exit(0);
	}
	kitapYazarOku(dizi);
	printf(".....:::KUTUPHANE OTOMASYONU:::.....\n\n");
	const char* ANA_MENU =
  		"1- Ogrenci Islemleri\n"
  		"2- Yazar Islemleri\n"
  		"3- Kitap Islemleri\n";
  	const char* ogrMenu =
  		"1- Tum Ogrencileri Gor\n"
  		"2- Ogrenci Ekle\n"
  		"3- Ogrenci Sil\n"
  		"4- Ogrenci Kayit Guncelle\n"
		"5- Ogrenci Kitap Alma Islemi\n"
		"6- Ogrenci Kitap Verme Islemi\n"
		"7- Cezali Ogrenci Listele\n"
		"8- Kitap Teslim Etmeyen Ogrenci Listele\n"
		"9- Ogrenci Bilgisi Goruntule";
  	const char* yazarMenu =
  		"1- Tum Yazarlari Gor\n"
  		"2- Yazar Ekle\n"
  		"3- Yazar Sil\n"
  		"4- Yazar Kayit Guncelle\n"
		"5- Yazar Bilgisi Goruntule";
  	const char* kitapMenu =
  		"1- Tum Kitaplari Gor\n"
  		"2- Kitap Ekle\n"
  		"3- Kitap Sil\n"
  		"4- Kitap Kayit Duzenle\n"
		"5- Raftaki Kitaplari Listele\n"
		"6- Teslimat Zamani Gecmis Kitaplari Listele\n"
		"7- Kitap - Yazar Eslestir\n"
		"8- Kitabin Yazarini Guncelle\n"
		"9- Kitap Bilgisi Goruntule";
	while(loop==1){
		printf("\n\n");
		printf(ANA_MENU);
  		printf("\nSeciminiz: ");
		scanf("%d",&n);
		switch(n){
			case 1:
				printf(ogrMenu);
				printf("\nSeciminiz: ");
				scanf("%d",&n);
				switch(n){
					case 1:
						//ogrYazdir(ogrINF); //Linkli listeden yazdirma yapar.
						yazdirF("ogrData.csv",ogrYaz); //Fonksiyon pointer kullanarak dosyadan yazdirir.
						break;
					case 2:
						printf("Ekleme istediginiz ogrenci Adi: ");	scanf("%s",ad);
						printf("\nOgrenci soyadi: ");	scanf("%s",soyad);
						printf("\nOgrenci numarasi: ");	scanf("%s",ogrID);
						printf("\nOGrenci puani: ");	scanf("%d",&puan);
						ogrEkle(&ogrINF,ogrID,ad,soyad,puan,1);
						break;
					case 3:
						printf("Silmek istediginiz ogrenciye ait numara: ");
						scanf("%s",ogrID);
						ogrSil(ogrID,&ogrINF);
						break;
					case 4:
						printf("1- Ad ve Soyad bilgisine gore ogrenci guncelle\n2- Ogrenci ID bilgisine gore ogrenci guncelle\n");
						printf("Seciminiz: ");
						scanf("%d",&t);
						if(t==1){
							printf("Kaydi Guncellenecek Ogrenci Adi: "); scanf("%s",ad);
							printf("\nKaydi Guncellenecek Ogrenci Soyadi: "); scanf("%s",soyad);
							printf("\nOgrenci yeni adi: ");	scanf("%s",adY);
							printf("\nOgrenci yeni soyadi: ");	scanf("%s",soyY);
							printf("\nOGrenci yeni puani: ");	scanf("%d",&puan);
							ogrGuncelleV1(ad,soyad,adY,soyY,puan,&ogrINF);							
						}else if(t==2){
							printf("Kaydi guncellenecek ogrenciye ait numara: "); scanf("%s",ogrID);
							printf("Ogrenci yeni adi: ");	scanf("%s",ad);
							printf("\nOgrenci yeni soyadi: ");	scanf("%s",soyad);
							printf("\nOGrenci yeni puani: ");	scanf("%d",&puan);
							ogrGuncelle(ogrID,ad,soyad,puan,&ogrINF);		
						}
						break;
					case 5:
						//Ogrenci Kitap Alma
						printf("Kitap almak isteyen ogrenci numarasi: "); scanf("%s",ogrID);
						while ((c = getchar()) != '\n' && c != EOF);
						printf("Alinmak istenen kitap ismi: ");	scanf("%[^\n]",ad);
						ogrKitapAl(ogrINF,kitapINF,ogrID,ad);
						break;
					case 6:
						//Ogrenci Kitap Verme
						printf("Kitap vermek isteyen ogrenci numarasi: "); scanf("%s",ogrID);
						while ((c = getchar()) != '\n' && c != EOF);
						printf("Verilmek istenen kitap ismi: ");	scanf("%[^\n]",ad);
						ogrKitapVer(ogrINF,kitapINF,ogrID,ad);
						break;
					case 7:
						printf("Cezali Ogrenci Listesi: \n");
						cezaliListele(ogrINF);
						break;
					case 8:
						printf("Kitap Teslim Etmeyen Ogrenciler: \n\n");
						kitapTeslimE();
						break;
					case 9:
						while ((c = getchar()) != '\n' && c != EOF);
						printf("Bilgisini gormek istediginiz Ogr ID veya Ad Soyad giriniz: "); scanf("%[^\n]",adY);
						ogrBilgiYazdir(adY,ogrINF);
						break;
				}
				break;
			case 2:
				printf(yazarMenu);
				printf("\nSeciminiz: ");
				scanf("%d",&n);
				switch(n){
					case 1:
						//yazdir(yazarINF); //Linkli listeden yazdirma yapar.
						yazdirF("yazarData.csv",yazarYaz); //Fonksiyon pointer kullanarak dosyadan yazdirir.
						break;
					case 2:
						printf("Eklemek istediginiz yazar adi: ");	scanf("%s",ad);
						printf("\nYazar soyadi: ");	scanf("%s",soyad);
						yazarID = yazarIDH(yazarINF);
						yazarEkle(&yazarINF,yazarID,ad,soyad,1);
						break;
					case 3:
						printf("Silmek istediginiz yazar adi: ");	scanf("%s",ad);
						printf("\nYazar soyadi: ");	scanf("%s",soyad);					
						yazarSil(&yazarINF,ad,soyad,dizi);
						break;
					case 4:
						printf("Degistirmek istediginiz yazar adi: ");	scanf("%s",ad);
						printf("\nYazar soyadi: ");	scanf("%s",soyad);
						printf("Yazar yeni adi: ");	scanf("%s",adY);
						printf("\nYazar yeni soyadi: ");	scanf("%s",soyY);					
						yazarGuncelle(ad,soyad,adY,soyY,&yazarINF);
						break;
					case 5:
						while ((c = getchar()) != '\n' && c != EOF);
						printf("Bilgisini gormek istediginiz yazarlarin adini giriniz: "); scanf("%[^\n]",adY);
						yazarBilgiYazdir(adY,yazarINF);
						break;
				}
				break;
			case 3:
				printf(kitapMenu);
				printf("\nSeciminiz: ");
				scanf("%d",&n);
				switch(n){
					case 1:
						kitapYazdir(kitapINF);
						break;
					case 2:
						while ((c = getchar()) != '\n' && c != EOF);
						printf("Kitap adi: ");	scanf("%[^\n]",adY);
						printf("\nKitap ISBN numarasi: ");	scanf("%s",soyad);
						printf("\nKitap stok adeti: ");	scanf("%d",&puan);
						kitapEkle(&kitapINF,adY,soyad,puan,1);
						break;
					case 3:
						//Kitap Sil
						while ((c = getchar()) != '\n' && c != EOF);
						printf("Silmek istediginiz kitap ISBN veya kitap adi: ");	scanf("%[^\n]",adY);
						kitapSil(&kitapINF,adY);
						break;
					case 4:
						//Kitap Guncelle
						printf("Adini ve stok adetini degistirmek istediginiz kitap ISBN: ");	scanf("%s",ISBN);
						while ((c = getchar()) != '\n' && c != EOF);
						printf("\nYeni kitap adi: "); scanf("%[^\n]",adY);
						printf("\nKitap yeni stok durumu: "); scanf("%d",&puan);
						kitapDataGuncelle(ISBN,adY,puan,&kitapINF);
						break;
					case 5:
						printf("Rafta Bulunan Kitaplar: \n");
						rafKitapListele(kitapINF);
						break;
					case 6:
						printf("Teslim Zamani Gecikmis Kitaplar: \n\n");
						teslimGKitap();
						break;
					case 7:
						printf("Kitap - Yazar Eslestirme\n");
						kitapYazarEslestir(kitapINF,yazarINF,&dizi);
						break;
					case 8:
						printf("Kitabin Yazarini Guncelle: ");
						kitapYazarGuncelle(kitapINF,yazarINF,&dizi);
						break;
					case 9:
						while ((c = getchar()) != '\n' && c != EOF);
						printf("Bilgisini goruntulemek istediginiz kitap adi: "); scanf("%[^\n]",adY);
						kitapBilgiYazdir(adY,kitapINF,yazarINF,dizi);
						break;
				}
				break;
			default:
				printf("Gecersiz Deger girdiniz.\n");
				while ((c = getchar()) != '\n' && c != EOF);
		}
		printf("\n\nCikmak icin 0/Devam etmek icin 1: ");	scanf("%d",&loop);
	}
	ogrListeSil(&ogrINF);
	yazarListeSil(&yazarINF);
	kitapListeSil(&kitapINF);
	free(dizi);
	return 0;
}

yazarINFO* yazarDugumYarat(int yazarID,char yazarAd[],char yazarSoyad[]){
	yazarINFO *yeniDugum = (yazarINFO*)malloc(sizeof(yazarINFO));
	if(yeniDugum==NULL){
	printf("\nERROR");
	exit(0);
	}
	yeniDugum->next = NULL;
	yeniDugum->yazarID = yazarID;
	strcpy(yeniDugum->yazarAd,yazarAd);
	strcpy(yeniDugum->yazarSoyad,yazarSoyad);
	return yeniDugum;
}

void yazarEkle(yazarINFO** root,int yazarID,char yazarAd[],char yazarSoyad[],int call){
	yazarINFO* yeni = yazarDugumYarat(yazarID,yazarAd,yazarSoyad);
	if (*root == NULL){
		if(call==1){
			FILE *fp = fopen("yazarData.csv", "a");
			if(fp==NULL){
				printf("\nERROR");
				exit(0);
			}
			fprintf(fp,"%d,%s,%s", yazarID, yazarAd, yazarSoyad);
			fclose(fp);
		}
		*root = yeni;
		return;
	}
	yazarINFO *current = *root;
	while (current->next != NULL){
		current = current->next;
	}
	current->next = yeni;
	if(call==1){ //fonksiyon dosyadan veriyi linkli listeye kaydetme dýþý çaðrýlýrsa, dosyaya ekleme yapar.
		FILE *file = fopen("yazarData.csv", "a");
		if(file==NULL){
			printf("\nERROR");
		}
		fprintf(file,"\n%d,%s,%s", yazarID, yazarAd, yazarSoyad);
		fclose(file);
	}
}


void yazarDosyaKontrol(yazarINFO** root){
	int yazarID;
	char yazarAd[30];
	char yazarSoyad[30];
	char satir[80];
	FILE *fp = fopen("yazarData.csv", "r");
	if(fp==NULL){
		printf("\nERROR");
		exit(0);
	}
	while (fgets(satir, sizeof(satir), fp) != NULL) {
		sscanf(satir, "%d,%[^,],%[^,\n]", &yazarID, yazarAd, yazarSoyad);
		yazarEkle(&*root,yazarID,yazarAd,yazarSoyad,0);
	}
	fclose(fp);
}

void yazarKitapDuzenle(int a,kitapYazarINFO* dizi){
	int i,satirSayisi = satirSay("KitapYazar.csv");
	for(i=0;i<satirSayisi;i++){
		if(dizi[i].yazarID==a){
			dizi[i].yazarID = -1;
		}
	}
	kitapYazarDosyaYaz(dizi,satirSayisi);	
}

void kitapYazarDosyaYaz(kitapYazarINFO* dizi,int k){
	int i;
	FILE *file = fopen("KitapYazar.csv", "w");
	if(file==NULL){
		printf("\nERROR");
		exit(0);
	}	
	for(i=0;i<k-1;i++){
		fprintf(file,"%s,%d\n",dizi[i].ISBN,dizi[i].yazarID);
	}
	fprintf(file,"%s,%d",dizi[i].ISBN,dizi[i].yazarID);
	fclose(file);
}


void yazarSil(yazarINFO **head,char ad[],char soyad[],kitapYazarINFO* dizi){
	int i=1;
	if (strcmp((strlwr((*head)->yazarAd)),(strlwr(ad)))==0 && strcmp((strlwr((*head)->yazarSoyad)),(strlwr(soyad)))==0){
		yazarINFO *temp = *head;
		yazarKitapDuzenle(temp->yazarID,dizi);
		*head = (*head)->next;
		satirSil(i,"yazarData.csv");
		free(temp);
		return;
	}
	i++;
	yazarINFO *current = *head;
	yazarINFO *temp = current->next;
	while (temp!=NULL){
		if(strcmp((strlwr(temp->yazarAd)),(strlwr(ad)))==0 && strcmp((strlwr(temp->yazarSoyad)),(strlwr(soyad)))==0){
			yazarKitapDuzenle(temp->yazarID,dizi);
			current->next = temp->next;
			satirSil(i,"yazarData.csv");
			free(temp);
			return;
		}
		current = current->next;
		temp = current->next;
		i++;
	}
	printf("Eleman Bulunamadi\n");
}


void satirSil(int line_num,char file_name[]){
	int k = satirSay(file_name),len;
	char file_path[128];
	strcpy(file_path, file_name);
	char temp_name[] = "temp.csv";
	FILE *temp_file = fopen(temp_name, "w");
	FILE *file = fopen(file_name, "r");
	if(file==NULL||temp_file==NULL){
		printf("\nERROR");
		exit(0);
	}
	char line[256];
	int current_line = 1;
	while(fgets(line, sizeof(line), file)){
		if(current_line==k-1 && line_num==k){//silinecek satir son satirsa
			len = strlen(line);              //sondan bir onceki satirin \n silinmeli.
			line[len-1] = '\0';
		}
		if(current_line != line_num){
	 		fputs(line, temp_file);
		}
		current_line++;
	}
	fclose(file);
	fclose(temp_file);
	remove(file_name);
	rename(temp_name, file_path);
}

void yazarGuncelle(char eskiAd[],char eskiSoyad[],char yeniAd[],char yeniSoyad[], yazarINFO **root){
	yazarINFO *current = *root;
	int i=1;
	int flag=0;
	while(current!=NULL && flag==0){
		if(strcmp(strlwr(current->yazarAd),strlwr(eskiAd))==0 && strcmp(strlwr(current->yazarSoyad),strlwr(eskiSoyad))==0){
			flag=1;
		}else
			current= current->next;
		i++;
	}
	if(flag==1){
		strcpy(current->yazarAd,yeniAd);
		strcpy(current->yazarSoyad,yeniSoyad);
		yazarDosyaYaz(i,*root,"yazarData.csv");
		
	}
	else{
		printf("Eleman Bulunamadi.");
	}
}


void yazarDosyaYaz(int yazarID,yazarINFO* root,char dosyaAd[]){
	//Bu fonksiyon kendisine verilen dosya adý linkli liste bas elemaný ve linkli liste eleman sayisina gore dosyaya linkli listeyi yazar.
	FILE *file = fopen(dosyaAd, "w");
	if(file==NULL){
		printf("\nERROR");
		exit(0);
	}
	yazarINFO *current = root;
  	while (current != NULL) {
    	if(current->next != NULL){
    		fprintf(file,"%d,%s,%s\n",current->yazarID, current->yazarAd, current->yazarSoyad);
		}else{
			fprintf(file,"%d,%s,%s",current->yazarID, current->yazarAd, current->yazarSoyad);			
		}
		current = current->next;
  	}
  	fclose(file);	
}

ogrINFO* ogrDugumYarat(char ogrID[],char ad[],char soyad[],int puan){
	ogrINFO *yeniDugum = (ogrINFO*)malloc(sizeof(ogrINFO));
	if(yeniDugum==NULL){
		printf("\nERROR");
		exit(0);
	}
	yeniDugum->next = NULL;
	yeniDugum->prev = NULL;
	yeniDugum->puan = puan;
	strcpy(yeniDugum->ogrID,ogrID);
	strcpy(yeniDugum->ad,ad);
	strcpy(yeniDugum->soyad,soyad);
	return yeniDugum;
}

void ogrEkle(ogrINFO** root,char ogrID[],char ad[],char soyad[],int puan,int call){
	ogrINFO* yeni = (ogrINFO*)ogrDugumYarat(ogrID,ad,soyad,puan);
	if (*root == NULL){
		if(call==1){
			FILE *fp = fopen("ogrData.csv", "a");
			if(fp==NULL){
				printf("\nERROR");
				exit(0);
			}
			fprintf(fp,"%s,%s,%s,%d", ogrID,ad,soyad,puan);
			fclose(fp);
		}
		*root = yeni;
		(*root)->prev=NULL;
		(*root)->next=NULL;
		return;
	}
	ogrINFO *current = *root;
	while (current->next != NULL){
		current = current->next;
	}
	current->next = yeni;
	yeni->prev = current;
	yeni->next = NULL;
	if(call==1){ //fonksiyon dosyadan veriyi linkli listeye kaydetme dýþý çaðrýlýrsa, dosyaya ekleme yapar.
		FILE *file = fopen("ogrData.csv", "a");
		if(file==NULL){
			printf("\nERROR");
			exit(0);
		}
		fprintf(file,"\n%s,%s,%s,%d", ogrID, ad, soyad,puan);
		fclose(file);
	}
}

void ogrDosyaKontrol(ogrINFO** root){
	char ogrID[9];
	char ad[30];
	char soyad[30];
	int puan;
	char satir[90];
	FILE *fp = fopen("ogrData.csv", "r");
	if(fp==NULL){
		printf("\nERROR");
		exit(0);
	}
	while (fgets(satir, sizeof(satir), fp) != NULL) {
		sscanf(satir, "%[^,],%[^,],%[^,],%d\n", ogrID,ad,soyad,&puan);
		ogrEkle(&*root,ogrID,ad,soyad,puan,0);
	}
	fclose(fp);
}



    
void ogrYazdir(ogrINFO *root){
  ogrINFO *current = root;
  while (current != NULL) { 
    printf("%s %s %s %d\n",current->ogrID,current->ad,current->soyad,current->puan);
    current = current->next;
  }
}

void ogrGuncelleV1(char eskiAd[],char eskiSoyad[],char yeniAd[],char yeniSoyad[],int yeniPuan,ogrINFO **root){
	ogrINFO *current = *root;
	int flag = 0;
	while(flag==0 && current!=NULL){
		if(strcmp(strlwr(current->ad),strlwr(eskiAd))==0 && strcmp(strlwr(current->soyad),strlwr(eskiSoyad))==0){
			flag = 1;
		}else{
			current= current->next;			
		}
	}
	if(flag==1){
		strcpy(current->ad,yeniAd);
		strcpy(current->soyad,yeniSoyad);
		current->puan = yeniPuan;
		ogrDosyaYaz(*root,"ogrData.csv");
	}
	else{
		printf("Eleman Bulunamadi.\n");
	}
}

void ogrGuncelle(char ogrID[],char yeniAd[],char yeniSoyad[],int yeniPuan,ogrINFO **root){
	ogrINFO *current = *root;
	int flag = 0;
	while(flag==0 && current!=NULL){
		if(atoi(current->ogrID)==atoi(ogrID)){
			flag = 1;
		}
		else
			current=current->next;
	}
	if(flag==1){
		strcpy(current->ad,yeniAd);
		strcpy(current->soyad,yeniSoyad);
		current->puan = yeniPuan;
		ogrDosyaYaz(*root,"ogrData.csv");
	}
	else{
		printf("Eleman Bulunamadi.\n");
	}
}

void ogrDosyaYaz(ogrINFO* root,char dosyaAd[]){
	//Bu fonksiyon kendisine verilen dosya adý linkli liste bas elemanýna gore dosyaya linkli listeyi yazar.
	FILE *file = fopen(dosyaAd, "w");
	if(file==NULL){
		printf("\nERROR");
		exit(0);
	}
	ogrINFO *current = root;
  	while (current != NULL) {
    	if(current->next != NULL){
    		fprintf(file,"%s,%s,%s,%d\n",current->ogrID,current->ad,current->soyad,current->puan);
		}else{
			fprintf(file,"%s,%s,%s,%d",current->ogrID, current->ad, current->soyad,current->puan);		
		}
		current = current->next;
  	}
  	fclose(file);
}

void ogrSil(char ogrID[],ogrINFO **root){
	ogrINFO *current = *root;
	int flag=0,i=1;
	while(current != NULL && flag == 0){
		if(atoi(current->ogrID)==atoi(ogrID)){
			if(*root == current){
				ogrINFO *temp = (*root)->next;
				*root = temp;
				(*root)->prev = NULL;
				flag = 1;
			}
			if(current->next==NULL){
				ogrINFO *temp = current->prev;
				temp->next = NULL;
			}
			if(current->next!=NULL && flag!=1){
				ogrINFO *temp = current->prev;
				temp->next = current->next;
				temp = current->next;
				temp->prev = current->prev;
			}
			free(current);
			flag = 1;
			satirSil(i,"ogrData.csv");	
		}
		i++;
    	current = current->next;
	}
	if(flag==0){
		printf("Kayitli ogrenci bulunamadi.\n");
	}
}

kitapINFO* kitapDugumYarat(char kitapAdi[],char ISBN[],int adet){
	kitapINFO *yeniDugum = (kitapINFO*)malloc(sizeof(kitapINFO));
	kitapOrnek *yeni = (kitapOrnek*)malloc(sizeof(kitapOrnek));
	if(yeniDugum==NULL||yeni==NULL){
		printf("\nERROR");
		exit(0);
	}
	strcpy(yeniDugum->kitapAdi,kitapAdi);
	strcpy(yeniDugum->ISBN,ISBN);
	yeniDugum->adet = adet;
	yeniDugum->next = NULL;
	yeniDugum->head = yeni;
	yeni->next = NULL;
	int i=1;
	char str[4];
	char temp[18];
	for(i=1;i<=adet;i++){
		strcpy(temp,ISBN);
		strcat(temp,"_");
		sprintf(str, "%d",i);
		strcat(temp,str);	
		strcpy(yeni->durum,"RAFTA");
		strcpy(yeni->etiketNo,temp);
		kitapOrnek *tmp = (kitapOrnek*)malloc(sizeof(kitapOrnek));
		if(tmp==NULL){
			printf("\nERROR");
			exit(0);
		}
		yeni->next = tmp;
		yeni = tmp;
		tmp->next = NULL;
	}
	return yeniDugum;
}

void kitapEkle(kitapINFO** root,char kitapAdi[],char ISBN[],int adet,int call){
	kitapINFO* yeni = kitapDugumYarat(kitapAdi,ISBN,adet);
	if (*root == NULL){
		if(call==1){
			FILE *fp = fopen("kitapData.csv", "a");
			if(fp==NULL){
				printf("\nERROR");
				exit(0);
			}
			fprintf(fp,"%s,%s,%d",kitapAdi,ISBN,adet);
			fclose(fp);
		}
		*root = yeni;
		return;
	}
	kitapINFO *current = *root;
	while (current->next != NULL){
		current = current->next;
	}
	current->next = yeni;
	if(call==1){ //fonksiyon dosyadan veriyi linkli listeye kaydetme dýþý çaðrýlýrsa, dosyaya ekleme yapar.
		FILE *file = fopen("kitapData.csv", "a");
		if(file==NULL){
			printf("\nERROR");
			exit(0);
		}
		fprintf(file,"\n%s,%s,%d",kitapAdi,ISBN,adet);
		fclose(file);
	}
}

void kitapDosyaKontrol(kitapINFO** root){
	char kitapAd[30];
	char ISBN[16];
	int adet;
	char satir[80];
	FILE *fp = fopen("kitapData.csv", "r");
	if(fp==NULL){
		printf("\nERROR");
		exit(0);
	}
	while (fgets(satir, sizeof(satir), fp) != NULL) {
		sscanf(satir, "%[^,],%[^,],%d\n",kitapAd,ISBN,&adet);
		kitapEkle(&*root,kitapAd,ISBN,adet,0);
	}
	fclose(fp);
}


void yazarListeSil(yazarINFO** root) {
	yazarINFO* current = *root;
	yazarINFO* next;
	while (current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}
	*root = NULL;
}
void ogrListeSil(ogrINFO** root) {
	ogrINFO* current = *root;
	ogrINFO* next;
	while (current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}
	*root = NULL;
}
void kitapListeSil(kitapINFO** root){
	kitapOrnek* curr;
	kitapOrnek* nextC;
	kitapINFO* current = *root;
	kitapINFO* next;
	while (current != NULL){
		next = current->next;
		curr = current->head;
		while(curr!=NULL){
			nextC = curr->next;
			free(curr);
			curr = nextC;
		}
		free(current);
		current = next;
	}
	*root = NULL;
}


void kitapYazdir(kitapINFO *root){
  kitapINFO *current = root;
  while (current != NULL) {
    printf("\nKitap Adi: %s ISBN: %s Stok Durumu: %d\n", current->kitapAdi,current->ISBN,current->adet);
    kitapOrnek *temp;
    temp = current->head;
    printf("\nDetayli Stok Durum:\n\n");
    while(temp->next!=NULL){
    	printf("Durum: %s\t Etiket No: %s\n",temp->durum,temp->etiketNo);
    	temp = temp->next;
	}
    current = current->next;
  }
}

void kitapSil(kitapINFO **head,char ISBN[]){
	int i=1,flag=0;
	if(strcmp((*head)->ISBN,ISBN)==0||strcmp(strlwr((*head)->kitapAdi),strlwr(ISBN))==0){
		kitapOrnek* c = (*head)->head;
		while(c->next!=NULL){
			if(strcmp(c->durum,"RAFTA")!=0){
				flag = 1;
			}
			c = c->next;
		}
		if(flag==1){
			printf("Silmek istediginiz kitabin en az 1 ornegi ogrencidedir.\nTum kitap ornekleri kutuphanede olmayan kitabi silemezsiniz.\n");
		}else{
			kitapINFO *temp = *head;	
			*head = (*head)->next;
			satirSil(i,"kitapData.csv");
			kitapOrnek* curr=temp->head;
	  		kitapOrnek* nextC;
	  		while(curr!=NULL){
	  			nextC = curr->next;
	  			free(curr);
	  			curr = nextC;
			}
			free(temp);
			return;	
		}
	}
	i++;
	kitapINFO *current = *head;
	kitapINFO *temp = current->next;
	while (temp!= NULL && strcmp(temp->ISBN,ISBN)!=0 && strcmp(strlwr(temp->kitapAdi),strlwr(ISBN))!=0){
    	temp = temp->next;
    	current = current->next;
    	i++;
  	}
  	if(temp!=NULL){
  		kitapOrnek* k = temp->head;
  		while(k->next!=NULL){
			if(strcmp(k->durum,"RAFTA")!=0){				
				flag = 1;
			}
			k = k->next;
		}
		if(flag==1){
			printf("Silmek istediginiz kitabin en az 1 ornegi ogrencidedir.\nTum kitap ornekleri kutuphanede olmayan kitabi silemezsiniz.\n");
		}else{
	  		kitapOrnek* curr=temp->head;
	  		kitapOrnek* nextC;
	  		while(curr!=NULL){
	  			nextC = curr->next;
	  			free(curr);
	  			curr = nextC;
			}
			current->next = temp->next;
	   		free(temp);
			satirSil(i,"kitapData.csv");		
		}
    }
    else
		printf("Kayitli Kitap Bulunamadi\n");
}

void kitapDataGuncelle(char ISBN[],char yeniAd[],int stok, kitapINFO **root){
	kitapINFO *current = *root;
	int i=1;
	int flag=0;
	while(current!=NULL && flag==0){
		if(strcmp(current->ISBN,ISBN)==0){
			flag=1;
		}else
			current = current->next;
		i++;
	}
	if(flag==1){
		strcpy(current->kitapAdi,yeniAd);
		current->adet = stok;
		kitapDosyaYaz(*root,"kitapData.csv");
	}
	else{
		printf("Eleman Bulunamadi.");
	}
}


void kitapDosyaYaz(kitapINFO* root,char dosyaAd[]){
	//Bu fonksiyon kendisine verilen dosya adý linkli liste bas elemaný ve linkli liste eleman sayisina gore dosyaya linkli listeyi yazar.
	FILE *file = fopen(dosyaAd, "w");
	if(file==NULL){
		printf("\nERROR");
		exit(0);
	}
	kitapINFO *current = root;
  	while (current != NULL){
    	if(current->next != NULL){
    		fprintf(file,"%s,%s,%d\n",current->kitapAdi, current->ISBN, current->adet);
		}else{
			fprintf(file,"%s,%s,%d\n",current->kitapAdi, current->ISBN, current->adet);			
		}
		current = current->next;
  	}
  	fclose(file);	
}

int satirSay(char file_path[]){
    FILE *file = fopen(file_path, "r");
   	if(file==NULL){
		printf("\nERROR");
		exit(0);
	}
    char buf[BUF_SIZE];
    int counter=0,i;
    while (!feof(file)) {
        size_t res = fread(buf, 1, BUF_SIZE, file);
        if (ferror(file))
            return -1;
        for(i = 0; i < res; i++)
            if (buf[i] == '\n')
                counter++;
    }
    fclose(file);
    return counter + 1;
}

void kitapYazarOku(kitapYazarINFO* dizi){
	int yazarID;
	char ISBN[16];
	char satir[20];
	FILE *fp = fopen("KitapYazar.csv", "r");
	if(fp==NULL){
		printf("\nERROR");
		exit(0);
	}
	int i=0;
	while (fgets(satir, sizeof(satir), fp) != NULL){
		sscanf(satir, "%[^,],%d\n",ISBN,&yazarID);
		strcpy(dizi[i].ISBN,ISBN);
		dizi[i].yazarID = yazarID;
		i++;
	}
	fclose(fp);
}


void kitapOduncDosyaKontrol(kitapINFO** root){
	char ISBN[16];
	char satir[85];
	char ogrNo[9];
	char ISBNg[14];
	int durum;
	FILE *fp = fopen("kitapOdunc.csv", "r");
	if(fp==NULL){
		printf("\nERROR");
		exit(0);
	}
	while (fgets(satir, sizeof(satir), fp) != NULL) {
		sscanf(satir, "%[^,],%[^,],%d\n",ISBN,ogrNo,&durum);
		// Bu asamada elimde kitapOdunc dosyasýnýn satýrlarý geliyor. 0 odunc alma , 1 kutuphaneye verme
		kitapINFO* current = *root;
		strncpy(ISBNg,ISBN,13);
		ISBNg[13]='\0'; //Bu kitap ISBN
		while(current!=NULL){
			if(strcmp(ISBNg,current->ISBN)==0){
				kitapOrnek* curr = current->head;
				while(curr!=NULL){
					if(strcmp(curr->etiketNo,ISBN)==0){
						//printf("%s\t%s\n",curr->etiketNo,ISBN);
						if(durum==0){
							strcpy(curr->durum,ogrNo);
						}
						else{
							strcpy(curr->durum,"RAFTA");
						}
					}				
					curr = curr->next;
				}
			}
			current = current->next;
		}
	}
}


void ogrKitapAl(ogrINFO* oroot,kitapINFO* kroot,char ogrID[],char kitapAd[]){
	if(ogrVarM(oroot,ogrID)==1){
		FILE *fp;
		int durum = 0,flag = 0,flg=0;
		time_t t = time(NULL);
		struct tm *tm = localtime(&t);
		char ISBN[15];
		char date[20];
		TARIH* temp = (TARIH*)malloc(sizeof(TARIH));
		if(temp==NULL){
			printf("\nERROR");
			exit(0);
		}
		temp->gun = tm->tm_mday;
		temp->ay = tm->tm_mon+1;
		temp->yil = tm->tm_year+1900;
		if(temp->gun-9>0){
			if(temp->ay-9>0){
				sprintf(date,"%d.%d.%d",temp->gun,temp->ay,temp->yil);				
			}else{
				sprintf(date,"%d.0%d.%d",temp->gun,temp->ay,temp->yil);			
			}
		}else{
			if(temp->ay-9>0){
				sprintf(date,"0%d.%d.%d",temp->gun,temp->ay,temp->yil);	
			}else{
				sprintf(date,"0%d.0%d.%d",temp->gun,temp->ay,temp->yil);
			}	
		}
		free(temp);
		kitapINFO* curr = kroot;
		while(curr!=NULL && flag==0){
			if(strcmp(strlwr(curr->kitapAdi),strlwr(kitapAd))==0){
				flg=1;
				kitapOrnek* c = curr->head;
				if(ogrPuan(oroot,ogrID)==-1){
					printf("Ogrenci Puan Yetersiz");
					flag = 1;
				}else{
					while(c!=NULL&&flag==0){
						if(strcmp(c->durum,"RAFTA")==0){
							strcpy(ISBN,c->etiketNo);
							fp = fopen("kitapOdunc.csv","r+");
							if(fp==NULL){
								printf("\nERROR");
								exit(0);
							}
							fseek(fp, 0, SEEK_END);
							fprintf(fp,"\n%s,%s,%d,%s",ISBN,ogrID,durum,date);
							fclose(fp);
							flag = 1;
							printf("%s ISBN numarali kitap %s ID numarali ogrenciye verildi.",ISBN,ogrID);
							strcpy(c->durum,ogrID);
						}
						c = c->next;
					}
					if(flag==0){
						printf("Kitaba ait tum ornekler ogrencilerdedir.ISLEM BASARISIZ");
					}	
				}
			}
			curr = curr->next;
		}
		if(flg==0){
			printf("%s adinda bir kitap yok.",kitapAd);
		}	
	}
	else{
		printf("Bu numaraya kayitli ogrenci yok.\n");
	}	
}

int ogrPuan(ogrINFO* root,char ogrID[]){
	ogrINFO* curr = root;
	while(curr!=NULL){
		if(strcmp(curr->ogrID,ogrID)==0){
			if(curr->puan>0){
				return 1;
			}else{
				return -1;
			}
		}
		curr = curr->next;	
	}
}

int ogrVarM(ogrINFO* root,char ogrID[]){
	ogrINFO* curr = root;
	while(curr!=NULL){
		if(strcmp(curr->ogrID,ogrID)==0){
			return 1;
		}
		curr = curr->next;	
	}
	return -1;
}

void ogrKitapVer(ogrINFO* oroot,kitapINFO* kroot,char ogrID[],char kitapAd[]){
	if(ogrVarM(oroot,ogrID)==1){
		FILE *fp;
		int durum = 1,flag = 0,flg=0;
		time_t t = time(NULL);
		struct tm *tm = localtime(&t);
		TARIH* temp = (TARIH*)malloc(sizeof(TARIH));
		if(temp==NULL){
			printf("\nERROR");
			exit(0);
		}
		temp->gun = tm->tm_mday;
		temp->ay = tm->tm_mon+1;
		temp->yil = tm->tm_year+1900;
		char date[20];
		if(temp->gun-9>0){
			if(temp->ay-9>0){
				sprintf(date,"%d.%d.%d",temp->gun,temp->ay,temp->yil);				
			}else{
				sprintf(date,"%d.0%d.%d",temp->gun,temp->ay,temp->yil);			
			}
		}else{
			if(temp->ay-9>0){
				sprintf(date,"0%d.%d.%d",temp->gun,temp->ay,temp->yil);	
			}else{
				sprintf(date,"0%d.0%d.%d",temp->gun,temp->ay,temp->yil);
			}	
		}
		char ISBN[15];
		kitapINFO* curr = kroot;
		while(curr!=NULL && flag==0){
			if(strcmp(strlwr(curr->kitapAdi),strlwr(kitapAd))==0){
				flg=1;
				kitapOrnek* c = curr->head;
				while(c!=NULL&&flag==0){
					if(strcmp(c->durum,ogrID)==0){
						ogrCeza(oroot,ogrID,c->etiketNo,temp->gun,temp->ay,temp->yil);
						strcpy(ISBN,c->etiketNo);
						fp = fopen("kitapOdunc.csv","r+");
						if(fp==NULL){
							printf("\nERROR");
							exit(0);
						}
						fseek(fp, 0, SEEK_END);
						fprintf(fp,"\n%s,%s,%d,%s",ISBN,ogrID,durum,date);
						fclose(fp);
						flag = 1;
						printf("%s ISBN numarali kitap %s ID numarali ogrenciden alindi.",ISBN,ogrID);
						strcpy(c->durum,"RAFTA");
					}
					c = c->next;
				}
				if(flag==0){
					printf("Ogrenci teslim almadigi kitabi teslim edemez.\n");
				}
			}
			curr = curr->next;
		}
		if(flg==0){
			printf("%s adinda bir kitap yok.",kitapAd);
		}	
		free(temp);
	}
	else{
		printf("Bu numaraya kayitli ogrenci yok.\n");
	}	
}

void ogrCeza(ogrINFO* root,char ogrID[],char etiket[],int day2,int mon2,int year2){
	FILE *fp;
    char line[100];
    int day1,mon1,year1;
	int temp=0,n,t;
	int flag = 0;
    fp = fopen("kitapOdunc.csv", "r");
   	if(fp==NULL){
		printf("\nERROR");
		exit(0);
	}
	while (flag==0&&fgets(line,100, fp) != NULL) {
		temp++;
		if (strstr(line,ogrID) != NULL) {
			if(strstr(line,etiket)!=NULL){
				n = temp;
				flag = 1;	
			}
		}
	}
	fclose(fp);
	char str1[3] = {line[27],line[28], '\0'};
	day1 = atoi(str1);
	char str2[3] = {line[30],line[31], '\0'};
	mon1 = atoi(str2);
	char str3[5] = {line[33],line[34],line[35],line[36], '\0'};
	year1 = atoi(str3);	   
	if(tarihF(day1,mon1,year1,day2,mon2,year2)){
		ogrINFO *c = root;
		while(c!=NULL){
			if(strcmp(c->ogrID,ogrID)==0){
				printf("Ogrenci kitabi gec teslim ettiginden -10 ceza puani almistir.\n");
				c->puan = c->puan-10;
			}
			c = c->next;
		}
		ogrDosyaYaz(root,"ogrData.csv");
	}
}

int tarihF(int day1,int mon1,int year1,int day2,int mon2,int year2){
	int date[3];
	if(day2 < day1){      
        if (mon2 == 3){
            if ((year2 % 4 == 0 && year2 % 100 != 0) || (year2 % 400 == 0)) {
                day2 += 29;
            }
            else{
                day2 += 28;
            }                        
        }
        else if (mon2 == 5 || mon2 == 7 || mon2 == 10 || mon2 == 12) {
           day2 += 30; 
        }
        else{
           day2 += 31;
        }
        mon2 = mon2 - 1;
    }
    if (mon2 < mon1){
        mon2 += 12;
        year2 -= 1;
    }       
    date[0] = day2 - day1;
    date[1] = mon2 - mon1;
    date[2] = year2 - year1;
    if(date[0]>15 || date[1]>=1 || date[2]>=1){
		return 1;
	}  
    return 0;
}

void cezaliListele(ogrINFO* root){
	ogrINFO *current = root;
  	while (current != NULL) {
  		if(current->puan <100){
  			printf("%s %s %s\t Puan: %d\n",current->ogrID,current->ad,current->soyad,current->puan);
		  }
    	current = current->next;
  	}
}

void kitapTeslimE(){
	char ISBN[15],ogrNo[15],satir[50],ogrNo1[15],ISBN1[15];
	int durum1,durum,flag=0;
	FILE *fp = fopen("kitapOdunc.csv", "r");
	if(fp==NULL){
		printf("\nERROR");
		exit(0);
	}
	while (fgets(satir, sizeof(satir), fp) != NULL) {	
		sscanf(satir, "%[^,],%[^,],%d\n",ISBN,ogrNo,&durum);
		if(durum==0){
			FILE *fp1 = fopen("kitapOdunc.csv", "r");
			if(fp1==NULL){
				printf("\nERROR");
				exit(0);
			}
			while(fgets(satir,sizeof(satir),fp1)!=NULL){
				sscanf(satir, "%[^,],%[^,],%d\n",ISBN1,ogrNo1,&durum1);
				if(strcmp(ISBN,ISBN1)==0 && strcmp(ogrNo,ogrNo1)==0 && durum1 == 1){
					flag = 1;		
				}
			}
			fclose(fp1);			
			if(flag==0)
				printf("%s numarali ogrenci %s ISBN numarali kitabi teslim etmemistir.\n",ogrNo,ISBN,durum);
			flag = 0;
		}
	}
	fclose(fp);
}

void ogrBilgiYazdir(char bilgi[],ogrINFO* root){
	ogrINFO *current = root;
	int flag = 0,durum;
	char dizi[30];
	char ISBN[15],ogrNo[15],satir[50],temp[10],tarih[10];
  	while (current != NULL){
  		sprintf(dizi,current->ad);
		sprintf(dizi + strlen(dizi), " %s", current->soyad);
  		if(strcmp(strlwr(bilgi),strlwr(dizi))==0 || strcmp(bilgi,current->ogrID)==0){
  			printf("\nOgrenci Bilgileri: \n");
  			printf("\n%s %s %s\t Puan: %d\n\n",current->ogrID,current->ad,current->soyad,current->puan);
  			strcpy(temp,current->ogrID);
  			flag = 1;
		  }
    	current = current->next;
  	}
  	if(flag==0){
  		printf("\nOgrenci Bulunamadi.");	
	}
	else{
		FILE *fp = fopen("kitapOdunc.csv", "r");
		if(fp==NULL){
			printf("\nERROR");
			exit(0);
		}
		printf("Ogrencinin Kitap Hareketleri: \n\n");
		while (fgets(satir, sizeof(satir), fp) != NULL){	
			sscanf(satir, "%[^,],%[^,],%d,%[^,\n]",ISBN,ogrNo,&durum,tarih);
			if(strcmp(temp,ogrNo)==0){
				if(durum==0){
					printf("Ogrenci %s tarihinde %s ISBN etiketli kitabi teslim almistir.\n",tarih,ISBN);
				}else{
					printf("Ogrenci %s tarihinde %s ISBN etiketli kitabi teslim etmistir.\n",tarih,ISBN);
				}
			}
		}
		fclose(fp);
	}  	
}

void rafKitapListele(kitapINFO* root){
	kitapINFO* curr = root;
	char kitap[30];
	while(curr!=NULL){
		strcpy(kitap,curr->kitapAdi);
		kitapOrnek* c = curr->head;
		while(c!=NULL){
			if(strcmp(c->durum,"RAFTA")==0){
				printf("Ad : %s\tISBN: %s\t RAFTA\n",kitap,c->etiketNo);
			}
			c = c->next;
		}
		curr = curr->next;
	}
}

void teslimGKitap(){
	char ISBN[15],ogrNo[15],satir[50],ogrNo1[15],ISBN1[15],tarih[12];
	int durum1,durum,flag=0;
	time_t t = time(NULL);
	struct tm *tm = localtime(&t);
	FILE *fp = fopen("kitapOdunc.csv", "r");
	if(fp==NULL){
		printf("\nERROR");
		exit(0);
	}
	while (fgets(satir, sizeof(satir), fp) != NULL){	
		sscanf(satir, "%[^,],%[^,],%d,%[^,\n]",ISBN,ogrNo,&durum,tarih);
		if(durum==0){
			FILE *fp1 = fopen("kitapOdunc.csv", "r");
			if(fp1==NULL){
				printf("\nERROR");
				exit(0);
			}
			while(fgets(satir,sizeof(satir),fp1)!=NULL){
				sscanf(satir, "%[^,],%[^,],%d\n",ISBN1,ogrNo1,&durum1);
				//printf("Dosya tarih %s \n",tarih);
				if(strcmp(ISBN,ISBN1)==0 && strcmp(ogrNo,ogrNo1)==0 && durum1 == 1){
					flag = 1;			
				}
			}
			fclose(fp1);
			if(flag==0){
				char str1[3] = {tarih[0],tarih[1], '\0'};
				int day1 = atoi(str1);
				char str2[3] = {tarih[3],tarih[4], '\0'};
				int mon1 = atoi(str2);
				char str3[5] = {tarih[6],tarih[7],tarih[8],tarih[9], '\0'};
				int year1 = atoi(str3);
				if(tarihF(day1,mon1,year1,tm->tm_mday,tm->tm_mon+1,tm->tm_year+1900)){
					printf("%s ISBN numarali kitabin teslimati gecikmistir.\n",ISBN);							
				}
			}
			flag = 0;	
		}
	}
	fclose(fp);
}

void yazdir(yazarINFO *root){
  yazarINFO *current = root;
  while (current != NULL) {
    printf("%d %s %s\n", current->yazarID,current->yazarAd,current->yazarSoyad);
    current = current->next;
  }
}

void yazarBilgiYazdir(char bilgi[],yazarINFO* root){
	yazarINFO *current = root;
	int flag = 0,id;
	char ISBN[SIZE],satir[SIZE];
  	while (current != NULL){
  		if(strcmp(strlwr(bilgi),strlwr(current->yazarAd))==0){
  			printf("\nYazar Bilgisi: \n");
  			printf("\nID Numarasi: %d\tAdi: %s\tSoyadi: %s\n\n",current->yazarID,current->yazarAd,current->yazarSoyad);
	  		FILE *fp = fopen("kitapYAzar.csv", "r");
			while (fgets(satir, sizeof(satir), fp) != NULL){	
				sscanf(satir, "%[^,],%d\n",ISBN,&id);
				if(id==current->yazarID){
					printf("%s ISBN numarali kitabi yazmistir.\n",ISBN);		
				}
			}
  			flag = 1;
		  }
    	current = current->next;
  	}
  	if(flag==0){
  		printf("\nBu Isimde Yazar Bulunamadi.");
	}	
}

void kitapYazarEslestir(kitapINFO* kroot,yazarINFO* yroot,kitapYazarINFO** dizi){
	kitapINFO* current = kroot;
	yazarINFO* curr = yroot;
	int a,loop=1,i=1,v,j,n,flag=0,satirSayisi;
	char temp[15];
	satirSayisi = satirSay("KitapYazar.csv");
	printf("Kitap Listesi : \n\n");
	printf("ISBN\t\tKitap Adi\n");
	while(current!=NULL){
		printf("%s\t%s\n",current->ISBN,current->kitapAdi);
		current = current->next;
	}
	printf("\nYazar Listesi\n\n");
	printf("ID\tYazar Adi Soyadi\n");
	while(curr!=NULL){
		printf("%d\t%s %s\n",curr->yazarID,curr->yazarAd,curr->yazarSoyad);
		curr = curr->next;
	}
	while(loop==1){
		v=0;
		printf("Lutfen eslestirmek istediginiz yazar ID ve kitap ISBN bilgisini giriniz: ");
		scanf("%d %s",&a,temp);
		current = kroot;
		curr = yroot;
		while(current!=NULL){
			if(strcmp(current->ISBN,temp)==0){
				v++;
			}	
			current = current->next;
		}
		while(curr!=NULL){
			if(curr->yazarID==a){
				v++;
			}
			curr = curr->next;
		}		
		if(v!=2){
			printf("Kayitlarimizda olmayan ID veya ISBN bilgisiyle eslestirme yapilamaz!\n");
		}
		else{
			for(j=0;j<satirSayisi+i-1;j++){
				if(strcmp((*dizi)[j].ISBN,temp)==0 && (*dizi)[j].yazarID==a){
					flag = 1;
				}
			}				
		}
		if(flag==1){
			printf("Girdiginiz yazar ve kitap onceden eslestirilmistir!\n");
		}
		else{
			if(v==2){
				printf("k");
				*dizi = realloc(*dizi,(satirSayisi+i)*sizeof(kitapYazarINFO));
				if(*dizi==NULL){
					printf("ERR");
					loop=0;
				}
				printf("Eslestirme islemi basariyla tamamlandi!\n");
				strcpy((*dizi)[satirSayisi+i-1].ISBN,temp);
				(*dizi)[satirSayisi+i-1].yazarID = a;
				i++;
			}
		}
		printf("1- Tekrar Eslestirme Yap\n2- Eslestirme Islemini Bitir\nSeciminiz: ");
		scanf("%d",&n);
		if(n==2){
			loop=0;
		}
		flag = 0;
	}
	if(i>1)
		kitapYazarDosyaYaz(*dizi,satirSayisi+i-1);
}

void kitapYazarGuncelle(kitapINFO* kroot,yazarINFO* yroot,kitapYazarINFO** dizi){
	char ad[SIZE],yAd[SIZE],ySoyad[SIZE],temp[SIZE],yAdE[SIZE],ySoyadE[SIZE];
	int flag=0,k,t,i,m,f=0,c;
	printf("\nYazarini guncellemek istediginiz kitabin adini giriniz: "); 
	while ((c = getchar()) != '\n' && c != EOF);
	scanf("%[^\n]",ad);
	while(kroot!=NULL){
		if(strcmp(strlwr(kroot->kitapAdi),strlwr(ad))==0){
			flag=1;
			strcpy(temp,kroot->ISBN);
		}
		kroot = kroot->next;
	}
	if(flag==1){	
		printf("Kitabin onceki yazarinin adini giriniz : "); scanf("%s",yAdE);
		printf("Kitabin onceki yazarinin soyadini giriniz: "); scanf("%s",ySoyadE);	
		printf("Kitabin guncel yazarinin adini giriniz : "); scanf("%s",yAd);
		printf("Kitabin guncel yazarinin soyadini giriniz: "); scanf("%s",ySoyad);
		while(yroot!=NULL){
			if(strcmp(strlwr(yroot->yazarAd),strlwr(yAd))==0 && strcmp(strlwr(yroot->yazarSoyad),strlwr(ySoyad))==0){
				flag=2;
				t = yroot->yazarID;
			}
			else if(strcmp(strlwr(yroot->yazarAd),strlwr(yAdE))==0 && strcmp(strlwr(yroot->yazarSoyad),strlwr(ySoyadE))==0){
				m = yroot->yazarID;
			}
			yroot = yroot->next;
		}
		if(flag==2){
			k = satirSay("KitapYazar.csv");	
			for(i=0;i<k;i++){
				if((*dizi)[i].yazarID == m){
					f=1;
					(*dizi)[i].yazarID = t;
				}
			}
			if(f==1){
				printf("Kitap - Yazar eslestirme kayitlarimizda bulunan bilgi guncellenmistir!");
				kitapYazarDosyaYaz(*dizi,k);
			}else{
				printf("Verdiginiz bilgiler Kitap - Yazar kayitlarimizda bulunamamis olup\nyeni kayit olarak eklenmistir.\n");
				*dizi = realloc(*dizi,(k+1)*sizeof(kitapYazarINFO));
				if(*dizi==NULL){
					printf("\nERROR");
					exit(0);
				}
				strcpy((*dizi)[k].ISBN,temp);
				(*dizi)[k].yazarID = t;
				kitapYazarDosyaYaz(*dizi,k+1);
			}
		}
		else{
			printf("Bilgilerini verdiginiz guncel yazar kayitlarimizda bulunmamaktadir.\nLutfen once yazar ekleme menusunu kullaniniz.\n");
		}
	}
	else{
		printf("Kayitlarimizda bu isimde bir kitap bulunmamaktadir.\n");
	}	
}

void kitapBilgiYazdir(char ad[],kitapINFO* kroot,yazarINFO* yroot,kitapYazarINFO* dizi){
	kitapINFO* current = kroot;
	int s = satirSay("KitapYazar.csv");
	int flag=0,i;
	while(current!=NULL){
		if(strcmp(strlwr(ad),strlwr(current->kitapAdi))==0){
			printf("\nKitap Adi: %s ISBN: %s Stok Durumu: %d\n", current->kitapAdi,current->ISBN,current->adet);
			kitapOrnek* temp = current->head;
			for(i=0;i<s;i++){
				if(strcmp(dizi[i].ISBN,current->ISBN)==0){
					yazarINFO* curr = yroot;
					while(curr!=NULL){
						if(curr->yazarID==dizi[i].yazarID){
							printf("Kitabin eslestirilen yazari: %s %s \n",curr->yazarAd,curr->yazarSoyad);
						}
						curr = curr->next;
					}
				}
			}
			printf("\nDetayli Stok Durum:\n\n");
			while(temp->next!=NULL){
    			printf("Durum: %s\t Etiket No: %s\n",temp->durum,temp->etiketNo);
    			temp = temp->next;
			}
			flag = 1;
		}
		current = current->next;
	}
	if(flag==0){
		printf("Kayitlarimizda bu ada ait kitap bulunamamistir.\n");
	}
}

void yazdirF(char dosyaYol[],void(*yaz)(char satir[])){
	char satir[60];
	FILE *fp = fopen(dosyaYol,"r");	
	if(fp==NULL){
		printf("\nERROR");
		exit(0);
	}
	while(fgets(satir,sizeof(satir),fp)!=NULL){
		yaz(satir);
	}
	fclose(fp);
}

void ogrYaz(char satir[]){
	char ogrID[SIZE],ad[SIZE],soyad[SIZE];
	int puan;
	sscanf(satir, "%[^,],%[^,],%[^,],%d\n", ogrID,ad,soyad,&puan);
	printf("%s %s %s %d\n",ogrID,ad,soyad,puan);
}

void yazarYaz(char satir[]){
	char ad[SIZE],soyad[SIZE];
	int id;
	sscanf(satir, "%d,%[^,],%[^,\n]",&id,ad,soyad);
	printf("%d %s %s\n",id,ad,soyad);
}

int yazarIDH(yazarINFO* root){
	int i,max;
	max = root->yazarID;
	root = root->next;
	while(root!=NULL){
		if(root->yazarID>max){
			max = root->yazarID;
		}
		root = root->next;
	}
	return max+1;
}

