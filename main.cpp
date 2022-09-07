
#include <cctype>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

// Maps para los meses -> nombre, clave
map<string, int> months;
map<int, string> monthsR;

// Duracion de los meses
int monthDuration[12] = {31, 28, 29, 31, 30, 31, 30, 31, 31, 30, 30, 31};

// Estructura de datos de registro
struct Registry {
  string month;
  int day;
  int hour;
  int minute;
  int second;
  string ip;
  string error;

  // Funciones verificadoras de fechas
  bool dateIsEqual(Registry const &entry) const {
    if ((months[month] == months[entry.month] && day == entry.day) &&
        hour == entry.hour) {
      return true;
    } else {
      return false;
    }
  }

  bool dateIsMinor(Registry const &entry) const {
    if (months[month] < months[entry.month]) {
      return true;
    }
    if (months[month] == months[entry.month] && day < entry.day) {
      return true;
    }
    if (months[month] == months[entry.month] && day == entry.day &&
        hour < entry.hour) {
      return true;
    } else {
      return false;
    }
  }

  bool hourIsMinor(Registry const &entry) const {
    if (hour <= entry.hour) {
      return true;
    } else {
      return false;
    }
  }

  bool hourIsMajor(Registry const &entry) const {
    if (hour >= entry.hour) {
      return true;
    } else {
      return false;
    }
  }

  bool hourIsEqual(Registry const &entry) const {
    if (hour == entry.hour) {
      return true;
    } else {
      return false;
    }
  }
};

// Funcion para llenar valores del map de meses
void populateMonths() {
  months.insert(pair<string, int>("Jan", 1));
  months.insert(pair<string, int>("Feb", 2));
  months.insert(pair<string, int>("Mar", 3));
  months.insert(pair<string, int>("Apr", 4));
  months.insert(pair<string, int>("May", 5));
  months.insert(pair<string, int>("Jun", 6));
  months.insert(pair<string, int>("Jul", 7));
  months.insert(pair<string, int>("Aug", 8));
  months.insert(pair<string, int>("Sep", 9));
  months.insert(pair<string, int>("Oct", 10));
  months.insert(pair<string, int>("Nov", 11));
  months.insert(pair<string, int>("Dic", 12));
}

// Funcion para invertir key y value de mapa de meses
void populatemonthsR() { //
  for (auto i = months.begin(); i != months.end(); ++i)
    monthsR[i->second] = i->first;
}

// Funcion para desplegar entry
void printEntry(Registry entry) {
  cout << entry.month << " " << entry.day << " " << entry.hour << ":"
       << entry.minute << ":" << entry.second << " " << entry.ip << " "
       << entry.error << endl;
}

// Funcion para convertir en string un entry formateado
string stringEntry(Registry entry) {

  stringstream ss;

  ss << entry.month << " " << entry.day << " " << entry.hour << ":"
     << entry.minute << ":" << entry.second << " " << entry.ip << " "
     << entry.error << "\n";
  return ss.str();
}

// Funcion para imprimir todas las entries de logs
void printEntries(vector<Registry> list) {
  cout << endl << "-----------=Resultado=-----------" << endl << endl;
  for (int i = 0; i < list.size(); i++) {
    printEntry(list[i]);
  }
}

// Funcion para ver si una entry es previa a otra
bool isEarlier(Registry &first, Registry &last) {
  if (months[first.month] > months[last.month]) {

    return true;
  }
  if (months[first.month] == months[last.month] && first.day > last.day) {
    return true;
  }
  if (months[first.month] == months[last.month] && first.day == last.day &&
      first.hour > last.hour) {
    return true;
  }
  if (months[first.month] == months[last.month] && first.day == last.day &&
      first.hour == last.hour && first.minute > last.minute) {
    return true;
  }
  if (months[first.month] == months[last.month] && first.day == last.day &&
      first.hour == last.hour && first.minute == last.minute &&
      first.second > last.second) {
    return true;
  } else {

    return false;
  }
}

// O(n)
// Funcion para dividir string por token o separador
vector<string> split(string str, string token) {
  vector<string> result;
  while (str.size()) {
    int index = str.find(token);
    if (index != string::npos) {
      result.push_back(str.substr(0, index));
      str = str.substr(index + token.size());
      if (str.size() == 0)
        result.push_back(str);
    } else {
      result.push_back(str);
      str = "";
    }
  }
  return result;
}

// O(n)
// Funcion para pasar a lowercase string
string toLowerCase(string str) {

  int str_len = str.length();

  string final_str = "";

  for (int i = 0; i < str_len; i++) {

    char character = str[i];

    if (character >= 65 && character <= 92) {

      final_str += (character + 32);

    } else {

      final_str += character;
    }
  }

  return final_str;
}

// Funcion para formatear el string de una fecha para ser valido
string monthFormater(string txt) {
  string txtMod = toLowerCase(txt);
  txtMod[0] = toupper(txtMod[0]);
  return txtMod;
}

// Sorting
template <class T>
void merge(vector<T> &list, int left, int middle, int right) {
  int i = 0, j = 0;
  int counter = left;
  vector<T> vectorLeft, vectorRight;

  // Copy to new vectors
  for (int iter1 = left; iter1 <= middle; iter1++) {
    vectorLeft.push_back(list[iter1]);
  }
  for (int iter2 = middle + 1; iter2 <= right; iter2++) {
    vectorRight.push_back(list[iter2]);
  }

  while (i < (middle - left + 1) && j < (right - middle)) {

    if (isEarlier(vectorLeft[i], vectorRight[j])) {
      list[counter] = vectorRight[j];
      j++;
    } else {
      list[counter] = vectorLeft[i];
      i++;
    }
    counter++;
  }

  while (i < (middle - left + 1)) {
    list[counter] = vectorLeft[i];
    counter++;
    i++;
  }
  while (j < (right - middle)) {
    list[counter] = vectorRight[j];
    counter++;
    j++;
  }
}

// O(nlogn)

template <class T> void mergeSort(vector<T> &list, int left, int right) {
  if (left < right) {
    int middle = left + (right - left) / 2;
    mergeSort(list, left, middle);
    mergeSort(list, middle + 1, right);

    merge(list, left, middle, right);
  }
}

// Searching

// O(log n)

int lowerIndexQuery(vector<Registry> &list, Registry &value) {
  int low, high, mid;
  int result = -1;
  low = 0;
  high = list.size();
  while (low <= high) {
    mid = (low + high) / 2;

    if (list[mid].dateIsEqual(value)) {
      result = mid;
      high = mid - 1;
    } else if (list[mid].dateIsMinor(value)) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }

  if (result != -1) {
    return result;
  }

  string newMonth;
  int newDay;

  if (value.day <= monthDuration[months[value.month] - 1]) {
    newMonth = value.month;
    newDay = value.day + 1;
  } else {
    newMonth = monthsR[months[value.month] + 1];
    newDay = 1;
  }

  Registry lower{newMonth, newDay, 0, 0, 0, "", ""};

  return lowerIndexQuery(list, lower);
}

// O(log n)

int upperIndexQuery(vector<Registry> &list, Registry &value) {
  int low, high, mid;
  low = 0;
  int result = -1;
  high = list.size();
  while (low <= high) {
    mid = (low + high) / 2;

    if (list[mid].dateIsEqual(value)) {
      result = mid;
      low = mid + 1;
    } else if (list[mid].dateIsMinor(value)) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }

  if (result != -1) {
    return result;
  }

  string newMonth;
  int newDay;

  if (value.day <= monthDuration[months[value.month] - 1] &&
      (value.day - 1) > 0) {
    newMonth = value.month;
    newDay = value.day - 1;
  } else {
    newMonth = monthsR[months[value.month] - 1];
    newDay = monthDuration[months[newMonth] - 1];
  }

  Registry upper{newMonth, newDay, 0, 0, 0, "", ""};

  return upperIndexQuery(list, upper);
}

// O(n)
// Resultado de las busquedas
string queryDates(vector<Registry> &list, int lower, int upper) {
  string dates = "";
  for (int i = lower; i <= upper; i++) {
    dates = dates + (stringEntry(list[i]));
  }
  return dates;
}

// O(m)

void print(vector<string> list) {
  for (int i = 0; i < list.size(); i++) {
    cout << list[i] << endl;
  }
  cout << endl;
}

void optionMenu() {
  cout << endl;
  cout << "1) Mostrar la bitacora" << endl;
  cout << "2) Buscar registros por fecha" << endl;
  cout << "3) Salir" << endl << endl;
}

// Funcion para hacer query de una fecha
void fetchQuery(vector<Registry> &list) {
  time_t rawtime;
  struct tm *timeinfo;
  char buffer[80];

  time(&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(buffer, sizeof(buffer), "%d-%m-%Y %H-%M-%S", timeinfo);
  std::string str(buffer);

  string lowerMonth, upperM, save, fetched;
  int lowerDay, upperDay, inputHourLower, inputHourUpper;
  bool continues = false;

  while (!continues) {
    cout << "Ingresa las primeras 3 letras del mes inicial >";
    cin >> lowerMonth;
    lowerMonth = monthFormater(lowerMonth);
    cout << "Ingresa el dia del mes inicial >";
    while (!(cin >> lowerDay)) {
      cout << endl << "ERROR: INVALID INPUT" << endl << endl;
      cout << endl << "Ingresa el dia del mes inicial >";
      cin.clear();
      cin.ignore(123, '\n');
    }
    cout << "Ingresa la hora >";
    while (!(cin >> inputHourLower)) {
      cout << endl << "ERROR: INVALID INPUT" << endl << endl;
      cout << endl << "Ingresa la hora >";
      cin.clear();
      cin.ignore(123, '\n');
    }

    cout << endl << "Ingresa las primeras 3 letras del mes final >";
    cin >> upperM;
    upperM = monthFormater(upperM);
    cout << "Ingresa el dia del mes final >";
    while (!(cin >> upperDay)) {
      cout << endl << "ERROR: INVALID INPUT" << endl << endl;
      cout << "Ingresa el dia del mes final >";
      cin.clear();
      cin.ignore(123, '\n');
    }
    cout << "Ingresa la hora >";
    while (!(cin >> inputHourUpper)) {
      cout << endl << "ERROR: INVALID INPUT" << endl << endl;
      cout << "Ingresa la hora >";
      cin.clear();
      cin.ignore(123, '\n');
    }

    if (months.find(lowerMonth) == months.end() &&
        months.find(upperM) == months.end()) {
      cout << endl << "INVALID INPUT" << endl << endl;
    } else {
      if (months[lowerMonth] <= months[upperM]) {
        if ((lowerDay > 0 && lowerDay < 31) ||
            (upperDay > 0 && lowerDay < 31)) {
          continues = true;
        } else {
          cout << endl
               << "INVALID INPUT, VERIFY MONTH AND DESIRED DATES" << endl
               << endl;
        }
      } else {
        cout << endl
             << "INVALID INPUT, VERIFY MONTH AND DESIRED DATES" << endl
             << endl;
      }
    }
  }

  cout << endl << "Would you like to save the result on a file (yes/no) >";
  cin >> save;

  save = toLowerCase(save);

  cout << endl << "-----------=Resultado=-----------" << endl << endl;

  Registry lower{lowerMonth, lowerDay, inputHourLower, 0, 0, " ", " "};
  Registry upper{upperM, upperDay, inputHourUpper, 0, 0, " ", " "};
  try {
    if (months[lower.month] >= months[list[0].month] &&
        months[upper.month] <= months[list[list.size() - 1].month]) {

      int lowerIndex = lowerIndexQuery(list, lower);
      int upperIndex = upperIndexQuery(list, upper);

      fetched = queryDates(list, lowerIndex, upperIndex);

      cout << fetched << endl;

      if (save == "yes") {
        ofstream out(str + ".txt");
        out << fetched;
        out.close();
      }
    } else {
      cout << "INTRODUZCA UN RANGO VALIDO" << endl
           << endl;
    }
  } catch (const exception &e) {
    cout << "ERROR" << endl << endl;
  }
}

void menu(vector<Registry> list) {

  cout << endl << "Cargando bitacora ";

  cout << endl;

  cout << endl
       << "EXITO: " << list.size() << " Las entradas se han cargado " << endl
       << endl;
  cout << "REGISTROS: (" << list[0].month << " - " << list[list.size() - 1].month
       << ")" << endl
       << endl;
  ;

  bool continues = true;
  int selection;
  string lowerMonth, upperMonth;
  int saveQuery;

  while (continues) {
    optionMenu();
    cout << "Seleccion >";
    while (!(cin >> selection)) {
      cout << endl << "OPCION NO VALIDA" << endl << endl;
      cout << "Seleccion >";
      cin.clear();
      cin.ignore(123, '\n');
    }
    cout << endl;
    switch (selection) {
    case 1:
      printEntries(list);
      cout << endl;
      ;
      break;
    case 2:
      fetchQuery(list);
      cout << endl;
      ;
      break;
    case 3:
      continues = false;
      break;
    default:
      cout << endl;
      ;
      cout << endl << "OPCION NO VALIDA" << endl << endl;
      ;
      break;
    }
  }
  cout << endl;
  ;
  cout << endl
       << "FAILED LOGIN REGISTRY | TERMINATED SUCCESSFULLY" << endl
       << endl;
  ;
}

int main() {
  populateMonths();
  populatemonthsR();

  ifstream file("bitacora.txt");
  vector<Registry> entries;

  if (file.is_open()) {
    string line;
    vector<string> words;
    vector<string> time;
    string errorString = ""; 

    int i = 0;
    while (getline(file,
                   line)) {
      words = split(line, " ");
      
      Registry entry; 
      entry.month = words[0];
      entry.day = stoi(words[1]);
      time = split(words[2], ":");
      entry.hour = stoi(time[0]); //
      entry.minute = stoi(time[1]);
      entry.second = stoi(time[2]);
      entry.ip = words[3];
      for (int i = 4; i < words.size();
           i++) { 
        if (i != 4 && i != words.size()) {
          errorString = errorString + " " + words[i];
        } else {
          errorString += words[i];
        };
      }

      entry.error = errorString;
      entries.push_back(entry); 
      errorString = "";
      words.clear();
      time.clear();

      i++;
    }
    file.close();
  }

  mergeSort(entries, 0, entries.size() - 1);

  menu(entries);

  return 0;
}
