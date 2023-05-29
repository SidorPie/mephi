#include <lab3-17b.h>

Item *table[SIZE]; // массив указателей на элементы таблицы

//Далее, реализуем функции поиска и вставки элементов в таблицу:

/* Вставка элемента в таблицу */
int insertElement(int key, char *info) {
  // Вычисление хеш-функции ключа элемента
  int index = hash(key);

  // Поиск последнего элемента с данным ключом
  Item *elem = NULL;
  int release = 0;
  for (elem = table[index]; elem != NULL; elem = elem->next) {
    if (elem->key == key) {
      release++;
    }
  }

  // Создание нового элемента
  Item *newElem = (Item *)malloc(sizeof(Item));
  newElem->key = key;
  newElem->release = release+1;
  newElem->info = (char *)malloc(sizeof(char) * (strlen(info) + 1));
  strcpy(newElem->info, info);
  newElem->next = NULL;

  // Добавление нового элемента в конец списка элементов с данным ключом
  if (table[index] == NULL) {
    table[index] = newElem;
  } else {
    Item *last = table[index];
    while (last->next != NULL) {
      last = last->next;
    }
    last->next = newElem;
  }

  return release+1;
}

/* Поиск элемента в таблице по ключу и номеру версии */
Item *findElement(int key, int release) {
  // Вычисление хеш-функции ключа элемента
  int index = hash(key);

  // Поиск элемента с заданным ключом и номером версии
  Item *elem = NULL;
  for(elem = table[index]; elem != NULL; elem = elem->next) {
    if(elem->key == key && elem->release == release) {
        return elem;
    }
  }

  // Элемент не найден
  return NULL;
}

/* Поиск всех элементов в таблице с заданным ключом */
Item **findAllElements(int key, int *count) {
  // Вычисление хеш-функции ключа элемента
  int index = hash(key);

  // Поиск числа элементов с заданным ключом
  *count = 0;
  Item *elem = NULL;
  for(elem = table[index]; elem != NULL; elem = elem->next) {
    if(elem->key == key) {
      (*count)++;
    }
  }

  // Создание массива указателей на элементы с заданным ключом
  Item **result = (Item **)malloc((*count) * sizeof(Item *));
  int i = 0;
  for(elem = table[index]; elem != NULL; elem = elem->next) {
    if(elem->key == key) {
      result[i++] = elem;
    }
  }

  // Возврат массива найденных элементов
  return result;
}

//Также, необходимы вспомогательные функции, такие как функция хеширования ключа, функции чтения/записи данных из файла и функции печати содержимого таблицы:

/* Хеш-функция для ключа элемента */
int hash(int key) {
  return key % SIZE;
}

/* Функция чтения числа */
int readNumber() {
    int result;
    scanf("%d", &result);
    return result;
}

/* Функция чтения строки */
char *readString() {
    char buffer[1024];
    scanf("%s", buffer);
    char *result = (char *)malloc(sizeof(char) * (strlen(buffer) + 1));
    strcpy(result, buffer);
    return result;
}

/* Функция записи таблицы в файл */
void writeTableToFile(char *filename) {
    // Открытие файла на запись
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Ошибка при открытии файла %s\n", filename);
        return;
    }

    // Запись каждого элемента таблицы в файл произвольного доступа
    for (int i=0; i<SIZE; i++) {
      Item *elem = table[i];
      while (elem != NULL) {
        // Запись ключа и номера версии элемента
        fwrite(&(elem->key), sizeof(int), 1, file);
        fwrite(&(elem->release), sizeof(int), 1, file);

        // Запись информации об элементе
        int infoSize = strlen(elem->info) + 1;
        fwrite(&(infoSize), sizeof(int), 1, file);
        fwrite(elem->info, sizeof(char), infoSize, file);

        elem = elem->next;
      }
    }

    // Закрытие файла
    fclose(file);
}

/* Функция чтения таблицы из файла */
void readTableFromFile(char *filename) {
    // Открытие файла на чтение
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Ошибка при открытии файла %s\n", filename);
        return;
    }

    // Удаление всех элементов из таблицы
    for (int i=0; i<SIZE; i++) {
      Item *elem = table[i];
      while (elem != NULL) {
        Item *next = elem->next;
        free(elem->info);
        free(elem);
        elem = next;
      }
      table[i] = NULL;
    }

    // Чтение каждого элемента таблицы из файла произвольного доступа
    while (1) {
        // Чтение ключа и номера версии элемента
        int key, release;
        int n = fread(&key, sizeof(int), 1, file);
        if (n == 0) {
          break;
        }
        fread(&release, sizeof(int), 1, file);

        // Чтение информации об элементе
        int infoSize;
        fread(&infoSize, sizeof(int), 1, file);
        char *info = (char *)malloc(sizeof(char) * infoSize);
        fread(info, sizeof(char), infoSize, file);

        // Вставка элемента в таблицу
        insertElement(key, info);
    }

    // Закрытие файла
    fclose(file);
}

/* Функция печати элемента */
void printElement(Item *elem) {
  printf("Ключ: %d, Номер версии: %d, Информация: %s\n", elem->key, elem->release, elem->info);
}

/* Функция печати всей таблицы */
void printTable() {
  for (int i=0; i<SIZE; i++) {
    Item *elem = table[i];
    while (elem != NULL) {
      printElement(elem);
      elem = elem->next;
    }
  }
}

//Далее, реализуем операцию "чистки" таблицы от устаревших элементов:
/* Удаление всех элементов таблицы, кроме последних */
void deleteObsoleteElements(int key) {
  // Вычисление хеш-функции ключа элемента
  int index = hash(key);

  // Поиск последнего элемента с данным ключом
  Item *last = NULL;
  for (Item *elem = table[index]; elem != NULL; elem = elem->next) {
    if (elem->key == key) {
      last = elem;
    }
  }

  // Удаление всех устаревших элементов с данным ключом
  Item *prev = NULL;
  for (Item *elem = table[index]; elem != NULL; elem = elem->next) {
    if (elem->key == key && elem != last) {
      if (prev == NULL) {
        table[index] = elem->next;
      } else {
        prev->next = elem->next;
      }
      free(elem->info);
      free(elem);
    }
    prev = elem;
  }
}

//Наконец, реализуем функцию итеративного ввода запросов оператора и обработки данных:
int Execute() {
  char *filename = readString();
  readTableFromFile(filename); // чтение таблицы из файла

  int exit = 0;
  while (!exit) {
    printf("Выберите действие:\n");
    printf("1. Включение нового элемента в таблицу\n");
    printf("2. Поиск элементов в таблице\n");
    printf("3. Чистка таблицы\n");
    printf("4. Вывод содержимого таблицы\n");
    printf("5. Выход из программы\n");

    int choice = readNumber();
    int key, release, count;
    char *info;
    switch (choice) {
      case 1: // Включение нового элемента в таблицу
        printf("Введите ключ элемента: ");
        key = readNumber();
        printf("Введите информацию об элементе: ");
        info = readString();
        release = insertElement(key, info);
        printf("Элемент добавлен в таблицу с номером версии %d\n", release);
        writeTableToFile(filename); // запись таблицы в файл
        break;
      case 2: // Поиск элементов в таблице
        printf("Введите ключ элемента: ");
        key = readNumber();
        printf("Введите номер версии элемента или 0 для поиска всех версий элемента: ");
        release = readNumber();
        if (release == 0) {
          Item **items = findAllElements(key, &count);
          printf("Найдено элементов: %d\n", count);
          for (int i=0; i<count; i++) {
            printElement(items[i]);
          }
        } else {
          Item *elem = findElement(key, release);
          if (elem == NULL) {
            printf("Элемент с заданным ключом и номером версии не найден\n");
          } else {
            printElement(elem);
          }
        }
        break;
      case 3: // Чистка таблицы
        printf("Введите ключ элемента: ");
        key = readNumber();
        deleteObsoleteElements(key);
        printf("Устаревшие элементы удалены из таблицы\n");
        writeTableToFile(filename); // запись таблицы в файл
        break;
      case 4: // Вывод содержимого таблицы
        printTable();
        break;
      case 5: // Выход из программы
        exit = 1;
        break;
      default:
        printf("Неверный выбор\n");
        break;
    }
  }

  return 0;
}