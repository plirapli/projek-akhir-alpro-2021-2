#include <iostream>
#include <conio.h>
#include <iomanip>
#include <string>
#include <fstream>

// Ngecek OS
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
	string dueDate;
	string startDate;
};

void readTodo(InfoTodo todo[], int jml);
void readFile(InfoTodo todo[], int &jml);

void addTodo(int jml);
void addToFile(InfoTodo todo);

void sorting(int array[], int size);

string getCurrentTime();
string numMonth(string month);
string replaceSpasi(string str);
string replaceHyphen(string str);

int main()
{
	InfoTodo todo[100];

	int banyakTodo = 0, i, idTodo;
	bool isExit = 0, found;
	char cariUlang, pilihanMenu;

	do
	{
		readFile(todo, banyakTodo);
		readTodo(todo, banyakTodo);
		cout << "\n";

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

		system("cls");

		switch (pilihanMenu)
		{
		case '1':
			addTodo(banyakTodo);
			break;

		case '2':
			break;

		case '3':
			break;

		case '4':
			break;

		case '5':
			do
			{
				cout << "Masukkan ID To-Do yang ingin dicari : ";
				cin >> idTodo;

				found = false;
				i = 0;

				while ((i <= banyakTodo) && !(found))
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
					cout << "\nApakah anda ingin mencari data lagi y/n ? ";
					cin >> cariUlang;
					if (!(cariUlang == 'y' || cariUlang == 'Y' || cariUlang == 'N' || cariUlang == 'n'))
						cout << "Input yang anda masukkan salah!" << endl;
				} while (!(cariUlang == 'y' || cariUlang == 'Y' || cariUlang == 'N' || cariUlang == 'n'));

				if (cariUlang == 'y' || cariUlang == 'Y')
				{
					system("pause");
					system("cls");
				}
			} while (cariUlang == 'y' || cariUlang == 'Y');

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
			cout << "Terima kasih telah menggunakan program kami.";
			isExit = 1;
			break;
		}
	} while (isExit != 1);
}

void readTodo(InfoTodo todo[], int jml)
{
	cout << " --------------------------------------------------------------------------------------------------------" << endl;
	cout << "| ID |                             TO - DO                             |    Start Date   |    Due Date   |" << endl;
	cout << " --------------------------------------------------------------------------------------------------------" << endl;

	for (int i = 0; i < jml; i++)
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
		// 1 lorem_ipsum lorem_ipsum_dolor_sit_amet 04/05/2022 19/04/2022 1

		myFile << todo.id << " "
					 << todo.judul << " " << todo.isi << " "
					 << todo.startDate << " " << todo.dueDate << " "
					 << todo.selesai << "\n";

		myFile.close();
	}
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