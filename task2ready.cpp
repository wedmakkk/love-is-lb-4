#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <locale.h>

struct Node {
	int data;
	struct Node* left;
	struct Node* right;
};

struct Result { // Структура для возврата двух значений
	int level;
	int count;
};

struct Node* root;

struct Node* CreateTree(struct Node* root, struct Node* r, int data)
{
	if (r == NULL)
	{
		r = (struct Node*)malloc(sizeof(struct Node));
		if (r == NULL)
		{
			printf("Ошибка выделения памяти");
			exit(0);
		}

		r->left = NULL;
		r->right = NULL;
		r->data = data;
		if (root == NULL) return r;

		if (data > root->data)	root->left = r;
		else root->right = r;
		return r;
	}

	if (data > r->data)
		CreateTree(r, r->left, data);
	else
		CreateTree(r, r->right, data);

	return root;
}

void print_tree(struct Node* r, int l)
{

	if (r == NULL)
	{
		return;
	}

	print_tree(r->right, l + 1);
	for (int i = 0; i < l; i++)
	{
		printf(" ");
	}

	printf("%d\n", r->data);
	print_tree(r->left, l + 1);
}
struct Result find(struct Node* root, int data, int cnt, int lvl) {
	struct Result res = { lvl, cnt }; // Инициализация структуры результата

	if (root == NULL) {
		return res; // Возвращаем, если узел пуст
	}

	if (root->data == data) {
		res.count++; // Увеличиваем счетчик
	}

	// Ищем в правом поддереве
	if (root->data >= data && root->right != NULL) {
		return find(root->right, data, res.count, lvl + 1); // Поиск в правом поддереве
	}
	// Ищем в левом поддереве
	else if (root->left != NULL) {
		return find(root->left, data, res.count, lvl + 1); // Поиск в левом поддереве
	}

	return res; // Возвращаем структуру результата
}

int main()
{
	setlocale(LC_ALL, "");
	int D, start = 1;

	root = NULL;
	printf("-1 - окончание построения дерева\n");
	while (start)
	{
		printf("Введите число: ");
		scanf_s("%d", &D);
		if (D == -1)
		{
			printf("Построение дерева окончено\n\n");
			start = 0;
		}
		else
			root = CreateTree(root, root, D);

	}

	print_tree(root, 0);


	printf("\nВведите число: ");
	int num,lvl;
	scanf_s("%i", &num);
	struct Result result = find(root, num, 0, 0); // Получаем результат
	printf("Количество: %d, Уровень: %d\n", result.count, result.level);
	getchar();
	getchar();
	getchar();
	return 0;
}