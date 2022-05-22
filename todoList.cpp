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

struct User
{
	string username, password;
	// InfoTodo todo[100];
};

// User Related
int userLogin(User user[], int jmlUser);
void userRegister(User user[], int &jmlUser);

// Todo CRUD
void readTodo(InfoTodo todo[], int jml, int id = 0);
void addTodo(InfoTodo todo[], int jml, string user);
void editTodo(InfoTodo todo[], int id, int jml, string user);

// R/W Files
void readFile(InfoTodo todo[], int &jml, string user);	// Read files
void writeFiles(InfoTodo todo[], int jml, string user); // Write multiple files

// Sorting
void sortByDate(InfoTodo todo[], int jml, string tglStr[]);
void sortByStatus(InfoTodo todo[], int jml);
void sorting(InfoTodo todo[], int size, int sorter[]);

// Searching
void searchById(InfoTodo todo[], int jml);
void searchByDate(InfoTodo todo[], int jml, bool startDate = 1);
int *multipleSearch(InfoTodo todo[], int jml, string input, bool startDate = 1);

// Fungsi buat Tanggal
string getCurrentTime();
string numMonth(string month);
int *getDateInt(string date, int indeks);
int strToInt(string str);

// Manipulasi String
char checkMark(bool status);
string replaceSpasi(string str);
string replaceHyphen(string str);

// Misc
void pressAnyKey();

int main()
{
	User user[100];
	InfoTodo todo[100];

	// Temporary User (Only for testing)
	user[0].username = "mrafli";
	user[0].password = "12345";

	int pilihSort, i;

	int jmlUser = 1, idUser;
	int banyakTodo = 0, idTodo;
	bool repeatMenu = 1, repeatMainMenu = 1, isExit = 0;
	char cariUlang, pilihanMenu;
	string userName;

	do
	{
		// Login
		do
		{
			cout << "Selamat Datang! \n"
					 << "[1] Login \n"
					 << "[2] Daftar \n"
					 << "[...] Keluar \n"
					 << "Pilih > ";
			cin >> pilihanMenu;
			system(CLEAR);

			switch (pilihanMenu)
			{
			case '1':
				idUser = userLogin(user, jmlUser);
				repeatMenu = idUser != -1 ? 0 : 1;
				repeatMainMenu = 1;
				break;

			case '2':
				userRegister(user, jmlUser);
				cout << user[jmlUser - 1].username << ": " << user[jmlUser - 1].password << "\n";
				repeatMenu = 1;
				repeatMainMenu = 1;
				break;

			default:
				repeatMenu = 0;
				repeatMainMenu = 0;
				isExit = 1;
				break;
			}
		} while (repeatMenu);

		// Main Menu
		while (repeatMainMenu)
		{
			userName = user[idUser].username;

			system(CLEAR);
			cout << "TODO LIST APP \n";

			readFile(todo, banyakTodo, userName);
			readTodo(todo, banyakTodo);

			cout << "Menu: \n"
					 << "[1] Tambah To-Do \n"
					 << "[2] Edit To-Do \n"
					 << "[3] Delete To-Do \n"
					 << "[4] Urutkan To-Do \n"
					 << "[5] Cari To-Do \n"
					 << "[6] Eksport To-Do \n"
					 << "[7] Logout \n"
					 << "[...] Keluar \n\n";
			cout << "Pilihan menu: ";
			cin >> pilihanMenu;

			system(CLEAR);

			switch (pilihanMenu)
			{
			case '1':
				addTodo(todo, banyakTodo, userName);
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
				editTodo(todo, id, banyakTodo, userName);
				break;
			}

			case '3':
			{
				int inputId;
				readTodo(todo, banyakTodo);

				cout << "Masukkan Nomor: ";
				cin >> inputId;

				// Menaikkan baris
				for (int i = inputId - 1; i < banyakTodo; i++)
				{
					todo[i] = todo[i + 1];
					todo[i].id -= 1;
				}

				banyakTodo--;
				writeFiles(todo, banyakTodo, userName);

				cout << "\n"
						 << "Todo telah dihapus! \n";
				pressAnyKey();

				break;
			}

			case '4':
			{
				string tglStr[100];
				InfoTodo sortedTodo[100];

				/* Mengcloning struct yang asli ke struct baru
					 yang akan digunakan untuk sorting */
				for (int i = 0; i < banyakTodo; i++)
					sortedTodo[i] = todo[i];

				cout << "Sorting berdasarkan : " << endl;
				cout << "Cari berdasarkan: \n"
						 << "[1] Start Date \n"
						 << "[2] Due Date \n"
						 << "[3] Status \n"
						 << "[...] Kembali \n"
						 << "Pilih > ";
				cin >> pilihanMenu;
				system(CLEAR);

				switch (pilihanMenu)
				{
				case '1':
					for (int i = 0; i < banyakTodo; i++)
						// Tanggal yang masih berbentuk string
						tglStr[i] = todo[i].startDate;

					sortByDate(sortedTodo, banyakTodo, tglStr);
					break;

				case '2':
					for (int i = 0; i < banyakTodo; i++)
						// Tanggal yang masih berbentuk string
						tglStr[i] = todo[i].dueDate;

					sortByDate(sortedTodo, banyakTodo, tglStr);
					break;

				case '3':
					sortByStatus(sortedTodo, banyakTodo);
					break;

				default:
					break;
				}
			}
			break;

			case '5':
			{
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

				case '2':
					searchByDate(todo, banyakTodo);
					break;

				case '3':
					searchByDate(todo, banyakTodo, 0);
					break;

				default:
					break;
				}

				break;
			}

			case '6':
			{
				cout << "Program anda akan diexport dalam bentuk file .txt dengan nama 'export.txt'" << endl;
				cout << "Please wait..." << endl
						 << endl;
				pressAnyKey();
				ofstream ofs("export.txt");

				if (ofs.is_open())
				{
					ofs << " ---------------------------------------------------------------------------------------------------------------------" << endl;
					ofs << "| ID |                             TO - DO                             |    Start Date   |    Due Date   |   status   |" << endl;
					ofs << " ---------------------------------------------------------------------------------------------------------------------" << endl;

					for (int i = 0; i < banyakTodo; i++)
					{
						ofs << "|" << setiosflags(ios::left) << setw(4) << i + 1;
						ofs << "|" << setiosflags(ios::left) << setw(65) << todo[i].judul;
						ofs << "|" << setiosflags(ios::left) << setw(17) << todo[i].startDate;
						ofs << "|" << setiosflags(ios::left) << setw(15) << todo[i].dueDate;
						ofs << "|" << setiosflags(ios::left) << setw(12) << checkMark(todo[i].selesai) << "|" << endl;
						ofs << "|" << setiosflags(ios::left) << setw(4) << " ";
						ofs << "|" << setiosflags(ios::left) << setw(65) << todo[i].isi;
						ofs << "|" << setiosflags(ios::left) << setw(17) << " ";
						ofs << "|" << setiosflags(ios::left) << setw(15) << " ";
						ofs << "|" << setiosflags(ios::left) << setw(12) << " "
								<< "|" << endl;
						ofs << " ---------------------------------------------------------------------------------------------------------------------" << endl;
					}

					ofs.close();

					cout << "Silahkan cek file lokasi source code ini. Anda akan menemukan hasil export tersebut dengan nama file 'export.txt'" << endl;
					cout << "Terima kasih telah menggunakan program kami";
				}
				pressAnyKey();
				break;
			}

			case '7':
				repeatMainMenu = 0;
				break;

			default:
				repeatMainMenu = 0;
				isExit = 1;
				break;
			}
		}
	} while (!isExit);

	cout << "Terima kasih telah menggunakan program kami.";
	return 0;
}

int userLogin(User user[], int jmlUser)
{
	int indexUser = -1, loginAttempt = 0;
	bool repeat = 1;

	do
	{
		string username, passwd;

		cout << "[LOGIN] \n"
				 << "Username: ";
		cin >> username;
		cout << "Password: ";
		cin >> passwd;
		cout << "\n";

		for (int i = 0; i < jmlUser; i++)
		{
			if (username == user[i].username && passwd == user[i].password)
			{
				indexUser = i;
				repeat = 0;
				break;
			}
		}

		if (indexUser == -1)
		{
			cout << "Username atau password anda salah! \n";
			loginAttempt++;
		}
		else
			cout << "Login berhasil! \n";

		pressAnyKey();
	} while (repeat && loginAttempt < 3);

	return indexUser;
}

void userRegister(User user[], int &jmlUser)
{
	bool repeat = 1;

	do
	{
		bool isExist = 0;
		string username, passwd;

		cout << "[Daftar] \n"
				 << "Masukkan username: ";
		cin >> username;
		cout << "Masukkan password: ";
		cin >> passwd;
		cout << "\n";

		for (int i = 0; i < jmlUser; i++)
		{
			if (username == user[i].username)
			{
				isExist = 1;
				repeat = 1;
				break;
			}
		}

		if (!isExist)
		{
			user[jmlUser].username = username;
			user[jmlUser].password = passwd;
			repeat = 0;

			cout << "User " + username + " telah berhasil didaftarkan! \n";
		}
		else
			cout << "User " + username + " telah terpakai! \n";

		pressAnyKey();
	} while (repeat);

	jmlUser++;
}

void readTodo(InfoTodo todo[], int jml, int id)
{
	cout << " ---------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "| ID |                             TO - DO                             |    Start Date   |    Due Date   |   status   |" << endl;
	cout << " ---------------------------------------------------------------------------------------------------------------------" << endl;

	for (int i = id; i < jml; i++)
	{
		cout << "|" << setiosflags(ios::left) << setw(4) << todo[i].id;
		cout << "|" << setiosflags(ios::left) << setw(65) << todo[i].judul;
		cout << "|" << setiosflags(ios::left) << setw(17) << todo[i].startDate;
		cout << "|" << setiosflags(ios::left) << setw(15) << todo[i].dueDate;
		cout << "|" << setiosflags(ios::left) << setw(12) << checkMark(todo[i].selesai) << "|" << endl;
		cout << "|" << setiosflags(ios::left) << setw(4) << " ";
		cout << "|" << setiosflags(ios::left) << setw(65) << todo[i].isi;
		cout << "|" << setiosflags(ios::left) << setw(17) << " ";
		cout << "|" << setiosflags(ios::left) << setw(15) << " ";
		cout << "|" << setiosflags(ios::left) << setw(12) << " "
				 << "|" << endl;
		cout << " ---------------------------------------------------------------------------------------------------------------------" << endl;
	}
	cout << "\n";
}

void readFile(InfoTodo todo[], int &jml, string user)
{
	string fileName = "./todo/" + user + ".txt"; // Temporary

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
		cout << "Gagal membuka file. \n";
}

void addTodo(InfoTodo todo[], int jml, string user)
{
	todo[jml].id = jml + 1;
	todo[jml].startDate = getCurrentTime();

	cout << "Judul  \t\t: ";
	cin.ignore();
	getline(cin, todo[jml].judul);
	cout << "Isi \t\t: ";
	getline(cin, todo[jml].isi);
	cout << "Due Date [DD/MM/YYY]: ";
	cin >> todo[jml].dueDate;
	cout << "\n";

	jml++;

	writeFiles(todo, jml, user);
	pressAnyKey();
}

void writeFiles(InfoTodo todo[], int jml, string user)
{
	int i;
	string fileName = "./todo/" + user + ".txt"; // Temporary

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
		cout << "Gagal membuka file. \n";
}

void editTodo(InfoTodo todo[], int id, int jml, string user)
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

		cout << "\n\n";
		cout << "Berhasil mengubah judul! \n\n";
		pressAnyKey();
		break;

	case '2':
		cout << "Ubah isi: ";
		cin.ignore();
		getline(cin, isi);

		todo[id - 1].isi = isi;

		cout << "\n\n";
		cout << "Berhasil mengubah isi! \n\n";
		pressAnyKey();
		break;

	case '3':
		cout << "Ubah Tgl [DD/MM/YYYY]: ";
		cin.ignore();
		getline(cin, dueDate);

		todo[id - 1].dueDate = dueDate;

		cout << "\n\n";
		cout << "Berhasil mengubah tanggal! \n\n";
		pressAnyKey();
		break;

	case '4':
		todo[id - 1].selesai = !status;
		cout << "Berhasil mengubah status Todo! \n";
		pressAnyKey();
		break;

	default:
		break;
	}

	writeFiles(todo, jml, user);
}

void sortByDate(InfoTodo todo[], int jml, string tglStr[])
{
	int tglBaru[100];

	for (int i = 0; i < jml; i++)
	{
		// Tanggal yang sudah berbentuk array of integer
		int *tglInt = getDateInt(tglStr[i], i);

		tglBaru[i] = (tglInt[0] + 100 * tglInt[1] + 10000 * tglInt[2]);
	}

	sorting(todo, jml, tglBaru);
	readTodo(todo, jml);
	pressAnyKey();
}

void sortByStatus(InfoTodo todo[], int jml)
{
	/* Variabel untuk menyimpan kumpulan status yang telah
		 dikonversi ke bentuk integer
	 */
	int status[100];

	for (int i = 0; i < jml; i++)
		status[i] = (todo[i].selesai) ? 1 : 0;

	sorting(todo, jml, status);
	readTodo(todo, jml);
	pressAnyKey();
}

void sorting(InfoTodo todo[], int size, int sorter[])
{
	InfoTodo tempStruct;
	int i, j, temp;

	for (i = 0; i < size - 1; i++)
	{
		for (j = 0; j < size - i - 1; j++)
		{
			if (sorter[j] > sorter[j + 1])
			{
				// Sorting penyortirnya
				temp = sorter[j];
				sorter[j] = sorter[j + 1];
				sorter[j + 1] = temp;

				// Sorting todo
				tempStruct = todo[j];
				todo[j] = todo[j + 1];
				todo[j + 1] = tempStruct;
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
			pressAnyKey();

	} while (cariUlang == 'y' || cariUlang == 'Y');
}

void searchByDate(InfoTodo todo[], int jml, bool startDate)
{
	InfoTodo foundTodo[100];
	string dateInput;
	int *result;

	cout << "Masukkan tanggal: ";
	cin >> dateInput;

	result = multipleSearch(todo, jml, dateInput, startDate);

	for (int i = 0; i < result[0]; i++)
		foundTodo[i] = todo[result[i + 1]];

	if (result[0] != 0)
		readTodo(foundTodo, result[0]);
	else
		cout << "Todo tidak ditemukan. \n";

	cout << "\n";
	pressAnyKey();
}

int *multipleSearch(InfoTodo todo[], int jml, string input, bool startDate)
{
	int *res = new int[100];
	int resIndex = 1;
	bool isFound = 0;

	if (startDate)
	{
		for (int i = 0; i < jml; i++)
		{
			if (input == todo[i].startDate)
			{
				isFound = 1;
				res[resIndex] = i;
				resIndex++;
			}
		}
	}
	else
	{
		for (int i = 0; i < jml; i++)
		{
			if (input == todo[i].dueDate)
			{
				isFound = 1;
				res[resIndex] = i;
				resIndex++;
			}
		}
	}

	res[0] = (isFound) ? resIndex - 1 : 0;

	return res;
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

int *getDateInt(string date, int indeks)
{
	int *tgl = new int[4];

	if (!(date.length() < 9))
	{
		// Memisah tgl, bln, thn
		char day[] = {date[0], date[1], '\0'};
		char month[] = {date[3], date[4], '\0'};
		char year[] = {date[6], date[7], date[8], date[9], '\0'};

		tgl[0] = strToInt(day);
		tgl[1] = strToInt(month);
		tgl[2] = strToInt(year);
		tgl[3] = indeks;
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

char checkMark(bool status)
{
	return status ? 'v' : 'x';
}

void pressAnyKey()
{
	cout << "[Press any key to continue.]";
	getch();
	system(CLEAR);
}
