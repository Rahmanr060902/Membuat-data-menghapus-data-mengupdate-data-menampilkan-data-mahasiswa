#include <stdio.h>
#include <string.h>

int main (void){
	//deklarasi variable
	char jawab;

	struct Mhs{
	char nim[50];
	char nm[50];
	char kls[50];
	}mhs;

	//perulangan do-while
	do{

		//deklarasi variable
		FILE *mahasiswa, *mhsSementara;
		char mainData[14] = "mahasiswa.txt", tempData[14] = "temporary.txt";
		int berhasil;
		char nimInputan[50];
		char nmInputanA[50];
		char nmInputanB[50];
		char klsInputan[50];
		char nimUpdate[50];
		char nimDelete[50];
		int i=0, duplikat=0, choice=0, ascii;

		//tampilan awal
		printf("======================================================\n");
		printf("|  	 PROGRAM PENDATAAN AKUN I-LAB INFOTECH       |\n");
		printf("======================================================\n");
		printf("\n");
		printf("Silahkan untuk memilih menu yang tersedia di layar\n");
		printf("\n");
		printf("1. Create data\n");
		printf("2. Show data\n");
		printf("3. Update data\n");
		printf("4. Delete data\n");
		printf("5. Exit\n");
		printf("\n");

		//memasukkan pilihan dari menu
		printf("Masukkan pilihan anda: ");
		scanf("%d",&choice);
		printf("\n");

		//kondisi jika memilih menu pertama
		if(choice==1){
			printf("===Create data===\n");
			printf("\n");
			mengulangi:
			duplikat=0;
			//menginput data nim
			printf("Masukkan NIM Pratikan anda: ");
			fflush(stdin);
			gets(nimInputan);

			//membuka file txt agar bisa diisi data
			mahasiswa = fopen(mainData, "r");
			if(mahasiswa == NULL){
				fclose(mahasiswa);

				printf("Membuat file baru!\n");

				mahasiswa = fopen(mainData, "a");
				fclose(mahasiswa);
			}else{
				while(fread(&mhs, sizeof(mhs), 1, mahasiswa)){
					if(strcmp(mhs.nim, nimInputan)==0){
						duplikat=1;
						break; //keluar dari loop while
					}
				}
				fclose(mahasiswa);
			}

			//menentukaan special character menggunakan ASCII
			for(i=0; nimInputan[i]!='\0';i++) {
				ascii = nimInputan[i];
				if((ascii >= 48 && ascii <= 57) || (ascii >= 65 && ascii <= 90) || (ascii >= 97 && ascii <= 122)){
					//nim tidak mengandung special character
				}else{
					printf("Nim mengandung karakter spesial, silahkan isi kembali\n");
					goto mengulangi;
				}
			}

			//kondisi untuk data nim
			if(duplikat==1){
				printf("Nim telah ada, silahkan isi kembali\n");
				goto mengulangi;
			}if(strlen(nimInputan)>18){
				printf("NIM anda invalid, silahkan isi kembali\n");
				goto mengulangi;
			}else if(strlen(nimInputan)<18){
				//membuat data
				printf("Masukkan Nama Awal Pratikan anda: ");
				fflush(stdin);
				gets(nmInputanA);
				printf("Masukkan Nama Belakang Pratikan anda: ");
				fflush(stdin);
				gets(nmInputanB);

				//menggabungkan nama depan dan belakang
				strcat(nmInputanA, " "); //menambah spasi diantara string
				strcat(nmInputanA, nmInputanB);

				printf("Masukkan Kelas Pemrograman Dasar anda: ");
				fflush(stdin);
				gets(klsInputan);
				strupr(klsInputan);
				printf("\n");

				//memasukkan data inputan ke dalam struct
				strcpy(mhs.nim, nimInputan);
				strcpy(mhs.nm, nmInputanA);
				strcpy(mhs.kls, klsInputan);

				//memasukkan data struct ke dalam file
				mahasiswa = fopen(mainData, "a");
				fwrite(&mhs, sizeof (mhs), 1, mahasiswa);
				fclose(mahasiswa);

				printf("====================================\n");
				printf("|  	Data berhasil disimpan     |\n");
				printf("====================================\n");
			}
		}

		//kondisi jika memilih menu kedua
		if(choice==2){
			printf("===Show data===\n");
			printf("\n");
            //membaca data file mahasiswa
			mahasiswa = fopen(mainData, "r");
			if(mahasiswa == NULL){
				printf("Maaf data tidak dapat ditemukan!");
				fclose(mahasiswa);
			}else{
                i=0;
                while(fread(&mhs, sizeof(mhs), 1, mahasiswa)){
					i++;
					printf("Menampilkan data ke-%d\n", i);
					printf("NIM Pratikan anda: %s\n", mhs.nim);
					printf("Nama Pratikan anda: %s\n", mhs.nm);
					printf("Kelas Pemrograman Dasar anda: %s\n\n", mhs.kls);
				}//ketika perulangan selesai

				//menutup file mahasiswa
				fclose(mahasiswa);
			}
		}

		//kondisi jika memilih menu ketiga
		if(choice==3){
			// Tambahan, read program mahasiswa
			duplikat = 0;
			printf("===Update data===\n");
			printf("\n");
			printf("Masukkan NIM Pratikan yang datanya ingin anda ubah: ");
			fflush(stdin);
			gets(nimUpdate);

			//membaca data file mahasiswa
			mahasiswa = fopen(mainData, "r");
			//mengecheck apakah nim yang ingin diedit tersedia
			if(mahasiswa == NULL){
				printf("Maaf file tidak dapat ditemukan!");
				fclose(mahasiswa);
			}else{
				while(fread(&mhs, sizeof(mhs), 1, mahasiswa)){
					if(strcmp(mhs.nim, nimUpdate)==0){ // jika data ditemukan
						duplikat=1;

						//mengubah data
						printf("Masukkan Nama Awal Pratikan anda yang ingin diubah: ");
						fflush(stdin);
						gets(nmInputanA);
						printf("Masukkan Nama Awal Pratikan anda yang ingin diubah: ");
						fflush(stdin);
						gets(nmInputanB);
						strcat(nmInputanA, " ");
						strcat(nmInputanA, nmInputanB);

						printf("Masukkan Kelas Pemrograman Dasar anda yang ingin diubah: ");
						fflush(stdin);
						gets(klsInputan);
						strupr(klsInputan);

						//memasukkan data inputan ke struct
						strcpy(mhs.nm, nmInputanA);
						strcpy(mhs.kls, klsInputan);

						//simpan struct yang telah dirubah ke dalam file yang baru
						mhsSementara = fopen(tempData, "a");
						fwrite(&mhs, sizeof(mhs), 1, mhsSementara);
						fclose(mhsSementara);

						printf("\n");
						printf("====================================\n");
						printf("|  	Data berhasil diubah       |\n");
						printf("====================================\n");
					}else{ //simpan data dari file lama ke yang baru
						mhsSementara = fopen(tempData, "a");
						fwrite(&mhs, sizeof(mhs), 1, mhsSementara);
						fclose(mhsSementara);
					}
				}//ketika perulangan selesai

				//menutup file mahasiswa
				fclose(mahasiswa);

				//hapus data lama, rubah temporary menjadi data baru
				berhasil = remove(mainData); //hapus file
				if(berhasil == 0){
					//file berhasil dihapus
				}else{
					printf("File tidak berhasil dihapus\n");
				}

				berhasil = rename(tempData, mainData); //rename file
				if(berhasil == 0){
					//file berhasil dirubah namanya
				}else{
					printf("File tidak berhasil dirubah namanya\n");
				}

			}

			if(duplikat == 0){
				printf("Maaf data tidak dapat ditemukan!");
			}
		}

		//kondisi jika memilih menu keempat
		if(choice==4){
			duplikat=0;
			printf("===Delete data===\n");
			printf("\n");
			printf("Masukkan NIM Pratikan yang datanya ingin anda hapus: ");
			fflush(stdin);
			gets(nimDelete);

			//membaca data file mahasiswa
			mahasiswa = fopen(mainData, "r");
			//mengecheck apakah nim yang akan dihapus tersedia
			if(mahasiswa == NULL){
				printf("Maaf file tidak dapat ditemukan!");
				fclose(mahasiswa);
			}else{
				while(fread(&mhs, sizeof(mhs), 1, mahasiswa)){
					if(strcmp(mhs.nim, nimDelete)==0) { //jika data ditemukan
						duplikat=1;
						printf("\n");
						printf("====================================\n");
						printf("|  	Data berhasil dihapus      |\n");
						printf("====================================\n");
					}else{ //simpan data dari file lama ke yang baru
						mhsSementara = fopen(tempData, "a");
						fwrite(&mhs, sizeof(mhs), 1, mhsSementara);
						fclose(mhsSementara);
					}
				}//ketika perulangan selesai

				//menutup file mahasiswa
				fclose(mahasiswa);

				//hapus data lama, rubah temporary menjadi data baru
				berhasil = remove(mainData); //hapus file
				if(berhasil == 0){
					// file berhasil dihapus
				}else{
					printf("File tidak berhasil dihapus\n");
				}

				berhasil = rename(tempData, mainData); //rename file
				if(berhasil == 0) {
					//file berhasil dirubah namanya
				}else{
					printf("File tidak berhasil dirubah namanya\n");
				}
			}

			if(duplikat == 0){
				printf("Maaf data tidak dapat ditemukan!");
			}
		}

		//kondisi jika memilih menu kelima
		if(choice==5){
			//keluar dari program
			printf("Program dihentikan...");
			return 0;
		}

		//tampilan untuk mengulang program
		printf("\n");
		printf("Apakah anda ingin mengulang program? [Y/T]: ");
		scanf("%s",&jawab);
		printf("\n");

    //perulangan do-while untuk mengulang prgoram
	}while (jawab == 'Y' || jawab == 'y');
	return 0;
}
