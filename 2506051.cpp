#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("用法: %s <源文件> <目标文件>\n", argv[0]);
        return 1;
    }

    FILE *src_file = fopen(argv[1], "rb");
    if (src_file == NULL)
    {
        perror("无法打开源文件");
        return 1;
    }

    FILE *dst_file = fopen(argv[2], "wb");
    if (dst_file == NULL)
    {
        perror("无法创建/打开目标文件");
        fclose(src_file);
        return 1;
    }

    int ch;
    while ((ch = fgetc(src_file)) != EOF)
    {
        fputc(ch, dst_file);
    }

    fclose(src_file);
    fclose(dst_file);
    printf("文件拷贝成功！\n");
    return 0;
}