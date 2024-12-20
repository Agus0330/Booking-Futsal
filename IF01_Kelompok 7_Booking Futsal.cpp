#include <iostream>
#include <stdlib.h>
#include <string>
#include <conio.h>
#include <windows.h>
#include <iomanip>
#define MAX 20

using namespace std;

/*
* Ini adalah aplikasi dari 21-IF-01
* Dibuat oleh Kelompok 7
* 
*/

struct menuSewa {
	//deklarasi struct dari menuSewa
	char namaPembooking[10][10];
	char tanggal[10][10];
	int lamaMain[10];
	char jam[10][10];
	int jml;
	int totBayar;
	int menu;
}booking;

struct sortingSearching {
	//deklarasi struct dari Sorting & Searching

	//Sorting
	string namaPemain[7];
	int noPunggung[7];
	int index[7];
	int awal, akhir, sementara;
	//Searching
	int cariData;
	int penanda;
}lineUp;

struct jajan {
	int atasJajan;
	string namaJajan[MAX];
}stackJajan;

struct harga {
	int data;
	harga* next;
};

//agar bisa dipanggil di void yang lain
void opening();
void pilihanSatu();
void pilihanDua();
void pilihanTiga();
void pilihanEmpat();
void pilihanLima();
void pilihanEnam();
void pilihanTujuh();
void menuBalik();

void opening() {
	//menu pembuka/selamat datang
	system("cls");
	string pembuka[5] = {
		"\n+++++++++++++++++++++++++++++++++++\n",
		"+        21-IF-01 SEWA FUTSAL        +\n",
		"+++++++++++++++++++++++++++++++++++\n",
		"+  Universitas Amikom Yogyakarta  +\n",
		"+++++++++++++++++++++++++++++++++++\n" };
	for (int i = 0; i < 5; i++) {
		cout << pembuka[i];
	}
}


void isiForm() {
	/*
	* menu untuk mengisi form data/identitas penyewa
	*/
	cout << "Masukkan Jumlah Pembooking : ";
	cin >> booking.jml;
	system("cls");
	for (int j = 0; j < booking.jml; j++) {
		cout << "\n+++++++++++++++++++++++++++++++++++";
		cout << "\n+     Masukkan Data Diri Anda     +\n";
		cout << "+++++++++++++++++++++++++++++++++++";
		cout << "\nMasukkan Nama Anda : ";
		cin >> booking.namaPembooking[j];
		cout << "Tanggal Sewa *dd/mm/yy* : ";
		cin >> booking.tanggal[j];
		cout << "Jam Berapa *XX:XX AM/PM* : ";
		cin >> booking.jam[j];
		cout << "Berapa Jam Main : ";
		cin >> booking.lamaMain[j];
	}
}

/*
* Program Khusus Admin : Nambah Jajan
*/

void initJajan() {
	stackJajan.atasJajan = -1;
}

bool kosongJajan() {
	return stackJajan.atasJajan == -1;
}

bool fullJajan() {
	return stackJajan.atasJajan == MAX - 1;
}

void tambahJajan() {
	if (fullJajan()) {
		cout << "Stock Jajan Penuh!" << endl;
	}
	else {
		stackJajan.atasJajan++;
		cout << "\nMasukkan Jajan : "; cin >> stackJajan.namaJajan[stackJajan.atasJajan];
		system("cls");
		cout << "Jajan " << stackJajan.namaJajan[stackJajan.atasJajan] << " masuk kedalam stock" << endl;
	}
}

void hapusJajan() {
	if (kosongJajan()) {
		cout << "Stock Jajan Kosong!" << endl;
	}
	else {
		cout << "Jajan " << stackJajan.namaJajan[stackJajan.atasJajan] << " sudah terhapus" << endl;
		stackJajan.atasJajan--;
	}
}

void lihatJajan() {
	if (kosongJajan()) {
		cout << "JAJANNYA KOSONG!!! \nASTAGFIRULAHALDZIM!!!";
	}
	else {
		cout << "\n      STOCK JAJAN" << endl;
		cout << "_______________________" << endl;
		for (int i = stackJajan.atasJajan; i >= 0; i--) {
			cout << " [-] " << stackJajan.namaJajan[i] << "\n" << endl;
		}
	}
}

int menuJajan() {
	int pilihan;
	initJajan();
	do {
		cout << "\n   ADMIN-JAJAN   " << endl;
		cout << "_________________" << endl;
		cout << "\n1. Tambah Jajan\n"
			<< "\n2. Hapus Jajan\n"
			<< "\n3. Lihat Jajan\n"
			<< "\n4. Balik Menu User\n";
		cout << "Masukkan Pilihan : ";
		cin >> pilihan;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Jangan iseng, Tolong pilihlah dengan pilihan yang tersedia.\n";
			cout << "Masukkan pilihan : ";
			cin >> pilihan;
		}

		switch (pilihan) {
		case 1:
			system("cls");
			cout << "Note : Inputlah kalimat tanpa backspace. \n" << endl;
			tambahJajan();
			break;
		case 2:
			system("cls");
			hapusJajan();
			break;
		case 3:
			system("cls");
			lihatJajan();
			break;
		case 4:
			system("cls");
			menuBalik();
			break;
		default:
			cout << "Pilihan tidak tersedia" << endl;
			break;
		}

	} while (pilihan != 4);

	return 0;
}

/*
 * Program tambah harga jajan
 */

harga* head;
harga* tail;
harga* curr;
harga* entry;
harga* del;

void inisialHarga() {
	head = NULL;
	tail = NULL;
}

void input(int dt) {
	entry = (harga*)malloc(sizeof(harga));
	entry->data = dt;
	entry->next = NULL;

	if (head == NULL) {
		head = entry;
		tail = head;
	}
	else {
		tail->next = entry;
		tail = entry;
	}
}

void hapusHarga() {
	int simpan;
	if (head == NULL) {
		cout << "\nHarga Jajan Kosong!" << endl;
	}
	else {
		simpan = head->data;
		cout << "\nData yang terhapus : " << simpan << endl;

		del = head;
		head = head->next;
		delete del;
	}
}

void lihatHarga() {
	curr = head;
	if (head == NULL) {
		cout << "Tidak ada data Harga" << endl;
	}
	else {
		system("cls");
		cout << "\n______________________";
		cout << "\n== Data Harga Jajan ==" << endl;
		cout << "______________________\n\n";
		cout << setw(6);
		while (curr != NULL) {
			cout << "  [-]  " << curr->data << endl;
			curr = curr->next;
		}
		cout << endl;
	}
}

void menuHarga()
{
	char pilih, ulang;
	int data;

	do
	{
		system("cls");
		cout << "\n__________________________________________________\n";
		cout << "\n==           ADMIN-TAMBAH HARGA JAJAN           ==" << endl;
		cout << "== (Masukkan Harga Sesuai Urutan atas ke Bawah) ==" << endl;
		cout << "\n__________________________________________________\n" << endl;
		cout << "1. Tambah Harga" << endl;
		cout << "2. Hapus Harga" << endl;
		cout << "3. Lihat Harga" << endl;
		cout << "4. Balik Ke Menu User\n" << endl;

		cout << "   Nama Jajan   " << endl;
		cout << "________________" << endl;
		for (int i = stackJajan.atasJajan; i >= 0; i--) {
			cout << "\n [-] " << stackJajan.namaJajan[i] << "\n" << endl;
		}
		cout << "Masukkan pilihan Anda : ";
		cin >> pilih;

		switch (pilih)
		{
		case '1':
			cout << "\nMasukkan data : ";
			cin >> data;
			input(data);
			break;
		case '2':
			hapusHarga();
			break;
		case '3':
			lihatHarga();
			break;
		case '4':
			menuBalik();
		default:
			cout << "\nPilih ulang" << endl;
		}
		cout << "\nInput Ulang?(y/n)";
		cin >> ulang;
	} while (ulang == 'y' || ulang == 'Y');
}

void mainHarga() {
	inisialHarga();
	menuHarga();
}

/*
* Program User Untuk Menyewa Futsal
*/

void menuUtama() {
	/*
	* menu utama untuk
	* - lihat siapa saja yang telah membooking
	* - menambahkan lineup dan menyorting lineup
	* - mencari nomor punggung pemain yang sudah disorting
	* - keluar
	*/

	//panggil opening();
	opening();

	//Menu Booking
	cout << endl;
	cout << "1. Lihat Daftar Pembooking" << endl;
	//Sorting -LineUp-
	cout << "2. Masukkan Lineup" << endl;
	cout << "3. Cari Data Pemain" << endl;
	cout << "4. (Admin) : Jajan" << endl;
	cout << "5. (Admin) : Harga Jajan" << endl;
	cout << "6. Lihat Jajan & Harga" << endl;
	cout << "7. Keluar" << endl;
	cout << "Pilih Menu : ";
	cin >> booking.menu;
	system("cls");

	if (booking.menu == 1) {
		pilihanSatu();
		menuBalik();
	}

	else if (booking.menu == 2) {
		pilihanDua();
		menuBalik();
	}

	else if (booking.menu == 3) {
		pilihanTiga();
		menuBalik();
	}

	else if (booking.menu == 4) {
		pilihanEmpat();
		menuBalik();
	}

	else if (booking.menu == 5) {
		pilihanLima();
		menuBalik();
	}

	else if (booking.menu == 6) {
		pilihanEnam();
		menuBalik();
	}

	else if (booking.menu == 7) {
		cout << "\n+++++++++++++++++++++++";
		cout << "\n+     TERIMAKASIH     +\n";
		cout << "+++++++++++++++++++++++\n";
		exit(0);
	}

	else {
		cout << "\n--  Pilihan Tidak Tersedia  --\n";
		menuBalik();
	}
}

void menuBalik() {
	//menu untuk balik ke menuUtama
	char pilihBalik = 0;
	bool exitNow = false;

	cout << "\nBalik ke menu? (y/n) : ";
	cin >> pilihBalik;
	if (pilihBalik == 'y') {
		return menuUtama();
	}
	else if (pilihBalik == 'n') {
		cout << "\n+++++++++++++++++++++++";
		cout << "\n+     TERIMAKASIH     +\n";
		cout << "+++++++++++++++++++++++\n";
		exit(0);
	}
	else {
		cout << "\n+++++++++++++++++++++++++++++++";
		cout << "\n+   PILIHAN TIDAK TERSEDIA   +\n";
		cout << "+++++++++++++++++++++++++++++++++";
	}
}

void pilihanSatu() {
	// mengisi data pembooking dengan struct
	for (int k = 0; k < booking.jml; k++) {
		cout << "\n===========================" << endl;
		cout << "    Tampilkan Informasi    " << endl;
		cout << "===========================" << endl;
		cout << "Nama Anda 				: " << booking.namaPembooking[k] << endl;
		cout << "Tanggal Sewa 				: " << booking.tanggal[k] << endl;
		cout << "Jam Main 				: " << booking.jam[k] << endl;
		cout << "Lama Bermain 				: " << booking.lamaMain[k] << endl;
		//rumus total bayar
		booking.totBayar = 120000 * booking.lamaMain[k];
		cout << "Biaya Sewa 				: " << booking.totBayar << endl;
	}
}

void pilihanDua() {
	// menambahkan lineup pemain sekaligus mengurutkan dengan sorting
	// Sorting - Tambah Lineup Pemain
	cout << "++++++++++++++++++++++++++++++++";
	cout << "\n+  Silahkan Isi Lineup Pemain  +\n";
	cout << "++++++++++++++++++++++++++++++++\n";
	for (lineUp.awal = 0; lineUp.awal < 5; lineUp.awal++) {
		//input nama lineup
		cout << "Masukkan Nama Pemain : ";
		cin >> lineUp.namaPemain[lineUp.awal];
		//input no punggung lineup
		cout << "Masukkan No Punggung Pemain : ";
		cin >> lineUp.noPunggung[lineUp.awal];
	}

	// Proses sorting menggunakan Bubble Sort
	for (lineUp.awal = 0; lineUp.awal < 5; lineUp.awal++) {
		lineUp.index[lineUp.awal] = lineUp.awal;
	}

	for (lineUp.awal = 0; lineUp.awal < 4; lineUp.awal++) {
		for (lineUp.akhir = lineUp.awal + 1; lineUp.akhir < 5; lineUp.akhir++) {
			if (lineUp.noPunggung[lineUp.index[lineUp.awal]] > lineUp.noPunggung[lineUp.index[lineUp.akhir]]) {
				lineUp.sementara = lineUp.index[lineUp.awal];
				lineUp.index[lineUp.awal] = lineUp.index[lineUp.akhir];
				lineUp.index[lineUp.akhir] = lineUp.sementara;
			}
		}
	}

	for (lineUp.awal = 0; lineUp.awal < 5; lineUp.awal++) {
		cout << "\n++++++++++++++++++++++" << "++++++";
		cout << "\n+    Data Pemain Urut " << lineUp.awal << "    +\n";
		cout << "++++++++++++++++++++++" << "++++++\n";

		cout << "- Nama Pemain : " << lineUp.namaPemain[lineUp.index[lineUp.awal]] << "				- No Punggung : ";
		cout << lineUp.noPunggung[lineUp.index[lineUp.awal]] << endl;
	}
	cin.ignore();
	cin.get();

	// system("pause");
}

void pilihanTiga() {
	// mencari no Punggung pemain dengan searching
	//tampilkan data pemain
	cout << "+++++++++++++++++++++";
	cout << "\n+    Data Pemain    +\n";
	cout << "+++++++++++++++++++++\n";

	for (lineUp.awal = 0; lineUp.awal < 5; lineUp.awal++) {
		lineUp.index[lineUp.awal] = lineUp.awal;
	}

	for (lineUp.awal = 0; lineUp.awal < 4; lineUp.awal++) {
		for (lineUp.akhir = lineUp.awal + 1; lineUp.akhir < 5; lineUp.akhir++) {
			if (lineUp.noPunggung[lineUp.index[lineUp.awal]] > lineUp.noPunggung[lineUp.index[lineUp.akhir]]) {
				lineUp.sementara = lineUp.index[lineUp.awal];
				lineUp.index[lineUp.awal] = lineUp.index[lineUp.akhir];
				lineUp.index[lineUp.akhir] = lineUp.sementara;
			}
		}
	}

	for (lineUp.awal = 0; lineUp.awal < 5; lineUp.awal++) {
		cout << "\n+++++++++++++++++++++++" << "++++++";
		cout << "\n+     Data Pemain     +\n";
		cout << "+++++++++++++++++++++++" << "++++++\n";

		cout << "- Nama Pemain : " << lineUp.namaPemain[lineUp.index[lineUp.awal]] << "				- No Punggung : ";
		cout << lineUp.noPunggung[lineUp.index[lineUp.awal]] << endl;
	}

	cout << "\n==========================";
	cout << "\n     Cari Data Pemain     \n";
	cout << "==========================\n";

	cout << "Silahkan Masukkan No.Punggung Yang Dicari : ";
	cin >> lineUp.cariData;

	//pake sequential search

	for (lineUp.awal = 0; lineUp.awal < 5; lineUp.awal++) {
		if (lineUp.noPunggung[lineUp.index[lineUp.awal]] == lineUp.cariData) {
			lineUp.penanda = 1;
			break;
		}
	}

	if (lineUp.penanda == 1) {
		cout << "Data ditemukan pada indeks ke- " << lineUp.awal << endl;
	}
	else {
		cout << "Data tidak ditemukan";
	}
	cin.get();
	_getche();
}


void pilihanEmpat(void) {
	menuJajan();
}

void pilihanLima() {
	mainHarga();
}

void pilihanEnam() {
	curr = head;
	cout << "_______________"
		<< "\n| Nama Jajan  |"
		<< "\n|_____________|" << endl;
	for (int i = stackJajan.atasJajan; i >= 0; i--) {
		cout << "[-] " << stackJajan.namaJajan[i] << "\n\n";
	}

	cout << "\n _______________";
	cout << "\n|  Harga Jajan  |";
	cout << "\n|_______________|";
	if (head == NULL) {
		cout << "\n[-] Not found" << endl;
	}
	else {
		cout << setw(6);
		while (curr != NULL) {
			cout << "\n[-] " << curr->data << "\n" << endl;
			curr = curr->next;
		}
		cout << endl;
	}
	menuBalik();
}

void pilihanTujuh() {

	exit(0);
}

int main(void) {
	//tampilkan opening
	opening();

	//Menu Sewa
	isiForm();

	//tampilkan & input pilihan
	system("cls");
	opening();
	menuUtama();
}