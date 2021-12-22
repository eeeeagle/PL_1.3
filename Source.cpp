#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <string.h>
char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZабвгдеЄжзийклмнопрстуфхцчшщъыьэю€јЅ¬√ƒ≈®∆«»… ЋћЌќѕ–—“”‘’÷„ЎўЏџ№Ёёя";

void clear(char *original, char *edited) 
{
	memset(original, 0, sizeof original);
	memset(edited, 0, sizeof edited);
}

void output(bool check, char original[512], char edited[512]) 
{
	system("cls");
	if (check == false)
		printf("¬ введеном тексте нет заданной буквы.\n========================\n\n");
	printf("»сходный текст:\n\n");
	puts(original);
	if (check) 
	{
		printf("========================\n\n»зменЄнный текст:\n\n");
		puts(edited);
	}
	printf("\n\n\n");
	getchar();
	getchar();
}

bool ending() 
{
		system("cls");
		printf("ƒл€ продолжени€ работы нажмите любую клавишу. ƒл€ завершени€ - ESC.");
		return (27 != _getch());
}

bool is_alpha(char symbol) 
{
	return strchr(alphabet, symbol) != NULL;
}

int to_lower(int s) 
{
	if (s == -88) 
		return -72; // дл€ ® и Є
	if ((s >= 65 && s <= 90) || (s >= -64 && s <= -33))
		return s + 32;
	else
		return s;
}

void highlight_word(int f, int l, char *edited) 
{
	int j = f;
	for (int i = strlen(edited) + 1; i > j; i--) 
	{
		edited[i] = edited[i - 1];
	}
	edited[j] = '(';
	j = l + 1;
	for (int i = strlen(edited) + 1; i > j; i--) 
	{
		edited[i] = edited[i - 1];
	}
	edited[j + 1] = ')';
}

void reverse_word(int fsym, int lsym, char *edited) 
{
	while (fsym < lsym) 
	{
		char temp = edited[fsym];
		edited[fsym] = edited[lsym];
		edited[lsym] = temp;
		fsym++, lsym--;
	}
}

char change_sym() 
{
	char newSym;
	getchar();
	printf("ќбнаружена введена€ буква. ¬ведите новую дл€ еЄ замены: ");
	do 
	{
		scanf_s("%c", &newSym, 1);
		if (is_alpha(newSym) == false) 
		{
			system("cls");
			printf("¬вести можно только букву. ѕовторите ввод: ");
		}
	} while (is_alpha(newSym) == false);
	return newSym;
}

bool edit_word(int fsym, int lsym, char *edited, char sym, char* newSym) 
{
	int count = 0;
	if(to_lower(edited[fsym]) == to_lower(sym))
		return false;
	for (int i = fsym + 1; i < lsym; i++) 
	{
		if (to_lower(edited[i]) == to_lower(sym)) 
		{
			if(*newSym == 0)
				*newSym = change_sym();
			edited[i] = *newSym;
			count++;
		}
	}
	if (to_lower(edited[lsym]) == to_lower(sym)) 
	{
		reverse_word(fsym, lsym, edited);
		count++;
	}
	if (count) 
		highlight_word(fsym, lsym, edited);
	return (count > 0);
}

bool find_word(char* edited, char sym)
{
	int fsym = 0, lsym = 0, count = 0;
	char newSym=0;
	for (unsigned s = 1; s < (strlen(edited) + 1); s++) 
	{
		if (is_alpha(edited[s - 1]) == false) 
			fsym = s;
		if (is_alpha(edited[s + 1]) == false) 
		{
			lsym = s;
			if (edit_word(fsym, lsym, edited, sym, &newSym))
			{
				count++;
				s += 2;
			}
		}
	}
	return (count > 0);
}

int main() 
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	do 
	{
		char original[512], edited[512], sym;
		system("cls");
		clear(original, edited);
		printf("¬ведите текст в виде одной или нескольких строк:\n(дл€ прекращени€ ввода оставьте пустое поле ввода)\n\n");
		char string[100];
		do
		{
			gets_s(string, 99);
			strcat_s(original, 512, string);
			strcat_s(original, 512, "\n");
		} while (string[0]);
		system("cls");
		printf("¬ведите любую букву: ");
		do
		{
			scanf_s("%c", &sym, 1);
			if (is_alpha(sym) == false)
			{
				system("cls");
				printf("¬вести можно только букву. ѕовторите ввод: ");
			}
		} while (is_alpha(sym) == false);
		strcpy_s(edited, original);

		output(find_word(edited, sym), original, edited);
	} while (ending());
	return 0;
}