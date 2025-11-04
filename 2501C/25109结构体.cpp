#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_LEN 100

// 图书结构体定义
typedef struct
{
    char isbn[MAX_LEN];      // ISBN号
    char title[MAX_LEN];     // 书名
    float price;             // 定价
    char author[MAX_LEN];    // 作者
    char publisher[MAX_LEN]; // 出版社
} Book;

// 插入图书
int insertBook(Book books[], int *size, Book newBook)
{
    if (*size >= MAX_BOOKS)
    {
        printf("无法插入，图书数组已满。\n");
        return 0;
    }

    for (int i = 0; i < *size; i++)
    {
        if (strcmp(books[i].isbn, newBook.isbn) == 0)
        {
            printf("插入失败，已有相同ISBN的图书。\n");
            return 0;
        }
    }

    books[*size] = newBook;
    (*size)++;
    printf("图书插入成功。\n");
    return 1;
}

// 删除图书
int deleteBook(Book books[], int *size, const char *isbn)
{
    for (int i = 0; i < *size; i++)
    {
        if (strcmp(books[i].isbn, isbn) == 0)
        {
            for (int j = i; j < *size - 1; j++)
            {
                books[j] = books[j + 1];
            }
            (*size)--;
            printf("图书删除成功。\n");
            return 1;
        }
    }
    printf("未找到对应ISBN的图书，删除失败。\n");
    return 0;
}

// 打印图书信息
void printBooks(Book books[], int size)
{
    if (size == 0)
    {
        printf("当前无图书记录。\n");
        return;
    }

    printf("当前图书列表：\n");
    for (int i = 0; i < size; i++)
    {
        printf("ISBN: %s | 书名: %s | 定价: %.2f | 作者: %s | 出版社: %s\n",
               books[i].isbn, books[i].title, books[i].price,
               books[i].author, books[i].publisher);
    }
}

int main()
{
    Book library[MAX_BOOKS];
    int size = 0;

    while (1)
    {
        int choice;
        printf("\n1. 插入图书\n");
        printf("2. 删除图书\n");
        printf("3. 打印图书\n");
        printf("4. 退出\n");
        printf("请选择：");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            Book newBook;
            printf("请输入图书信息（ISBN 书名 定价 作者 出版社）：\n");
            scanf("%s %s %f %s %s", newBook.isbn, newBook.title, &newBook.price, newBook.author, newBook.publisher);
            insertBook(library, &size, newBook);
            break;
        }
        case 2:
        {
            char isbn[MAX_LEN];
            printf("请输入要删除的图书的ISBN：");
            scanf("%s", isbn);
            deleteBook(library, &size, isbn);
            break;
        }
        case 3:
            printBooks(library, size);
            break;
        case 4:
            printf("程序已退出。\n");
            return 0;
        default:
            printf("输入错误，请重新输入。\n");
            break;
        }
    }

    return 0;
}
