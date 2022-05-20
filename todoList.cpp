#include <iostream>
#include <conio.h>
#include <iomanip>
#include <string>
#include <fstream>

// Ngecek OS doang
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

using namespace std;

struct InfoTodo
{
	int id;
	string judul, isi;
	bool selesai = 0;
	string startDate, dueDate;
};

// CRUD
void readTodo(InfoTodo todo[], int jml, int id = 0);
void addTodo(int jml);
void editTodo(InfoTodo todo[], int id, int jml);
void readFile(InfoTodo todo[], int &jml);
void addToFile(InfoTodo todo);
void addFiles(InfoTodo todo[], int jml);

void sorting(int array[], int size);

void searchById(InfoTodo todo[], int jml);

// Fungsi buat Tanggal
string getCurrentTime();
string numMonth(string month);
int *getDateInt(string date);
int strToInt(string str);

string replaceSpasi(string str);
string replaceHyphen(string str);

int main()
{
	InfoTodo todo[100];

	int banyakTodo = 0, idTodo;
	bool isExit = 0;
	char cariUlang, pilihanMenu;

	do
	{
		readFile(todo, banyakTodo);
		readTodo(todo, banyakTodo);

		cout << "Menu: \n"
				 << "[1] Tambah To-Do \n"
				 << "[2] Edit To-Do \n"
				 << "[3] Delete To-Do \n"
				 << "[4] Urutkan To-Do \n"
				 << "[5] Cari To-Do \n"
				 << "[6] Eksport To-Do \n"
				 << "[...] Keluar \n\n";

		cout << "Pilihan menu: ";
		cin >> pilihanMenu;

		system(CLEAR);

		switch (pilihanMenu)
		{
		case '1':
			addTodo(banyakTodo);
			break;

		case '2':
		{
			int id;

			readTodo(todo, banyakTodo);

			cout << "Masukkan Id: ";
			cin >> id;
			system(CLEAR);

			// Menampilkan Todo
			readTodo(todo, id, id - 1);
			editTodo(todo, id, banyakTodo);

			break;
		}

		case '3':
			break;

		case '4':
		{
			// Tanggal yang masih berbentuk string
			string tglStr = getCurrentTime();

			// Tanggal yang sudah berbentuk array of integer
			int *tglInt = getDateInt(tglStr);

			cout << "tgl (string): " << tglStr << "\n";
			cout << "tgl (int): ";
			for (int i = 0; i < 3; i++)
				cout << tglInt[i] << " ";

			break;
		}

		case '5':
			cout << "Cari berdasarkan: \n"
					 << "[1] ID \n"
					 << "[2] Start Date \n"
					 << "[3] Due Date \n"
					 << "[...] Kembali \n"
					 << "Pilih > ";
			cin >> pilihanMenu;
			system(CLEAR);

			switch (pilihanMenu)
			{
			case '1':
				searchById(todo, banyakTodo);
				break;

			default:
				break;
			}

			cout << "\nTerima kasih telah menggunakan program kami!";
			break;

		case '6':
		{
			cout << "Program anda akan diexport dalam bentuk file .txt dengan nama 'export.txt'" << endl;
			cout << "Please wait..." << endl
					 << endl;
			system("pause");
			system("cls");
			ofstream ofs("export.txt");

			if (ofs.is_open())
			{
				ofs << " --------------------------------------------------------------------------------------------------------" << endl;
				ofs << "| ID |                             TO - DO                             |    Input Date   |    Due Date   |" << endl;
				ofs << " --------------------------------------------------------------------------------------------------------" << endl;

				for (int i = 0; i < banyakTodo; i++)
				{
					ofs << "|" << setiosflags(ios::left) << setw(4) << i + 1;
					ofs << "|" << setiosflags(ios::left) << setw(65) << todo[i].judul;
					ofs << "|" << setiosflags(ios::left) << setw(17) << todo[i].startDate;
					ofs << "|" << setiosflags(ios::left) << setw(15) << todo[i].dueDate << "|" << endl;
					ofs << "|" << setiosflags(ios::left) << setw(4) << " ";
					ofs << "|" << setiosflags(ios::left) << setw(65) << todo[i].isi;
					ofs << "|" << setiosflags(ios::left) << setw(17) << " ";
					ofs << "|" << setiosflags(ios::left) << setw(15) << " "
							<< "|" << endl;
					ofs << " --------------------------------------------------------------------------------------------------------" << endl;
				}

				ofs.close();

				cout << "Silahkan cek file lokasi source code ini. Anda akan menemukan hasil export tersebut dengan nama file 'export.txt'" << endl;
				cout << "Terima kasih telah menggunakan program kami";
			}

			break;
		}

		default:
			isExit = 1;
			break;
		}
		system(CLEAR);
	} while (isExit != 1);

	cout << "Terima kasih telah menggunakan program kami.";
	return 0;
}

void readTodo(InfoTodo todo[], int jml, int id)
{
	cout << " --------------------------------------------------------------------------------------------------------" << endl;
	cout << "| ID |                             TO - DO                             |    Start Date   |    Due Date   |" << endl;
	cout << " --------------------------------------------------------------------------------------------------------" << endl;

	for (int i = id; i < jml; i++)
	{
		cout << "|" << setiosflags(ios::left) << setw(4) << i + 1;
		cout << "|" << setiosflags(ios::left) << setw(65) << todo[i].judul;
		cout << "|" << setiosflags(ios::left) << setw(17) << todo[i].startDate;
		cout << "|" << setiosflags(ios::left) << setw(15) << todo[i].dueDate << "|" << endl;
		cout << "|" << setiosflags(ios::left) << setw(4) << " ";
		cout << "|" << setiosflags(ios::left) << setw(65) << todo[i].isi;
		cout << "|" << setiosflags(ios::left) << setw(17) << " ";
		cout << "|" << setiosflags(ios::left) << setw(15) << " "
				 << "|" << endl;
		cout << " --------------------------------------------------------------------------------------------------------" << endl;
	}
	cout << "\n";
}

void readFile(InfoTodo todo[], int &jml)
{
	string fileName = "rafli.txt"; // Temporary

	ifstream myFile(fileName);
	jml = 0;

	if (myFile.is_open())
	{
		int i = jml;
		while (!myFile.eof())
		{
			myFile >> todo[i].id >> todo[i].judul >> todo[i].isi;
			myFile >> todo[i].startDate >> todo[i].dueDate >> todo[i].selesai;

			todo[i].judul = replaceHyphen(todo[i].judul);
			todo[i].isi = replaceHyphen(todo[i].isi);
			i++;
		}

		jml += i - 1;
		myFile.close();
	}
	else
		cout << "Todo masih kosong. \n";
}

void addTodo(int jml)
{
	InfoTodo todo;

	todo.id = jml + 1;
	todo.startDate = getCurrentTime();

	cout << "Judul  \t\t: ";
	cin.ignore();
	getline(cin, todo.judul);
	cout << "Isi \t\t: ";
	getline(cin, todo.isi);
	cout << "Due Date [DD/MM/YYY]: ";
	cin >> todo.dueDate;

	addToFile(todo);

	cout << "\n"
			 << "Berhasil menambahkan todo!";
	getch();
	system(CLEAR);
}

void addToFile(InfoTodo todo)
{
	string fileName = "rafli.txt"; // Temporary

	todo.judul = replaceSpasi(todo.judul);
	todo.isi = replaceSpasi(todo.isi);

	ofstream myFile(fileName, ios::app);
	if (myFile.is_open())
	{
		// Contoh format file:
		// 1 lorem_ipsum lorem_ipsum_dolor_sit_amet 04/05/2022 19/04/2022 0

		myFile << todo.id << " "
					 << todo.judul << " " << todo.isi << " "
					 << todo.startDate << " " << todo.dueDate << " "
					 << todo.selesai << "\n";

		myFile.close();
	}
	else
		cout << "Todo masih kosong. \n";
}

void addFiles(InfoTodo todo[], int jml)
{
	int i;
	string fileName = "rafli.txt"; // Temporary

	for (i = 0; i < jml; i++)
	{
		todo[i].judul = replaceSpasi(todo[i].judul);
		todo[i].isi = replaceSpasi(todo[i].isi);
	}

	ofstream myFile(fileName);
	if (myFile.is_open())
	{
		for (i = 0; i < jml; i++)
		{
			// Contoh format file:
			// 1 lorem_ipsum lorem_ipsum_dolor_sit_amet 04/05/2022 19/04/2022 0

			myFile << todo[i].id << " "
						 << todo[i].judul << " " << todo[i].isi << " "
						 << todo[i].startDate << " " << todo[i].dueDate << " "
						 << todo[i].selesai << "\n";
		}
		myFile.close();
	}
	else
		cout << "Todo masih kosong. \n";
}

void editTodo(InfoTodo todo[], int id, int jml)
{
	char menu;
	bool status = todo[id - 1].selesai;
	string judul, isi, dueDate;

	cout << "Pilih yang ingin diubah: \n"
			 << "[1] Judul \n"
			 << "[2] Isi \n"
			 << "[3] Due Date \n"
			 << "[4] Status \n"
			 << "[...] Kembali \n"
			 << "Pilih > ";
	cin >> menu;

	switch (menu)
	{
	case '1':
		cout << "Ubah judul: ";
		cin.ignore();
		getline(cin, judul);
		todo[id - 1].judul = judul;
		break;

	case '2':
		cout << "Ubah isi: ";
		cin.ignore();
		getline(cin, isi);

		todo[id - 1].isi = isi;

		cout << "Berhasil mengubah judul.";
		getch();
		break;

	case '3':
		cout << "Ubah Tgl [DD/MM/YYYY]: ";
		cin.ignore();
		getline(cin, dueDate);

		todo[id - 1].dueDate = dueDate;

		cout << "Berhasil mengubah isi.";
		getch();
		break;

	case '4':
		todo[id - 1].selesai = !status;
		cout << "Berhasil mengubah status todo.";
		getch();
		break;

	default:
		break;
	}

	addFiles(todo, jml);
}

void sorting(int array[], int size)
{
	int temp, i, j;

	for (i = 0; i < size - 1; i++)
	{
		for (j = 0; j < size - i - 1; j++)
		{
			if (array[j] > array[j + 1])
			{
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}
}

void searchById(InfoTodo todo[], int jml)
{
	int idTodo, i;
	bool found;
	char cariUlang;

	do
	{
		cout << "Masukkan ID To-Do yang ingin dicari : ";
		cin >> idTodo;

		found = false;
		i = 0;

		while ((i <= jml) && !(found))
		{
			if (todo[i].id == idTodo)
				found = true;
			else
				i++;
		}

		if (found)
		{
			cout << endl;
			cout << "Data " << idTodo << " ditemukan!" << endl;
			cout << "Input Date  : " << todo[i].startDate << endl;
			cout << "Judul       : " << todo[i].judul << endl;
			cout << "Isi         : " << todo[i].isi << endl;
			cout << "Due Date    : " << todo[i].dueDate << endl;
		}
		else
			cout << "Data tidak ditemukan!" << endl;

		do
		{
			cout << "\nApakah anda ingin mencari data lagi (y/n)? ";
			cin >> cariUlang;

			if (!(cariUlang == 'y' || cariUlang == 'Y' || cariUlang == 'N' || cariUlang == 'n'))
				cout << "Input yang anda masukkan salah!" << endl;

		} while (!(cariUlang == 'y' || cariUlang == 'Y' || cariUlang == 'N' || cariUlang == 'n'));

		if (cariUlang == 'y' || cariUlang == 'Y')
		{
			system("pause");
			system(CLEAR);
		}
	} while (cariUlang == 'y' || cariUlang == 'Y');
}

string getCurrentTime()
{
	// Mengambil waktu sekarang
	time_t now = time(0);

	// Konversi ke string
	char *dt = ctime(&now);

	// Memisah tgl, bln, thn
	char day[] = {dt[8], dt[9], '\0'};
	char month[] = {dt[4], dt[5], dt[6], '\0'};
	char year[] = {dt[20], dt[21], dt[22], dt[23], '\0'};

	string date = string(day) + "/" + numMonth(month) + "/" + year;

	return date;
}

string numMonth(string month)
{
	string months[][12] = {
			{"Jan", "Feb", "Mar", "Apr", "May", "Jun",
			 "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"},
			{"01", "02", "03", "04", "05", "06",
			 "07", "08", "09", "10", "11", "12"}};

	// Melakukan pengecekan antara input bln & bln yang ada
	for (int i = 0; i < 12; i++)
		if (month == months[0][i])
			return months[1][i];

	return "01";
}

int *getDateInt(string date)
{
	int *tgl = new int[3];

	if (!(date.length() < 9))
	{
		// Memisah tgl, bln, thn
		char day[] = {date[0], date[1], '\0'};
		char month[] = {date[3], date[4], '\0'};
		char year[] = {date[6], date[7], date[8], date[9], '\0'};

		tgl[0] = strToInt(day);
		tgl[1] = strToInt(month);
		tgl[2] = strToInt(year);
	}
	else
	{
		cout << "Tidak dapat mengambil tanggal! \n";

		tgl[0] = 31;
		tgl[1] = 1;
		tgl[2] = 2022;
	}

	return tgl;
}

int strToInt(string str)
{
	int num = 0;
	int n = str.length();

	for (int i = 0; i < n; i++)
		num = num * 10 + (int(str[i]) - 48);

	return num;
}

string replaceSpasi(string str)
{
	for (int i = 0; i < str.length(); i++)
		if (str[i] == ' ')
			str[i] = '-';

	return str;
}

string replaceHyphen(string str)
{
	for (int i = 0; i < str.length(); i++)
		if (str[i] == '-')
			str[i] = ' ';

	return str;
}