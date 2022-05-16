#include <iostream>
#include <conio.h>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

struct Infotodo {
	int id;
	string judul, isi;
	bool selesai;
	string dueDate;
	string inputDate;
};

void sorting (int array[], int size);

int main (){
	int banyakTodo, pilihanMenu, i, idTodo;
	bool found;
	char cariUlang;
	
	cout << "Banyak To-Do yang ingin di list : ";
	cin >> banyakTodo;
	Infotodo todo[banyakTodo];
	cout << endl;
	cin.ignore();
	
	for (int i = 0; i < banyakTodo; i++) {
		cout << "ID          : " << i+1 << endl;
		cout << "Date Format : DD/MM/YYYY" << endl;
		cout << "Input Date  : ";
		getline(cin, todo[i].inputDate);
		cout << "Judul       : "; 
		getline(cin, todo[i].judul);
		cout << "Isi         : "; 
		getline(cin, todo[i].isi);
		cout << "Due Date    : ";
		getline(cin, todo[i].dueDate);
		cout << endl;
	}	
	
	system ("pause");
	system ("cls");
	
	for (int i = 0; i < banyakTodo; i++) {
		cout << "Input Date   : " << todo[i].inputDate << endl;
		cout << "ID           : " << i+1 << endl;
		todo[i].id = i+1;
		cout << "Judul        : " << todo[i].judul << endl; 
		cout << "Isi          : " << todo[i].isi << endl;
		cout << "Due Date     : " << todo[i].dueDate << endl << endl;
	}
	
	system ("pause");
	system ("cls");
	
	cout << " --------------------------------------------------------------------------------------------------------" << endl;
	cout << "| ID |                             TO - DO                             |    Input Date   |    Due Date   |" << endl;
	cout << " --------------------------------------------------------------------------------------------------------"<< endl;
	for (int i = 0; i < banyakTodo; i++) {
		cout << "|" << setiosflags(ios::left) << setw(4) << i+1;
		cout << "|" << setiosflags(ios::left) << setw(65) << todo[i].judul;
		cout << "|" << setiosflags(ios::left) << setw(17) << todo[i].inputDate;
		cout << "|" << setiosflags(ios::left) << setw(15) << todo[i].dueDate << "|" <<endl;
		cout << "|" << setiosflags(ios::left) << setw(4) << " ";
		cout << "|" << setiosflags(ios::left) << setw(65) << todo[i].isi;
		cout << "|" << setiosflags(ios::left) << setw(17) << " ";
		cout << "|" << setiosflags(ios::left) << setw(15) << " " << "|" << endl;
		cout << " --------------------------------------------------------------------------------------------------------"<< endl;
	}
	
	cout << endl;
	cout << "Menu : " << endl;
	cout << "[1] Tambah To-Do" << endl;
	cout << "[2] Edit To-Do" <<endl;
	cout << "[3] Delete To-Do" << endl;
	cout << "[4] Urutkan To-Do" << endl;
	cout << "[5] Cari To-Do" << endl;
	cout << "[6] Eksport To-Do" << endl;
	cout << "[7] Keluar" << endl;
	do {
	cout << "Pilihan menu : ";
	cin >> pilihanMenu;
	if (!(pilihanMenu >= 1 && pilihanMenu <=7)) cout << endl << "Input yang dimasukkan salah!" <<endl;
	} while (!(pilihanMenu >= 1 && pilihanMenu <=6));
	
	system ("pause");
	system ("cls");
	
	switch (pilihanMenu) {
		case 1 :
			break;
		case 2 :
			break;
		case 3 :
			break;
		case 4 : 
			break;
		case 5 :
			do{
			cout << "Masukkan ID To-Do yang ingin dicari : ";
			cin >> idTodo;
			found = false;
			i = 0;
			while ((i <= banyakTodo) && !(found)){
				if (todo[i].id == idTodo) {
					found = true;
				} else {
					i++;
				}
			}
			if (found) {
				cout << endl;
				cout << "Data " << idTodo << " ditemukan!" <<endl;
				cout << "Input Date  : " << todo[i].inputDate << endl;
				cout << "Judul       : " << todo[i].judul << endl;
				cout << "Isi         : " << todo[i].isi << endl;
				cout << "Due Date    : " << todo[i].dueDate << endl;	
			} else {
				cout << "Data tidak ditemukan!" << endl;
			}
			do {
				cout << "\nApakah anda ingin mencari data lagi y/n ? ";
				cin >> cariUlang;
				if (!(cariUlang == 'y' ||cariUlang == 'Y'||cariUlang == 'N'||cariUlang == 'n')) cout << "Input yang anda masukkan salah!" << endl;
				} while (!(cariUlang == 'y' ||cariUlang == 'Y'||cariUlang == 'N'||cariUlang == 'n'));
				if (cariUlang == 'y' || cariUlang == 'Y') {
				system ("pause");
				system ("cls");
				}
			} while (cariUlang == 'y' || cariUlang == 'Y');
				cout << "\nTerima kasih telah menggunakan program kami!";
			break;
		case 6 :
			cout << "Program anda akan diexport dalam bentuk file .txt dengan nama 'export.txt'" << endl;
			cout << "Please wait..." << endl << endl;
			system ("pause");
			system ("cls");
			ofstream ofs("export.txt");
			if (ofs.is_open()) {
				ofs << " --------------------------------------------------------------------------------------------------------" << endl;
				ofs << "| ID |                             TO - DO                             |    Input Date   |    Due Date   |" << endl;
				ofs << " --------------------------------------------------------------------------------------------------------"<< endl;
				for (int i = 0; i < banyakTodo; i++) {
					ofs << "|" << setiosflags(ios::left) << setw(4) << i+1;
					ofs << "|" << setiosflags(ios::left) << setw(65) << todo[i].judul;
					ofs << "|" << setiosflags(ios::left) << setw(17) << todo[i].inputDate;
					ofs << "|" << setiosflags(ios::left) << setw(15) << todo[i].dueDate << "|" <<endl;
					ofs << "|" << setiosflags(ios::left) << setw(4) << " ";
					ofs << "|" << setiosflags(ios::left) << setw(65) << todo[i].isi;
					ofs << "|" << setiosflags(ios::left) << setw(17) << " ";
					ofs << "|" << setiosflags(ios::left) << setw(15) << " " << "|" << endl;
					ofs << " --------------------------------------------------------------------------------------------------------"<< endl;
				}
				ofs.close();
				cout << "Silahkan cek file lokasi source code ini. Anda akan menemukan hasil export tersebut dengan nama file 'export.txt'" << endl;
				cout << "Terima kasih telah menggunakan program kami";
			}
			break;	
	}
}

void sorting (int array[], int size) {
	int temp, i, j;
	
	for (i = 0; i < size - 1; i++) {
		for (j = 0; j < size - i - 1; j++) {
			if (array[j] > array[j+1]) {
				temp = array[j];
				array[j] = array[j+1];
				array[j+1] = temp;
			}
		}
	}
}
